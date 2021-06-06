#include "CauTruc.h"
#include "DoHoa.h"

using namespace std;
//======================= nguyen mau ham =====================================
void them_cuoi_sv(PTRSV &head,NODESV *sv);
NODEDANGKI* search_sv_ltc(DSLTC &dsltc, char *c);
NODESV* search_masv(PTRSV head, char *masv_timkiem);
void xoa_dau_sv(PTRSV &head);
void xoa_giua_sv(PTRSV &head, char *c);
void xoa_cuoi_sv(PTRSV &head);
void xuat_thong_tin_sv(SINHVIEN sv);
void xuat_dssv(PTRSV head);
void kt_huyltc(LTC *ltc);
unsigned short full_ltc(DSLTC dsltc);
unsigned short empty_ltc(DSLTC dsltc);
void xuat_ltc(LTC *ltc);
void xuatds_ltc(DSLTC dsltc);
void them_ltc(DSLTC &dsltc);
void xoa_ltc(DSLTC &dsltc, int vitricanxoa);
int search_maltc(DSLTC &dsltc, int malopTc);
void mo_loptc(DSLTC &dsltc, LTC *ltc);
unsigned short dem_sv(PTRSV head);
unsigned short dem_svdk(LTC *ltc);
void dang_ki_ltc(DSLTC &dsltc, PTRSV dssv, PTRMH t, unsigned short &nk, unsigned short &hk);
void them_cuoi_nodedk(PTRDK &head, NODEDANGKI *p);
void auto_huy_ltc(DSLTC &dsltc, short nk, short hk);
void xuat_dssvdk(PTRDK head);
NODEDANGKI *tao_node_svdk(DANGKI svdk);
int kiem_tra_trung_mh(PTRMH dsmh, char mmh[]);
PTRMH kiem_tra_trung_ma_hoc(PTRMH dsmh, char mmh[]);

//================= DSSV ================
//========= tao nodesv =========
NODESV *tao_nodesv(SINHVIEN sv){
	NODESV *p = new NODESV;
	p->data = sv;
	p->pnext = NULL;
	return p;
}
//================= nhap thong tin sv ===========
void nhap_thong_tin_sv(SINHVIEN &sv){
	cout << "\nNhap ma sinh vien(toi da 15 ky tu): ";
//	nhap_sovachu(sv.masv, 16);
	cout << "\nNhap ho sv(toi da 30 ky tu): ";
//	nhap_chu_hoten(sv.ho, 30);
	cout << "\nNhap ten sv(toi da 10 ky tu): ";
//	nhap_chu(sv.ten, 11);
	cout << "\nNhap gioi tinh sv(toi da 3 ky tu): ";
//	nhap_chu(sv.phai, 4);
	cout << "\nNhap sdt sv(toi da 11 ky tu): ";
//	nhap_so(sv.sdt, 12);
	cout << "\nNhap ma lop(toi da 15 ky tu): ";
//	nhap_sovachu(sv.malop, 16);
	cout << endl;
}
void nhap_va_them_1sv_vao_dssv(PTRSV &dssv){
	SINHVIEN sv;
	rewind(stdin);
	nhap_thong_tin_sv(sv);
	NODESV *nodesv = tao_nodesv(sv);
	them_cuoi_sv(dssv, nodesv);
}
//========== xuat thong tin sv =============
void xuat_thong_tin_sv(SINHVIEN sv){
	cout << "\nHo ten sv: " << sv.ho << " " << sv.ten;
	cout << "\nMa sv: " << sv.masv;
	cout << "\nMa lop: " << sv.malop;
	cout << "\nSo dien thoai: " << sv.sdt;
	cout << "\nGioi tinh: " << sv.phai;
}
void xuat_dssv(PTRSV head){
	if (head == NULL){
		cout << "\nDSSV rong khong the xuat !";
		system("pause");
		return;
	}
	for (; head != NULL; head = head->pnext){
		xuat_thong_tin_sv(head->data);
		cout << endl;
	}
}

//============them sinh vien==========
void them_cuoi_sv(PTRSV &head,NODESV *sv){
	if(head == NULL){
		head = sv;
	}else{
		sv->pnext = head;
		head = sv;
	}
}
// tim ma sinh vien trong ds sinh vien
NODESV* search_masv(PTRSV head, char *masv_timkiem){
	if (head == NULL){
		return NULL;
	}
	for (NODESV* p = head; p != NULL; p = p->pnext){
		if (strcmp(p->data.masv, masv_timkiem) == 0){
			return p;
		}
	}return NULL;
}

