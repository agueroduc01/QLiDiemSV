#include "XuLi.h"
#include <fstream>

//========doc file mon hoc=======
void doc_file_mh(PTRMH &t){
	ifstream infile;
	string data;
	int a;
	infile.open("D:\\DO_AN_QLSV\\DSMH.txt", ios_base::in);
	MONHOC mh;
	if(infile.fail() == true){
		cout <<"\nKhong tim thay file";
		system("pause");
		return;
	}
	while(infile.eof() != true){
		
		getline(infile, data);
		if(data.size() == 0)
			break; // file k co du lieu
		strcpy(mh.mamh, data.c_str());
		getline(infile, data);	strcpy(mh.tenmh, data.c_str());	
		infile >> a; mh.stclt = a;
		infile >> a; mh.stcth = a;
		infile.ignore();// doc \n;
		them_node_vao_cay(t, mh);
	}
	infile.close();	
}
//===========ghi file mon hoc=========
void ghi_file_nlr(ofstream &fileout, PTRMH dsmh){
	if(dsmh != NULL){
		fileout << endl <<dsmh->data.mamh << endl
				<< dsmh->data.tenmh << endl
				<< dsmh->data.stclt << endl
				<< dsmh->data.stcth;
		ghi_file_nlr(fileout, dsmh->left);		
		ghi_file_nlr(fileout, dsmh->right);
	}
}
void ghi_file_dsmh(PTRMH dsmh){
	ofstream fileout;
	fileout.open("DSMH.txt", ios :: out);
	ghi_file_nlr(fileout, dsmh);
	fileout.close();
}

//============ doc file DSLTC =============
void doc_file_dsltc(DSLTC &dsltc){
	ifstream infile;
	string data;
	infile.open("DSLTC.txt", ios_base::in);
	if (infile.fail() == true){
		cout << "\nKhong tim thay file!";
		system("pause");
		return;
	}
	short i, soluong_svdk;
	NODEDANGKI *p;
	while(infile.eof() != true){
		dsltc.ds_ltc[dsltc.soluong] = new LTC;
		infile >> dsltc.ds_ltc[dsltc.soluong]->maloptc;
		infile.ignore();// doc \n;
		getline(infile, data); strcpy(dsltc.ds_ltc[dsltc.soluong]->mamh, data.c_str());
		if(data.size() == 0)
			break; // file k co du lieu
		infile >> dsltc.ds_ltc[dsltc.soluong]->nienkhoa;
		infile >> dsltc.ds_ltc[dsltc.soluong]->hocki;
		infile >> dsltc.ds_ltc[dsltc.soluong]->nhom;
		infile >> dsltc.ds_ltc[dsltc.soluong]->sosvmax;
		dsltc.ds_ltc[dsltc.soluong]->sosvmin = 0;
		infile >> soluong_svdk; // doc so luong svdk
		if (soluong_svdk != 0){
			for (i = 0; i < soluong_svdk; i++){
				p = new NODEDANGKI;
				p->pnext = NULL;
				infile >> p->data.diem;
				infile.ignore();// doc \n;
				getline(infile, data); strcpy(p->data.masv, data.c_str());
				them_cuoi_nodedk(dsltc.ds_ltc[dsltc.soluong]->head, p);
			}
			dsltc.soluong++;
		}
	}
	infile.close();
}
//============= ghi file dsltc ============
void ghi_file_dsltc(DSLTC dsltc){
	ofstream outfile;
	outfile.open("DSLTC.txt", ios_base::out);
	for (int i = 0; i < dsltc.soluong; i++){
		outfile << dsltc.ds_ltc[i]->maloptc << endl;
		outfile << dsltc.ds_ltc[i]->mamh << endl;
		outfile << dsltc.ds_ltc[i]->nienkhoa << endl;
		outfile << dsltc.ds_ltc[i]->hocki << endl;
		outfile << dsltc.ds_ltc[i]->nhom << endl;
		outfile << dsltc.ds_ltc[i]->sosvmax << endl;
		outfile << dem_svdk(dsltc.ds_ltc[i]) << endl;
		for (PTRDK k = dsltc.ds_ltc[i]->head; k != NULL; k = k->pnext){
			outfile << k->data.diem << endl;
			outfile << k->data.masv << endl;
		}
	}
	outfile.close();
}
//================= doc file sinh vien ==============
void doc_file_sv(PTRSV &dssv){
	ifstream filein;
	filein.open("DSSV.txt", ios_base::in);
	string data;
	filein.ignore();
	SINHVIEN sv;
	while(!filein.eof()){
		getline(filein, data);		strcpy(sv.malop, data.c_str());	
		getline(filein, data);		strcpy(sv.masv, data.c_str());	
		getline(filein, data);		strcpy(sv.ho, data.c_str());
		getline(filein, data);		strcpy(sv.ten, data.c_str());
		getline(filein, data);		strcpy(sv.phai, data.c_str());
		getline(filein, data);		strcpy(sv.sdt, data.c_str());
		them_cuoi_sv(dssv, tao_nodesv(sv));
	}
	
	filein.close();
}
//ghi file sinh vien
void ghi_file_sv(PTRSV dssv){
	ofstream fileout;
	fileout.open("DSSV.txt", ios::out);
	while(dssv != NULL){
		fileout << endl << dssv->data.malop << endl;
		fileout << dssv->data.masv << endl;
		fileout << dssv->data.ho << endl;
		fileout << dssv->data.ten << endl;
		fileout << dssv->data.phai << endl;
		fileout << dssv->data.sdt;
		dssv = dssv->pnext;
	}
}
