#ifndef _QUESTION_LIST
#define _QUESTION_LIST
#define MAX_MAMH 15
#define len_ID   5
#define MAX_ND   300
#define MAX_DA   200
#define MAX_QUEST 200
#include <fstream>
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
	unsigned n;
	questInfor Q[MAX_QUEST];
}; 
void set_quesInfor(questInfor& quesif,int ID, char* ND, char* A, char* B, char* C, char* D, char DA);
void Init_QuesList(questList &qList);
bool Empty_QuesList(questList qList);
bool Full_QuestList(questList qList);
int Delete_Quest(questList &qList,int i);
int Insert_Quest(questList &qList, questInfor& infor);
int Search_Quest(questList &qList, int QuestID);
int getMAXID(questList &qList,char* MAMH);
void load_QuestList(std::ifstream &filein,questList &qList);
void save_QuestList(std::ofstream &fileout, questList &qList);
#endif

