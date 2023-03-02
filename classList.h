#ifndef _CLASS_LIST
#define _CLASS_LIST
#define MAX_MALOP   11
#define MAX_TENLOP  50
#define MAX_CLASS   100 
#include "stuList.h"  
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

void set_classInfor(classInfor &classif, char* classID, char* className);
PTRS search_student_all_class_MSSV(classList &CList,char* stuID);
int insert_CList_CTT(classList &CList, Class &CLS);
void free_CList(classList &CList);
void init_CList(classList &CList);
int insert_CList_idx(classList &CList, Class &CLS, int idx);
void delete_CList_idx(classList &CList, int idx);
int search_CList_ML(classList& CList,char* classID);
void load_CList(std::ifstream &filein, classList& CList);
void save_CList(std::ofstream &fileout, classList& CList);
int lop_da_co_sinh_vien_thi(PTRC CNode);
#endif
