#include "classList.h"
#include "subjList.h"
#include "graphic.h"
#include "prcstring.h"
#include <iostream>
#include <ctime>								  				  
using namespace std;

char studentMenu[][50]={ "THI TRAC NGHIEM",
                         "XEM KET QUA"};
char lecturerMenu[][50]={ "DANH SACH LOP & SV",
						  "DANH SACH MON HOC & CH",
						  "THI TRAC NGHIEM",
						  "XEM DIEM THI"};
int lengthlecMenu[]	= {311, 334,286,277};		
int lengthStuMenu[] = {300,300};					  
char classTable[][50]={ "STT",
                        "MA LOP",
						"TEN LOP",
						"DSSV"};
int alignsCTable[]={CENTER,LEFT,LEFT,CENTER};											
int lengthsCTable[]={100,170,350,100};
char studentTable[][50]={ "STT",
						  "MA SV",
                          "HO VA TEN",
						  "PHAI",
						  "PASSWORD"};
int alignsStuTable[]= {CENTER,LEFT,LEFT,LEFT,LEFT};											
int lengthsStuTable[]= {100,150,340,100,150};
char subjTable[][50]={ "STT",
                        "MA MH",
						"TEN MON HOC",
						"DSCH"};
int alignsSubjTable[]={CENTER,LEFT,LEFT,CENTER};											
int lengthsSubjTable[]={100,120,400,100};
char markTable1[][50]={ "STT",
                        "MA SV",
						"TEN SV",
						"DIEM",
						"CTBT"};
int alignsMarkTable1[]={CENTER,LEFT,LEFT,CENTER,CENTER};											
int lengthsMarkTable1[]={100,150,360,120,120};			
char markTable2[][50]={ "STT",
                        "MA MH",
						"TEN MON HOC",
						"DIEM",
						"CTBT"};
int alignsMarkTable2[]={CENTER,LEFT,LEFT,CENTER,CENTER};											
int lengthsMarkTable2[]={100,120,400,100,120};	
char quesTable[][50]={ "ID",
                        "NOI DUNG"};
int alignsQuesTable[]={CENTER,LEFT};											
int lengthsQuesTable[]={100,500};

int Key(){//bat phim nhap vao
	int key = getch();
	if(key == 0){
		key = getch();
		return key + 2000;
	} 
	return key;
}
time_t dead_line(int seconds){// tinh thoi gian ket thuc 
	time_t time_now = time(0);// thoi gian tinh bang giay - là so giây dã trôi qua tu 1/1/1970
	return time_now + seconds;// thoi gian lam bai + thoi gian hien tai 
}
int remaining_time(time_t deadline){//tinh thoi gian lam bai con lai
	time_t time_now = time(0);
	return deadline - time_now;
}
int get_index(int indexs[],int n_index,int value){//lay ra vi tri theo gia tri
	for(int i=0;i<n_index;i++){
		if(indexs[i]==value) return i;
	}
	return -1;
}
void HO_TEN_MASV(stuInfor &stuif, char* buff){// chi dung cho giao dien
	strcpy(buff,stuif.HO);
	strcat(buff," ");
	strcat(buff,stuif.TEN);
	strcat(buff," - ");
	strcat(buff,stuif.MASV);
	settextstyle(font_text,0,sizeM);
}


//TABLE VA COMBOBOX
void set_CTable(classList &CList, rowTable* ROWTBs,int* indexs,int n_index,int page, int& nRow,int nPageTable,int last_nPageTable,BUTTON& page_after, BUTTON& page_before,int idx_class, char* page_text){//tao bang danh sach lop
	AREA area;
	BUTTON button;
	BUTTON buttons[3];
	char buff[10];
	int x, y = w_win/3+55, length_text, idx_choose = get_index(indexs,n_index,idx_class);
	int old_nRow = nRow;
	nRow = (nPageTable==0)?0:((nPageTable == page)?n_index-((page-1)*10):10);
	if(page!=nPageTable) draw_button(page_after);
	if(page>1) draw_button(page_before);
	strcpy(page_text,itoa(page,buff,decimal));
	settextstyle(font_text,0,sizeM);
	out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(buff),w_win-67,page_text,white,black);
	out_text_xy(l_win/4+155,w_win-67,(char*)"/",3,black);
	out_text_xy(l_win/4+170,w_win-67,itoa(nPageTable,buff,decimal),3,black);
	if(nPageTable!=0) out_text_xy(l_win/16+140,w_win/4-17+30,(char*)"Tu khoa toi da 50 ki tu",3,3);
	if(nPageTable == 0 && last_nPageTable!=0){
		settextstyle(font_text,0,sizeS-1);
		out_text_xy(l_win/16+140,w_win/4-17+30,(char*)"Khong co ket qua nao",3,red);
	}
	if(page <= 1) delete_button(page_before,3);
	if(page == nPageTable && nRow!= 10){
		delete_button(page_after,3);
		create_1_bar(l_win/16-1,w_win/3+56+nRow*30,721,30*(10-nRow),3,3); 
	}					
	for(int i=0;i<nRow;i++){
		if(strcmp(CList.classes[indexs[(page-1)*10+i]]->classi4.MALOP,ROWTBs[i].buttons[1].text)==0&&i!=idx_choose%10){
		    if(i >= old_nRow) draw_rowTable2(ROWTBs[i]);
		}
	    else{
	    	x = 0;
   			set_area(area,l_win/16,y,lengthsCTable[0],30);
   		   	set_button(button, area, itoa((page-1)*10+i+1,buff,decimal),sizeM-1,black, alignsCTable[0],black,3);
   		   	buttons[0] = button;
   		   	draw_button(buttons[0]);
   		   	x += lengthsCTable[0];
   	   		length_text = strlen(CList.classes[indexs[(page-1)*10+i]]->classi4.MALOP);
   	   		if(length_text*(lth_sizeM-2)+20<lengthsCTable[1]) create_1_bar(l_win/16+x+10+length_text*(lth_sizeM-2),y+1,lengthsCTable[1]-10-length_text*(lth_sizeM-2),30-2,3,3);
  	 		set_area(area,l_win/16+x,y,lengthsCTable[1],30);
   			set_button(button, area, CList.classes[indexs[(page-1)*10+i]]->classi4.MALOP,sizeM-1,black, alignsCTable[1],black,3);	
   			buttons[1] = button;
   			if(i==idx_choose%10) draw_button(buttons[1]);
   			else draw_button2(buttons[1]);
	   		x += lengthsCTable[1];
	   		length_text = strlen(CList.classes[indexs[(page-1)*10+i]]->classi4.TENLOP);
   	   		if(length_text*(lth_sizeM-2)+20<lengthsQuesTable[2]) create_1_bar(l_win/16+x+10+length_text*(lth_sizeM-2),y+1,lengthsCTable[2]-10-length_text*(lth_sizeM-2),30-2,3,3);
			set_area(area,l_win/16+x,y,lengthsCTable[2],30);
	  		set_button(button, area, CList.classes[indexs[(page-1)*10+i]]->classi4.TENLOP,sizeM-1,black, alignsCTable[2],black,3);
	   		buttons[2] = button;
	   		if(i==idx_choose%10) draw_button(buttons[2]);
   			else draw_button2(buttons[2]);
	   		set_rowTable(ROWTBs[i],buttons,3);
	   		x+=lengthsCTable[2];
		}
		setcolor(black);
		rectangle(l_win/16+620,w_win/3+55+30*i,l_win/16+620+100,w_win/3+55+30*i+30);
		settextstyle(font_text,0,sizeM-1);
		out_text_xy(l_win/16+645,w_win/3+60+30*i,(char*)"DSSV",3,darkBlue);
		y += 30;
	}
}
void set_SubjTable(PTRSUB &root, rowTable* ROWTBs,int IDs[],int n_index,int page, int& nRow,int nPageTable,int last_nPageTable,BUTTON& page_after, BUTTON& page_before,int idx_subject, char* page_text){//bang danh sach mon hoc
	AREA area;
	PTRSUB subNode;
	BUTTON button;
	BUTTON buttons[3];
	char buff[10];
	int x, y = w_win/3+55, length_text, idx_choose = get_index(IDs, n_index, idx_subject);
	int old_nRow = nRow;
	nRow = (nPageTable==0)?0:((nPageTable == page)?n_index-((page-1)*10):10);
	if(page!=nPageTable) draw_button(page_after);
	if(page>1) draw_button(page_before);
	strcpy(page_text,itoa(page,buff,decimal));
	settextstyle(font_text,0,sizeM);
	out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(buff),w_win-67,page_text,white,black);
	out_text_xy(l_win/4+155,w_win-67,(char*)"/",3,black);
	out_text_xy(l_win/4+170,w_win-67,itoa(nPageTable,buff,decimal),3,black);
	if(nPageTable!=0) out_text_xy(l_win/16+140,w_win/4-17+30,(char*)"Tu khoa toi da 50 ki tu",3,3);
	if(nPageTable == 0 && last_nPageTable!=0){
		settextstyle(font_text,0,sizeS-1);
		out_text_xy(l_win/16+140,w_win/4-17+30,(char*)"Khong co ket qua nao",3,darkRed);
	}
	if(page <= 1) delete_button(page_before,3);
	if(page == nPageTable && nRow!= 10){
		delete_button(page_after,3);
		create_1_bar(l_win/16-1,w_win/3+56+nRow*30,721,30*(10-nRow),3,3); 
	}					
	for(int i=0;i<nRow;i++){
		subNode = Search_Subject(root,IDs[(page-1)*10+i]);
		if(stricmp(subNode->subi4.MAMH,ROWTBs[i].buttons[1].text)==0&&i!=idx_choose%10){
		    if(i>= old_nRow) draw_rowTable2(ROWTBs[i]);
		}
	    else{
	    	x = 0;
   			set_area(area,l_win/16,y,lengthsSubjTable[0],30);
   		   	set_button(button, area, itoa((page-1)*10+i+1,buff,decimal),sizeM-1,black, alignsSubjTable[0],black,3);
   		   	buttons[0] = button;
   		   	draw_button(buttons[0]);
   		   	x += lengthsSubjTable[0];
   	   		length_text = strlen(subNode->subi4.MAMH);
   	   		if(length_text*(lth_sizeM-2)+20<lengthsSubjTable[1]) create_1_bar(l_win/16+x+10+length_text*(lth_sizeM-2),y+1,lengthsSubjTable[1]-10-length_text*(lth_sizeM-2),30-2,3,3);
  	 		set_area(area,l_win/16+x,y,lengthsSubjTable[1],30);
   			set_button(button, area, subNode->subi4.MAMH,sizeM-1,black, alignsSubjTable[1],black,3);	
   			buttons[1] = button;
   			if(i==idx_choose%10) draw_button(buttons[1]);
   			else draw_button2(buttons[1]);
	   		x += lengthsSubjTable[1];
	   		length_text = strlen(subNode->subi4.TENMH);
   	   		if(length_text*(lth_sizeM-2)+20<lengthsSubjTable[2]) create_1_bar(l_win/16+x+10+length_text*(lth_sizeM-2),y+1,lengthsSubjTable[2]-10-length_text*(lth_sizeM-2),30-2,3,3);
			set_area(area,l_win/16+x,y,lengthsSubjTable[2],30);
	  		set_button(button, area, subNode->subi4.TENMH,sizeM-1,black, alignsSubjTable[2],black,3);
	   		buttons[2] = button;
	   		if(i==idx_choose%10) draw_button(buttons[2]);
   			else draw_button2(buttons[2]);
	   		set_rowTable(ROWTBs[i],buttons,3);
	   		x+=lengthsSubjTable[2];
		}
		setcolor(black);
		rectangle(l_win/16+620,w_win/3+55+30*i,l_win/16+620+100,w_win/3+55+30*i+30);
		settextstyle(font_text,0,sizeM-1);
		out_text_xy(l_win/16+645,w_win/3+60+30*i,(char*)"DSCH",3,darkBlue);
		y += 30;
	}
}
void set_Quest_Table2(questList &qList, BUTTON Questions[],int page, int nPage,int Quest, int nQuestion,int& nRow,PTRA answers){//bang cau hoi da co dap an 
    char buff[10];
    int idx_Q;
	if(page<nPage) nRow = 15;
	else nRow = nQuestion - (page-1)*15;
	AREA area = Questions[(Quest-1)%15].area;
	for(int i=0;i<15;i++){
		if(i<nRow){
			strcpy(Questions[i].text+4,itoa((page-1)*15+1+i,buff,decimal));
			idx_Q = Search_Quest(qList,answers[(page-1)*15+i].ID);
			if(qList.Q[idx_Q].DapAn == answers[(page-1)*15+i].TRALOI) highlight_button(Questions[i],darkGreen,white,white);
			else highlight_button(Questions[i],darkRed,white,white);
		}
		else highlight_button(Questions[i],3,3,3);
	}
	setcolor(darkBlue);
	rectangle(area.x,area.y,area.x+area.length,area.y+area.width);
	settextstyle(font_text,0,sizeM);
	if(Quest>1) out_text_xy(l_win/4-50,w_win/2+205,(char*)"CAU TRUOC",3,darkBlue);
	else out_text_xy(l_win/4-50,w_win/2+205,(char*)"CAU TRUOC",3,3);
	if(Quest<nQuestion) out_text_xy(l_win/4+370,w_win/2+205,(char*)"CAU SAU",3,darkBlue);
	else out_text_xy(l_win/4+370,w_win/2+205,(char*)"CAU SAU",3,3);
}
void set_Quest_Table(BUTTON Questions[],int page, int nPage,int Quest, int nQuestion,int& nRow,PTRA answers){//bang cau hoi de thi
    char buff[10];
	if(page<nPage) nRow = 15;
	else nRow = nQuestion - (page-1)*15;
	AREA area = Questions[(Quest-1)%15].area;
	for(int i=0;i<15;i++){
		if(i<nRow){
			strcpy(Questions[i].text+4,itoa((page-1)*15+1+i,buff,decimal));
			if(answers[(page-1)*15+i].TRALOI!='X') highlight_button(Questions[i],grey,white,white);
			else draw_button(Questions[i]);
		}
		else highlight_button(Questions[i],3,3,3);
	}
	setcolor(darkBlue);
	rectangle(area.x,area.y,area.x+area.length,area.y+area.width);
	settextstyle(font_text,0,sizeM);
	if(Quest>1) out_text_xy(l_win/4-50,w_win/2+205,(char*)"CAU TRUOC",3,darkBlue);
	else out_text_xy(l_win/4-50,w_win/2+205,(char*)"CAU TRUOC",3,3);
	if(Quest<nQuestion) out_text_xy(l_win/4+370,w_win/2+205,(char*)"CAU SAU",3,darkBlue);
	else out_text_xy(l_win/4+370,w_win/2+205,(char*)"CAU SAU",3,3);
}
void set_quesTable(questList &qList, rowTable* ROWTBs,int IDs[],int n_index,int page, int& nRow,int nPageTable,int last_nPageTable,BUTTON& page_after, BUTTON& page_before,int ID, char* page_text){//tim kiem cau hoi
	AREA area;
	BUTTON button;
	BUTTON buttons[2];
	char buff[10];
	int x, y = w_win/3+55, length_text, idx_choose = get_index(IDs,n_index,ID);
	int old_nRow = nRow;
	nRow = (nPageTable==0)?0:((nPageTable == page)?n_index-((page-1)*10):10);
	if(page!=nPageTable) draw_button(page_after);
	if(page>1) draw_button(page_before);
	strcpy(page_text,itoa(page,buff,decimal));
	settextstyle(font_text,0,sizeM);
	out_text_xy(l_win/4-20-(lth_sizeM/2)*strlen(buff),w_win-67,page_text,white,black);
	out_text_xy(l_win/4+35,w_win-67,(char*)"/",3,black);
	out_text_xy(l_win/4+50,w_win-67,itoa(nPageTable,buff,decimal),3,black);
	if(nPageTable!=0) out_text_xy( l_win/16-30+strlen("TIM KIEM:")*lth_sizeM+7,w_win/4+30,(char*)"                       ",3,3);
	if(nPageTable == 0 &&last_nPageTable!=0){
		settextstyle(font_text,0,sizeS-1);
		out_text_xy(l_win/16-30+strlen("TIM KIEM:")*lth_sizeM+7,w_win/4+30,(char*)"Khong co ket qua nao",3,darkRed);
	}
	if(page <= 1) delete_button(page_before,3);
	if(page == nPageTable ){
	    delete_button(page_after,3);
	    create_1_bar(21,w_win/3+56+nRow*30,lengthsQuesTable[0]+lengthsQuesTable[1]+1,30*(10-nRow),3,3); 
	}				
	for(int i=0;i<nRow;i++){
		itoa(IDs[(page-1)*10+i],buff,decimal);
		if(strcmp(buff,ROWTBs[i].buttons[0].text)==0&&i!=idx_choose%10){
		    if(i >= old_nRow) draw_rowTable2(ROWTBs[i]);
		}
	    else{
	    	x = 0;
  	 		set_area(area,22,y,lengthsQuesTable[0],30);
   			set_button(button, area,buff,sizeM-1,black, alignsQuesTable[0],black,3);
			buttons[0] = button;	
   		//	if(i==idx_choose%10) 
		   draw_button(buttons[0]);
	   	//	else draw_button2(buttons[0]);
	   		x += lengthsQuesTable[0];
	   		length_text = strlen(qList.Q[Search_Quest(qList,IDs[(page-1)*10+i])].NoiDung);
  	   		if(length_text*(lth_sizeM-2)+20<lengthsQuesTable[1]) create_1_bar(22+x+10+length_text*(lth_sizeM-2),y+1,lengthsQuesTable[1]-10-length_text*(lth_sizeM-2),30-2,3,3);
			set_area(area,22+x,y,lengthsQuesTable[1],30);
	  		set_button(button, area, qList.Q[Search_Quest(qList,IDs[(page-1)*10+i])].NoiDung,sizeM-1,black, alignsQuesTable[1],black,3);
	   		buttons[1] = button;
	   		if(i==idx_choose%10) draw_button(buttons[1]);
	   		else draw_button2(buttons[1]);
   			set_rowTable(ROWTBs[i],buttons,2);
		}
		y += 30;
	}
}
void set_StuTable(PTRS SFirst, rowTable* ROWTBs,int* indexs,int n_index,int page, int& nRow,int nPageTable,int last_nPageTable,BUTTON& page_after, BUTTON& page_before,int idx_student, char* page_text){//bang danh sach sinh vien
	AREA area;
	BUTTON button;
	BUTTON buttons[5];
	char buff[10], HO_TEN[MAX_HO+MAX_TEN+1];
	PTRS SNode;
	int x, y = w_win/3+55, length_text, idx_choose = get_index(indexs,n_index,idx_student);
	int old_nRow = nRow;
	nRow = (nPageTable==0)?0:((nPageTable == page)?n_index-((page-1)*10):10);
	if(page!=nPageTable) draw_button(page_after);
	if(page>1) draw_button(page_before);
	strcpy(page_text,itoa(page,buff,decimal));
	settextstyle(font_text,0,sizeM);
	out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(buff),w_win-67,page_text,white,black);
	out_text_xy(l_win/4+155,w_win-67,(char*)"/",3,black);
	out_text_xy(l_win/4+170,w_win-67,itoa(nPageTable,buff,decimal),3,black);
	if(nPageTable!=0) out_text_xy(l_win/16+140,w_win/4-17+30,(char*)"                       ",3,3);
	if(nPageTable == 0 &&last_nPageTable!=0){
		settextstyle(font_text,0,sizeS-1);
		out_text_xy(l_win/16+140,w_win/4-17+30,(char*)"Khong co ket qua nao",3,darkRed);
	}
	if(page <= 1) delete_button(page_before,3);
	if(page == nPageTable && nRow!= 10){
	    delete_button(page_after,3);
	    create_1_bar(21,w_win/3+56+nRow*30,842,30*(10-nRow),3,3); 
	}				
	for(int i=0;i<nRow;i++){
		SNode = get_student_idx(SFirst,indexs[(page-1)*10+i]);
		if(strcmp(SNode->stui4.MASV,ROWTBs[i].buttons[1].text)==0&&i!=idx_choose%10){
		    if(i >= old_nRow) draw_rowTable2(ROWTBs[i]);
		}
	    else{
	    	x = 0;
   			set_area(area,22,y,lengthsStuTable[0],30);
   		   	set_button(button, area, itoa((page-1)*10+i+1,buff,decimal),sizeM-1,black, alignsStuTable[0],black,3);
   		   	buttons[0] = button;
   		   	draw_button(buttons[0]);
   		   	x += lengthsStuTable[0];
   	   		length_text = strlen(SNode->stui4.MASV);
   	   		if(length_text*(lth_sizeM-2)+20<lengthsStuTable[1]) create_1_bar(22+x+10+length_text*(lth_sizeM-2),y+1,lengthsStuTable[1]-10-length_text*(lth_sizeM-2),30-2,3,3);
  	 		set_area(area,22+x,y,lengthsStuTable[1],30);
   			set_button(button, area, SNode->stui4.MASV,sizeM-1,black, alignsStuTable[1],black,3);
			buttons[1] = button;	
   			if(i==idx_choose%10) draw_button(buttons[1]);
	   		else draw_button2(buttons[1]);
	   		x += lengthsStuTable[1];
	   		strcpy(HO_TEN,SNode->stui4.HO);
	   		strcat(HO_TEN," ");
	   		strcat(HO_TEN,SNode->stui4.TEN);
	   		length_text = strlen(HO_TEN);
   	   		if(length_text*(lth_sizeM-2)+20<lengthsStuTable[2]) create_1_bar(22+x+10+length_text*(lth_sizeM-2),y+1,lengthsStuTable[2]-10-length_text*(lth_sizeM-2),30-2,3,3);
			set_area(area,22+x,y,lengthsStuTable[2],30);
	  		set_button(button, area, HO_TEN,sizeM-1,black, alignsStuTable[2],black,3);
	   		buttons[2] = button;
	   		if(i==idx_choose%10) draw_button(buttons[2]);
	   		else draw_button2(buttons[2]);
	   		x+=lengthsStuTable[2];
	   		length_text = strlen(SNode->stui4.PHAI);
   	   		if(length_text*(lth_sizeM-2)+20<lengthsStuTable[3]) create_1_bar(22+x+10+length_text*(lth_sizeM-2),y+1,lengthsStuTable[3]-10-length_text*(lth_sizeM-2),30-2,3,3);
  	 		set_area(area,22+x,y,lengthsStuTable[3],30);
   			set_button(button, area, SNode->stui4.PHAI,sizeM-1,black, alignsStuTable[3],black,3);	
   			buttons[3] = button;
   			if(i==idx_choose%10) draw_button(buttons[3]);
	   		else draw_button2(buttons[3]);
	   		x += lengthsStuTable[3];
	   		length_text = strlen(SNode->stui4.password);
   	   		if(length_text*(lth_sizeM-2)+20<lengthsStuTable[4]) create_1_bar(22+x+10+length_text*(lth_sizeM-2),y+1,lengthsStuTable[4]-10-length_text*(lth_sizeM-2),30-2,3,3);
  	 		set_area(area,22+x,y,lengthsStuTable[4],30);
   			set_button(button, area, SNode->stui4.password,sizeM-1,black, alignsStuTable[4],black,3);
			buttons[4] = button;	
   			if(i==idx_choose%10) draw_button(buttons[4]);
	   		else draw_button2(buttons[4]);
   			set_rowTable(ROWTBs[i],buttons,5);
		}
		y += 30;
	}
}
void set_markTable1(PTRS SFirst,PTRSUB &subNode, rowTable* ROWTBs,int* indexs,int n_index,int page, int& nRow,int nPageTable,int last_nPageTable,BUTTON& page_after, BUTTON& page_before, char* page_text){//bang diem diem cua lop theo mon hoc
	AREA area;
	BUTTON button;
	BUTTON buttons[4];
	char buff[10], HO_TEN[MAX_HO+MAX_TEN+1];
	PTRS SNode;
	int x, y = w_win/3+55, length_text;
	float mark;
	int old_nRow = nRow;
	nRow = (nPageTable==0)?0:((nPageTable == page)?n_index-((page-1)*10):10);
	if(page!=nPageTable) draw_button(page_after);
	if(page>1) draw_button(page_before);
	strcpy(page_text,itoa(page,buff,decimal));
	settextstyle(font_text,0,sizeM);
	out_text_xy(l_win/4+250-(lth_sizeM/2)*strlen(buff),w_win-67,page_text,white,black);
	out_text_xy(l_win/4+305,w_win-67,(char*)"/",3,black);
	out_text_xy(l_win/4+320,w_win-67,itoa(nPageTable,buff,decimal),3,black);
	if(nPageTable!=0) out_text_xy(l_win/16+290,w_win/4-17+30,(char*)"                         ",3,3);
	if(nPageTable == 0 &&last_nPageTable!=0){
		settextstyle(font_text,0,sizeS-1);
		out_text_xy(l_win/16+290,w_win/4-17+30,(char*)"Khong co ket qua nao",3,darkRed);
	}
	if(page <= 1) delete_button(page_before,3);
	if(page == nPageTable && nRow!= 10){
	    delete_button(page_after,3);
	    create_1_bar(171,w_win/3+56+nRow*30,852,30*(10-nRow),3,3); 
	}				
	for(int i=0;i<nRow;i++){
		SNode = get_student_idx(SFirst,indexs[(page-1)*10+i]);
		mark = mark_of_subj(SNode->MFirst,subNode->subi4.MAMH);
		if(strcmp(SNode->stui4.MASV,ROWTBs[i].buttons[1].text)==0){
		    if(i >= old_nRow) draw_rowTable2(ROWTBs[i]);
		}
	    else{
	    	x = 0;
   			set_area(area,172,y,lengthsMarkTable1[0],30);
   		   	set_button(button, area, itoa((page-1)*10+i+1,buff,decimal),sizeM-1,black, alignsMarkTable1[0],black,3);
   		   	buttons[0] = button;
   		   	draw_button(buttons[0]);
   		   	x += lengthsMarkTable1[0];
   	   		length_text = strlen(SNode->stui4.MASV);
   	   		if(length_text*(lth_sizeM-2)+20<lengthsMarkTable1[1]) create_1_bar(172+x+10+length_text*(lth_sizeM-2),y+1,lengthsMarkTable1[1]-10-length_text*(lth_sizeM-2),30-2,3,3);
  	 		set_area(area,172+x,y,lengthsMarkTable1[1],30);
   			set_button(button, area, SNode->stui4.MASV,sizeM-1,black, alignsMarkTable1[1],black,3);
			buttons[1] = button;	
	   		draw_button2(buttons[1]);
	   		x += lengthsMarkTable1[1];
	   		strcpy(HO_TEN,SNode->stui4.HO);
	   		strcat(HO_TEN," ");
	   		strcat(HO_TEN,SNode->stui4.TEN);
	   		length_text = strlen(HO_TEN);
   	   		if(length_text*(lth_sizeM-2)+20<lengthsMarkTable1[2]) create_1_bar(172+x+10+length_text*(lth_sizeM-2),y+1,lengthsMarkTable1[2]-10-length_text*(lth_sizeM-2),30-2,3,3);
			set_area(area,172+x,y,lengthsMarkTable1[2],30);
	  		set_button(button, area, HO_TEN,sizeM-1,black, alignsMarkTable1[2],black,3);
	   		buttons[2] = button;
	   		draw_button2(buttons[2]);
	   		x+=lengthsMarkTable1[2];
	   		if(mark==-1) strcpy(buff,"Chua thi");
	   		else if (mark==10) snprintf(buff,5,"%f",mark);
	   		else snprintf(buff,4,"%f",mark);
	   		length_text = strlen(buff);
   	   		if(length_text*(lth_sizeM-2)+20<lengthsMarkTable1[3]) create_1_bar(172+x+10+length_text*(lth_sizeM-2),y+1,lengthsMarkTable1[3]-10-length_text*(lth_sizeM-2),30-2,3,3);
  	 		set_area(area,172+x,y,lengthsMarkTable1[3],30);
   			set_button(button, area, buff,sizeM-1,black, alignsMarkTable1[3],black,3);	
   			buttons[3] = button;
	   		draw_button(buttons[3]);
	   		x += lengthsMarkTable1[3];
   			set_rowTable(ROWTBs[i],buttons,4);
		}
		if(mark!=-1){
			settextstyle(font_text,0,sizeM-1);
			out_text_xy(l_win/16+859,w_win/3+60+30*i,(char*)"CTBT",3,darkBlue);
		}
		setcolor(black);
		rectangle(l_win/16+824,w_win/3+55+30*i,l_win/16+824+120,w_win/3+55+30*i+30);
		y += 30;
	}
}
void set_markTable2(PTRM MFirst,PTRSUB &root, rowTable* ROWTBs,int* indexs,int n_index,int page, int& nRow,int nPageTable,int last_nPageTable,BUTTON& page_after, BUTTON& page_before, char* page_text) {//bang xem diem cua 1 sinh vien
	AREA area;
	BUTTON button;
	BUTTON buttons[4];
	char buff[10];
	PTRM MNode;
	PTRSUB SubNode;
	int x, y = w_win/3+55, length_text, i_TENMH;
	int old_nRow = nRow;
	nRow = (nPageTable==0)?0:((nPageTable == page)?n_index-((page-1)*10):10);
	if(page!=nPageTable) draw_button(page_after);
	if(page>1) draw_button(page_before);
	strcpy(page_text,itoa(page,buff,decimal));
	settextstyle(font_text,0,sizeM);
	out_text_xy(l_win/4+250-(lth_sizeM/2)*strlen(buff),w_win-67,page_text,white,black);
	out_text_xy(l_win/4+305,w_win-67,(char*)"/",3,black);
	out_text_xy(l_win/4+320,w_win-67,itoa(nPageTable,buff,decimal),3,black);
	if(nPageTable!=0) out_text_xy(l_win/16+290,w_win/4-17+30,(char*)"                         ",3,3);
	if(nPageTable == 0 &&last_nPageTable!=0){
		settextstyle(font_text,0,sizeS-1);
		out_text_xy(l_win/16+290,w_win/4-17+30,(char*)"Khong co ket qua nao",3,darkRed);
	}
	if(page <= 1) delete_button(page_before,3);
	if(page == nPageTable && nRow!= 10){
	    delete_button(page_after,3);
	    create_1_bar(171,w_win/3+56+nRow*30,842,30*(10-nRow),3,3); 
	}				
	for(int i=0;i<nRow;i++){
		MNode = get_mark_idx(MFirst,indexs[(page-1)*10+i]);
		SubNode = Search_Subject_MMH(root,MNode->marki4.Mamh);
		if(strcmp(MNode->marki4.Mamh,ROWTBs[i].buttons[1].text)==0){
		    if(i >= old_nRow) draw_rowTable2(ROWTBs[i]);
		}
	    else{
	    	x = 0;
   			set_area(area,172,y,lengthsMarkTable1[0],30);
   		   	set_button(button, area, itoa((page-1)*10+i+1,buff,decimal),sizeM-1,black, alignsMarkTable2[0],black,3);
   		   	buttons[0] = button;
   		   	draw_button(buttons[0]);
   		   	x += lengthsMarkTable2[0];
   	   		length_text = strlen(MNode->marki4.Mamh);
   	   		if(length_text*(lth_sizeM-2)+20<lengthsMarkTable2[1]) create_1_bar(172+x+10+length_text*(lth_sizeM-2),y+1,lengthsMarkTable2[1]-10-length_text*(lth_sizeM-2),30-2,3,3);
  	 		set_area(area,172+x,y,lengthsMarkTable2[1],30);
   			set_button(button, area, MNode->marki4.Mamh,sizeM-1,black, alignsMarkTable2[1],black,3);
			buttons[1] = button;	
	   		draw_button2(buttons[1]);
	   		x += lengthsMarkTable2[1];
	   		PTRSUB subNode1=Search_Subject_MMH(root,MNode->marki4.Mamh);
	   		length_text = strlen(subNode1->subi4.TENMH);
   	   		if(length_text*(lth_sizeM-2)+20<lengthsMarkTable2[2]) create_1_bar(172+x+10+length_text*(lth_sizeM-2),y+1,lengthsMarkTable2[2]-10-length_text*(lth_sizeM-2),30-2,3,3);
			set_area(area,172+x,y,lengthsMarkTable2[2],30);
	  		set_button(button, area, subNode1->subi4.TENMH,sizeM-1,black, alignsMarkTable2[2],black,3);
	   		buttons[2] = button;
	   		draw_button2(buttons[2]);
	   		x+=lengthsMarkTable2[2];
	   		if(MNode->marki4.Diem==10) snprintf(buff,5,"%f",MNode->marki4.Diem);
	   		else snprintf(buff,4,"%f",MNode->marki4.Diem);
	   		length_text = strlen(buff);
   	   		if(length_text*(lth_sizeM-2)+20<lengthsMarkTable1[3]) create_1_bar(172+x+10+length_text*(lth_sizeM-2),y+1,lengthsMarkTable2[3]-10-length_text*(lth_sizeM-2),30-2,3,3);
  	 		set_area(area,172+x,y,lengthsMarkTable2[3],30);
   			set_button(button, area, buff,sizeM-1,black, alignsMarkTable2[3],black,3);	
   			buttons[3] = button;
	   		draw_button(buttons[3]);
	   		x += lengthsMarkTable2[3];
   			set_rowTable(ROWTBs[i],buttons,4);
		}
		setcolor(black);
		rectangle(l_win/16+814,w_win/3+55+30*i,l_win/16+814+120,w_win/3+55+30*i+30);
		settextstyle(font_text,0,sizeM-1);
		out_text_xy(l_win/16+849,w_win/3+60+30*i,(char*)"CTBT",3,darkBlue);
		y += 30;
	}
}
void set_MMHTable(AREA& area_bar,PTRSUB &root,BUTTON buttons[],int *indexs,int n_index, int page,int &nRow,int nPageTable,int last_nPageTable,BUTTON& page_after, BUTTON& page_before){
	//combobox ds mon hoc
	AREA area;
	PTRSUB subNode;
	char MMH_TMH[MAX_MAMH+MAX_TENMH+5]={0};
	int length_text;
	nRow = (nPageTable==0)?0:((nPageTable == page)?n_index-((page-1)*10):10);
	if(page!=nPageTable){
		set_area(page_after.area,area_bar.x+area_bar.length,area_bar.y+area_bar.width+2+30*nRow,30,area_bar.width);
		draw_button(page_after);
	}
	else if(nRow!=10) {
		delete_button(page_after,3);
		create_1_bar(area_bar.x,area_bar.y+area_bar.width+2+30*nRow,area_bar.length+30,30*(10-nRow),3,3); 
	} 
	if(page>1){
		if(nRow<10)  delete_button(page_before,3);
		set_area(page_before.area,area_bar.x,area_bar.y+area_bar.width+2+30*nRow,30,area_bar.width);
	    draw_button(page_before);	
	} 
	else delete_button(page_before,3);
	for(int i=0;i<nRow;i++){
		subNode = Search_Subject(root,indexs[(page-1)*10+i]);
		if(strstr(buttons[i].text,subNode->subi4.MAMH)!=NULL){
		    draw_button(buttons[i]);
		}
	    else{
   			set_area(area,area_bar.x,area_bar.y+area_bar.width+2+30*i,area_bar.length+30,area_bar.width);
   			strcpy(MMH_TMH,subNode->subi4.MAMH);
   			strcat(MMH_TMH," - ");
   			strcat(MMH_TMH,subNode->subi4.TENMH);
   		   	set_button(buttons[i], area, MMH_TMH,sizeM-1,black, LEFT,white,white);
   		   	draw_button(buttons[i]);
		}
	}
}
void set_MLTable(classList& CList,BUTTON buttons[],int *indexs,int n_index, int page,int& nRow,int nPageTable,int last_nPageTable,BUTTON& page_after, BUTTON& page_before){
	//combobox lop
	AREA area;
    int length_text;
	char ML_TL[MAX_MALOP+MAX_TENLOP+5]={0};
	nRow = (nPageTable==0)?0:((nPageTable == page)?n_index-((page-1)*10):10); 	
	if(page==nPageTable && nRow!=10) {
		delete_button(page_after,3);
		create_1_bar(200,w_win/4+60+32+30*nRow,430,30*(10-nRow),3,3); 
	} 
	else if(page!=nPageTable){
		set_area(page_after.area,200+430-30,w_win/4+60+32+30*nRow,30,30);
		draw_button(page_after);
	}
	if(page<=1) delete_button(page_before,3);
	else{
	    if(nRow<10)  delete_button(page_before,3);
	    set_area(page_before.area,200,w_win/4+60+32+30*nRow,30,30);
		draw_button(page_before);	
	}
	for(int i=0;i<nRow;i++){
		if(strstr(buttons[i].text,CList.classes[indexs[(page-1)*10+i]]->classi4.MALOP)!=NULL){
		    draw_button(buttons[i]);
		}
	    else{
   			set_area(area,200,w_win/4+60+32+30*i,430,30);
   			strcpy(ML_TL,CList.classes[indexs[(page-1)*10+i]]->classi4.MALOP);
   			strcat(ML_TL," - ");
   			strcat(ML_TL,CList.classes[indexs[(page-1)*10+i]]->classi4.TENLOP);
   		   	set_button(buttons[i], area, ML_TL,sizeM-1,black, LEFT,white,white);
   		   	draw_button(buttons[i]);
		}
	}
}
void set_MSVTable(PTRS SFirst,BUTTON buttons[],int *indexs,int n_index, int page,int& nRow,int nPageTable,int last_nPageTable,BUTTON& page_after,BUTTON& page_before){
	//combo sinh vien - chi co trong xem diem
	AREA area;
    PTRS SNode;
	char MSV_TSV[MAX_MASV+MAX_TEN+MAX_HO+5]={0};
	nRow = (nPageTable==0)?0:((nPageTable == page)?n_index-((page-1)*10):10);
	if(page!=nPageTable){
		set_area(page_after.area,740+430-30,w_win/4+60+32+30*nRow,30,30);
		draw_button(page_after);
	}
	else if(nRow!=10) {
		delete_button(page_after,3);
		create_1_bar(740,w_win/4+60+32+30*nRow,430,30*(10-nRow),3,3); 
	} 
	if(page>1){
		if(nRow<10)  delete_button(page_before,3);
		set_area(page_before.area,740,w_win/4+60+32+30*nRow,30,30);
	    draw_button(page_before);	
	} 
	else delete_button(page_before,3);
	for(int i=0;i<nRow;i++){
		SNode = get_student_idx(SFirst,indexs[(page-1)*10+i]);
		if(strstr(buttons[i].text,SNode->stui4.MASV)!=NULL){
		    draw_button(buttons[i]);
		}
	    else{
   			set_area(area,740,w_win/4+60+32+30*i,430,30);
   			strcpy(MSV_TSV,SNode->stui4.MASV);
   			strcat(MSV_TSV," - ");
   			strcat(MSV_TSV,SNode->stui4.HO);
   			strcat(MSV_TSV," ");
   			strcat(MSV_TSV,SNode->stui4.TEN);
   		   	set_button(buttons[i], area, MSV_TSV,sizeM-1,black, LEFT,white,white);
   		   	draw_button(buttons[i]);
		}
	}
}

