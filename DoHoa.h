#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
using namespace std;

// Hàm thay doi kích co cua khung cmd voi tham so truyen vào là chieu cao, chieu rong.
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}
void SetBGColor(WORD color){
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

// Hàm dich chuyen con tro den toa do x, y.
void gotoxy(int x,int y)
{    
	HANDLE hConsoleOutput;    
	COORD Cursor_an_Pos = {x-1,y-1};   
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

// Hàm xóa màn hình.
void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

// Hàm lay Key tu bàn phím
/* GetAsyncKeyState(VK_ESCAPE) => bat su kien phím Esc */ 

void ToMau(int x, int y, char *a, int color) // x, y là taa do con tro can nhay den de viet, a là chuoi can truyen vào, color là màu truyen vào.
{
	gotoxy(x, y);
	textcolor(color);
	cout << a;
	textcolor(7);
}

//Ghi chu
void ghi_chu(char *c, int x, int y, int color, int sleep){
	gotoxy(x, y);
	textcolor(color);
	cout << c;
	Sleep(sleep);
	gotoxy(x, y);
	textcolor(14);
	for(int i = 0; i < strlen(c); i++){
		cout << " ";
	}
}
int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}
int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
//Xóa tu vi trí con tro toi het dòng hien tai, roi dua con tro ve vi trí cu.
void clreol(){
COORD coord;
DWORD written;
CONSOLE_SCREEN_BUFFER_INFO info;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
coord.X = info.dwCursorPosition.X;
coord.Y = info.dwCursorPosition.Y;
FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
  info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
gotoxy (info.dwCursorPosition.X , info.dwCursorPosition.Y );
}

void highlight(short t_color, short bg_color){
	textcolor(t_color);
	SetBGColor(bg_color);
}
void normal(){
	textcolor(15);
	SetBGColor(0);
}

void blockConsoleChange(){
	HWND consoleWindow = GetConsoleWindow(); 
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void removeScrollbar()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    COORD new_size = 
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1,
    };
    SetConsoleScreenBufferSize(handle, new_size);
}

void hideCursor()
{
	HANDLE hStdOut = NULL;
    CONSOLE_CURSOR_INFO curInfo;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &curInfo);
}

void ToMauBar(int y, int x, int dong, int cot){
	int i, j;
	for (i = y; i < dong; i++){
		for (j = x; j < cot; j++){
			gotoxy(j, i);
			textcolor(9);
			cout << (char)219;
		}
		cout << endl;
	}
	textcolor(15);
}

int get_key(){
	char key; key = getch();
	if(key == -32 || key == '\0')
		return -getch();
	else return key;
}

//Hàm ve rectangle
BOOL setxy(int x, int y)
{
	COORD c = {x,y};
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void DrawRect(int x, int y, int width, int height, int curPosX=0, int curPosY=0)
{
	setxy(x,y);cout << char(201);
	for(int i = 1; i < width; i++)cout << char(205);
	cout << char(187);
	setxy(x,height + y);cout << char(200);
	for(int i = 1; i < width; i++)cout << char(205);
	cout << char(188);
	for(int i = y + 1; i < height + y; i++)
	{
		setxy(x,i);cout << char(186);
		setxy(x + width,i);cout << char(186);
	}
	setxy(curPosX,curPosY);
}

void SetUpConsole(){
	resizeConsole(1450,750);
	blockConsoleChange();
	SetConsoleTitle("N19DCCN039 - NGUYEN NGOC DUC & N19DCCN075 - TRAN QUANG NGOC HUYNH");
	removeScrollbar();
}

void SetConsoleBackgroundColor(int cntFlashes, int flashInterval_ms, COLORREF color){
    CONSOLE_SCREEN_BUFFER_INFOEX sbInfoEx;
    sbInfoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

    HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);

    COLORREF storedBG = sbInfoEx.ColorTable[0];
	sbInfoEx.ColorTable[0] = color;
    SetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx); 
}
