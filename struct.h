#include <string.h>
#include <fstream>
#define MAX_MALOP   11
#define MAX_TENLOP  50
#define MAX_CLASS   100 
#define MAX_MAMH 15
#define MAX_CH   90000
#define len_ID   5
#define MAX_ND   300
#define MAX_DA   200
#define MAX_MASV  11 
#define MAX_HO    50
#define MAX_TEN   15
#define MAX_PHAI  3
#define MAX_PASS  10
#define MAX_STD   100
#define MAX_MAMH  15
#define MAX_TENMH 50
#define MAX_SUBJ  500
#define MAX_QUEST 200
//Danh sach cau hoi - danh sach tuyen tinh
struct questInfor{
	char done;
	int ID;
	char NoiDung[MAX_ND+1];
	char A[MAX_DA+1];
	char B[MAX_DA+1];
	char C[MAX_DA+1];
	char D[MAX_DA+1];
	char DapAn;	
};
struct questList{ 
	unsigned int n=0 ;
	questInfor Q[MAX_QUEST];
};
//Danh sach cau tra loi - tuyen tinh cap phat dong
struct answer{
    int ID;
	char TRALOI; 
};
typedef answer* PTRA;
//Bai thi- tuyen tinh 
struct test{
	int nMin;
	int n;
	PTRA answers;
};
//Danh sach mon hoc - cay nhi phan tim kiem
struct subInfor{
	char MAMH[MAX_MAMH+1];
	char TENMH[MAX_TENMH+1];
	questList ql; //lay ra cau hoi thu i - ql.Q[i]
};
struct subNode {
	int key;
	subInfor subi4;
	subNode* left;
	subNode* right;
};
typedef subNode* PTRSUB;
//Danh sach diem - danh sach lien ket don
struct markInfor{
	char Mamh[MAX_MAMH+1];
	float Diem;	
};
struct markNode{
	markInfor marki4;
	test testi4;
	struct markNode* Next;
};
typedef markNode* PTRM;
//Danh sach sinh vien - danh sach lien ket don
struct stuInfor{
	char MASV[MAX_MASV+1];
	char HO[MAX_HO+1];
	char TEN[MAX_TEN+1];
	char PHAI[MAX_PHAI+1];
	char password[MAX_PASS+1];
};
struct stuNode{
	stuInfor stui4;
	PTRM MFirst;
	struct stuNode* Next;
};
typedef stuNode* PTRS;
//Danh sach lop - mang con tro
struct classInfor{
	char MALOP[MAX_MALOP+1];
	char TENLOP[MAX_TENLOP+1];
};
struct Class{
	classInfor classi4;
	PTRS SFirst;
};
typedef Class* PTRC;
struct classList{
	int nClass;
	PTRC classes[MAX_CLASS];
};