//GIAO DIEN SINH VIEN - CHO GV XEM
void make_string_student(PTRS SNode,char* buff){//HO TRO TIM KIEM SINH VIEN
	strcpy(buff,SNode->stui4.HO);
	strcat(buff,SNode->stui4.TEN);
	strcat(buff,SNode->stui4.MASV);
	strcat(buff,SNode->stui4.PHAI);
	strcat(buff,SNode->stui4.password);
}
void get_index_StuList(PTRS SFirst, int* indexs,int& n_index, char* search_text){//HAM TIM KIEM SINH VIEN
	n_index = 0;
	char buff[MAX_HO+MAX_TEN+MAX_MASV+MAX_PHAI+MAX_PASS+1], buff2[MAX_HO+MAX_TEN+MAX_MASV+MAX_PHAI+MAX_PASS+1];
	strcpy(buff,search_text);
	delete_blks_str(buff);
	upper_str(buff);
	int i = 0;
	for(PTRS SNode = SFirst; SNode!= NULL ; SNode = SNode->Next){
		make_string_student(SNode,buff2);
		delete_blks_str(buff2);
		upper_str(buff2);
		if(strstr(buff2,buff)!=NULL) indexs[n_index++] = i;
		i++;
	}
}
void stuList_interface(){//danh sach sinh vien- gv xem
	settextstyle(font_text,0,sizeM);
	out_text_xy(l_win/16,w_win/4-17,(char *)"TIM KIEM:",3,black);
	out_text_xy(l_win/2+270,w_win/3-40,(char*)"MA SV:",3,black);
	out_text_xy(l_win/2+270,w_win/3+20,(char*)"HO:",3,black);
	out_text_xy(l_win/2+480,w_win/3+20,(char*)"TEN:",3,black);
	out_text_xy(l_win/2+270,w_win/3+170,(char*)"PASSWORD:",3,black);
	out_text_xy(l_win/2+270,w_win/3+110,(char*)"PHAI:",3,black);
	out_text_xy(l_win/2+400,w_win/3+110,(char*)"Nam",3,darkBlue);
	out_text_xy(l_win/2+500,w_win/3+110,(char*)"Nu",3,darkBlue);
	settextstyle(font_text,0,sizeM+1);
	out_text_xy(l_win/2+295,w_win/5-10,(char*)"THONG TIN SV",3,black);
	settextstyle(font_text,0,sizeS);
	out_text_xy(l_win/16,w_win/3,(char*)"Click chuot trai tai 1 dong de chinh sua hoac xoa",3,darkRed);
	create_1_bar(l_win/2+360,w_win/3-42,170,30,white,white);
	create_1_bar(l_win/2+270,w_win/3+48,200,30,white,white);
	create_1_bar(l_win/2+480,w_win/3+48,100,30,white,white);
    create_1_bar(l_win/2+400,w_win/3+168,170,30,white,white);
    create_1_bar(l_win/4+50,w_win-70,100,30,white,white);
    setcolor(darkRed);
	rectangle(l_win/2+270,w_win/2+170,l_win/2+580,w_win/2+280);
	setcolor(black);
	rectangle(l_win/2+275,w_win/2+175,l_win/2+575,w_win/2+275);
	create_table(22,w_win/3+25,lengthsStuTable,30,5,1,studentTable,sizeM,black,darkWhite,black);
}
void student_List(classList& CList,PTRC& CLASS,BUTTON Menu[],int& tt){
	stuList_interface(); 
	settextstyle(font_text,0,sizeM-1);
	out_text_xy(l_win/100+16,w_win/7+10,CLASS->classi4.MALOP,3,darkBlue);
    char ch, search_text[MAX_TENLOP+MAX_MALOP+2] ={0}, LName_text[MAX_HO+1]={0}, SID_text[MAX_MASV+1]={0}, FName_text[MAX_TEN+1]={0},sex[MAX_PHAI+1]={0},PW_text[MAX_PASS+1]={0},buff[10]={0},SID_text2[MAX_MALOP+1], page_text[10];
	int x, y, hover=-1, j, s=0, sub_tt , key,sub_page = 1, cursor_pos_search = 0, idx_start_search=0, idx_search = 0;
	int cursor_pos_MSV = 0, cursor_pos_LN = 0, cursor_pos_FN = 0, cursor_pos_PW = 0, idx_start_LN = 0, idx_start_FN = 0, idx_LN= 0, idx_FN = 0, print_s = 0, idx_student=-1, cursor_pos_page =0;
	int choose = 0, n = T_cursor+1, page = 1, indexs[MAX_STD+1]={-1}, n_index, nRow =0,nPageTable,last_nPageTable=-1, page_tmp, is_fix =0;
	AREA studentID, LName, FName, password, pageArea;
	CTick male, female;
	BUTTON exit, page_after, page_before, bar_search, clear, THEM, LUU, XOA, subClear, Return;
	get_index_StuList(CLASS->SFirst,indexs,n_index,search_text);
	set_nPageTable(nRow,nPageTable,n_index,page,1);
	rowTable ROWTBs[10]={};
	set_buttons_StuList(exit,page,nRow, page_after,page_before, nPageTable,bar_search,clear, studentID,LName,FName,password,THEM,LUU,XOA,subClear,pageArea,male,female,Return);
	set_StuTable(CLASS->SFirst, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_student,page_text);
    PTRS SNode,SNode_tmp = NULL;
	stuInfor stuif;
	while(1){
		delay(1);
		if(s && print_s) inform1(s,sub_tt,SID_text2,print_s);
		if(choose==1) print_cursor(l_win/16+140+cursor_pos_search*(lth_sizeM-2),w_win/4-16,n);
		else if(choose==2) print_cursor(l_win/2+367+cursor_pos_MSV*(lth_sizeM-2),w_win/3-37,n);
		else if(choose==3) print_cursor(l_win/2+277+cursor_pos_LN*(lth_sizeM-2),w_win/3+53,n);
		else if(choose==4) print_cursor(l_win/2+487+cursor_pos_FN*(lth_sizeM-2),w_win/3+53,n);
		else if(choose==5) print_cursor(l_win/2+407+cursor_pos_PW*(lth_sizeM-2),w_win/3+173,n);
		else if(choose==7) print_cursor(l_win/4+100-strlen(page_text)/2.0*(lth_sizeM)+cursor_pos_page*lth_sizeM,w_win-65,n);
		if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE,x,y);
			set_hover_CList(Menu, ROWTBs,hover,j,tt,x,y,nRow,clear,LUU,subClear,THEM,XOA);
	        if(j!=hover&&j!=-1){
	        	if(j<nLecMenu) draw_button(Menu[j]);
	        	else if(j==11) draw_button(clear);
	        	else if(j==12) {
	        		if(is_fix||sub_page==1) draw_button(subClear);
				}
	        	else if(j==13) draw_button(THEM);	
	        	else if(j==14){
	        		if(sub_page==2&&!is_fix) draw_button(XOA);
				} 
	        	else if(j==15) {
	        		if(sub_page==2) draw_button(LUU);
				}
 	        	else if(j<100+nRow)  draw_rowTable(ROWTBs[j-100]);
	        	if(hover<nLecMenu) highlight_button(Menu[hover],grey,white,white);
	        	else if(hover==11) highlight_button(clear,grey,white,white);
	        	else if(hover==12){
	        		if(is_fix||sub_page==1) highlight_button(subClear,grey,white,white);
				}
	        	else if(hover==13) highlight_button(THEM,grey,white,white);	
	        	else if(hover==14){
	        		if(sub_page==2&&!is_fix) highlight_button(XOA,grey,white,white);
				} 
	        	else if(hover==15){
	        		if(sub_page==2) highlight_button(LUU,grey,white,white);
				} 
	        	else if(hover<100+nRow) highlight_rowTable(ROWTBs[hover-100],grey,black,white);  
			}
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for(int i=0;i<nLecMenu;i++){
				if(i==tt) continue;
	         	if(is_area(Menu[i].area,x,y)){
	         		create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		        	Menu[tt].area.width+5,3,3);
		        	draw_button(Menu[tt]);
		        	tt=i;
	         		return;
				}
		    }
		    for(int i=0;i<nRow;i++){
		    	if(is_rowTable(ROWTBs[i],x,y)){
		    		settextstyle(font_text,0,sizeS);
		    		clear_notice_stui4();
			        idx_start_LN = 0;
			        idx_start_FN = 0;
			        idx_student = indexs[(page-1)*10+i];
			        SNode = get_student_idx(CLASS->SFirst,idx_student);
					if(sub_page==1||is_fix){
		    			set_bar_edit_stui4(red);
              		   	strcpy(LUU.text,"SUA");
        		   	    draw_button2(LUU);
				        draw_button2(XOA);
			            highlight_button2(subClear,darkWhite,white,white);
			            strcpy(THEM.text,"BACK");
			            draw_button2(THEM);
			            sub_page = 2;
			            if(is_fix) is_fix=0;
			    	}
			    	else clear_edit_stui4(SID_text,LName_text,idx_start_LN,FName_text,idx_start_FN,PW_text);
					strcpy(sex,SNode->stui4.PHAI);
		    		strcpy(SID_text, SNode->stui4.MASV);
		    		strcpy(LName_text,SNode->stui4.HO);
		    		strcpy(FName_text,SNode->stui4.TEN);
		    		strcpy(PW_text,SNode->stui4.password);
			    	print_text_bar(l_win/2+367,w_win/3-37,SID_text,12,white,black);
			        print_text_bar(l_win/2+277,w_win/3+53,LName_text+idx_start_LN,15,white,black);
			        print_text_bar(l_win/2+487,w_win/3+53,FName_text+idx_start_FN,7,white,black);
			        print_text_bar(l_win/2+407,w_win/3+173,PW_text,10,white,black);
			        strcpy(sex,SNode->stui4.PHAI);
			        if(strcmp(sex,"NAM")==0) Tick_CTick(male,darkRed);
			        else Tick_CTick(female,darkRed);
		            if(choose!=1) {
		            	choose=0;
		            	continue;
					}
				}
			}
			if(is_area(Return.area,x,y)) return;
			else if(is_area(exit.area,x,y)){
				create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		       	Menu[tt].area.width+5,3,3);
		       	draw_button(Menu[tt]);
		       	delete_button(exit,3);
				tt=-1;
				return;
			}
			else if(is_area(page_after.area,x,y)){
				if(page<nPageTable){
				    page++;
				    set_StuTable(CLASS->SFirst, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_student,page_text);	
				}
			}		  
			else if(is_area(page_before.area,x,y)){
				if(page>1){
				    page--;
				    set_StuTable(CLASS->SFirst, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_student,page_text);
			    }
			}
			else if(is_area(THEM.area,x,y)){
				idx_start_LN = 0;
				if(sub_page==1){
					xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,0,page_text,page_tmp);
					settextstyle(font_text,0,sizeS);
					clear_notice_stui4();
					if(strlen(SID_text)==0) out_text_xy(l_win/2+277,w_win/3-37+30,(char*)"Nhap ma SV",3,darkRed);
					if(strlen(LName_text)==0) out_text_xy(l_win/2+277,w_win/3+53+30,(char*)"Nhap ho",3,darkRed);
					if(strlen(FName_text)==0) out_text_xy(l_win/2+475,w_win/3+53+30,(char*)"Nhap ten",3,darkRed);
				    if(strlen(PW_text)==0) out_text_xy(l_win/2+277,w_win/3+173+30,(char*)"Nhap password",3,darkRed);
					if(strlen(sex)==0)  out_text_xy(l_win/2+270,w_win/3+140,(char*)"Chua chon gioi tinh",3,darkRed);
					if(search_student_all_class_MSSV(CList,SID_text)!=NULL) out_text_xy(l_win/2+277,w_win/3-37+30,(char*)"Ma SV da ton tai",3,red);
					else if(strlen(SID_text)!=0&&strlen(LName_text)!=0&&strlen(FName_text)!=0&&strlen(sex)!=0&&strlen(PW_text)!=0){
						set_stuInfor(stuif,SID_text,LName_text,FName_text,sex,PW_text);
						insert_SList_CTT(CLASS->SFirst,stuif,NULL);
						s = 200, sub_tt = 1, print_s =1;
						strcpy(SID_text2,SID_text);
				    	get_index_StuList(CLASS->SFirst,indexs,n_index,search_text);
				    	last_nPageTable = nPageTable;
			            set_nPageTable(nRow,nPageTable,n_index,page,0);
			            set_StuTable(CLASS->SFirst, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_student,page_text);
		                clear_edit_stui4(SID_text,LName_text,idx_start_LN,FName_text,idx_start_FN,PW_text);	
			    		reset_stui4(SID_text,cursor_pos_MSV,cursor_pos_LN,LName_text,idx_LN,idx_start_LN,FName_text,cursor_pos_FN,idx_FN,idx_start_FN,sex, PW_text,cursor_pos_PW);
						n= T_cursor+1;
				    }
				}
				else{
					strcpy(THEM.text,"THEM");
					draw_button(THEM);
					if(is_fix){
						strcpy(LUU.text,"SUA");
						is_fix =0;
					} 
					else{
						highlight_button(XOA,darkWhite,white,white);	
     					draw_button(subClear);
					} 
					highlight_button(LUU,darkWhite,white,white);
                    set_bar_edit_stui4(white);
    		    	reset_stui4(SID_text,cursor_pos_MSV,cursor_pos_LN,LName_text,idx_LN,idx_start_LN,FName_text,cursor_pos_FN,idx_FN,idx_start_FN,sex, PW_text,cursor_pos_PW);
					n= T_cursor+1;
    				sub_page=1;
					choose = 0;				
				}
			}
			else if(is_area(bar_search.area,x,y)){
				n = T_cursor +1;
				if(strlen(search_text)==0) highlight_button(bar_search,white,white,white);
				xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,1,page_text,page_tmp);
			    cursor_pos_search = (x - l_win/16-133)/(lth_sizeM-2);
			    if (cursor_pos_search>strlen(search_text)&&strlen(search_text)<40) cursor_pos_search = strlen(search_text);
			    else if(cursor_pos_search>40) cursor_pos_search=40;
			    idx_search = idx_start_search +cursor_pos_search;
			}
			else if(is_area(studentID,x,y)&&(sub_page==1||is_fix)){
				n = T_cursor +1;
				out_text_xy(l_win/2+277,w_win/3-37+30,(char*)"                      ",3,3);
				xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text,choose,2,page_text,page_tmp);
			    cursor_pos_MSV = (x - (l_win/2+277))/(lth_sizeM-2);
			    if (cursor_pos_MSV>strlen(SID_text)&&strlen(SID_text)<12) cursor_pos_MSV = strlen(SID_text);
			    else if(cursor_pos_MSV>12) cursor_pos_MSV=12;
			}
			else if(is_area(LName,x,y)&&(sub_page==1||is_fix)){
				n = T_cursor +1;
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+277,w_win/3+53+30,(char*)"                ",3,3);
				xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,3,page_text,page_tmp);
			    cursor_pos_LN = (x - (l_win/2+270))/(lth_sizeM-2);
			    if (cursor_pos_LN>strlen(LName_text)&&strlen(LName_text)<15) cursor_pos_LN = strlen(LName_text);
			    else if(cursor_pos_LN>15) cursor_pos_LN=15;
			    idx_LN = idx_start_LN +cursor_pos_LN;
			}
			else if(is_area(FName,x,y)&&(sub_page==1||is_fix)){
				n = T_cursor +1;
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+475,w_win/3+53+30,(char*)"          ",3,3);
				xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,4,page_text,page_tmp);
			    cursor_pos_FN = (x - (l_win/2+480))/(lth_sizeM-2);
			    if (cursor_pos_FN>strlen(FName_text)&&strlen(FName_text)<7) cursor_pos_FN = strlen(FName_text);
			    else if(cursor_pos_FN>7) cursor_pos_FN=7;
			    idx_FN = idx_start_FN + cursor_pos_FN;
			}
			else if(is_area_CTick(male,x,y)&&(sub_page==1||is_fix)){
				if(strcmp(sex,"NU")==0) draw_CTick(female); 
				strcpy(sex,"NAM");
				Tick_CTick(male,grey);
				out_text_xy(l_win/2+270,w_win/3+140,(char*)"                   ",3,3);
				xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text,choose,0,page_text,page_tmp);
			}
			else if(is_area_CTick(female,x,y)&&(sub_page==1||is_fix)){
				if(strcmp(sex,"NAM")==0) draw_CTick(male); 
				strcpy(sex,"NU");
				Tick_CTick(female,grey);
				out_text_xy(l_win/2+270,w_win/3+140,(char*)"                   ",3,3);
				xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text,choose,0,page_text,page_tmp);
			}
			else if(is_area(password,x,y)&&(sub_page==1||is_fix)){
				n = T_cursor +1;
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+277,w_win/3+173+30,(char*)"                        ",3,3);
				xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,5,page_text,page_tmp);
			    cursor_pos_PW = (x - (l_win/2+400))/(lth_sizeM-2);
			    if (cursor_pos_PW>strlen(PW_text)&&strlen(PW_text)<10) cursor_pos_PW = strlen(PW_text);
			    else if(cursor_pos_PW>10) cursor_pos_PW=10;
			}
			else if(is_area(clear.area,x,y)){
				search_text[0]='\0';
				cursor_pos_search = 0;
				idx_start_search = 0;
				idx_search =0;
				if(choose!=1){
					choose=0;
					draw_button(bar_search);
                }
				else{
					n = T_cursor+1;
        	        highlight_button(bar_search,white,white,white);
				}
				get_index_StuList(CLASS->SFirst,indexs,n_index,search_text);
			    last_nPageTable = nPageTable;
	   	        set_nPageTable(nRow,nPageTable,n_index,page,1);
	   	        set_StuTable(CLASS->SFirst, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_student,page_text);
			}
			else if(is_area(subClear.area,x,y)&&(sub_page==1||is_fix)){
	            idx_start_LN =0;
			    clear_notice_stui4();
		    	clear_edit_stui4(SID_text,LName_text,idx_start_LN,FName_text,idx_start_FN,PW_text);	
				reset_stui4(SID_text,cursor_pos_MSV,cursor_pos_LN,LName_text,idx_LN,idx_start_LN,FName_text,cursor_pos_FN,idx_FN,idx_start_FN,sex, PW_text,cursor_pos_PW);
				n= T_cursor+1;
				xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,0,page_text,page_tmp);
			}
			else if(is_area(XOA.area,x,y)&&(sub_page==2&&!is_fix)){
				if(sinh_vien_da_thi(SNode)){
					s = 200, sub_tt = 4, print_s =1;
					continue;
	            }
				if(!is_delete(SID_text,2)) continue;
				delete_SList_MSSV(CLASS->SFirst,SID_text);
				s = 200, sub_tt = 2, print_s =1;
				strcpy(SID_text2,SID_text);
			    get_index_StuList(CLASS->SFirst,indexs,n_index,search_text);
			    last_nPageTable = nPageTable;
	            set_nPageTable(nRow,nPageTable,n_index,page,0);
	            set_StuTable(CLASS->SFirst, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_student,page_text);
           		strcpy(THEM.text,"THEM");
				draw_button(THEM);
				highlight_button(XOA,darkWhite,white,white);
				if(!is_fix) draw_button(subClear);
				highlight_button(LUU,darkWhite,white,white);
    	    	set_bar_edit_stui4(white);
				reset_stui4(SID_text,cursor_pos_MSV,cursor_pos_LN,LName_text,idx_LN,idx_start_LN,FName_text,cursor_pos_FN,idx_FN,idx_start_FN,sex, PW_text,cursor_pos_PW);
				choose=0;
				sub_page =1;	
			}
			else if(is_area(LUU.area,x,y)&&sub_page==2){
				if(is_fix==0){
					highlight_button(XOA,darkWhite,white,white);
					strcpy(LUU.text,"LUU");
					draw_button(LUU);
					draw_button(subClear);
					set_bar_edit_stui4(white);
			    	print_text_bar(l_win/2+367,w_win/3-37,SID_text,12,white,black);
			        print_text_bar(l_win/2+277,w_win/3+53,LName_text+idx_start_LN,15,white,black);
			        print_text_bar(l_win/2+487,w_win/3+53,FName_text+idx_start_FN,7,white,black);
			        print_text_bar(l_win/2+407,w_win/3+173,PW_text,10,white,black);
			        if(strcmp(sex,"NAM")==0) Tick_CTick(male,grey);
			        else Tick_CTick(female,grey);
					is_fix = 1;
				}
				else{
					xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,0,page_text,page_tmp);
					SNode_tmp = search_student_all_class_MSSV(CList,SID_text);
					clear_notice_stui4();
					if(strlen(SID_text)==0) out_text_xy(l_win/2+277,w_win/3-37+30,(char*)"Nhap ma SV",3,darkRed);
					if(strlen(LName_text)==0) out_text_xy(l_win/2+277,w_win/3+53+30,(char*)"Nhap ho",3,darkRed);
					if(strlen(FName_text)==0) out_text_xy(l_win/2+475,w_win/3+53+30,(char*)"Nhap ten",3,darkRed);
				    if(strlen(PW_text)==0) out_text_xy(l_win/2+277,w_win/3+173+30,(char*)"Nhap password",3,darkRed);
					if(strlen(sex)==0) out_text_xy(l_win/2+270,w_win/3+140,(char*)"Chua chon gioi tinh",3,darkRed);
					if(SNode_tmp!=NULL&&SNode_tmp!=SNode) out_text_xy(l_win/2+277,w_win/3-37+30,(char*)"Ma SV da ton tai",3,red);
					else if(strlen(SID_text)!=0&&strlen(LName_text)!=0&&strlen(FName_text)!=0&&strlen(sex)!=0&&strlen(PW_text)!=0){
						set_stuInfor(stuif,SID_text,LName_text,FName_text,sex,PW_text); 
						delete_SList_MSSV(CLASS->SFirst,SNode->stui4.MASV);
						insert_SList_CTT(CLASS->SFirst,stuif,NULL);
						s = 200, sub_tt = 3, print_s =1;
						strcpy(SID_text2,SID_text);
					    get_index_StuList(CLASS->SFirst,indexs,n_index,search_text);
					    last_nPageTable = nPageTable;
			            set_nPageTable(nRow,nPageTable,n_index,page,0);
			            set_StuTable(CLASS->SFirst, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_student,page_text);
		               	strcpy(THEM.text,"THEM");
						draw_button(THEM);
						highlight_button(LUU,darkWhite,white,white);
		   		    	clear_edit_stui4(SID_text,LName_text,idx_start_LN,FName_text,idx_start_FN,PW_text);	
						reset_stui4(SID_text,cursor_pos_MSV,cursor_pos_LN,LName_text,idx_LN,idx_start_LN,FName_text,cursor_pos_FN,idx_FN,idx_start_FN,sex, PW_text,cursor_pos_PW);
						sub_page=1;	
						is_fix = 0;						
					} 
				}
			}
			else if(is_area(pageArea,x,y)){
				xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,7,page_text,page_tmp);
				if(page==0) continue; 
				page_tmp = page;
				cursor_pos_page = (x -((l_win/4+93)-strlen(page_text)*(lth_sizeM)/2.0))/lth_sizeM;
				if(cursor_pos_page<0) cursor_pos_page = 0;
				else if(cursor_pos_page>strlen(page_text)) cursor_pos_page = strlen(page_text);
				n = T_cursor+1;
			}
			else xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,0,page_text,page_tmp);
			settextstyle(font_text,0,sizeM);
			if(choose==1) print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
			else if(choose==2) print_text_bar(l_win/2+367,w_win/3-37,SID_text,12,white,black);
			else if(choose==3) print_text_bar(l_win/2+277,w_win/3+53,LName_text+idx_start_LN,15,white,black);
			else if(choose==4) print_text_bar(l_win/2+487,w_win/3+53,FName_text+idx_start_FN,7,white,black);
			else if(choose==5) print_text_bar(l_win/2+407,w_win/3+173,PW_text,10,white,black);
			else if(choose==7) out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
		}
		if(kbhit()){
			n = T_cursor+1;
			key = Key();
			if(choose == 1){
				settextstyle(font_text,0,sizeS);
                print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,white);
			    if(key==key_Right){
					if(idx_search<strlen(search_text)){
						idx_search++; 
						if(cursor_pos_search==40) idx_start_search++;
					} 
                    if(cursor_pos_search<40&&cursor_pos_search<strlen(search_text)) cursor_pos_search++;
				    print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
			    else if(key==key_Left){
                    if(idx_search>0) idx_search--; 
                    if(cursor_pos_search>0) cursor_pos_search--;
                    else if(idx_start_search>0) idx_start_search--;
				    print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
				else if(strlen(search_text)==50&&key!=key_BS){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/16+140,w_win/4-17+30,(char*)"Tu khoa toi da 50 ki tu",3,darkRed);
					settextstyle(font_text,0,sizeS);
					print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
				else{
					if(key==key_BS){
						if(idx_search>0){
							strcpy(search_text + idx_search-1, search_text + idx_search);
							idx_search--;
						}
					    if(idx_start_search>0) idx_start_search--;
					    else if(cursor_pos_search >0) cursor_pos_search--;
		     	    }
		     	    else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'||key==key_SP||key=='-'){
    					insert_chr_to_str(search_text,key,idx_search);
    	                idx_search++;
    					if(cursor_pos_search < 40) cursor_pos_search++;
    					else idx_start_search++;
			    	}
			    	print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
			    	get_index_StuList(CLASS->SFirst,indexs,n_index,search_text);
			    	last_nPageTable = nPageTable;
	                set_nPageTable(nRow,nPageTable,n_index,page,1);
	                set_StuTable(CLASS->SFirst, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_student,page_text);
				}
		    }
		    else if(choose==2){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+277,w_win/3-37+30,(char*)"Ma SV toi da 11 ki tu",3,3);
                print_text_bar(l_win/2+367,w_win/3-37,SID_text,11,white,white);
			    if(key==key_Right){
                    if(cursor_pos_MSV<strlen(SID_text)) cursor_pos_MSV++;
				}
			    else if(key==key_Left){
                    if(cursor_pos_MSV>0) cursor_pos_MSV--;
				}
				else if(key==key_Enter||key==key_Down){
			        if(strlen(LName_text)>15) cursor_pos_LN = idx_LN = 15;
					else cursor_pos_LN = idx_LN = strlen(LName_text);
					xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,3,page_text,page_tmp);	        
				}
				else if(key==key_BS){
					if(cursor_pos_MSV >0){
						strcpy(SID_text + cursor_pos_MSV-1, SID_text + cursor_pos_MSV);
						cursor_pos_MSV--;
					} 
		  	    }
	    	    else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'||key==(int)'-'){
	    	    	if(strlen(SID_text)==MAX_MASV){
	            		settextstyle(font_text,0,sizeS-1);
						out_text_xy(l_win/2+277,w_win/3-37+30,(char*)"Ma SV toi da 11 ki tu",3,darkRed);
				    }
				    else{
				    	ch = (char)key;
						upper_chr(ch); 
    	   				insert_chr_to_str(SID_text,ch,cursor_pos_MSV);
    			    	if(cursor_pos_MSV < 12) cursor_pos_MSV++;
					}
			    }
			    print_text_bar(l_win/2+367,w_win/3-37,SID_text,11,white,black);
		    }
		    else if(choose==3){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+277,w_win/3+53+30,(char*)"Toi da 50 ki tu",3,3);
				print_text_bar(l_win/2+277,w_win/3+53,LName_text+idx_start_LN,15,white,white);
			    if(key==key_Right){
					if(idx_LN<strlen(LName_text)){
						idx_LN++; 
						if(cursor_pos_LN==15) idx_start_LN++;
					} 
                    if(cursor_pos_LN<15&&cursor_pos_LN<strlen(LName_text)) cursor_pos_LN++;
				}
			    else if(key==key_Left){
                    if(idx_LN>0) idx_LN--; 
                    if(cursor_pos_LN>0) cursor_pos_LN--;
                    else if(idx_start_LN>0) idx_start_LN--;
				}
				else if(key==key_Up){
					fix_str1(LName_text);
					idx_start_LN = 0;
				    cursor_pos_MSV = strlen(SID_text);
					xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,2,page_text,page_tmp);
				}
				else if(key==key_Enter||key==key_Down){
					fix_str1(LName_text);
					idx_start_LN = 0;
			        if(strlen(FName_text)>7) cursor_pos_FN = idx_FN = 7;
					else cursor_pos_FN = idx_FN = strlen(FName_text);
					xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,4,page_text,page_tmp);	        
				}
				else if(key==key_BS){
				 	if(idx_LN>0){
						strcpy(LName_text + idx_LN-1, LName_text + idx_LN);
						idx_LN--;
					}
				    if(idx_start_LN>0) idx_start_LN--;
					else if(cursor_pos_LN >0) cursor_pos_LN--;
		  	    }
				else if(strlen(LName_text)==MAX_HO){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/2+277,w_win/3+53+30,(char*)"Toi da 50 ki tu",3,darkRed);
				}
	    	    else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'||key==(int)'-'||key==' '){
	    	    	if(key==' '){
	    	    		if(cursor_pos_LN==0){
	    	    			print_text_bar(l_win/2+277,w_win/3+53,LName_text+idx_start_LN,15,white,black);
	    	    			continue;
						}
					}
					insert_chr_to_str(LName_text,key,idx_LN);
    	            idx_LN++;
    		    	if(cursor_pos_LN < 15) cursor_pos_LN++;
    				else idx_start_LN++;
			    }
			    print_text_bar(l_win/2+277,w_win/3+53,LName_text+idx_start_LN,15,white,black);
		    }
		    else if(choose==4){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+475,w_win/3+53+30,(char*)"T.da 15 kt",3,3);
		     	print_text_bar(l_win/2+487,w_win/3+53,FName_text+idx_start_FN,7,white,white);
			    if(key==key_Right){
					if(idx_FN<strlen(FName_text)){
						idx_FN++; 
						if(cursor_pos_FN==7) idx_start_FN++;
					} 
                    if(cursor_pos_FN<7&&cursor_pos_FN<strlen(FName_text)) cursor_pos_FN++;
				}
			    else if(key==key_Left){
                    if(idx_FN>0) idx_FN--; 
                    if(cursor_pos_FN>0) cursor_pos_FN--;
                    else if(idx_start_FN>0) idx_start_FN--;
				}
				else if(key==key_Up){
					fix_str1(FName_text);
					idx_start_FN = 0;
					if(strlen(LName_text)>15) cursor_pos_LN = idx_LN = 15;
					else cursor_pos_LN = idx_LN = strlen(LName_text);
					xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,3,page_text,page_tmp);
				}
				else if(key==key_Enter||key==key_Down){
					fix_str1(LName_text);
					idx_start_FN = 0;
			        cursor_pos_PW = strlen(PW_text);
					xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,5,page_text,page_tmp);	        
				}
				else if(key==key_BS){
				 	if(idx_FN>0){
						strcpy(FName_text + idx_FN-1, FName_text + idx_FN);
						idx_FN--;
					}
				    if(idx_start_FN>0) idx_start_FN--;
					else if(cursor_pos_FN >0) cursor_pos_FN--;
		  	    }
				else if(strlen(FName_text)==MAX_TEN){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/2+480,w_win/3+53+30,(char*)"T.da 15 kt",3,darkRed);
				}
	    	    else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'||key==(int)'-'||key==' '){
	    	    	if(key==' '){
	    	    		if(cursor_pos_FN==0){
	    	    			print_text_bar(l_win/2+487,w_win/3+53,FName_text+idx_start_FN,7,white,black);
	    	    			continue;
						}
					}
					insert_chr_to_str(FName_text,key,idx_FN);
    	            idx_FN++;
    		    	if(cursor_pos_FN < 7) cursor_pos_FN++;
    				else idx_start_FN++;
			    }
			    print_text_bar(l_win/2+487,w_win/3+53,FName_text+idx_start_FN,7,white,black);
		    }
		    else if(choose==5){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+277,w_win/3+173+30,(char*)"Password toi da 10 ki tu",3,3);
                print_text_bar(l_win/2+407,w_win/3+173,PW_text,10 ,white,white);
			    if(key==key_Right){
                    if(cursor_pos_PW<strlen(PW_text)) cursor_pos_PW++;
				}
			    else if(key==key_Left){
                    if(cursor_pos_PW>0) cursor_pos_PW--;
				}
                else if(key==key_Up){
					if(strlen(FName_text)>7) cursor_pos_FN = idx_FN = 15;
					else cursor_pos_FN = idx_FN = strlen(FName_text);
					xoa1(bar_search,search_text,idx_start_search, SID_text, LName_text,idx_start_LN, FName_text, idx_start_FN, PW_text, choose,4,page_text,page_tmp);
				}
				else if(key==key_BS){
					if(cursor_pos_PW >0){
						strcpy(PW_text + cursor_pos_PW-1, PW_text + cursor_pos_PW);
						cursor_pos_PW--;
					} 
		  	    }
	    	    else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'){
	    	    	if(strlen(PW_text)==MAX_PASS){
	            		settextstyle(font_text,0,sizeS-1);
						out_text_xy(l_win/2+277,w_win/3+173+30,(char*)"Password toi da 10 ki tu",3,darkRed);
				    }
				    else{
				    	ch = (char)key;
						upper_chr(ch); 
    	   				insert_chr_to_str(PW_text,ch,cursor_pos_PW);
    			    	if(cursor_pos_PW < 10) cursor_pos_PW++;
					}
			    }
			    print_text_bar(l_win/2+407,w_win/3+173,PW_text,10,white,black);
		    }
		    else if(choose==7){
		    	settextstyle(font_text,0,sizeM);
				out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,white);
			    if(key==key_Right){
					if(cursor_pos_page<strlen(page_text)) cursor_pos_page++;
				}
			    else if(key==key_Left){
                    if(cursor_pos_page>0) cursor_pos_page--;
				}
				else if(key==key_BS){
				 	if(cursor_pos_page>0){
				 		strcpy(page_text+cursor_pos_page-1,page_text+cursor_pos_page);
				 		cursor_pos_page--;
					}
		  	    }
	    	    else if(key>='0'&&key<='9'){
	    	    	if(key!='0'||cursor_pos_page!=0){
	    	   	    	insert_chr_to_str(page_text,key,cursor_pos_page);
	    	    		if(atoi(page_text)>nPageTable){
	    	    		itoa(nPageTable,page_text,decimal);
	    	    		cursor_pos_page = nPageTable/10 + 1;
						}
    					else cursor_pos_page++;
					}
			    }
			    else if(key==key_Enter){
			    	choose = 0;	
                 	if(strlen(page_text)==0) strcpy(page_text,itoa(page_tmp,buff,decimal));
			    	else {
			    		page = atoi(page_text);
			    		set_StuTable(CLASS->SFirst, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_student,page_text);
					}
				}
				settextstyle(font_text,0,sizeM);
				out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
			}
		}
	}	
}

