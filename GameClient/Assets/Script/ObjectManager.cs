﻿using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//오브젝트를 생성하고 관리해주는 함수
public class ObjectManager : MonoBehaviour
{
    public static ObjectManager instance;

    private object lockObject = new object();

    private bool FistCreateComplete = false;
    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
        }
        else
        {
            Destroy(this.gameObject);
        }
        NetWork.instance.ReConnect(8081);
    }

    public void SetObject(InputMemoryStream inInputStream)
    {
        short Count = 0;
        
        inInputStream.Read(ref Count);
        if (Count != 0)
        {
            PlayerSet(inInputStream, Count);
        }
        inInputStream.Read(ref Count);
        MonsterSet(inInputStream, Count);
    }

    private void PlayerSet(InputMemoryStream inInputStream,short Count)
    {
        lock(lockObject)
        {
            for (int i = 0; i < Count; ++i)
            {
                string name = "";
                inInputStream.Read(ref name);
                short state = 0;
                inInputStream.Read(ref state);
                if (state == Defines.USER_OUT)
                {
                    PlayerManager.instance.DelteUser(name);
                }
                else
                {
                    Vector3 _pos = Vector3.zero;
                    inInputStream.Read(ref _pos);
                    Vector3 _dir = Vector3.zero;
                    inInputStream.Read(ref _dir);
                    PlayerManager.instance.SearchPlayer(name, _pos, _dir, state);
                }

            }
        }
    }

    private void MonsterSet(InputMemoryStream inInputStream,short Count)
    {
        lock(lockObject)
        {
            for (int i = 0; i < Count; i++)
            {
                int _id = 0;
                Vector3 _pos = new Vector3();
                Vector3 _dir = new Vector3();
                float _hp = 0;
                inInputStream.Read(ref _id);
                inInputStream.Read(ref _pos);
                inInputStream.Read(ref _dir);
                inInputStream.Read(ref _hp);
                MonsterManager.instance.SearchMonster(_id, _pos, _dir, _hp);
            }

            if(!FistCreateComplete)
            {
                OutputMemoryStream os = new OutputMemoryStream();
                os.Write((short)Defines.SET_COMPLETE);
                NetWork.instance.Send(os);
                FistCreateComplete = true;
            }
        }
      
    }
}
