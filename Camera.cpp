
//Camera.cpp

#include	"Camera.h"
#include	"keyboard.h"

Camera		g_Camera;	//�J�����Ǘ��\����


void	InitCamera()
{
	//�J�����̏�����
	g_Camera.Position = XMFLOAT3(0.0f, 0.0f, 0.0f);	//�J�������W
	g_Camera.UpVector = XMFLOAT3(0.0f, 1.0f, 0.0f);		//�J�����̏���x�N�g��
	g_Camera.AtPosition = XMFLOAT3(0.0f, 0.0f, 1.0f);	//�J�����̒����_���W
	g_Camera.Fov = 45.0f;								//��p
	g_Camera.Nearclip = 0.5f;							//�ߖʃN���b�v
	g_Camera.Farclip = 1000.0f;							//���ʃN���b�v

}

void	FinalizeCamera()
{

}

void	UpdateCamera()
{


}

void	DrawCamera()//3D�g�p��
{
	//�v���W�F�N�V�����s����쐬
	XMMATRIX	ProjectionMatrix =
		XMMatrixPerspectiveFovLH(
			XMConvertToRadians(g_Camera.Fov),//��p�@����
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
			g_Camera.Nearclip,
			g_Camera.Farclip
		);
	//�v���W�F�N�V�����s����Z�b�g
	SetProjectionMatrix(ProjectionMatrix);

	//�J�����s����쐬
	XMVECTOR	eyev = XMLoadFloat3(&g_Camera.AtPosition);
	XMVECTOR	pos = XMLoadFloat3(&g_Camera.Position);
	XMVECTOR	up = XMLoadFloat3(&g_Camera.UpVector);
	XMMATRIX	ViewMatrix =
		XMMatrixLookAtLH(pos, eyev, up);

	//�J�����s����Z�b�g
	SetViewMatrix(ViewMatrix);
}




