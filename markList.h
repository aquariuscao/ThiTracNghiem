#ifndef _MARK_LIST
#define _MARK_LIST
#include "quesList.h"
#include "ansList.h"
#include <string.h>
#include <fstream>
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

void init_MList(PTRM &MFirst);
void set_markInfor(markInfor &markif, char* subjID, float mark);
bool MList_empty(PTRM MFirst);
PTRM new_mark_node(markInfor& markif,test& testif);
PTRM get_mark_idx(PTRM MFirst, int idx);
void insert_first_MList(PTRM &MFirst, markInfor& markif,test& testif);
void insert_afterAt_MList(PTRM atMNode, markInfor& markif, test& testif);
void insert_last_MList(PTRM &MFirst, markInfor &markif,test& testif);
PTRM search_MList_MMH(PTRM MFirst,char* subjID);
void free_MList(PTRM &MFirst);
float mark_of_subj(PTRM MFirst,char* subjID);
void save_MList(std::ofstream &fileout, PTRM MFirst);
void load_MList(std::ifstream &filein, PTRM &MFirst);
#endif
 
                         
