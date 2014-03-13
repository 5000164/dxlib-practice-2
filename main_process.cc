#include "common_header.h"

// メイン処理
void MainProcess()
{
	///
	/// 設定
	///

	// 背景色
	int background_color[] = { 30, 30, 30 };

	// 文字色
	int font_color[] = { 230, 230, 230 };

	// 影色
	int shadow_color[] = { 5, 5, 5 };

	// フォントサイズ
	int font_size = 18;

	// 行の高さ
	double line_height = 1.73;

	// テキスト表示開始位置
	int text_x = 100;
	int text_y = 100;

	// 影のオフセット
	int shadow_offset_x = 0;
	int shadow_offset_y = 2;



	///
	/// DXライブラリ用
	///

	// 背景描画用画面
	int backscreen = MakeScreen(1024, 768, FALSE);

	// 背景色のセット
	SetBackgroundColor(background_color[0], background_color[1], background_color[2]);

	// 文字色を取得
	int font_color_dx = GetColor(font_color[0], font_color[1], font_color[2]);

	// 影色を取得
	int shadow_color_dx = GetColor(shadow_color[0], shadow_color[1], shadow_color[2]);

	// 表示するフォントファミリーセット
	ChangeFont("ＭＳ Ｐゴシック");

	// フォントサイズのセット
	SetFontSize(font_size);

	// フォントの表示方式をセット
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);



	///
	/// 表示テキスト読み込み
	///

	// 読み込むファイル名
	char *input_file_name = "text.txt";

	// 表示テキスト
	char text[256][256];

	// ファイルを開く
	int file_handler = FileRead_open(input_file_name);

	// 行数カウント
	int text_row = 0;

	// ファイル読み込み
	while (FileRead_eof(file_handler) == 0 && text_row < 256)
	{
		FileRead_gets(text[text_row], 256, file_handler);
		text_row++;
	}

	// ファイルを閉じる
	FileRead_close(file_handler);



	///
	/// ループ処理
	///

	// ページ数カウント
	int page_counter = 0;

	// エンターキー入力フラグ
	bool return_input_flag = false;

	// Escキーの入力でループ終了
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		///
		/// エンターキー入力判定
		///

		// エンターキーが入力された場合
		if (CheckHitKey(KEY_INPUT_RETURN) == 1)
		{
			page_counter++;
			return_input_flag = true;

			// テキストの行数を超える場合はページを進めない
			if (page_counter >= text_row)
			{
				page_counter = text_row - 1;
			}
		}



		///
		/// 背景を描画
		///

		// 描画先を背景にセット
		SetDrawScreen(backscreen);

		// 背景を初期化
		ClearDrawScreen();

		// 影のベースとなる文字列を描画
		for (int row = 0; row <= page_counter; row++)
		{
			int x = text_x + shadow_offset_x;
			int y = (int)(text_y + ((font_size * line_height) * row) + shadow_offset_y);

			DrawString(x, y, text[row], shadow_color_dx);
		}

		// ガウスフィルターを施して影にする
		GraphFilter(backscreen, DX_GRAPH_FILTER_GAUSS, 8, 50);



		///
		/// 前景を描画
		///

		// 描画対象を裏画面にする
		SetDrawScreen(DX_SCREEN_BACK);

		// 裏画面を初期化
		ClearDrawScreen();

		// 背景を描画
		DrawGraph(0, 0, backscreen, FALSE);

		// 文字列の描画
		for (int row = 0; row <= page_counter; row++)
		{
			int x = text_x;
			int y = (int)(text_y + ((font_size * line_height) * row));

			DrawString(x, y, text[row], font_color_dx);
		}



		///
		/// 画面表示
		///

		// 裏画面を表画面に反映
		ScreenFlip();



		///
		/// 待機処理
		///

		// 連続入力を避けるために300ms待機
		if (return_input_flag)
		{
			WaitTimer(300);
			return_input_flag = false;
		}
	}



	///
	/// 終了処理
	///

	return;
}