//GIAO DIEN LOP - CHO GV XEM
void make_string_class(classInfor &classif,char *buff){//HO TRO TIM KIEM LOP
	strcpy(buff,classif.MALOP);
	strcat(buff,classif.TENLOP);
}
int get_index_CList(classList &CList, int* indexs,int& n_index, char* search_text){//HAM TIM KIEM LOP
	n_index = 0;
	char buff[MAX_TENLOP+MAX_MALOP+1], buff2[MAX_TENLOP+MAX_MALOP+1];
	strcpy(buff,search_text);
	delete_blks_str(buff);
	upper_str(buff);
	for(int i=0; i< CList.nClass;i++){
		make_string_class(CList.classes[i]->classi4,buff2);
		delete_blks_str(buff2);
		upper_str(buff2);
		if(strstr(buff2,buff)!=NULL) indexs[n_index++] = i;
	}
}
void classList_interface(){
	settextstyle(font_text,0,sizeM);
	out_text_xy(l_win/16,w_win/4-17,(char *)"TIM KIEM:",3,black);
	out_text_xy(l_win/2+270,w_win/3-10,(char*)"MA LOP:",3,black);
	out_text_xy(l_win/2+270,w_win/3+50,(char*)"TEN LOP:",3,black);
	settextstyle(font_text,0,sizeM+1);
	out_text_xy(l_win/2+295,w_win/5+10,(char*)"THONG TIN LOP",3,black);
	settextstyle(font_text,0,sizeS);
	out_text_xy(l_win/16,w_win/3,(char*)"Click chuot trai tai 1 dong de chinh sua hoac xoa",3,darkRed);
	create_table(l_win/16,w_win/3+25,lengthsCTable,30,4,1,classTable,sizeM,black,darkWhite,black); 
	create_1_bar(l_win/2+375,w_win/3-12,170,30,white,white);
	create_1_bar(l_win/2+270,w_win/3+80,310,30,white,white);
    create_1_bar(l_win/4+50,w_win-70,100,30,white,white);
    setcolor(darkRed);
	rectangle(l_win/2+270,w_win/2+170,l_win/2+580,w_win/2+280);
	setcolor(black);
	rectangle(l_win/2+275,w_win/2+175,l_win/2+575,w_win/2+275);
}
void class_List(classList &CList,PTRC& CLASS, BUTTON* Menu, int& tt){
	classList_interface();   
    char ch, search_text[MAX_TENLOP+MAX_MALOP+2] ={0}, CName_text[MAX_TENLOP+1]={0},CID_text[MAX_MALOP+1]={0},buff[10]={0}, CID_text2[MAX_MALOP+1]={0}, page_text[10];
	int x, y, hover=-1, j, s=0, sub_tt , key,sub_page = 1, cursor_pos_search = 0, idx_start_search=0, idx_search = 0, idx_tmp;
	int cursor_pos_ML = 0, cursor_pos_TL = 0,idx_start_TL=0, idx_TL= 0, print_s = 0, idx_class =-1, cursor_pos_page =0;
	int choose = 0, n = T_cursor+1, page = 1, indexs[MAX_CLASS+1]={-1}, n_index,nRow =0,nPageTable,last_nPageTable=-1, page_tmp, is_fix =0;
	AREA classID, className, pageArea, DSSV[10];
	BUTTON exit, page_after, page_before, bar_search, clear, THEM, LUU, XOA, subClear;
	rowTable ROWTBs[10]={};
	//giao dien
	get_index_CList(CList,indexs,n_index,search_text);
	set_nPageTable(nRow,nPageTable,n_index,page,1);
	set_buttons_classList(exit,page,nRow, page_after,page_before, nPageTable,bar_search,clear,classID,className,THEM,LUU,XOA,subClear,pageArea,DSSV);
	set_CTable(CList, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_class,page_text);
	
	Class CLS;
	while(1){
		delay(1);
		if(s && print_s) inform(s,sub_tt,CID_text2,print_s);
		if(choose==1) print_cursor(l_win/16+140+cursor_pos_search*(lth_sizeM-2),w_win/4-16,n);
		else if(choose==2) print_cursor(l_win/2+382+cursor_pos_ML*(lth_sizeM-2),w_win/3-8,n);
		else if(choose==3) print_cursor(l_win/2+277+cursor_pos_TL*(lth_sizeM-2),w_win/3+84,n);
		else if(choose==4) print_cursor(l_win/4+100-strlen(page_text)/2.0*(lth_sizeM)+cursor_pos_page*lth_sizeM,w_win-65,n);
		if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE,x,y);
			set_hover_CList(Menu, ROWTBs,hover,j,tt,x,y,nRow,clear,LUU,subClear,THEM,XOA);
	        if(j!=hover&&j!=-1){
	        	if(j<nLecMenu) draw_button(Menu[j]);
	        	else if(j==11) draw_button(clear);
	        	else if(j==12) {
	        		if(is_fix||sub_page==1) draw_button(subClear);
				}
	        	else if(j==13) draw_button(THEM);	
	        	else if(j==14){
	        		if(sub_page==2&&!is_fix) draw_button(XOA);
				} 
	        	else if(j==15) {
	        		if(sub_page==2) draw_button(LUU);
				}
 	        	else if(j<100+nRow)  draw_rowTable(ROWTBs[j-100]);
	        	if(hover<nLecMenu) highlight_button(Menu[hover],grey,white,white);
	        	else if(hover==11) highlight_button(clear,grey,white,white);
	        	else if(hover==12){
	        		if(is_fix||sub_page==1) highlight_button(subClear,grey,white,white);
				}
	        	else if(hover==13) highlight_button(THEM,grey,white,white);	
	        	else if(hover==14){
	        		if(sub_page==2&&!is_fix) highlight_button(XOA,grey,white,white);
				} 
	        	else if(hover==15){
	        		if(sub_page==2) highlight_button(LUU,grey,white,white);
				} 
	        	else if(hover<100+nRow) highlight_rowTable(ROWTBs[hover-100],grey,black,white);  
			}
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for(int i=0;i<nLecMenu;i++){
				if(i==tt) continue;
	         	if(is_area(Menu[i].area,x,y)){
	         		create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		        	Menu[tt].area.width+5,3,3);
		        	draw_button(Menu[tt]);
		        	tt=i;
	         		return;
				}
		    }
		    for(int i=0;i<nRow;i++){
		    	if(is_area(DSSV[i],x,y)){
		    		CLASS = CList.classes[indexs[10*(page-1)+i]];
		    		tt=6;
					return; 
				}
			}
		    for(int i=0;i<nRow;i++){
		    	if(is_rowTable(ROWTBs[i],x,y)){
			        idx_start_TL =0;
			        clear_notice_classi4();
	    		    idx_class = indexs[(page-1)*10+i];
		    		if(sub_page==1||is_fix){
		    			set_bar_edit_classi4(darkRed);
              		   	strcpy(LUU.text,"SUA");
        		   	    draw_button2(LUU);
				        draw_button2(XOA);
			            highlight_button2(subClear,darkWhite,white,white);
			            strcpy(THEM.text,"THEM");
			            draw_button2(THEM);
			            sub_page = 2;
			            if(is_fix) is_fix=0;
			    	}
			    	else clear_edit_classi4(CID_text,CName_text,idx_start_TL);
			    	strcpy(CID_text,CList.classes[idx_class]->classi4.MALOP);
		    		strcpy(CName_text,CList.classes[idx_class]->classi4.TENLOP);
		        	print_text_bar(l_win/2+382,w_win/3-9,CID_text,11,white,black);
		            print_text_bar(l_win/2+277,w_win/3+83,CName_text+idx_start_TL,24,white,black);
		            if(choose!=1) {
		            	choose=0;
		            	continue;
					}
				}
			}
			if(is_area(exit.area,x,y)){
				create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		       	Menu[tt].area.width+5,3,3);
		       	draw_button(Menu[tt]);
		       	delete_button(exit,3);
				tt=-1;
				return;
			}
			else if(is_area(page_after.area,x,y)){
				if(page<nPageTable){
				    page++;
				    set_CTable(CList, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_class,page_text);
				}
			}		  
			else if(is_area(page_before.area,x,y)){
				if(page>1){
				    page--;
				    set_CTable(CList, ROWTBs, indexs, n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_class,page_text);
				}
			}
			else if(is_area(THEM.area,x,y)){
				idx_start_TL = 0;
				if(sub_page==1){
					xoa(bar_search, choose,search_text, CID_text, CName_text,idx_start_search,idx_start_TL,0,page_text,page_tmp);
					settextstyle(font_text,0,sizeS);
					if(strlen(CID_text)==0) out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"Nhap ma lop",3,darkRed);
					if(strlen(CName_text)==0) out_text_xy(l_win/2+277,w_win/3+83+30,(char*)"Nhap ten lop",3,darkRed);
					if(search_CList_ML(CList,CID_text)!=-1) out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"Ma lop da ton tai",3,darkRed);
					else if(strlen(CID_text)!=0&&strlen(CName_text)!=0){
						set_classInfor(CLS.classi4,CID_text,CName_text);
						CLS.SFirst = NULL;
						if(insert_CList_CTT(CList,CLS)){
							s = 200, sub_tt = 1, print_s =1;
							strcpy(CID_text2,CID_text);
							
							//reload giao dien
					    	get_index_CList(CList,indexs,n_index,search_text);
					    	last_nPageTable = nPageTable;
			                set_nPageTable(nRow,nPageTable,n_index,page,0);
			                set_CTable(CList, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_class,page_text);	
						}
						else out_text_xy(l_win/2+277,w_win/3+175,(char*)"DS lop da day (100 lop)",3,darkRed);
		                clear_edit_classi4(CID_text,CName_text,idx_start_TL);
						reset_classi4(CID_text,cursor_pos_ML,CName_text,cursor_pos_TL,idx_TL,idx_start_TL);		
						n= T_cursor+1;
					}
				}
				else{
					strcpy(THEM.text,"THEM");
					draw_button(THEM);
					if(is_fix){
						strcpy(LUU.text,"SUA");
						is_fix =0;
					} 
					else{
						highlight_button(XOA,darkWhite,white,white);	
     					draw_button(subClear);
					} 
					highlight_button(LUU,darkWhite,white,white);
					set_bar_edit_classi4(white);
				    reset_classi4(CID_text,cursor_pos_ML,CName_text,cursor_pos_TL,idx_TL,idx_start_TL);		
					n = T_cursor+1;
    				sub_page=1;
					choose = 0;				
				}
			}
			else if(is_area(bar_search.area,x,y)){
				n = T_cursor +1;
				if(strlen(search_text)==0) highlight_button(bar_search,white,white,white);
				xoa(bar_search, choose,search_text, CID_text, CName_text,idx_start_search,idx_start_TL,1,page_text,page_tmp);
			    cursor_pos_search = (x - l_win/16-133)/(lth_sizeM-2);
			    if (cursor_pos_search>strlen(search_text)&&strlen(search_text)<40) cursor_pos_search = strlen(search_text);
			    else if(cursor_pos_search>40) cursor_pos_search=40;
			    idx_search = idx_start_search +cursor_pos_search;
			}
			else if(is_area(classID,x,y)&&(sub_page==1||is_fix)){
				n = T_cursor +1;
				out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"                     ",3,3);
				xoa(bar_search, choose,search_text, CID_text, CName_text,idx_start_search,idx_start_TL,2,page_text,page_tmp);
			    cursor_pos_ML = (x - (l_win/2+375))/(lth_sizeM-2);
			    if (cursor_pos_ML>strlen(CID_text)&&strlen(CID_text)<11) cursor_pos_ML = strlen(CID_text);
			    else if(cursor_pos_ML>11) cursor_pos_ML=11;
			}
			else if(is_area(className,x,y)&&(sub_page==1||is_fix)){
				n = T_cursor +1;
				out_text_xy(l_win/2+277,w_win/3+83+30,(char*)"                       ",3,3);
				xoa(bar_search, choose,search_text, CID_text, CName_text,idx_start_search,idx_start_TL,3,page_text,page_tmp);
			    cursor_pos_TL = (x - (l_win/2+270))/(lth_sizeM-2);
			    if (cursor_pos_TL>strlen(CName_text)&&strlen(CName_text)<24) cursor_pos_TL = strlen(CName_text);
			    else if(cursor_pos_TL>24) cursor_pos_TL=24;
			    idx_TL = idx_start_TL +cursor_pos_TL;
			}
			else if(is_area(clear.area,x,y)){
				search_text[0]='\0';
				cursor_pos_search = 0;
				idx_start_search = 0;
				idx_search =0;
				if(choose!=1){
					choose=0;
					draw_button(bar_search);
                }
				else{
					n = T_cursor+1;
        	        highlight_button(bar_search,white,white,white);
				}
				
				//reaload giao dien
				get_index_CList(CList,indexs,n_index,search_text);
			    last_nPageTable = nPageTable;
	   	        set_nPageTable(nRow,nPageTable,n_index,page,1);
	   	        set_CTable(CList, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_class,page_text);
			}
			else if(is_area(subClear.area,x,y)&&(sub_page==1||is_fix)){
	            idx_start_TL =0;
			    clear_notice_classi4();
		    	clear_edit_classi4(CID_text,CName_text,idx_start_TL);		
				reset_classi4(CID_text,cursor_pos_ML,CName_text,cursor_pos_TL,idx_TL,idx_start_TL);	
				n= T_cursor+1;
				xoa(bar_search, choose,search_text, CID_text, CName_text,idx_start_search,idx_start_TL,0,page_text,page_tmp);
			}
			else if(is_area(XOA.area,x,y)&&(sub_page==2&&!is_fix)){
				if(lop_da_co_sinh_vien_thi(CList.classes[idx_class]) /*|| CList.classes[idx_class]->SFirst!=NULL*/){//da co sv thi thi k cho xoa
					s = 200, sub_tt = 4, print_s =1;
					continue;
				}
				if(!is_delete(CID_text,1)) continue;
				else{
					delete_CList_idx(CList,idx_class);
					s = 200, sub_tt = 2, print_s =1;
					strcpy(CID_text2,CID_text);
					
					//reload giao dien
			    	get_index_CList(CList,indexs,n_index,search_text);
			    	last_nPageTable = nPageTable;
	                set_nPageTable(nRow,nPageTable,n_index,page,0);
	                set_CTable(CList, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_class,page_text);
           		}
           		strcpy(THEM.text,"THEM");
				draw_button(THEM);
				highlight_button(XOA,darkWhite,white,white);
				if(!is_fix) draw_button(subClear);
				highlight_button(LUU,darkWhite,white,white);
    	    	set_bar_edit_classi4(white);
				reset_classi4(CID_text,cursor_pos_ML,CName_text,cursor_pos_TL,idx_TL,idx_start_TL);	
				choose=0;
				sub_page =1;	
			}
			else if(is_area(LUU.area,x,y)&&sub_page==2){
				if(is_fix==0){
					highlight_button(XOA,darkWhite,white,white);
					strcpy(LUU.text,"LUU");
					draw_button(LUU);
					draw_button(subClear);
					set_bar_edit_classi4(white);
			        print_text_bar(l_win/2+382,w_win/3-9,CID_text,11,white,black);
		            print_text_bar(l_win/2+277,w_win/3+83,CName_text+idx_start_TL,24,white,black);
					is_fix = 1;
				}
				else{
					xoa(bar_search, choose,search_text, CID_text, CName_text,idx_start_search,idx_start_TL,0,page_text,page_tmp);
					idx_tmp = search_CList_ML(CList,CID_text);
					if(strlen(CID_text)==0) out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"Nhap ma lop",3,darkRed);
					if(strlen(CName_text)==0) out_text_xy(l_win/2+277,w_win/3+83+30,(char*)"Nhap ten lop",3,darkRed);
					if(idx_tmp!=-1&&idx_tmp!=idx_class) out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"Ma lop da ton tai",3,darkRed);
					else if(strlen(CID_text)!=0&&strlen(CName_text)!=0){
						CLS = *CList.classes[idx_class];   
						set_classInfor(CLS.classi4,CID_text,CName_text); 
						CList.classes[idx_class]->SFirst = NULL;   
						delete_CList_idx(CList,idx_class);
						insert_CList_CTT(CList, CLS);
						s = 200, sub_tt = 3, print_s =1;
						strcpy(CID_text2,CID_text);
					    get_index_CList(CList,indexs,n_index,search_text);
					    last_nPageTable = nPageTable;
			            set_nPageTable(nRow,nPageTable,n_index,page,0);
			            set_CTable(CList, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_class,page_text);
		               	strcpy(THEM.text,"THEM");
						draw_button(THEM);
						highlight_button(LUU,darkWhite,white,white);
		   		    	clear_edit_classi4(CID_text,CName_text,idx_start_TL);
						reset_classi4(CID_text,cursor_pos_ML,CName_text,cursor_pos_TL,idx_TL,idx_start_TL);
						sub_page=1;	
						is_fix = 0;						
					} 
				}
			}
			else if(is_area(pageArea,x,y)){
				xoa(bar_search, choose,search_text, CID_text, CName_text,idx_start_search,idx_start_TL,4,page_text,page_tmp);
				if(page==0) continue; 
				page_tmp = page;
				cursor_pos_page = (x -((l_win/4+93)-strlen(page_text)*(lth_sizeM)/2.0))/lth_sizeM;
				if(cursor_pos_page<0) cursor_pos_page = 0;
				else if(cursor_pos_page>strlen(page_text)) cursor_pos_page = strlen(page_text);
				n = T_cursor+1;
			}
			else xoa(bar_search, choose,search_text, CID_text, CName_text,idx_start_search,idx_start_TL,0,page_text,page_tmp);
			settextstyle(font_text,0,sizeM);
			if(choose==1) print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
			else if(choose==2) print_text_bar(l_win/2+382,w_win/3-9,CID_text,11,white,black);
			else if(choose==3) print_text_bar(l_win/2+277,w_win/3+83,CName_text+idx_start_TL,24,white,black);
			else if(choose==4) out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
		}
		if(kbhit()){
			n = T_cursor+1;
			key = Key();
			if(choose == 1){
				settextstyle(font_text,0,sizeS);
                print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,white);
			    if(key==key_Right){
					if(idx_search<strlen(search_text)){
						idx_search++; 
						if(cursor_pos_search==40) idx_start_search++;
					} 
                    if(cursor_pos_search<40&&cursor_pos_search<strlen(search_text)) cursor_pos_search++;
				    print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
			    else if(key==key_Left){
                    if(idx_search>0) idx_search--; 
                    if(cursor_pos_search>0) cursor_pos_search--;
                    else if(idx_start_search>0) idx_start_search--;
				    print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
				else if(strlen(search_text)==50&&key!=key_BS){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/16+140,w_win/4-17+30,(char*)"Tu khoa toi da 50 ki tu",3,darkRed);
					settextstyle(font_text,0,sizeS);
					print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
				else{
					if(key==key_BS){
						if(strlen(search_text)==50) out_text_xy(l_win/16+140,w_win/4-17+30,(char*)"Tu khoa toi da 50 ki tu",3,3);
						if(idx_search>0){
							strcpy(search_text + idx_search-1, search_text + idx_search);
							idx_search--;
						}
					    if(idx_start_search>0) idx_start_search--;
					    else if(cursor_pos_search >0) cursor_pos_search--;
		     	    }
		     	    else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'||key==key_SP||key==(int)'-'){
    					insert_chr_to_str(search_text,key,idx_search);
    	                idx_search++;
    					if(cursor_pos_search < 40) cursor_pos_search++;
    					else idx_start_search++;
			    	}
			    	print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
			    	
			    	//reload giao dien
			    	get_index_CList(CList,indexs,n_index,search_text);
			    	last_nPageTable = nPageTable;
	                set_nPageTable(nRow,nPageTable,n_index,page,1);
	                set_CTable(CList, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_class,page_text);  
				}
		    }
		    else if(choose==2){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"Ma lop toi da 11 ki tu",3,3);
                print_text_bar(l_win/2+382,w_win/3-9,CID_text,11,white,white);
			    if(key==key_Right){
                    if(cursor_pos_ML<strlen(CID_text)) cursor_pos_ML++;
				}
			    else if(key==key_Left){
                    if(cursor_pos_ML>0) cursor_pos_ML--;
				}
				else if(key==key_Enter||key==key_Down){
			        if(strlen(CName_text)>24) cursor_pos_TL = idx_TL = 24;
					else cursor_pos_TL = idx_TL = strlen(CName_text);
					xoa(bar_search, choose,search_text, CID_text, CName_text,idx_start_search,idx_start_TL,3,page_text,page_tmp);
				}
				else if(key==key_BS){
					if(cursor_pos_ML >0){
						strcpy(CID_text + cursor_pos_ML-1, CID_text + cursor_pos_ML);
						cursor_pos_ML--;
					} 
		  	    }
	    	    else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'||key==(int)'-'){
	    	    	if(strlen(CID_text)==MAX_MALOP){
	            		settextstyle(font_text,0,sizeS-1);
						out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"Ma lop toi da 11 ki tu",3,darkRed);
				    }
				    else{
				    	ch = (char)key;
						upper_chr(ch); 
    	   				insert_chr_to_str(CID_text,ch,cursor_pos_ML);
    			    	if(cursor_pos_ML < 11) cursor_pos_ML++;
					}
			    }
			    print_text_bar(l_win/2+382,w_win/3-9,CID_text,11,white,black);
		    }
		    else if(choose==3){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+277,w_win/3+83+30,(char*)"Ma lop toi da 50 ki tu",3,3);
				print_text_bar(l_win/2+277,w_win/3+83,CName_text+idx_start_TL,24,white,white);
			    if(key==key_Right){
					if(idx_TL<strlen(CName_text)){
						idx_TL++; 
						if(cursor_pos_TL==24) idx_start_TL++;
					} 
                    if(cursor_pos_TL<24&&cursor_pos_TL<strlen(CName_text)) cursor_pos_TL++;
				}
			    else if(key==key_Left){
                    if(idx_TL>0) idx_TL--; 
                    if(cursor_pos_TL>0) cursor_pos_TL--;
                    else if(idx_start_TL>0) idx_start_TL--;
				}
				else if(key==key_Up){
					fix_str2(CName_text);
					idx_start_TL = 0;
				    cursor_pos_ML = strlen(CID_text);
					xoa(bar_search, choose,search_text, CID_text, CName_text,idx_start_search,idx_start_TL,2,page_text,page_tmp);
				}
				else if(key==key_BS){
				 	if(idx_TL>0){
						strcpy(CName_text + idx_TL-1, CName_text + idx_TL);
						idx_TL--;
					}
				    if(idx_start_TL>0) idx_start_TL--;
					else if(cursor_pos_TL >0) cursor_pos_TL--;
		  	    }
				else if(strlen(CName_text)==MAX_TENLOP){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/2+277,w_win/3+83+30,(char*)"Ten lop toi da 50 ki tu",3,darkRed);
				}
	    	    else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'||key==(int)'-'||key==' '){
	    	    	if(key==' '){
	    	    		if(cursor_pos_TL==0){
	    	    			print_text_bar(l_win/2+277,w_win/3+83,CName_text+idx_start_TL,24,white,black);
	    	    			continue;
						}
					}
					insert_chr_to_str(CName_text,key,idx_TL);
    	            idx_TL++;
    		    	if(cursor_pos_TL < 24) cursor_pos_TL++;
    				else idx_start_TL++;
			    }
			    print_text_bar(l_win/2+277,w_win/3+83,CName_text+idx_start_TL,24,white,black);
		    }
		    else if(choose==4){
		    	settextstyle(font_text,0,sizeM);
				out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,white);
			    if(key==key_Right){
					if(cursor_pos_page<strlen(page_text)) cursor_pos_page++;
				}
			    else if(key==key_Left){
                    if(cursor_pos_page>0) cursor_pos_page--;
				}
				else if(key==key_BS){
				 	if(cursor_pos_page>0){
				 		strcpy(page_text+cursor_pos_page-1,page_text+cursor_pos_page);
				 		cursor_pos_page--;
					}
		  	    }
	    	    else if(key>='0'&&key<='9'){
	    	    	if(key!='0'||cursor_pos_page!=0){
	    	   	    	insert_chr_to_str(page_text,key,cursor_pos_page);
	    	    		if(atoi(page_text)>nPageTable){
	    	    		itoa(nPageTable,page_text,decimal);
	    	    		cursor_pos_page = nPageTable/10 + 1;
						}
    					else cursor_pos_page++;
					}
			    }
			    else if(key==key_Enter){
			    	choose = 0;	
                 	if(strlen(page_text)==0) strcpy(page_text,itoa(page_tmp,buff,decimal));
			    	else {
			    		page = atoi(page_text);
			    		set_CTable(CList, ROWTBs, indexs, n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,idx_class,page_text);
					}
				}
				settextstyle(font_text,0,sizeM);
				out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
			}
		}
	}	
}

