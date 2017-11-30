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

	//コンストラクタ
	CPrimitive();

	//デストラクタ
	~CPrimitive();
	
	/*
	 *	プリミティブの作成
	 *	primitiveType		プリミティブタイプ
	 *	numVertex			頂点数
	 *	vertexStride		頂点ストライド
	 *	vertexLayout		頂点レイアウト
	 *	pSrcVertexBuffer	ソース頂点バッファ
	 *	numIndex			インデックスの数
	 *	IndexFormat			インデックスバッファのフォーマット
	 *	pSrcIndexBuffer		ソースインデックスバッファ
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

	//リリース
	void Release();

	//頂点バッファの取得
	CVertexBuffer* GetVertexBuffer()
	{
		return &m_vertexBuffer;
	}

	//インデックスバッファの取得
	CIndexBuffer* GetIndexBuffer()
	{
		return &m_indexBuffer;
	}

	//D3DPRIMITIVETYPEを取得
	D3DPRIMITIVETYPE GetD3DPrimitiveType() const
	{
		return m_d3dPrimitiveType;
	}

	//頂点数を取得
	int GetNumVertex() const
	{
		return m_numVertex;
	}

	//ポリゴン数を取得
	int GetNumPolygon() const
	{
		return m_numPolygon;
	}

	//頂点定義を取得
	IDirect3DVertexDeclaration9* GetVertexDecl()
	{
		return m_vertexBuffer.GetVertexDecl();
	}
private:
	int					m_numVertex;		//頂点数
	int					m_vertexStride;		//頂点ストライド
	int					m_numIndex;			//インデックスの数
	int					m_numPolygon;		//ポリゴンの数
	CVertexBuffer		m_vertexBuffer;		//頂点バッファ
	CIndexBuffer		m_indexBuffer;		//インデックスバッファ
	EType				m_type;				//プリミティブタイプ
	D3DPRIMITIVETYPE	m_d3dPrimitiveType;	//D3DPRIMITIVETYPE
};