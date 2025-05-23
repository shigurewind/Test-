/*==============================================================================

   頂点管理[polygon.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


////////////////
//構造体
////////////////

class Object2D
{
	public:
		XMFLOAT3	Position;		//表示座標
		XMFLOAT4	Color;			//色
		XMFLOAT2	Size;			//サイズ
		XMFLOAT2	Scale;			//拡大縮小率
		float		Rotate;			//回転角度（360表現）
		int			TexID;			//テクスチャID

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPolygon2D(void);
void FinalizePolygon2D(void);
void UpdatePolygon2D(void);
void DrawPolygon2D(void);

