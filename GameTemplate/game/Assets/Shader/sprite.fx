struct VS_INPUT
{
	float4 pos		: POSITION;
	float2 uv		: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos		: POSITION;
	float2 uv		: TEXCOORD0;
};

float4x4 g_world;
float g_alpha;
float g_uvPos;
bool g_uvMove;

texture g_texture;
sampler TextureSampler = 
sampler_state
{
	Texture = <g_texture>;
};

//頂点シェーダー
VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;

	Out.pos = In.pos;
	Out.pos = mul(In.pos, g_world);
	Out.uv = In.uv;
	return Out;
}

//ピクセルシェーダー
float4 PSMain(VS_OUTPUT In) : COLOR
{
	if (g_uvMove) {
		In.uv.x += g_uvPos;
		In.uv.y += g_uvPos;
	}
	float4 color = tex2D(TextureSampler,In.uv);
	color.w *= g_alpha;
	return color;
}

technique Sprite
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
};