#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define USE_ORTHO_PROJECTION

/*!
* @brief	定義でDirectX9で動作
*/
#define TK_PLATFORM_DX9

#define BUILD_LEVEL_DEBUG		0		//デバッグビルド
#define BUILD_LEVEL_PREVIEW		1		//プレビュービルド
#define BUILD_LEVEL_MASTER		2		//マスタービルド。

/*!
* @brief	ビルドレベル。
* @details
*  BUILD_LEVELはBUILD_LEVEL_DEBUG、BUILD_LEVEL_PREVIEW、BUILD_LEVEL_MASTER</br>
*	の３つの値をとります。この３つの値は下記の意味を持ちます。
*		BUILD_LEVEL_DEBUG		完全なデバッグビルド。
*		BUILD_LEVEL_PREVIEW		コードは最適化されているが、デバッグ機能は残っている。
*		BUILD_LEVEL_MASTER		マスタービルド。デバッグ機能は完全に削除されている。
* デバッグコードを埋め込む時は、BUILD_LEVEL_MASTERでは無効になるように実装してください。
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