//GIAO DIEN CAU HOI - CHO GV XEM
void get_ID_questList(PTRSUB &subNode, int IDs[], int& n_index, char* search_text){//lay ID cua tat ca cau hoi 
	n_index = 0;
	questList qList=subNode->subi4.ql;
	char buff[len_ID+MAX_ND+1],buff1[10], buff2[len_ID+MAX_ND+1];
	strcpy(buff,search_text);
	delete_blks_str(buff);
	upper_str(buff);
	for(int i=0;i<qList.n;i++){
		itoa(qList.Q[i].ID,buff1,decimal);
		strcpy(buff2,buff1);
		strcat(buff2,qList.Q[i].NoiDung);
		delete_blks_str(buff2);
		upper_str(buff2);
		if(strstr(buff2,buff)!=NULL) IDs[n_index++] = qList.Q[i].ID;

	}
}
void questionList_interface(int ID_now,char* subjID){
	char buff[10];
	settextstyle(font_text,0,sizeM);
	out_text_xy(l_win/16-30,w_win/4,(char *)"TIM KIEM:",3,black);
	out_text_xy(l_win/2+20,w_win/3-40,(char*)"ID:",3,black);
	out_text_xy(l_win/2+260,w_win/3-40,(char*)"MA MH:",3,black);
	out_text_xy(l_win/2+20,w_win/3+25,(char*)"ND:",3,black);
	out_text_xy(l_win/2+20,w_win/3+90,(char*)"A:",3,black);
	out_text_xy(l_win/2+300,w_win/3+90,(char*)"B:",3,black);
	out_text_xy(l_win/2+20,w_win/3+155,(char*)"C:",3,black);
	out_text_xy(l_win/2+300,w_win/3+155,(char*)"D:",3,black);
	out_text_xy(l_win/2+20,w_win/3+220,(char*)"DÁP ÁN:",3,black);
	settextstyle(font_text,0,sizeM+1);
	out_text_xy(l_win/2+150,w_win/5-10,(char*)"THONG TIN CAU HOI",3,black);
	settextstyle(font_text,0,sizeS);
	out_text_xy(l_win/16-50,w_win/3,(char*)"Click chuot trai tai 1 dong de chinh sua hoac xoa",3,darkRed);
	create_1_bar_text(l_win/2+70,w_win/3-42,120,30,darkWhite,white,itoa(ID_now,buff,decimal),sizeS,darkRed,CENTER);
	create_1_bar_text(l_win/2+350,w_win/3-40,220,30,darkWhite,white,subjID,sizeS,darkRed,CENTER);
	create_1_bar(l_win/2+70,w_win/3+23,500,30,white,white);
	create_1_bar(l_win/2+50,w_win/3+88,230,30,white,white);
	create_1_bar(l_win/2+340,w_win/3+88,230,30,white,white);
	create_1_bar(l_win/2+50,w_win/3+153,230,30,white,white);
	create_1_bar(l_win/2+340,w_win/3+153,230,30,white,white);
    setcolor(darkRed);
	rectangle(l_win/2+270,w_win/2+170,l_win/2+580,w_win/2+280);
	setcolor(black);
	rectangle(l_win/2+275,w_win/2+175,l_win/2+575,w_win/2+275);
	create_table(22,w_win/3+25,lengthsQuesTable,30,2,1,quesTable,sizeM,black,darkWhite,black);
	create_1_bar(l_win/4-70,w_win-70,100,30,white,white);
	buff[1] = '\0';
	for(int i=0;i<4;i++){
		buff[0] = 'A' + i;
		out_text_xy(l_win/2+190+100*i,w_win/3+220,buff,3,darkBlue);
	} 
}
void question_List(PTRSUB &root,PTRSUB &subNode,BUTTON Menu[], int& tt){
	int ID_now=getMAXID(subNode->subi4.ql,subNode->subi4.MAMH)+1;
	questionList_interface(ID_now,subNode->subi4.MAMH); 
	settextstyle(font_text,0,sizeM-1);
	out_text_xy(l_win/100+16,w_win/7+10,subNode->subi4.MAMH,3,darkBlue);
	out_text_xy(l_win/100+16,w_win/7+10+20,subNode->subi4.TENMH,3,darkBlue);
    char ch, ID[6], da ='X', search_text[MAX_TENLOP+MAX_MALOP+2] = {0},ND[MAX_ND+1]={0}, A[MAX_DA+1]={0},B[MAX_DA+1]={0},C[MAX_DA+1]={0},D[MAX_DA+1]={0}, page_text[10]={0} ,buff[10];
	int x, y, hover=-1, j, s=0, sub_tt , key,sub_page = 1, cursor_pos_search = 0, idx_start_search=0, idx_search = 0;
	int cursor_pos_ND = 0, cursor_pos_A = 0, cursor_pos_B = 0, cursor_pos_C = 0, cursor_pos_D=0,cursor_pos_DA=0;
	int idx_start_ND = 0, idx_start_A = 0, idx_start_B = 0,idx_start_C = 0,idx_start_D= 0,idx_ND= 0, idx_A = 0,idx_B = 0,idx_C= 0,idx_D=0, print_s = 0, cursor_pos_page =0;
	int choose = 0, n = T_cursor+1, page = 1, IDs[500] = {-1}, n_index, nRow =0,nPageTable,last_nPageTable=-1, page_tmp, is_fix =0, ID_choose =0, ID2;
	AREA NoiDung, CauA, CauB, CauC, CauD, DapAn, pageArea;
	BUTTON exit, page_after, page_before, bar_search, clear, THEM, LUU, XOA, subClear, Return;
	get_ID_questList(subNode,IDs,n_index,search_text);
	set_nPageTable(nRow,nPageTable,n_index,page,1);
	rowTable ROWTBs[10]={};
	CTick DAPAN[4];
	set_buttons_quesList(exit,ROWTBs,page,nRow, page_after,page_before, nPageTable,bar_search,clear, NoiDung, CauA,CauB,CauC,CauD,THEM,LUU,XOA,subClear,pageArea,Return,DAPAN);
	set_quesTable(subNode->subi4.ql, ROWTBs, IDs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);
	questInfor quesi4;
    int idx_Q;
	while(1){
		delay(1);
		if(s && print_s) inform6(s,sub_tt,itoa(ID2,buff,decimal),print_s);
		if(choose==1) print_cursor(l_win/16+110+cursor_pos_search*(lth_sizeM-2),w_win/4+5,n);
		else if(choose==2) print_cursor(l_win/2+77+cursor_pos_ND*(lth_sizeM-2),w_win/3+28,n);
		else if(choose==3) print_cursor(l_win/2+57+cursor_pos_A*(lth_sizeM-2),w_win/3+93,n);
		else if(choose==4) print_cursor(l_win/2+347+cursor_pos_B*(lth_sizeM-2),w_win/3+93,n);
		else if(choose==5) print_cursor(l_win/2+57+cursor_pos_C*(lth_sizeM-2),w_win/3+158,n);
		else if(choose==6) print_cursor(l_win/2+347+cursor_pos_D*(lth_sizeM-2),w_win/3+158,n);
		else if(choose==7) print_cursor(l_win/4-20-strlen(page_text)/2.0*(lth_sizeM)+cursor_pos_page*lth_sizeM,w_win-65,n);
		if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE,x,y);
			set_hover_CList(Menu, ROWTBs,hover,j,tt,x,y,nRow,clear,LUU,subClear,THEM,XOA);
	        if(j!=hover&&j!=-1){
	        	if(j<nLecMenu) draw_button(Menu[j]);
	        	else if(j==11) draw_button(clear);
	        	else if(j==12) {
	        		if(is_fix||sub_page==1) draw_button(subClear);
				}
	        	else if(j==13) draw_button(THEM);	
	        	else if(j==14){
	        		if(sub_page==2&&!is_fix) draw_button(XOA);
				} 
	        	else if(j==15) {
	        		if(sub_page==2) draw_button(LUU);
				}
 	        	else if(j<100+nRow)  draw_rowTable(ROWTBs[j-100]);
	        	if(hover<nLecMenu) highlight_button(Menu[hover],grey,white,white);
	        	else if(hover==11) highlight_button(clear,grey,white,white);
	        	else if(hover==12){
	        		if(is_fix||sub_page==1) highlight_button(subClear,grey,white,white);
				}
	        	else if(hover==13) highlight_button(THEM,grey,white,white);	
	        	else if(hover==14){
	        		if(sub_page==2&&!is_fix) highlight_button(XOA,grey,white,white);
				} 
	        	else if(hover==15){
	        		if(sub_page==2) highlight_button(LUU,grey,white,white);
				} 
	        	else if(hover<100+nRow) highlight_rowTable(ROWTBs[hover-100],grey,black,white);  
			}
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for(int i=0;i<nLecMenu;i++){
				if(i==tt) continue;
	         	if(is_area(Menu[i].area,x,y)){
	         		create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		        	Menu[tt].area.width+5,3,3);
		        	draw_button(Menu[tt]);
		        	tt=i;
	         		return;
				}
		    }
		    if(sub_page==1||is_fix){
		    	for(int i=0;i<4;i++){
			    	if(is_area_CTick(DAPAN[i],x,y)){
			    		out_text_xy(l_win/2+150,w_win/3+215+30,(char*)"                     ",3,3);
			    		for(int j=0;j<4;j++){
			    			if(j==i) {
			    				da = 'A' +j;
			    				Tick_CTick(DAPAN[j],black);
							}
			    			else draw_CTick(DAPAN[j]);
						}
						break;
					}
				}
			}
		    for(int i=0;i<nRow;i++){
		    	if(is_rowTable(ROWTBs[i],x,y)){
		    		settextstyle(font_text,0,sizeS);
		    		clear_notice_quesi4();
			        idx_start_ND = 0;
			        idx_start_A = 0;
			        idx_start_B = 0;
			        idx_start_C =0;
			        idx_start_D =0;
			        ID_choose = IDs[(page-1)*10+i];
			        create_1_bar_text(l_win/2+70,w_win/3-42,120,30,darkWhite,darkRed,itoa(ID_choose,buff,decimal),sizeS,darkRed,CENTER);
			        create_1_bar_text(l_win/2+350,w_win/3-40,220,30,darkWhite,darkRed,subNode->subi4.MAMH,sizeS,darkRed,CENTER);
					idx_Q = Search_Quest(subNode->subi4.ql,ID_choose);
					if(sub_page==1||is_fix){
		    			set_bar_edit_quesi4(red);
              		   	strcpy(LUU.text,"SUA");
        		   	    draw_button2(LUU);
				        draw_button2(XOA);
			            highlight_button2(subClear,darkWhite,white,white);
			            strcpy(THEM.text,"BACK");
			            draw_button2(THEM);
			            sub_page = 2;
			            if(is_fix) is_fix=0;
			    	}
			    	else clear_edit_quesi4(ND,idx_start_ND,A,idx_start_A,B,idx_start_B,C,idx_start_C,D,idx_start_D);
					strcpy(ND,subNode->subi4.ql.Q[idx_Q].NoiDung);
		    		strcpy(A,subNode->subi4.ql.Q[idx_Q].A);
		    		strcpy(B,subNode->subi4.ql.Q[idx_Q].B);
		    		strcpy(C,subNode->subi4.ql.Q[idx_Q].C);
					strcpy(D,subNode->subi4.ql.Q[idx_Q].D);
					da = subNode->subi4.ql.Q[idx_Q].DapAn;
			    	print_text_bar(l_win/2+77,w_win/3+28,ND+idx_start_ND ,40,white,black);
					print_text_bar(l_win/2+57,w_win/3+93,A+idx_start_A,18,white,black);
					print_text_bar(l_win/2+347,w_win/3+93,B+idx_start_B,18,white,black);
					print_text_bar(l_win/2+57,w_win/3+158,C+idx_start_C,18,white,black);
					print_text_bar(l_win/2+347,w_win/3+158,D+idx_start_D,18,white,black);
			        for(int j=0;j<4;j++){
			    		if('A'+j==da) Tick_CTick(DAPAN[j],darkRed);
			    		else draw_CTick(DAPAN[j]);
				    }
		            if(choose!=1) {
		            	choose=0;
		            	continue;
					}
				}
			}
			if(is_area(Return.area,x,y)) return;
			else if(is_area(exit.area,x,y)){
				create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		       	Menu[tt].area.width+5,3,3);
		       	draw_button(Menu[tt]);
		       	delete_button(exit,3);
				tt=-1;
				return;
			}
			else if(is_area(page_after.area,x,y)){
				if(page<nPageTable){
				    page++;
				    set_quesTable(subNode->subi4.ql, ROWTBs, IDs ,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);	
				}
			}		  
			else if(is_area(page_before.area,x,y)){
				if(page>1){
				    page--;
				    set_quesTable(subNode->subi4.ql, ROWTBs, IDs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);
			    }
			}
			else if(is_area(THEM.area,x,y)){
				idx_start_ND = idx_start_A = idx_start_B = idx_start_C = idx_start_D = 0;
				if(sub_page==1){
					xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D, choose,0,page_text,page_tmp);
					settextstyle(font_text,0,sizeS);
					clear_notice_quesi4();
					if(strlen(ND)==0) out_text_xy(l_win/2+77,w_win/3+28+30,(char*)"Nhap noi dung CH",3,red);
					if(strlen(A)==0) out_text_xy(l_win/2+57,w_win/3+93+30,(char*)"Nhap dap an A",3,red);
					if(strlen(B)==0) out_text_xy(l_win/2+347,w_win/3+93+30,(char*)"Nhap dap an B",3,red);
				    if(strlen(C)==0) out_text_xy(l_win/2+57,w_win/3+158+30,(char*)"Nhap dap an C",3,red);
					if(strlen(D)==0) out_text_xy(l_win/2+347,w_win/3+158+30,(char*)"Nhap dap an D",3,red);
					if(da == 'X') out_text_xy(l_win/2+150,w_win/3+215+30,(char*)"Chon dap an dung",3,red);
					else if(strcmp(A,B) == 0 || strcmp(B,C) == 0 || strcmp(C,D) ==0 || strcmp(A,C) ==0 || strcmp(A,D)==0 || strcmp(B,D)== 0 ) out_text_xy(l_win/2+150,w_win/3+215+30,(char*)"Dap an khong duoc trung",3,red);
					else if (strlen(ND)!=0&&strlen(A)!=0&&strlen(B)!=0&&strlen(C)!=0&&strlen(D)!=0&&da!='X'){
						set_quesInfor(quesi4,ID_now,ND,A,B,C,D,da);
						if(Insert_Quest(subNode->subi4.ql,quesi4)){
						ID2 = ID_now;
						ID_now=getMAXID(subNode->subi4.ql,subNode->subi4.MAMH)+1;
						create_1_bar_text(l_win/2+70,w_win/3-42,120,30,darkWhite,white,itoa(ID_now,buff,decimal),sizeS,darkRed,CENTER);
						s = 200, sub_tt = 1, print_s =1;
						n_index=0;
				    	get_ID_questList(subNode,IDs,n_index,search_text);
				    	last_nPageTable = nPageTable;
			            set_nPageTable(nRow,nPageTable,n_index,page,1);
			            set_quesTable(subNode->subi4.ql, ROWTBs, IDs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);}
			            
			            else out_text_xy(l_win/2+290,w_win/2+180,(char*)"DS CH da day",3,darkRed);
			            
		                clear_edit_quesi4(ND,idx_start_ND,A,idx_start_A,B,idx_start_B,C,idx_start_C,D,idx_start_D);
			    		reset_quesi4(ND,cursor_pos_ND,idx_start_ND,idx_ND,A,cursor_pos_A,idx_start_A,idx_A,B,cursor_pos_B,idx_start_B,idx_B,C,cursor_pos_C,idx_start_C,idx_C,D,cursor_pos_D,idx_start_D,idx_D,da);
						n= T_cursor+1;
				    }
				}
				else{
					strcpy(THEM.text,"THEM");
					draw_button(THEM);
					if(is_fix){
						strcpy(LUU.text,"SUA");
						is_fix =0;
					} 
					else{
						highlight_button(XOA,darkWhite,white,white);	
     					draw_button(subClear);
					} 
					highlight_button(LUU,darkWhite,white,white);
                    set_bar_edit_quesi4(white);
    		    	
					reset_quesi4(ND,cursor_pos_ND,idx_start_ND,idx_ND,A,cursor_pos_A,idx_start_A,idx_A,B,cursor_pos_B,idx_start_B,idx_B,C,cursor_pos_C,idx_start_C,idx_C,D,cursor_pos_D,idx_start_D,idx_D,da);
					create_1_bar_text(l_win/2+70,w_win/3-42,120,30,darkWhite,white,itoa(ID_now,buff,decimal),sizeS,darkRed,CENTER);
					create_1_bar_text(l_win/2+350,w_win/3-40,220,30,darkWhite,white,subNode->subi4.MAMH,sizeS,darkRed,CENTER);
					n= T_cursor+1;
    				sub_page=1;
					choose = 0;				
				}
			}
			else if(is_area(bar_search.area,x,y)){
				n = T_cursor +1;
				if(strlen(search_text)==0) highlight_button(bar_search,white,white,white);
				xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D, choose,1,page_text,page_tmp);
				cursor_pos_search = (x - (l_win/16+110))/(lth_sizeM-2);
			    if (cursor_pos_search>strlen(search_text)&&strlen(search_text)<25) cursor_pos_search = strlen(search_text);
			    else if(cursor_pos_search>25) cursor_pos_search=25;
			    idx_search = idx_start_search +cursor_pos_search;
			}
			else if(is_area(NoiDung,x,y)&&(sub_page==1||is_fix)){
				n = T_cursor +1;
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+77,w_win/3+28+30,(char*)"Toi da 300 ki tu ",3,3);
				xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D, choose,2,page_text,page_tmp);
				cursor_pos_ND = (x - (l_win/2+77))/(lth_sizeM-2);
			    if (cursor_pos_ND>strlen(ND)&&strlen(ND)<40) cursor_pos_ND = strlen(ND);
			    else if(cursor_pos_ND>40) cursor_pos_ND=40;
			    idx_ND = idx_start_ND +cursor_pos_ND;
			}
			else if(is_area(CauA,x,y)&&(sub_page==1||is_fix)){
				n = T_cursor +1;
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+57,w_win/3+93+30,(char*)"Toi da 18 ki tu ",3,3);
				xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,3,page_text,page_tmp);
			    cursor_pos_A = (x - (l_win/2+50))/(lth_sizeM-2);
			    if (cursor_pos_A>strlen(A)&&strlen(A)<18) cursor_pos_A = strlen(A);
			    else if(cursor_pos_A>18) cursor_pos_A=18;
			    idx_A = idx_start_A + cursor_pos_A;
			}
			else if(is_area(CauB,x,y)&&(sub_page==1||is_fix)){
				n = T_cursor +1;
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+347,w_win/3+93+30,(char*)"Toi da 18 ki tu ",3,3);
				xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,4,page_text,page_tmp);
			    cursor_pos_B = (x - (l_win/2+340))/(lth_sizeM-2);
			    if (cursor_pos_B>strlen(B)&&strlen(B)<18) cursor_pos_B = strlen(B);
			    else if(cursor_pos_B>18) cursor_pos_B=18;
			    idx_B = idx_start_B + cursor_pos_B;
			}
			else if(is_area(CauC,x,y)&&(sub_page==1||is_fix)){
				n = T_cursor +1;
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+57,w_win/3+158+30,(char*)"Toi da 18 ki tu ",3,3);
				xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,5,page_text,page_tmp);
			    cursor_pos_C = (x - (l_win/2+50))/(lth_sizeM-2);
			    if (cursor_pos_C>strlen(C)&&strlen(C)<18) cursor_pos_C = strlen(C);
			    else if(cursor_pos_C>18) cursor_pos_C=18;
			    idx_C = idx_start_C + cursor_pos_C;
			}
			else if(is_area(CauD,x,y)&&(sub_page==1||is_fix)){
				n = T_cursor +1;
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+347,w_win/3+158+30,(char*)"Toi da 18 ki tu ",3,3);
				xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,6,page_text,page_tmp);
			    cursor_pos_D = (x - (l_win/2+340))/(lth_sizeM-2);
			    if (cursor_pos_D>strlen(D)&&strlen(D)<18) cursor_pos_D = strlen(D);
			    else if(cursor_pos_D>18) cursor_pos_D=18;
			    idx_D = idx_start_D + cursor_pos_D;
			}
			else if(is_area(clear.area,x,y)){
				search_text[0]='\0';
				cursor_pos_search = 0;
				idx_start_search = 0;
				idx_search =0;
				if(choose!=1){
					choose=0;
					draw_button(bar_search);
                }
				else{
					n = T_cursor+1;
        	        highlight_button(bar_search,white,white,white);
				}
				get_ID_questList(subNode,IDs,n_index,search_text);
			    set_nPageTable(nRow,nPageTable,n_index,page,1);
	            last_nPageTable = nPageTable;
	 		    set_quesTable(subNode->subi4.ql, ROWTBs, IDs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);
			}
			else if(is_area(subClear.area,x,y)&&(sub_page==1||is_fix)){
			    clear_notice_quesi4();
		    	clear_edit_quesi4(ND,idx_start_ND,A,idx_start_A,B,idx_start_B,C,idx_start_C,D,idx_start_D);
				reset_quesi4(ND,cursor_pos_ND,idx_start_ND,idx_ND,A,cursor_pos_A,idx_start_A,idx_A,B,cursor_pos_B,idx_start_B,idx_B,C,cursor_pos_C,idx_start_C,idx_C,D,cursor_pos_D,idx_start_D,idx_D,da);
				n= T_cursor+1;
				xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,0,page_text,page_tmp);
			}
			else if(is_area(XOA.area,x,y)&&(sub_page==2&&!is_fix)){
				if(subNode->subi4.ql.Q[idx_Q].done == 'T') {
					s = 200, sub_tt = 4, print_s =1;
					continue;
			    }
				else if(!is_delete(itoa(ID_choose,buff,decimal),4)) continue;
				if(Delete_Quest(subNode->subi4.ql,ID_choose)){
				s = 200, sub_tt = 2, print_s =1;
				ID2 = ID_choose;
				create_1_bar_text(l_win/2+70,w_win/3-42,120,30,darkWhite,white,itoa(ID_now,buff,decimal),sizeS,darkRed,CENTER);

				get_ID_questList(subNode,IDs,n_index,search_text);
			    last_nPageTable = nPageTable;
			    set_nPageTable(nRow,nPageTable,n_index,page,1);
			    set_quesTable(subNode->subi4.ql, ROWTBs, IDs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);}
			    

           		strcpy(THEM.text,"THEM");
				draw_button(THEM);
				highlight_button(XOA,darkWhite,white,white);
				if(!is_fix) draw_button(subClear);
				highlight_button(LUU,darkWhite,white,white);
    	    	set_bar_edit_quesi4(white);
				reset_quesi4(ND,cursor_pos_ND,idx_start_ND,idx_ND,A,cursor_pos_A,idx_start_A,idx_A,B,cursor_pos_B,idx_start_B,idx_B,C,cursor_pos_C,idx_start_C,idx_C,D,cursor_pos_D,idx_start_D,idx_D,da);
				choose=0;
				sub_page =1;	
			}
			else if(is_area(LUU.area,x,y)&&sub_page==2){
				if(subNode->subi4.ql.Q[idx_Q].done == 'T') {
					s = 200, sub_tt = 5, print_s =1;
					continue;
			    }
				if(is_fix==0){
					highlight_button(XOA,darkWhite,white,white);
					strcpy(LUU.text,"LUU");
					draw_button(LUU);
					draw_button(subClear);
					set_bar_edit_quesi4(white);
					print_text_bar(l_win/2+77,w_win/3+28,ND+idx_start_ND ,40,white,black);
					print_text_bar(l_win/2+57,w_win/3+93,A+idx_start_A,18,white,black);
					print_text_bar(l_win/2+347,w_win/3+93,B+idx_start_B,18,white,black);
					print_text_bar(l_win/2+57,w_win/3+158,C+idx_start_C,18,white,black);
					print_text_bar(l_win/2+347,w_win/3+158,D+idx_start_D,18,white,black);
			        for(int j=0;j<4;j++){
			    		if('A'+j==da) Tick_CTick(DAPAN[j],black);
			    		else draw_CTick(DAPAN[j]);
				    }
					is_fix = 1;
				}
				else{
					xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,0,page_text,page_tmp);
					clear_notice_quesi4();
					if(strlen(ND)==0) out_text_xy(l_win/2+77,w_win/3+28+30,(char*)"Nhap noi dung CH",3,red);
					if(strlen(A)==0) out_text_xy(l_win/2+57,w_win/3+93+30,(char*)"Nhap dap an A",3,red);
					if(strlen(B)==0) out_text_xy(l_win/2+347,w_win/3+93+30,(char*)"Nhap dap an B",3,red);
				    if(strlen(C)==0) out_text_xy(l_win/2+57,w_win/3+158+30,(char*)"Nhap dap an C",3,red);
					if(strlen(D)==0) out_text_xy(l_win/2+347,w_win/3+158+30,(char*)"Nhap dap an D",3,red);
					if(da == 'X') out_text_xy(l_win/2+150,w_win/3+215+30,(char*)"Chon dap an dung",3,red);
					else if(strcmp(A,B) == 0 || strcmp(B,C) == 0 || strcmp(C,D) ==0 || strcmp(A,C) ==0 || strcmp(A,D)==0 || strcmp(B,D)== 0 ) out_text_xy(l_win/2+150,w_win/3+215+30,(char*)"Dap an khong duoc trung",3,red);
					else if(strlen(ND)!=0&&strlen(A)!=0&&strlen(B)!=0&&strlen(C)!=0&&strlen(D)!=0&&da!='X'){
						set_quesInfor(subNode->subi4.ql.Q[idx_Q],ID_choose,ND,A,B,C,D,da); 
						s = 200, sub_tt = 3, print_s =1;
						ID2 = ID_choose; 
						create_1_bar_text(l_win/2+70,w_win/3-42,120,30,darkWhite,white,itoa(ID_now,buff,decimal),sizeS,darkRed,CENTER);
						get_ID_questList(subNode,IDs,n_index,search_text);
				    	last_nPageTable = nPageTable;
			            set_nPageTable(nRow,nPageTable,n_index,page,1);
			            set_quesTable(subNode->subi4.ql, ROWTBs, IDs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);
		               	strcpy(THEM.text,"THEM");
						draw_button(THEM);
						highlight_button(LUU,darkWhite,white,white);
		   		    	clear_edit_quesi4(ND,idx_start_ND,A,idx_start_A,B,idx_start_B,C,idx_start_C,D,idx_start_D);
			    		reset_quesi4(ND,cursor_pos_ND,idx_start_ND,idx_ND,A,cursor_pos_A,idx_start_A,idx_A,B,cursor_pos_B,idx_start_B,idx_B,C,cursor_pos_C,idx_start_C,idx_C,D,cursor_pos_D,idx_start_D,idx_D,da);
						sub_page = 1;	
						is_fix = 0;						
					} 
				}
			}
			else if(is_area(pageArea,x,y)){
				xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,7,page_text,page_tmp);
				if(page==0) continue; 
				page_tmp = page;
				cursor_pos_page = (x -((l_win/4-20)-strlen(page_text)*(lth_sizeM)/2.0))/lth_sizeM;
				if(cursor_pos_page<0) cursor_pos_page = 0;
				else if(cursor_pos_page>strlen(page_text)) cursor_pos_page = strlen(page_text);
				n = T_cursor+1;
			}
			else xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,0,page_text,page_tmp);
			settextstyle(font_text,0,sizeM);
			if(choose==1) print_text_bar(l_win/16+110,w_win/4+5,search_text+idx_start_search,25,white,black);
			else if(choose==2) print_text_bar(l_win/2+77,w_win/3+28,ND+idx_start_ND ,40,white,black);
			else if(choose==3) print_text_bar(l_win/2+57,w_win/3+93,A+idx_start_A,18,white,black);
			else if(choose==4) print_text_bar(l_win/2+347,w_win/3+93,B+idx_start_B,18,white,black);
			else if(choose==5) print_text_bar(l_win/2+57,w_win/3+158,C+idx_start_C,18,white,black);
			else if(choose==5) print_text_bar(l_win/2+347,w_win/3+158,D+idx_start_D,18,white,black);
			else if(choose==7) out_text_xy(l_win/4-20-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
		}
		if(kbhit()){
			n = T_cursor+1;
			key = Key();
			if(choose == 1){
				settextstyle(font_text,0,sizeS);
                print_text_bar(l_win/16+110,w_win/4+5,search_text+idx_start_search,25,white,white);
			    if(key==key_Right){
					if(idx_search<strlen(search_text)){
						idx_search++; 
						if(cursor_pos_search==25) idx_start_search++;
					} 
                    if(cursor_pos_search<25&&cursor_pos_search<strlen(search_text)) cursor_pos_search++;
				    print_text_bar(l_win/16+110,w_win/4+5,search_text+idx_start_search,25,white,black);
				}
			    else if(key==key_Left){
                    if(idx_search>0) idx_search--; 
                    if(cursor_pos_search>0) cursor_pos_search--;
                    else if(idx_start_search>0) idx_start_search--;
				    print_text_bar(l_win/16+110,w_win/4+5,search_text+idx_start_search,25,white,black);
				}
				else if(strlen(search_text)==50&&key!=key_BS){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/16+110,w_win/4+5+30,(char*)"Tu khoa toi da 50 ki tu",3,red);
					settextstyle(font_text,0,sizeS);
					print_text_bar(l_win/16+110,w_win/4+5,search_text+idx_start_search,25,white,black);
				}
				else{
					if(key==key_BS){
						if(idx_search>0){
							strcpy(search_text + idx_search-1, search_text + idx_search);
							idx_search--;
						}
					    if(idx_start_search>0) idx_start_search--;
					    else if(cursor_pos_search >0) cursor_pos_search--;
		     	    }
		     	    else if(key>=key_SP&&key<127){
    					insert_chr_to_str(search_text,key,idx_search);
    	                idx_search++;
    					if(cursor_pos_search < 25) cursor_pos_search++;
    					else idx_start_search++;
			    	}
			    	print_text_bar(l_win/16+110,w_win/4+5,search_text+idx_start_search,25,white,black);
			    	get_ID_questList(subNode,IDs,n_index,search_text);
			    	last_nPageTable = nPageTable;
	                set_nPageTable(nRow,nPageTable,n_index,page,1);
	                set_quesTable(subNode->subi4.ql, ROWTBs, IDs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);
	            }
			}
		    else if(choose==2){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+77,w_win/3+28+30,(char*)"Toi da 300 ki tu",3,3);
		     	print_text_bar(l_win/2+77,w_win/3+28,ND+idx_start_ND,40,white,white);
			    if(key==key_Right){
					if(idx_ND<strlen(ND)){
						idx_ND++; 
						if(cursor_pos_ND==40) idx_start_ND++;
					} 
                    if(cursor_pos_ND<40&&cursor_pos_ND<strlen(ND)) cursor_pos_ND++;
				}
			    else if(key==key_Left){
                    if(idx_ND>0) idx_ND--; 
                    if(cursor_pos_ND>0) cursor_pos_ND--;
                    else if(idx_start_ND>0) idx_start_ND--;
				}
				else if(key==key_Enter||key==key_Down){
					fix_str2(ND);
					idx_start_ND = 0;
			        if(strlen(A)>18) cursor_pos_A = idx_A = 18;
					else cursor_pos_A = idx_A = strlen(A);
				xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,3,page_text,page_tmp);
				}
				else if(key==key_BS){
				 	if(idx_ND>0){
						strcpy(ND + idx_ND-1, ND + idx_ND);
						idx_ND--;
					}
				    if(idx_start_ND>0) idx_start_ND--;
					else if(cursor_pos_ND >0) cursor_pos_ND--;
		  	    }
				else if(strlen(ND)==MAX_ND){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/2+77,w_win/3+28+30,(char*)"Toi da 300 ki tu",3,red);
				}
	    	    else if(key>=key_SP&&key<127){
	    	    	if(key==' '){
	    	    		if(cursor_pos_ND==0){
	    	    			print_text_bar(l_win/2+77,w_win/3+28,ND+idx_start_ND,40,white,black);
	    	    			continue;
						}
					}
					insert_chr_to_str(ND,key,idx_ND);
    	            idx_ND++;
    		    	if(cursor_pos_ND < 40) cursor_pos_ND++;
    				else idx_start_ND++;
			    }
			    print_text_bar(l_win/2+77,w_win/3+28,ND+idx_start_ND,40,white,black);
		    }
		    else if(choose==3){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+57,w_win/3+93+30,(char*)"Toi da 18 ki tu",3,3);
				print_text_bar(l_win/2+57,w_win/3+93,A+idx_start_A,18,white,white);
			    if(key==key_Right){
					if(idx_A<strlen(A)){
						idx_A++; 
						if(cursor_pos_A==18) idx_start_A++;
					} 
                    if(cursor_pos_A<18&&cursor_pos_A<strlen(A)) cursor_pos_A++;
				}
			    else if(key==key_Left){
                    if(idx_A>0) idx_A--; 
                    if(cursor_pos_A>0) cursor_pos_A--;
                    else if(idx_start_A>0) idx_start_A--;
				}
				else if(key==key_Enter||key==key_Down){
					fix_str2(A);
					idx_start_A = 0;
				    if(strlen(B)>18) cursor_pos_B = idx_B= 18;
					else cursor_pos_B = idx_B = strlen(B);
				xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,4,page_text,page_tmp);
				}
				else if(key==key_Up){
					fix_str2(A);
					idx_start_A = 0;
			        if(strlen(ND)>40) cursor_pos_ND = idx_ND = 40;
					else cursor_pos_ND = idx_ND = strlen(ND);
				xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,2,page_text,page_tmp);
				}
				else if(key==key_BS){
				 	if(idx_A>0){
						strcpy(A + idx_A-1, A + idx_A);
						idx_A--;
					}
				    if(idx_start_A>0) idx_start_A--;
					else if(cursor_pos_A >0) cursor_pos_A--;
		  	    }
				else if(strlen(A)==MAX_DA){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/2+57,w_win/3+93+30,(char*)"Toi da 200 ki tu",3,red);
				}
	    	    else if(key>=key_SP&&key<127){
	    	    	if(key==' '){
	    	    		if(cursor_pos_A==0){
	    	    			print_text_bar(l_win/2+57,w_win/3+93,A+idx_start_A,18,white,black);
	    	    			continue;
						}
					}
					insert_chr_to_str(A,key,idx_A);
    	            idx_A++;
    		    	if(cursor_pos_A < 18) cursor_pos_A++;
    				else idx_start_A++;
			    }
			    print_text_bar(l_win/2+57,w_win/3+93,A+idx_start_A,18,white,black);
		    }
		    else if(choose==4){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+347,w_win/3+93+30,(char*)"Toi da 18 ki tu",3,3);
				print_text_bar(l_win/2+347,w_win/3+93,B+idx_start_B,18,white,white);
			    if(key==key_Right){
					if(idx_B<strlen(B)){
						idx_B++; 
						if(cursor_pos_B==18) idx_start_B++;
					} 
                    if(cursor_pos_B<18&&cursor_pos_B<strlen(B)) cursor_pos_B++;
				}
			    else if(key==key_Left){
                    if(idx_B>0) idx_B--; 
                    if(cursor_pos_B>0) cursor_pos_B--;
                    else if(idx_start_B>0) idx_start_B--;
				}
				else if(key==key_Enter||key==key_Down){
					fix_str2(B);
					idx_start_B = 0;
				    if(strlen(C)>18) cursor_pos_C = idx_C= 18;
					else cursor_pos_C = idx_C = strlen(C);
				xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,5,page_text,page_tmp);
				}
				else if(key==key_Up){
					fix_str2(B);
					idx_start_B = 0;
			        if(strlen(A)>18) cursor_pos_A = idx_A = 18;
					else cursor_pos_A = idx_A = strlen(A);
					xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,3,page_text,page_tmp);
				}
				else if(key==key_BS){
				 	if(idx_B>0){
						strcpy(B + idx_B-1, B + idx_B);
						idx_B--;
					}
				    if(idx_start_B>0) idx_start_B--;
					else if(cursor_pos_B >0) cursor_pos_B--;
		  	    }
				else if(strlen(B)==MAX_DA){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/2+347,w_win/3+93+30,(char*)"Toi da 200 ki tu",3,red);
				}
	    	    else if(key>=key_SP&&key<127){
	    	    	if(key==' '){
	    	    		if(cursor_pos_B==0){
	    	    			print_text_bar(l_win/2+347,w_win/3+93,B+idx_start_B,18,white,black);
	    	    			continue;
						}
					}
					insert_chr_to_str(B,key,idx_B);
    	            idx_B++;
    		    	if(cursor_pos_B < 18) cursor_pos_B++;
    				else idx_start_B++;
			    }
			    print_text_bar(l_win/2+347,w_win/3+93,B+idx_start_B,18,white,black);
		    }
		    else if(choose==5){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+57,w_win/3+158+30,(char*)"Toi da 18 ki tu",3,3);
				print_text_bar(l_win/2+57,w_win/3+158,C+idx_start_C,18,white,white);
			    if(key==key_Right){
					if(idx_C<strlen(C)){
						idx_C++; 
						if(cursor_pos_C==18) idx_start_C++;
					} 
                    if(cursor_pos_C<18&&cursor_pos_C<strlen(C)) cursor_pos_C++;
				}
			    else if(key==key_Left){
                    if(idx_C>0) idx_C--; 
                    if(cursor_pos_C>0) cursor_pos_C--;
                    else if(idx_start_C>0) idx_start_C--;
				}
				else if(key==key_Enter||key==key_Down){
					fix_str2(C);
					idx_start_C = 0;
				    if(strlen(D)>18) cursor_pos_D = idx_D= 18;
					else cursor_pos_D = idx_D = strlen(D);
					xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,6,page_text,page_tmp);
				}
				else if(key==key_Up){
					fix_str2(C);
					idx_start_C = 0;
			        if(strlen(B)>18) cursor_pos_B = idx_B = 18;
					else cursor_pos_B = idx_B = strlen(B);
					xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,4,page_text,page_tmp);
				}
				else if(key==key_BS){
				 	if(idx_C>0){
						strcpy(C + idx_C-1, C + idx_C);
						idx_C--;
					}
				    if(idx_start_C>0) idx_start_C--;
					else if(cursor_pos_C >0) cursor_pos_C--;
		  	    }
				else if(strlen(C)==MAX_DA){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/2+57,w_win/3+158+30,(char*)"Toi da 200 ki tu",3,red);
				}
	    	    else if(key>=key_SP&&key<127){
	    	    	if(key==' '){
	    	    		if(cursor_pos_C==0){
	    	    			print_text_bar(l_win/2+57,w_win/3+158,C+idx_start_C,18,white,black);
	    	    			continue;
						}
					}
					insert_chr_to_str(C,key,idx_C);
    	            idx_C++;
    		    	if(cursor_pos_C < 18) cursor_pos_C++;
    				else idx_start_C++;
			    }
			    print_text_bar(l_win/2+57,w_win/3+158,C+idx_start_C,18,white,black);
		    }
		    else if(choose==6){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+347,w_win/3+158+30,(char*)"Toi da 18 ki tu",3,3);
				print_text_bar(l_win/2+347,w_win/3+158,D+idx_start_D,18,white,white);
			    if(key==key_Right){
					if(idx_D<strlen(D)){
						idx_D++; 
						if(cursor_pos_D==18) idx_start_D++;
					} 
                    if(cursor_pos_D<18&&cursor_pos_D<strlen(D)) cursor_pos_D++;
				}
			    else if(key==key_Left){
                    if(idx_D>0) idx_D--; 
                    if(cursor_pos_D>0) cursor_pos_D--;
                    else if(idx_start_D>0) idx_start_D--;
				}
				else if(key==key_Up){
					fix_str2(D);
					idx_start_D = 0;
			        if(strlen(C)>18) cursor_pos_C = idx_C = 18;
					else cursor_pos_C = idx_C = strlen(C);
					xoa6(bar_search,search_text,idx_start_search, ND, idx_start_ND, A, idx_start_A, B,idx_start_B, C,idx_start_C,D,idx_start_D ,choose,5,page_text,page_tmp);
				}
				else if(key==key_BS){
				 	if(idx_D>0){
						strcpy(D + idx_D-1, D + idx_D);
						idx_D--;
					}
				    if(idx_start_D>0) idx_start_D--;
					else if(cursor_pos_D >0) cursor_pos_D--;
		  	    }
				else if(strlen(D)==MAX_DA){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/2+347,w_win/3+158+30,(char*)"Toi da 200 ki tu",3,red);
				}
	    	    else if(key>=key_SP&&key<127){
	    	    	if(key==' '){
	    	    		if(cursor_pos_D==0){
	    	    			print_text_bar(l_win/2+347,w_win/3+158,D+idx_start_D,18,white,black);
	    	    			continue;
						}
					}
					insert_chr_to_str(D,key,idx_D);
    	            idx_D++;
    		    	if(cursor_pos_D < 18) cursor_pos_D++;
    				else idx_start_D++;
			    }
			    print_text_bar(l_win/2+347,w_win/3+158,D+idx_start_D,18,white,black);
		    }
		    else if(choose==7){
		    	settextstyle(font_text,0,sizeM);
				out_text_xy(l_win/4-20-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,white);
			    if(key==key_Right){
					if(cursor_pos_page<strlen(page_text)) cursor_pos_page++;
				}
			    else if(key==key_Left){
                    if(cursor_pos_page>0) cursor_pos_page--;
				}
				else if(key==key_BS){
				 	if(cursor_pos_page>0){
				 		strcpy(page_text+cursor_pos_page-1,page_text+cursor_pos_page);
				 		cursor_pos_page--;
					}
		  	    }
	    	    else if(key>='0'&&key<='9'){
	    	    	if(key!='0'||cursor_pos_page!=0){
	    	   	    	insert_chr_to_str(page_text,key,cursor_pos_page);
	    	    		if(atoi(page_text)>nPageTable){
	    	    		itoa(nPageTable,page_text,decimal);
	    	    		cursor_pos_page = nPageTable/10 + 1;
						}
    					else cursor_pos_page++;
					}
			    }
			    else if(key==key_Enter){
			    	choose = 0;	
                 	if(strlen(page_text)==0) strcpy(page_text,itoa(page_tmp,buff,decimal));
			    	else {
			    		page = atoi(page_text);
			    		set_quesTable(subNode->subi4.ql, ROWTBs, IDs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);
					}
				}
				settextstyle(font_text,0,sizeM);
				out_text_xy(l_win/4-20-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
			}
		}
	}	
}