//===========Xoa sinh vien=======
// xoa dau
void xoa_dau_sv(PTRSV &head){
	NODESV *p = head;
	head = head->pnext;
	delete p;
}
// xoa theo masv
void xoa_giua_sv(PTRSV &head, char c[]){
	NODESV *p = head;
	NODESV *k = NULL;
	for(; p != NULL; p = p->pnext){
		if(strcmp((p->data.masv), c) == 0){
			k->pnext = p->pnext;
			delete p;
			return;
		}	
			k = p;
	}
}
// xoa cuoi
void xoa_cuoi_sv(PTRSV &head){
	NODESV *p = head;
	NODESV *k = NULL;
	for(; p->pnext != NULL; p = p->pnext)
		if(p->pnext == NULL){
			k->pnext = NULL;
			delete p;
			return;
		}	
		k = p;
}
//======================== DSLTC ====================
//kiem tra lop mo/dong
void kt_huyltc(LTC *ltc){
	if (ltc->huy == false) cout << "bi dong";
	else cout << "duoc mo";
}
// kiem tra ds co full khong
unsigned short full_ltc(DSLTC dsltc){
	return (dsltc.soluong == MAXLTC ? 1 : 0);
}
// kiem tra ds co trong khong
unsigned short empty_ltc(DSLTC dsltc){
	return (dsltc.soluong == 0 ? 1 : 0);
}

bool check_trung_2chuoi(char *chuoi1, char *chuoi2){
	if (strlen(chuoi1) == strlen(chuoi2)){
		for(short i = 0; i < strlen(chuoi1); i++)
			if (chuoi1[i] != chuoi2[i]) return 0; // Khong trung
		return 1; // Trung
	}
	else return 0; // Khong trung
}

bool check_trung_ltc(DSLTC dsltc, char *ma_mh, unsigned short nk, unsigned short hk, unsigned short nhom){
	short i;
	for (i = 0; i < dsltc.soluong; i++)
		if (check_trung_2chuoi(dsltc.ds_ltc[i]->mamh,ma_mh) && dsltc.ds_ltc[i]->nienkhoa == nk && dsltc.ds_ltc[i]->hocki == hk && dsltc.ds_ltc[i]->nhom == nhom) return 1;
	return 0;
}

bool check_trung_ltc(DSLTC dsltc, LTC *ltc){
	short i;
	for (i = 0; i < dsltc.soluong; i++)
		if (check_trung_2chuoi(dsltc.ds_ltc[i]->mamh, ltc->mamh) && dsltc.ds_ltc[i]->nienkhoa == ltc->nienkhoa && dsltc.ds_ltc[i]->hocki == ltc->hocki && dsltc.ds_ltc[i]->nhom == ltc->nhom)
		return 1;
	return 0;
}

bool check_trung_maltc(DSLTC dsltc, short maloptinchi){
	for (short i = 0; i <dsltc.soluong; i++){
		if (maloptinchi == dsltc.ds_ltc[i]->maloptc)
			return 1; // trung
	}
	return 0; // khong trung
}
// xoa lop tin chi theo ma ltc
void xoa_ltc(DSLTC &dsltc, int vitricanxoa){
	if (empty_ltc(dsltc) == 1 || vitricanxoa < 0 || vitricanxoa > dsltc.soluong - 1){
		return;
	}
	if (vitricanxoa == dsltc.soluong)
	{
		delete dsltc.ds_ltc[dsltc.soluong];
		dsltc.soluong--;
		dsltc.ds_ltc[dsltc.soluong] = NULL;//tranh tinh trang con tro bi treo
		return;
	}
	else {
		delete dsltc.ds_ltc[vitricanxoa];
		int i;
		for (i = vitricanxoa; i < dsltc.soluong; i++){
			dsltc.ds_ltc[i] = dsltc.ds_ltc[i + 1];
		}
		dsltc.soluong--;
		dsltc.ds_ltc[dsltc.soluong] = NULL; // k gan thi con tro se bi loi
	}
	return;
}
// xuat thong tin 1 ltc
void xuat_ltc(LTC *ltc){
	cout << "\nMa LTC: " << ltc->maloptc;
	cout << "\nMa Mon Hoc: " << ltc->mamh;
	cout << "\nKhoa: " << ltc->nienkhoa;
	cout << "\nHoc Ki: " << ltc->hocki;
	cout << "\tNhom: " << ltc->nhom;
	cout << "\tSV min: " << ltc->sosvmin;
	cout << "\tSV max: " << ltc->sosvmax;
	cout << "\tLop dang: "; kt_huyltc(ltc);
	xuat_dssvdk(ltc->head);
	cout << endl;
}
// xuat ds lop tin chi
void xuatds_ltc(DSLTC dsltc){
	if (empty_ltc(dsltc) == 1)
		cout << "Danh sach lop tin chi dang trong!";
	else {
		for (short i = 0; i < dsltc.soluong; i++){
		xuat_ltc(dsltc.ds_ltc[i]);
		}
	}
}
//test
void xuatds_ltc(DSLTC dsltc, int chon){
	if (empty_ltc(dsltc) == 1)
		cout << "Danh sach lop tin chi dang trong!";
	else {
		xuat_ltc(dsltc.ds_ltc[chon]);
	}
}

