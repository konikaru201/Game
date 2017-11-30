#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"

class CPrimitive {
public:
	enum EType {
		eTriangleList,
		eTriangleStrip,
		eTypeNum,
	};

	//�R���X�g���N�^
	CPrimitive();

	//�f�X�g���N�^
	~CPrimitive();
	
	/*
	 *	�v���~�e�B�u�̍쐬
	 *	primitiveType		�v���~�e�B�u�^�C�v
	 *	numVertex			���_��
	 *	vertexStride		���_�X�g���C�h
	 *	vertexLayout		���_���C�A�E�g
	 *	pSrcVertexBuffer	�\�[�X���_�o�b�t�@
	 *	numIndex			�C���f�b�N�X�̐�
	 *	IndexFormat			�C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g
	 *	pSrcIndexBuffer		�\�[�X�C���f�b�N�X�o�b�t�@
	 */
	void Create(
		EType					primitiveType,
		int						numVertex,
		int						vertexStride,
		const D3DVERTEXELEMENT9* vertexLayout,
		void*					pSrcVertexBuffer,
		int						numIndex,
		D3DFORMAT				indexFormat,
		void*					pSrcIndexbuffer
	);

	//�����[�X
	void Release();

	//���_�o�b�t�@�̎擾
	CVertexBuffer* GetVertexBuffer()
	{
		return &m_vertexBuffer;
	}

	//�C���f�b�N�X�o�b�t�@�̎擾
	CIndexBuffer* GetIndexBuffer()
	{
		return &m_indexBuffer;
	}

	//D3DPRIMITIVETYPE���擾
	D3DPRIMITIVETYPE GetD3DPrimitiveType() const
	{
		return m_d3dPrimitiveType;
	}

	//���_�����擾
	int GetNumVertex() const
	{
		return m_numVertex;
	}

	//�|���S�������擾
	int GetNumPolygon() const
	{
		return m_numPolygon;
	}

	//���_��`���擾
	IDirect3DVertexDeclaration9* GetVertexDecl()
	{
		return m_vertexBuffer.GetVertexDecl();
	}
private:
	int					m_numVertex;		//���_��
	int					m_vertexStride;		//���_�X�g���C�h
	int					m_numIndex;			//�C���f�b�N�X�̐�
	int					m_numPolygon;		//�|���S���̐�
	CVertexBuffer		m_vertexBuffer;		//���_�o�b�t�@
	CIndexBuffer		m_indexBuffer;		//�C���f�b�N�X�o�b�t�@
	EType				m_type;				//�v���~�e�B�u�^�C�v
	D3DPRIMITIVETYPE	m_d3dPrimitiveType;	//D3DPRIMITIVETYPE
};