//GIAO DIEN MON HOC - CHO GV XEM
void make_string_subject(char* buff,subInfor& subji4){//HO TRO TIM KIEM THEO MON HOC
	strcpy(buff,subji4.MAMH);
	strcat(buff,subji4.TENMH);
}
void get_index_sub(PTRSUB &subNode,int IDs[],int& n_index, char*buff){
	if(subNode==NULL) return;
	char buff0[MAX_TENMH+MAX_MAMH+1];
	make_string_subject(buff0,subNode->subi4);
	delete_blks_str(buff0);
	upper_str(buff0);
	if(strstr(buff0,buff)!=NULL) IDs[n_index++]=subNode->key;
	get_index_sub(subNode->left,IDs,n_index,buff);
	get_index_sub(subNode->right,IDs,n_index,buff);
}
void get_index_subjList(PTRSUB &root,int IDs[],int &n_index,char* search_text){
	n_index=0;
	char buff[MAX_TENMH+MAX_MAMH+1];
	strcpy(buff,search_text);
	delete_blks_str(buff);
	upper_str(buff);
	get_index_sub(root,IDs,n_index,buff);
}
void subjList_interface(){
	settextstyle(font_text,0,sizeM);
	out_text_xy(l_win/16,w_win/4-17,(char *)"TIM KIEM:",3,black);
	out_text_xy(l_win/2+270,w_win/3-10,(char*)"MA MH:",3,black);
	out_text_xy(l_win/2+270,w_win/3+50,(char*)"TEN MH:",3,black);
	settextstyle(font_text,0,sizeM+1);
	out_text_xy(l_win/2+295,w_win/5+10,(char*)"THONG TIN MH",3,black);
	settextstyle(font_text,0,sizeS);
	out_text_xy(l_win/16,w_win/3,(char*)"Click chuot trai tai 1 dong de chinh sua hoac xoa",3,darkRed);
	create_table(l_win/16,w_win/3+25,lengthsSubjTable,30,4,1,subjTable,sizeM,black,darkWhite,black); 
	create_1_bar(l_win/2+365,w_win/3-12,210,30,white,white);
	create_1_bar(l_win/2+270,w_win/3+80,310,30,white,white);
    create_1_bar(l_win/4+50,w_win-70,100,30,white,white);
    setcolor(darkRed);
	rectangle(l_win/2+270,w_win/2+170,l_win/2+580,w_win/2+280);
	setcolor(black);
	rectangle(l_win/2+275,w_win/2+175,l_win/2+575,w_win/2+275);
}
void edit_subji4_of_CList(classList& CList,char* old_subjID,char* new_subjID){//sua ma mon hoc trong danh sach diem cua tat ca sinh vien cac lop
	PTRS SF;
	PTRM MNode;
	for(int i=0;i<CList.nClass;i++){
		SF = CList.classes[i]->SFirst;
        for(PTRS SNode = SF; SNode!=NULL; SNode=SNode->Next){
        	MNode = search_MList_MMH(SNode->MFirst,old_subjID);
        	if(MNode!=NULL) strcpy(MNode->marki4.Mamh,new_subjID);
		}   		
	}
}
void subject_List(PTRSUB &root,PTRSUB &subNode, classList& CList,BUTTON Menu[], int& tt,int& offset, int&k, int&d){//danh sach mon hoc
	subjList_interface();
    char ch, search_text[MAX_MAMH+MAX_TENMH+2] ={0}, SName_text[MAX_TENMH+1]={0},SID_text[MAX_MAMH+1]={0},buff[10]={0}, SID_text2[MAX_MAMH+1]={0}, page_text[10];
	int x, y, hover=-1, j, s=0, sub_tt , key,sub_page = 1, cursor_pos_search = 0, idx_start_search=0, idx_search = 0, idx_tmp;
	int cursor_pos_MMH = 0, cursor_pos_TMH = 0,idx_start_TMH=0, idx_TMH= 0, print_s = 0, ID_choose =-1, cursor_pos_page =0;
	int choose = 0, n = T_cursor+1, page = 1, indexs[MAX_SUBJ+1]={-1}, n_index,nRow =0,nPageTable,last_nPageTable=-1, page_tmp, is_fix =0;
	AREA subjID, subjName, pageArea, DSCH[10];
	BUTTON exit, page_after, page_before, bar_search, clear, THEM, LUU, XOA, subClear;
	get_index_subjList(root,indexs,n_index,search_text);
	set_nPageTable(nRow,nPageTable,n_index,page,1);
	rowTable ROWTBs[10]={};
	set_buttons_subjList(exit,page,nRow, page_after,page_before,nPageTable,bar_search,clear,subjID,subjName,THEM,LUU,XOA,subClear,pageArea,DSCH);
	set_SubjTable(root, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);
	PTRSUB subNode1;
	subInfor infor;
	while(1){
		delay(1);
		if(s && print_s) inform2(s,sub_tt,SID_text2,print_s);
		if(choose==1) print_cursor(l_win/16+140+cursor_pos_search*(lth_sizeM-2),w_win/4-16,n);
		else if(choose==2) print_cursor(l_win/2+372+cursor_pos_MMH*(lth_sizeM-2),w_win/3-8,n);
		else if(choose==3) print_cursor(l_win/2+277+cursor_pos_TMH*(lth_sizeM-2),w_win/3+84,n);
		else if(choose==4) print_cursor(l_win/4+100-strlen(page_text)/2.0*(lth_sizeM)+cursor_pos_page*lth_sizeM,w_win-65,n);
		if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE,x,y);
			set_hover_CList(Menu, ROWTBs,hover,j,tt,x,y,nRow,clear,LUU,subClear,THEM,XOA);
	        if(j!=hover&&j!=-1){
	        	if(j<nLecMenu) draw_button(Menu[j]);
	        	else if(j==11) draw_button(clear);
	        	else if(j==12) {
	        		if(is_fix||sub_page==1) draw_button(subClear);
				}
	        	else if(j==13) draw_button(THEM);	
	        	else if(j==14){
	        		if(sub_page==2&&!is_fix) draw_button(XOA);
				} 
	        	else if(j==15) {
	        		if(sub_page==2) draw_button(LUU);
				}
 	        	else if(j<100+nRow)  draw_rowTable(ROWTBs[j-100]);
	        	if(hover<nLecMenu) highlight_button(Menu[hover],grey,white,white);
	        	else if(hover==11) highlight_button(clear,grey,white,white);
	        	else if(hover==12){
	        		if(is_fix||sub_page==1) highlight_button(subClear,grey,white,white);
				}
	        	else if(hover==13) highlight_button(THEM,grey,white,white);	
	        	else if(hover==14){
	        		if(sub_page==2&&!is_fix) highlight_button(XOA,grey,white,white);
				} 
	        	else if(hover==15){
	        		if(sub_page==2) highlight_button(LUU,grey,white,white);
				} 
	        	else if(hover<100+nRow) highlight_rowTable(ROWTBs[hover-100],grey,black,white);  
			}
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for(int i=0;i<nLecMenu;i++){
				if(i==tt) continue;
	         	if(is_area(Menu[i].area,x,y)){
	         		create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		        	Menu[tt].area.width+5,3,3);
		        	draw_button(Menu[tt]);
		        	tt=i;
	         		return;
				}
		    }
		    for(int i=0;i<nRow;i++){
		    	if(is_area(DSCH[i],x,y)){
		    		ID_choose = indexs[(page-1)*10+i];
		    		subNode = Search_Subject(root,ID_choose);
		    		tt = 7;
					return; 
				}
			}
		    for(int i=0;i<nRow;i++){
		    	if(is_rowTable(ROWTBs[i],x,y)){
			        idx_start_TMH =0;
			        clear_notice_subji4();
	    		    ID_choose = indexs[(page-1)*10+i];
		    		if(sub_page==1||is_fix){
		    			set_bar_edit_subji4(darkRed);
              		   	strcpy(LUU.text,"SUA");
        		   	    draw_button2(LUU);
				        draw_button2(XOA);
			            highlight_button2(subClear,darkWhite,white,white);
			            strcpy(THEM.text,"BACK");
			            draw_button2(THEM);
			            sub_page = 2;
			            if(is_fix) is_fix=0;
			    	}
			    	else clear_edit_subji4(SID_text,SName_text,idx_start_TMH);
			    	subNode1=Search_Subject(root,ID_choose);
					strcpy(SID_text,subNode1->subi4.MAMH);
		    		strcpy(SName_text,subNode1->subi4.TENMH);
		        	print_text_bar(l_win/2+372,w_win/3-9,SID_text,15,white,black);
		            print_text_bar(l_win/2+277,w_win/3+83,SName_text+idx_start_TMH,24,white,black);
		            if(choose!=1) {
		            	choose=0;
		            	continue;
					}
				}
			}
			if(is_area(exit.area,x,y)){
				create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		       	Menu[tt].area.width+5,3,3);
		       	draw_button(Menu[tt]);
		       	delete_button(exit,3);
				tt=-1;
				return;
			}
			else if(is_area(page_after.area,x,y)){
				if(page<nPageTable){
				    page++;
				    set_SubjTable(root, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);
				}
			}		  
			else if(is_area(page_before.area,x,y)){
				if(page>1){
				    page--;
				    set_SubjTable(root, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);
				}
			}
			else if(is_area(THEM.area,x,y)){
				idx_start_TMH = 0;
				if(sub_page==1){
					xoa2(bar_search, choose,search_text, SID_text, SName_text,idx_start_search,idx_start_TMH,0,page_text,page_tmp);
					settextstyle(font_text,0,sizeS);
					if(strlen(SID_text)==0) out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"Nhap ma MH",3,darkRed);
					if(strlen(SName_text)==0) out_text_xy(l_win/2+277,w_win/3+83+30,(char*)"Nhap ten MH",3,darkRed);
					if(Search_Subject_MMH(root,SID_text)!=NULL) out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"Ma MH da ton tai",3,darkRed);
					else if(strlen(SID_text)!=0&&strlen(SName_text)!=0){
							set_subjInfor(infor,SID_text,SName_text);
							int tmp=sinhkhoa(offset,k,d);
							Insert_Subject(root,infor,tmp);
							s = 200, sub_tt = 1, print_s =1;
							strcpy(SID_text2,SID_text);
							
							
					    	get_index_subjList(root,indexs,n_index,search_text);
					    	last_nPageTable = nPageTable;
			                set_nPageTable(nRow,nPageTable,n_index,page,0);
			                set_SubjTable(root, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);	
			                
		                clear_edit_subji4(SID_text,SName_text,idx_start_TMH);
						reset_subji4(SID_text,cursor_pos_MMH,SName_text,cursor_pos_TMH,idx_TMH,idx_start_TMH);		
						n= T_cursor+1;
					}
				}
				else{
					strcpy(THEM.text,"THEM");
					draw_button(THEM);
					if(is_fix){
						strcpy(LUU.text,"SUA");
						is_fix =0;
					} 
					else{
						highlight_button(XOA,darkWhite,white,white);	
     					draw_button(subClear);
					} 
					highlight_button(LUU,darkWhite,white,white);
					set_bar_edit_subji4(white);
				    reset_subji4(SID_text,cursor_pos_MMH,SName_text,cursor_pos_TMH,idx_TMH,idx_start_TMH);		
					n = T_cursor+1;
    				sub_page=1;
					choose = 0;				
				}
			}
			else if(is_area(bar_search.area,x,y)){
				n = T_cursor +1;
				if(strlen(search_text)==0) highlight_button(bar_search,white,white,white);
				xoa2(bar_search, choose,search_text, SID_text, SName_text,idx_start_search,idx_start_TMH,1,page_text,page_tmp);
			    cursor_pos_search = (x - l_win/16-133)/(lth_sizeM-2);
			    if (cursor_pos_search>strlen(search_text)&&strlen(search_text)<40) cursor_pos_search = strlen(search_text);
			    else if(cursor_pos_search>40) cursor_pos_search=40;
			    idx_search = idx_start_search +cursor_pos_search;
			}
			else if(is_area(subjID,x,y)&&(sub_page==1||is_fix)){
				n = T_cursor +1;
				out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"Ma MH toi da 15 ki tu",3,3);
				xoa2(bar_search, choose,search_text, SID_text, SName_text,idx_start_search,idx_start_TMH,2,page_text,page_tmp);
			    cursor_pos_MMH = (x - (l_win/2+365))/(lth_sizeM-2);
			    if (cursor_pos_MMH>strlen(SID_text)&&strlen(SID_text)<15) cursor_pos_MMH = strlen(SID_text);
			    else if(cursor_pos_MMH>15) cursor_pos_MMH=15;
			}
			else if(is_area(subjName,x,y)&&(sub_page==1||is_fix)){
				n = T_cursor +1;
				out_text_xy(l_win/2+277,w_win/3+83+30,(char*)"Ten MH toi da 50 ki tu",3,3);
				xoa2(bar_search, choose,search_text, SID_text, SName_text,idx_start_search,idx_start_TMH,3,page_text,page_tmp);
			    cursor_pos_TMH = (x - (l_win/2+270))/(lth_sizeM-2);
			    if (cursor_pos_TMH>strlen(SName_text)&&strlen(SName_text)<24) cursor_pos_TMH = strlen(SName_text);
			    else if(cursor_pos_TMH>24) cursor_pos_TMH=24;
			    idx_TMH = idx_start_TMH +cursor_pos_TMH;
			}
			else if(is_area(clear.area,x,y)){
				search_text[0]='\0';
				cursor_pos_search = 0;
				idx_start_search = 0;
				idx_search =0;
				if(choose!=1){
					choose=0;
					draw_button(bar_search);
                }
				else{
					n = T_cursor+1;
        	        highlight_button(bar_search,white,white,white);
				}
				get_index_subjList(root,indexs,n_index,search_text);
			    last_nPageTable = nPageTable;
	   	        set_nPageTable(nRow,nPageTable,n_index,page,1);
	   	        set_SubjTable(root, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);
			}
			else if(is_area(subClear.area,x,y)&&(sub_page==1||is_fix)){
	            idx_start_TMH =0;
			    clear_notice_subji4();
		    	clear_edit_subji4(SID_text,SName_text,idx_start_TMH);		
				reset_subji4(SID_text,cursor_pos_MMH,SName_text,cursor_pos_TMH,idx_TMH,idx_start_TMH);	
				n= T_cursor+1;
				xoa2(bar_search, choose,search_text,SID_text, SName_text,idx_start_search,idx_start_TMH,0,page_text,page_tmp);
			}
			else if(is_area(XOA.area,x,y)&&(sub_page==2&&!is_fix)){
				if(Mon_hoc_co_cau_hoi_da_thi(root,SID_text)==1) {
					s = 200, sub_tt = 4, print_s =1;
					continue;
				}
				if(!is_delete(SID_text,3)) continue;
					Delete_Subject(root,ID_choose);
					s = 200, sub_tt = 2, print_s =1;
					strcpy(SID_text2,SID_text);

			    	get_index_subjList(root,indexs,n_index,search_text);
			    	last_nPageTable = nPageTable;
	                set_nPageTable(nRow,nPageTable,n_index,page,0);
	                set_SubjTable(root, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);
           		strcpy(THEM.text,"THEM");
				draw_button(THEM);
				highlight_button(XOA,darkWhite,white,white);
				if(!is_fix) draw_button(subClear);
				highlight_button(LUU,darkWhite,white,white);
    	    	set_bar_edit_subji4(white);
				reset_subji4(SID_text,cursor_pos_MMH,SName_text,cursor_pos_TMH,idx_TMH,idx_start_TMH);	
				choose=0;
				sub_page =1;	
			}
			else if(is_area(LUU.area,x,y)&&sub_page==2){
				if(is_fix==0){
					highlight_button(XOA,darkWhite,white,white);
					strcpy(LUU.text,"LUU");
					draw_button(LUU);
					draw_button(subClear);
					set_bar_edit_subji4(white);
			        print_text_bar(l_win/2+372,w_win/3-9,SID_text,15,white,black);
		            print_text_bar(l_win/2+277,w_win/3+83,SName_text+idx_start_TMH,24,white,black);
					is_fix = 1;
				}
				else{
					xoa2(bar_search, choose,search_text, SID_text, SName_text,idx_start_search,idx_start_TMH,0,page_text,page_tmp);
					PTRSUB tmp= Search_Subject_MMH(root,SID_text);
					if(strlen(SID_text)==0) out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"Nhap ma MH",3,darkRed);
					if(strlen(SName_text)==0) out_text_xy(l_win/2+277,w_win/3+83+30,(char*)"Nhap ten MH",3,darkRed);
					if(tmp!=NULL&&tmp->key!=ID_choose) out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"Ma MH da ton tai",3,darkRed);
					else if(strlen(SID_text)!=0&&strlen(SName_text)!=0){
						
						//sua lai thong tin mon hoc trong ds diem cua lop
				        edit_subji4_of_CList(CList,subNode1->subi4.MAMH,SID_text);
						set_subjInfor(subNode1->subi4,SID_text,SName_text); 
											
						s = 200, sub_tt = 3, print_s =1;
						strcpy(SID_text2,SID_text);

					    get_index_subjList(root,indexs,n_index,search_text);
					    last_nPageTable = nPageTable;
			            set_nPageTable(nRow,nPageTable,n_index,page,0);
			            set_SubjTable(root, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);
		               	strcpy(THEM.text,"THEM");
						draw_button(THEM);
						highlight_button(LUU,darkWhite,white,white);
		   		    	clear_edit_subji4(SID_text,SName_text,idx_start_TMH);
						reset_subji4(SID_text,cursor_pos_MMH,SName_text,cursor_pos_TMH,idx_TMH,idx_start_TMH);
						sub_page=1;	
						is_fix = 0;						
					} 
				}
			}
			else if(is_area(pageArea,x,y)){
				xoa2(bar_search, choose,search_text, SID_text, SName_text,idx_start_search,idx_start_TMH,4,page_text,page_tmp);
				if(page==0) continue; 
				page_tmp = page;
				cursor_pos_page = (x -((l_win/4+93)-strlen(page_text)*(lth_sizeM)/2.0))/lth_sizeM;
				if(cursor_pos_page<0) cursor_pos_page = 0;
				else if(cursor_pos_page>strlen(page_text)) cursor_pos_page = strlen(page_text);
				n = T_cursor+1;
			}
			else xoa2(bar_search, choose,search_text,SID_text, SName_text,idx_start_search,idx_start_TMH,0,page_text,page_tmp);
			settextstyle(font_text,0,sizeM);
			if(choose==1) print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
			else if(choose==2) print_text_bar(l_win/2+372,w_win/3-9,SID_text,15,white,black);
			else if(choose==3) print_text_bar(l_win/2+277,w_win/3+83,SName_text+idx_start_TMH,24,white,black);
			else if(choose==4) out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
		}
		if(kbhit()){
			n = T_cursor+1;
			key = Key();
			if(choose == 1){
				settextstyle(font_text,0,sizeS);
                print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,white);
			    if(key==key_Right){
					if(idx_search<strlen(search_text)){
						idx_search++; 
						if(cursor_pos_search==40) idx_start_search++;
					} 
                    if(cursor_pos_search<40&&cursor_pos_search<strlen(search_text)) cursor_pos_search++;
				    print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
			    else if(key==key_Left){
                    if(idx_search>0) idx_search--; 
                    if(cursor_pos_search>0) cursor_pos_search--;
                    else if(idx_start_search>0) idx_start_search--;
				    print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
				else if(strlen(search_text)==50&&key!=key_BS){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/16+140,w_win/4-17+30,(char*)"Tu khoa toi da 50 ki tu",3,darkRed);
					settextstyle(font_text,0,sizeS);
					print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
				else{
					if(key==key_BS){
						if(strlen(search_text)==50) out_text_xy(l_win/16+140,w_win/4-17+30,(char*)"Tu khoa toi da 50 ki tu",3,3);
						if(idx_search>0){
							strcpy(search_text + idx_search-1, search_text + idx_search);
							idx_search--;
						}
					    if(idx_start_search>0) idx_start_search--;
					    else if(cursor_pos_search >0) cursor_pos_search--;
		     	    }
		     	    else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'||key==key_SP||key==(int)'-'){
    					insert_chr_to_str(search_text,key,idx_search);
    	                idx_search++;
    					if(cursor_pos_search < 40) cursor_pos_search++;
    					else idx_start_search++;
			    	}
			    	print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
			    	get_index_subjList(root,indexs,n_index,search_text);
			    	last_nPageTable = nPageTable;
	                set_nPageTable(nRow,nPageTable,n_index,page,1);
	                set_SubjTable(root, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);  
				}
		    }
		    else if(choose==2){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"Ma MH toi da 15 ki tu",3,3);
                print_text_bar(l_win/2+372,w_win/3-9,SID_text,15,white,white);
			    if(key==key_Right){
                    if(cursor_pos_MMH<strlen(SID_text)) cursor_pos_MMH++;
				}
			    else if(key==key_Left){
                    if(cursor_pos_MMH>0) cursor_pos_MMH--;
				}
				else if(key==key_Enter||key==key_Down){
			        if(strlen(SName_text)>24) cursor_pos_TMH = idx_TMH = 24;
					else cursor_pos_TMH = idx_TMH = strlen(SName_text);
					xoa2(bar_search, choose,search_text, SID_text, SName_text,idx_start_search,idx_start_TMH,3,page_text,page_tmp);
				}
				else if(key==key_BS){
					if(cursor_pos_MMH >0){
						strcpy(SID_text + cursor_pos_MMH-1, SID_text + cursor_pos_MMH);
						cursor_pos_MMH--;
					} 
		  	    }
	    	    else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'||key==(int)'-'){
	    	    	if(strlen(SID_text)==MAX_MAMH){
	            		settextstyle(font_text,0,sizeS-1);
						out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"Ma MH toi da 15 ki tu",3,darkRed);
				    }
				    else{
				    	ch = (char)key;
						upper_chr(ch); 
    	   				insert_chr_to_str(SID_text,ch,cursor_pos_MMH);
    			    	if(cursor_pos_MMH < 15) cursor_pos_MMH++;
					}
			    }
			    print_text_bar(l_win/2+372,w_win/3-9,SID_text,15,white,black);
		    }
		    else if(choose==3){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+277,w_win/3+83+30,(char*)"Ten MH toi da 50 ki tu",3,3);
				print_text_bar(l_win/2+277,w_win/3+83,SName_text+idx_start_TMH,24,white,white);
			    if(key==key_Right){
					if(idx_TMH<strlen(SName_text)){
						idx_TMH++; 
						if(cursor_pos_TMH==24) idx_start_TMH++;
					} 
                    if(cursor_pos_TMH<24&&cursor_pos_TMH<strlen(SName_text)) cursor_pos_TMH++;
				}
			    else if(key==key_Left){
                    if(idx_TMH>0) idx_TMH--; 
                    if(cursor_pos_TMH>0) cursor_pos_TMH--;
                    else if(idx_start_TMH>0) idx_start_TMH--;
				}
				else if(key==key_Up){
					fix_str2(SName_text);
					idx_start_TMH = 0;
				    cursor_pos_MMH = strlen(SID_text);
					xoa2(bar_search, choose,search_text, SID_text, SName_text,idx_start_search,idx_start_TMH,2,page_text,page_tmp);
				}
				else if(key==key_BS){
				 	if(idx_TMH>0){
						strcpy(SName_text + idx_TMH-1, SName_text + idx_TMH);
						idx_TMH--;
					}
				    if(idx_start_TMH>0) idx_start_TMH--;
					else if(cursor_pos_TMH >0) cursor_pos_TMH--;
		  	    }
				else if(strlen(SName_text)==MAX_TENMH){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/2+277,w_win/3+83+30,(char*)"Ten lop toi da 50 ki tu",3,darkRed);
				}
	    	    else if(key>=key_SP&&key<127){
	    	    	if(key==' '){
	    	    		if(cursor_pos_TMH==0){
	    	    			print_text_bar(l_win/2+277,w_win/3+83,SName_text+idx_start_TMH,24,white,black);
	    	    			continue;
						}
					}
					insert_chr_to_str(SName_text,key,idx_TMH);
    	            idx_TMH++;
    		    	if(cursor_pos_TMH < 24) cursor_pos_TMH++;
    				else idx_start_TMH++;
			    }
			    print_text_bar(l_win/2+277,w_win/3+83,SName_text+idx_start_TMH,24,white,black);
		    }
		    else if(choose==4){
		    	settextstyle(font_text,0,sizeM);
				out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,white);
			    if(key==key_Right){
					if(cursor_pos_page<strlen(page_text)) cursor_pos_page++;
				}
			    else if(key==key_Left){
                    if(cursor_pos_page>0) cursor_pos_page--;
				}
				else if(key==key_BS){
				 	if(cursor_pos_page>0){
				 		strcpy(page_text+cursor_pos_page-1,page_text+cursor_pos_page);
				 		cursor_pos_page--;
					}
		  	    }
	    	    else if(key>='0'&&key<='9'){
	    	    	if(key!='0'||cursor_pos_page!=0){
	    	   	    	insert_chr_to_str(page_text,key,cursor_pos_page);
	    	    		if(atoi(page_text)>nPageTable){
	    	    		itoa(nPageTable,page_text,decimal);
	    	    		cursor_pos_page = nPageTable/10 + 1;
						}
    					else cursor_pos_page++;
					}
			    }
			    else if(key==key_Enter){
			    	choose = 0;	
                 	if(strlen(page_text)==0) strcpy(page_text,itoa(page_tmp,buff,decimal));
			    	else {
			    		page = atoi(page_text);
			    		set_SubjTable(root, ROWTBs, indexs, n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before,ID_choose,page_text);
					}
				}
				settextstyle(font_text,0,sizeM);
				out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
			}
		}
	}	
}