// tim vi tri ma lop tin chi trong DSLTC
int search_maltc(DSLTC &dsltc, int malopTc){
	int i;
	for (i = 0; i < dsltc.soluong; i++){
		//so sanh bang ma lop tin chi
		if (dsltc.ds_ltc[i]->maloptc == malopTc){
			return i; //neu phan trung thi tra ve vi tri i
		}
	}
	return -1; //khong tim thay trung
}

int search_dsltc_mamh_nienkhoa(DSLTC &dsltc, char ma_mon_hoc[], short nk){
	int i;
	for (i = 0; i < dsltc.soluong; i++){
		if (strcmp(dsltc.ds_ltc[i]->mamh, ma_mon_hoc) == 0) {
			if (dsltc.ds_ltc[i]->nienkhoa == nk)
				return 1; // dung thi tra ve 1
		}
	}
	return 0;
}

int search_maloptc_mamh(DSLTC dsltc, int maloptc, char mamh[], int dem)
{
	for (int i = 0; i < dem; i++){
		//so sanh bang ma lop tin chi
		if (dsltc.ds_ltc[i]->maloptc == maloptc)
		{
			if (strcmp(dsltc.ds_ltc[i]->mamh, mamh) == 0) {
				return i; //neu phan trung thi tra ve vi tri i
			}
		}
	}
	return -1; //khong tim thay trung
}

//tim vi tri ma mon hoc trong DSLTC
int search_ma_mon_hoc(DSLTC &dsltc, char ma_mon_hoc[]){
	int i;
	for (i = 0; i < dsltc.soluong; i++){
		//so sanh bang ma mon hoc
		if (strcmp(dsltc.ds_ltc[i]->mamh, ma_mon_hoc) == 0){
			return i; //neu phan trung thi tra ve vi tri i
		}
	}
	return -1; //khong tim thay trung
}

void mo_loptc(DSLTC &dsltc, LTC *ltc){
	cout << "\nNhap vao ma ltc muon mo: ";
	int maltcmuonmo;
	cin >> maltcmuonmo;
	if (search_maltc(dsltc, maltcmuonmo) == -1){
	} else cout << "\nDa ton tai ma ltc nay.";
}

unsigned short dem_svdk(LTC *ltc){
	unsigned short demsv = 0;
	NODEDANGKI *k = ltc->head;
	for (; k != NULL; k = k->pnext){
		demsv++;
	}
	return demsv;
}
// dem bang` ma mon hoc
int dem_so_lop_da_dang_ki(DSLTC dsltc, char mamh[]) {
	int dem = 0;
	for (int i = 0; i < dsltc.soluong; i++){
		if (strcmp(dsltc.ds_ltc[i]->mamh, mamh) == 0) {
			dem++;
		}
	}
	return dem;
}

void huy_ltc(LTC *ltc){
	if(dem_svdk(ltc) < ltc->sosvmin) ltc->huy = false; // dong y huy lop
	else ltc->huy = true;
}
void auto_huy_ltc(DSLTC &dsltc, short nk, short hk){
	short i, check;
	cout << "\nBan co chac chan huy cac ltc nay?";
	cout << "\nDong y nhan 1 || Khong chap nhan nhan 0\n";
	cin >> check;
	if (check == 1){
		for (i = 0; i < dsltc.soluong; i++){
			if (dsltc.ds_ltc[i]->nienkhoa == nk && dsltc.ds_ltc[i]->hocki == hk){
				huy_ltc(dsltc.ds_ltc[i]);
			}
		}
		cout << "\nHuy thanh cong !!";
	}
	else if (check == 0) cout << "\nHuy that bai !!";
}

