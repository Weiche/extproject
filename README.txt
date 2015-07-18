必ず守ること
移植性：CONFIG.h,<Module>_HAL.cにハードウエア依存コードを記述、それ以外のファイルにはハードウエア依存・コンパイラ依存記述をしないこと

大域変数を使わないこと：ファイル内の静的変数　＋　関数APIで操作する

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
	