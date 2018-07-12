/*!
 * @brief	��ʊE�[�x
 */

texture g_scene;	//�V�[���e�N�X�`���B

sampler g_SceneSampler = 
sampler_state
{
    Texture = <g_scene>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = CLAMP;
    AddressV = CLAMP;
};

struct VS_INPUT{
	float4	pos : POSITION;
	float2	uv : TEXCOORD;
};

struct VS_OUTPUT{
	float4  pos : POSITION;
	float2  tex : TEXCOORD0;
	float4	PosInProj : TEXCOORD1;
};

VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	Out.pos = In.pos;		//�g�����X�t�H�[���ςݒ��_�Ȃ̂ł��̂܂�
	Out.tex = In.uv;
	//Out.tex = (In.pos.xy * 0.5f) + 0.5f;
	//Out.tex.y = 1.0f - Out.tex.y;
	Out.PosInProj = In.pos;
	return Out;
}

struct VS_BlurOutput{
	float4 pos	: POSITION;
	float2 tex0	: TEXCOORD0;
	float2 tex1 : TEXCOORD1;
	float2 tex2 : TEXCOORD2;
	float2 tex3 : TEXCOORD3;
	float2 tex4 : TEXCOORD4;
	float2 tex5 : TEXCOORD5;
	float2 tex6 : TEXCOORD6;
	float2 tex7 : TEXCOORD7;
};
texture g_blur;	//�u���[�e�N�X�`��

sampler g_blurSampler = 
sampler_state
{
    Texture = <g_blur>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = CLAMP;
    AddressV = CLAMP;
};

float2 g_texSize;				//�e�N�X�`���̃T�C�Y�B
float2 g_offset;				//�I�t�Z�b�g
float  g_weight[8];				//�K�E�X�t�B���^�̏d�݁B

/*!
 * @brief	X�u���[���_�V�F�[�_�[�B
 */
VS_BlurOutput VSXBlur(VS_INPUT In)
{
	VS_BlurOutput Out;
	Out.pos = In.pos;
	float2 tex = (In.pos * 0.5f) + 0.5f;
	tex.y = 1.0f - tex.y;
	tex += float2( 0.5/ g_texSize.x, 0.5/ g_texSize.y);
	Out.tex0 = tex + float2( - 1.0f/ g_texSize.x, 0.0f );
    Out.tex1 = tex + float2( - 3.0f/ g_texSize.x, 0.0f );
    Out.tex2 = tex + float2( - 5.0f/ g_texSize.x, 0.0f );
    Out.tex3 = tex + float2( - 7.0f/ g_texSize.x, 0.0f );
    Out.tex4 = tex + float2( - 9.0f/ g_texSize.x, 0.0f );
    Out.tex5 = tex + float2( -11.0f/ g_texSize.x, 0.0f );
    Out.tex6 = tex + float2( -13.0f/ g_texSize.x, 0.0f );
    Out.tex7 = tex + float2( -15.0f/ g_texSize.x, 0.0f );
    return Out;
}
/*!
 * @brief	X�u���[�s�N�Z���V�F�[�_�[�B
 */
float4 PSXBlur( VS_BlurOutput In ) : COLOR
{
	float4 Color;
	Color  = g_weight[0] * (tex2D( g_blurSampler, In.tex0 )
	                 + tex2D( g_blurSampler, In.tex7 + g_offset ));
	Color += g_weight[1] * (tex2D( g_blurSampler, In.tex1 )
	                 + tex2D( g_blurSampler, In.tex6 + g_offset ));
	Color += g_weight[2] * (tex2D( g_blurSampler, In.tex2 )
	            + tex2D( g_blurSampler, In.tex5 + g_offset ));
	Color += g_weight[3] * (tex2D( g_blurSampler, In.tex3 )
	                 + tex2D( g_blurSampler, In.tex4 + g_offset ));
	Color += g_weight[4] * (tex2D( g_blurSampler, In.tex4 )
	                 + tex2D( g_blurSampler, In.tex3 + g_offset ));
	Color += g_weight[5] * (tex2D( g_blurSampler, In.tex5 )
	                 + tex2D( g_blurSampler, In.tex2 + g_offset ));
	Color += g_weight[6] * (tex2D( g_blurSampler, In.tex6 )
	                 + tex2D( g_blurSampler, In.tex1 + g_offset ));
	Color += g_weight[7] * (tex2D( g_blurSampler, In.tex7 )
	                 + tex2D( g_blurSampler, In.tex0 + g_offset ));
	return Color;
}
/*!
 * @brief	Y�u���[���_�V�F�[�_�[�B
 */
