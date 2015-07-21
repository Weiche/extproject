必ず守ること
移植性：CONFIG.h,<Module>_HAL.cにハードウエア依存コードを記述、それ以外のファイルにはハードウエア依存・コンパイラ依存記述をしないこと

アプリケーションノート：＜コンパイラ活用ガイド＞
効率の良いプログラミング手法 編
大域変数を使わないこと：ファイル内の静的変数　＋　関数APIで操作する
ポインタを引数に使う際、入力のみに使うならばconstをつける　void foo (const uint8_t *input, uint8_t* output_and_input ) のように



[TIMER]
Periphral:
	CMT0
Interrupt:
	CMT0_CMI0
	
[SERIAL]
Periphral:
	SCI6
	DMA0
	PORT0
	