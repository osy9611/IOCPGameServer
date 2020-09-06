#pragma once
#pragma waring(disable :4819)
#define _WINSOCKAPI_
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<WS2tcpip.h>
#include<Windows.h>
#include<cassert>

#include"memory.h"
#include<iostream>
#include<atltime.h>
#include<vector>
#include<deque>
#include<queue>
#include<string>
#include<conio.h>
#include<sysinfoapi.h>
#include"cassert"
#include"unordered_set"
#include"unordered_map"
#include<random>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

class GameObject;
class GameObjectManager;
class PacketProc;
class MonsterManager;
class PlayerManager;

#include"Math.h"


#include"CriticalSection.h"
#include"GlobalSingleton.h"

#include"MemoryStream.h"
#include"PacketProc.h"

#include"IOCP.h"
#include"ServerSession.h"

#include"GameObjectManager.h"
#include"GameObject.h"
#include"FrameManager.h"

#include"Monster.h"
#include"MonsterManager.h"

#include "Player.h"
#include "PlayerManager.h"

#include"DBManager.h"

#ifndef CONCATENATE
#define CONCATENATE( arg1, arg2 )   _CONCATENATE1( arg1, arg2 )
#define _CONCATENATE1( arg1, arg2 )  _CONCATENATE2( arg1, arg2 )
#define _CONCATENATE2( arg1, arg2 )  arg1##arg2	//## : �����ڿ� �� �ĺ��ڸ� �ϳ��� �����ϴ� ������
#endif

#define DUMMY_STATEMENT	CONCATENATE(unsigned int  _DUMMY, __LINE__) =0; \
	CONCATENATE(_DUMMY,__LINE__) +=1;


