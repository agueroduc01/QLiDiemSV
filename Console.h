#include "DocGhiFileDoAn.h"
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27
#define F1 59
#define F2 60
#define F3 61
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
"4. DANH SACH DIEM"};
const char menu_dsltc[4][30] = {" Them Lop Tin Chi ",
" Sua Va Xoa Lop Tin Chi ",
" Tim Kiem Lop Tin Chi ",
" Danh Sach Lop Tin Chi "};
const char menu_dssv[4][30] = {"  Them Sinh Vien   ",
" Sua Va Xoa Sinh Vien  ", 
" Tim Kiem Sinh Vien ",
" Danh Sach Sinh Vien "};
const char menu_dsmh[4][30] = {"  Them Mon Hoc   " ,
" Sua Va Xoa Mon Hoc ",
" Dang Ky Mon Hoc ",
" Danh Sach Mon Hoc "};
const char menu_diem[4][30] = {" Nhap Diem Lop Tin Chi ",
"  Bang Diem Mon Hoc ",
" Diem Trung Binh  ",
" Diem Tong Ket "};
int veMenuChinh(short chon);
int veMenuPhu(const char menu[][30], short chon);
// LOP TIN CHI
int themLopTinChi(const char menu[][30]);//
int veBangSuaXoaLTC(short check);
int inDssvDangKy();
int suaVaXoaLopTinChi(const char menu[][30]);//
int suaVaXoaLopTinChi(const char menu[][30], DSLTC dsltc, MONHOC** mang, unsigned short &soluong);
int timMaLopTinChi(const char menu[][30]);
int inDssvLopTinChi(const char menu[][30]);
void veBangMonHoc();
int veBangThemLTC(short check);
int veBangThemLTC(short check, MONHOC** mang, unsigned short soluong);
void veBangLopTinChi();
void inNhapMaLopTinChi();
//SINH VIEN
int them_sinh_vien(const char menu[][30]);
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
				return veMenuPhu(menu_diem, chon);
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
		case ENTER:
			if (menu == menu_dsltc){ // Chuc nang lop tin chi
				if (chon == 0) return themLopTinChi(menu);
				else if (chon == 1) return suaVaXoaLopTinChi(menu);
				else if (chon == 2) return timMaLopTinChi(menu); // Bo sung
				else if (chon == 3) return inDssvLopTinChi(menu);
			}
			else if (menu == menu_dssv){
				if (chon == 0)	return them_sinh_vien(menu);
				else if (chon == 1)	return sua_va_xoa_sinh_vien(menu);
				else if (chon == 2) return tim_ma_sinh_vien(menu); // Bo sung
				else if (chon == 3) return in_danh_sach_sinh_vien(menu);
			}
