#include "Main.h"
#include "Renderer.h"
#include "Manager.h"
#include "Sprite.h"
#include "Game.h"
#include "keyboard.h"
#include "Manager.h"
#include "Camera.h"
#include "texture.h"

#include	"polygon2D.h"
#include	"polygon3D.h"
#include	"polygonModel.h"
#include	"Model.h"

//===============================================
//グローバル変数
 
//ポーズフラグ
static	bool	pause = false;

//===============================================
//ポーズフラグセット
void	SetPause(bool flg)
{
	pause = flg;
}
//===============================================
//ポーズフラグ取得
bool	GetPause()
{
	return pause;
}

//===============================================
//ゲームシーン初期化
void InitGame()
{
	TextureInitialize(GetDevice());
	InitCamera();

	InitPolygon2D();
	InitPolygon3D();
	InitPolygonModel();

}

//===============================================
//ゲームシーン終了
void FinalizeGame()
{
	FinalizeCamera();
	FinalizePolygon2D();
	FinalizePolygon3D();
	FinalizePolygonModel();

	TextureFinalize();
}

//===============================================
//ゲームシーン更新
void UpdateGame()
{

	if (GetPause() == false)//ポーズ中でなければ更新実行
	{
		UpdateCamera();
		UpdatePolygon2D();
		UpdatePolygon3D();
		UpdatePolygonModel();

	}

}

//===============================================
//ゲームシーン描画
void DrawGame()
{

	// 2D用マトリクス設定
	SetWorldViewProjection2D();
	DrawPolygon2D();
	DrawPolygon3D();
	DrawPolygonModel();



}