//GIAO DIEN TIM KIEM DIEM
void get_index_MMHTable(PTRSUB &subNode,int *indexs,int& n_index,char* search_text){//SUA LAI
	//combobox ma mon hoc trong tim kiem diem thi
	if(subNode==NULL) return;
	char buff[MAX_MAMH+1], buff2[MAX_MAMH+1];
	strcpy(buff,search_text);
	delete_blks_str(buff);
	upper_str(buff);
	strcpy(buff2,subNode->subi4.MAMH);
	delete_blks_str(buff2);
	upper_str(buff2);
	if(strstr(buff2,buff)!=NULL) indexs[n_index++] = subNode->key;
	get_index_MMHTable(subNode->left,indexs,n_index,search_text);
	get_index_MMHTable(subNode->right,indexs,n_index,search_text);
	
}
void get_index_MLTable(classList& CList,int *indexs,int& n_index,char* search_text){
	//combox ma lop trong tim kiem diem thi
	n_index = 0;
	char buff[MAX_MALOP+1], buff2[MAX_MALOP+1];
	strcpy(buff,search_text);
	delete_blks_str(buff);
	upper_str(buff);
	for(int i=0; i< CList.nClass;i++){
		strcpy(buff2,CList.classes[i]->classi4.MALOP);
		delete_blks_str(buff2);
		upper_str(buff2);
		if(strstr(buff2,buff)!=NULL) indexs[n_index++] = i;
	}
}
void get_index_MSVTable(PTRS SFirst,int *indexs,int& n_index,char* search_text){
	//COMboBOx sinh vien trong tim kiem diem
	n_index = 0;
	char buff[MAX_MASV+1], buff2[MAX_MASV+1];
	strcpy(buff,search_text);
	delete_blks_str(buff);
	upper_str(buff);
	int i = 0;
	for(PTRS SNode = SFirst; SNode!= NULL ; SNode = SNode->Next){
		strcpy(buff2,SNode->stui4.MASV);
		delete_blks_str(buff2);
		upper_str(buff2);
		if(strstr(buff2,buff)!=NULL) indexs[n_index++] = i;
		i++;
	}
}
void make_string_mark1(PTRS SNode,float mark,char* buff){//HO TRO TIM KIEM DIEM CUA LOP THEO MON HOC
	if(mark==-1) strcpy(buff,"Chua thi");
	else if(mark==10) snprintf(buff,5,"%f",mark);
	else snprintf(buff,4,"%f",mark);
	strcat(buff,SNode->stui4.MASV);
	strcat(buff,SNode->stui4.HO);
	strcat(buff,SNode->stui4.TEN);
}
void get_index_markList1(PTRS SFirst,PTRSUB &subNode, int* indexs,int& n_index, char* search_text){//HO TRO XEM DIEM CUA LOP THEO MON HOC
	n_index = 0;
	char buff[MAX_MASV+MAX_HO+MAX_TEN+10], buff2[MAX_MASV+MAX_HO+MAX_TEN+10];
	strcpy(buff,search_text);
	delete_blks_str(buff);
	upper_str(buff);
	int i = 0;
	float mark;
	for(PTRS SNode = SFirst; SNode!= NULL ; SNode = SNode->Next){
		mark = mark_of_subj(SNode->MFirst,subNode->subi4.MAMH);
		make_string_mark1(SNode,mark,buff2);
		delete_blks_str(buff2);
		upper_str(buff2);
		if(strstr(buff2,buff)!=NULL){
			indexs[n_index++] = i;
		} 
		i++;	
	}
}
void make_string_mark2(PTRM MNode,PTRSUB &root,char* buff){//HO TRO TIM KIEM DIEM THEO SINH VIEN
	char buff2[5];
	if(MNode->marki4.Diem==10) snprintf(buff2,5,"%f",MNode->marki4.Diem);
	else snprintf(buff2,4,"%f",MNode->marki4.Diem);
	PTRSUB subNode = Search_Subject_MMH(root,MNode->marki4.Mamh); //Mnode la node trong danh sach diem
	if(subNode==NULL) return;
	strcpy(buff,MNode->marki4.Mamh);
	strcat(buff,subNode->subi4.TENMH);// tu ma lay ra ten mon hoc
	strcat(buff,buff2);
}
void get_index_markList2(PTRM MFirst,PTRSUB &root, int* indexs,int& n_index, char* search_text){//TIM KIEM DIEM THEO SINH VIEN
	n_index = 0;
	char buff[MAX_MAMH+MAX_TENMH+5], buff2[MAX_MAMH+MAX_TENMH+5];
	strcpy(buff,search_text);
	delete_blks_str(buff);
	upper_str(buff);
	int i = 0;
	for(PTRM MNode = MFirst; MNode!= NULL ; MNode = MNode->Next){
		make_string_mark2(MNode,root,buff2);
		delete_blks_str(buff2);
		upper_str(buff2);
		if(strstr(buff2,buff)!=NULL){
			indexs[n_index++] = i;
		} 
		i++;
	}
}
void mark_List1_interface(PTRC CLASS,subInfor& subji4){//giao dien xem diem cua lop theo mon hoc
	out_text_xy(l_win/16+100,w_win/2-120,(char*)"MON:",3, black);
	out_text_xy(l_win/2+180,w_win/2-120,(char*)"LOP:",3, black);
    settextstyle(font_text,0,sizeL-1);
    out_text_xy(l_win/2-130,100,(char*)"BANG DIEM",3,darkRed);
    settextstyle(font_text,0,sizeM-1);
	out_text_xy(l_win/2-380,w_win/2-120,subji4.TENMH,3,darkRed);
	out_text_xy(l_win/2+250,w_win/2-120,CLASS->classi4.MALOP,3,darkRed);
	settextstyle(font_text,0,sizeM);
	out_text_xy(l_win/16+150,w_win/4-17,(char *)"TIM KIEM:",3,black);
    create_1_bar(l_win/4+200,w_win-70,100,30,white,white);
    create_table(172,w_win/3+25,lengthsMarkTable1,30,5,1,markTable1,sizeM,black,darkWhite,black); 
}
void mark_List2_interface(PTRS SNode,int user){//giao dien xem diem theo sinh vien
    settextstyle(font_text,0,sizeL-1);
    out_text_xy(l_win/2-130,100,(char*)"BANG DIEM",3,darkRed);
    settextstyle(font_text,0,sizeM);
    out_text_xy(l_win/16+100,w_win/2-120,(char*)"SV:",3, black);
	char buff[MAX_HO+MAX_TEN+MAX_MASV+5];
	HO_TEN_MASV(SNode->stui4,buff);
	settextstyle(font_text,0,sizeM-1);
	out_text_xy(l_win/2-400,w_win/2-117,buff,3,darkRed);
	settextstyle(font_text,0,sizeM);
	out_text_xy(l_win/16+150,w_win/4-17,(char *)"TIM KIEM:",3,black);
    create_1_bar(l_win/4+200,w_win-70,100,30,white,white);
    create_table(172,w_win/3+25,lengthsMarkTable2,30,5,1,markTable2,sizeM,black,darkWhite,black); 
}
void markList_interface(){// giao den nhap thong tin de xem diem
	settextstyle(font_text,0,sizeM);
	out_text_xy(100,w_win/4+60,(char *)"MA LOP: ",3,black);
	out_text_xy(100,w_win/4-47,(char *)"XEM DIEM THEO: ",3,black);
	out_text_xy(650,w_win/4+60,(char *)"MA MH: ",3,black);
}
void mark_List1(PTRC CLASS,PTRS& SNode,PTRSUB &subNode, BUTTON Menu[],int& tt){//DIEM THEO MON HOC
	mark_List1_interface(CLASS,subNode->subi4);
    char ch, search_text[51] ={0},page_text[10]={0},buff[10]; 
	int x, y, hover=-1, j, key, sub_page = 1, cursor_pos_search = 0, idx_start_search=0, idx_search = 0, cursor_pos_page =0;
	int choose = 0, n = T_cursor+1, page = 1, indexs[MAX_STD+1]={-1}, n_index, nRow =0,nPageTable,last_nPageTable=-1, page_tmp, is_fix =0;
	AREA pageArea, CTBT[10];
	BUTTON exit, page_after, page_before, bar_search, clear, Return;
	get_index_markList1(CLASS->SFirst,subNode,indexs,n_index,search_text);
	set_nPageTable(nRow,nPageTable,n_index,page,1);
	rowTable ROWTBs[10]={};
	set_buttons_markList1(exit,page,nRow, page_after,page_before, nPageTable,bar_search,clear, pageArea,Return,CTBT);
	set_markTable1(CLASS->SFirst,subNode, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before, page_text);
	while(1){
		delay(1);
		if(choose==1) print_cursor(l_win/16+290+cursor_pos_search*(lth_sizeM-2),w_win/4-16,n);
		else if(choose==7) print_cursor(l_win/4+250-strlen(page_text)/2.0*(lth_sizeM)+cursor_pos_page*lth_sizeM,w_win-65,n);
		if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE,x,y);
			set_hover_markList1(Menu,ROWTBs,hover,j,tt,x,y,nRow,clear);
	        if(j!=hover&&j!=-1){
	        	if(j<nLecMenu) draw_button(Menu[j]);
	        	else if(j==11) draw_button(clear);
 	        	else if(j<100+nRow)  draw_rowTable(ROWTBs[j-100]);
	        	if(hover<nLecMenu) highlight_button(Menu[hover],grey,white,white);
	        	else if(hover==11) highlight_button(clear,grey,white,white);
	        	else if(hover<100+nRow) highlight_rowTable(ROWTBs[hover-100],grey,black,white);  
			}
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for(int i=0;i<nLecMenu;i++){
				if(i==tt) continue;
	         	if(is_area(Menu[i].area,x,y)){
	         		create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		        	Menu[tt].area.width+5,3,3);
		        	draw_button(Menu[tt]);
		        	tt=i;
	         		return;
				}
		    }
		    for(int i=0;i<nRow;i++){
		    	if(is_area(CTBT[i],x,y)){
		    		SNode = get_student_idx(CLASS->SFirst,indexs[(page-1)*10+i]);
		    		if(mark_of_subj(SNode->MFirst,subNode->subi4.MAMH)!=-1){
		    			tt = 22;
		    		    return; 
					}
					else break;
				}
			}
			if(is_area(exit.area,x,y)){
				create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		       	Menu[tt].area.width+5,3,3);
		       	draw_button(Menu[tt]);
		       	delete_button(exit,3);
				tt=-1;
				return;
			}
			else if(is_area(Return.area,x,y)) return;
			else if(is_area(page_after.area,x,y)){
				if(page<nPageTable){
				    page++;
				    set_markTable1(CLASS->SFirst,subNode, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before, page_text);
				}
			}		  
			else if(is_area(page_before.area,x,y)){
				if(page>1){
				    page--;
				    set_markTable1(CLASS->SFirst,subNode, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before, page_text);
			    }
			}
			else if(is_area(bar_search.area,x,y)){
				n = T_cursor +1;
				if(strlen(search_text)==0) highlight_button(bar_search,white,white,white);
				xoa3(bar_search,search_text,idx_start_search,choose,1,page_text,page_tmp);
			    cursor_pos_search = (x - l_win/16+83)/(lth_sizeM-2);
			    if (cursor_pos_search>strlen(search_text)&&strlen(search_text)<40) cursor_pos_search = strlen(search_text);
			    else if(cursor_pos_search>40) cursor_pos_search=40;
			    idx_search = idx_start_search +cursor_pos_search;
			}
			else if(is_area(clear.area,x,y)){
				search_text[0]='\0';
				cursor_pos_search = 0;
				idx_start_search = 0;
				idx_search =0;
				if(choose!=1){
					choose=0;
					draw_button(bar_search);
                }
				else{
					n = T_cursor+1;
        	        highlight_button(bar_search,white,white,white);
				}
				get_index_markList1(CLASS->SFirst,subNode,indexs,n_index,search_text);
			    last_nPageTable = nPageTable;
	   	        set_nPageTable(nRow,nPageTable,n_index,page,1);
	   	        set_markTable1(CLASS->SFirst,subNode, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before, page_text);
			}
			else if(is_area(pageArea,x,y)){
                xoa3(bar_search,search_text,idx_start_search,choose,7,page_text,page_tmp);
				if(page==0) continue; 
				page_tmp = page;
				cursor_pos_page = (x -((l_win/4+243)-strlen(page_text)*(lth_sizeM)/2.0))/lth_sizeM;
				if(cursor_pos_page<0) cursor_pos_page = 0;
				else if(cursor_pos_page>strlen(page_text)) cursor_pos_page = strlen(page_text);
				n = T_cursor+1;
			}
			else xoa3(bar_search,search_text,idx_start_search,choose,0,page_text,page_tmp);
			settextstyle(font_text,0,sizeM);
			if(choose==1) print_text_bar(l_win/16+290,w_win/4-17,search_text+idx_start_search,40,white,black);
			else if(choose==7) out_text_xy(l_win/4+250-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
		}
		if(kbhit()){
			n = T_cursor+1;
			key = Key();
			if(choose == 1){
				settextstyle(font_text,0,sizeS);
                print_text_bar(l_win/16+290,w_win/4-17,search_text+idx_start_search,40,white,white);
			    if(key==key_Right){
					if(idx_search<strlen(search_text)){
						idx_search++; 
						if(cursor_pos_search==40) idx_start_search++;
					} 
                    if(cursor_pos_search<40&&cursor_pos_search<strlen(search_text)) cursor_pos_search++;
				    print_text_bar(l_win/16+290,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
			    else if(key==key_Left){
                    if(idx_search>0) idx_search--; 
                    if(cursor_pos_search>0) cursor_pos_search--;
                    else if(idx_start_search>0) idx_start_search--;
				    print_text_bar(l_win/16+290,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
				else if(strlen(search_text)==50&&key!=key_BS){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/16+290,w_win/4-17+30,(char*)"Tu khoa toi da 50 ki tu",3,darkRed);
					settextstyle(font_text,0,sizeS);
					print_text_bar(l_win/16+290,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
				else{
					if(key==key_BS){
						if(idx_search>0){
							strcpy(search_text + idx_search-1, search_text + idx_search);
							idx_search--;
						}
					    if(idx_start_search>0) idx_start_search--;
					    else if(cursor_pos_search >0) cursor_pos_search--;
		     	    }
		     	    else if(key>=key_SP&&key<127){
    					insert_chr_to_str(search_text,key,idx_search);
    	                idx_search++;
    					if(cursor_pos_search < 40) cursor_pos_search++;
    					else idx_start_search++;
			    	}
			    	print_text_bar(l_win/16+290,w_win/4-17,search_text+idx_start_search,40,white,black);
			    	get_index_markList1(CLASS->SFirst,subNode,indexs,n_index,search_text);
				    last_nPageTable = nPageTable;
		   	        set_nPageTable(nRow,nPageTable,n_index,page,1);
		   	        set_markTable1(CLASS->SFirst,subNode, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before, page_text);
				}
		    }
		    else if(choose==7){
		    	settextstyle(font_text,0,sizeM);
				out_text_xy(l_win/4+250-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,white);
			    if(key==key_Right){
					if(cursor_pos_page<strlen(page_text)) cursor_pos_page++;
				}
			    else if(key==key_Left){
                    if(cursor_pos_page>0) cursor_pos_page--;
				}
				else if(key==key_BS){
				 	if(cursor_pos_page>0){
				 		strcpy(page_text+cursor_pos_page-1,page_text+cursor_pos_page);
				 		cursor_pos_page--;
					}
		  	    }
	    	    else if(key>='0'&&key<='9'){
	    	    	if(key!='0'||cursor_pos_page!=0){
	    	   	    	insert_chr_to_str(page_text,key,cursor_pos_page);
	    	    		if(atoi(page_text)>nPageTable){
	    	    		itoa(nPageTable,page_text,decimal);
	    	    		cursor_pos_page = nPageTable/10 + 1;
						}
    					else cursor_pos_page++;
					}
			    }
			    else if(key==key_Enter){
			    	choose = 0;	
                 	if(strlen(page_text)==0) strcpy(page_text,itoa(page_tmp,buff,decimal));
			    	else {
			    		page = atoi(page_text);
	   	                set_markTable1(CLASS->SFirst,subNode, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before, page_text);
					}
				}
				settextstyle(font_text,0,sizeM);
				out_text_xy(l_win/4+250-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
			}
		}
	}	
}
void mark_List2(PTRS SNode, PTRSUB &root, PTRSUB &subNode, BUTTON Menu[],int nMenu,int &tt,int user){//DIEM THEO SINH VIEN
	mark_List2_interface(SNode,user); 
    char ch, search_text[51] ={0},page_text[10]={0},buff[10]; 
	int x, y, hover=-1, j, key, sub_page = 1, cursor_pos_search = 0, idx_start_search=0, idx_search = 0;
	int idx_student=-1, cursor_pos_page =0;
	int choose = 0, n = T_cursor+1, page = 1, indexs[MAX_SUBJ+1]={-1}, n_index, nRow =0,nPageTable,last_nPageTable=-1, page_tmp, is_fix =0;
	AREA pageArea,  CTBT[10];
	BUTTON exit, page_after, page_before, bar_search, clear, Return;
	get_index_markList2(SNode->MFirst,root,indexs,n_index,search_text);
	set_nPageTable(nRow,nPageTable,n_index,page,1);
	rowTable ROWTBs[10]={};
	set_buttons_markList2(exit,page,nRow, page_after,page_before, nPageTable,bar_search,clear, pageArea, Return,CTBT,user);
	set_markTable2(SNode->MFirst,root, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before, page_text);
	while(1){
		delay(1);
		if(choose==1) print_cursor(l_win/16+290+cursor_pos_search*(lth_sizeM-2),w_win/4-16,n);
		else if(choose==7) print_cursor(l_win/4+250-strlen(page_text)/2.0*(lth_sizeM)+cursor_pos_page*lth_sizeM,w_win-65,n);
		if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE,x,y);
			set_hover_markList2(Menu,nMenu,ROWTBs,hover,j,tt,x,y,nRow,clear);
	        if(j!=hover&&j!=-1){
	        	if(j<nMenu) draw_button(Menu[j]);
	        	else if(j==11) draw_button(clear);
 	        	else if(j<100+nRow)  draw_rowTable(ROWTBs[j-100]);
	        	if(hover<nMenu) highlight_button(Menu[hover],grey,white,white);
	        	else if(hover==11) highlight_button(clear,grey,white,white);
	        	else if(hover<100+nRow) highlight_rowTable(ROWTBs[hover-100],grey,black,white);  
			}
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for(int i=0;i<nMenu;i++){
				if(i==tt) continue;
	         	if(is_area(Menu[i].area,x,y)){
	         		create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		        	Menu[tt].area.width+5,3,3);
		        	draw_button(Menu[tt]);
		        	tt=i;
	         		return;
				}
		    }
		    for(int i=0;i<nRow;i++){
		    	if(is_area(CTBT[i],x,y)){
		    		PTRM MNode = get_mark_idx(SNode->MFirst,indexs[(page-1)*10+i]);
		    		subNode =Search_Subject_MMH(root,MNode->marki4.Mamh);
		    		tt = 22;
					return; 
				}
			}
		    if(is_area(Return.area,x,y)&&user==LECTURER) return;
			else if(is_area(exit.area,x,y)){
				create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		       	Menu[tt].area.width+5,3,3);
		       	draw_button(Menu[tt]);
		       	delete_button(exit,3);
				tt=-1;
				return;
			}
			else if(is_area(page_after.area,x,y)){
				if(page<nPageTable){
				    page++;
				    set_markTable2(SNode->MFirst,root, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before, page_text);	
				}
			}		  
			else if(is_area(page_before.area,x,y)){
				if(page>1){
				    page--;
				    set_markTable2(SNode->MFirst,root, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before, page_text);
			    }
			}
			else if(is_area(bar_search.area,x,y)){
				n = T_cursor +1;
				if(strlen(search_text)==0) highlight_button(bar_search,white,white,white);
				xoa3(bar_search,search_text,idx_start_search,choose,1,page_text,page_tmp);
			    cursor_pos_search = (x - l_win/16+83)/(lth_sizeM-2);
			    if (cursor_pos_search>strlen(search_text)&&strlen(search_text)<40) cursor_pos_search = strlen(search_text);
			    else if(cursor_pos_search>40) cursor_pos_search=40;
			    idx_search = idx_start_search +cursor_pos_search;
			}
			else if(is_area(clear.area,x,y)){
				search_text[0]='\0';
				cursor_pos_search = 0;
				idx_start_search = 0;
				idx_search =0;
				if(choose!=1){
					choose=0;
					draw_button(bar_search);
                }
				else{
					n = T_cursor+1;
        	        highlight_button(bar_search,white,white,white);
				}
				n_index=0;
				get_index_markList2(SNode->MFirst,root,indexs,n_index,search_text);
			    last_nPageTable = nPageTable;
	   	        set_nPageTable(nRow,nPageTable,n_index,page,1);
	   	        set_markTable2(SNode->MFirst,root, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before, page_text);
			}
			else if(is_area(pageArea,x,y)){
                xoa3(bar_search,search_text,idx_start_search,choose,7,page_text,page_tmp);
				if(page==0) continue; 
				page_tmp = page;
				cursor_pos_page = (x -((l_win/4+243)-strlen(page_text)*(lth_sizeM)/2.0))/lth_sizeM;
				if(cursor_pos_page<0) cursor_pos_page = 0;
				else if(cursor_pos_page>strlen(page_text)) cursor_pos_page = strlen(page_text);
				n = T_cursor+1;
			}
			else xoa3(bar_search,search_text,idx_start_search,choose,0,page_text,page_tmp);
			settextstyle(font_text,0,sizeM);
			if(choose==1) print_text_bar(l_win/16+290,w_win/4-17,search_text+idx_start_search,40,white,black);
			else if(choose==7) out_text_xy(l_win/4+250-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
		}
		if(kbhit()){
			n = T_cursor+1;
			key = Key();
			if(choose == 1){
				settextstyle(font_text,0,sizeS);
                print_text_bar(l_win/16+290,w_win/4-17,search_text+idx_start_search,40,white,white);
			    if(key==key_Right){
					if(idx_search<strlen(search_text)){
						idx_search++; 
						if(cursor_pos_search==40) idx_start_search++;
					} 
                    if(cursor_pos_search<40&&cursor_pos_search<strlen(search_text)) cursor_pos_search++;
				    print_text_bar(l_win/16+290,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
			    else if(key==key_Left){
                    if(idx_search>0) idx_search--; 
                    if(cursor_pos_search>0) cursor_pos_search--;
                    else if(idx_start_search>0) idx_start_search--;
				    print_text_bar(l_win/16+290,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
				else if(strlen(search_text)==50&&key!=key_BS){
	            	settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/16+290,w_win/4-17+30,(char*)"Tu khoa toi da 50 ki tu",3,darkRed);
					settextstyle(font_text,0,sizeS);
					print_text_bar(l_win/16+290,w_win/4-17,search_text+idx_start_search,40,white,black);
				}
				else{
					if(key==key_BS){
						if(idx_search>0){
							strcpy(search_text + idx_search-1, search_text + idx_search);
							idx_search--;
						}
					    if(idx_start_search>0) idx_start_search--;
					    else if(cursor_pos_search >0) cursor_pos_search--;
		     	    }
		     	    else if(key>=key_SP&&key<127){
    					insert_chr_to_str(search_text,key,idx_search);
    	                idx_search++;
    					if(cursor_pos_search < 40) cursor_pos_search++;
    					else idx_start_search++;
			    	}
			    	print_text_bar(l_win/16+290,w_win/4-17,search_text+idx_start_search,40,white,black);
			    	get_index_markList2(SNode->MFirst,root,indexs,n_index,search_text);
			    	last_nPageTable = nPageTable;
	   	        	set_nPageTable(nRow,nPageTable,n_index,page,1);
	   	        	set_markTable2(SNode->MFirst,root, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before, page_text);
				}
		    }
		    else if(choose==7){
		    	settextstyle(font_text,0,sizeM);
				out_text_xy(l_win/4+250-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,white);
			    if(key==key_Right){
					if(cursor_pos_page<strlen(page_text)) cursor_pos_page++;
				}
			    else if(key==key_Left){
                    if(cursor_pos_page>0) cursor_pos_page--;
				}
				else if(key==key_BS){
				 	if(cursor_pos_page>0){
				 		strcpy(page_text+cursor_pos_page-1,page_text+cursor_pos_page);
				 		cursor_pos_page--;
					}
		  	    }
	    	    else if(key>='0'&&key<='9'){
	    	    	if(key!='0'||cursor_pos_page!=0){
	    	   	    	insert_chr_to_str(page_text,key,cursor_pos_page);
	    	    		if(atoi(page_text)>nPageTable){
	    	    		itoa(nPageTable,page_text,decimal);
	    	    		cursor_pos_page = nPageTable/10 + 1;
						}
    					else cursor_pos_page++;
					}
			    }
			    else if(key==key_Enter){
			    	choose = 0;	
                 	if(strlen(page_text)==0) strcpy(page_text,itoa(page_tmp,buff,decimal));
			    	else {
			    		page = atoi(page_text);
	   	                set_markTable2(SNode->MFirst,root, ROWTBs, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before, page_text);
					}
				}
				settextstyle(font_text,0,sizeM);
				out_text_xy(l_win/4+250-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
			}
		}
	}	
}
void mark_List(classList &CList,PTRSUB &root,PTRC& CLASS,PTRS& SNode,PTRSUB &subNode,BUTTON Menu[], int& tt){//GIAO DIEN TIM DIEM
	markList_interface();   
    char ch, text1[MAX_MALOP+1]={0}, text2[20]={0}, buff[10]={0};
	int x, y, hover=-1, j,key,filter =1, is_click_filter = 0, idx_class = -1,idx_subj = -1,page, is_click_text1 = 0, is_click_text2 = 0;
	int cursor_pos_1 = 0, cursor_pos_2 =0;
	int choose = 0, n = T_cursor+1, indexs[MAX_CLASS+1]={-1}, n_index, nRow =0,nPageTable,last_nPageTable=-1;
	BUTTON exit, LOC, ML, MMH_MSV, XEM, LOC2, page_after, page_before;
	BUTTON buttons[10]={};
	set_buttons_markList(exit, LOC, ML, MMH_MSV,XEM, LOC2,page_after,page_before);
	PTRSUB subNode1;
	while(1){
		delay(1);
		if(choose==1) print_cursor(207+cursor_pos_1*(lth_sizeM-2),w_win/4+63,n);
		else if(choose==2) print_cursor(747+cursor_pos_2*(lth_sizeM-2),w_win/4+63,n);
		if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE,x,y);
			set_hover_markList(Menu,hover,j,tt,x,y,XEM,LOC2,buttons,nRow);
	        if(j!=hover&&j!=-1){
	        	if(j<nLecMenu) draw_button(Menu[j]);
	        	else if(j==11){
	        		if(choose==2||strlen(text2)!=0) draw_button(XEM);
				} 
	        	else if(j==12){
	        		if(is_click_filter) draw_button(LOC2);
				}  
	        	else if(j<100+nRow){
	        		if(is_click_text1||is_click_text2) draw_button(buttons[j-100]);
				} 
	        	if(hover<nLecMenu) highlight_button(Menu[hover],grey,white,white);
	        	else if(hover==11){
	        		if(choose==2||strlen(text2)!=0) highlight_button(XEM,grey,white,white);
				} 
	        	else if(hover==12){
	        		if(is_click_filter) highlight_button(LOC2,grey,white,white);
				} 
	        	else if(hover<nRow+100){
	        		if(is_click_text1||is_click_text2) highlight_button(buttons[hover-100],grey,white,white);
				} 
			}
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for(int i=0;i<nLecMenu;i++){
				if(i==tt) continue;
	         	if(is_area(Menu[i].area,x,y)){
	         		create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		        	Menu[tt].area.width+5,3,3);
		        	draw_button(Menu[tt]);
		        	tt=i;
	         		return;
				}
		    }
		    if(is_click_text1||is_click_text2){
		    	for(int i=0;i<nRow;i++){
			    	if(is_area(buttons[i].area,x,y)){
		    		    if(is_click_text1){
		    		    	strcpy(text1, CList.classes[indexs[(page-1)*10+i]]->classi4.MALOP);
		    		    	cursor_pos_1 = strlen(text1);
						} 
						else if(is_click_text2){						
							if(filter==1) {
								subNode1=Search_Subject(root,indexs[(page-1)*10+i]);
								strcpy(text2,subNode1->subi4.MAMH);
							}
							else{
								SNode = get_student_idx(CList.classes[idx_class]->SFirst,indexs[(page-1)*10+i]);
								strcpy(text2,SNode->stui4.MASV);
							}
							cursor_pos_2 = strlen(text2);
						}
						n = T_cursor+1;
					}
			    }
			}
			if(is_area(exit.area,x,y)){
				create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		       	Menu[tt].area.width+5,3,3);
		       	draw_button(Menu[tt]);
		       	delete_button(exit,3);
				tt=-1;
				return;
			}
			else if(is_area(page_after.area,x,y)){
				if(page<nPageTable){
					page ++;
					if(is_click_text1) set_MLTable(CList, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);
					else if(is_click_text2){
						if(filter==1)  set_MMHTable(MMH_MSV.area,root, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);	
						else set_MSVTable(CList.classes[idx_class]->SFirst, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);	
					}
				} 
			}
			else if(is_area(page_before.area,x,y)){
			    if(page>1) {
			    	page --;
				    if(is_click_text1) set_MLTable(CList, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);
				    else if(is_click_text2){
				    	if(filter==1)    set_MMHTable(MMH_MSV.area,root, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);	
					    else set_MSVTable(CList.classes[idx_class]->SFirst, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);	
				    }
			    }
		    }
			else if(is_area_opt(ML,x,y)){
				n =T_cursor+1;
				if(is_click_text1==0){
					xoa4(text1,text2,choose,1,nRow,is_click_filter,is_click_text1,is_click_text2,LOC2,XEM);
					is_click_text1 = 1;
					get_index_MLTable(CList,indexs,n_index,text1);
             		set_nPageTable(nRow,nPageTable,n_index,page,1);
             		set_MLTable(CList, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);
				}
				else xoa4(text1,text2,choose,1,nRow,is_click_filter,is_click_text1,is_click_text2,LOC2,XEM);
			}
			else if(is_area_opt(MMH_MSV,x,y)){		
				if(choose != 2){
					xoa4(text1,text2,choose,1,nRow,is_click_filter,is_click_text1,is_click_text2,LOC2,XEM);
					settextstyle(font_text,0,sizeS);
					if(strlen(text1)==0){
						out_text_xy(207,w_win/4+33,(char*)"Nhap ma lop truoc",3,darkRed);
						continue;
					} 
			    	else if((idx_class = search_CList_ML(CList,text1))==-1){
			    		out_text_xy(207,w_win/4+33,(char*)"Ma lop khong dung",3,darkRed);
			    		continue;
					} 
			    	else {
					    if(choose==1) draw_button(XEM);
				    	cursor_pos_2 = (x - 740)/(lth_sizeM-2);
				    	if(filter==1){
				       		if (cursor_pos_2>strlen(text2)&&strlen(text2)<15) cursor_pos_2 = strlen(text2);
				        	else if(cursor_pos_2>15) cursor_pos_2=15;
				    	}
					    else{
				   		    if (cursor_pos_2>strlen(text2)&&strlen(text2)<11) cursor_pos_2 = strlen(text2);
				    	    else if(cursor_pos_2>11) cursor_pos_2=11;
				    	}
			    	}			
				}
				if(is_click_text2  == 0 ){
					is_click_text2 = 1;
					choose = 2;
					if(filter ==1){
						n_index=0;
						get_index_MMHTable(root,indexs,n_index,text2);
		           		set_nPageTable(nRow,nPageTable,n_index,page,1);
		           		set_MMHTable(MMH_MSV.area,root, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);	
					}
					else{
						get_index_MSVTable(CList.classes[idx_class]->SFirst,indexs,n_index,text2);
		           		set_nPageTable(nRow,nPageTable,n_index,page,1);
		           		set_MSVTable(CList.classes[idx_class]->SFirst, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);	
					}		
				}
				else xoa4(text1,text2,choose,2,nRow,is_click_filter,is_click_text1,is_click_text2,LOC2,XEM);
			}
			else if(is_area(XEM.area,x,y)&&strlen(text1)!=0){
				settextstyle(font_text,0,sizeS);
				if(filter==1){
					if(strlen(text2)==0) {
						if(choose!=2) continue;
						out_text_xy(747,w_win/4+33,(char*)"Nhap ma MH",3,darkRed);
					}
					else {
				     	if((subNode = Search_Subject_MMH(root,text2))==NULL){
				     	    xoa4(text1,text2,choose,2,nRow,is_click_filter,is_click_text1,is_click_text2,LOC2,XEM);
				     	    out_text_xy(747,w_win/4+33,(char*)"Ma MH khong dung",3,darkRed);	
		    			}
			  
				    	else{
				    		tt = 12;
				     		CLASS = CList.classes[idx_class];
				     		subNode->subi4=subNode1->subi4;
				     		return;
						}
					}
				}	
				else{
					if(strlen(text2)==0){
						if(choose!=2) continue;
					    out_text_xy(747,w_win/4+33,(char*)"Nhap ma SV",3,darkRed);
					} 
					else {
						SNode = search_SList_MSSV(CList.classes[idx_class]->SFirst,text2);
						if(SNode==NULL){
							out_text_xy(747,w_win/4+33,(char*)"Ma SV khong dung",3,darkRed);
							choose = 2;
						} 
						else{
							tt = 11;
							return;
						}
					}
				}
			}
			else if(is_area_opt(LOC,x,y)){
				if(is_click_filter==0){
					xoa4(text1,text2,choose,-1,nRow,is_click_filter,is_click_text1,is_click_text2,LOC2,XEM);
					is_click_filter = 1;
				    draw_button(LOC2);
				}
				else xoa4(text1,text2,choose,-1,nRow,is_click_filter,is_click_text1,is_click_text2,LOC2,XEM);
			}
			else if(is_area(LOC2.area,x,y)&&is_click_filter){
				n = T_cursor+1;
				if(strcmp(LOC.text,"MON HOC")==0){
					filter = 2;
					strcpy(LOC2.text,LOC.text);
				    strcpy(LOC.text,"SINH VIEN");
				    out_text_xy(650,w_win/4+60,(char *)"MA SV:",3,black);
				} 
				else{
					filter=1;
					strcpy(LOC2.text,LOC.text);
				    strcpy(LOC.text,"MON HOC");
				    draw_button_opt(MMH_MSV);
				    settextstyle(font_text,0,sizeM);
					out_text_xy(650,w_win/4+60,(char *)"MA MH:",3,black);
				}
				draw_button_opt(ML);
				draw_button_opt(MMH_MSV);
				highlight_button(LOC2,3,3,3);
				draw_button(LOC);
				is_click_filter = 0;
				text1[0] ='\0';
				text2[0] ='\0';
			    cursor_pos_1 =0;
			    cursor_pos_2 =0;
			}
			else if(is_area(ML.area,x,y)){
				n = T_cursor +1;
				out_text_xy(747,w_win/4+33,(char*)"Ma MH toi da 11 ki tu",3,3);
				if(choose!=1)    xoa4(text1,text2,choose,1,nRow,is_click_filter,is_click_text1,is_click_text2,LOC2,XEM);
				cursor_pos_1 = (x - 200)/(lth_sizeM-2);
			    if (cursor_pos_1>strlen(text1)&&strlen(text1)<11) cursor_pos_1 = strlen(text1);
			    else if(cursor_pos_1>11) cursor_pos_1=11;
			}
			else if(is_area(MMH_MSV.area,x,y)){
				n = T_cursor+1;
				if(choose != 2){
					xoa4(text1,text2,choose,1,nRow,is_click_filter,is_click_text1,is_click_text2,LOC2,XEM);
					settextstyle(font_text,0,sizeS);
					if(strlen(text1)==0){
						out_text_xy(207,w_win/4+33,(char*)"Nhap ma lop truoc",3,darkRed);
						continue;
					} 
			    	else if((idx_class = search_CList_ML(CList,text1))==-1){
			    		out_text_xy(207,w_win/4+33,(char*)"Ma lop khong dung",3,darkRed);
			    		continue;
					} 
			    	else {
					    draw_button(XEM);
				        choose =2;
			    	}			
				}
				cursor_pos_2 = (x - 740)/(lth_sizeM-2);
				if(filter==1){
				  	if (cursor_pos_2>strlen(text2)&&strlen(text2)<15) cursor_pos_2 = strlen(text2);
				    else if(cursor_pos_2>15) cursor_pos_2=15;
				}
		        else{
				    if (cursor_pos_2>strlen(text2)&&strlen(text2)<11) cursor_pos_2 = strlen(text2);
				    else if(cursor_pos_2>11) cursor_pos_2=11;
				}
			}
			else xoa4(text1,text2,choose,0,nRow,is_click_filter,is_click_text1,is_click_text2,LOC2,XEM);
			settextstyle(font_text,0,sizeS);
			if(choose==1) out_text_xy(207,w_win/4+63,text1,white,black);
			else if(choose==2) out_text_xy(747,w_win/4+63,text2,white,black);
		}
		if(kbhit()){
			n = T_cursor+1;
			key = Key();
			if(choose == 1){
				settextstyle(font_text,0,sizeS);
				out_text_xy(207,w_win/4+33,(char*)"Ma lop toi da 11 ki tu",3,3);
	            print_text_bar(207,w_win/4+63,text1,11,white,white);
				if(key==key_Right){
	                if(cursor_pos_1<strlen(text1)) cursor_pos_1++;
				}
				else if(key==key_Left){
	             if(cursor_pos_1>0) cursor_pos_1--;
				}
				else{ 
					if(key==key_BS){
						if(cursor_pos_1 >0){
							strcpy(text1 + cursor_pos_1-1, text1 + cursor_pos_1);
							cursor_pos_1--;
						}
						else continue; 
				  	}
			    	else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'||key==(int)'-'){
			    	   	if(strlen(text1)==MAX_MALOP){
			            	settextstyle(font_text,0,sizeS-1);
							out_text_xy(207,w_win/4+33,(char*)"Ma lop toi da 11 ki tu",3,darkRed);
						}
						else{
						   	ch = (char)key;
							upper_chr(ch); 
		    	   			insert_chr_to_str(text1,ch,cursor_pos_1);
		    			   	if(cursor_pos_1 < 11) cursor_pos_1++;
						}
					}
			    }
				print_text_bar(207,w_win/4+63,text1,11,white,black);
				if(is_click_text1){
					delay(10);
					get_index_MLTable(CList,indexs,n_index,text1);
	             	set_nPageTable(nRow,nPageTable,n_index,page,1);
	             	set_MLTable(CList, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);
				}
			}
			else if(choose==2){
				if(filter==1){
					settextstyle(font_text,0,sizeS);
					out_text_xy(747,w_win/4+33,(char*)"Ma MH toi da 15 ki tu",3,3);
	                print_text_bar(747,w_win/4+63,text2,15,white,white);
				    if(key==key_Right){
	                    if(cursor_pos_2<strlen(text2)) cursor_pos_2++;
					}
				    else if(key==key_Left){
	                    if(cursor_pos_2>0) cursor_pos_2--;
					}
					else if(key==key_BS){
						if(cursor_pos_2 >0){
							strcpy(text2 + cursor_pos_2-1, text2 + cursor_pos_2);
							cursor_pos_2--;
						}
						else continue; 
			  	    }
		    	    else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'||key==(int)'-'){
		    	    	if(strlen(text2)==MAX_MAMH){
		            		settextstyle(font_text,0,sizeS-1);
							out_text_xy(747,w_win/4+33,(char*)"Ma MH toi da 15 ki tu",3,darkRed);
					    }
					    else{
					    	ch = (char)key;
							upper_chr(ch); 
	    	   				insert_chr_to_str(text2,ch,cursor_pos_2);
	    			    	if(cursor_pos_2 < 15) cursor_pos_2++;
						}
				    }
				    print_text_bar(747,w_win/4+63,text2,15,white,black);
				    if(is_click_text2){
				    	delay(10);
				    	n_index=0;
				    	get_index_MMHTable(root,indexs,n_index,text2);
	             		set_nPageTable(nRow,nPageTable,n_index,page,1);
	             		set_MMHTable(MMH_MSV.area,root, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);
				    }	
			    }
			    else{
			    	settextstyle(font_text,0,sizeS);
					out_text_xy(747,w_win/4+33,(char*)"Ma SV toi da 11 ki tu",3,3);
	                print_text_bar(747,w_win/4+63,text2,11,white,white);
				    if(key==key_Right){
	                    if(cursor_pos_2<strlen(text2)) cursor_pos_2++;
					}
				    else if(key==key_Left){
	                    if(cursor_pos_2>0) cursor_pos_2--;
					}
					else if(key==key_BS){
						if(cursor_pos_2 >0){
							strcpy(text2 + cursor_pos_2-1, text2 + cursor_pos_2);
							cursor_pos_2--;
						}
						else continue; 
			  	    }
		    	    else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'||key==(int)'-'){
		    	    	if(strlen(text2)==MAX_MASV){
		            		settextstyle(font_text,0,sizeS-1);
							out_text_xy(747,w_win/4+33,(char*)"Ma SV toi da 11 ki tu",3,darkRed);
					    }
					    else{
					    	ch = (char)key;
							upper_chr(ch); 
	    	   				insert_chr_to_str(text2,ch,cursor_pos_2);
	    			    	if(cursor_pos_2 < 11) cursor_pos_2++;
						}
				    }
				    print_text_bar(747,w_win/4+63,text2,11,white,black);
				    if(is_click_text2){
				    	delay(10);
				    	get_index_MSVTable(CList.classes[idx_class]->SFirst,indexs,n_index,text2);
		           		set_nPageTable(nRow,nPageTable,n_index,page,1);
		           		set_MSVTable(CList.classes[idx_class]->SFirst, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);	
					}
				}
			}	
		}
	}	
}


