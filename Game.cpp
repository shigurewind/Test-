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
//�O���[�o���ϐ�
 
//�|�[�Y�t���O
static	bool	pause = false;

//===============================================
//�|�[�Y�t���O�Z�b�g
void	SetPause(bool flg)
{
	pause = flg;
}
//===============================================
//�|�[�Y�t���O�擾
bool	GetPause()
{
	return pause;
}

//===============================================
//�Q�[���V�[��������
void InitGame()
{
	TextureInitialize(GetDevice());
	InitCamera();

	InitPolygon2D();
	InitPolygon3D();
	InitPolygonModel();

}

//===============================================
//�Q�[���V�[���I��
void FinalizeGame()
{
	FinalizeCamera();
	FinalizePolygon2D();
	FinalizePolygon3D();
	FinalizePolygonModel();

	TextureFinalize();
}

//===============================================
//�Q�[���V�[���X�V
void UpdateGame()
{

	if (GetPause() == false)//�|�[�Y���łȂ���΍X�V���s
	{
		UpdateCamera();
		UpdatePolygon2D();
		UpdatePolygon3D();
		UpdatePolygonModel();

	}

}

//===============================================
//�Q�[���V�[���`��
void DrawGame()
{

	// 2D�p�}�g���N�X�ݒ�
	SetWorldViewProjection2D();
	DrawPolygon2D();
	DrawPolygon3D();
	DrawPolygonModel();



}
