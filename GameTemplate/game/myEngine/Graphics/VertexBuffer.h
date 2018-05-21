#pragma once

enum EVertexFormat {
	eVertexFormat_xyz = D3DFVF_XYZ,
	eVertexFormat_wyzrhw = D3DFVF_XYZRHW,
	eVertexFormat_xyzw = D3DFVF_XYZW,
	eVertexFormat_normal = D3DFVF_NORMAL,
	eVertexFormat_diffuse = D3DFVF_DIFFUSE,
	eVertexFormat_tex0 = D3DFVF_TEX0,
	eVertexFormat_tex1 = D3DFVF_TEX1,
	eVertexFormat_tex2 = D3DFVF_TEX2,
	eVertexFormat_tex3 = D3DFVF_TEX3,
	eVertexFormat_tex4 = D3DFVF_TEX4,
	eVertexFormat_tex5 = D3DFVF_TEX5,
	eVertexFormat_tex6 = D3DFVF_TEX6,
	eVertexFormat_tex7 = D3DFVF_TEX7,
	eVertexFormat_tex8 = D3DFVF_TEX8,
	eVertexFormat_invalid = 0xffffffff,
};

class CVertexBuffer {
public:
	CVertexBuffer();
	~CVertexBuffer();
	/*
	 *	���_�o�b�t�@�̍쐬
	 *	numVertex			���_��
	 *	stride				���_�X�g���C�h
	 *	vertexLayout		���_���C�A�E�g
	 *	pSrcVertexBuffer	�\�[�X���_�o�b�t�@�B�쐬���ꂽ���_�o�b�t�@�ɃR�s�[����܂��BNULL���w��\�B
	 */
	void Create(
		int numVertex,
		int stride,
		const D3DVERTEXELEMENT9* vertexLayout,
		const void* pSrcVerTexBuffer
	);

	//���_�o�b�t�@�̉��
	void Release();

	//LPDIRECT3DVERTEXBUFFER9���擾
	LPDIRECT3DVERTEXBUFFER9 GetBody()
	{
		return m_pVB;
	}

	//���_�X�g���C�h���擾
	int GetStride()	const
	{
		return m_stride;
	}

	//���_��`���擾
	IDirect3DVertexDeclaration9* GetVertexDecl()
	{
		return m_pVertexDecl;
	}

private:
	LPDIRECT3DVERTEXBUFFER9			m_pVB;			//���_�o�b�t�@
	IDirect3DVertexDeclaration9*	m_pVertexDecl;	//���_��`
	int								m_stride;		//���_�X�g���C�h
	int								m_numVertex;	//���_��
	int								m_size;			//�o�b�t�@�T�C�Y
};