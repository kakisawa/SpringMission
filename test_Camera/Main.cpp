#include "DxLib.h"
#include "Player.h"
#include "Camera.h"
#include "Game.h"
#include <vector>

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);
	SetGraphMode(kScreenWidth, kScreenHeight, kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);	// ����ʂ�`��Ώۂɂ���
	SetUseZBufferFlag(TRUE);		// �y�o�b�t�@���g�p����
	SetWriteZBufferFlag(TRUE);		// �y�o�b�t�@�ւ̏������݂��s��
	SetUseBackCulling(TRUE);		// �o�b�N�J�����O���s��

	// ����
	Camera* camera = new Camera();
	Player* player = new Player();

	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	LONGLONG frameTime = 0;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		frameTime = GetNowHiPerformanceCount();
		// �v���C���[����.
		player->Update();

		// �}�b�v�`�b�v�̃T�C�Y
		camera->Update(*player);

		// ��ʂ�����������
		ClearDrawScreen();

		// �`��
		player->Draw();

		// �f�o�b�O�`��
		// XYZ��
		float lineSize = 300.0f;
		DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
		DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0), GetColor(0, 255, 0));
		DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), GetColor(0, 0, 255));

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		// �G��60fps�Œ�
		while ((GetNowHiPerformanceCount() - frameTime) < 16667) {}
	}

	// ��n��
	delete(player);
	delete(camera);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}