#include "subjList.h"
void set_subjInfor(subInfor &subjif, char* subjID, char* subjName){
	strcpy(subjif.MAMH, subjID);
	strcpy(subjif.TENMH, subjName);
}
void Init_SubjList(PTRSUB &root){
	root = NULL;
}
bool Empty_SubjList(PTRSUB root){
	return root == NULL;
}
PTRSUB NewSubj(subInfor &subif,int Nkey){
    PTRSUB p;
    p = new subNode;
    if (p!=NULL){
    	p->key=Nkey;
        p->subi4 = subif;
        p->left = NULL;
        p->right = NULL;
        return p;
    }
    return NULL;
}
int taoNutGoc(int x) {
	int count = 0;
	while (x > 0) {
		x = x >> 1;
		count++;
	}
	return (int)pow(2, count) * 127;
}
int sinhkhoa(int &offset,int &k,int &d){
	if(k==pow(2,d-1)){
		d++;
		k = 0;
		offset /= 2;
		if (offset == 0)
			return -1;
	}
	k++;
	return (offset) + (offset*2)*(k-1);
}
void Insert_Subject(PTRSUB &root, subInfor& subif,int &Nkey){
    if (root==NULL) root = NewSubj(subif,Nkey);
    else {
        if(Nkey < root->key)
            Insert_Subject(root->left,subif,Nkey);    
        else
            Insert_Subject(root->right,subif,Nkey);
    }
}
void find_left_node(PTRSUB &root, PTRSUB &p){
    if (p->left!= NULL)   //  p la nut la tm la nut trai nhat cua nhanh phai
        find_left_node(root, p->left);
    else{
        root->subi4 = p->subi4;  
        root = p; 
        p = p->right;
    }
}
void Delete_Subject(PTRSUB &root, int Nkey){
    if (root!=NULL){
        if (Nkey>root->key)
        	Delete_Subject(root->right,Nkey);
        else if (Nkey<root->key)
        	Delete_Subject(root->left,Nkey);
        else {	//if (root->quesi4.ID==infor)
        	PTRSUB p1 = root;
			if (p1->right==NULL){// co 1 nhanh con ben trai
				root = p1->left;	
			}
			else if (p1->left==NULL){// co 1 nhanh con ben phai
				root = p1->right;
			}
			else {//cay co 2 nhanh con
				find_left_node(p1,root->right);
			}
			delete p1;
			} 
		}
	else return;
}
int KT_Cau_hoi_da_thi(questList qList, char* subjID){//ho tro xoa cau hoi
	for(int i=0;i<qList.n;i++){
		if(qList.Q[i].done=='T') return 1;
		}
	return 0;
}
int Mon_hoc_co_cau_hoi_da_thi(PTRSUB &root,char* subjID){
	PTRSUB subNode=Search_Subject_MMH(root,subjID);
	if(subNode==NULL) return -1;
	else if(KT_Cau_hoi_da_thi(subNode->subi4.ql,subjID)==1){
		return 1;
	}
	return 0;
}
PTRSUB Search_Subject(PTRSUB &root, int x){    
   PTRSUB p= root;                         
   while (p!= NULL && x!=p->key)
     if(x < p->key)
         p = p->left; 
      else
         p = p->right;
	return p; 
	
	
}
PTRSUB Search_Subject_MMH(PTRSUB &root, char* SubID){
   if(root == NULL) return NULL; 
   const int STACKSIZE = 500;
   PTRSUB Stack[STACKSIZE];
   int sp = -1;	
   PTRSUB p = root;
   while (p != NULL){
      if(strcmp(p->subi4.MAMH,SubID)==0) return p;
      if (p->right != NULL) Stack[++sp]= p->right;
      if (p->left != NULL) p = p->left;
      else if(sp == -1) break;
	  else p = Stack[sp--];
   }
   return NULL;
}
void Free_Subj_List(PTRSUB &root){
	if (root!=NULL){
		Free_Subj_List(root->left);
		Free_Subj_List(root->right);
		delete root;
	}
}
void load_SubList(std::ifstream &filein,PTRSUB &root,int &offset, int &k, int &d){
	int tempLength;
	char buff[10];
	filein >> tempLength;
	offset = taoNutGoc(tempLength);
	subInfor subi4;	
	int nSub=tempLength;
	for(int i=1;i<=nSub;i++){
		filein.getline(buff,10);
		filein.getline(subi4.MAMH,MAX_MAMH);
		filein.getline(subi4.TENMH,MAX_TENMH);
		Init_QuesList(subi4.ql);
		load_QuestList(filein,subi4.ql);
		int tmp=sinhkhoa(offset,k,d);
		Insert_Subject(root,subi4,tmp);
	}
}
int nSub(PTRSUB &root){
	if(root==NULL) return 0;
	return 1 + nSub(root->left) + nSub(root->right);
}
void save_Subject(std::ofstream &fileout, PTRSUB &root){
	if(root == NULL) return;
	fileout<<root->subi4.MAMH<<endl;
	fileout<<root->subi4.TENMH<<endl;
	save_QuestList(fileout,root->subi4.ql);
	save_Subject(fileout,root->left);
	save_Subject(fileout,root->right);
}
void save_SubjList(std::ofstream &fileout, PTRSUB &root){
  	fileout << nSub(root) <<endl;
	save_Subject(fileout,root);
}


