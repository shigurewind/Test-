/*==============================================================================

   頂点管理 [polygon3D.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "polygon3D.h"
#include "sprite.h"
#include "Camera.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define	BOX_NUM_VERTEX	(36)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static	Camera		g_CameraObject;	//カメラ構造体
static	Object3D	g_Object1;		//3Dポリゴンオブジェクト構造体
static	ID3D11VertexShader* g_VertexShader;	//頂点シェーダーオブジェクトポインタ
static	ID3D11PixelShader* g_PixelShader;	//ピクセルシェーダーオブジェクトポインタ
static	ID3D11InputLayout* g_VertexLayout;	//頂点レイアウトオブジェクトポインタ

static	ID3D11Buffer* g_VertexBuffer;	//テスト用頂点バッファ
static	ID3D11Buffer* g_IndexBuffer;	//テスト用インデックスバッファ


//頂点データ
/*
      V0------------------V1
      |                  |
     |      天井        |
    |                  |
   V2-----------------V3


	  V5------------------V4
	  |                  |
	 |       底面       |
	|                  |
   V7-----------------V6
*/




VERTEX_3D	Box[BOX_NUM_VERTEX] =
{
	//天井////////////////////////////////////////////
	{//頂点V0 LEFT-TOP
		XMFLOAT3(-0.5f, 0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,0.0f,0.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,0.0f)				//テクスチャ座標
	},
	{//頂点V1 RIGHT-TOP
		XMFLOAT3(0.5f, 0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,0.0f,0.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,0.0f)				//テクスチャ座標
	},
	{//頂点V2 LEFT-BOTTOM
		XMFLOAT3(-0.5f, 0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,0.0f,0.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,1.0f)				//テクスチャ座標
	},

	{//頂点V3 RIGHT-BOTTOM
		XMFLOAT3(0.5f, 0.5f, -0.5f),		//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,0.0f,0.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V2 LEFT-BOTTOM
		XMFLOAT3(-0.5f, 0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,0.0f,0.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V1 RIGHT-TOP
		XMFLOAT3(0.5f, 0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,0.0f,0.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,0.0f)				//テクスチャ座標
	},


	//前面////////////////////////////////////////////
	{//頂点V2 LEFT-TOP
		XMFLOAT3(-0.5f, 0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,1.0f,0.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,0.0f)				//テクスチャ座標
	},
	{//頂点V3 RIGHT-TOP
		XMFLOAT3(0.5f, 0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,1.0f,0.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,0.0f)				//テクスチャ座標
	},
	{//頂点V7 LEFT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,1.0f,0.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V6 RIGHT-BOTTOM
		XMFLOAT3(0.5f,-0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,1.0f,0.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V7 LEFT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,1.0f,0.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V3 RIGHT-TOP
		XMFLOAT3(0.5f, 0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,1.0f,0.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,0.0f)				//テクスチャ座標
	},



	//右側面////////////////////////////////////////////
	{//頂点V3 LEFT-TOP
		XMFLOAT3(0.5f, 0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,0.0f)				//テクスチャ座標
	},
	{//頂点V1 RIGHT-TOP
		XMFLOAT3(0.5f, 0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,0.0f)				//テクスチャ座標
	},
	{//頂点V6 LEFT-BOTTOM
		XMFLOAT3(0.5f,-0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V4 RIGHT-BOTTOM
		XMFLOAT3(0.5f, -0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V6 LEFT-BOTTOM
		XMFLOAT3(0.5f,-0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V1 RIGHT-TOP
		XMFLOAT3(0.5f, 0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,0.0f)				//テクスチャ座標
	},



	//背面////////////////////////////////////////////
	{//頂点V1 LEFT-TOP
		XMFLOAT3(0.5f, 0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(0.0f,1.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,0.0f)				//テクスチャ座標
	},
	{//頂点V0 RIGHT-TOP
		XMFLOAT3(-0.5f, 0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(0.0f,1.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,0.0f)				//テクスチャ座標
	},
	{//頂点V4 LEFT-BOTTOM
		XMFLOAT3(0.5f, -0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(0.0f,1.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V5 RIGHT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(0.0f,1.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V4 LEFT-BOTTOM
		XMFLOAT3(0.5f, -0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(0.0f,1.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V0 RIGHT-TOP
		XMFLOAT3(-0.5f, 0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(0.0f,1.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,0.0f)				//テクスチャ座標
	},



	//左側面////////////////////////////////////////////
	{//頂点V0 LEFT-TOP
		XMFLOAT3(-0.5f, 0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(0.0f,0.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,0.0f)				//テクスチャ座標
	},
	{//頂点V2 RIGHT-TOP
		XMFLOAT3(-0.5f, 0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(0.0f,0.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,0.0f)				//テクスチャ座標
	},
	{//頂点V5 LEFT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(0.0f,0.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,1.0f)				//テクスチャ座標
	},

	{//頂点V2 RIGHT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(0.0f,0.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V7 LEFT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(0.0f,0.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V5 RIGHT-TOP
		XMFLOAT3(-0.5f, 0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(0.0f,0.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,0.0f)				//テクスチャ座標
	},


	//底面////////////////////////////////////////////
	{//頂点V7 LEFT-TOP
		XMFLOAT3(-0.5f, -0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,0.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,0.0f)				//テクスチャ座標
	},
	{//頂点V6 RIGHT-TOP
		XMFLOAT3(0.5f,-0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,0.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,0.0f)				//テクスチャ座標
	},
	{//頂点V5 LEFT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,0.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,1.0f)				//テクスチャ座標
	},

	{//頂点V6 RIGHT-BOTTOM
		XMFLOAT3(0.5f,-0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,0.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V4 LEFT-BOTTOM
		XMFLOAT3(-0.5f, -0.5f, 0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,0.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(0.0f,1.0f)				//テクスチャ座標
	},
	{//頂点V5 RIGHT-TOP
		XMFLOAT3(0.5f, -0.5f, -0.5f),	//頂点座標
		XMFLOAT3(0.0f,0.0f,0.0f),		//法線
		XMFLOAT4(1.0f,0.0f,1.0f,1.0f),	//カラー
		XMFLOAT2(1.0f,0.0f)				//テクスチャ座標
	},

};





//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPolygon3D(void)
{

	//テクスチャ読み込み
	int Texture = TextureLoad(L"asset\\texture\\sura.jpg");

	//シェーダー読み込み
	CreateVertexShader(&g_VertexShader, &g_VertexLayout, "testshaderVS.cso");
	CreatePixelShader(&g_PixelShader, "testshaderPS.cso");

	//カメラの初期化
	g_CameraObject.Position = XMFLOAT3(0.0f, 0.0f, -5.0f);
	g_CameraObject.UpVector = XMFLOAT3(0.0f, 1.0f, 0.0f);
	g_CameraObject.AtPosition = XMFLOAT3(0.0f, 0.0f, 1.0f);
	g_CameraObject.Fov = 45.0f;
	g_CameraObject.Nearclip = 0.5f;
	g_CameraObject.Farclip = 1000.0f;

	//頂点バッファ作成
	{
		D3D11_BUFFER_DESC	bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * BOX_NUM_VERTEX;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

		//頂点バッファの書き込み先のポインターを取得
		D3D11_MAPPED_SUBRESOURCE	msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		//頂点データをコピー
		CopyMemory(&vertex[0], &Box[0], sizeof(VERTEX_3D) * BOX_NUM_VERTEX);
		//書き込み完了
		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	//3Dオブジェクト管理構造体の初期化
	g_Object1.Position = XMFLOAT3(1.5f, 0.0f, 0.0f);
	g_Object1.Rotate = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Object1.Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	g_Object1.TexID = Texture;


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void FinalizePolygon3D(void)
{
	//作ったものを解放
	g_VertexShader->Release();
	g_VertexLayout->Release();
	g_PixelShader->Release();

	g_VertexBuffer->Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon3D(void)
{
	//適当に回転
	g_Object1.Rotate.y += 0.3f;
	g_Object1.Rotate.x += 0.1f;

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon3D(void)
{
	//頂点レイアウトを設定
	GetDeviceContext()->IASetInputLayout(g_VertexLayout);
	//頂点シェーダーをセット
	GetDeviceContext()->VSSetShader(g_VertexShader, NULL, 0);
	//ピクセルシェーダーをセット
	GetDeviceContext()->PSSetShader(g_PixelShader, NULL, 0);

	//3D用行列設定
	SetDepthEnable(true);		//奥行き処理有効

	//プロジェクション行列を作成
	XMMATRIX	ProjectionMatrix =
		XMMatrixPerspectiveFovLH(
			XMConvertToRadians(g_CameraObject.Fov),//画角
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,//アスペクト比
			g_CameraObject.Nearclip,//近クリップ距離
			g_CameraObject.Farclip//遠クリップ距離
		);
	//DirectXへセット
	SetProjectionMatrix(ProjectionMatrix);

	//カメラ行列を作成
	XMVECTOR	eyev = XMLoadFloat3(&g_CameraObject.AtPosition);//位置
	XMVECTOR	pos = XMLoadFloat3(&g_CameraObject.Position);//注視点
	XMVECTOR	up = XMLoadFloat3(&g_CameraObject.UpVector);//上方ベクトル（1.0固定）

	XMMATRIX	ViewMatrix =
		XMMatrixLookAtLH(pos, eyev, up);//左手系ルックアットカメラ

	//DirectXへセット
	SetViewMatrix(ViewMatrix);

	{//3Dポリゴン１つずつの処理
		//テクスチャをセット
		ID3D11ShaderResourceView* tex = GetTexture(g_Object1.TexID);
		GetDeviceContext()->PSSetShaderResources(0, 1, &tex);

		//平行移動行列作成
		XMMATRIX	TranslationMatrix =
			XMMatrixTranslation(
				g_Object1.Position.x,
				g_Object1.Position.y,
				g_Object1.Position.z
			);
		//回転行列作成
		XMMATRIX	RotationMatrix =
			XMMatrixRotationRollPitchYaw(
				XMConvertToRadians(g_Object1.Rotate.x),
				XMConvertToRadians(g_Object1.Rotate.y),
				XMConvertToRadians(g_Object1.Rotate.z)
			);
		//スケーリング行列作成
		XMMATRIX	ScalingMatrix =
			XMMatrixScaling(
				g_Object1.Scale.x,
				g_Object1.Scale.y,
				g_Object1.Scale.z
			);
		//ワールド行列作成 ※乗算の順番に注意
		XMMATRIX	WorldMatrix =
			ScalingMatrix *
			RotationMatrix *
			TranslationMatrix;
		//DirectXへセット
		SetWorldMatrix(WorldMatrix);

		//頂点バッファをセット
		UINT	stride = sizeof(VERTEX_3D);
		UINT	offset = 0;
		GetDeviceContext()->IASetVertexBuffers(
			0,
			1,
			&g_VertexBuffer,
			&stride,
			&offset
		);

		//プリミティブトポロジーの設定
		GetDeviceContext()->IASetPrimitiveTopology(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);
		//マテリアル設定
		MATERIAL	material;
		ZeroMemory(&material, sizeof(MATERIAL));
		material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		SetMaterial(material);

		//描画
		GetDeviceContext()->Draw(BOX_NUM_VERTEX, 0);//インデックス無し描画
	}


}
