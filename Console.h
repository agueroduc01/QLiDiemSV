#include "DocGhiFileDoAn.h"
#define UP -72
#define DOWN -80
#define LEFT -75
#define RIGHT -77
#define ENTER 13
#define ESC 27
#define F1 -59
#define F2 -60
#define F3 -61
#define F4 62

const char len = 24;
const char xuong = 25;
const int dong = 4;
const int cot = 3;
const char doc = 179;
const char ngang = 196;

const char menu_chinh[4][30] = {"1. DANH SACH LOP TIN CHI",
"2. DANH SACH SINH VIEN",
"3. DANH SACH MON HOC",
"4. DANH SACH DANG KI"};
const char menu_dsltc[4][30] = {"  Them Lop Tin Chi",
"  Xoa Lop Tin Chi",
"  Hieu Chinh Lop Tin Chi",
"  Danh Sach Lop Tin Chi"};
const char menu_dssv[4][30] = {"    Them Sinh Vien",
"  Xoa Sinh Vien", 
"  Hieu Chinh Sinh Vien",
"  Danh Sach Sinh Vien"};
const char menu_dsmh[4][30] = {"  Them Mon Hoc" ,
" Xoa Mon Hoc",
" Hieu Chinh Mon Hoc",
" Danh Sach Mon Hoc"};
const char menu_dangki[4][30] = {" Dang Ki Lop Tin Chi",
"  Huy Lop Tin Chi",
"  Nhap Diem",
" Bang Diem Mon Hoc"};

int veMenuChinh(short chon);
int veMenuPhu(const char menu[][30], short chon);
// LOP TIN CHI
int veBangSuaXoaLTC(short check);
int inDssvDangKy();
int hieu_chinh_dsltc(DSLTC &dsltc, PTRMH dsmh);
int timMaLopTinChi(const char menu[][30]);
void veBangMonHoc();
int veBangThemLTC(short check);
int veBangThemLTC(short check, MONHOC** mang, unsigned short soluong);
void veBangLopTinChi();
void inNhapMaLopTinChi();
//SINH VIEN
int ve_bang_sv();
int ve_bang_sv_con(short check);
int sua_va_xoa_sinh_vien(const char menu[][30]);
int tim_ma_sinh_vien(const char menu[][30]);
int in_danh_sach_sinh_vien(const char menu[][30]);
//MON HOC
int them_mon_hoc(const char menu[][30], PTRMH &dsmh);
//int sua_va_xoa_mon_hoc(const char menu[][30]);
//int dang_ky(const char menu[][30]);
//int in_danh_sach_mon_hoc(const char menu[][30]);
//DIEM
int nhap_diem_lop_tin_chi(const char menu[][30]);
int ve_bang_diem();
int bang_diem_mon_hoc(const char menu[][30]);
int diem_trung_binh(const char menu[][30]);
int diem_tong_ket(const char menu[][30]);

// them node mon hoc
void them_node_mh(PTRMH &dsmh, MONHOC mh){
	if(dsmh == NULL){
		PTRMH p = new NODEMH;
		p->data = mh;
		p->left = NULL;
		p->right = NULL;
		dsmh = p;
		return;
	}else if(strcmp(dsmh->data.mamh, mh.mamh) < 0)
		them_node_mh(dsmh->right, mh);
	else if(strcmp(dsmh->data.mamh, mh.mamh) > 0)
		them_node_mh(dsmh->left, mh);
}

void VeKhungGiaoDien(){
	textcolor(14);
//	textcolor(244);
//	SetConsoleBackgroundColor(20, 50, RGB(250, 250, 250)); //set background trang
	setxy(1, 1);
	DrawRect(0, 0, 167, 36); // ve khung lon
	DrawRect(1, 1, 30, 17); // ve khung menu con
	DrawRect(1, 19, 30, 9); // ve khung HDSD
	DrawRect(1, 29, 30, 6);// ve khung thong bao
	SetBGColor(0);
}

void xoa_hdsd(){
	textcolor(0);
	for (int i = 21; i < 27; i++){
		gotoxy(3, i);
		cout << "                             ";
	}
}

void xoa_menu(){
	textcolor(0);
	for (int i = 4; i <= 18; i++){
		gotoxy(3, i);
		cout << "                             ";
	}
}

void xoaHienThiChucNang(){
	textcolor(0);
	for (int i = 3; i <= 7; i++){
		gotoxy(33, i);
		cout << "                                                                                                                                 ";
	}
}

void xoaBang(){
	SetBGColor(0);
	textcolor(0);
	for (short i = 4; i <= 36; i++){
		gotoxy(35,i);
		cout << "                                                                                                                                   ";
	}
	textcolor(15);
}

void xoaBangCon(){
	SetBGColor(0);
	textcolor(0);
	for (short i = 10; i <= 28; i++){
		gotoxy(60,i);
		cout << "                                                             ";
	}
	textcolor(15);
}

void HDSD(){
	textcolor(9);
	SetBGColor(0);
	gotoxy(13,21); cout << "HUONG DAN";
	gotoxy(3,23); cout << "Dung phim " << len << xuong << " de di chuyen";
	gotoxy(3,24); cout << "Nhan Enter de chon";
	gotoxy(3,25); cout << "ESC de quay lai";
}

void HienThiTrang(int trang, int tongtrang, int x, int y) {
	textcolor(174);	gotoxy(x, y); cout << " Trang:        ";
	gotoxy(x + 8, y); cout << trang << "/" << tongtrang;
	textcolor(14);
}

void ThongBaoMenu(){
	textcolor(15);
	SetBGColor(4);
	gotoxy(13,31);
	cout << "THONG BAO";
	textcolor(0);
}

void VeNut(short y, int luachon, const char menu[][30]){
	DrawRect(cot - 1, y - 1, 28, 2);
//	ToMauBar(y, cot + 1, y + 3, cot + 27);
	textcolor(9);
	gotoxy((36 - strlen(menu[luachon])) / 2, y + 1);
	cout << menu[luachon];
}

void veNutHienThiChucNang(short y, int luachon, const char menu[][30]){
	textcolor(15);
	DrawRect(80, y, 28, 2);
	textcolor(9);
	gotoxy(80 + (28 - strlen(menu[luachon])) /2 + 1, y + 2);
	cout << menu[luachon];
}

void ve_menu(const char menu[][30]){
	for (short i = 0; i < 4; i++)
		VeNut(dong * (i + 1), i, menu);
}

void VeKhung(int x, int y, int max_X, int max_Y, int tdc1, int tdc2, int tdc3, int tdc4, int tdc5, int tdc6){
//	textcolor(15); // Toa Do Cat la diem se cat xuong thanh khung
	gotoxy(x,y);
	cout << (char )218; // tren dau
	for (int j = x + 1; j < max_X; j++){
		if (j == tdc1 || j == tdc2 || j == tdc3 || j == tdc4 || j == tdc5 || j == tdc6) cout << (char )194; // tren giua
		else cout << (char )196; // ve ngang
	}
	cout << (char )191; // tren cuoi
	
	for (int i = y + 1; i <= max_Y; i++){
		for (int j = x; j <= max_X; j++){
			gotoxy(j ,i);
			if (i != max_Y && i % 2 == 0 && j == x){
				cout << (char )195; // giua dau
			}
			else if ((i != max_Y && i % 2 == 0) && (j == tdc1 || j == tdc2 || j == tdc3 || j == tdc4 || j == tdc5 || j == tdc6)){
				cout << (char )197; // giua giua
			}
			else if ((i != max_Y && i % 2 == 0) && j == max_X){
				cout << (char )180; // giua cuoi
			}
			else if ((i % 2 == 0 && i != max_Y) && (j != x && j != max_X && j != tdc1 && j != tdc2 && j != tdc3 && j != tdc4 && j != tdc5 && j != tdc6)){
				cout << (char )196; // ve ngang
			}
			else if (i % 2 != 0 && (j == x || j == max_X || j == tdc1 || j == tdc2 || j == tdc3 || j == tdc4 || j == tdc5 || j == tdc6)){
				cout << (char )179; // cot
			}
		}
	}
	gotoxy(x, max_Y);
	cout << (char )192; // cuoi dau
	for (int j = x + 1; j < max_X; j++){
		if (j == tdc1 || j == tdc2 || j == tdc3 || j == tdc4 || j == tdc5 || j == tdc6) cout << (char )193; // cuoi giua
		else cout << (char )196; // ve ngang
	}
	cout << (char )217; // cuoi cuoi
}
//==================================================== Menu ===============================================
int veMenuChinh(short chon){
	chon = 0;
	normal();
	ve_menu(menu_chinh);
	xoaHienThiChucNang();
	veNutHienThiChucNang(3, chon, menu_chinh);
	highlight(15, 9);
	VeNut(dong + chon * 4, chon , menu_chinh);
	unsigned char kytu;
	do {
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		switch (kytu){
		case UP:
			if (chon > 0){
				highlight(9, 0);
				VeNut(dong + chon * 4, chon, menu_chinh);
				chon--;
				xoaHienThiChucNang();
				veNutHienThiChucNang(3, chon, menu_chinh);
				highlight(15, 9);
				VeNut(dong + chon * 4, chon, menu_chinh);
			}
			break;
		case DOWN:
			if (chon + 1 < 4){
				highlight(9, 0);
				VeNut(dong + chon * 4, chon, menu_chinh);
				chon++;
				xoaHienThiChucNang();
				veNutHienThiChucNang(3, chon, menu_chinh);
				highlight(15, 9);
				VeNut(dong + chon * 4, chon, menu_chinh);
			}
			break;
		case ENTER:
			xoa_menu();
			if (chon == 0)
				return veMenuPhu(menu_dsltc, chon);
			else if (chon == 1)
				return veMenuPhu(menu_dssv, chon);
			else if (chon == 2)
				return veMenuPhu(menu_dsmh, chon);
			else if (chon == 3)
				return veMenuPhu(menu_dangki, chon);
		break;
		case F1: VeKhung(58, 4, 160, 36, 66, 120, 150, 0, 0, 0);
		break;
		case F2: xoaBang();
		break;
		case F3:
			xoaHienThiChucNang();
			break;
		case F4:
			xoa_menu();
			break;
		case ESC: return 0;
		}
	} while (1);
}

