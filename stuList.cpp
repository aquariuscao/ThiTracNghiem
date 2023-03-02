#include "stuList.h"
void set_stuInfor(stuInfor& stuif,char* stuID, char* LName, char* FName, char* sex, char* PWRD){
	strcpy(stuif.MASV,stuID);
	strcpy(stuif.HO,LName);
	strcpy(stuif.TEN,FName);
	strcpy(stuif.PHAI,sex);
	strcpy(stuif.password,PWRD);
}
void init_SList(PTRS &SFirst){
	SFirst = NULL;
}
bool SList_empty(PTRS SFirst){
	return SFirst==NULL;
}
PTRS get_student_idx(PTRS SFirst, int idx){
	for(int i=0 ; i<idx && SFirst != NULL; i++, SFirst = SFirst->Next);
	return SFirst;  
}
PTRS new_stu_node(stuInfor &stuif, PTRM MFirst){
	PTRS SNode = new stuNode;
	if(SNode == NULL) return NULL;
	SNode->stui4 = stuif; 
	SNode->MFirst = MFirst;
    return SNode;
}
void insert_first_SList(PTRS &SFirst, stuInfor &stuif, PTRM MFirst){
	PTRS SNode = new_stu_node(stuif, MFirst);
	SNode->Next= SFirst;
	SFirst = SNode;
}
void insert_afterAt_SList(PTRS atSNode, stuInfor &stuif, PTRM MFirst){
	if(atSNode==NULL) return; 
	PTRS SNode = new_stu_node(stuif, MFirst);
	SNode->Next= atSNode->Next;
	atSNode->Next = SNode;
}
void insert_last_SList(PTRS &SFirst, stuInfor &stuif, PTRM MFirst){
	if(SList_empty(SFirst)) insert_first_SList(SFirst,stuif,MFirst);
	else{
	    PTRS nodeRun = SFirst;
	    while(nodeRun->Next!=NULL) nodeRun = nodeRun->Next;
	    insert_afterAt_SList(nodeRun,stuif,MFirst);
    }
}

void insert_SList_CTT(PTRS &SFirst, stuInfor &stuif, PTRM MFirst){// tim vi tri can chen dua vao ten - insert after
	char i4Is[MAX_MASV+1],i4At[MAX_MASV+1];
	PTRS at = SFirst, before;
	strcpy(i4Is,stuif.MASV);
	while(at!=NULL){
		strcpy(i4At,at->stui4.MASV);
		if(stricmp(i4Is,i4At)<0) break;
		before=at;
	    at=at->Next;
	}
    if(at==SFirst) insert_first_SList(SFirst,stuif,MFirst);
    else insert_afterAt_SList(before,stuif,MFirst);
}
void free_SNode(PTRS &SNode){
	if(SNode!=NULL){
		free_MList(SNode->MFirst);
		delete SNode;
	}
}
void delete_first_SList(PTRS &SFirst){
	if(SList_empty(SFirst)) return;
	PTRS SNode = SFirst;
	SFirst = SFirst->Next;
	free_SNode(SNode);
}
void delete_afterAt_SList(PTRS atSNode){
	if(atSNode==NULL||atSNode->Next==NULL) return;
	PTRS SNode = atSNode->Next;
	atSNode->Next=SNode->Next;
	free_SNode(SNode);
}
void delete_SList_MSSV(PTRS& SFirst,char* stuID){
	if(SList_empty(SFirst)) return;
	if(stricmp(SFirst->stui4.MASV,stuID)==0) delete_first_SList(SFirst);
	else{
	    for(PTRS SNode = SFirst; SNode->Next!=NULL; SNode=SNode->Next){
		    if(stricmp(SNode->Next->stui4.MASV,stuID)==0){
		        delete_afterAt_SList(SNode);
		        break;
	        }
        }
	}
}
bool check_password(PTRS SNode,char* PSW){
	if(SNode == NULL) return 0;
	if(stricmp(SNode->stui4.password,PSW)==0) return 1;
	return 0;
}
int sinh_vien_da_thi(PTRS SNode){//kiem tra sinh vien da thi hay chua
	if(SNode==NULL) return -1;
	if(SNode->MFirst!=NULL) return 1;
	return 0;
}
void free_SList(PTRS &SFirst){
	PTRS SNode;
	while(SFirst!=NULL){
		SNode = SFirst;
		SFirst = SFirst->Next;
		free_SNode(SNode);
	}
}
int nStuNode(PTRS SFirst){
	int nSNode = 0;
	while(SFirst!=NULL){
		nSNode++;
		SFirst=SFirst->Next;
	}
	return nSNode;
}
void MH_GM(char* str){//ma hoa va giai ma pass
	if(str == NULL) return;
	while(*str != '\0'){
		*str = - *str -1; 
		str++;
	} 
}
void load_SList(std::ifstream &filein, PTRS &SFirst){
	int nSNode;
	filein.read((char*)&nSNode,sizeof(nSNode));
    stuInfor stuif;
	PTRM MFirst;
	for(int i=0; i<nSNode; i++){
		filein.read((char*)&stuif,sizeof(stuif));
		MH_GM(stuif.password);//giai ma
		init_MList(MFirst);
		load_MList(filein,MFirst);
		insert_last_SList(SFirst,stuif,MFirst);
    }
}
void save_SList(std::ofstream &fileout, PTRS SFirst){
	stuInfor buff;
	int nSNode = nStuNode(SFirst);
	fileout.write((const char*)&nSNode,sizeof(nSNode));
	for(PTRS SNode = SFirst; SNode!=NULL;SNode=SNode->Next){
		buff = SNode->stui4; 
		MH_GM(buff.password);//ma hoa
		fileout.write((const char*)&buff,sizeof(buff));
		save_MList(fileout, SNode->MFirst);
	}
}
PTRS search_SList_MSSV(PTRS SFirst,char* stuID){//tim kiem sinh vien theo mssv
	for(PTRS SNode = SFirst; SNode!=NULL; SNode = SNode->Next){
		if(stricmp(SNode->stui4.MASV,stuID)==0) return SNode;
	}
	return NULL;
}

