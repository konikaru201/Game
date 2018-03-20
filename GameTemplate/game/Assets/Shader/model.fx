/*!
 * @brief	�X�L�����f���V�F�[�_�[�B(4�{�[���X�L�j���O)
 */

#include "LightingFunction.h"

//�X�L���s��B
#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4    g_mViewProj : VIEWPROJECTION;
float		g_numBone;			//���̐��B

float4x4	g_worldMatrix;			//!<���[���h�s��B
float4x4	g_rotationMatrix;		//!<��]�s��B
float4x4	g_viewMatrixRotInv;		//!<�J�����̉�]�s��̋t�s��B
float3		vEyePos;

bool g_isShadowReciever;				//�V���h�E���V�[�o�[�H�P�Ȃ�V���h�E���V�[�o�[�B
float4x4 g_lightViewMatrix;			//���C�g�r���[�s��B
float4x4 g_lightProjectionMatrix;	//���C�g�v���W�F�N�V�����s��B

bool g_isHasSpecularMap;		//�X�y�L�����}�b�v�ێ����Ă���H
bool g_isHasNormalMap;			//�@���}�b�v�ێ����Ă���H
bool g_isHasCubeMap;			//�L���[�u�}�b�v�ێ����Ă���H

float g_alpha;			//�����x

texture g_diffuseTexture;		//�f�B�t���[�Y�e�N�X�`���B
sampler g_diffuseTextureSampler = 
sampler_state
{
	Texture = <g_diffuseTexture>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
    AddressU = Wrap;
	AddressV = Wrap;
};

//�@���}�b�v
texture g_normalTexture;
sampler g_normalMapSampler = 
sampler_state
{
	Texture = <g_normalTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = Wrap;
	AddressV = Wrap;
};

//�X�y�L�����}�b�v
texture g_specularTexture;
sampler g_specularMapSampler =
sampler_state
{
	Texture = <g_specularTexture>;
	 MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
    AddressU = Wrap;
	AddressV = Wrap;
};

texture g_shadowMapTexture;		//�V���h�E�}�b�v�e�N�X�`���B
sampler g_shadowMapTextureSampler = 
sampler_state
{
	Texture = <g_shadowMapTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = CLAMP;
	AddressV = CLAMP;
};

//�L���[�u�}�b�v
texture g_cubeTexture;
sampler g_cubeMapSampler = 
sampler_state
{
	Texture = <g_cubeTexture>;
	MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = Wrap;
	AddressV = Wrap;
};

/*!
 * @brief	���͒��_
 */
struct VS_INPUT
{
    float4  Pos             : POSITION;
    float4  BlendWeights    : BLENDWEIGHT;
    float4  BlendIndices    : BLENDINDICES;
    float3  Normal          : NORMAL;
    float3	Tangent			: TANGENT;		//�ڃx�N�g��
    float3  Tex0            : TEXCOORD0;
};

/*!
 * @brief	�o�͒��_�B
 */
struct VS_OUTPUT
{
	float4  Pos     		: POSITION;
    float3  Normal			: NORMAL;
    float2  Tex0   			: TEXCOORD0;
    float3	Tangent			: TEXCOORD1;	//�ڃx�N�g��
	float3	worldPos		: TEXCOORD2;
	float4	lightViewPos 	: TEXCOORD3;		//���[���h���->���C�g�r���[���->���C�g�ˉe��Ԃɕϊ����ꂽ���W�B
	float4  PosInProj		: TEXCOORD4;
};
/*!
 *@brief	���[���h���W�ƃ��[���h�@�����X�L���s�񂩂�v�Z����B
 *@param[in]	In		���͒��_�B
 *@param[out]	Pos		���[���h���W�̊i�[��B
 *@param[out]	Normal	���[���h�@���̊i�[��B
 *@param[out]	Tangent	���[���h�ڃx�N�g���̊i�[��B
 */