//================================================== DSSV_DK ====================================================
NODEDANGKI* tao_node_svdk(DANGKI svdk){
	NODEDANGKI *p = new NODEDANGKI;
	if (p == NULL){
		cout << "\nCap phat that bai !";
		return NULL;
	}
	p->data.diem = svdk.diem;
	strcpy(p->data.masv, svdk.masv);
	p->pnext = NULL;
	return p;
}
// them sinh vien dang ki
void them_cuoi_nodedk(PTRDK &head, NODEDANGKI *p){
	if (head == NULL){
		head = p;
	}else{
		NODEDANGKI *k = head;
		while(k->pnext != NULL) k = k->pnext;
		k->pnext = p;
	}
}
// xuat 1 svdk
void xuat_svdk(DANGKI svdk){
	cout << "\nMa SV: " << svdk.masv;
	cout << "\nDiem SV: " << svdk.diem;
}
// xuat dssvdk
void xuat_dssvdk(PTRDK head){
	if (head == NULL){
		cout << "\nDanh Sach rong!";
		system("pause");
		return;
	}
	while (head != NULL){
		xuat_svdk(head->data);
		head = head->pnext;
	}
}
//===========tim kiem sv dk===========
NODEDANGKI* search_svdk_ltc(PTRDK dsdk, char masv[]){
	for (PTRDK p = dsdk; p != NULL; p = p->pnext){
		if (strcmp(p->data.masv, masv) == 0) {
			return p;
		}
	}
	return NULL;
}

