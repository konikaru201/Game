#pragma once

class CParticle;

//パーティクル生成パラメータ
struct SParticleEmitParameter {
	//初期化
	void Init()
	{
		memset(this, 0, sizeof(SParticleEmitParameter));
	}
	const char* texturePath;		//テクスチャのファイルパス
	float w;						//パーティクルの幅
	float h;						//パーティクルの高さ
	float intervalTime;				//パーティクルの発生間隔
	D3DXVECTOR3 initSpeed;			//初速度
	D3DXVECTOR3 position;			//座標
	float		alpha;				//透明度
};

//パーティクルの発生機
class CParticleEmitter {
public:
	//コンストラクタ
	CParticleEmitter();

	//デストラクタ
	~CParticleEmitter();

	//初期化
	void Init(const SParticleEmitParameter& param);

	//更新
	void Update();

	//座標を設定
	void SetPosition(const D3DXVECTOR3 pos)
	{
		param.position = pos;
		param.position += param.initSpeed * 0.5f;
	}

	//速度を設定
	void SetSpeed(const D3DXVECTOR3 speed)
	{
		param.initSpeed = speed;
	}
private:
	SParticleEmitParameter	param;				//パラメータ
	float					timer;				//タイマー
	std::list<CParticle*>	m_particleList;
};