void CalcWorldPosAndNormalFromSkinMatrix( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = 0.0f;
	Normal = 0.0f;
	Tangent = 0.0f;
	//�u�����h����{�[���̃C���f�b�N�X�B
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
	
	//�u�����h���[�g�B
	float BlendWeightsArray[4] = (float[4])In.BlendWeights;
    int   IndexArray[4]        = (int[4])IndexVector;
    float LastWeight = 0.0f;
    for (int iBone = 0; iBone < g_numBone-1; iBone++)
    {
        LastWeight = LastWeight + BlendWeightsArray[iBone];
        
        Pos += mul(In.Pos, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        Normal += mul(In.Normal, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        Tangent += mul(In.Tangent, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
    }
    LastWeight = 1.0f - LastWeight; 
    
	Pos += (mul(In.Pos, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
    Normal += (mul(In.Normal, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
    Tangent += (mul(In.Tangent, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
}
/*!
 *@brief	���[���h���W�ƃ��[���h�@�����v�Z�B
 *@param[in]	In		���͒��_�B
 *@param[out]	Pos		���[���h���W�̊i�[��B
 *@param[out]	Normal	���[���h�@���̊i�[��B
 *@param[out]	Tangent	���[���h�ڃx�N�g���̊i�[��B
 */
void CalcWorldPosAndNormal( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = mul(In.Pos, g_worldMatrix );
	Normal = mul(In.Normal, g_rotationMatrix );
	Tangent = mul(In.Tangent, g_rotationMatrix );
}
/*!
 *@brief	���_�V�F�[�_�[�B
 *@param[in]	In			���͒��_�B
 *@param[in]	hasSkin		�X�L������H
 */
VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if(hasSkin){
		//�X�L������B
	    CalcWorldPosAndNormalFromSkinMatrix( In, Pos, Normal, Tangent );
	}else{
		//�X�L���Ȃ��B
		CalcWorldPosAndNormal( In, Pos, Normal, Tangent );
	}
	o.worldPos = Pos;
    o.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	o.PosInProj = o.Pos;
    o.Normal = normalize(Normal);
    o.Tangent = normalize(Tangent);
    o.Tex0 = In.Tex0;

	if(g_isShadowReciever){
		//�V���h�E���V�[�o�[�B
		//���[���h���W�����C�g�J�������猩���ˉe��Ԃɕϊ�����B
		o.lightViewPos = mul(float4(o.worldPos,1.0f), g_lightViewMatrix);
		o.lightViewPos = mul(o.lightViewPos, g_lightProjectionMatrix);
	}

	return o;
}
/*!
 * @brief	�s�N�Z���V�F�[�_�[�B
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	float4 color = tex2D(g_diffuseTextureSampler, In.Tex0);
	float3 normal = In.Normal;
	
	if(g_isHasNormalMap){
		float3 localNormal = tex2D(g_normalMapSampler,In.Tex0);
		localNormal = (localNormal * 2.0f) - 1.0f;
		float3 tangent = normalize(In.Tangent);
		float3 biNormal = cross(tangent, normal);
		biNormal = normalize(biNormal);
		normal = tangent * localNormal.x
				+ biNormal * localNormal.y
				+ normal * localNormal.z;
	}
	
	float3 eye = In.worldPos.xyz - vEyePos;
	float3 L = -g_light.diffuseLightDir[0];
	float3 N = normal.xyz;
	float3 R = eye + 2.0f * dot(N, -eye) * N;
	R = normalize (R);

	float4 lig = DiffuseLight(normal);
	
	float4 spec;
	if(g_isHasSpecularMap){
		//�X�y�L�����}�b�v������
		spec = tex2D(g_specularMapSampler,In.Tex0);
	}

	lig += pow(max(0, dot(L, R)), 10) * g_light.diffuseLightColor[0] * length(spec) * 10.0f;
	color *= lig;

	if (g_isShadowReciever) {
		//���C�g��Z�l���v�Z
		float lightViewPosZ = In.lightViewPos.z / In.lightViewPos.w;
		//�ˉe���(�X�N���[�����W�n)�ɕϊ����ꂽ���W��w�����Ŋ����Ă���(-1.0f�`1.0)�͈̔͂̐��K�����W�n�ɂȂ�B
		//�����UV���W�n(0.0�`1.0)�ɕϊ����āA�V���h�E�}�b�v���t�F�b�`���邽�߂�UV�Ƃ��Ċ��p����B
		float2 shadowMapUV = In.lightViewPos.xy / In.lightViewPos.w;	//���̌v�Z��(-1.0�`1.0)�͈̔͂ɂȂ�B
		if(-1.0f <= shadowMapUV.x && shadowMapUV.x <= 1.0f && -1.0f <= shadowMapUV.y && shadowMapUV.y <= 1.0f){
			shadowMapUV *= float2(0.5f, -0.5f);								//���̌v�Z��(-0.5�`0.5)�͈̔͂ɂȂ�B
			shadowMapUV += float2(0.5f, 0.5f);								//�����Ă����(0.0�`1.0)�͈̔͂ɂȂ��Ăt�u���W�n�ɕϊ��ł����B������ˁB
			float4 shadowVal = tex2D(g_shadowMapTextureSampler, shadowMapUV);	//�V���h�E�}�b�v�͉e�������Ă���Ƃ���̓O���[�X�P�[���ɂȂ��Ă���B
			if (shadowVal.r < lightViewPosZ) {
				color *= float4(0.0f, 0.0f, 0.0f, 1.0f);
			}
		}
	}
	
	color.w *= g_alpha;
	
	return color;
}

/*!
 *@brief	�V���h�E�}�b�v�������ݗp�̃s�N�Z���V�F�[�_�[�B
 */
float4 PSRenderToShadowMapMain(VS_OUTPUT In) : COLOR
{
	float z = In.PosInProj.z / In.PosInProj.w;
	return float4(z, z, z, 1.0f);
}

/*!
 *@brief	�V���G�b�g�p�̃s�N�Z���V�F�[�_�[�B
 */
float4 PSDepthStencilRenderMain(VS_OUTPUT In) : COLOR
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}

/*!
 *@brief	�L���[�u�}�b�v�p�̃s�N�Z���V�F�[�_�[�B
 */
float4 PSSkyCubeMapMain(VS_OUTPUT In) : COLOR
{
	return texCUBE(g_cubeMapSampler,In.Normal);
}

/*!
 *@brief	�X�L���Ȃ�
 *@brief	�L���[�u�}�b�v�p�̃e�N�j�b�N�B
 */
technique NoSkinModelSkyCubeMap
{
    pass p0
    {
        VertexShader = compile vs_3_0 VSMain(false);
        PixelShader = compile ps_3_0 PSSkyCubeMapMain();
    }
}

/*!
 *@brief	�X�L�����胂�f���p�̃e�N�j�b�N�B
 */
technique SkinModel
{
    pass p0
    {
        VertexShader = compile vs_3_0 VSMain(true);
        PixelShader = compile ps_3_0 PSMain();
    }
}
/*!
 *@brief	�X�L���Ȃ����f���p�̃e�N�j�b�N�B
 */
technique NoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSMain();
	}
}

/*!
 *@brief	�X�L������
 *@brief	�V���h�E�}�b�v�������ݗp�̃e�N�j�b�N
 */
technique SkinModelRenderToShadowMap
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMain(true);
		PixelShader 	= compile ps_3_0 PSRenderToShadowMapMain();
	}
}

/*!
*@brief	�X�L���Ȃ�
*@brief	�V���h�E�}�b�v�������ݗp�̃e�N�j�b�N
*/
technique NoSkinModelRenderToShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSRenderToShadowMapMain();
	}
}

/*!
*@brief	�X�L������
*@brief	�V���G�b�g�p�̃e�N�j�b�N
*/
technique DepthStencilRender
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(true);
		PixelShader = compile ps_3_0 PSDepthStencilRenderMain();
	}
}

/*!
*@brief	�X�L���Ȃ�
*@brief	�V���G�b�g�p�̃e�N�j�b�N
*/
technique NoSkinDepthStencilRender
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSDepthStencilRenderMain();
	}
}