#include "quesList.h"
#include <string.h>
using namespace std;
void set_quesInfor(questInfor& quesif,int ID, char* ND, char* A, char* B, char* C, char* D, char DA){
	quesif.ID = ID;
	strcpy(quesif.NoiDung,ND);
	strcpy(quesif.A,A);
	strcpy(quesif.B,B);
	strcpy(quesif.C,C);
	strcpy(quesif.D,D);
	quesif.DapAn = DA;
}
void Init_QuesList(questList &qList){
   qList.n=0;
}
bool Empty_QuestList(questList &qList){
    return qList.n==0;
}
bool Full_QuestList(questList qList){ 
	return qList.n==MAX_QUEST-1;
}
int Search_Quest(questList &qList, int QuestID) {
  for (int i =0; i < qList.n ; i++)
		if (qList.Q[i].ID == QuestID) return i;
  return -1;
}
int getMAXID(questList &qList,char* MAMH){//tim id cua cau hoi moi nhat vua dc them vao
	if(qList.n == 0) return -1;
	int maxID = qList.Q[0].ID;
	for(int i = 1; i < qList.n; i++){
		if(qList.Q[i].ID > maxID) maxID = qList.Q[i].ID;
	}
	return maxID;
}
int Insert_Quest(questList &qList, questInfor &questi4){
	int j; 
	if (Full_QuestList(qList))
		return 0;
	questi4.done='F';
	qList.Q[qList.n++]=questi4;
	return 1;
}
int Delete_Quest( questList &qList,int i) {
	if(i < 0 || i >= qList.n || qList.n==0) {
		return 0;
	}
		for(int j = i+1; j < qList.n; j++)
			qList.Q[j-1] = qList.Q[j];
	qList.n--;
	return 1;
}
void load_QuestList(std::ifstream &filein,questList &qList){
	char buff[10];
	filein >> qList.n;	
	for(int i=0;i<qList.n;i++){
		filein >> qList.Q[i].ID;
		filein.getline(buff,10);
		filein >> qList.Q[i].done;
		filein.getline(buff,10);
		filein.getline(qList.Q[i].NoiDung,MAX_ND); 
		filein.getline(qList.Q[i].A,MAX_DA);
		filein.getline(qList.Q[i].B,MAX_DA);
		filein.getline(qList.Q[i].C,MAX_DA);
		filein.getline(qList.Q[i].D,MAX_DA);
		filein >>qList.Q[i].DapAn;
	}
}
void save_QuestList(std::ofstream &fileout, questList &qList){		
	fileout<<qList.n<<endl;
	for(int i=0;i<qList.n;i++){
	fileout<<qList.Q[i].ID<<endl;
	fileout<<qList.Q[i].done<<endl;
	fileout<<qList.Q[i].NoiDung<<endl;
	fileout<<qList.Q[i].A<<endl;
	fileout<<qList.Q[i].B<<endl;
	fileout<<qList.Q[i].C<<endl;
	fileout<<qList.Q[i].D<<endl;
	fileout<<qList.Q[i].DapAn<<endl;
	}
}

