#ifndef _STUDENT_LIST
#define _STUDENT_LIST
#define MAX_MASV  11 
#define MAX_HO    50
#define MAX_TEN   15
#define MAX_PHAI  3
#define MAX_PASS  10
#define MAX_STD   100
#include "markList.h"
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

void set_stuInfor(stuInfor& stuif,char* stuID, char* LName, char* FName, char* sex, char* PWRD);
bool SList_empty(PTRS SFirst);
PTRS get_student_idx(PTRS SFirst, int idx);
PTRS search_SList_MSSV(PTRS SFirst,char* stuID);
void insert_first_SList(PTRS &SFirst, stuInfor &stuif, PTRM MFirst);
void insert_afterAt_SList(PTRS atSNode, stuInfor &stuif, PTRM MFirst);
void insert_SList_CTT(PTRS &SFirst, stuInfor &stuif, PTRM MFirst);
void free_SNode(PTRS &SNode);
void free_SList(PTRS &SFirst);
void delete_first_SList(PTRS &SFirst);
void delete_afterAt_SList(PTRS atSNode);
void delete_SList_MSSV(PTRS &SFirst, char* stuID);
bool check_password(PTRS SNode,char* PSW);
void TEN_HO_MASV(char* buff, stuInfor& stuif);
void load_SList(std::ifstream &filein, PTRS &SFirst);
void save_SList(std::ofstream &fileout, PTRS SFirst);
void init_SList(PTRS &SFirst);
void MH_GM(char* str);
int sinh_vien_da_thi(PTRS SNode);
#endif

