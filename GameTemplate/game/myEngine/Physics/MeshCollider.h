#pragma once
#include "myEngine/Physics/ICollider.h"


/*!
 * @brief	メッシュコライダー。
 */
class MeshCollider : public ICollider
{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	MeshCollider();
	/*!
	 * @brief	デストラクタ。
	 */
	~MeshCollider();
	/*!
	 * @brief	CSkinModelからメッシュコライダーを生成。
	 *@param[in]	model		スキンモデル。
	 */
	void CreateFromSkinModel( SkinModel* model, const D3DXMATRIX* offsetMatrix );
	btCollisionShape* GetBody() override
	{
		return meshShape;
	}

	void ConfigHalfSize() override {} //	メッシュコライダーは複雑形状なのでハーフサイズを定義しない。

private:
	typedef std::vector<D3DXVECTOR3>	VertexBuffer;		//頂点バッファ。
	typedef std::vector<unsigned int>	IndexBuffer;		//インデックスバッファ。
	std::vector<VertexBuffer*>		vertexBufferArray;		//頂点バッファの配列。
	std::vector<IndexBuffer*>		indexBufferArray;		//インデックスバッファの配列。
	btBvhTriangleMeshShape*			meshShape = NULL;					//メッシュ形状。
	btTriangleIndexVertexArray*		stridingMeshInterface = NULL;
};