//GIAO DIEN THI TRAC NGHIEM
void shuff_Quest(int IDs[],int nQuest,int n){//xao tron cau hoi - lay ngau nhien nQuest cau hoi cho bai thi len dau mang 
	int j, tmp;
	srand(time(NULL));//tao ra bo so ngau nhien
	for(int i=0;i<nQuest;i++){
		j = rand()%n + i; //random trong khoang i->n
		tmp = IDs[i];
		IDs[i] = IDs[j];
		IDs[j] =tmp;
		n--;
    }
}
void create_test(PTRSUB subNode, test& testi4){//tao bai thi - phai lay cau hoi  tu ds mon hoc 
	questList qList=subNode->subi4.ql;
	int *IDs = new int[qList.n];
	for(int i=0;i<qList.n;i++){
		IDs[i]=qList.Q[i].ID;
	}
	shuff_Quest(IDs,testi4.n,qList.n); 
	testi4.answers = alloc_AList(testi4.n);
	for(int i=0; i<testi4.n;i++){
		testi4.answers[i].ID = IDs[i];
		testi4.answers[i].TRALOI = 'X';
	}
	delete[] IDs;//giai phong
}
int nQ_True(questList &qList,test& testif){//tinh so cau tra loi dung
	int idx;
	char ans;
	int nTrue = 0;
	for(int i=0;i<testif.n;i++){
		idx = Search_Quest(qList,testif.answers[i].ID);
		ans=qList.Q[idx].DapAn;
		if (testif.answers[i].TRALOI == ans) nTrue++;
	}
	return nTrue;
}
void set_done_Quest(PTRSUB &root,test& testif){//ghi chu cau hoi da ra thi
	int idx;
	for(int i=0; i< testif.n;i++) {
		idx = Search_Quest(root->subi4.ql,testif.answers[i].ID);
		root->subi4.ql.Q[idx].done = 'T';
	}
}
void print_Question(questInfor& quesif,int color){
	settextstyle(6,0,1);
	print_text(200,120,quesif.NoiDung,53,color);
	print_text(265+30,219,quesif.A, 45,color);
	print_text(265+30,219+60,quesif.B,45,color);
	print_text(265+30,219+120,quesif.C,45,color);
	print_text(265+30,219+180,quesif.D,45,color);
}
float mark_test(questList &qList, test& testif){//ham tinh diem
	float mark = nQ_True(qList,testif)*10.0/testif.n;
	return roundf(mark*10)/10;//lam tron diem
}
bool is_submit(int& tgcl,int deadline){//xac nhan nop bai
	int x, y, j, hover=-1,s = 0, k = 0;
	AREA area;
	BUTTON Yes,No;
	set_area(area,l_win/2+330,w_win/2+240,strlen("Dong y")*(lth_sizeM-2)+14,30);
	set_button(Yes,area,(char*)"Dong y",sizeM-1,black,CENTER,3,3);
	draw_button(Yes);
	set_area(area,l_win/2+470,w_win/2+240,strlen("Huy")*(lth_sizeM-2)+14,30);
	set_button(No,area,(char*)"Huy",sizeM-1,black,CENTER,3,3);
	draw_button(No);
	settextstyle(font_text,0,sizeS);
	out_text_xy(l_win/2+300,w_win/2+190,(char*)"Ban co muon nop bai?",3,darkRed);
	while(1){
		delay(1);
		tgcl = remaining_time(deadline);
		if(tgcl>=0) print_time(l_win-497,w_win-57,tgcl);
		else return true;
		if(s){
			s--;
			if((s%5)==0){
				if(k==0){
					setcolor(white);
	             	k=1;
	 			}
	 			else{
	 				setcolor(black);
	             	k=0;
				}	
				rectangle(l_win/2+270,w_win/2+170,l_win/2+580,w_win/2+280);
			}
		}
		else {
			k=0;
			setcolor(red);
			rectangle(l_win/2+270,w_win/2+170,l_win/2+580,w_win/2+280);
		}
		if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE,x,y);
			j = hover;
			if(is_area(Yes.area,x,y)) hover = 1;
          	else if(is_area(No.area,x,y)) hover = 2;
			else hover=-2;	
          	if(j!=hover&&j!=-1){
	        	if(j==1) draw_button(Yes);
	        	else if(j==2) draw_button(No);
	        	if(hover==1) highlight_button(Yes,3,3,darkGreen);
	        	else if(hover==2) highlight_button(No,3,3,darkRed);
	        }
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			if(is_area(Yes.area,x,y)){
				create_1_bar(l_win/2+270,w_win/2+170,310,115,3,3);
				return true;
			} 
			else if(is_area(No.area,x,y)){
				create_1_bar(l_win/2+270,w_win/2+170,310,115,3,3);
             	return false;
			}
			else if((x<l_win/2+280)||(y<w_win/2+175)||(x>l_win/2+570)||(y>w_win/2+280)){
				s = 46;
			}			
		}
	}
}
void Thi_TN_interface(){//giao dien nhap thong tin thi tn
	out_text_xy(100,w_win/4,(char*)"MA MH:",3,black);
	out_text_xy(l_win/2+50,w_win/4,(char*)"SO CAU HOI THI:",3,black);
	out_text_xy(l_win/2+50,w_win/4+70,(char*)"SO PHUT THI:",3,black);
	create_1_bar(l_win/2+270,w_win/4,150,30,white,white);
	create_1_bar(l_win/2+230,w_win/4+70,150,30,white,white);
}
void Thi_TN(PTRSUB &root,classList& CList,PTRSUB &subNode, subInfor& subji4,BUTTON Menu[],int nMenu,int& nQue,int& nMin,int& tt,PTRS SNode){//chon thong tin thi trac nghiem
    Thi_TN_interface();
	int x,y, hover=-1,j, n = T_cursor+1,choose = 1,cursor_pos_MMH = 0,cursor_pos_nQ = 0, cursor_pos_nM = 0, key, is_click_MMH = 0, n_Q_of_subj;
	int indexs[MAX_SUBJ+1], n_index = 0, nRow = 0, nPageTable, page=1, last_nPageTable = -1, idx_subject;
	char ch, subjID_text[MAX_MAMH+1]={0}, nQuest[10]={0}, nMinute[10]={0}, buff[10];
	AREA area, nQuest_bar, nMinute_bar;
	BUTTON buttons[10]={}, exit, Enter, subjID, page_after, page_before;
	set_buttons_Thi_TN(exit,Enter,subjID,page_after,page_before,nQuest_bar,nMinute_bar);
	while(1){
		delay(1);
		if(choose==1) print_cursor(207+cursor_pos_MMH*(lth_sizeM-2),w_win/4+5,n);
		else if (choose==2) print_cursor(l_win/2+277+cursor_pos_nQ*(lth_sizeM-2),w_win/4+5,n);
		else if(choose==3) print_cursor(l_win/2+237+cursor_pos_nM*(lth_sizeM-2),w_win/4+75,n);
 		if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE,x,y);
			set_hover_Thi_TN(Menu,nMenu,hover,j,tt,x,y,Enter,buttons,nRow);
	        if(j!=hover&&j!=-1){
	        	if(j<nMenu) draw_button(Menu[j]);
	        	else if(j==11){
	        		if(choose==2||choose==3||strlen(nQuest)!=0&&strlen(nMinute)!=0) draw_button(Enter);
				} 
	        	else if(j<100+nRow){
	        		if(is_click_MMH) draw_button(buttons[j-100]);
				} 
	        	if(hover<nMenu) highlight_button(Menu[hover],grey,white,white);
	        	else if(hover==11){
	        		if(choose==2||choose==3||strlen(nQuest)!=0&&strlen(nMinute)!=0) highlight_button(Enter,grey,white,white);
				} 
	        	else if(hover<nRow+100){
	        		if(is_click_MMH) highlight_button(buttons[hover-100],grey,white,white);
				} 
			}
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for(int i=0;i<nMenu;i++){
				if(i==tt) continue;
	         	if(is_area(Menu[i].area,x,y)){
	         		create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		        	Menu[tt].area.width+5,3,3);
		        	draw_button(Menu[tt]);
		        	tt=i;
	         		return;
				}
		    }
		    if(is_click_MMH){
		    	for(int i=0;i<nRow;i++){
			    	if(is_area(buttons[i].area,x,y)){
			    		subNode=Search_Subject(root,indexs[(page-1)*10+i]);
		    		    strcpy(subjID_text,subNode->subi4.MAMH);
						cursor_pos_MMH = strlen(subjID_text);
					}
					n = T_cursor+1;
			    }
			}
			if(is_area(exit.area,x,y)){
				create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		       	Menu[tt].area.width+5,3,3);
		       	draw_button(Menu[tt]);
		       	delete_button(exit,3);
				tt=-1;
				return;
			}
			else if(is_area(page_after.area,x,y)){
				if(page<nPageTable){
					page ++;
					if(is_click_MMH) set_MMHTable(subjID.area,root, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);	
				} 
			}
			else if(is_area(page_before.area,x,y)){
			    if(page>1) {
			    	page --;
				    if(is_click_MMH) set_MMHTable(subjID.area,root, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);	
			    }
		    }
			else if(is_area(Enter.area,x,y)&&(strlen(subjID_text)!=0&&strlen(nQuest)!=0&&strlen(nMinute)!=0||choose==2||choose==3)){
				xoa5(subjID_text,nQuest,nMinute,choose,0,nRow,is_click_MMH,Enter);
				settextstyle(font_text,0,sizeS);
			    if(SNode != NULL) {
			    	if(search_MList_MMH(SNode->MFirst,subjID_text)!=NULL) {
			    		out_text_xy(207,w_win/4-30,(char*)"Mon hoc da thi",3,darkRed);
			    		print_text_bar(l_win/2+277,w_win/4+5,nQuest,3,white,white);
			   			print_text_bar(l_win/2+237,w_win/4+75,nMinute,3,white,white);
						nQuest[0] = nMinute[0] = '\0';
			    		cursor_pos_nQ = cursor_pos_nM = 0;
			    		continue;
					}
				}	
				if(strlen(nQuest)==0) out_text_xy(l_win/2+277,w_win/4+5+30,(char*)"Nhap so cau hoi",3,darkRed);	
			    if(strlen(nMinute)==0) out_text_xy(l_win/2+237,w_win/4+75+30,(char*)"Nhap so phut thi",3,darkRed);
				if(strlen(nQuest)==0||strlen(nMinute)==0) continue;
				highlight_button(exit,black,black,black);
				for(int i=0;i<nMenu;i++){
					if(i!=tt) highlight_button(Menu[i],darkWhite,white,white);
				}
				tt = 10;
				nQue = atoi(nQuest);
				nMin = atoi(nMinute);
				subji4 = subNode->subi4;
			    return;
			}
			else if(is_area(subjID.area,x,y)){
				n = T_cursor+1;
				print_text_bar(l_win/2+277,w_win/4+5,nQuest,3,white,white);
				print_text_bar(l_win/2+237,w_win/4+75,nMinute,3,white,white);
				nQuest[0] = nMinute[0] = '\0';
				cursor_pos_nQ = cursor_pos_nM = 0;
				xoa5(subjID_text,nQuest,nMinute,choose,1,nRow,is_click_MMH,Enter);
				cursor_pos_MMH = (x - 200)/(lth_sizeM-2);
			    if (cursor_pos_MMH>strlen(subjID_text)&&strlen(subjID_text)<15) cursor_pos_MMH = strlen(subjID_text);
				else if(cursor_pos_MMH>15) cursor_pos_MMH=15;
			}
			else if(is_area(nQuest_bar,x,y)){
				n = T_cursor+1;
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+277,w_win/4+5+30,(char*)"                      ",3,3);
				xoa5(subjID_text,nQuest,nMinute,choose,1,nRow,is_click_MMH,Enter);
				if(choose != 2||choose!=3){
					settextstyle(font_text,0,sizeS);
					if(strlen(subjID_text)==0){
						out_text_xy(207,w_win/4-30,(char*)"Nhap ma mon hoc",3,darkRed);
						continue;
					} 
			    	else if((subNode = Search_Subject_MMH(root,subjID_text))==NULL){
			    		out_text_xy(207,w_win/4-30,(char*)"Ma MH khong dung",3,darkRed);
			    		continue;
					} 
			    	else {
			    		subNode=Search_Subject_MMH(root,subjID_text);
			    		n_Q_of_subj= subNode->subi4.ql.n;
				        if(n_Q_of_subj ==0){
					        settextstyle(font_text,0,sizeS);
					        out_text_xy(207,w_win/4-30,(char*)"MH chua co cau hoi",3,darkRed);
			         	} 
					    else{
					    	draw_button(Enter);
				        	choose = 2;
						}
			    	}			
				}
				cursor_pos_nQ = (x - (l_win/2+270))/(lth_sizeM-2);
			    if (cursor_pos_nQ>strlen(nQuest)&&strlen(nQuest)<3) cursor_pos_nQ = strlen(nQuest);
				else if(cursor_pos_nQ>3) cursor_pos_nQ=3;
			}
			else if(is_area(nMinute_bar,x,y)){
				n = T_cursor+1;
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+237,w_win/4+75+30,(char*)"                          ",3,3);
				xoa5(subjID_text,nQuest,nMinute,choose,1,nRow,is_click_MMH,Enter);
				if(choose != 2||choose!=3){
					settextstyle(font_text,0,sizeS);
					if(strlen(subjID_text)==0){
						out_text_xy(207,w_win/4-30,(char*)"Nhap ma mon hoc",3,darkRed);
						continue;
					} 
			    	else if((subNode = Search_Subject_MMH(root,subjID_text))==NULL){
			    		out_text_xy(207,w_win/4-30,(char*)"Ma MH khong dung",3,darkRed);
			    		continue;
					} 
			    	else {
			    		subNode=Search_Subject_MMH(root,subjID_text);
			    		n_Q_of_subj= subNode->subi4.ql.n;
						if(n_Q_of_subj ==0){
							settextstyle(font_text,0,sizeS);
							out_text_xy(207,w_win/4-30,(char*)"MH hien chua co cau hoi",3,darkRed);
							continue;
						}
						else{
							draw_button(Enter);
				        	choose = 3;
						}
			    	}			
				}
				cursor_pos_nM = (x - (l_win/2+230))/(lth_sizeM-2);
			    if (cursor_pos_nM>strlen(nMinute)&&strlen(nMinute)<3) cursor_pos_nM = strlen(nMinute);
				else if(cursor_pos_nM>3) cursor_pos_nM=3;
			}
			else if(is_area_opt(subjID,x,y)){
				n =T_cursor+1;
				if(is_click_MMH==0){
				
			    	print_text_bar(l_win/2+277,w_win/4+5,nQuest,3,white,white);
			   		print_text_bar(l_win/2+237,w_win/4+75,nMinute,3,white,white);
					nQuest[0] = nMinute[0] = '\0';
		    		cursor_pos_nQ = cursor_pos_nM = 0;
					xoa5(subjID_text,nQuest,nMinute,choose,1,nRow,is_click_MMH,Enter);
					is_click_MMH = 1;
					n_index=0;
					get_index_MMHTable(root,indexs,n_index,subjID_text);
	             	set_nPageTable(nRow,nPageTable,n_index,page,1);
	             	set_MMHTable(subjID.area,root, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);
				}
				else xoa5(subjID_text,nQuest,nMinute,choose,1,nRow,is_click_MMH,Enter);
			}
			else xoa5(subjID_text,nQuest,nMinute,choose,0,nRow,is_click_MMH,Enter);
			settextstyle(font_text,0,sizeM);
			if(choose==1) print_text_bar(207,w_win/4+5,subjID_text,15,white,black);	
			else if(choose==2) print_text_bar(l_win/2+277,w_win/4+5,nQuest,3,white,black);	  
		}
		if(kbhit()){
			n = T_cursor+1;
			key = Key();
			if(choose==1){
			    settextstyle(font_text,0,sizeS);
				out_text_xy(207,w_win/4-30,(char*)"Ma MH toi da 15 ki tu",3,3);
	            print_text_bar(207,w_win/4+5,subjID_text,15,white,white);
				if(key==key_Right){
	                if(cursor_pos_MMH<strlen(subjID_text)) cursor_pos_MMH++;
				}
				else if(key==key_Left){
	                if(cursor_pos_MMH>0) cursor_pos_MMH--;
				}
				else if(key==key_BS){
					if(cursor_pos_MMH >0){
						strcpy(subjID_text + cursor_pos_MMH-1, subjID_text + cursor_pos_MMH);
						cursor_pos_MMH--;
					}
					else continue; 
			  	}
		    	else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'||key==(int)'-'){
		    	    if(strlen(subjID_text)==MAX_MAMH){
		            	settextstyle(font_text,0,sizeS-1);
						out_text_xy(207,w_win/4-30,(char*)"Ma MH toi da 15 ki tu",3,darkRed);
					}
					else{
					    ch = (char)key;
						upper_chr(ch); 
	    	   			insert_chr_to_str(subjID_text,ch,cursor_pos_MMH);
	    			   	if(cursor_pos_MMH < 15) cursor_pos_MMH++;
					}
			    }
				print_text_bar(207,w_win/4+5,subjID_text,15,white,black);
				if(is_click_MMH){
			    	delay(10);
			    	n_index=0;
				    get_index_MMHTable(root,indexs,n_index,subjID_text);
	             	set_nPageTable(nRow,nPageTable,n_index,page,1);
	             	set_MMHTable(subjID.area,root, buttons, indexs,n_index, page, nRow,nPageTable,last_nPageTable,page_after,page_before);
				}	
			}
			else if(choose==2){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+270,w_win/4+5+30,(char*)"Ma lop toi da 11 ki tu",3,3);
                print_text_bar(l_win/2+277,w_win/4+5,nQuest,3,white,white);
			    if(key==key_Right){
                    if(cursor_pos_nQ<strlen(nQuest)) cursor_pos_nQ++;
				}
			    else if(key==key_Left){
                    if(cursor_pos_nQ>0) cursor_pos_nQ--;
				}
				else if(key==key_Enter||key==key_Down){
			        cursor_pos_nM = strlen(nMinute);
					xoa5(subjID_text,nQuest,nMinute,choose,3,nRow,is_click_MMH,Enter);
				}
				else if(key==key_BS){
					if(cursor_pos_nQ >0){
						strcpy(nQuest+ cursor_pos_nQ-1, nQuest + cursor_pos_nQ);
						cursor_pos_nQ--;
					} 
		  	    }
	    	    else if(key>='0'&&key<='9'){
	    	    	ch = (char)key;
					upper_chr(ch); 
    	   			insert_chr_to_str(nQuest,ch,cursor_pos_nQ);
	    	    	if(atoi(nQuest)>n_Q_of_subj){
	    	    		strcpy(nQuest,itoa(n_Q_of_subj,buff,decimal));
	            		settextstyle(font_text,0,sizeS-1);
						out_text_xy(l_win/2+277,w_win/4+5+30,(char*)"So cau hoi toi da:",3,darkRed);
						out_text_xy(l_win/2+277+strlen("So cau hoi toi da: ")*11,w_win/4+5+30,itoa(n_Q_of_subj,buff,decimal),3,darkRed);
				    }
    			    if(cursor_pos_nQ < strlen(nQuest)) cursor_pos_nQ++;
			    }
			    print_text_bar(l_win/2+277,w_win/4+5,nQuest,3,white,black);
		    }
			else if(choose==3){
				settextstyle(font_text,0,sizeS);
				out_text_xy(l_win/2+230,w_win/4+75+30,(char*)"Ma lop toi da 11 ki tu",3,3);
                print_text_bar(l_win/2+237,w_win/4+75,nMinute,3,white,white);
			    if(key==key_Right){
                    if(cursor_pos_nM<strlen(nMinute)) cursor_pos_nM++;
				}
			    else if(key==key_Left){
                    if(cursor_pos_nM>0) cursor_pos_nM--;
				}
				else if(key==key_Up){
			        cursor_pos_nQ = strlen(nQuest);
					xoa5(subjID_text,nQuest,nMinute,choose,2,nRow,is_click_MMH,Enter);
				}
				else if(key==key_BS){
					if(cursor_pos_nM >0){
						strcpy(nMinute + cursor_pos_nM-1, nMinute + cursor_pos_nM);
						cursor_pos_nM--;
					} 
		  	    }
	    	    else if(key>='0'&&key<='9'){
				    ch = (char)key;
					upper_chr(ch); 
					insert_chr_to_str(nMinute,ch,cursor_pos_nM);
    	   			if(atoi(nMinute)>100){
    	   				strcpy(nMinute,"100");
	            		settextstyle(font_text,0,sizeS-1);
						out_text_xy(l_win/2+237,w_win/4+75+30,(char*)"Toi da 100 phut",3,darkRed);
				    }
				    if(cursor_pos_nM < 3) cursor_pos_nM++; 			    	
			    }
			    print_text_bar(l_win/2+237,w_win/4+75,nMinute,3,white,black);
		    }
		}
	}	
}
void Thi_TN_2_interface(int nPage,PTRS SNode, test& testi4, PTRSUB &subNode){//giao dien lam bai
	char buff[10], HO_TEN[MAX_HO+MAX_TEN+2];
	char ans[][3] = {"A.","B.","C.","D."}; 
	int x_y[]={5+35,w_win-70+8,5+15,w_win-70+19,5+35,w_win-70+30,5+35,w_win-70+8};
	int x_y2[]={150,w_win-70+8,150+20,w_win-70+19,150,w_win-70+30,150,w_win-70+8};
	create_solid_polygon( x_y, 4, black);
	create_solid_polygon( x_y2, 4, black);
	settextstyle(font_text,0,sizeM);
	out_text_xy(95,w_win-65,(char*)"/",3,black);
	out_text_xy(110,w_win-65,itoa(nPage,buff,decimal),3,black);
	settextstyle(font_text,0,sizeL-1);
	out_text_xy(l_win/3+110,w_win/2+200,(char*)"/",3,black);
	out_text_xy(l_win/3+130,w_win/2+200,itoa(testi4.n,buff,decimal),3,black);
    create_1_bar(l_win-504,w_win-60,126,30,white,white);
    setcolor(darkRed);
	rectangle(l_win/7,101,l_win/7+680,500);
	rectangle(l_win/7+1,101+1,l_win/7+680-1,500-1);
	rectangle(l_win/7,510,l_win/7+680,577);
	rectangle(l_win/7+1,510+1,l_win/7+680-1,577-1);
	settextstyle(6,0,1);
	for(int i=0;i<4;i++) out_text_xy(265,219+60*i,ans[i],3, black);
	settextstyle(font_text,0,sizeS);
	setcolor(darkRed);
	rectangle(l_win/2+270,w_win/2+170,l_win/2+580,w_win/2+280);
	setcolor(black);
	rectangle(l_win/2+275,w_win/2+175,l_win/2+575,w_win/2+275);
	if(SNode!=NULL){
		out_text_xy(l_win/2+270,w_win/5,(char*)"MA SV:",3,black);
		out_text_xy(l_win/2+450,w_win/5,SNode->stui4.MASV,3,black);
		strcpy(HO_TEN,SNode->stui4.HO);
		strcat(HO_TEN," ");
		strcat(HO_TEN,SNode->stui4.TEN);
		print_text(l_win/2+270,w_win/5+30,HO_TEN,26,darkRed);
	}
	else{
		out_text_xy(l_win/2+270,w_win/5,(char*)"GV",3,black);
		print_text(l_win/2+270,w_win/5+30,(char*)"GV",26,darkRed);
	}
	out_text_xy(l_win/2+270,w_win/5+90,(char*)"MA MH:",3,black);
	out_text_xy(l_win/2+450,w_win/5+90,subNode->subi4.MAMH,3,black);
    print_text(l_win/2+270,w_win/5+120,subNode->subi4.TENMH,26,darkRed);
    out_text_xy(l_win/2+270,w_win/5+180,(char*)"So cau:",3,black);
    itoa(testi4.n,buff,decimal);
    out_text_xy(l_win/2+450,w_win/5+180,buff,3,black);
    out_text_xy(l_win/2+270,w_win/5+210,(char*)"Thoi gian:",3,black);
    itoa(testi4.nMin,buff,decimal);
    out_text_xy(l_win/2+450,w_win/5+210,buff,3,black);
    out_text_xy(l_win/2+450+strlen(buff)*(lth_sizeM-2),w_win/5+210,(char*)"'",3,black);	
    
}

void Thi_TN_2(classList& CList,PTRSUB &root, PTRSUB &subNode, PTRS& SNode,BUTTON Menu[],int nMenu,int& tt,int nMinute, int& nQuestion){//giao dien thi trac nghiem
	char buff[10];
	test testi4;
	testi4.n = nQuestion;
    testi4.nMin = nMinute;
	create_test(subNode,testi4);
	int idx_Q=Search_Quest(subNode->subi4.ql,testi4.answers[0].ID);
	print_Question(subNode->subi4.ql.Q[idx_Q],black);
	int tgcl,x,y, hover=-1,j, nPage = nQuestion/15, page = 1, Quest = 1,nRow;
	time_t deadline = dead_line(nMinute*60);
	BUTTON Questions[15], submit;
	AREA page_after, page_before, Quest_after,Quest_before,area;
	CTick DA[4];
	if(nQuestion%15!=0) nPage++;
	settextstyle(font_text,0,sizeM);
	out_text_xy(60,w_win-65,itoa(page,buff,decimal),3,black);
	settextstyle(font_text,0,sizeL-1);
	out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,black);
	Thi_TN_2_interface(nPage,SNode,testi4,subNode);
	set_buttons_Thi_TN_2(Questions,submit, page_after, page_before, Quest_after, Quest_before,DA);
	set_Quest_Table(Questions,page,nPage,Quest,nQuestion,nRow,testi4.answers);
	while(1){
		delay(1);
		tgcl = remaining_time(deadline);
		if(tgcl>=0) print_time(l_win-497,w_win-57,tgcl);
		else break;
		if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE,x,y);
			j = hover;	
			if(is_area(submit.area,x,y)) hover = 1;
			else hover = 0;
	        if(j!=-1&&hover!=j){
	        	if(j==1) draw_button(submit);
	        	if(hover==1) highlight_button(submit,grey,white,white);
			}  
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for(int i=0;i<4;i++){
				if(is_area_CTick(DA[i],x,y)){
					if(testi4.answers[Quest-1].TRALOI=='X') highlight_button(Questions[(Quest-1)%15],grey,darkBlue,white);
					else draw_CTick(DA[(int)(testi4.answers[Quest-1].TRALOI-'A')]);
					testi4.answers[Quest-1].TRALOI='A'+i;
					Tick_CTick(DA[i],grey);
			    }
			}
			if(!is_area(Questions[(Quest-1)%15].area,x,y)){
				for(int i=0;i<nRow;i++){
			        if(is_area(Questions[i].area,x,y)){
			        	settextstyle(font_text,0,sizeL-1);
			        	out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,3);
			        	area = Questions[(Quest-1)%15].area;
			        	setcolor(white);
			        	rectangle(area.x,area.y,area.x+area.length,area.y+area.width);
			        	area = Questions[i].area;
			        	setcolor(darkBlue);
			        	rectangle(area.x,area.y,area.x+area.length,area.y+area.width);
			        	if(testi4.answers[Quest-1].TRALOI!='X') draw_CTick(DA[testi4.answers[Quest-1].TRALOI-'A']);
						print_Question(subNode->subi4.ql.Q[idx_Q],3);         
						Quest = (page-1)*15+i+1;
			        	idx_Q= Search_Quest(subNode->subi4.ql,testi4.answers[Quest-1].ID);
                     	print_Question(subNode->subi4.ql.Q[idx_Q],black);
			            if(testi4.answers[Quest-1].TRALOI!='X') Tick_CTick(DA[testi4.answers[Quest-1].TRALOI-'A'],grey);
                    	settextstyle(font_text,0,sizeL-1);
						out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,black);
                    	settextstyle(font_text,0,sizeM);
                    	if(Quest>1) out_text_xy(l_win/4-50,w_win/2+205,(char*)"CAU TRUOC",3,darkBlue);
						else out_text_xy(l_win/4-50,w_win/2+205,(char*)"CAU TRUOC",3,3);
						if(Quest<nQuestion) out_text_xy(l_win/4+370,w_win/2+205,(char*)"CAU SAU",3,darkBlue);
						else out_text_xy(l_win/4+370,w_win/2+205,(char*)"CAU SAU",3,3);
						itoa(testi4.answers[(page-1)*15+i].ID,buff,decimal);
					} 
		    	}
	     	}
			if(is_area(submit.area,x,y)) {
				if(is_submit(tgcl,deadline)) break;
			}
		    else if(is_area(page_after,x,y)){
		    	if(page<nPage){
		    		page++;
		    		settextstyle(font_text,0,sizeL-1);
			        out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,3);
		    		settextstyle(font_text,0,sizeM);
                    out_text_xy(60,w_win-65,itoa(page,buff,decimal),3,black);
                    if(testi4.answers[Quest-1].TRALOI!='X') draw_CTick(DA[testi4.answers[Quest-1].TRALOI-'A']);
					print_Question(subNode->subi4.ql.Q[idx_Q],3);		            
					Quest = (page-1)*15+1;
			        idx_Q= Search_Quest(subNode->subi4.ql,testi4.answers[Quest-1].ID);
                    print_Question(subNode->subi4.ql.Q[idx_Q],black);
                    settextstyle(font_text,0,sizeL-1);
                    out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,black);
                    set_Quest_Table(Questions,page,nPage,Quest,nQuestion,nRow,testi4.answers);
			        if(testi4.answers[Quest-1].TRALOI!='X') Tick_CTick(DA[testi4.answers[Quest-1].TRALOI-'A'],grey);
				}
			}
			else if(is_area(page_before,x,y)){
				if(page>1){
					page--;
					settextstyle(font_text,0,sizeL-1);
			        out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,3);
					settextstyle(font_text,0,sizeM);
                    out_text_xy(60,w_win-65,itoa(page,buff,decimal),3,black);
                    if(testi4.answers[Quest-1].TRALOI!='X') draw_CTick(DA[testi4.answers[Quest-1].TRALOI-'A']);
					print_Question(subNode->subi4.ql.Q[idx_Q],3);			            
					Quest = (page-1)*15+1;
			        idx_Q= Search_Quest(subNode->subi4.ql,testi4.answers[Quest-1].ID);
                   	print_Question(subNode->subi4.ql.Q[idx_Q],black);
                    settextstyle(font_text,0,sizeL-1);
                    out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,black);
                    set_Quest_Table(Questions,page,nPage,Quest,nQuestion,nRow,testi4.answers);
			        if(testi4.answers[Quest-1].TRALOI!='X') Tick_CTick(DA[testi4.answers[Quest-1].TRALOI-'A'],grey);
				}	
			}
			else if(is_area(Quest_after,x,y)){
				if(Quest<nQuestion){
					if(testi4.answers[Quest-1].TRALOI!='X') draw_CTick(DA[testi4.answers[Quest-1].TRALOI-'A']);	
					settextstyle(font_text,0,sizeL-1);
					out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,3);
				    print_Question(subNode->subi4.ql.Q[idx_Q],3);
					Quest++;
					idx_Q= Search_Quest(subNode->subi4.ql,testi4.answers[Quest-1].ID);
                    print_Question(subNode->subi4.ql.Q[idx_Q],black);
					settextstyle(font_text,0,sizeL-1);
                    out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,black);
                    settextstyle(font_text,0,sizeM);
					if(Quest%15==1){
					    page++;
					    set_Quest_Table(Questions,page,nPage,Quest,nQuestion,nRow,testi4.answers);
                       	out_text_xy(60,w_win-65,itoa(page,buff,decimal),3,black);					    
					} 
					else {
						area = Questions[(Quest-2)%15].area;
			        	setcolor(white);
			        	rectangle(area.x,area.y,area.x+area.length,area.y+area.width);
			        	area = Questions[(Quest-1)%15].area;
			        	setcolor(darkBlue);
			        	rectangle(area.x,area.y,area.x+area.length,area.y+area.width);
					}
			        if(testi4.answers[Quest-1].TRALOI!='X') Tick_CTick(DA[testi4.answers[Quest-1].TRALOI-'A'],grey);	
					if(Quest==nQuestion) out_text_xy(l_win/4+370,w_win/2+205,(char*)"CAU SAU",3,3);
					if(Quest==2) out_text_xy(l_win/4-50,w_win/2+205,(char*)"CAU TRUOC",3,darkBlue);		    
				}
			}
			else if(is_area(Quest_before,x,y)){
				if(Quest>1){
					if(testi4.answers[Quest-1].TRALOI!='X') draw_CTick(DA[testi4.answers[Quest-1].TRALOI-'A']);	
					settextstyle(font_text,0,sizeL-1);
					out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,3);
					print_Question(subNode->subi4.ql.Q[idx_Q],3);
					Quest--;
					idx_Q= Search_Quest(subNode->subi4.ql,testi4.answers[Quest-1].ID);
                    print_Question(subNode->subi4.ql.Q[idx_Q],black);
					settextstyle(font_text,0,sizeL-1);
                    out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,black);
                    settextstyle(font_text,0,sizeM);
					if(Quest%15==0){
					    page--;
					    set_Quest_Table(Questions,page,nPage,Quest,nQuestion,nRow,testi4.answers);
                       	out_text_xy(60,w_win-65,itoa(page,buff,decimal),3,black);					    
					} 
					else {
						area = Questions[Quest%15].area;
			        	setcolor(white);
			        	rectangle(area.x,area.y,area.x+area.length,area.y+area.width);
			        	area = Questions[(Quest-1)%15].area;
			        	setcolor(darkBlue);
			        	rectangle(area.x,area.y,area.x+area.length,area.y+area.width);
					}
			        if(testi4.answers[Quest-1].TRALOI!='X') Tick_CTick(DA[testi4.answers[Quest-1].TRALOI-'A'],grey);
					if(Quest==1) out_text_xy(l_win/4-50,w_win/2+205,(char*)"CAU TRUOC",3,3);
					else if(Quest==nQuestion-1)	out_text_xy(l_win/4+370,w_win/2+205,(char*)"CAU SAU",3,darkBlue);	     
				}
			}
		}
	}
	tt = 20;
    markInfor marki4;
    set_markInfor(marki4,subNode->subi4.MAMH,mark_test(subNode->subi4.ql,testi4)); 
    if(SNode==NULL){
        SNode = new stuNode;
        SNode->MFirst = NULL;
		SNode->Next = NULL;	
		insert_first_MList(SNode->MFirst,marki4,testi4);
	}
	else{
		insert_first_MList(SNode->MFirst,marki4,testi4);
		set_done_Quest(root,testi4);
	}
	nQuestion = nQ_True(subNode->subi4.ql,testi4);
	return;
}

