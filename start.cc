#include "common_header.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウで実行
	ChangeWindowMode(TRUE);

	// 1024x768px、32bitで実行
	SetGraphMode(1024, 768, 32);
	
	// 異常処理で強制終了
	if (DxLib_Init() == -1)	return -1;

	// メイン処理呼び出し
	MainProcess();

	// DXライブラリ使用終了処理
	DxLib_End();

	return 0;
}