//========================== DSMH =====================
//===========khoi tao cay======
void khoi_tao_cay(PTRMH &t){
	t = NULL;
}
//=============them mon hoc=======
//kiem tra rong
bool empty_dsmh(PTRMH t){
	if(t == NULL)
		return true;
	return false;	
}
//kiem tra trung` mon hoc
int kiem_tra_trung_mh(PTRMH dsmh, char mmh[]){
	if(dsmh == NULL)	
		return 0;
	else{
		if(strcmp(dsmh->data.mamh, mmh) == 0)
			return 1;
		else if(strcmp(dsmh->data.mamh, mmh) > 0)
			kiem_tra_trung_mh(dsmh->left, mmh);
		else
			kiem_tra_trung_mh(dsmh->right, mmh);	
	}
}
PTRMH kiem_tra_trung_ma_hoc(PTRMH dsmh, char mmh[]){
	if (dsmh == NULL) return NULL;
	else{
		if(strcmp(dsmh->data.mamh, mmh) == 0)
			return dsmh;
		else if(strcmp(dsmh->data.mamh, mmh) > 0)
			kiem_tra_trung_ma_hoc(dsmh->left, mmh);
		else
			kiem_tra_trung_ma_hoc(dsmh->right, mmh);	
	}
}
// them
void them_node_vao_cay(PTRMH &t, MONHOC data){
	if(empty_dsmh(t) == true){
		PTRMH p = new NODEMH;
		p->data = data;
		p->left = NULL;
		p->right= NULL;
		t = p;
		return;
	}else{
		if(0 < strcmp(t->data.mamh, data.mamh))
			them_node_vao_cay(t->left, data);
		else if (0 > strcmp(t->data.mamh, data.mamh))
			them_node_vao_cay(t->right, data);
		// bi trung thi in ra thong bao (console)
	}
}
////xoa mon hoc
//void node_the_mang(PTRMH &p, PTRMH &q){ // node be nhat ben phai
//	if(q->left  != NULL){
//		node_the_mang(p, q->left); 
//	}else{
//		p->data = q->data; // cap nhat du lieu node q cho p
//		p = q;				// p tro toi q de xoa node q;
//		q = q->right; 		// cap nhat lai moi lien ket cua cha node q voi con ben phai node q
//	}
//}
//void xoa_node_trong_cay(PTRMH &dsmh, char mmh[]){
//	if(dsmh == NULL)
//		return;
//	if(strcmp(dsmh->data.mamh, mmh) > 0)
//		xoa_node_trong_cay(dsmh->left, mmh);
//	else if(strcmp(dsmh->data.mamh, mmh) < 0)
//		xoa_node_trong_cay(dsmh->right, mmh);
//	else{
//		PTRMH del = dsmh;
//		if(dsmh->left == NULL)
//			dsmh = dsmh->right; // cap nhat lien ket giua node cha dsmh vs con dsmh		
//		else if(dsmh->right == NULL)
//			dsmh = dsmh->left;
//		else
//			node_the_mang(del, dsmh->right);
//		delete del;
//	}			
//}
//void xoa_mon_hoc(DSLTC &dsltc, PTRMH &dsmh){
//	int key, vitri = 0, temp1, temp2 = 2;
//	MONHOC mh;
////	Khung_Xoa_MonHoc();
//RESET:
//	while(true){
//		TextColor(7);
//		gotoXY(x + vitri, y);
//		key = get_key();
//		if((key <= 'Z' && key >= 'A' || key <= 'z' && key >= 'a'|| key <= '9' && key >= '0') && vitri < 10){
//			mh.mamh[vitri] = char(key);
//			mh.mamh[vitri] = toupper(mh.mamh[vitri]);
//			cout << mh.mamh[vitri];
//			vitri++;
//		}if(key == BACKSPACE && vitri > 0){
//			vitri--;
//			gotoXY(x + vitri, y);
//			cout << " ";
//			gotoXY(x + vitri, y);
//		}if(key == ENTER && vitri != 0){
//			mh.mamh[vitri] = '\0';
//			temp1 = kiem_tra_trung_mh(dsmh, mh.mamh);
//			if(temp1 == 1){ // co mon hoc trong danh sach
//				// kiem tra trung lop tin chi
//				// neu chua mo thi co the xoa
//				if(temp2 != -1){
//					xoa_node_trong_cay(dsmh, mh.mamh);
//					ghi_chu("Xoa thanh cong!", 15,26,3,699);
//					return;					
//				}else{// da mo lop tin chi roi, khong the xoa
//					ghi_chu("Mon hoc da mo lop tin chi khong the xoa!", 15,26,3,699);
//					gotoXY(x, y);
//					goto RESET;	
//				}
//			}else {// khong co mon hoc trong danh sach
//					ghi_chu("Mon hoc nay khong ton tai trong danh sach!", 15,26,3,699);
//					gotoXY(x, y);
//					goto RESET;
//			}
//		}
//		if(key == ESC)
//			return;
//	}	
//	
//}
// xuat ds mon hoc
void xuat_lnr(PTRMH t){
	if(t != NULL){
		xuat_lnr(t->left);
		cout << endl;cout << t->data.mamh;
		cout << endl;cout << t->data.tenmh;
		cout << endl;cout << t->data.stclt;
		cout << endl;cout << t->data.stcth;
		xuat_lnr(t->right);
	}
}
void do_dsmh_ra_mang(PTRMH t, MONHOC** mang, unsigned short &soluong){
	if(t != NULL){
		do_dsmh_ra_mang(t->left, mang, soluong);
		mang[soluong] = new MONHOC;
			strcpy(mang[soluong]->mamh, t->data.mamh);
			strcpy(mang[soluong]->tenmh, t->data.tenmh);
			mang[soluong]->stclt = t->data.stclt;
			mang[soluong]->stcth = t->data.stcth;
			soluong++;
		do_dsmh_ra_mang(t->right, mang, soluong);
	}
}
void xuat_mang_mon_hoc(MONHOC* mang[], unsigned short soluong, unsigned short checktrang, unsigned short chon){
	unsigned short i;
	if (soluong == 0){
		cout << "\nMang rong";
		return;
	}
	if (checktrang == 1){
		for (i = 0; i < soluong; i++){
			if (i / 13 == 0){
//			if (chon < 13){
				gotoxy(40, 9 + (chon % 13) * 2);	cout << mang[i]->mamh;
				gotoxy(65, 9 + (chon % 13) * 2);	cout << mang[i]->tenmh;
				gotoxy(129, 9 + (chon % 13) * 2);	cout << mang[i]->stclt;
				gotoxy(153, 9 + (chon % 13) * 2);	cout << mang[i]->stcth;
			}
			chon++;
		}
	}
	else if (checktrang == 2){
		chon = 0;
		for (; i < soluong; i++){
			if (i / 13 > 0){
//			if (chon >= 13){
				gotoxy(40, 9 + (chon % 13) * 2);	cout << mang[i]->mamh;
				gotoxy(65, 9 + (chon % 13) * 2);	cout << mang[i]->tenmh;
				gotoxy(129, 9 + (chon % 13) * 2);	cout << mang[i]->stclt;
				gotoxy(153, 9 + (chon % 13) * 2);	cout << mang[i]->stcth;
			}
			chon++;
		}
	}
	else if (checktrang == 3){
		chon = 0;
		for (; i < soluong; i++){
			if (i / 13 > 1){
//			if (chon >= 13){
				gotoxy(40, 9 + (chon % 13) * 2);	cout << mang[i]->mamh;
				gotoxy(65, 9 + (chon % 13) * 2);	cout << mang[i]->tenmh;
				gotoxy(129, 9 + (chon % 13) * 2);	cout << mang[i]->stclt;
				gotoxy(153, 9 + (chon % 13) * 2);	cout << mang[i]->stcth;
			}
			chon++;
		}
	}
}
//LTC
void xuat_mang_dsltc(DSLTC dsltc, MONHOC* mang[], unsigned short soluong, unsigned short checktrang, unsigned short chon){
	unsigned short i, j, demsl_xuatduoc = 0;
	if (dsltc.soluong == 0){
		cout << "\nMang rong";
		return;
	}
	if (checktrang == 1){
		for (i = 0; i < dsltc.soluong; i++){
			for (j = 0; j < soluong; j++){
				if (stricmp(dsltc.ds_ltc[i]->mamh, mang[j]->mamh) == 0){
//					if (i / 13 == 0){
						gotoxy(44, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->maloptc;
						gotoxy(52, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->mamh;
						gotoxy(65, 9 + (chon % 13) * 2);	cout << mang[j]->tenmh;
						gotoxy(116, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->nienkhoa;
						gotoxy(127, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->hocki;
						gotoxy(136, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->nhom;
						gotoxy(148, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->sosvmax;
						gotoxy(160, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->sosvmax - dem_svdk(dsltc.ds_ltc[i]);
						demsl_xuatduoc++;
//					}
					chon++;
				}
			}
		}
	}
	else if ((checktrang == 2) && (demsl_xuatduoc > 13)){
		chon = 0;
		for (i = 13; i < dsltc.soluong; i++){
			for (j = 0; j < soluong; j++){
				if (stricmp(dsltc.ds_ltc[i]->mamh, mang[j]->mamh) == 0){
					if (i / 13 > 0){
						gotoxy(44, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->maloptc;
						gotoxy(52, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->mamh;
						gotoxy(65, 9 + (chon % 13) * 2);	cout << mang[j]->tenmh;
						gotoxy(116, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->nienkhoa;
						gotoxy(127, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->hocki;
						gotoxy(136, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->nhom;
						gotoxy(148, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->sosvmax;
						gotoxy(160, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->sosvmax - dem_svdk(dsltc.ds_ltc[i]);
						demsl_xuatduoc++;
					}
					chon++;
				}
			}
		}
	}
}
//overloading
//void xuat_mang_dsltc(DSLTC dsltc, unsigned short checktrang, unsigned short chon){
//	unsigned short i, j;
//	if (dsltc.soluong == 0){
//		cout << "\nMang rong";
//		return;
//	}
//	if (checktrang == 1){
//		for (i = 0; i < dsltc.soluong; i++){
//			for (j = 0; j < soluong; j++){
//				if (stricmp(dsltc.ds_ltc[i]->mamh, mang[j]->mamh) == 0){
//					if (i / 13 == 0){
//						gotoxy(44, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->maloptc;
//						gotoxy(52, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->mamh;
//						gotoxy(65, 9 + (chon % 13) * 2);	cout << mang[j]->tenmh;
//						gotoxy(116, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->nienkhoa;
//						gotoxy(127, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->hocki;
//						gotoxy(136, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->nhom;
//						gotoxy(148, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->sosvmax;
//						gotoxy(160, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->sosvmax - dem_svdk(dsltc.ds_ltc[i]);
//					}
//					chon++;
//				}
//			}
//		}
//	}
//	else if (checktrang == 2){
//		chon = 0;
//		for (i = 0; i < dsltc.soluong; i++){
//			for (j = 0; j < soluong; j++){
//				if (stricmp(dsltc.ds_ltc[i]->mamh, mang[j]->mamh) == 0){
//					if (i / 13 > 0){
//						gotoxy(44, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->maloptc;
//						gotoxy(52, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->mamh;
//						gotoxy(65, 9 + (chon % 13) * 2);	cout << mang[j]->tenmh;
//						gotoxy(116, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->nienkhoa;
//						gotoxy(127, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->hocki;
//						gotoxy(136, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->nhom;
//						gotoxy(148, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->sosvmax;
//						gotoxy(160, 9 + (chon % 13) * 2);	cout << dsltc.ds_ltc[i]->sosvmax - dem_svdk(dsltc.ds_ltc[i]);
//					}
//					chon++;
//				}
//			}
//		}
//	}
//}