//GIAO DIEN KET QUA THI
void result(PTRS SNode,int &tt,int nTrue,int user){//giao dien ket qua thi
	char buff[10];
    int x,y,j,hover=-1;
	itoa(nTrue,buff,decimal);
	create_1_bar(l_win/2-400,w_win/2-100,400+2,200+2,black,black);
	create_1_bar(l_win/2-400,w_win/2-100,400,200,white,black);
	settextstyle(font_text,0,sizeM+1);
	out_text_xy(l_win/2-320,w_win/2-90,(char*)"KET QUA THI",white,darkRed);
	settextstyle(font_text,0,sizeM);
	out_text_xy(l_win/2-360,w_win/2-30,(char*)"SO CAU DUNG:",white,black);
	out_text_xy(l_win/2-130,w_win/2-30,buff,white,black);
	x = lth_sizeM*strlen(buff);
	out_text_xy(l_win/2-130+ x,w_win/2-30,(char*)"/",white,black);
	itoa(SNode->MFirst->testi4.n,buff,decimal);
	out_text_xy(l_win/2-130+ x + lth_sizeM, w_win/2-30,buff,white,black);
	out_text_xy(l_win/2-360,w_win/2,(char*)"DIEM:",white,black);
	if(SNode->MFirst->marki4.Diem==10) snprintf(buff,5,"%f",SNode->MFirst->marki4.Diem);
	else snprintf(buff,4,"%f",SNode->MFirst->marki4.Diem);
	out_text_xy(l_win/2-130,w_win/2,buff,white,black);
	BUTTON XKQ, VTD;
	AREA area;
	set_area(area,l_win/2-320,w_win/2+45,90,30);
	set_button(XKQ,area,(char*)"XEM KQ",sizeM,darkBlue,CENTER,white,white);
	draw_button(XKQ);
	set_area(area,l_win/2-200,w_win/2+45,110,30);
	set_button(VTD,area,(char*)"QUAY VE",sizeM,darkBlue,CENTER,white,white);
	draw_button(VTD);
	while(1){
		delay(1);
		if(ismouseclick(WM_MOUSEMOVE)){
			getmouseclick(WM_MOUSEMOVE,x,y);
			j = hover;
			if(is_area(XKQ.area,x,y)) hover = 1;
          	else if(is_area(VTD.area,x,y)) hover = 2;
			else hover=-2;	
          	if(j!=hover&&j!=-1){
	        	if(j==1) draw_button(XKQ);
	        	else if(j==2) draw_button(VTD);
	        	if(hover==1) highlight_button(XKQ,white,white,darkGreen);
	        	else if(hover==2) highlight_button(VTD,white,white,darkGreen);
	        }
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			if(is_area(XKQ.area,x,y)){
				tt = 21;
				return;
			} 
			else if(is_area(VTD.area,x,y)){
				if(user==LECTURER){
					free_SList(SNode);
					tt = 2; 
				}
				else tt = 0;
				return;
			}
     	}
	} 
}
void xem_KQ_interface(PTRSUB &root,PTRS SNode,PTRSUB &subNode,int nPage,PTRM MNode){//giao dien xem cac cau hoi da thi va co dap an
	char buff[10], HO_TEN[MAX_HO+MAX_TEN+2];
	char ans[][3] = {"A.","B.","C.","D."}; 
	int x_y[]={5+35,w_win-70+8,5+15,w_win-70+19,5+35,w_win-70+30,5+35,w_win-70+8};
	int x_y2[]={150,w_win-70+8,150+20,w_win-70+19,150,w_win-70+30,150,w_win-70+8};
	create_solid_polygon( x_y, 4, black);
	create_solid_polygon( x_y2, 4, black);
	settextstyle(font_text,0,sizeM);
	out_text_xy(95,w_win-65,(char*)"/",3,black);
	out_text_xy(110,w_win-65,itoa(nPage,buff,decimal),3,black);
	settextstyle(font_text,0,sizeL-1);
	out_text_xy(l_win/3+110,w_win/2+200,(char*)"/",3,black);
	out_text_xy(l_win/3+130,w_win/2+200,itoa(MNode->testi4.n,buff,decimal),3,black);
    setcolor(darkRed);
	rectangle(l_win/7,101,l_win/7+680,500);
	rectangle(l_win/7+1,101+1,l_win/7+680-1,500-1);
	rectangle(l_win/7,510,l_win/7+680,577);
	rectangle(l_win/7+1,510+1,l_win/7+680-1,577-1);
	settextstyle(6,0,1);
	for(int i=0;i<4;i++) out_text_xy(265,219+60*i,ans[i],3, black);
	settextstyle(font_text,0,sizeS);
	if(stricmp(SNode->stui4.MASV,"GV")==0){
		out_text_xy(l_win/2+270,w_win/5+30,(char*)"GV",3,black);
		print_text(l_win/2+270,w_win/5+60,(char*)"GV",26,darkRed);		
	}
	else{
		out_text_xy(l_win/2+270,w_win/5+30,(char*)"MA SV:",3,black);
		out_text_xy(l_win/2+450,w_win/5+30,SNode->stui4.MASV,3,black);
		strcpy(HO_TEN,SNode->stui4.HO);
		strcat(HO_TEN," ");
		strcat(HO_TEN,SNode->stui4.TEN);
		print_text(l_win/2+270,w_win/5+60,HO_TEN,26,darkRed);
	}
	out_text_xy(l_win/2+270,w_win/5+120,(char*)"MA MH:",3,black);
	out_text_xy(l_win/2+450,w_win/5+120,subNode->subi4.MAMH,3,black);
    print_text(l_win/2+270,w_win/5+150,subNode->subi4.TENMH,26,darkRed);
    out_text_xy(l_win/2+270,w_win/5+210,(char*)"So cau:",3,black);
    itoa(MNode->testi4.n,buff,decimal);
    out_text_xy(l_win/2+450,w_win/5+210,buff,3,black);
    out_text_xy(l_win/2+270,w_win/5+240,(char*)"Thoi gian:",3,black);
    itoa(MNode->testi4.nMin,buff,decimal);
    out_text_xy(l_win/2+450,w_win/5+240,buff,3,black);
    out_text_xy(l_win/2+450+strlen(buff)*(lth_sizeM-2),w_win/5+240,(char*)"'",3,black);	
    out_text_xy(l_win/2+270,w_win/5+300,(char*)"So cau dung:",3,black);
    itoa(nQ_True(subNode->subi4.ql,MNode->testi4),buff,decimal);
    out_text_xy(l_win/2+450,w_win/5+300,buff,3,darkRed);
    out_text_xy(l_win/2+270,w_win/5+330,(char*)"Diem:",3,black);
    if(MNode->marki4.Diem!=10) snprintf(buff,4,"%f",MNode->marki4.Diem);
    else snprintf(buff,5,"%f",MNode->marki4.Diem);
    out_text_xy(l_win/2+450,w_win/5+330,buff,3,darkRed);
}
void xem_KQ(PTRSUB &root,PTRS SNode,PTRSUB &subNode,BUTTON Menu[],int nMenu,int& tt){//danh sach cac cau hoi da thi va co dap an
	int x,y, hover=-1,j, nPage, page = 1, Quest = 1,nRow;
	BUTTON Questions[15],exit,Return;
	AREA page_after, page_before, Quest_after,Quest_before,area;
	CTick DA[4];
	char buff[10];
	PTRM MNode = search_MList_MMH(SNode->MFirst,subNode->subi4.MAMH);
	int idx = Search_Quest(subNode->subi4.ql,MNode->testi4.answers[0].ID);
	print_Question(subNode->subi4.ql.Q[idx],black);
	nPage = MNode->testi4.n/15;
	if(MNode->testi4.n%15!=0) nPage++;
	set_exit(exit,(char*)"VE TRANG DAU",l_win-25,5,black);
	setcolor(darkRed);
	set_exit(Return,(char*)"QUAY LAI",l_win-50,100,darkRed);
	settextstyle(font_text,0,sizeM);
	out_text_xy(60,w_win-65,itoa(page,buff,decimal),3,black);
	settextstyle(font_text,0,sizeL-1);
	out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,black);
	xem_KQ_interface(root,SNode,subNode,nPage,MNode);
	set_buttons_xem_KQ(Questions, page_after, page_before, Quest_after, Quest_before,DA);
	set_Quest_Table2(subNode->subi4.ql,Questions,page,nPage,Quest,MNode->testi4.n,nRow,MNode->testi4.answers);
	if(MNode->testi4.answers[Quest-1].TRALOI!='X') Tick_CTick(DA[MNode->testi4.answers[Quest-1].TRALOI-'A'],darkRed);
	Tick_CTick(DA[subNode->subi4.ql.Q[idx].DapAn-'A'],darkGreen);
	while(1){
		delay(1);
	    if(ismouseclick(WM_MOUSEMOVE)){
			j = hover;
			getmouseclick(WM_MOUSEMOVE,x,y);	
			for(hover=0;hover<nMenu;hover++){
				if(hover==tt) continue;
				if(is_area(Menu[hover].area,x,y)) break;
			}
	        if(j!=-1&&hover!=j&&j!=nMenu) draw_button(Menu[j]); 	
	        if(hover!=j&&hover!=nMenu) highlight_button(Menu[hover],grey,white,white);
		}
   		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for(int i=0;i<nMenu;i++){
				if(i==tt) continue;
	         	if(is_area(Menu[i].area,x,y)){
	         		create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		        	Menu[tt].area.width+6,3,3);
		        	draw_button(Menu[tt]);
		        	tt = i;
	         		return;
				}
		    }
			if(is_area(exit.area,x,y)){
				create_1_bar(Menu[tt].area.x,Menu[tt].area.y,Menu[tt].area.length+1,
		       	Menu[tt].area.width+6,3,3);
		       	draw_button(Menu[tt]);
		       	delete_button(exit,3);
				tt=-1;
				return;
			}
			if(is_area(Return.area,x,y)){
				if(tt==3) tt = 100; 
				return;
			}		  
			if(!is_area(Questions[(Quest-1)%15].area,x,y)){
				for(int i=0;i<nRow;i++){
			        if(is_area(Questions[i].area,x,y)){
			        	settextstyle(font_text,0,sizeL-1);
			        	out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,3);
			        	area = Questions[(Quest-1)%15].area;
			        	setcolor(white);
			        	rectangle(area.x,area.y,area.x+area.length,area.y+area.width);
			        	area = Questions[i].area;
			        	setcolor(darkBlue);
			        	rectangle(area.x,area.y,area.x+area.length,area.y+area.width);
			        	if(MNode->testi4.answers[Quest-1].TRALOI!='X') draw_CTick(DA[MNode->testi4.answers[Quest-1].TRALOI-'A']);
						draw_CTick(DA[subNode->subi4.ql.Q[idx].DapAn-'A']);
						print_Question(subNode->subi4.ql.Q[idx],3);			            
						Quest = (page-1)*15+i+1;
						idx =Search_Quest(subNode->subi4.ql,MNode->testi4.answers[i].ID);
                     	print_Question(subNode->subi4.ql.Q[idx],black);	
			            if(MNode->testi4.answers[Quest-1].TRALOI!='X') Tick_CTick(DA[MNode->testi4.answers[Quest-1].TRALOI-'A'],darkRed);
			            Tick_CTick(DA[subNode->subi4.ql.Q[idx].DapAn-'A'],darkGreen);
			            settextstyle(font_text,0,sizeL-1);
                    	out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,black);
                    	settextstyle(font_text,0,sizeM);
                    	if(Quest>1) out_text_xy(l_win/4-50,w_win/2+205,(char*)"CAU TRUOC",3,darkBlue);
						else out_text_xy(l_win/4-50,w_win/2+205,(char*)"CAU TRUOC",3,3);
						if(Quest<MNode->testi4.n) out_text_xy(l_win/4+370,w_win/2+205,(char*)"CAU SAU",3,darkBlue);
						else out_text_xy(l_win/4+370,w_win/2+205,(char*)"CAU SAU",3,3);
					} 
		    	}
	     	}
		    if(is_area(page_after,x,y)){
		    	if(page<nPage){
		    		page++;
		    		settextstyle(font_text,0,sizeL-1);
			        out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,3);
		    		settextstyle(font_text,0,sizeM);
                    out_text_xy(60,w_win-65,itoa(page,buff,decimal),3,black);
                    if(MNode->testi4.answers[Quest-1].TRALOI!='X') draw_CTick(DA[MNode->testi4.answers[Quest-1].TRALOI-'A']);
                    draw_CTick(DA[subNode->subi4.ql.Q[idx].DapAn-'A']);
					print_Question(subNode->subi4.ql.Q[idx],3);
					Quest = (page-1)*15+1;
                    idx = Search_Quest(subNode->subi4.ql,MNode->testi4.answers[Quest-1].ID);
                    print_Question(subNode->subi4.ql.Q[idx],black);
                    settextstyle(font_text,0,sizeL-1);
                    out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,black);
                    set_Quest_Table2(subNode->subi4.ql,Questions,page,nPage,Quest,MNode->testi4.n,nRow,MNode->testi4.answers);
			        if(MNode->testi4.answers[Quest-1].TRALOI!='X') Tick_CTick(DA[MNode->testi4.answers[Quest-1].TRALOI-'A'],darkRed);
			        Tick_CTick(DA[subNode->subi4.ql.Q[idx].DapAn-'A'],darkGreen);
				}
			}
			else if(is_area(page_before,x,y)){
				if(page>1){
					page--;
					settextstyle(font_text,0,sizeL-1);
			        out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,3);
					settextstyle(font_text,0,sizeM);
                    out_text_xy(60,w_win-65,itoa(page,buff,decimal),3,black);
                    if(MNode->testi4.answers[Quest-1].TRALOI!='X') draw_CTick(DA[MNode->testi4.answers[Quest-1].TRALOI-'A']);
                    draw_CTick(DA[subNode->subi4.ql.Q[idx].DapAn-'A']);
					print_Question(subNode->subi4.ql.Q[idx],3);
					Quest = (page-1)*15+1;
                    idx = Search_Quest(subNode->subi4.ql,MNode->testi4.answers[Quest-1].ID);
                    print_Question(subNode->subi4.ql.Q[idx],black);
                    settextstyle(font_text,0,sizeL-1);
                    out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,black);
                    set_Quest_Table2(subNode->subi4.ql,Questions,page,nPage,Quest,MNode->testi4.n,nRow,MNode->testi4.answers);
			        if(MNode->testi4.answers[Quest-1].TRALOI!='X') Tick_CTick(DA[MNode->testi4.answers[Quest-1].TRALOI-'A'],darkRed);
			        Tick_CTick(DA[subNode->subi4.ql.Q[idx].DapAn-'A'],darkGreen);
				}	
			}
			else if(is_area(Quest_after,x,y)){
				if(Quest<MNode->testi4.n){
					if(MNode->testi4.answers[Quest-1].TRALOI!='X') draw_CTick(DA[MNode->testi4.answers[Quest-1].TRALOI-'A']);	
					draw_CTick(DA[subNode->subi4.ql.Q[idx].DapAn-'A']);
					settextstyle(font_text,0,sizeL-1);
					out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,3);
				    print_Question(subNode->subi4.ql.Q[idx],3);
					Quest++;
					idx = Search_Quest(subNode->subi4.ql,MNode->testi4.answers[Quest-1].ID);
                    print_Question(subNode->subi4.ql.Q[idx],black);
					settextstyle(font_text,0,sizeL-1);
                    out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,black);
                    settextstyle(font_text,0,sizeM);
					if(Quest%15==1){
					    page++;
					    set_Quest_Table2(subNode->subi4.ql,Questions,page,nPage,Quest,MNode->testi4.n,nRow,MNode->testi4.answers);
                       	out_text_xy(60,w_win-65,itoa(page,buff,decimal),3,black);					    
					} 
					else {
						area = Questions[(Quest-2)%15].area;
			        	setcolor(white);
			        	rectangle(area.x,area.y,area.x+area.length,area.y+area.width);
			        	area = Questions[(Quest-1)%15].area;
			        	setcolor(darkBlue);
			        	rectangle(area.x,area.y,area.x+area.length,area.y+area.width);
					}
			        if(MNode->testi4.answers[Quest-1].TRALOI!='X') Tick_CTick(DA[MNode->testi4.answers[Quest-1].TRALOI-'A'],darkRed);
			        Tick_CTick(DA[subNode->subi4.ql.Q[idx].DapAn-'A'],darkGreen);	
					if(Quest==MNode->testi4.n) out_text_xy(l_win/4+370,w_win/2+205,(char*)"CAU SAU",3,3);
					if(Quest==2) out_text_xy(l_win/4-50,w_win/2+205,(char*)"CAU TRUOC",3,darkBlue);		    
				}
			}
			else if(is_area(Quest_before,x,y)){
				if(Quest>1){
					if(MNode->testi4.answers[Quest-1].TRALOI!='X') draw_CTick(DA[MNode->testi4.answers[Quest-1].TRALOI-'A']);	
					draw_CTick(DA[subNode->subi4.ql.Q[idx].DapAn-'A']);
					settextstyle(font_text,0,sizeL-1);
					out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,3);
					print_Question(subNode->subi4.ql.Q[idx],3);
					Quest--;
					idx = Search_Quest(subNode->subi4.ql,MNode->testi4.answers[Quest-1].ID);
                    print_Question(subNode->subi4.ql.Q[idx],black);
					settextstyle(font_text,0,sizeL-1);
                    out_text_xy(l_win/3+30,w_win/2+200,itoa(Quest,buff,decimal),3,black);
                    settextstyle(font_text,0,sizeM);
					if(Quest%15==0){
					    page--;
					    set_Quest_Table2(subNode->subi4.ql,Questions,page,nPage,Quest,MNode->testi4.n,nRow,MNode->testi4.answers);
                       	out_text_xy(60,w_win-65,itoa(page,buff,decimal),3,black);					    
					} 
					else {
						area = Questions[Quest%15].area;
			        	setcolor(white);
			        	rectangle(area.x,area.y,area.x+area.length,area.y+area.width);
			        	area = Questions[(Quest-1)%15].area;
			        	setcolor(darkBlue);
			        	rectangle(area.x,area.y,area.x+area.length,area.y+area.width);
					}
			        if(MNode->testi4.answers[Quest-1].TRALOI!='X') Tick_CTick(DA[MNode->testi4.answers[Quest-1].TRALOI-'A'],darkRed);
			        Tick_CTick(DA[subNode->subi4.ql.Q[idx].DapAn-'A'],darkGreen);
					if(Quest==1) out_text_xy(l_win/4-50,w_win/2+205,(char*)"CAU TRUOC",3,3);
					else if(Quest==MNode->testi4.n-1)	out_text_xy(l_win/4+370,w_win/2+205,(char*)"CAU SAU",3,darkBlue);	     
				}
			}
		}
	}
}

//GIAO DIEN DANG NHAP SINH VIEN
void student_interface(){
	setbkcolor(black);
	cleardevice();
	draw_circle(30,20,15,white);
	setcolor(black);
	circle(30,10,5);
	circle(30,20,15);
	draw_circle(30,10,5,grey);
	setfillstyle(1,grey);
	pieslice(30,28,0,180,13);
	rectangle(5,40,l_win-15,w_win-20);
	create_1_bar(l_win/100,w_win/14+40,l_win-34,w_win-113,white,3);
}
void student_menu(classList &CList,PTRSUB root, PTRS &SNode){//giao dien sinh vien
	int x, y,nMin, nQues;
    Class CLASS;
    subInfor subji4;
    PTRSUB subNode;
    student_interface();
    char i4[MAX_HO+MAX_TEN+MAX_MASV+20];
    HO_TEN_MASV(SNode->stui4,i4);
	out_text_xy(50,5,i4,3,black);
	BUTTON Menu[nStuMenu], exit;
	AREA buff;
	set_exit(exit,(char*)"DANG XUAT",l_win-25,5,black);
	int x_bar = l_win/100+1, hover=-1, choose =-1, j;
	for(int i=0; i<nStuMenu; i++){
		set_area(buff, x_bar,w_win/14, lengthStuMenu[i], 35);
		set_button(Menu[i],buff,studentMenu[i],sizeM, black, CENTER, white, darkWhite);
		draw_button(Menu[i]);
		x_bar +=lengthStuMenu[i]+2;
	}
	while(1){
		delay(1);
		if(ismouseclick(WM_MOUSEMOVE)){
			j = hover;
			getmouseclick(WM_MOUSEMOVE,x,y);	
			for(hover=0;hover<nStuMenu;hover++)
	         	if(is_area(Menu[hover].area,x,y)) break;
	        if(j!=-1&&hover!=j&&j!=nStuMenu) draw_button(Menu[j]); 	
	        if(hover!=j&&hover!=nStuMenu) highlight_button(Menu[hover],grey,white,white);
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for(int i=0;i<nStuMenu;i++)
	         	if(is_area(Menu[i].area,x,y)) choose=i;	
			while(choose!=-1){
				if(choose!=1&&choose!=0){
					create_1_bar(l_win/100+6,w_win/7,1204,527,3,3);
               		create_1_bar(l_win/100+857,w_win/7,5,527,white,white);
               	}	
				else create_1_bar(l_win/100+6,w_win/7,1204,527,3,3);
				delay(200);
				if(choose < 2){
					create_1_bar_text(Menu[choose].area.x,Menu[choose].area.y,Menu[choose].area.length,
			    	Menu[choose].area.width+7,white,white,Menu[choose].text,Menu[choose].sizechr,black,CENTER);	
				}
    			if (choose==0) Thi_TN(root,CList,subNode,subji4,Menu,nStuMenu,nQues,nMin,choose,SNode); 
		        else if(choose==1) mark_List2(SNode,root,subNode,Menu,nStuMenu,choose,STUDENT);
		        else if(choose==10) {
	    	    	choose = 0;
	    	    	Thi_TN_2(CList,root,subNode,SNode,Menu,nStuMenu,choose,nMin,nQues);
				}
				else if(choose==20){
					result(SNode,choose,nQues,STUDENT);
					for(int i=0;i<nStuMenu;i++)  if(i!=0) draw_button(Menu[i]);
				} 
				else if(choose==21){
					choose = 0;
					xem_KQ(root,SNode,subNode,Menu,nStuMenu,choose);
				}
				else if(choose==22){
					choose = 1;
					xem_KQ(root,SNode,subNode,Menu,nStuMenu,choose);
				}
				if(choose==-1){
	    	    	create_1_bar(l_win/100,w_win/14+40,l_win-34,w_win-113,white,3);
	    			draw_button(exit);
	  		        line(l_win-25-strlen(exit.text)*lth_sizeM,30,l_win-25,30);
				}
		    }
		    if(is_area(exit.area,x,y)) return;
		}
	}
}

//GIAO DIEN DANG NHAP GIANG VIEN
void lecturer_interface(){
	setbkcolor(black);
	cleardevice();
	draw_circle(30,20,15,white);
	setcolor(black);
	circle(30,10,5);
	circle(30,20,15);
	draw_circle(30,10,5,grey);
	setfillstyle(1,grey);
	pieslice(30,28,0,180,13);
	rectangle(5,40,l_win-15,w_win-20);
	create_1_bar(l_win/100,w_win/14+40,l_win-34,w_win-113,white,3);
}
void lecturer_menu(classList &CList, PTRSUB &root,int& offset, int& k, int& d){//giao dien giao vien
    int x, y, nMin, nQues;
    char subjID[MAX_MAMH+1];
    PTRC CLASS;
    PTRS SNode;
    PTRSUB subNode;
    subInfor subji4;
    lecturer_interface();
	out_text_xy(50,5,(char*)"GV",3,black);
	BUTTON Menu[nLecMenu], exit;
	AREA buff;
	set_exit(exit,(char*)"DANG XUAT",l_win-25,5,black);
	int x_bar = l_win/100+1, hover=-1, choose =-1, j;
	for(int i=0; i<nLecMenu; i++){
		set_area(buff, x_bar,w_win/14, lengthlecMenu[i], 35);
		set_button(Menu[i],buff,lecturerMenu[i],sizeM, black, CENTER, white, darkWhite);
		draw_button(Menu[i]);
		x_bar +=lengthlecMenu[i]+2;
	}
	while(1){
		delay(1);
		if(ismouseclick(WM_MOUSEMOVE)){
			j = hover;
			getmouseclick(WM_MOUSEMOVE,x,y);	
			for(hover=0;hover<nLecMenu;hover++)
	         	if(is_area(Menu[hover].area,x,y)) break;
	        if(j!=-1&&hover!=j&&j!=nLecMenu) draw_button(Menu[j]); 	
	        if(hover!=j&&hover!=nLecMenu) highlight_button(Menu[hover],grey,white,white);
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for(int i=0;i<nLecMenu;i++)
	         	if(is_area(Menu[i].area,x,y)) choose=i;	
			while(choose!=-1){
				if(choose==7){
					create_1_bar(l_win/100+6,w_win/7,1204,527,3,3);
					create_1_bar(l_win/2,w_win/7,5,527,white,white);
				}
				else if(choose!=3&&choose!=11&&choose!=12&&choose!=2){
					create_1_bar(l_win/100+6,w_win/7,1204,527,3,3);
               		create_1_bar(l_win/100+857,w_win/7,5,527,white,white);
				}
				else create_1_bar(l_win/100+6,w_win/7,1204,527,3,3);
				delay(200);
				if(choose < 4){
					create_1_bar_text(Menu[choose].area.x,Menu[choose].area.y,Menu[choose].area.length,
			    	Menu[choose].area.width+7,white,white,Menu[choose].text,Menu[choose].sizechr,black,CENTER);	
				}
    			if (choose==0) class_List(CList,CLASS, Menu,choose); 
		        else if(choose==1) subject_List(root,subNode, CList, Menu,choose,offset,k,d);
    		    else if(choose==2) Thi_TN(root,CList,subNode,subji4,Menu,nLecMenu,nQues,nMin,choose,NULL);
	    	    else if(choose==3) mark_List(CList,root,CLASS,SNode,subNode, Menu,choose);
	    	    else if(choose==6) {
	    	    	choose = 0;
	    	    	student_List(CList,CLASS, Menu,choose);
				}
				else if(choose==7){
					choose = 1;
					question_List(root,subNode,Menu,choose);
				}
				else if(choose==10){
					choose = 2;
					SNode = NULL; 
					Thi_TN_2(CList,root,subNode,SNode,Menu,nLecMenu,choose,nMin,nQues);
				}
				else if(choose==11){
					nMin = choose;
					choose =3;
					mark_List2(SNode,root,subNode,Menu,nLecMenu,choose,LECTURER);
				}
				else if(choose==12){
					nMin = choose;
					choose =3;
					mark_List1(CLASS,SNode,subNode,Menu,choose);
				}
				else if(choose==20){
					result(SNode,choose,nQues,LECTURER);
					for(int i=0;i<nLecMenu;i++) 
					    if(i!=2) draw_button(Menu[i]);
				} 
	            else if(choose==21){
					choose = 2;
					strcpy(SNode->stui4.MASV,"GV");
					xem_KQ(root,SNode,subNode,Menu,nLecMenu,choose);
					free_SList(SNode);
				}
				else if(choose==22){
					choose = 3;
					xem_KQ(root,SNode,subNode,Menu,nLecMenu,choose);
					if(choose==100) choose = nMin;
				}
				if(choose==-1){
	    	    	create_1_bar(l_win/100,w_win/14+40,l_win-34,w_win-113,white,3);
	    			draw_button(exit);
	  		        line(l_win-25-strlen(exit.text)*lth_sizeM,30,l_win-25,30);
			    }
		    }
		    if(is_area(exit.area,x,y)) return;
		}
	}
}

//GIAO DIEN DANG NHAP
PTRS input_username(classList &CList, char* username, char* password,int &cursor_pos_UN, int &cursor_pos_PW, BUTTON& exit, int& stop){
		int n = T_cursor+1, x, y;
		AREA bar_password, bar_username;
		set_area(bar_username,l_win/2-50,w_win/3+68,250,30);
		set_area(bar_password,l_win/2-50,w_win/3+138,250,30);
    	PTRS SFirst;
		while(1){
			delay(1);
			print_cursor(l_win/2-45+cursor_pos_UN*lth_sizeM,w_win/3+73,n);
			if(kbhit()){
				out_text_xy(l_win/2-45,w_win/3+70, username,white,white);
				out_text_xy(l_win/2-50,w_win/3+100,(char*)"                            ",3,3);
				int key = Key();
				if(key == key_BS){
					if(cursor_pos_UN > 0){
		    			strcpy(username + cursor_pos_UN-1, username+ cursor_pos_UN);
		    			cursor_pos_UN--;
		    	    }
				}
				else if(key==key_SP){
					settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/2-50,w_win/3+100,(char*)"Tai khoan khong chua khoang trang",3,red);
				}
				else if(key==key_Left) {
					if(cursor_pos_UN>0) cursor_pos_UN--;
				} 
				else if(key==key_Right){
					if(cursor_pos_UN<strlen(username)) cursor_pos_UN++;
				} 
				else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'){	
					if(strlen(username)==MAX_MASV){
	                    settextstyle(font_text,0,sizeS-1);					
					    out_text_xy(l_win/2-50,w_win/3+100,(char*)"Tai khoan khong qua 15 ki tu",3,red);	
						}           
					else {
						insert_chr_to_str(username,key,cursor_pos_UN);
						cursor_pos_UN++;
					}
				}
				else if(key==key_Enter||key==key_Down){
					if(strlen(username)==0){
						settextstyle(font_text,0,sizeS-1);
						out_text_xy(l_win/2-50,w_win/3+100,(char*)"Chua nhap tai khoan",3,red);
					}
					else if((SFirst = search_student_all_class_MSSV(CList,username))==NULL&&stricmp(username,"GV")!=0) {
						settextstyle(font_text,0,sizeS-1);
						out_text_xy(l_win/2-50,w_win/3+100,(char*)"Sai ten tai khoan",3,red);
					}
					else{
						upper_str(username);
						out_text_xy(l_win/2-45,w_win/3+70,username,white,black);
						cursor_pos_PW = strlen(password);
						if(stricmp(username,"GV")==0) return NULL;
						return SFirst;
					} 
				}
				else if(key>key_SP&&key<127){
					settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/2-50,w_win/3+100,(char*)"Tai khoan khong chua ki tu dac biet",3,red);
				}
			settextstyle(font_text,0,sizeM);
			out_text_xy(l_win/2-45,w_win/3+70,username,white,black);
		    n=T_cursor+1; 
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			out_text_xy(l_win/2-45,w_win/3+70,username,white,white);
			out_text_xy(l_win/2-50,w_win/3+100,(char*)"                            ",3,3);
		    getmouseclick(WM_LBUTTONDOWN,x,y);
		    if(is_area(exit.area,x,y)){
                stop = 1;
                return NULL;
			}
		    if(is_area(bar_password,x,y)){
		    	if(strlen(username)==0){
					settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/2-50,w_win/3+100,(char*)"Chua nhap tai khoan",3,red);
				}
				else if((SFirst = search_student_all_class_MSSV(CList,username))==NULL&&stricmp(username,"GV")!=0) {
					settextstyle(font_text,0,sizeS-1);
					out_text_xy(l_win/2-50,w_win/3+100,(char*)"Sai ten tai khoan",3,red);
				}
				else{
					upper_str(username);
					out_text_xy(l_win/2-45,w_win/3+70,username,white,black);
					cursor_pos_PW = (x-(l_win/2-52))/lth_sizeM;
					if(cursor_pos_PW > strlen(password)) cursor_pos_PW = strlen(password); 
					if(stricmp(username,"GV")==0) return NULL;
					return SFirst;
				} 
			}
			else if(is_area(bar_username,x,y)){
				cursor_pos_UN =(x-(l_win/2-52))/lth_sizeM;
				if(cursor_pos_UN > strlen(username)) cursor_pos_UN = strlen(username);
			}
			settextstyle(font_text,0,sizeM);
		   	out_text_xy(l_win/2-45,w_win/3+70,username,white,black);
	        n = T_cursor+1; 
		}	
	}
}
int input_password(PTRS SNode, char* username, char *password, int &cursor_pos_UN,int &cursor_pos_PW,BUTTON& exit, int& stop){
	int n = T_cursor+1, x, y;
	AREA bar_username, bar_password;
	set_area(bar_username,l_win/2-50,w_win/3+68,250,30);
	set_area(bar_password,l_win/2-50,w_win/3+138,250,30);
    char security[MAX_PASS+1]={0};
    for(int i=0; i<strlen(password); i++) security[i] = '*';
	while(1){
   		delay(1);
		print_cursor(l_win/2-45+cursor_pos_PW*lth_sizeM,w_win/3+143,n);
		if(kbhit()){
			out_text_xy(l_win/2-45,w_win/3+141,password,white,white);
			out_text_xy(l_win/2-50,w_win/3+170,(char*)"                           ",3,3);
			int key = Key();
			if(key==key_BS){
				if(cursor_pos_PW>0){
	    			strcpy(password+cursor_pos_PW-1,password+cursor_pos_PW);
	    			strcpy(security+cursor_pos_PW-1,security+cursor_pos_PW);
	    			cursor_pos_PW--;
	    	    }
			}
			else if(key==key_SP){
				settextstyle(font_text,0,sizeS-1);
			   	out_text_xy(l_win/2-50,w_win/3+170,(char*)"Mat khau khong chua khoang trang",3,red);
			}
			else if(key==key_Left) {
				if(cursor_pos_PW>0) cursor_pos_PW--;
			} 
			else if(key==key_Right){
				if(cursor_pos_PW<strlen(password)) cursor_pos_PW++;
			} 
			else if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key>='0'&&key<='9'){
		    	if(strlen(password)==MAX_PASS){
                    settextstyle(font_text,0,sizeS-1);					
				    out_text_xy(l_win/2-50,w_win/3+170,(char*)"Mat khau khong qua 10 ki tu",3,red);	
                }
				else{
					insert_chr_to_str(password,key,cursor_pos_PW);
					insert_chr_to_str(security,'*',cursor_pos_PW);
					cursor_pos_PW ++;
				}		
			}
			else if(key==key_Enter){
				out_text_xy(l_win/2-45,w_win/3+141,security,white,black);
				n=T_cursor+1; 
				if(strlen(password)==0){
					settextstyle(font_text,0,sizeS-1);
			    	out_text_xy(l_win/2-50,w_win/3+170,(char*)"Chua nhap mat khau",3,red);
				}
				else {
			        settextstyle(font_text,0,sizeS-1);
				    out_text_xy(l_win/2-50,w_win/3+170,(char*)"Sai mat khau",3,red);
			    }
			}
			else if(key==key_Up){
				out_text_xy(l_win/2-45,w_win/3+141,security,white,black);
				draw_cursor(l_win/2-45+cursor_pos_PW*lth_sizeM,w_win/3+143,white); 
				cursor_pos_UN = strlen(username);
				return 0;
			}
			else if(key>key_SP&&key<127){
				settextstyle(font_text,0,sizeS-1);
				out_text_xy(l_win/2-50,w_win/3+170,(char*)"Mat khau khong chua ki tu dac biet",3,red);
			}
			settextstyle(font_text,0,sizeM);
			out_text_xy(l_win/2-45,w_win/3+141,security,white,black);
		    n=T_cursor+1;
	    }
	    if(ismouseclick(WM_LBUTTONDOWN)){
			out_text_xy(l_win/2-45,w_win/3+141,password,white,white);
			out_text_xy(l_win/2-50,w_win/3+170,(char*)"                         ",3,3);
		    getmouseclick(WM_LBUTTONDOWN,x,y);
		    if(is_area(exit.area,x,y)){
                stop = 1;
                return -1;
			}
		    else if(is_area(bar_username,x,y)){
		    	out_text_xy(l_win/2-45,w_win/3+141,security,white,black);
				draw_cursor(l_win/2-45+cursor_pos_PW*lth_sizeM,w_win/3+143,white);
				cursor_pos_UN = (x-(l_win/2-52))/lth_sizeM; 
				if(cursor_pos_UN>strlen(username)) cursor_pos_UN = strlen(username);
				return 0;
			}
			else if(is_area(bar_password,x,y)){
				cursor_pos_PW =(x-(l_win/2-52))/lth_sizeM;
				if(cursor_pos_PW>strlen(password)) cursor_pos_PW = strlen(password);
			}
			settextstyle(font_text,0,sizeM);
			out_text_xy(l_win/2-45,w_win/3+141,security,white,black);
		    n=T_cursor+1;
		}
	    if(check_password(SNode,password)||stricmp(password,"GV")==0&&SNode==NULL) {
		    delay(100);
	    	return 1;
	    }
	} 
}
int login(classList &CList, PTRS &SNode, int& stop){
	login_interface();
	BUTTON exit;
    set_exit(exit,(char*)"THOAT",l_win-25,5,black);
	char username[MAX_MASV+1]={0};
	char password[MAX_PASS+1]={0};
	int cursor_pos_UN = 0, cursor_pos_PW = 0;
	while(1){ 
	    SNode = input_username(CList, username, password, cursor_pos_UN, cursor_pos_PW,exit,stop);
	    if(stop) return -1;
        if(input_password(SNode, username,password, cursor_pos_UN, cursor_pos_PW,exit,stop)) break;
        if(stop) return -1;
    }
    if(stricmp(username,"GV")==0&&stricmp(password,"GV")==0) return LECTURER;
	return STUDENT;
}

int main(){ 
	int k=0,d=1;
	int offset;
    initwindow(l_win,w_win);
    classList CList;
    PTRSUB root;
    
	init_CList(CList);
    Init_SubjList(root);
    
	ifstream filein;
	filein.open("dulieu.txt",ios::binary);
   	load_CList(filein,CList);
   	filein.close();

    
    ifstream filein2;
	filein2.open("DSCH.txt",ios::in);
    load_SubList(filein2,root,offset,k,d);
    filein2.close();
    
    PTRS SNode;
    int stop = 0;
    while(1){
        int user = login(CList,SNode,stop);
        if(stop) break;
        cleardevice();
        if(user == LECTURER) lecturer_menu(CList,root,offset,k,d);
        else student_menu(CList,root,SNode);
        while(kbhit()) getch();
    }  
    ofstream fileout;
	fileout.open("dulieu.txt",ios::binary);
	save_CList(fileout,CList);
	fileout.close();
	
	ofstream fileout2;
	fileout2.open("DSCH.txt",ios::out);
	save_SubjList(fileout2,root);
	fileout2.close();
	
	free_CList(CList);
	Free_Subj_List(root);
    return 1;

} 

