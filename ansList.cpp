#include "ansList.h"
PTRA alloc_AList(int n){//cap phat dong
	if(n<=0) return NULL;
	PTRA answers = new answer[n];
	return answers;
}
void free_AList(PTRA &answers){
    if(answers!=NULL) delete[] answers;	
}
int load_test(std::ifstream& filein, test& testif){
	filein.read((char*)&testif.nMin,sizeof(testif.nMin));
	filein.read((char*)&testif.n,sizeof(testif.n));
	testif.answers = alloc_AList(testif.n);
	if(testif.answers == NULL) return 0;         
	filein.read((char*)testif.answers,testif.n*sizeof(*(testif.answers)));
	return 1;
}   
void save_test(std::ofstream& fileout, const test &testif){
	fileout.write((const char*)&testif.nMin,sizeof(testif.nMin));
	fileout.write((const char*)&testif.n,sizeof(testif.n));
	fileout.write((const char*)testif.answers,testif.n*sizeof(*(testif.answers)));
}