VS_BlurOutput VSYBlur(VS_INPUT In)
{
	VS_BlurOutput Out;
	Out.pos = In.pos;
	float2 tex = (In.pos * 0.5f) + 0.5f;
	tex.y = 1.0f - tex.y;
	tex += float2(0.5 / g_texSize.x, 0.5 / g_texSize.y);
	Out.tex0 = tex + float2( 0.0f,- 1.0f/ g_texSize.y  );
    Out.tex1 = tex + float2( 0.0f,- 3.0f/ g_texSize.y  );
    Out.tex2 = tex + float2( 0.0f,- 5.0f/ g_texSize.y  );
    Out.tex3 = tex + float2( 0.0f,- 7.0f/ g_texSize.y  );
    Out.tex4 = tex + float2( 0.0f,- 9.0f/ g_texSize.y  );
    Out.tex5 = tex + float2( 0.0f,-11.0f/ g_texSize.y  );
    Out.tex6 = tex + float2( 0.0f,-13.0f/ g_texSize.y  );
    Out.tex7 = tex + float2( 0.0f,-15.0f/ g_texSize.y  );
    return Out;
}
/*!
 * @brief	Y�u���[�s�N�Z���V�F�[�_�[�B
 */
float4 PSYBlur( VS_BlurOutput In ) : COLOR
{
	float4 Color;
	Color  = g_weight[0] * (tex2D( g_blurSampler, In.tex0 )
	                 + tex2D( g_blurSampler, In.tex7 + g_offset ));
	Color += g_weight[1] * (tex2D( g_blurSampler, In.tex1 )
	                 + tex2D( g_blurSampler, In.tex6 + g_offset ));
	Color += g_weight[2] * (tex2D( g_blurSampler, In.tex2 )
	            + tex2D( g_blurSampler, In.tex5 + g_offset ));
	Color += g_weight[3] * (tex2D( g_blurSampler, In.tex3 )
	                 + tex2D( g_blurSampler, In.tex4 + g_offset ));
	Color += g_weight[4] * (tex2D( g_blurSampler, In.tex4 )
	                 + tex2D( g_blurSampler, In.tex3 + g_offset ));
	Color += g_weight[5] * (tex2D( g_blurSampler, In.tex5 )
	                 + tex2D( g_blurSampler, In.tex2 + g_offset ));
	Color += g_weight[6] * (tex2D( g_blurSampler, In.tex6 )
	                 + tex2D( g_blurSampler, In.tex1 + g_offset ));
	Color += g_weight[7] * (tex2D( g_blurSampler, In.tex7 )
	                 + tex2D( g_blurSampler, In.tex0 + g_offset ));
	return Color;
}

//�����e�N�X�`���B
texture g_combineTex00;
sampler g_combineSampler00 = 
sampler_state
{
	Texture = <g_combineTex00>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = CLAMP;
    AddressV = CLAMP;
};
texture g_combineTex01;
sampler g_combineSampler01 = 
sampler_state
{
    Texture = <g_combineTex01>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = CLAMP;
    AddressV = CLAMP;
};

float4 PSCombine( VS_OUTPUT In ) : COLOR
{
	float2 uv = In.tex;
	//uv += g_offset;

	float4 combineColor = tex2D(g_combineSampler00, uv);
	combineColor += tex2D(g_combineSampler01, uv);
	combineColor /= 2.0f;

	return combineColor;
}

texture g_depthMapTexture;
sampler g_depthMapSampler =
sampler_state
{
	Texture = <g_depthMapTexture>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture g_blurTexture0;
sampler g_blurSampler0 =
sampler_state
{
	Texture = <g_blurTexture0>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};
texture g_blurTexture1;
sampler g_blurSampler1 =
sampler_state
{
	Texture = <g_blurTexture1>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture g_mainTexture;
sampler g_mainSampler =
sampler_state
{
	Texture = <g_mainTexture>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

/*!
 * @brief	�t�@�C�i���B
 */
VS_OUTPUT VSFinal( VS_INPUT In )
{
	VS_OUTPUT Out;
	Out.pos = In.pos;		//�g�����X�t�H�[���ςݒ��_�Ȃ̂ł��̂܂�
	Out.tex = (In.pos.xy * 0.5f) + 0.5f;
	Out.tex.y = 1.0f - Out.tex.y;
	Out.tex += g_offset;
	Out.PosInProj = In.pos;
	return Out;
}
float4 PSFinal( VS_OUTPUT In ) : COLOR
{
	float2 uv = In.tex;

	float4 depth = tex2D(g_depthMapSampler, uv);

	float4 color = tex2D(g_mainSampler, uv);
	if (depth.r < 0.9f) {
		color = tex2D(g_blurSampler0, uv);
	}
	else if (depth.r > 0.99f) {
		color = tex2D(g_blurSampler1, uv);
	}

	return color;
}

/*!
 * @brief	���u���[
 */
technique XBlur
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSXBlur();
		PixelShader = compile ps_3_0 PSXBlur();
	}
}

/*!
 * @brief	�c�u���[
 */
technique YBlur
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSYBlur();
		PixelShader = compile ps_3_0 PSYBlur();
	}
}

/*!
 * @brief	�����B
 */
technique Combine
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSCombine();
	}
}
 
technique Final
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSFinal();
		PixelShader = compile ps_3_0 PSFinal();
	}
}