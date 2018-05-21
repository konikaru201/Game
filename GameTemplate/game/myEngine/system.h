#pragma once

#include "myEngine/Graphics/EffectManager.h"
#include "myEngine/Sound/SoundEngine.h"

extern LPDIRECT3D9				g_pD3D;		
extern LPDIRECT3DDEVICE9		g_pd3dDevice;
extern EffectManager*			g_effectManager;
extern CSoundEngine*			g_soundEngine;

const int NUM_COIN = 1000;
extern IDirect3DVertexBuffer9*  worldMatrixBuffer;
extern IDirect3DVertexDeclaration9* vertexDecl;
extern D3DXMATRIX IWorldMatrix[NUM_COIN];

const int FRAME_BUFFER_WIDTH = 1280;
const int FRAME_BUFFER_HEIGHT = 720;