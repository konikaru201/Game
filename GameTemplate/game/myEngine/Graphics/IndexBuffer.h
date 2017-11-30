#pragma once

class CIndexBuffer {
public:
	CIndexBuffer();
	~CIndexBuffer();
	/*		
	 *	�C���f�b�N�X�o�b�t�@�̍쐬
	 *	numIndex		�C���f�b�N�X�̐�
	 *	format			�C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g
	 *	pSrcIndexBuffer	�\�[�X�C���f�b�N�X�o�b�t�@�B�쐬���ꂽ�C���f�b�N�X�o�b�t�@�ɃR�s�[����܂��BNULL���w��\�B
	 */
	void Create(int numIndex, D3DFORMAT format, const void* pSrcIndexBuffer);

	//�C���f�b�N�X�o�b�t�@�̉��
	void Release();

	//LPDIRECT3DINDEXBUFFER9�̎擾
	LPDIRECT3DINDEXBUFFER9 GetBody()
	{
		return m_pIB;
	}
private:
	LPDIRECT3DINDEXBUFFER9 m_pIB;	//�C���f�b�N�X�o�b�t�@
};