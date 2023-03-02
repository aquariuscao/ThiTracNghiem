#ifndef _STUDENT_TEST
#define _STUDENT_TEST
#include <fstream>
//Danh sach cau tra loi - tuyen tinh
struct answer{
    int ID;
	char TRALOI; 
};
typedef answer* PTRA;
struct test{
	int nMin;
	int n;
	PTRA answers;
};
void set_test(test &testif, int nQues);
PTRA alloc_AList(int n);
void free_AList(PTRA &answers);
int load_test(std::ifstream& filein, test &testif);
void save_test(std::ofstream& fileout, const test &testif);
#endif
