#ifndef _SUBJ_LIST
#define _SUBJ_LIST
#define MAX_MAMH  15
#define MAX_TENMH 50
#define MAX_SUBJ  500
#include <string.h>
#include <cmath>
#include <fstream>
#include "quesList.h"
#include <iostream>
using namespace std;
struct subInfor{
	char MAMH[MAX_MAMH+1];
	char TENMH[MAX_TENMH+1];
	questList ql; 
};
struct subNode { 
	int key;
	subInfor subi4;
	subNode* left;
	subNode* right;
};
typedef subNode* PTRSUB;

void set_subjInfor(subInfor &subjif, char* subjID, char* subjName);
bool Empty_SubjList(PTRSUB &root);
void Init_SubjList(PTRSUB &root);
PTRSUB NewSubj(subInfor &subjif,int Nkey);
void find_left_node(PTRSUB &root, PTRSUB &p);
void Insert_Subject(PTRSUB &root, subInfor& subif,int &Nkey);
void Delete_Subject(PTRSUB &root, int infor);
PTRSUB Search_Subject(PTRSUB &root, int x);
int Mon_hoc_co_cau_hoi_da_thi(PTRSUB &root,char* subjID);
int KT_Cau_hoi_da_thi(questList qList, char* subjID);
PTRSUB Search_Subject_MMH(PTRSUB &root, char* SubID);
void Free_Subj_List(PTRSUB &root);
void load_SubList(std::ifstream &filein,PTRSUB &root,int &offset, int &k, int &d);
int nSub(PTRSUB &root);
int taoNutGoc(int x);
int sinhkhoa(int &offset,int &k,int &d);
void save_Subject(std::ofstream &fileout, PTRSUB &root);
void save_SubjList(std::ofstream &fileout, PTRSUB &root);
#endif

