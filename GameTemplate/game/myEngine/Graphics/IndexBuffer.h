#pragma once

class CIndexBuffer {
public:
	CIndexBuffer();
	~CIndexBuffer();
	/*		
	 *	インデックスバッファの作成
	 *	numIndex		インデックスの数
	 *	format			インデックスバッファのフォーマット
	 *	pSrcIndexBuffer	ソースインデックスバッファ。作成されたインデックスバッファにコピーされます。NULLを指定可能。
	 */
	void Create(int numIndex, D3DFORMAT format, const void* pSrcIndexBuffer);

	//インデックスバッファの解放
	void Release();

	//LPDIRECT3DINDEXBUFFER9の取得
	LPDIRECT3DINDEXBUFFER9 GetBody()
	{
		return m_pIB;
	}
private:
	LPDIRECT3DINDEXBUFFER9 m_pIB;	//インデックスバッファ
};