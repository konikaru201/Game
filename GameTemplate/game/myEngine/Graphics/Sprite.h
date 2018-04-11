#pragma once

class Sprite {
public:
	//�R���X�g���N�^
	Sprite();

	//�f�X�g���N�^
	~Sprite();

	//������
	void Initialize(char *filpath);

	//�e�N�X�`���ǂݍ���
	void LoadTexture(char *filePath);

	//�`��
	void Render();

	//�G�t�F�N�g�ǂݍ���
	LPD3DXEFFECT LoadEffect(char *filePath);

	//���
	void Release();

	//���_�o�b�t�@
	struct Vertex {
		float vertex[4];
		float uv[2];
	};

	//���W��ݒ�
	//pos	���W
	void SetPosition(const D3DXVECTOR2& pos)
	{
		m_position = pos;
	}

	//���W���擾
	const D3DXVECTOR2& GetPosition()
	{
		return m_position;
	}

	//�T�C�Y��ݒ�
	//scale		�T�C�Y
	void SetSize(const D3DXVECTOR2& size)
	{
		m_size = size;
	}

	//�s�����x��ݒ�
	//alpha		�s�����x�B0.0�Ŋ��S�ɓ���
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

	//�s�����x���擾
	float GetAlpha()
	{
		return m_alpha;
	}

	//UV�𓮂����t���O��ݒ�
	void SetUVMove(bool uvMove)
	{
		m_uvMove = uvMove;
	}

	//�J������Ԃɕϊ�����t���O
	void SetIsTrans(bool isTrans)
	{
		m_isTrans = isTrans;
	}
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`��
	D3DXIMAGE_INFO m_imginfo;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	LPD3DXEFFECT m_pEffect;
	D3DXVECTOR2 m_position;
	D3DXVECTOR2 m_size;
	float m_alpha = 1.0f;
	bool m_uvMove = false;				//UV�𓮂����t���O
	float uvPos = 0.0f;
	bool m_isTrans = false;
};