//			else if (menu == menu_dsmh){
//				if (chon == 0)	return them_mon_hoc(menu, dsmh);
//				else if (chon == 1)	return sua_va_xoa_mon_hoc(menu);
//				else if (chon == 2) return dang_ky(menu); // Bo sung
//				else if (chon == 3) return in_danh_sach_mon_hoc(menu);
//			}
			else if (menu == menu_diem){
				if (chon == 0)	return nhap_diem_lop_tin_chi(menu);
				else if (chon == 1)	return bang_diem_mon_hoc(menu);
				else if (chon == 2) return diem_trung_binh(menu); // Bo sung
				else if (chon == 3) return diem_tong_ket(menu);
			}
			break;
		case ESC:
			xoa_menu();
			if (menu == menu_dsltc) return veMenuChinh(0);
			else if (menu == menu_dssv) return veMenuChinh(1);
			else if (menu == menu_dsmh) return veMenuChinh(2);
			else if (menu == menu_diem) return veMenuChinh(3);
		}
	} while (1);
}
//==================================================== Menu ===============================================
//========================================== LTC ==========================================
int themLopTinChi(const char menu[][30]){
	unsigned short chon = 0, kytu, checktrang = 1;
	if (menu == menu_dsltc){
		xoaHienThiChucNang();
		xoaBang();
		HienThiTrang(1, 2, 145, 35);
		veBangMonHoc();
//		xuat_mang_mon_hoc(mang, soluong, checktrang, chon);
		textcolor(2);
		gotoxy(36, 9);	cout << (char)16;
		do{
			kytu = getch();
			if (kytu == -32) kytu = getch();
			switch(kytu){
				case UP:
					if (chon % 13 == 0 && chon != 0){
						xoaBang();
						veBangMonHoc();
						textcolor(15);
						checktrang--;
//						xuat_mang_mon_hoc(mang, soluong, checktrang, chon);
						textcolor(2);
						gotoxy(36,33); cout << (char)16;
						chon--;
					}
					else if (chon % 13 > 0){	// len bth
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
						textcolor(15);
						checktrang++;
//						xuat_mang_mon_hoc(mang, soluong, checktrang, chon);
						textcolor(2);
						gotoxy(36,9); cout << (char)16;
						chon++;
					}
					else if ((chon + 1) % 13 < 13){ // xuong bth
						textcolor(0);
						gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
						chon++;
						textcolor(2);
						gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
					}
					break;
				case ENTER:
					return veBangThemLTC(0);
				case ESC:
					xoaBang();
		//			xoa_hdsd();
					veMenuPhu(menu, 0);
					return -1;
			}
		} while (1);
	}
}
//test
//int themLopTinChi(const char menu[][30], MONHOC* mang[], unsigned short &soluong){
//	unsigned short chon = 0, kytu, checktrang = 1;
//	if (menu == menu_dsltc){
//		xoaHienThiChucNang();
//		xoaBang();
//		HienThiTrang(1, 2, 145, 35);
//		veBangMonHoc();
//		xuat_mang_mon_hoc(mang, soluong, checktrang, chon);
//		textcolor(2);
//		gotoxy(36, 9);	cout << (char)16;
//		do{
//			kytu = getch();
//			if (kytu == -32) kytu = getch();
//			switch(kytu){
//				case UP:
//					if (chon % 13 == 0 && chon != 0){
//						xoaBang();
//						veBangMonHoc();
//						textcolor(15);
//						checktrang--;
//						xuat_mang_mon_hoc(mang, soluong, checktrang, chon);
//						textcolor(2);
//						gotoxy(36,33); cout << (char)16;
//						chon--;
//					}
//					else if (chon % 13 > 0){	// len bth
//						textcolor(0);
//						gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
//						chon--;
//						textcolor(2);
//						gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
//					}
//					break;
//				case DOWN:
//					if ((chon + 1) % 13 == 0){
//						xoaBang();
//						veBangMonHoc();
//						textcolor(15);
//						checktrang++;
//						xuat_mang_mon_hoc(mang, soluong, checktrang, chon);
//						textcolor(2);
//						gotoxy(36,9); cout << (char)16;
//						chon++;
//					}
//					else if ((chon + 1) % 13 < 13){ // xuong bth
//						textcolor(0);
//						gotoxy(36,9 + (chon % 13) * 2); cout << ' ';
//						chon++;
//						textcolor(2);
//						gotoxy(36,9 + (chon % 13) * 2); cout << (char)16;
//					}
//					break;
//				case ENTER:
//					return veBangThemLTC(0, mang, soluong);
//				case ESC:
//					xoaBang();
//		//			xoa_hdsd();
//					veMenuPhu(menu, 0);
//					return -1;
//			}
//		} while (1);
//	}
//}

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
				return themLopTinChi(menu_dsltc);
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

