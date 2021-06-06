#include "Console.h"


int main(){
	PTRSV dssv = NULL;
	DSLTC dsltc;
	PTRMH t;
	khoi_tao_cay(t);
	doc_file_mh(t);
	doc_file_dsltc(dsltc);
	doc_file_sv(dssv);
//	MONHOC* mang[100];
//	unsigned short sl = 0, check = 1, chon = 0;
//	do_dsmh_ra_mang(t, mang, sl);
//	xuat_mang_dsltc(dsltc, mang, sl, check, chon);
	
//	cout << "\n\n\t\t\tDANH SACH SV DANG KI";
//	for (int i = 0; i < dsltc.soluong; i++){
//		cout << "\nMA LTC: " << dsltc.ds_ltc[i]->maloptc << endl;
//		xuat_dssvdk(dsltc.ds_ltc[i]->head);
//		cout << endl << endl << endl;
//	}

//	cout << "\n\n\t\tDANH SACH LTC";
//	xuatds_ltc(dsltc);
//	cout << endl << endl;
//	cap_nhat_dsltc(dsltc);
//	cout << "\n\n\t\tDANH SACH LTC sau khi chinh sua";
//	xuatds_ltc(dsltc);
	

//	xuly_dsltc(dsltc, t);

	dangki_ltc(dsltc, t, dssv);




//	cout << "\n\n\t\t Sau Khi Xoa";
//	xoa_ltc(dsltc, ltc, 0);
//	xuatds_ltc(dsltc);
	

//	unsigned short nk, hk;
//	dang_ki_ltc(dsltc, dssv, t, nk, hk);

//	for (short i = 0; i < dsltc.soluong; i++){
//		if (dsltc.ds_ltc[i]->nienkhoa == nk && dsltc.ds_ltc[i]->hocki == hk){
//			if (kiem_tra_trung_ma_hoc(t, dsltc.ds_ltc[i]->mamh) != NULL){
//				cout << "\n\n\t\tMa lop tin chi thu " << dsltc.ds_ltc[i]->maloptc << endl << endl;
//				xuat_dssvdk(dsltc.ds_ltc[i]->head);
//				cout << endl;
//			}
//		}
//	}

//	auto_huy_ltc(dsltc, nk, hk);
	

	system("pause");













//	clreol();
//	SetUpConsole();
//	VeKhungGiaoDien();
//	HDSD();
//	ThongBaoMenu();
//	themLopTinChi(menu_dsltc);
//	suaVaXoaLopTinChi(menu_dsltc, dsltc, mang, sl);
//	timMaLopTinChi(menu_dsltc, dsltc);
//	veMenuChinh(0);
//color: 244 252 253

//	textcolor(15);
//	inDssvLopTinChi(menu_dsltc, dsltc, mang, sl);
//for (int i = 0; i < 256; i++){
//	cout << "\ni " << i << " la:"<<(char) i;
//}
//cout << (char) 16;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	gotoxy(50,38);
	return 0;
}

