#include "common_header.h"

// ���C������
void MainProcess()
{
	///
	/// �ݒ�
	///

	// �w�i�F
	int background_color[] = { 30, 30, 30 };

	// �����F
	int font_color[] = { 230, 230, 230 };

	// �e�F
	int shadow_color[] = { 5, 5, 5 };

	// �t�H���g�T�C�Y
	int font_size = 18;

	// �s�̍���
	double line_height = 1.73;

	// �e�L�X�g�\���J�n�ʒu
	int text_x = 100;
	int text_y = 100;

	// �e�̃I�t�Z�b�g
	int shadow_offset_x = 0;
	int shadow_offset_y = 2;

	// �\���e�L�X�g
	char* text[] = { "���̃C�[�n�g�[���H��", "�����Ƃ��������A", "�Ăł���ɗ₽������������A", "���������X�ŏ���ꂽ�����[�I�s�A", "�x�O�̂��炬��Ђ��鑐�̔g�B" };

	// �z��̗v�f�����擾
	int text_length = sizeof(text) / sizeof(text[0]);



	///
	/// DX���C�u�����p
	///

	// �w�i�`��p���
	int backscreen = MakeScreen(1024, 768, FALSE);

	// �w�i�F�̃Z�b�g
	SetBackgroundColor(background_color[0], background_color[1], background_color[2]);

	// �����F���擾
	int font_color_dx = GetColor(font_color[0], font_color[1], font_color[2]);

	// �e�F���擾
	int shadow_color_dx = GetColor(shadow_color[0], shadow_color[1], shadow_color[2]);

	// �\������t�H���g�t�@�~���[�Z�b�g
	ChangeFont("�l�r �o�S�V�b�N");

	// �t�H���g�T�C�Y�̃Z�b�g
	SetFontSize(font_size);

	// �t�H���g�̕\���������Z�b�g
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);



	///
	/// ���[�v����
	///

	// �y�[�W���J�E���g
	int page_counter = 0;

	// �G���^�[�L�[���̓t���O
	bool return_input_flag = false;

	// Esc�L�[�̓��͂Ń��[�v�I��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		///
		/// �G���^�[�L�[���͔���
		///

		// �G���^�[�L�[�����͂��ꂽ�ꍇ
		if (CheckHitKey(KEY_INPUT_RETURN) == 1)
		{
			page_counter++;
			return_input_flag = true;

			// �e�L�X�g�̐��𒴂���ꍇ�̓y�[�W��i�߂Ȃ�
			if (page_counter >= text_length)
			{
				page_counter = text_length - 1;
			}
		}



		///
		/// �w�i��`��
		///

		// �`����w�i�ɃZ�b�g
		SetDrawScreen(backscreen);

		// �w�i��������
		ClearDrawScreen();

		// �e�̃x�[�X�ƂȂ镶�����`��
		DrawString(text_x + shadow_offset_x, text_y + shadow_offset_y, text[page_counter], shadow_color_dx);

		// �K�E�X�t�B���^�[���{���ĉe�ɂ���
		GraphFilter(backscreen, DX_GRAPH_FILTER_GAUSS, 8, 50);



		///
		/// �O�i��`��
		///

		// �`��Ώۂ𗠉�ʂɂ���
		SetDrawScreen(DX_SCREEN_BACK);

		// ����ʂ�������
		ClearDrawScreen();

		// �w�i��`��
		DrawGraph(0, 0, backscreen, FALSE);

		// ������̕`��
		DrawString(text_x, text_y, text[page_counter], font_color_dx);



		///
		/// ��ʕ\��
		///

		// ����ʂ�\��ʂɔ��f
		ScreenFlip();



		///
		/// �ҋ@����
		///

		// �A�����͂�����邽�߂�1�b�ҋ@
		if (return_input_flag)
		{
			WaitTimer(300);
			return_input_flag = false;
		}
	}



	///
	/// �I������
	///

	return;
}
