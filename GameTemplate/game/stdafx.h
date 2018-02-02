#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define USE_ORTHO_PROJECTION

/*!
* @brief	��`��DirectX9�œ���
*/
#define TK_PLATFORM_DX9

#define BUILD_LEVEL_DEBUG		0		//�f�o�b�O�r���h
#define BUILD_LEVEL_PREVIEW		1		//�v���r���[�r���h
#define BUILD_LEVEL_MASTER		2		//�}�X�^�[�r���h�B

/*!
* @brief	�r���h���x���B
* @details
*  BUILD_LEVEL��BUILD_LEVEL_DEBUG�ABUILD_LEVEL_PREVIEW�ABUILD_LEVEL_MASTER</br>
*	�̂R�̒l���Ƃ�܂��B���̂R�̒l�͉��L�̈Ӗ��������܂��B
*		BUILD_LEVEL_DEBUG		���S�ȃf�o�b�O�r���h�B
*		BUILD_LEVEL_PREVIEW		�R�[�h�͍œK������Ă��邪�A�f�o�b�O�@�\�͎c���Ă���B
*		BUILD_LEVEL_MASTER		�}�X�^�[�r���h�B�f�o�b�O�@�\�͊��S�ɍ폜����Ă���B
* �f�o�b�O�R�[�h�𖄂ߍ��ގ��́ABUILD_LEVEL_MASTER�ł͖����ɂȂ�悤�Ɏ������Ă��������B
*/
#ifdef _DEBUG
#define BUILD_LEVEL		BUILD_LEVEL_DEBUG
#elif defined(TK_MASTER)
#define BUILD_LEVEL		BUILD_LEVEL_MASTER
#else
#define BUILD_LEVEL		BUILD_LEVEL_PREVIEW
#endif

#if defined( TK_PLATFORM_DX9 )
#include <windows.h>
#include <mmsystem.h>
#endif // #if defined( TK_PLATFORM_DX9 )
#include <memory>
#include <d3dx9.h>
#include <d3d9.h>
#include <XInput.h> // XInput API
#include <xaudio2.h>
#include <x3daudio.h>
#include <xaudio2fx.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"X3DAudio.lib")
#ifdef _DEBUG
#include <DxErr.h>
#pragma comment(lib, "dxerr.lib")
#endif
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <string>


#include <d3dx9effect.h>
#pragma warning( disable : 4996 ) 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <cstdlib>
#include <memory>

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

#include "myEngine/System.h"

#include "myEngine/Graphics/Camera.h"
#include "myEngine/Graphics/SkinModel.h"
#include "myEngine/Graphics/SkinModelData.h"
#include "myEngine/Graphics/Animation.h"
#include "myEngine/Graphics/Light.h"
#include "myEngine/Graphics/RenderTarget.h"
#include "myEngine/Timer/Timer.h"

extern CRenderTarget* mainRenderTarget;
extern void DrawQuadPrimitive();
