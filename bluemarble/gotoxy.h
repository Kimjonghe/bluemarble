#include <windows.h>
void movecursor(int a, int b) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = a;
	pos.Y = b;
	SetConsoleCursorPosition(consoleHandle, pos);
}