int veMenuPhu(const char menu[][30], short chon){
	chon = 0;
	normal();
	PTRMH dsmh = NULL;
	ve_menu(menu);
	xoaHienThiChucNang();
	veNutHienThiChucNang(3, chon, menu);
	highlight(15, 9);
	VeNut(dong + chon * 4, chon, menu);
	unsigned char kytu;
	do {
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		switch (kytu){
		case UP:
			if (chon > 0){
				highlight(9, 0); VeNut(dong + chon * 4, chon, menu);
				chon--;
				xoaHienThiChucNang();
				veNutHienThiChucNang(3, chon, menu);
				highlight(15, 9); VeNut(dong + chon * 4, chon, menu);
			}
			break;
		case DOWN:
			if (chon + 1 < 4){
				highlight(9, 0);
				VeNut(dong + chon * 4, chon, menu);
				chon++;
				xoaHienThiChucNang();
				veNutHienThiChucNang(3, chon, menu);
				highlight(15, 9);
				VeNut(dong + chon * 4, chon, menu);
			}
			break;
//		case ENTER:
//			if (menu == menu_dsltc){ // Chuc nang lop tin chi
//				if (chon == 0) return xuly_dsltc(menu);
//				else if (chon == 1) return suaVaXoaLopTinChi(menu);
//				else if (chon == 2) return timMaLopTinChi(menu); // Bo sung
//				else if (chon == 3) return inDssvLopTinChi(menu);
//			}
//			else if (menu == menu_dssv){
//				if (chon == 0)	return them_sinh_vien(menu);
//				else if (chon == 1)	return sua_va_xoa_sinh_vien(menu);
//				else if (chon == 2) return tim_ma_sinh_vien(menu); // Bo sung
//				else if (chon == 3) return in_danh_sach_sinh_vien(menu);
//			}
//			else if (menu == menu_dsmh){
//				if (chon == 0)	return them_mon_hoc(menu, dsmh);
//				else if (chon == 1)	return sua_va_xoa_mon_hoc(menu);
//				else if (chon == 2) return dang_ky(menu); // Bo sung
//				else if (chon == 3) return in_danh_sach_mon_hoc(menu);
//			}
//			else if (menu == menu_dangki){
//				if (chon == 0)	return nhap_diem_lop_tin_chi(menu);
//				else if (chon == 1)	return bang_diem_mon_hoc(menu);
//				else if (chon == 2) return diem_trung_binh(menu); // Bo sung
//				else if (chon == 3) return diem_tong_ket(menu);
//			}
//			break;
//		case ESC:
//			xoa_menu();
//			if (menu == menu_dsltc) return veMenuChinh(0);
//			else if (menu == menu_dssv) return veMenuChinh(1);
//			else if (menu == menu_dsmh) return veMenuChinh(2);
//			else if (menu == menu_dangki) return veMenuChinh(3);
		}
	} while (1);
}
//==================================================== Menu ===============================================
//========================================== LTC ==========================================
//Them Lop Tin chi.
int them_ltc(DSLTC &dsltc, PTRMH dsmh){
	int key;
	int x = 33, y = 11;
	int vitri = 0, vitri_LTC = 0;
	char tam[10];
	int check_trung;
	int maLtc_trung;
	int ktmaLtc_trung;
	LTC *lopTc;
//	Khung_Sua_LTC();
	gotoxy(x, y);
MALOPTC:
	while (1){
		textcolor(245);
		gotoxy(19, 13); cout << "Ki tu so: (0-9). Toi da 10 ki tu!";
		textcolor(14);
		gotoxy(9 + vitri, y);
		key = get_key();

		if ((key >= '0' && key <= '9') && (vitri < 10))
		{
			tam[vitri] = char(key);
//			tam[vitri] = toupper(tam[vitri]);
			cout << tam[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
//			if (full_ltc(dsltc)) continue;
			tam[vitri] = '\0';
			lopTc->maloptc = atoi(tam);
			check_trung = search_maltc(dsltc, lopTc->maloptc);
			if (check_trung != -1 && check_trung != vitri_LTC){
				ghi_chu("Trung ma Lop Tin Chi", 35, 27, 79, 1000);
				gotoxy(9 + vitri, y);
				continue;
			}
			vitri = strlen(lopTc->mamh);
			gotoxy(23 + vitri, y);
			goto MAMH;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(9 + vitri, y);
			cout << " ";
			gotoxy(9 + vitri, y);
		}
		if (key == UP && vitri != 0){
			if (full_ltc(dsltc)) continue;
			tam[vitri] = '\0';
			lopTc->maloptc = atoi(tam);
			check_trung = search_maltc(dsltc, lopTc->maloptc);
			if (check_trung != -1 && check_trung != vitri_LTC){
				ghi_chu("Trung Ma Lop Tin Chi", 35, 27, 79, 1000);
				gotoxy(9 + vitri, y);
				continue;
			}
			vitri = strlen(lopTc->mamh);
			gotoxy(23 + vitri, y);
			goto MAMH;
		}
		if (key == ESC || key == F2){
			return 0;
		}
	}
MAMH:
	vitri = 0;
	while (1){
		textcolor(245);
		gotoxy(19, 13); cout << "Ki tu so & chu: (A-Z) && (0-9). Toi da 10 ki tu!";
		textcolor(14);
		gotoxy(23 + vitri, y);
		key = get_key();
		if (lopTc->maloptc == 0)		//Kiem tra ・ph僘 truoc c・du~ lieu chua
		{
			ghi_chu("Ban chua nhap ma lop", 35, 27, 79, 700);
			vitri = 0;
			gotoxy(9, y);
			goto MALOPTC;
		}
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			lopTc->mamh[vitri] = char(key);
			lopTc->mamh[vitri] = toupper(lopTc->mamh[vitri]);
			cout << lopTc->mamh[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			lopTc->mamh[vitri] = '\0';
			int temp = 0;
			temp = kiem_tra_trung_mh(dsmh, lopTc->mamh);
			if (temp == 1){
				itoa(lopTc->nienkhoa, tam, 10);
				vitri = strlen(tam);
				gotoxy(40 + vitri, y);
				goto NIENKHOA;
			}
			else {
				ghi_chu("MON HOC KHONG TON TAI", 35, 27, 79, 700);
				gotoxy(23 + vitri, y);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(23 + vitri, y);
			cout << " ";
			gotoxy(23 + vitri, y);
		}
		if (key == DOWN)
		{
			lopTc->mamh[vitri] = '\0';
			itoa(lopTc->maloptc, tam, 10);
			vitri = strlen(tam);
			gotoxy(9 + vitri, y);
			goto MALOPTC;
		}
		if (key == UP)
		{
			lopTc->mamh[vitri] = '\0';
			int temp;
			temp = kiem_tra_trung_mh(dsmh, lopTc->mamh);
			if (temp == 1) {
				itoa(lopTc->nienkhoa, tam, 10);
				vitri = strlen(tam);
				gotoxy(40 + vitri, y);
				goto NIENKHOA;
			}
			else {
				ghi_chu("MON HOC KHONG TON TAI", 35, 27, 79, 700);
				gotoxy(23 + vitri, y);
				continue;
			}
		}
		if (key == ESC || key == F2){
			return 0;
		}
	}
NIENKHOA:
	vitri = 0;
	while (1)
	{
		textcolor(245);
		gotoxy(19, 13); cout << "Ki tu so: (0-9). Toi da 4 ki tu!";
		textcolor(14);
		gotoxy(40 + vitri, y);
		key = get_key();
		if (lopTc->mamh == '\0')		//Kiem tra ・ph僘 truoc c・du~ lieu chua
		{
			ghi_chu("Ban chua nhap ma mon hoc", 35, 27, 79, 700);
			vitri = 0;
			gotoxy(23, y);
			goto MAMH;
		}
		if ((key <= '9' && key >= '0') && (vitri < 4))
		{
			tam[vitri] = char(key);
			cout << tam[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			tam[vitri] = '\0';
			lopTc->nienkhoa = atoi(tam);
			if (lopTc->nienkhoa >= 2017 && lopTc->nienkhoa <= 2021)
			{
				itoa(lopTc->hocki, tam, 10);
				vitri = strlen(tam);
				gotoxy(50 + vitri, y);
				goto HOCKI;
			}
			else {
				ghi_chu("       NAM KHONG HOP LE     ", 35, 27, 79, 700);
				gotoxy(40 + vitri, y);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(40 + vitri, y);
			cout << " ";
			gotoxy(40 + vitri, y);
		}
		if (key == DOWN)
		{
			tam[vitri] = '\0';
			vitri = strlen(lopTc->mamh);
			gotoxy(23 + vitri, y);
			goto MAMH;
		}
		if (key == UP)
		{
			tam[vitri] = '\0';
			lopTc->nienkhoa = atoi(tam);
			if (lopTc->nienkhoa >= 2017 && lopTc->nienkhoa <= 2021)
			{
				itoa(lopTc->hocki, tam, 10);
				vitri = strlen(tam);
				gotoxy(50 + vitri, y);
				goto HOCKI;
			}
			else {
				ghi_chu("       NAM KHONG HOP LE     ", 35, 27, 79, 700);
				gotoxy(40 + vitri, y);
				continue;
			}
		}
		if (key == ESC || key == F2)
		{
			return 0;
		}
	}
HOCKI:
	vitri = 0;
	while (1)
	{
		textcolor(245);
		gotoxy(19, 13); cout << "Ki tu so: (0-9). Toi da 1 ki tu!";
		textcolor(14);
		gotoxy(50 + vitri, y); // vi tri nhap tiep theo
		key = get_key();
		if (lopTc->nienkhoa == '\0')		//Kiem tra ・ph僘 truoc c・du~ lieu chua
		{
			ghi_chu("Ban chua nhap nien khoa", 35, 27, 79, 700);
			vitri = 0;
			gotoxy(40, y);
			goto NIENKHOA;
		}
		if ((key <= '2' && key >= '1') && (vitri < 1))
		{
			tam[vitri] = char(key);
			cout << tam[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			tam[vitri] = '\0';
			lopTc->hocki = atoi(tam);
			itoa(lopTc->nhom, tam, 10);
			vitri = strlen(tam);
			gotoxy(60 + vitri, y);
			goto NHOM;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(50 + vitri, y);
			cout << " ";
			gotoxy(50 + vitri, y);
		}
		if (key == DOWN)
		{
			tam[vitri] = '\0';
			itoa(lopTc->nienkhoa, tam, 10);
			vitri = strlen(tam);
			gotoxy(40 + vitri, y);
			goto NIENKHOA;
		}
		if (key == UP)
		{
			tam[vitri] = '\0';
			lopTc->hocki = atoi(tam);
			itoa(lopTc->nhom, tam, 10);
			vitri = strlen(tam);
			gotoxy(60 + vitri, y);
			goto NHOM;
		}
		if (key == ESC || key == F2)
		{
			return 0;
		}
	}
NHOM:
	vitri = 0;
	while (1)
	{
		textcolor(245);
		gotoxy(19, 13); cout << "Ki tu so : (0-9). Toi da 1 ki tu!";
		textcolor(14);
		gotoxy(60 + vitri, y); // vi tri nhap tiep theo
		key = get_key();
		if (lopTc->hocki == '\0')		//Kiem tra ・ph僘 truoc c・du~ lieu chua
		{
			ghi_chu("Ban chua nhap hoc ki", 35, 27, 79, 700);
			vitri = 0;
			gotoxy(50, y);
			goto HOCKI;
		}
		if ((key <= '9' && key >= '1') && (vitri < 1))
		{
			tam[vitri] = char(key);
			cout << tam[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			tam[vitri] = '\0';
			lopTc->nhom = atoi(tam);
			int pochinki = check_trung_ltc(dsltc, lopTc);
			if (0 == pochinki) {
				itoa(lopTc->sosvmax, tam, 10);
				vitri = strlen(tam);
				gotoxy(68 + vitri, y);
				goto SOLUONGMAX;
			}
			if (1 == pochinki) {
				ghi_chu("Thong tin Ma mon hoc, Nien Khoa, Hoc ki, Nhom khong duoc trung", 20, 27, 79, 2000);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(60 + vitri, y);
			cout << " ";
			gotoxy(60 + vitri, y);
		}
		if (key == DOWN)
		{
			tam[vitri] = '\0';
			itoa(lopTc->hocki, tam, 10);
			vitri = strlen(tam);
			gotoxy(50 + vitri, y);
			goto HOCKI;
		}
		if (key == UP)
		{
			tam[vitri] = '\0';
			lopTc->nhom = atoi(tam);
			int pochinki = check_trung_ltc(dsltc, lopTc);
			if (0 == pochinki) {
				itoa(lopTc->sosvmax, tam, 10);
				vitri = strlen(tam);
				gotoxy(68 + vitri, y);
				goto SOLUONGMAX;
			}
			if (1 == pochinki) {
				ghi_chu("Thong tin Ma mon hoc, Nien Khoa, Hoc ki, Nhom khong duoc trung", 20, 27, 79, 2000);
				continue;
			}
		}
		if (key == ESC || key == F2){
			return 0;
		}
	}
SOLUONGMAX:
	vitri = 0;
	while (1)
	{
		textcolor(245);
		gotoxy(19, 13); cout << "Ki tu so : (0-9). Toi da 999 sinh vien!";
		textcolor(14);
		gotoxy(68 + vitri, y); // vi tri nhap tiep theo
		key = get_key();
		if (lopTc->nhom == '\0')		//Kiem tra ・ph僘 truoc c・du~ lieu chua
		{
			ghi_chu("Ban chua nhap nhom", 35, 27, 79, 700);
			vitri = 0;
			gotoxy(60, y);
			goto NHOM;
		}
		if ((key <= '9' && key >= '0') && (vitri < 3))
		{
			tam[vitri] = char(key);
			cout << tam[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			tam[vitri] = '\0';
			lopTc->sosvmax = atoi(tam);
			//khuc nay nen tao ham` INSERT ltc
//			dsltc.ds_ltc[vitri_LTC]->maloptc = lopTc->maloptc;
//			strcpy(dsltc.ds_ltc[vitri_LTC]->mamh, lopTc->mamh);
//			dsltc.ds_ltc[vitri_LTC]->nienkhoa = lopTc->nienkhoa;
//			dsltc.ds_ltc[vitri_LTC]->hocki = lopTc->hocki;
//			dsltc.ds_ltc[vitri_LTC]->nhom = lopTc->nhom;
//			dsltc.ds_ltc[vitri_LTC]->sosvmax = lopTc->sosvmax;

			ghi_chu("Da luu vao bo nho", 40, 27, 228, 500);	textcolor(12);
//			ghi_file_dsltc(dsltc);

			return 1;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(68 + vitri, y);
			cout << " ";
			gotoxy(68 + vitri, y);
		}
		if (key == DOWN)
		{
			tam[vitri] = '\0';
			itoa(lopTc->nhom, tam, 10);
			vitri = strlen(tam);
			gotoxy(60 + vitri, y);
			goto NHOM;
		}
		if (key == ESC)
		{
			return 0;
		}
	}
}

//Xoa Lop Tin chi
int xoa_ltc(DSLTC &dsltc) {
	int key;
	int x = 33, y = 14;
	int vitri = 0, vitri_LTC;
	int malopXoa;
	char tam[11];
//	Khung_Xoa_LTC();
	gotoxy(x, y);
	while (1)
	{
		textcolor(14);
		key = get_key();
		if ((key >= '0' && key <= '9') && (vitri < 10))
		{
			tam[vitri] = char(key);
			cout << tam[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			tam[vitri] = '\0';
			malopXoa = atoi(tam);
			vitri_LTC = search_maltc(dsltc, malopXoa);
			if (-1 == vitri_LTC) {
				ghi_chu("LOP TIN CHI KHONG TON TAI!", 35, 27, 79, 700);
				gotoxy(33 + vitri, y);
				continue;
			}
			else {
				if (dsltc.ds_ltc[vitri_LTC]->head != NULL) {
					ghi_chu("LOP TIN CHI DA CO SINH VIEN. KHONG THE XOA!", 35, 27, 79, 700);
					continue;
				}
				//hoi user chac muon xoa ltc nay
				xoa_ltc(dsltc, vitri_LTC);
				ghi_chu("XOA THANH CONG LOP TIN CHI", 35, 27, 79, 1000);
				return 1;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(33 + vitri, y);
			cout << " ";
			gotoxy(33 + vitri, y);
		}
		if (key == ESC || key == F3) {
			return 0;
		}
	}
}

void veBangMonHoc(){
	SetBGColor(2);
	textcolor(15);
	gotoxy(90, 4); cout << "DANH SACH MON HOC";
	SetBGColor(0);
	VeKhung(38, 6, 165, 34, 63, 118, 141, 0, 0, 0);
	gotoxy(45,7);	cout << "MA MON HOC";
	gotoxy(86, 7);	cout << "TEN MON HOC";
	gotoxy(120, 7);	cout << "SO TIN CHI LY THUYET";
	gotoxy(143, 7);	cout << "SO TIN CHI THUC HANH";
}

int veBangThemLTC(short check){
	xoaBang();
	textcolor(15);
	VeKhung(60, 10, 120, 28, 0, 0, 0, 0, 0, 0);
	gotoxy(3,27); cout << "Nhan F1 de Luu";
	gotoxy(3,28); cout << "Nhan F2 de Huy";
	SetBGColor(3);
	gotoxy(79,11); cout << "THEM LOP TIN CHI";
	SetBGColor(2);
	gotoxy(62,13); cout << " MA LOP       ";
	gotoxy(62,15); cout << " MA MON HOC   ";
	gotoxy(62,17); cout << " TEN MON HOC  ";
	gotoxy(62,19); cout << " NIEN KHOA    ";
	gotoxy(62,21); cout << " HOC KY       ";
	gotoxy(62,23); cout << " NHOM         ";
	gotoxy(62,25); cout << " SV TOI DA    ";
	gotoxy(62,27); cout << " SV TOI THIEU ";
	SetBGColor(0);
	gotoxy(77,13);//nhap so lieu
	unsigned char kytu;
	do{
		kytu = getch();
		if (kytu == 0) kytu = getch();
		switch(kytu){
			case F1:
				if (check == 0)
//				return themLopTinChi(menu_dsltc);
//				else if (check == 2 || check == 3){
//					xoaBang();
//					return sua_va_xoa_mon_hoc(menu_dsmh);
//				}
			case F2:
				return 0;
			case ESC: break;
		}
	} while (1);
}
//test
//int veBangThemLTC(short check, MONHOC** mang, unsigned short soluong){
//	xoaBang();
//	textcolor(15);
//	VeKhung(60, 10, 120, 28, 0, 0, 0, 0, 0, 0);
//	gotoxy(3,27); cout << "Nhan F1 de Luu";
//	gotoxy(3,28); cout << "Nhan F2 de Huy";
//	SetBGColor(3);
//	gotoxy(79,11); cout << "THEM LOP TIN CHI";
//	SetBGColor(2);
//	gotoxy(62,13); cout << " MA LOP       ";
//	gotoxy(62,15); cout << " MA MON HOC   ";
//	gotoxy(62,17); cout << " TEN MON HOC  ";
//	gotoxy(62,19); cout << " NIEN KHOA    ";
//	gotoxy(62,21); cout << " HOC KY       ";
//	gotoxy(62,23); cout << " NHOM         ";
//	gotoxy(62,25); cout << " SV TOI DA    ";
//	gotoxy(62,27); cout << " SV TOI THIEU ";
//	SetBGColor(0);
//	gotoxy(77,13);//nhap so lieu
//	unsigned char kytu;
//	do{
//		kytu = getch();
//		if (kytu == 0) kytu = getch();
//		switch(kytu){
////			case ENTER:
////				nhap_thong_tin_ltc(dsltc);
//			case ESC:
//				if (check == 0)
//				return themLopTinChi(menu_dsltc, mang, soluong);
//				else if (check == 2 || check == 3){
//					xoaBang();
//					return sua_va_xoa_mon_hoc(menu_dsmh);
//				}
//			case F2:
//				return 0;
//		}
//	} while (1);
//}

void veBangLopTinChi(){
	SetBGColor(2);
	textcolor(15);
//	gotoxy(88, 4); cout << "DANH SACH LOP TIN CHI";
	SetBGColor(0);
	VeKhung(40, 6, 165, 34, 49, 63, 112, 124, 0, 0);
	gotoxy(42,7);	cout << "MA LOP";
	gotoxy(51,7);	cout << "MA MON HOC";
	gotoxy(80,7);	cout << "NIEN KHOA";
	gotoxy(113,7);	cout << "HOC KI";
	gotoxy(125,7);	cout << "NHOM";
	gotoxy(135,7);	cout << "SV TOI DA";
}

int veBangSuaXoaLTC(short check){
	xoaBangCon();
//	xoa_hdsd();
	textcolor(15);
	VeKhung(60, 10, 120, 28, 0, 0, 0, 0, 0, 0);
	gotoxy(3,28); cout << "Nhan F1 de Luu";
	gotoxy(3,29); cout << "Nhan F2 de Huy";
	SetBGColor(3);
	gotoxy(62,13); cout << " MA LOP       ";
	gotoxy(62,15); cout << " MA MON HOC   ";
	gotoxy(62,17); cout << " TEN MON HOC  ";
	gotoxy(62,19); cout << " NIEN KHOA    ";
	gotoxy(62,21); cout << " HOC KY       ";
	gotoxy(62,23); cout << " NHOM         ";
	gotoxy(62,25); cout << " SV TOI DA    ";
	gotoxy(62,27); cout << " SV TOI THIEU ";
	SetBGColor(2);
	gotoxy(80,11); cout << "SUA LOP TIN CHI";
	SetBGColor(0);
	gotoxy(77,13);//nhap so lieu
	unsigned char kytu;
	do{
		kytu = getch();
		if (kytu == 0) kytu = getch();
		switch(kytu){
			case F1:
				if (check == 0)
//				return suaVaXoaLopTinChi(menu_dsltc);
//				else if (check == 1){
					xoaBang();
					return nhap_diem_lop_tin_chi(menu_dangki);
//				}
//			case F2:
//				return ve_bang_diem();
			default: break;
		}
	} while (1);
}

int hieu_chinh_dsltc(DSLTC &dsltc, PTRMH dsmh) {
	int key;
	int x = 33, y = 11;
	int vitri = 0, vitri_LTC;
	int malopSua;
	char tam[10];
	int check_trung;
	int maLtc_trung;
	int ktmaLtc_trung;
	//DSLTC.n++;
	LTC *lopTc;
//	Khung_Sua_LTC();
	gotoxy(x, y);
	while (1) {
		textcolor(14);
		key = get_key();
		if ((key >= '0' && key <= '9') && (vitri < 10))
		{
			tam[vitri] = char(key);
			tam[vitri] = toupper(tam[vitri]);
			cout << tam[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			tam[vitri] = '\0';
			malopSua = atoi(tam); // chi? chuyen? ki so trong chuoi thanh so nguyen, khong the chuyen chu cai
			vitri_LTC = search_maltc(dsltc, malopSua);
			if (-1 == vitri_LTC) {
				ghi_chu("LOP TIN CHI KHONG TON TAI!", 35, 27, 79, 700);
				gotoxy(33 + vitri, y);
				textcolor(14);
				continue;
			}
			else {
				vitri = 0;
				gotoxy(9, y);
//				Khung_Them_LTC();
				textcolor(4);
				lopTc->maloptc = dsltc.ds_ltc[vitri_LTC]->maloptc;
				itoa(lopTc->maloptc, tam, 10); // doi maltc thanh char tam, voi co so la 10
				vitri = strlen(tam);
				strcpy(lopTc->mamh, dsltc.ds_ltc[vitri_LTC]->mamh);
				lopTc->nienkhoa = dsltc.ds_ltc[vitri_LTC]->nienkhoa;
				lopTc->hocki = dsltc.ds_ltc[vitri_LTC]->hocki;
				lopTc->nhom = dsltc.ds_ltc[vitri_LTC]->nhom;
				lopTc->sosvmax = dsltc.ds_ltc[vitri_LTC]->sosvmax;
				gotoxy(9, y); cout << tam;
				gotoxy(24, y); cout << lopTc->mamh;
				gotoxy(41, y); cout << lopTc->nienkhoa;
				gotoxy(54, y); cout << lopTc->hocki;
				gotoxy(64, y); cout << lopTc->nhom;
				gotoxy(71, y); cout << lopTc->sosvmax;
				goto MALOPTC;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(33 + vitri, y);
			cout << " ";
			gotoxy(33 + vitri, y);
		}
		if (key == ESC || key == F2)
		{
			return 0;
		}
	}

MALOPTC:
	vitri = 0;
	while (1)
	{
		textcolor(245);
		gotoxy(19, 13); cout << "Ki tu so: (0-9). Toi da 10 ki tu!";
		textcolor(14);
		gotoxy(9 + vitri, y);
		key = get_key();

		if ((key >= '0' && key <= '9') && (vitri < 10))
		{
			tam[vitri] = char(key);
			tam[vitri] = toupper(tam[vitri]);
			cout << tam[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			tam[vitri] = '\0';
			lopTc->maloptc = atoi(tam);
			check_trung = search_maltc(dsltc, lopTc->maloptc);
			if (check_trung != -1 && check_trung != vitri_LTC){
				ghi_chu("Ma lop tin chi la duy nhat! Da ton tai", 35, 27, 79, 1000);
				gotoxy(9 + vitri, y);
				continue;
			}
			vitri = strlen(lopTc->mamh);
			gotoxy(24 + vitri, y);
			goto MAMH;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(9 + vitri, y);
			cout << " ";
			gotoxy(9 + vitri, y);
		}
		if (key == UP)
		{
			tam[vitri] = '\0';
			lopTc->maloptc = atoi(tam);
			check_trung = search_maltc(dsltc, lopTc->maloptc);
			if (check_trung != -1 && check_trung != vitri_LTC){
				ghi_chu("Ma lop tin chi la duy nhat! Da ton tai", 35, 27, 79, 1000);
				gotoxy(9 + vitri, y);
				continue;
			}
			vitri = strlen(lopTc->mamh);
			gotoxy(24 + vitri, y);
			goto MAMH;
		}
		if (key == ESC || key == F2)
		{
			//DSLTC.n--;
			return 0;
		}
	}
MAMH:
	vitri = 0;
	while (1)
	{
		textcolor(245);
		gotoxy(19, 13); cout << "Ki tu so & chu: (A-Z) && (0-9). Toi da 10 ki tu!";
		textcolor(14);
		gotoxy(24 + vitri, y);
		key = get_key();
		if (lopTc->maloptc == '\0')		//Kiem tra ・ph僘 truoc c・du~ lieu chua
		{
			ghi_chu("Ban chua nhap ma lop", 35, 27, 79, 700);
			vitri = 0;
			gotoxy(9, y);
			goto MALOPTC;
		}
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			lopTc->mamh[vitri] = char(key);
			lopTc->mamh[vitri] = toupper(lopTc->mamh[vitri]);
			cout << lopTc->mamh[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			lopTc->mamh[vitri] = '\0';
			int temp;
			temp = kiem_tra_trung_mh(dsmh, lopTc->mamh);
			if (temp == 1) {
				itoa(lopTc->nienkhoa, tam, 10);
				vitri = strlen(tam);
				gotoxy(41 + vitri, y);
				goto NIENKHOA;
			}
			else {
				ghi_chu("MON HOC KHONG TON TAI", 35, 27, 79, 700);
				gotoxy(24 + vitri, y);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(24 + vitri, y);
			cout << " ";
			gotoxy(24 + vitri, y);
		}
		if (key == DOWN)
		{
			lopTc->mamh[vitri] = '\0';
			itoa(lopTc->maloptc, tam, 10);
			vitri = strlen(tam);
			gotoxy(9 + vitri, y);
			goto MALOPTC;
		}
		if (key == UP)
		{
			lopTc->mamh[vitri] = '\0';
			int temp;
			temp = kiem_tra_trung_mh(dsmh, lopTc->mamh);
			if (temp == 1) {
				itoa(lopTc->nienkhoa, tam, 10);
				vitri = strlen(tam);
				gotoxy(41 + vitri, y);
				goto NIENKHOA;
			}
			else {
				ghi_chu("MON HOC KHONG TON TAI", 35, 27, 79, 700);
				gotoxy(24 + vitri, y);
				continue;
			}
		}
		if (key == ESC || key == F2)
		{
			//DSLTC.n--;
			return 0;
		}
	}
NIENKHOA:
	vitri = 0;
	while (1)
	{
		textcolor(245);
		gotoxy(19, 13); cout << "Ki tu so: (0-9). Toi da 4 ki tu!";
		textcolor(14);
		gotoxy(41 + vitri, y);
		key = get_key();
		if (lopTc->mamh == '\0')		//Kiem tra ・ph僘 truoc c・du~ lieu chua
		{
			ghi_chu("Ban chua nhap ma mon hoc", 35, 27, 79, 700);
			vitri = 0;
			gotoxy(24, y);
			goto MAMH;
		}
		if ((key <= '9' && key >= '0') && (vitri < 4))
		{
			tam[vitri] = char(key);
			cout << tam[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			tam[vitri] = '\0';
			lopTc->nienkhoa = atoi(tam);
			if (lopTc->nienkhoa >= 2017 && lopTc->nienkhoa <= 2021)
			{
				itoa(lopTc->hocki, tam, 10);
				vitri = strlen(tam);
				gotoxy(54 + vitri, y);
				goto HOCKI;
			}
			else {
				ghi_chu("       NAM KHONG HOP LE     ", 35, 27, 79, 700);
				gotoxy(41 + vitri, y);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(41 + vitri, y);
			cout << " ";
			gotoxy(41 + vitri, y);
		}
		if (key == DOWN)
		{
			vitri = strlen(lopTc->mamh);
			gotoxy(24 + vitri, y);
			goto MAMH;
		}
		if (key == UP)
		{
			tam[vitri] = '\0';
			lopTc->nienkhoa = atoi(tam);
			if (lopTc->nienkhoa >= 2017 && lopTc->nienkhoa <= 2021)
			{
				itoa(lopTc->hocki, tam, 10);
				vitri = strlen(tam);
				gotoxy(54 + vitri, y);
				goto HOCKI;
			}
			else {
				ghi_chu("       NAM KHONG HOP LE     ", 35, 27, 79, 700);
				gotoxy(41 + vitri, y);
				continue;
			}
		}
		if (key == ESC || key == F2)
		{
			//DSLTC.n--;
			return 0;
		}
	}
HOCKI:
	vitri = 0;
	while (1)
	{
		textcolor(245);
		gotoxy(19, 13); cout << "Ki tu so: (0-9). Toi da 1 ki tu!";
		textcolor(14);
		gotoxy(54 + vitri, y); // vi tri nhap tiep theo
		key = get_key();
		if (lopTc->nienkhoa == '\0')		//Kiem tra ・ph僘 truoc c・du~ lieu chua
		{
			ghi_chu("Ban chua nhap nien khoa", 35, 27, 79, 700);
			vitri = 0;
			gotoxy(41, y);
			goto NIENKHOA;
		}
		if ((key <= '2' && key >= '1') && (vitri < 1))
		{
			tam[vitri] = char(key);
			cout << tam[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			tam[vitri] = '\0';
			lopTc->hocki = atoi(tam);
			itoa(lopTc->nhom, tam, 10);
			vitri = strlen(tam);
			gotoxy(64 + vitri, y);
			goto NHOM;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(54 + vitri, y);
			cout << " ";
			gotoxy(54 + vitri, y);
		}
		if (key == DOWN)
		{
			itoa(lopTc->nienkhoa, tam, 10);
			vitri = strlen(tam);
			gotoxy(41 + vitri, y);
			goto NIENKHOA;
		}
		if (key == UP)
		{
			tam[vitri] = '\0';
			lopTc->hocki = atoi(tam);
			itoa(lopTc->nhom, tam, 10);
			vitri = strlen(tam);
			gotoxy(64 + vitri, y);
			goto NHOM;
		}
		if (key == ESC || key == F2)
		{
			return 0;
		}
	}
NHOM:
	vitri = 0;
	while (1)
	{
		textcolor(245);
		gotoxy(19, 13); cout << "Ki tu so : (0-9). Toi da 1 ki tu!";
		textcolor(14);
		gotoxy(64 + vitri, y); // vi tri nhap tiep theo
		key = get_key();
		if (lopTc->hocki == '\0')		//Kiem tra ・ph僘 truoc c・du~ lieu chua
		{
			ghi_chu("Ban chua nhap hoc ki", 35, 27, 79, 700);
			vitri = 0;
			gotoxy(54, y);
			goto HOCKI;
		}
		if ((key <= '9' && key >= '1') && (vitri < 1))
		{
			tam[vitri] = char(key);
			cout << tam[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			tam[vitri] = '\0';
			lopTc->nhom = atoi(tam);
			int pochinki = check_trung_ltc(dsltc, lopTc);
			if (0 == pochinki) {
				itoa(lopTc->sosvmax, tam, 10);
				vitri = strlen(tam);
				gotoxy(71 + vitri, y);
				goto SOLUONGMAX;
			}
			if (1 == pochinki) {
				ghi_chu("Thong tin 4 field Ma mon hoc, Nien Khoa, Hoc ki, Nhom khong duoc trung", 20, 27, 79, 2000);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(64 + vitri, y);
			cout << " ";
			gotoxy(64 + vitri, y);
		}
		if (key == DOWN)
		{
			itoa(lopTc->hocki, tam, 10);
			vitri = strlen(tam);
			gotoxy(54 + vitri, y);
			goto HOCKI;
		}
		if (key == UP)
		{
			tam[vitri] = '\0';
			lopTc->nhom = atoi(tam);
			int pochinki = check_trung_ltc(dsltc, lopTc);
			if (0 == pochinki) {
				itoa(lopTc->sosvmax, tam, 10);
				vitri = strlen(tam);
				gotoxy(71 + vitri, y);
				goto SOLUONGMAX;
			}
			if (1 == pochinki) {
				ghi_chu("Thong tin 4 field Ma mon hoc, Nien Khoa, Hoc ki, Nhom khong duoc trung", 20, 27, 79, 2000);
				continue;
			}
		}
		if (key == ESC || key == F2)
		{
			//DSLTC.n--;
			return 0;
		}
	}
SOLUONGMAX:
	vitri = 0;
	while (1)
	{
		textcolor(245);
		gotoxy(19, 13); cout << "Ki tu so : (0-9). Toi da 999 sinh vien!";
		textcolor(14);
		gotoxy(71 + vitri, y); // vi tri nhap tiep theo
		key = get_key();
		if (lopTc->nhom == '\0')		//Kiem tra ・ph僘 truoc c・du~ lieu chua
		{
			ghi_chu("Ban chua nhap nhom", 35, 27, 79, 700);
			vitri = 0;
			gotoxy(64, y);
			goto NHOM;
		}
		if ((key <= '9' && key >= '0') && (vitri < 3))
		{
			tam[vitri] = char(key);
			cout << tam[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
// hoi user chac chan muon luu
// neu dong y thi thuc hien gan'
			tam[vitri] = '\0';
			lopTc->sosvmax = atoi(tam);
//			dsltc.ds_ltc[vitri_LTC]->maloptc = lopTc->maloptc;
//			strcpy(dsltc.ds_ltc[vitri_LTC]->mamh, lopTc->mamh);
//			dsltc.ds_ltc[vitri_LTC]->nienkhoa = lopTc->nienkhoa;
//			dsltc.ds_ltc[vitri_LTC]->hocki = lopTc->hocki;
//			dsltc.ds_ltc[vitri_LTC]->nhom = lopTc->nhom;
//			dsltc.ds_ltc[vitri_LTC]->sosvmax = lopTc->sosvmax;
			ghi_chu("Da luu vao bo nho", 40, 27, 228, 500);	textcolor(12);
//			ghi_file_dsltc(dsltc);
// neu khong dong y thi khong gan' va thoat ra
			return 1;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(71 + vitri, y);
			cout << " ";
			gotoxy(71 + vitri, y);
		}
		if (key == DOWN)
		{
			itoa(lopTc->nhom, tam, 10);
			vitri = strlen(tam);
			gotoxy(64 + vitri, y);
			goto NHOM;
		}
		if (key == ESC || key == F2)
		{
			return 0;
		}
	}
}

//Buble Sort
void SortDSLTC(DSLTC &dsltc) {
	int i, j, temp;
	for (i = 1; i < dsltc.soluong; i++) {
		for (j = dsltc.soluong - 1; j >= i; j--) {
			if (dsltc.ds_ltc[j - 1]->maloptc > dsltc.ds_ltc[j]->maloptc) {
				temp = dsltc.ds_ltc[j - 1]->maloptc;
				dsltc.ds_ltc[j - 1]->maloptc = dsltc.ds_ltc[j]->maloptc;
				dsltc.ds_ltc[j]->maloptc = temp;
			}
		}
	}
}

int xuly_dsltc(DSLTC &dsltc, PTRMH dsmh){
	int key;
	int dem, trang = 0, tongtrang = 0;
//	bool check_change = false;
	while (1) {
		dem = 0;
		if (dsltc.soluong == 0) {
			ghi_chu("Chua co danh sach lop", 35, 27, 79, 1000);
		}
		else {
			if (dsltc.soluong < 13) {
				tongtrang = 1;
				trang = 0;
			}
			else {
				tongtrang = ((dsltc.soluong - 1) / 13 + 1);
			}
		}
		SortDSLTC(dsltc);
		textcolor(14);
		system("cls");
//		Khung_Xuat_LTC();
		for (int i = trang * 13; i < 13 + trang * 13 && i < dsltc.soluong; i++) {
			textcolor(12); gotoxy(6, 8 + dem); cout << (i + 1);
			textcolor(14);
			gotoxy(10, 8 + dem); cout << dsltc.ds_ltc[i]->maloptc;
			gotoxy(24, 8 + dem); cout << dsltc.ds_ltc[i]->mamh;
			gotoxy(41, 8 + dem); cout << dsltc.ds_ltc[i]->nienkhoa;
			gotoxy(56, 8 + dem); cout << dsltc.ds_ltc[i]->hocki;
			gotoxy(65, 8 + dem); cout << dsltc.ds_ltc[i]->nhom;
			gotoxy(73, 8 + dem); cout << dsltc.ds_ltc[i]->sosvmax;
			dem++;
		}
		HienThiTrang(trang + 1, tongtrang, 65, 26);
		gotoxy(73, 26);
		key = get_key();
		if ((key == RIGHT || key == DOWN) && trang < tongtrang - 1) { trang++; }
		if ((key == LEFT || key == UP) && trang > 0) { trang--; }
		if (key == F1)
		{
			if (full_ltc(dsltc)) { continue; }
			system("cls");
			gotoxy(20, 24);  textcolor(246);	cout << "F1"; //To mau` F1
			return them_ltc(dsltc, dsmh);
		}
		if (key == F2)
		{
			system("cls");
			gotoxy(36, 24);	textcolor(246);	cout << "F2"; //To mau` F2
			return xoa_ltc(dsltc);
		}
		if (key == F3)
		{
			system("cls");
			gotoxy(50, 24);	textcolor(246);	cout << "F3"; //To mau` F3 
			return hieu_chinh_dsltc(dsltc, dsmh);
		}
		if (key == ESC)
		{
//			if (check_change == true)
//			{
//				putchar(7);
				gotoxy(4, 24); textcolor(246); cout << "ESC"; //To mau` ESC
//				int temp = ThongBao_ESC();

//				if (temp == -1) { continue; }	//Tra ve -1 => Bat' duoc phim' ESC 1 l穗` nua~
//				if (temp == 1) {
//					ghi_chu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
//					ghi_file_dsltc(DSLTC);
//				}
//				if (temp == 0) { ghi_chu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000); }
//			}
			system("cls");
			return 0;
		}
	}
}

int inDssvDangKy(){
	SetBGColor(2);
	textcolor(15);
	gotoxy(79, 4); cout << "DANH SACH SINH VIEN DANG KY LOP TIN CHI";
	SetBGColor(0);
	VeKhung(40, 6, 165, 34, 59, 93, 120, 148, 0, 0);
	gotoxy(42,7);	cout << "MA SO SINH VIEN";
	gotoxy(75,7);	cout << "HO";
	gotoxy(106,7);	cout << "TEN";
	gotoxy(122,7);	cout << "PHAI";
	gotoxy(130,7);	cout << "SO DIEN THOAI";
	gotoxy(155,7);	cout << "LOP";
	gotoxy(150, 40); cout << "F1: In dssvDangKy\tF2: IndssvDangKy";
	char kytu;
	do {
		kytu = getch();
		if (kytu == -32) kytu = getch();
		switch(kytu){
			case F1:
				return inDssvDangKy();
			case F2:
				return inDssvDangKy();
			case ESC:
				xoaBang();
				return 0;
		}
	} while (1);
}

//============================================= SINH VIEN ==========================================

int ve_bang_sv(){
	SetBGColor(2);
	textcolor(15);
	gotoxy(90, 4); cout << "THEM SINH VIEN MOI";
	SetBGColor(0);
	VeKhung(38, 6, 165, 34, 90, 0, 0, 0, 0, 0);
	gotoxy(65, 7);	cout << "TEN LOP HOC";
	gotoxy(120, 7);	cout << "SO SINH VIEN HIEN TAI CUA LOP";
}

int ve_bang_sv_con(short check){
	SetBGColor(2);
	textcolor(15);
	gotoxy(90, 3); cout << "MA LOP: ....";
	gotoxy(82, 4); cout << "SO SINH VIEN CUA LOP NAY LA : ....";
	SetBGColor(0);
	VeKhung(38, 6, 165, 34, 63, 120, 140, 150, 0, 0);
	gotoxy(45,7);	cout << "MA SINH VIEN";
	gotoxy(90, 7);	cout << "HO";
	gotoxy(129, 7);	cout << "TEN";
	gotoxy(144, 7);	cout << "PHAI";
	gotoxy(157, 7);	cout << "SDT";
	unsigned short kytu;
	do{
		kytu = getch();
		if (kytu == -32) kytu = getch();
		switch(kytu){
			case ESC:
				if (check == 0){
					xoaBang();
					return 0;
				}
				else if (check == 1){
					xoaBang();
					return sua_va_xoa_sinh_vien(menu_dssv);
				}
				else if (check == 2){
					xoaBang();
					return tim_ma_sinh_vien(menu_dssv);
				}
				else if (check == 3){
					xoaBang();
					return in_danh_sach_sinh_vien(menu_dssv);
				}
				else if (check == 4){
					xoaBang();
					return diem_trung_binh(menu_dangki);
				}
				else if (check == 5){
					xoaBang();
					return diem_tong_ket(menu_dangki);
				}
		}
	} while(1);
}

int sua_va_xoa_sinh_vien(const char menu[][30]){
	short chon = 0;
	unsigned char kytu;
	if (menu == menu_dssv){
		if (chon == 0){
			xoaHienThiChucNang();
			SetBGColor(0);
			gotoxy(3,26); cout << "F1: Sua sinh vien da chon";
			gotoxy(3,27); cout << "F2: Xoa sinh vien da chon";
			gotoxy(3,28); cout << "F3: Tim kiem sinh vien";
			HienThiTrang(1, 2, 145, 35);
			ve_bang_sv();
			textcolor(2);
			gotoxy(36,9); cout << (char)16;
			do{
				kytu = getch();
				if (kytu == -32) kytu = getch();
				switch(kytu){
					case UP:
						if (chon % 13 == 0 && chon != 0){
							xoaBang();
							ve_bang_sv();
							textcolor(2);
							gotoxy(36,33); cout << (char)16;
							chon--;
						}
						else if (chon % 13 > 0){
							textcolor(0);
							gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
							chon--;
							textcolor(2);
							gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
						}
						break;
					case DOWN:
						if ((chon + 1) % 13 == 0){
							xoaBang();
							ve_bang_sv();
							textcolor(2);
							gotoxy(36,9); cout << (char)16;
							chon++;
						}
						else if ((chon + 1) % 13 < 13){
							textcolor(0);
							gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
							chon++;
							textcolor(2);
							gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
						}
						break;
					case F1: // Sua
						xoaBang();
						return ve_bang_sv_con(1);
					case F2: // Xoa
						return 0;
					case ESC:
						xoaBang();
//						xoa_hdsd();
						veMenuPhu(menu_dssv, 1);
						return -1;
				}
			} while (1);
		}
	}
}

int tim_ma_sinh_vien(const char menu[][30]){
	short chon = 0;
	unsigned char kytu;
	if (menu == menu_dssv){
		do {
			xoaHienThiChucNang();
			VeKhung(65, 15, 115, 17, 0, 0, 0, 0, 0, 0); // ve khung nhap ma sinh vien
			//nhap ma sinh vien
			//kiem tra ltc co trong dssv
			//co thi xuat ra thong tin sinh vien do'
			xoaBangCon();
			VeKhung(60, 10, 120, 28, 0, 0, 0, 0, 0, 0);// xuat thong tin sinh vien
			kytu = getch();
			if (kytu == 0) kytu = getch();
			switch(kytu){
				case ESC:
				xoaBang();
				return veMenuPhu(menu, 2);
			}
		} while (1);
	}
}

int in_danh_sach_sinh_vien(const char menu[][30]){
	short chon = 0;
	unsigned char kytu;
	if (menu == menu_dssv){
		if (chon == 0){
			xoaHienThiChucNang();
			HienThiTrang(1, 2, 145, 35);
			ve_bang_sv();
			textcolor(2);
			gotoxy(36,9); cout << (char)16;
			do {
				kytu = getch();
				if (kytu == -32) kytu = getch();
				switch(kytu){
					case UP:
						if (chon % 13 == 0 && chon != 0){
							xoaBang();
							ve_bang_sv();
							gotoxy(36,33); cout << (char)16;
							chon--;
						}
						else if (chon % 13 > 0){
							textcolor(0);
							gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
							chon--;
							textcolor(2);
							gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
						}
						break;
					case DOWN:
						if ((chon + 1) % 13 == 0){
							xoaBang();
							ve_bang_sv();
							gotoxy(36,9); cout << (char)16;
							chon++;
						}
						else if ((chon + 1) % 13 < 13){
							textcolor(0);
							gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
							chon++;
							textcolor(2);
							gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
						}
						break;
					case ENTER:
						xoaBang();
						xoaHienThiChucNang();
						return ve_bang_sv_con(3);
					case ESC:
						xoaBang();
//						xoa_hdsd();
						veMenuPhu(menu_dssv, 3);
						return -1;
				}
			} while (1);
		}
	}
}
////============================================== MON HOC ======================================================

//int sua_va_xoa_mon_hoc(const char menu[][30]){
//	MONHOC mh;
//	unsigned char kytu; int chon = 0;
//	if (menu == menu_dsmh){
//		xoaHienThiChucNang();
//		xoaBang();
//		HienThiTrang(1, 2, 145, 35);
//		veBangMonHoc();
//		textcolor(2);
//			gotoxy(36,9); cout << (char)16;
//			do{
//				kytu = getch();
//				if (kytu == -32) kytu = getch();
//				switch(kytu){
//					case UP:
//						if (chon % 13 == 0 && chon != 0){
//							xoaBang();
//							veBangMonHoc();
//							textcolor(2);
//							gotoxy(36,33); cout << (char)16;
//							chon--;
//						}
//						else if (chon % 13 > 0){
//							textcolor(0);
//							gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
//							chon--;
//							textcolor(2);
//							gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
//						}
//						break;
//					case DOWN:
//						if ((chon + 1) % 13 == 0){
//							xoaBang();
//							veBangMonHoc();
//							textcolor(2);
//							gotoxy(36,9); cout << (char)16;
//							chon++;
//						}
//						else if ((chon + 1) % 13 < 13){
//							textcolor(0);
//							gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
//							chon++;
//							textcolor(2);
//							gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
//						}
//						break;
//					case ENTER:
//						return veBangThemLTC(2);
//					case ESC:
//						xoaBang();
////						xoa_hdsd();
//						veMenuPhu(menu, 1);
//						return -1;
//				}
//			} while (1);
//		}
//}

int in_danh_sach_mon_hoc(const char str[][30]){
	unsigned char kytu; int chon = 0;
	if (str == menu_dsmh){
		xoaHienThiChucNang();
		xoaBang();
		HienThiTrang(1, 2, 145, 35);
		veBangMonHoc();
		textcolor(2);
			gotoxy(36,9); cout << (char)16;
			do{
				kytu = getch();
				if (kytu == -32) kytu = getch();
				switch(kytu){
					case UP:
						if (chon % 13 == 0 && chon != 0){
							xoaBang();
							veBangMonHoc();
							textcolor(2);
							gotoxy(36,33); cout << (char)16;
							chon--;
						}
						else if (chon % 13 > 0){
							textcolor(0);
							gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
							chon--;
							textcolor(2);
							gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
						}
						break;
					case DOWN:
						if ((chon + 1) % 13 == 0){
							xoaBang();
							veBangMonHoc();
							textcolor(2);
							gotoxy(36,9); cout << (char)16;
							chon++;
						}
						else if ((chon + 1) % 13 < 13){
							textcolor(0);
							gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
							chon++;
							textcolor(2);
							gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
						}
						break;
					case ENTER:
						return veBangThemLTC(3);
					case ESC:
						xoaBang();
//						xoa_hdsd();
						veMenuPhu(str, 3);
						return -1;
				}
			} while (1);
		}
}

//=============================================================== DANG KI ====================================================================
int nhap_masv_mamh_nienkhoa(DSLTC dsltc, PTRMH dsmh, DANGKI &svdk, MONHOC &monhoc, LTC *lopTc, PTRSV dssv) {
//	Khung_Nhap_MSV_MMH_NK();
	int x = 34, y = 2;
	int key;
	int vitri = 0;
	PTRSV check_sv; //kiem tra sinh vien
	int check_nk; //kiem tra nien khoa
	PTRSV vitrisv;
	int check_ma_mh, vitri_mamh; //kiem tra ma mon
	char temp[10]; // de chuyen nien khoa thanh char*
	svdk.masv[0] = NULL;
MASV:
	while (1) {
		textcolor(228); gotoxy(30, 3); cout << "                                      ";
		textcolor(14);
		gotoxy(34 + vitri, y);
		key = get_key();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			svdk.masv[vitri] = char(key);
			svdk.masv[vitri] = toupper(svdk.masv[vitri]);
			cout << svdk.masv[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(34 + vitri, y);
			cout << " ";
			gotoxy(34 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			svdk.masv[vitri] = '\0';	//Ngat chuoi~
			for (int i = 0; i < dsltc.soluong; i++){
				check_sv = search_masv(dssv, svdk.masv);
//				vitrisv = Search_MSV(ds.dsl[i].DSSV, sv.mssv); // lay vi tri
				if (check_sv != NULL){
					vitri = strlen(monhoc.mamh);
					gotoxy(49 + vitri, y);
					goto MAMH;
				}
			}
			if (check_sv == NULL){
				ghi_chu("  MA SINH VIEN KHONG TON TAI  ", 30, 4, 79, 500);
			}
		}
		if (key == RIGHT && vitri != 0)
		{
			svdk.masv[vitri] = '\0';	//Ngat chuoi~
			for (int i = 0; i < dsltc.soluong; i++){
				check_sv = search_masv(dssv, svdk.masv);
//				vitrisv = Search_MSV(ds.dsl[i].DSSV, sv.mssv); // lay vi tri
				if (check_sv != NULL){
					vitri = strlen(monhoc.mamh);
					gotoxy(49 + vitri, y);
					goto MAMH;
				}
			}
			if (check_sv == NULL){
				ghi_chu("  MA SINH VIEN KHONG TON TAI  ", 30, 4, 79, 500);
			}
		}
		if (key == ESC) { textcolor(14);	return 0; }
	}
MAMH:
	vitri = 0;
	while (1) {
//		textcolor(228); gotoxy(30, 3); cout << "    Nhan F5 de xem Danh sach mon hoc     ";
		textcolor(14);
		gotoxy(49 + vitri, y);
		key = get_key();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			monhoc.mamh[vitri] = char(key);
			monhoc.mamh[vitri] = toupper(monhoc.mamh[vitri]);
			cout << monhoc.mamh[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(49 + vitri, y);
			cout << " ";
			gotoxy(49 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			monhoc.mamh[vitri] = '\0';	//Ngat chuoi~
			vitri_mamh = kiem_tra_trung_mh(dsmh, monhoc.mamh);
			if (vitri_mamh == 1){
				check_ma_mh = search_ma_mon_hoc(dsltc, monhoc.mamh);
				if (-1 == check_ma_mh) {
					ghi_chu("MON HOC NAY CHUA DUOC MO TRONG LOP TIN CHI", 30, 4, 79, 700);
					gotoxy(49 + vitri, y);
					continue;
				}
				else {
					itoa(lopTc->nienkhoa, temp, 10);
					vitri = strlen(temp);
					gotoxy(64 + vitri, y);
					goto NIENKHOA;
				}
			}
			else {
				ghi_chu("MA MON HOC KHONG TON TAI TRONG DSMH", 30, 4, 79, 700);
				gotoxy(49 + vitri, y);
				continue;
			}
		}
//		if (key == F5)
//		{
//			XemMonHoc(DSLTC, DSMH, 1);
//			Khung_Nhap_MSV_MMH_NK();
//			textcolor(228); gotoxy(18, 24); cout << "              NHAN F5 DE BAT CHUC NANG DI CHUYEN                  ";
//			textcolor(14);
//			mmh.mmh[vitri] = '\0';
//			gotoxy(49, y); cout << mmh.mmh;
//			gotoxy(34, y); cout << sv.mssv;
//		}
		if (key == RIGHT && vitri != 0)
		{
			monhoc.mamh[vitri] = '\0';	//Ngat chuoi~
			vitri_mamh = kiem_tra_trung_mh(dsmh, monhoc.mamh);
			if (vitri_mamh != 0) {
				check_ma_mh = search_ma_mon_hoc(dsltc, monhoc.mamh);
				if (-1 == check_ma_mh) {
					ghi_chu("     MON HOC NAY CHUA DUOC MO LOP    ", 30, 4, 79, 700);
					gotoxy(49 + vitri, y);
					continue;
				}
				else {
					itoa(lopTc->nienkhoa, temp, 10);
					vitri = strlen(temp);
					gotoxy(64 + vitri, y);
					goto NIENKHOA;
				}
			}
			else {
				ghi_chu("       MA MON HOC KHONG TON TAI     ", 30, 4, 79, 700);
				gotoxy(49 + vitri, y);
				continue;
			}
		}
		if (key == LEFT) {
			monhoc.mamh[vitri] = '\0';
			vitri = strlen(svdk.masv);
			gotoxy(34 + vitri, y);
			goto MASV;
		}
		if (key == ESC) { textcolor(14);	return 0; }
	}
NIENKHOA:
	vitri = 0;
	while (1) {
		textcolor(228); gotoxy(30, 3); cout << "    Nhan F5 de xem Danh sach Lop tin chi   ";
		textcolor(14);
		gotoxy(64 + vitri, y);
		key = get_key();
		if ( (key <= '9' && key >= '0') && (vitri < 4))
		{
			temp[vitri] = char(key);
			temp[vitri] = toupper(temp[vitri]);
			cout << temp[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(64 + vitri, y);
			cout << " ";
			gotoxy(64 + vitri, y);
		}
		if (key == ENTER && vitri == 4) {
			temp[vitri] = '\0';
			lopTc->nienkhoa = atoi(temp);
			if (lopTc->nienkhoa >= 2017 && lopTc->nienkhoa <= 2021){
				check_nk = search_dsltc_mamh_nienkhoa(dsltc, monhoc.mamh, lopTc->nienkhoa);
				if (check_nk == 1) {
					ghi_chu("        DANG NHAP THANH CONG       ", 30, 4, 79, 700);
					system("cls");
					return 1;
				}
				else {
					ghi_chu("KHONG TON TAI LOP HOC CO NIEN KHOA NAY", 30, 4, 79, 700);
					gotoxy(64 + vitri, y);
				}
			}
			else {
				ghi_chu("              NAM KHONG HOP LE               ", 30, 4, 79, 700);
				gotoxy(64 + vitri, y);
				continue;
			}
		}
		else {
			if (key == ENTER && vitri != 4) {
				ghi_chu("     NIEN KHOA PHAI DAY DU 4 KI TU!   ", 30, 4, 79, 700);
				gotoxy(64 + vitri, y);
				continue;
			}
		}
		if (key == LEFT) {
			temp[vitri] = '\0';
			lopTc->nienkhoa = atoi(temp);
			vitri = strlen(monhoc.mamh);
			gotoxy(49 + vitri, y);
			goto MAMH;
		}
//		if (key == F5)
//		{
//			XemDSLTC(DSLTC, DSMH, 1);
//			Khung_Nhap_MSV_MMH_NK();
//			textcolor(228); gotoxy(18, 24); cout << "              NHAN F5 DE BAT CHUC NANG DI CHUYEN                  ";
//			textcolor(14);
//			lopTc.nienkhoa[vitri] = '\0';
//			gotoxy(64, y); cout << lopTc.nienkhoa;
//			gotoxy(49, y); cout << mmh.mmh;
//			gotoxy(34, y); cout << sv.mssv;
//		}
		if (key == ESC) { textcolor(14);	return 0; }
	}
}

int dangki_ltc(DSLTC &dsltc, PTRMH dsmh, PTRSV dssv){
	int key;
	int x = 34, y = 2;
	int dem, trang = 0, tongtrang = 0;
	int kiemtraESC;
	int solop; //dem so lop thoa man
	int vitrilop;
	DANGKI svdk; MONHOC monhoc; LTC *lopTc;
	svdk.masv[0] = NULL; monhoc.mamh[0] = NULL; lopTc->nienkhoa = 0;
	kiemtraESC = nhap_masv_mamh_nienkhoa(dsltc, dsmh, svdk, monhoc, lopTc, dssv);
	if (0 == kiemtraESC){
		return 0; // qua trinh dang nhap dung lai se tra ve 0l
	}
	solop = dem_so_lop_da_dang_ki(dsltc, monhoc.mamh);
	if (solop == 0)
	{
		ghi_chu("Lop Chua Duoc Mo", 35, 27, 79, 500); // truong hop chac khong bao gio xay ra
	}
	textcolor(14);	system("cls");	 //Khung_DKLTC();
	gotoxy(93, 4);
//	Khung_DKLTC();
	char temp[11]; // de doi tu` int sang char
	int vitri = 0;
	int quyetdinh, test = 0;
	int i;
MALOPTC:
	while (1){
		textcolor(14);
		veBangLopTinChi();
//		cout << "\nNhap ma lop tc:"; // 2 dong` cout dung` de test loi~ sai
		dem = 0;
		for (i = 0; i < dsltc.soluong; i++){
			if (strcmp(dsltc.ds_ltc[i]->mamh, monhoc.mamh) == 0) {
				if (dsltc.ds_ltc[i]->nienkhoa == lopTc->nienkhoa){
//			cout << "\t\tChay dc";
					textcolor(12); gotoxy(6, 8 + dem); cout << (dem + 1);
					textcolor(14);
					gotoxy(10, 8 + dem); cout << dsltc.ds_ltc[i]->maloptc;
					gotoxy(24, 8 + dem); cout << dsltc.ds_ltc[i]->mamh;
					gotoxy(41, 8 + dem); cout << dsltc.ds_ltc[i]->nienkhoa;
					gotoxy(56, 8 + dem); cout << dsltc.ds_ltc[i]->hocki;
					gotoxy(65, 8 + dem); cout << dsltc.ds_ltc[i]->nhom;
					gotoxy(73, 8 + dem); cout << dsltc.ds_ltc[i]->sosvmax;
					dem++;
				}
			}
		}
		textcolor(14);
		gotoxy(93 + vitri, 4);
		key = get_key();
		if ((key >= '0' && key <= '9') && (vitri < 10)){
			temp[vitri] = char(key);
			temp[vitri] = toupper(temp[vitri]);
			cout << temp[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			temp[vitri] = '\0';
			lopTc->maloptc = atoi(temp);
			vitrilop = search_maloptc_mamh(dsltc, lopTc->maloptc, monhoc.mamh, dsltc.soluong);
			if (vitrilop == -1){
				ghi_chu("MA LOP KHONG DUNG!", 93, 15, 79, 500);
				test = test + 10; // no bi cai loi cu l gi o dong` nay, bo di thi lai chay sai ?
				continue;
			}
			else {
				// quyet dinh de hoi user co muon dang ki
				quyetdinh = 1;
				if (-1 == quyetdinh) {
					textcolor(14);
					gotoxy(85, 22); cout << "                                 ";
					gotoxy(85, 23); cout << "                                 ";
					gotoxy(85, 24); cout << "                                 ";
					gotoxy(85, 25); cout << "                                 ";
					gotoxy(85, 26); cout << "                                 ";
					continue;
				}
				if (1 == quyetdinh){
					textcolor(14);
					gotoxy(85, 22); cout << "                                 ";
					gotoxy(85, 23); cout << "                                 ";
					gotoxy(85, 24); cout << "                                 ";
					gotoxy(85, 25); cout << "                                 ";
					gotoxy(85, 26); cout << "                                 ";
					for (int j = 0; j < dsltc.soluong; j++){
						if (strcmp(dsltc.ds_ltc[j]->mamh, monhoc.mamh) == 0){
							if (search_svdk_ltc(dsltc.ds_ltc[j]->head, svdk.masv) != NULL) {
								ghi_chu("SINH VIEN DA DANG KI LOP! KHONG DUOC DANG KI TIEP", 35, 15, 79, 2000);
								gotoxy(93 + vitri, 4); goto MALOPTC;
							}
						}
					}
					ghi_chu("DANG KI THANH CONG", 93, 15, 79, 1000);
					them_cuoi_nodedk(dsltc.ds_ltc[vitrilop]->head, tao_node_svdk(svdk));
					return 1;
				}
				if (0 == quyetdinh) {
					textcolor(14);
					gotoxy(85, 22); cout << "                                 ";
					gotoxy(85, 23); cout << "                                 ";
					gotoxy(85, 24); cout << "                                 ";
					gotoxy(85, 25); cout << "                                 ";
					gotoxy(85, 26); cout << "                                 ";
					continue;
				}
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoxy(93 + vitri, 4);
			cout << " ";
			gotoxy(93 + vitri, 4);
		}
		if (key == RIGHT || key == LEFT || key == UP || key == DOWN) { continue; }
		if (key == ESC){
			// hoi user co chac chan muon dang ki
//				if (temp == 1) {
//					ghi_chu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
//					ghi_file_dsltc(dsltc);
//				}
//				if (temp == 0) { ghi_chu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000); }
//			}
			system("cls");
			return 0;
		}
	}
}

int ve_bang_diem(){
	xoaBang();
//	xoa_hdsd();
	textcolor(15);
	VeKhung(60, 10, 120, 28, 0, 0, 0, 0, 0, 0);
	gotoxy(3,28); cout << "ESC: thoat";
	SetBGColor(2);
	textcolor(15);
	gotoxy(94, 4); cout << "MON HOC: ......";
	gotoxy(88, 5);	cout << "Nien Khoa: ...";
	gotoxy(100, 5);	cout << "Hoc Ki: ....";
	gotoxy(110, 5);	cout << "Nhom: ...";
	SetBGColor(0);
	VeKhung(40, 6, 165, 34, 63, 109, 140, 0, 0, 0);
	gotoxy(57,7);	cout << "MA MON HOC";
	gotoxy(85,7);	cout << "HO";
	gotoxy(135,7);	cout << "TEN";
	gotoxy(151,7);	cout << "DIEM";
	unsigned char kytu;
	do{
		kytu = getch();
		if (kytu == 0) kytu = getch();
		switch(kytu){
			case F1:
				return bang_diem_mon_hoc(menu_dangki);
			case F2:
				return 0;
			default: break;
		}
	} while (1);
}

int bang_diem_mon_hoc(const char menu[][30]){
	short chon = 0;
	unsigned char kytu;
	if (menu == menu_dangki){
		if (chon == 0){
			xoaBang();
			SetBGColor(0);
			gotoxy(3,26); cout << "ENTER: xem diem";
			gotoxy(3,27); cout << "ESC: thoat";
			veBangLopTinChi();
			textcolor(2);
			gotoxy(36,9); cout << (char)16;
			do{
				kytu = getch();
				if (kytu == -32) kytu = getch();
				switch(kytu){
					case UP:
						if (chon % 13 == 0 && chon != 0){
							xoaBang();
							veBangLopTinChi();
							textcolor(2);
							gotoxy(36,33); cout << (char)16;
							chon--;
						}
						else if (chon % 13 > 0){
							textcolor(0);
							gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
							chon--;
							textcolor(2);
							gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
						}
						break;
					case DOWN:
						if ((chon + 1) % 13 == 0){
							xoaBang();
							veBangLopTinChi();
							textcolor(2);
							gotoxy(36,9); cout << (char)16;
							chon++;
						}
						else if ((chon + 1) % 13 < 13){
							textcolor(0);
							gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
							chon++;
							textcolor(2);
							gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
						}
						break;
					case F1: // Sua
						return veBangSuaXoaLTC(1);
					case F2: // Xoa
						return 0;
					case ESC:
						xoaBang();
//						xoa_hdsd();
						veMenuPhu(menu, 1);
						return -1;
				}
			} while (1);
		}
	}
}

int diem_trung_binh(const char menu[][30]){
	short chon = 0;
	unsigned char kytu;
	if (menu == menu_dangki){
		xoaHienThiChucNang();
		HienThiTrang(1, 2, 145, 35);
		ve_bang_sv();
		textcolor(2);
		gotoxy(36,9); cout << (char)16;
		do{
			kytu = getch();
			if (kytu == -32) kytu = getch();
			switch(kytu){
				case UP:
					if (chon % 13 == 0 && chon != 0){
						xoaBang();
						ve_bang_sv();
						textcolor(2);
						gotoxy(36,33); cout << (char)16;
						chon--;
					}
					else if (chon % 13 > 0){
						textcolor(0);
						gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
						chon--;
						textcolor(2);
						gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
					}
					break;
				case DOWN:
					if ((chon + 1) % 13 == 0){
						xoaBang();
						ve_bang_sv();
						textcolor(2);
						gotoxy(36,9); cout << (char)16;
						chon++;
					}
					else if ((chon + 1) % 13 < 13){
						textcolor(0);
						gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
						chon++;
						textcolor(2);
						gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
					}
					break;
				case ENTER:
					xoaBang();
					xoaHienThiChucNang();
					return ve_bang_sv_con(4);
				case ESC:
					xoaBang();
//						xoa_hdsd();
					veMenuPhu(menu, 2);
					return -1;
			}
		} while (1);
	}
}

int diem_tong_ket(const char menu[][30]){
	short chon = 0;
	unsigned char kytu;
	if (menu == menu_dangki){
		xoaHienThiChucNang();
		HienThiTrang(1, 2, 145, 35);
		ve_bang_sv();
		textcolor(2);
		gotoxy(36,9); cout << (char)16;
		do{
			kytu = getch();
			if (kytu == -32) kytu = getch();
			switch(kytu){
				case UP:
					if (chon % 13 == 0 && chon != 0){
						xoaBang();
						ve_bang_sv();
						textcolor(2);
						gotoxy(36,33); cout << (char)16;
						chon--;
					}
					else if (chon % 13 > 0){
						textcolor(0);
						gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
						chon--;
						textcolor(2);
						gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
					}
					break;
				case DOWN:
					if ((chon + 1) % 13 == 0){
						xoaBang();
						ve_bang_sv();
						textcolor(2);
						gotoxy(36,9); cout << (char)16;
						chon++;
					}
					else if ((chon + 1) % 13 < 13){
						textcolor(0);
						gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
						chon++;
						textcolor(2);
						gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
					}
					break;
				case ENTER:
					xoaBang();
					xoaHienThiChucNang();
					return ve_bang_sv_con(5);
				case ESC:
					xoaBang();
//					xoa_hdsd();
					veMenuPhu(menu, 3);
					return -1;
			}
		} while (1);
	}
}
