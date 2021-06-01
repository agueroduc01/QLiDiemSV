#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#define ENTER 13
#define BACKSPACE 8
//f1	112
//f2	113
//f3	114
//f4	115
//f5	116
//f6	117
//f7	118
//f8	119
//f9	120
//f10	121
//f11	122
//f12	123
#define MAXLTC 10000



//===================== DSSV ====================
struct SINHVIEN{
	char masv[16];
	char ho[31];
	char ten[11];
	char phai[4];
	char sdt[12];
	char malop[16];
};
struct NODESV{
	SINHVIEN data;
	struct NODESV *pnext;
};
typedef struct NODESV* PTRSV;
//===================== DSSV_DK =======================
struct DANGKI{
	char masv[16];
	float diem;
};
struct NODEDANGKI{
	DANGKI data;
	struct NODEDANGKI *pnext;
};
typedef struct NODEDANGKI* PTRDK;
//============== DSLTC =================
struct LTC{
	unsigned short maloptc;
	char mamh[11];
	unsigned short nienkhoa, hocki, nhom;
	unsigned short sosvmax, sosvmin;
	bool huy = false;
	PTRDK head = NULL;
};
struct DSLTC{
	short soluong = 0;
	LTC *ds_ltc[MAXLTC];
};
//================== DSMH ==========================
struct MONHOC{
	char mamh[11];
	char tenmh[51];
	unsigned short stclt, stcth;
};
struct NODEMH{
	MONHOC data;
	struct NODEMH* left;
	struct NODEMH* right;
};
typedef struct NODEMH* PTRMH;
