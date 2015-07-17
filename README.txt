必ず守ること
移植性：CONFIG.h,<Module>_HAL.cにハードウエア依存コードを記述、それ以外のファイルにはハードウエア依存・コンパイラ依存記述をしないこと

大域変数を使わないこと：ファイル内の静的変数　＋　関数APIで操作する
[Periphral @ TIMER]
CMT0
[Interrupt @ TIMER]
CMI0

[Periphral @ KEYMATRIX]
[7:0]PORT6
[Interrupt @ KEYMATRIX]
None

[Periphral @ SERIAL]
SCI6
[1:1]PORT0 as RX
DMA0
[Interrupt @ KEYMATRIX]
TXI6( DMA trigger )