int suaVaXoaLopTinChi(const char menu[][30]){
	unsigned short chon = 0;
	unsigned char kytu;
	if (menu == menu_dsltc){
		if (chon == 0){
			xoaBang();
			SetBGColor(0);
			gotoxy(3,27); cout << "F1: Sua lop tin chi";
			gotoxy(3,28); cout << "F2: Xoa lop tin chi";
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
						return veBangSuaXoaLTC(0);
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

//test
//int suaVaXoaLopTinChi(const char menu[][30], DSLTC dsltc, MONHOC** mang, unsigned short &soluong){
//	unsigned short chon = 0, checktrang = 1;
//	unsigned char kytu;
//	if (menu == menu_dsltc){
//		if (chon == 0){
//			xoaBang();
//			SetBGColor(0);
//			gotoxy(3,27); cout << "F1: Sua lop tin chi";
//			gotoxy(3,28); cout << "F2: Xoa lop tin chi";
//			veBangLopTinChi();
//			xuat_mang_dsltc(dsltc, mang, soluong, checktrang, chon);
//			textcolor(2);
//			gotoxy(36,9); cout << (char)16;
//			do{
//				kytu = getch();
//				if (kytu == -32) kytu = getch();
//				switch(kytu){
//					case UP:
//						if (chon % 13 == 0 && chon != 0){
//							xoaBang();
//							veBangLopTinChi();
//							checktrang--;
//							xuat_mang_dsltc(dsltc, mang, soluong, checktrang, chon);
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
//							veBangLopTinChi();
//							checktrang++;
//							xuat_mang_dsltc(dsltc, mang, soluong, checktrang, chon);
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
//					case F1: // Sua
//						return veBangSuaXoaLTC(0);
//					case F2: // Xoa
//						return 0;
//					case ESC:
//						xoaBang();
////						xoa_hdsd();
//						veMenuPhu(menu, 1);
//						return -1;
//				}
//			} while (1);
//		}
//	}
//}

void veBangLopTinChi(){
	SetBGColor(2);
	textcolor(15);
	gotoxy(88, 4); cout << "DANH SACH LOP TIN CHI";
	SetBGColor(0);
	VeKhung(40, 6, 165, 34, 49, 63, 112, 124, 0, 0);
	gotoxy(42,7);	cout << "MA LOP";
	gotoxy(51,7);	cout << "MA MON HOC";
	gotoxy(80,7);	cout << "TEN MON HOC";
	gotoxy(113,7);	cout << "NIEN KHOA";
	gotoxy(125,7);	cout << "HOC KI";
	gotoxy(135,7);	cout << "NHOM";
	gotoxy(145,7);	cout << "SV TOI DA";
	gotoxy(158,7);	cout << "CON LAI";
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
				return suaVaXoaLopTinChi(menu_dsltc);
				else if (check == 1){
					xoaBang();
					return nhap_diem_lop_tin_chi(menu_diem);
				}
//			case F2:
//				return ve_bang_diem();
			default: break;
		}
	} while (1);
}

int timMaLopTinChi(const char menu[][30]){
	short chon = 0;
	unsigned char kytu;
	if (menu == menu_dsltc){
		xoaHienThiChucNang();
		do {
			VeKhung(65, 15, 115, 17, 0, 0, 0, 0, 0, 0);// ve khung nhap ma lop tin chi
			//nhap ma lop tin chi
			//kiem tra ltc co trong dsltc
			//co thi xuat ra thong tin ltc do'
			xoaBangCon();
			VeKhung(60, 10, 120, 28, 0, 0, 0, 0, 0, 0);// xuat ra thong tin ltc
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

//test
int timMaLopTinChi(const char menu[][30], DSLTC dsltc){
	unsigned char kytu;
	unsigned short maltccheck;
	if (menu == menu_dsltc){
		xoaHienThiChucNang();
		textcolor(15);
		VeKhung(65, 15, 115, 17, 0, 0, 0, 0, 0, 0);// ve khung nhap ma lop tin chi
		do {
			//nhap ma lop tin chi
			gotoxy(73, 15);
			nhap_so(maltccheck, 7);
			//kiem tra ltc co trong dsltc
			//co thi xuat ra thong tin ltc do'
			if (check_trung_maltc(dsltc, maltccheck) == 1){
				xoaBangCon();
				textcolor(15);
				VeKhung(60, 10, 120, 28, 0, 0, 0, 0, 0, 0);// xuat ra thong tin ltc
				xuat_ltc(dsltc.ds_ltc[maltccheck - 1]);
			}
			//else xuat thong bao khong tim thay
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
//test
//int inDssvLopTinChi(const char menu[][30], DSLTC dsltc, MONHOC *mang[], unsigned short soluong){
//	unsigned char kytu;
//	unsigned short chon = 0, checktrang = 1;
//	if (menu == menu_dsltc){
//		if (chon == 0){
//			xoaHienThiChucNang();
//			veBangLopTinChi();
//			xuat_mang_dsltc(dsltc, mang, soluong, checktrang, chon);
//			textcolor(2);
//			gotoxy(36,9); cout << (char)16;
//			do {
//				kytu = getch();
//				if (kytu == -32) kytu = getch();
//				switch(kytu){
//					case UP:
//						if (chon % 13 == 0 && chon != 0){
//							xoaBang();
//							veBangLopTinChi();
//							checktrang--;
//							xuat_mang_dsltc(dsltc, mang, soluong, checktrang, chon);
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
//							veBangLopTinChi();
//							checktrang++;
//							xuat_mang_dsltc(dsltc, mang, soluong, checktrang, chon);
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
//						xoaBang();
//						xoaHienThiChucNang();
//						return inDssvDangKy();
//					case ESC:
//						xoaBang();
////						xoa_hdsd();
//						veMenuPhu(menu_dsltc, 3);
//						return -1;
//				}
//			} while (1);
//		}
//	}
//}

int inDssvLopTinChi(const char menu[][30]){
	short chon = 0;
	unsigned char kytu;
	if (menu == menu_dsltc){
		if (chon == 0){
			xoaHienThiChucNang();
			veBangLopTinChi();
			textcolor(2);
			gotoxy(36,9); cout << (char)16;
			do {
				kytu = getch();
				if (kytu == -32) kytu = getch();
				switch(kytu){
					case UP:
						if (chon % 13 == 0 && chon != 0){
							xoaBang();
							veBangLopTinChi();
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
						return inDssvDangKy();
					case ESC:
						xoaBang();
//						xoa_hdsd();
						veMenuPhu(menu_dsltc, 3);
						return -1;
				}
			} while (1);
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
				return inDssvLopTinChi(menu_dsltc);
		}
	} while (1);
}

//============================================= SINH VIEN ==========================================
int them_sinh_vien(const char menu[][30]){
	short chon = 0;
	unsigned char kytu;
	if (menu == menu_dssv){
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
					return ve_bang_sv_con(0);
				case ESC:
					xoaBang();
//						xoa_hdsd();
					veMenuPhu(menu, 0);
					return -1;
			}
		} while (1);
	}
}

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
					return them_sinh_vien(menu_dssv);
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
					return diem_trung_binh(menu_diem);
				}
				else if (check == 5){
					xoaBang();
					return diem_tong_ket(menu_diem);
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
int them_mon_hoc(const char menu[][30], PTRMH &dsmh){
	unsigned short chon = 0;
	MONHOC mh;
	unsigned char kytu;
	if (menu == menu_dsmh){
		do {
			xoaHienThiChucNang();
			textcolor(244);
			VeKhung(65, 15, 115, 17, 0, 0, 0, 0, 0, 0); // ve khung nhap mon hoc
			gotoxy(70, 23);	cout << "NHAP MA MON HOC:";
			gotoxy(90, 23);	nhap_sovachu(mh.mamh, 11);
			if (kiem_tra_trung_mh(dsmh, mh.mamh) == 1){	//trung
				ghi_chu("Mon hoc nay da ton tai. Vui long nhap lai!", 4,30,3,1000);
				continue;
			}
			//nhap ten mon hoc
			gotoxy(70, 25);	cout << "NHAP TEN MON HOC:";
			gotoxy(90, 25);nhap_chu(mh.tenmh, 50);
			gotoxy(70, 27);	cout << "NHAP STCLT:";
			gotoxy(90, 27);nhap_so(mh.stclt, 2);
			gotoxy(70, 27);	cout << "NHAP STCTH:";
			gotoxy(90, 27);nhap_so(mh.stcth, 2);
//			xoaBangCon();
			kytu = getch();
			if (kytu == 0) kytu = getch();
			switch(kytu){
				case ENTER:
					them_node_mh(dsmh, mh);
					ghi_chu("Them thanh cong!", 4,30,7,1000);
					return veMenuPhu(menu, 0);
				case ESC:
				xoaBang();
				return veMenuPhu(menu, 0);
			}
		} while (1);
	}
}

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

int dang_ky(const char menu[][30]){
	short chon = 0;
	unsigned char kytu;
	if (menu == menu_dsmh){
		do {
			xoaHienThiChucNang();
			textcolor(244);
			VeKhung(75, 19, 115, 21, 0, 0, 0, 0, 0, 0); // ve khung nhap ma sinh vien dang ki
			//nhap ma sinh vien dang ki
			// kiem tra
//			xoaBangCon();
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

//=============================================== DIEM =======================================================
int nhap_diem_lop_tin_chi(const char menu[][30]){
	short chon = 0;
	unsigned char kytu;
	if (menu == menu_diem){
		if (chon == 0){
			xoaBang();
			SetBGColor(0);
			gotoxy(3,26); cout << "ENTER: nhap diem";
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
						veMenuPhu(menu, 0);
						return -1;
				}
			} while (1);
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
				return bang_diem_mon_hoc(menu_diem);
			case F2:
				return 0;
			default: break;
		}
	} while (1);
}

int bang_diem_mon_hoc(const char menu[][30]){
	short chon = 0;
	unsigned char kytu;
	if (menu == menu_diem){
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
	if (menu == menu_diem){
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
	if (menu == menu_diem){
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
