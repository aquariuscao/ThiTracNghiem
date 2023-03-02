#include "graphic.h"

int left(int x){
	return x+10;
}
int center(int x, int length, int lentext, int size){
	return x + (length - (size-sizeM+lth_sizeM)*lentext)/2;
}
void set_exit(BUTTON &exit,char* text,int x,int y,int color){
	AREA buff;
	set_area(buff,x-strlen(text)*lth_sizeM,y,strlen(text)*lth_sizeM,30);
	set_button(exit,buff,text,sizeM,color,CENTER,3,3);
	draw_button(exit);
	line(x-strlen(text)*lth_sizeM,y+27,x,y+27);
}
void out_text_xy( int x, int y, char* text, int bk_color, int text_color){
	setcolor( text_color);
	setbkcolor(bk_color);
	outtextxy( x, y, text);
}
void print_text_bar(int x,int y, char* text,int n, int bk_color,int text_color){
    settextstyle(font_text,0,sizeS);
	if(strlen(text)<n) {
		out_text_xy(x,y,text,bk_color,text_color);
	}
	else{
		char ch = text[n];
		text[n]='\0';
		out_text_xy(x,y,text,bk_color,text_color);
 		text[n] = ch;	
	}
}
void out_text_bar(int x,int y, char* text,int n, int bk_color,int text_color,int size){
	settextstyle(font_text,0,size);
	if(strlen(text)<n) {
		out_text_xy(x,y,text,bk_color,text_color);
	}
	else{
		char ch = text[n];
		text[n]='\0';
		out_text_xy(x,y,text,bk_color,text_color);
 		text[n] = ch;	
	}
}
void create_1_bar( int x, int y, int length, int width, int bk_color, int bdr_color){
	setfillstyle( 1, bk_color);
	bar( x, y, x+length, y+width);
   	setcolor( bdr_color);
	rectangle( x, y, x+length, y+width);
}
void create_1_bar_text( int x, int y, int length, int width, int bk_color, int bdr_color, char text[], int sizechr,int text_color,int align) {
	settextstyle(font_text,0,sizechr);
    create_1_bar( x, y, length, width, bk_color, bdr_color);
	if(align==CENTER) out_text_xy(center(x,length,strlen(text),sizechr), y+3, text, bk_color, text_color);      
	else out_text_bar(left(x), y+3, text, (length-20)/(lth_sizeM-2*(sizeM-sizechr)), bk_color, text_color,sizechr);                  	
}
void create_1_bar_text2( int x, int y, int length, int width, int bk_color, int bdr_color, char text[], int sizechr,int text_color,int align) {
	settextstyle(font_text,0,sizechr);
   	setcolor( bdr_color);
	rectangle( x, y, x+length, y+width);
	if(align==CENTER) out_text_xy(center(x,length,strlen(text),sizechr), y+3, text, bk_color, text_color);                
	else out_text_bar(left(x), y+3, text, (length-20)/(lth_sizeM-2*(sizeM-sizechr)), bk_color, text_color,sizechr);               	
}
void create_1_row_of_table( int x, int y, int lengths[], int width, int nColumn,int bk_color,int bdr_color){
	for(int column=0; column<nColumn; column++){ 
    	create_1_bar(x ,y, lengths[column], width, bk_color, bdr_color);
    	x += lengths[column];
	}
}
void create_1_row_of_table_text(int x, int y, int lengths[], int width, int nColumn,int bk_color,int bdr_color,char titles[][max_lentitle],int sizechr,int text_color){
    for(int column=0; column<nColumn; column++){ 
    	create_1_bar_text(x ,y, lengths[column], width, bk_color, bdr_color, titles[column],sizechr, text_color, CENTER);
    	x += lengths[column];
    }
}
void create_table( int x, int y, int lengths[], int width, int nColumn, int nRow, char titles[][max_lentitle],int sizechr,int text_color,int color_row1, int bdr_color){
    char buff[ max_tt+1];
	for( int row=0; row<nRow; row++){
		if(row==0)	create_1_row_of_table_text( x, y+width*row, lengths, width, nColumn, color_row1, bdr_color, titles,sizechr, text_color);              								   	
		else create_1_row_of_table( x, y+width*row, lengths, width, nColumn, white, bdr_color);   
    }
}
void draw_circle(int x,int y,int R,int color){
	setcolor(color);
	circle(x,y,R);
	setfillstyle(1,color);
    floodfill(x,y,color);
}
void append_tt_stime(char* str_time,int tt){
	char buff[max_tt+1];
	if(tt<10) strcat( str_time, "0");
	strcat( str_time, itoa( tt, buff, decimal));
}
void create_solid_polygon(int x_y[],int n_xy,int bk_color){
	setfillstyle(1,bk_color);
	fillpoly(n_xy,x_y);
}
void create_1_bar_opt( int x, int y, int length, int width, int bk_color,int bdr_color,int text_color){
	create_1_bar( x, y, length, width, bk_color, bdr_color);
	int _x = x + length;
	create_1_bar( _x, y, width, len_optbar, bk_color, bdr_color);
	int x_y[]={_x+5,y+8,_x+25,y+8,_x+15,y+23,_x+5,y+8};
	create_solid_polygon( x_y, 4, text_color);
}
void set_time(int seconds,int& hh,int& mm,int& ss){
	hh = seconds/3600;
	mm = (seconds%3600)/60;
	ss = (seconds%3600)%60;
}
void print_time( int x, int y, int seconds){
    int hh, mm, ss;
	set_time(seconds,hh,mm,ss);
	char str_time[max_str_time+1]; 
	append_tt_stime(str_time,hh);
	strcat( str_time, ":");
	append_tt_stime(str_time,mm);
	strcat( str_time, ":");
	append_tt_stime(str_time,ss);
	if(seconds<31) setcolor(red);
	else setcolor(black);
	settextstyle(font_text,0,sizeM);
	setbkcolor(white);
	outtextxy( x, y, str_time);
}
void login_interface(){//giao dien dang nhap
	setbkcolor(3);
	cleardevice();
	settextstyle(font_text,0,sizeL+3);
	out_text_xy(l_win/5+20,w_win/14,(char*)"THI TRAC NGHIEM",3,red);
	rectangle(l_win/2-350,w_win/4+100,l_win/2+350,w_win/4+300);
	settextstyle(font_text,0,sizeM+2);
	outtextxy(l_win/2-80,w_win/3-20,(const char*)"DANG NHAP");
	settextstyle(font_text,0,sizeM);
	outtextxy(l_win/3,w_win/3+70,(const char*)"TAI KHOAN:");
	outtextxy(l_win/3,w_win/3+140,(const char*)"MAT KHAU:");
	create_1_bar(l_win/2-50,w_win/3+68,250,30,white,white);
	create_1_bar(l_win/2-50,w_win/3+138,250,30,white,white);
}
void draw_cursor(int x,int y,int color){
	setcolor(color);
	line(x,y,x,y+20);
}
void print_cursor(int x,int y, int &n){
	n--;
	if(n==T_cursor) draw_cursor(x, y,black);
	else if(n==T_cursor/2) draw_cursor(x,y,white);
	else if(n==0)  n=T_cursor+1;
}

void set_area(AREA &area,int x1,int y1,int lth,int wth){
	area.x=x1;
	area.y=y1;
	area.length=lth;
	area.width=wth;
}
void set_button(BUTTON &BT, AREA &area, char* text,int sizechr,int text_color, int align, int bdr_color, int bk_color){
	BT.area = area;
	strncpy(BT.text,text,MAX_TEXT);
	BT.text[MAX_TEXT] = '\0';
	BT.sizechr = sizechr;
	BT.text_color = text_color;
	BT.align = align;
	BT.bdr_color = bdr_color;
	BT.bk_color = bk_color;
}
void draw_button(BUTTON &BT){
	create_1_bar_text(BT.area.x, BT.area.y, BT.area.length, BT.area.width, BT.bk_color, BT.bdr_color,BT.text,BT.sizechr,BT.text_color,BT.align);
}
void draw_button2(BUTTON &BT){
	create_1_bar_text2(BT.area.x, BT.area.y, BT.area.length, BT.area.width, BT.bk_color, BT.bdr_color,BT.text,BT.sizechr,BT.text_color,BT.align);
}
bool is_area(AREA &area,int x,int y){
	return (area.x<=x)&&(x<=area.x+area.length)&&(area.y<=y)&&(y<=area.y+area.width);
}
void highlight_button(BUTTON &BT, int bk_color, int bdr_color, int text_color){
	create_1_bar_text(BT.area.x, BT.area.y, BT.area.length, BT.area.width, bk_color, bdr_color,BT.text,BT.sizechr,text_color,BT.align);	
}
void highlight_button2(BUTTON &BT, int bk_color, int bdr_color, int text_color){
	create_1_bar_text2(BT.area.x, BT.area.y, BT.area.length, BT.area.width, bk_color, bdr_color,BT.text,BT.sizechr,text_color,BT.align);	
}
void delete_button(BUTTON &BT, int color){
	create_1_bar(BT.area.x,BT.area.y,BT.area.length,BT.area.width,color,color);
}
void set_rowTable(rowTable &rowTB, BUTTON* buttons, int nButton){
	for(int i=0;i<nButton;i++) rowTB.buttons[i] = buttons[i];
	rowTB.nbutton = nButton;
}
bool is_rowTable(rowTable &rowTable,int x,int y){
	AREA areaFirst = rowTable.buttons[0].area;
	AREA areaLast = rowTable.buttons[rowTable.nbutton-1].area;
	return areaFirst.x<x&&areaFirst.y<y&&(areaLast.x+areaLast.length)>x&&(areaLast.y+areaLast.width)>y;
}
void draw_rowTable(rowTable &rowTable){
	for(int i=0;i<rowTable.nbutton;i++) draw_button(rowTable.buttons[i]);
}
void draw_rowTable2(rowTable &rowTable){
	for(int i=0;i<rowTable.nbutton;i++) draw_button2(rowTable.buttons[i]);
}
void highlight_rowTable(rowTable &rowTable,int bk_color, int bdr_color, int text_color){
	for(int i=0;i<rowTable.nbutton;i++) highlight_button(rowTable.buttons[i],bk_color,bdr_color,text_color);
}
void highlight_rowTable2(rowTable &rowTable,int bk_color, int bdr_color, int text_color){
    for(int i=0;i<rowTable.nbutton;i++) highlight_button2(rowTable.buttons[i],bk_color,bdr_color,text_color);
}
void draw_CTick(CTick& Tick){
	draw_circle(Tick.x,Tick.y,Tick.R,white);
}
void Tick_CTick(CTick& Tick,int color){
	draw_circle(Tick.x,Tick.y,Tick.R-3,color);
}
void delete_CTick(CTick& Tick,int color){
	draw_circle(Tick.x,Tick.y,Tick.R,color);
}
void set_CTick(CTick& Tick,int x,int y,int R){
	Tick.x=x;
	Tick.y=y;
	Tick.R=R;
}
bool is_area_CTick(CTick& Tick,int x,int y){
	return (Tick.x-Tick.R<=x)&&(Tick.y-Tick.R<=y)&&(Tick.x+Tick.R>=x)&&(Tick.y+Tick.R>=y);
}
void draw_button_opt(BUTTON &BT){
	create_1_bar_opt(BT.area.x, BT.area.y, BT.area.length, BT.area.width, BT.bk_color, BT.bdr_color,grey);
	settextstyle(font_text,0,BT.sizechr);
    out_text_xy(BT.area.x+7, BT.area.y+3, BT.text, BT.bk_color, BT.text_color);   
}
void highlight_button_opt(BUTTON &BT,int bk_color,int bdr_color,int text_color){
	create_1_bar_opt(BT.area.x, BT.area.y, BT.area.length, BT.area.width, bk_color, bdr_color,text_color);
	settextstyle(font_text,0,BT.sizechr);
    out_text_xy(BT.area.x+10, BT.area.y+3, BT.text, bk_color, text_color);  
}
bool is_area_opt(BUTTON& BT,int x,int y){
	return BT.area.x+BT.area.length<=x&&BT.area.x+BT.area.length+30>=x&&BT.area.y<=y&&BT.area.y+BT.area.width>=y;
}
void set_buttons_markList(BUTTON& exit,BUTTON& LOC,BUTTON& ML,BUTTON& MMH,BUTTON& XEM,BUTTON& LOC2,	BUTTON& page_after,BUTTON& page_before){
	AREA area;
	char buff[10];
	set_exit(exit,(char*)"VE TRANG DAU",l_win-25,5,black);
	set_area(area,300,w_win/4-47,150,30);
	set_button(LOC,area,(char*)"MON HOC",sizeM,black,LEFT,grey,white);
	draw_button_opt(LOC);
	set_area(area,300,w_win/4-15,180,30);
	set_button(LOC2,area,(char*)"SINH VIEN",sizeM,black,LEFT,white,white);
	set_area(area,200,w_win/4+60,400,30);
	set_button(ML,area,(char*)"",sizeS,darkRed,LEFT,white,white);
	draw_button_opt(ML);
	set_area(area,740,w_win/4+60,400,30);
	set_button(MMH,area,(char*)"",sizeS,darkRed,LEFT,white,white);
	draw_button_opt(MMH);
	set_area(area,650,w_win/4-47,150,30);
	set_button(XEM,area,(char*)"XEM DIEM",sizeM,black,CENTER,white,darkWhite);
	highlight_button(XEM,darkWhite,white,white);
	set_area(area,-1,-1,0,0);
	set_button(page_after,area,(char*)"->",sizeM,darkRed,CENTER,white,white);
	set_button(page_before,area,(char*)"<-",sizeM,darkRed,CENTER,white,white);
}
void set_buttons_classList(BUTTON& exit,int page,int nRow,BUTTON& pageA, BUTTON& pageB,int nPageTable, BUTTON& bar_search,BUTTON& clear, 
AREA &classID, AREA &className,BUTTON& THEM, BUTTON &LUU,BUTTON& XOA,BUTTON& subClear,AREA& pageArea, AREA* DSSV){
	AREA area;
	char buff[10];
    set_area(classID,l_win/2+375,w_win/3-12,170,30);
	set_area(className,l_win/2+270,w_win/3+80,310,30);
	set_area(pageArea,l_win/4+50,w_win-70,100,30);
	set_exit(exit,(char*)"VE TRANG DAU",l_win-25,5,black);
	set_area(area,l_win/2-50,w_win-70,14.8*strlen("TRANG SAU"),30);
	set_button(pageA,area,(char*)"TRANG SAU",sizeM,black,CENTER,3,3);
	set_area(area,l_win/7,w_win-70,14*strlen("TRANG TRUOC"),30);
	set_button(pageB,area,(char*)"TRANG TRUOC",sizeM,black,CENTER,3,3);
	set_area(area, l_win/16+strlen("TIM KIEM:")*lth_sizeM+7,w_win/4-20,500,30);
	set_button(bar_search,area,(char*)"Nhap tu khoa de tim kiem",sizeM-1,black,LEFT,white,white);
	set_area(area, l_win/16+640,w_win/4-20,75,30);
	set_button(clear,area,(char*)"CLEAR",sizeM,black,CENTER,white,darkWhite);
	set_area(area,l_win/2+372,w_win/3+145,(strlen("THEM")+1)*lth_sizeM,30);
	set_button(THEM,area,(char*)"THEM",sizeM,black,CENTER,white,darkWhite);
	set_area(area,l_win/2+453,w_win/3+145,(strlen("LUU")+1)*lth_sizeM,30);
    set_button(LUU,area,(char*)"SUA",sizeM,black,CENTER,white,darkWhite);
    set_area(area,l_win/2+520,w_win/3+145,(strlen("XOA")+1)*lth_sizeM,30);
    set_button(XOA,area,(char*)"XOA",sizeM,black,CENTER,white,darkWhite);
    set_area(area,l_win/2+277,w_win/3+145,(strlen("CLEAR")+1)*lth_sizeM,30);
    set_button(subClear,area,(char*)"CLEAR",sizeM,black,CENTER,white,darkWhite);
    for(int i=0;i<10;i++) set_area(DSSV[i],l_win/16+645,w_win/3+60+30*i,strlen("DSSV")*(lth_sizeM-2),20);
	draw_button(bar_search);
	draw_button(clear);
	draw_button(THEM);
	draw_button(subClear);
	highlight_button(XOA,darkWhite,white,white);
	highlight_button(LUU,darkWhite,white,white);	
}
void set_buttons_StuList(BUTTON& exit,int page,int nRow,BUTTON& pageA, BUTTON& pageB,int nPageTable, BUTTON& bar_search,BUTTON& clear, 
AREA& studentID, AREA &LName, AREA &FName,AREA& password,BUTTON& THEM, BUTTON &LUU,BUTTON& XOA,BUTTON& subClear,AREA& pageArea,CTick& male,CTick& female, BUTTON& Return){
	AREA area;
	char buff[10];
    set_area(studentID,l_win/2+360,w_win/3-42,170,30);
	set_area(LName,l_win/2+270,w_win/3+48,200,30);
	set_area(FName,l_win/2+480,w_win/3+48,100,30);
	set_area(password,l_win/2+400,w_win/3+168,170,30);
	set_area(pageArea,l_win/4+50,w_win-70,100,30);
	set_exit(exit,(char*)"VE TRANG DAU",l_win-25,5,black);
	set_area(area,l_win/2-50,w_win-70,14.8*strlen("TRANG SAU"),30);
	set_button(pageA,area,(char*)"TRANG SAU",sizeM,black,CENTER,3,3);
	set_area(area,l_win/7,w_win-70,14*strlen("TRANG TRUOC"),30);
	set_button(pageB,area,(char*)"TRANG TRUOC",sizeM,black,CENTER,3,3);
	set_area(area, l_win/16+strlen("TIM KIEM:")*lth_sizeM+7,w_win/4-20,500,30);
	set_button(bar_search,area,(char*)"Nhap tu khoa de tim kiem",sizeM-1,black,LEFT,white,white);
	set_area(area, l_win/16+640,w_win/4-20,75,30);
	set_button(clear,area,(char*)"CLEAR",sizeM,black,CENTER,white,darkWhite);
	set_area(area,l_win/2+372,w_win/3+230,(strlen("THEM")+1)*lth_sizeM,30);
	set_button(THEM,area,(char*)"THEM",sizeM,black,CENTER,white,darkWhite);
	set_area(area,l_win/2+453,w_win/3+230,(strlen("LUU")+1)*lth_sizeM,30);
    set_button(LUU,area,(char*)"SUA",sizeM,black,CENTER,white,darkWhite);
    set_area(area,l_win/2+520,w_win/3+230,(strlen("XOA")+1)*lth_sizeM,30);
    set_button(XOA,area,(char*)"XOA",sizeM,black,CENTER,white,darkWhite);
    set_exit(Return,(char*)"QUAY LAI",l_win/2+230,w_win/7+10,darkRed);
    set_area(area,l_win/2+277,w_win/3+230,(strlen("CLEAR")+1)*lth_sizeM,30);
    set_button(subClear,area,(char*)"CLEAR",sizeM,black,CENTER,white,darkWhite);
    set_CTick(male,l_win/2+380,w_win/3+125,8);
    set_CTick(female,l_win/2+480,w_win/3+125,8);
    draw_CTick(male);
    draw_CTick(female);
	draw_button(bar_search);
	draw_button(clear);
	draw_button(THEM);
	draw_button(subClear);
	highlight_button(XOA,darkWhite,white,white);
	highlight_button(LUU,darkWhite,white,white);	
}
void set_buttons_markList1(BUTTON& exit,int page,int nRow,BUTTON& pageA, BUTTON& pageB,int nPageTable, BUTTON& bar_search,BUTTON& clear, AREA& pageArea,BUTTON& Return,AREA CTBT[]){
	AREA area;
	char buff[10];
	set_area(pageArea,l_win/4+200,w_win-70,100,30);
	set_exit(exit,(char*)"VE TRANG DAU",l_win-25,5,black);
	set_area(area,l_win/2+100,w_win-70,14.8*strlen("TRANG SAU"),30);
	set_button(pageA,area,(char*)"TRANG SAU",sizeM,black,CENTER,3,3);
	set_area(area,l_win/7+150,w_win-70,14*strlen("TRANG TRUOC"),30);
	set_button(pageB,area,(char*)"TRANG TRUOC",sizeM,black,CENTER,3,3);
	set_area(area, l_win/16+150+strlen("TIM KIEM:")*lth_sizeM+7,w_win/4-20,500,30);
	set_button(bar_search,area,(char*)"Nhap tu khoa de tim kiem",sizeM-1,black,LEFT,white,white);
	set_area(area, l_win/16+790,w_win/4-20,75,30);
	set_button(clear,area,(char*)"CLEAR",sizeM,black,CENTER,white,darkWhite);
	set_exit(Return,(char*)"QUAY LAI",l_win-50,100,darkRed);
	for(int i=0;i<10;i++) set_area(CTBT[i],l_win/16+859,w_win/3+60+30*i,strlen("CTBT")*(lth_sizeM-2),20);
	draw_button(bar_search);
	draw_button(clear);
}
void set_buttons_markList2(BUTTON& exit,int page,int nRow,BUTTON& pageA, BUTTON& pageB,int nPageTable, BUTTON& bar_search,BUTTON& clear, AREA& pageArea, BUTTON& Return, AREA CTBT[], int user){
	AREA area;
	char buff[10];
	set_area(pageArea,l_win/4+200,w_win-70,100,30);
	set_exit(exit,(char*)"VE TRANG DAU",l_win-25,5,black);
	set_area(area,l_win/2+100,w_win-70,14.8*strlen("TRANG SAU"),30);
	set_button(pageA,area,(char*)"TRANG SAU",sizeM,black,CENTER,3,3);
	set_area(area,l_win/7+150,w_win-70,14*strlen("TRANG TRUOC"),30);
	set_button(pageB,area,(char*)"TRANG TRUOC",sizeM,black,CENTER,3,3);
	set_area(area, l_win/16+150+strlen("TIM KIEM:")*lth_sizeM+7,w_win/4-20,500,30);
	set_button(bar_search,area,(char*)"Nhap tu khoa de tim kiem",sizeM-1,black,LEFT,white,white);
	set_area(area, l_win/16+790,w_win/4-20,75,30);
	set_button(clear,area,(char*)"CLEAR",sizeM,black,CENTER,white,darkWhite);
	if(user==LECTURER) set_exit(Return,(char*)"QUAY LAI",l_win-50,100,darkRed);
	for(int i=0;i<10;i++) set_area(CTBT[i],l_win/16+849,w_win/3+60+30*i,strlen("CTBT")*(lth_sizeM-2),20);
	draw_button(bar_search);
	draw_button(clear);
}
void set_hover_CList(BUTTON* Menu,rowTable* ROWTBs,int &hover,int& j,int tt,int x,int y,int nRow,BUTTON& clear,BUTTON& LUU,BUTTON& subClear,BUTTON& THEM,BUTTON& XOA){
	j = hover;	
	for(hover=0;hover<nLecMenu;hover++){
		if(hover==tt) continue;
		if(is_area(Menu[hover].area,x,y)) break;
	}
	if(hover!=nLecMenu) return;
	for(hover = 100; hover<100+nRow;hover++) 
   	    if(is_rowTable(ROWTBs[hover-100],x,y)) break;
   	if(is_area(clear.area,x,y)) hover = 11;
	else if(is_area(subClear.area,x,y)) hover=12;
	else if(is_area(THEM.area,x,y)) hover=13;
	else if(is_area(XOA.area,x,y)) hover =14;   
   	else if(is_area(LUU.area,x,y)) hover=15; 
}
void set_buttons_subjList(BUTTON& exit,int page,int nRow,BUTTON& pageA, BUTTON& pageB,int nPageTable, BUTTON& bar_search,BUTTON& clear, 
AREA &subjID, AREA &subjName,BUTTON& THEM, BUTTON &LUU,BUTTON& XOA,BUTTON& subClear,AREA& pageArea, AREA* DSMH){
	AREA area;
	char buff[10];
    set_area(subjID,l_win/2+365,w_win/3-12,210,30);
	set_area(subjName,l_win/2+270,w_win/3+80,310,30);
	set_area(pageArea,l_win/4+50,w_win-70,100,30);
	set_exit(exit,(char*)"VE TRANG DAU",l_win-25,5,black);
	set_area(area,l_win/2-50,w_win-70,14.8*strlen("TRANG SAU"),30);
	set_button(pageA,area,(char*)"TRANG SAU",sizeM,black,CENTER,3,3);
	set_area(area,l_win/7,w_win-70,14*strlen("TRANG TRUOC"),30);
	set_button(pageB,area,(char*)"TRANG TRUOC",sizeM,black,CENTER,3,3);
	set_area(area, l_win/16+strlen("TIM KIEM:")*lth_sizeM+7,w_win/4-20,500,30);
	set_button(bar_search,area,(char*)"Nhap tu khoa de tim kiem",sizeM-1,black,LEFT,white,white);
	set_area(area, l_win/16+640,w_win/4-20,75,30);
	set_button(clear,area,(char*)"CLEAR",sizeM,black,CENTER,white,darkWhite);
	set_area(area,l_win/2+372,w_win/3+145,(strlen("THEM")+1)*lth_sizeM,30);
	set_button(THEM,area,(char*)"THEM",sizeM,black,CENTER,white,darkWhite);
	set_area(area,l_win/2+453,w_win/3+145,(strlen("LUU")+1)*lth_sizeM,30);
    set_button(LUU,area,(char*)"SUA",sizeM,black,CENTER,white,darkWhite);
    set_area(area,l_win/2+520,w_win/3+145,(strlen("XOA")+1)*lth_sizeM,30);
    set_button(XOA,area,(char*)"XOA",sizeM,black,CENTER,white,darkWhite);
    set_area(area,l_win/2+277,w_win/3+145,(strlen("CLEAR")+1)*lth_sizeM,30);
    set_button(subClear,area,(char*)"CLEAR",sizeM,black,CENTER,white,darkWhite);
    for(int i=0;i<10;i++) set_area(DSMH[i],l_win/16+645,w_win/3+60+30*i,strlen("DSCH")*(lth_sizeM-2),20);
	draw_button(bar_search);
	draw_button(clear);
	draw_button(THEM);
	draw_button(subClear);
	highlight_button(XOA,darkWhite,white,white);
	highlight_button(LUU,darkWhite,white,white);	
}
void set_hover_markList1(BUTTON* Menu,rowTable* ROWTBs,int &hover,int& j,int tt,int x,int y,int nRow,BUTTON& clear){
	j = hover;	
	for(hover=0;hover<nLecMenu;hover++){
		if(hover==tt) continue;
		if(is_area(Menu[hover].area,x,y)) break;
	}
	if(hover!=nLecMenu) return;
	for(hover = 100; hover<100+nRow;hover++) 
   	    if(is_rowTable(ROWTBs[hover-100],x,y)) break;
   	if(is_area(clear.area,x,y)) hover = 11;
}
void set_hover_markList2(BUTTON* Menu,int nMenu,rowTable* ROWTBs,int &hover,int& j,int tt,int x,int y,int nRow,BUTTON& clear){
	j = hover;	
	for(hover=0;hover<nMenu;hover++){
		if(hover==tt) continue;
		if(is_area(Menu[hover].area,x,y)) break;
	}
	if(hover!=nMenu) return;
	for(hover = 100; hover<100+nRow;hover++) 
   	    if(is_rowTable(ROWTBs[hover-100],x,y)) break;
   	if(is_area(clear.area,x,y)) hover = 11;
}
void set_hover_markList(BUTTON* Menu,int &hover,int& j,int tt,int x,int y,BUTTON& XEM,BUTTON& LOC2,BUTTON buttons[],int nRow){
	j = hover;	
	for(hover=0;hover<nLecMenu;hover++){
		if(hover==tt) continue;
		if(is_area(Menu[hover].area,x,y)) break;
	}
	if(hover!=nLecMenu) return;
	for(hover = 100; hover<100+nRow;hover++) 
   	    if(is_area(buttons[hover-100].area,x,y)) break;
   	if(is_area(XEM.area,x,y)) hover = 11;
	else if(is_area(LOC2.area,x,y)) hover=12; 
}
void set_nPageTable(int &nRow,int &nPageTable,int n_index,int& page,int is_search){
	nPageTable = n_index/10; 
	nPageTable += (n_index%10 != 0) ;
	if(nPageTable==0) page=0;
	else if(is_search) page =1;
	else if(page>nPageTable||page==0) page = nPageTable;
}
void xoa(BUTTON& bar_search, int& choose,char* search_text,char* CID_text,char* CName_text,int idx_start_search,int& idx_start_TL, int chooseNow,char* page_text, int page_tmp){
	settextstyle(font_text,0,sizeS);
	if(choose==1) {
		if(strlen(search_text)==0&&chooseNow!=1) draw_button(bar_search);
		else print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
	}
	else if(choose==2){
		out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"                      ",3,3);
		if(strlen(CID_text)==0) out_text_xy(l_win/2+382,w_win/3-9,(char*)" ",white,white);
        else print_text_bar(l_win/2+382,w_win/3-9,CID_text,11,white,black);
        
	}
	else if(choose==3){
		out_text_xy(l_win/2+277,w_win/3+83+30,(char*)"                        ",3,3);
		if(strlen(CName_text)==0) out_text_xy(l_win/2+277,w_win/3+83,(char*)" ",white,white);
		else {
			print_text_bar(l_win/2+277,w_win/3+83,CName_text+idx_start_TL,24,white,white);	
			fix_str2(CName_text);
			idx_start_TL = 0;
     		print_text_bar(l_win/2+277,w_win/3+83,CName_text+idx_start_TL,24,white,black);	
		}
	}
	else if(choose==4){
		if(strlen(page_text)==0){
			char buff[10];
			strcpy(page_text,itoa(page_tmp,buff,decimal));
		}
		settextstyle(font_text,0,sizeM);
		out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
	}
	choose = chooseNow;
}
void xoa1(BUTTON& bar_search,char* search_text,int idx_start_search , char* SID_text,char* LName_text, int& idx_start_LN, char* FName_text, int idx_start_FN,char* PW_text, int& choose,int chooseNow,char* page_text, int page_tmp){
	settextstyle(font_text,0,sizeS);
	if(choose==1) {
		if(strlen(search_text)==0&&chooseNow!=1) draw_button(bar_search);
		else print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
	}
	else if(choose==2){
		out_text_xy(l_win/2+277,w_win/3-37+30,(char*)"                     ",3,3);
		if(strlen(SID_text)==0) out_text_xy(l_win/2+367,w_win/3-37,(char*)" ",white,white);
        else print_text_bar(l_win/2+367,w_win/3-37,SID_text,11,white,black);       
	}
	else if(choose==3){
		out_text_xy(l_win/2+277,w_win/3+53+30,(char*)"                ",3,3);
		if(strlen(LName_text)==0) out_text_xy(l_win/2+277,w_win/3+53,(char*)" ",white,white);
		else {
			print_text_bar(l_win/2+277,w_win/3+53,LName_text+idx_start_LN,15,white,white);
			fix_str1(LName_text);
			idx_start_LN = 0;
     		print_text_bar(l_win/2+277,w_win/3+53,LName_text+idx_start_LN,15,white,black);	
		}
	}
	else if(choose==4){
	    out_text_xy(l_win/2+475,w_win/3+53+30,(char*)"         ",3,3);
		if(strlen(FName_text)==0) out_text_xy(l_win/2+487,w_win/3+53,(char*)" ",white,white);
		else {
			print_text_bar(l_win/2+487,w_win/3+53,FName_text+idx_start_FN,7,white,white);
			fix_str1(FName_text);
			idx_start_FN = 0;
     		print_text_bar(l_win/2+487,w_win/3+53,FName_text+idx_start_FN,7,white,black);	
		}
	}
	else if(choose==5){
		out_text_xy(l_win/2+277,w_win/3+173+30,(char*)"                      ",3,3);
		if(strlen(PW_text)==0) out_text_xy(l_win/2+407,w_win/3+173,(char*)" ",white,white);
        else print_text_bar(l_win/2+407,w_win/3+173,PW_text,10,white,black);       
	}
	else if(choose==7){
		if(strlen(page_text)==0){
			char buff[10];
			strcpy(page_text,itoa(page_tmp,buff,decimal));
		}
		settextstyle(font_text,0,sizeM);
		out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
	}
	choose = chooseNow;
}
void xoa2(BUTTON& bar_search, int& choose,char* search_text,char* SID_text,char* SName_text,int idx_start_search,int& idx_start_TMH, int chooseNow,char* page_text, int page_tmp){
	settextstyle(font_text,0,sizeS);
	if(choose==1) {
		if(strlen(search_text)==0&&chooseNow!=1) draw_button(bar_search);
		else print_text_bar(l_win/16+140,w_win/4-17,search_text+idx_start_search,40,white,black);
	}
	else if(choose==2){
		out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"                     ",3,3);
		if(strlen(SID_text)==0) out_text_xy(l_win/2+372,w_win/3-9,(char*)" ",white,white);
        else print_text_bar(l_win/2+372,w_win/3-9,SID_text,15,white,black);
        
	}
	else if(choose==3){
		out_text_xy(l_win/2+277,w_win/3+83+30,(char*)"                      ",3,3);
		if(strlen(SName_text)==0) out_text_xy(l_win/2+277,w_win/3+83,(char*)" ",white,white);
		else {
			print_text_bar(l_win/2+277,w_win/3+83,SName_text+idx_start_TMH,24,white,white);	
			fix_str2(SName_text);
			idx_start_TMH = 0;
     		print_text_bar(l_win/2+277,w_win/3+83,SName_text+idx_start_TMH,24,white,black);	
		}
	}
	else if(choose==4){
		if(strlen(page_text)==0){
			char buff[10];
			strcpy(page_text,itoa(page_tmp,buff,decimal));
		}
		settextstyle(font_text,0,sizeM);
		out_text_xy(l_win/4+100-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
	}
	choose = chooseNow;
}
void xoa3(BUTTON& bar_search,char* search_text,int idx_start_search, int& choose,int chooseNow,char* page_text, int page_tmp){
	settextstyle(font_text,0,sizeS);
	if(choose==1) {
		if(strlen(search_text)==0&&chooseNow!=1) draw_button(bar_search);
		else print_text_bar(l_win/16+290,w_win/4-17,search_text+idx_start_search,40,white,black);
	}
	else if(choose==7){
		if(strlen(page_text)==0){
			char buff[10];
			strcpy(page_text,itoa(page_tmp,buff,decimal));
		}
		settextstyle(font_text,0,sizeM);
		out_text_xy(l_win/4+250-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
	}
	choose = chooseNow;
}
void xoa4(char* text1,char* text2,int& choose,int chooseNow,int nRow,int& is_click_filter,int& is_click_text1,int& is_click_text2,BUTTON& LOC2,BUTTON& XEM){
	settextstyle(font_text,0,sizeS);
	if(choose==1) {
		out_text_xy(207,w_win/4+33,(char*)"                          ",3,3);
		if(strlen(text1)==0) out_text_xy(207,w_win/4+63,(char*)" ",white,white);
		else out_text_xy(207,w_win/4+63,text1,white,black);
		if(is_click_text1){
			is_click_text1 = 0;
			create_1_bar(200,w_win/4+60+32,430,(nRow+1)*30,3,3);
		}
	}
	else if(choose==2){
		out_text_xy(747,w_win/4+33,(char*)"                          ",3,3);
		if(strlen(text2)==0){
			out_text_xy(747,w_win/4+63,(char*)" ",white,white);
			if(chooseNow!=2) highlight_button(XEM,darkWhite,white,white);
		} 
        else out_text_xy(747,w_win/4+63,text2,white,black);
        if(is_click_text2){
        	is_click_text2 = 0;
        	create_1_bar(740,w_win/4+60+32,430,30*(nRow+1),3,3); 
		}
	}	
	if(choose==-1){
		if(is_click_filter){
			is_click_filter = 0;
			highlight_button(LOC2,3,3,3);
	    }
	}
	choose = chooseNow;
}
void inform(int& s,int sub_tt,char* CID_text, int& print_s){
	settextstyle(font_text,0,sizeS);
	if(--s) {
		if(s<199) return; 
		else if(sub_tt==1) {
	    	out_text_xy(l_win/2+290,w_win/2+180,(char*)"Da them lop: ",3,black);
	    	out_text_xy(l_win/2+370,w_win/2+210,CID_text,3,red);
    	}
    	else if(sub_tt==2){ 
	    	out_text_xy(l_win/2+290,w_win/2+180,(char*)"Da xoa lop: ",3,black);
	    	out_text_xy(l_win/2+370,w_win/2+210,CID_text,3,red);    		
		}
		else if(sub_tt==3){
	    	out_text_xy(l_win/2+290,w_win/2+180,(char*)"Da luu lop: ",3,black);
	    	out_text_xy(l_win/2+370,w_win/2+210,CID_text,3,red);    		
		}
		else if(sub_tt==4){
			out_text_xy(l_win/2+290,w_win/2+180,(char*)"Lop co SV da thi",3,darkRed);
			out_text_xy(l_win/2+290,w_win/2+210,(char*)"Khong the xoa!",3,darkRed);
		} 
	}
	else {
		print_s = 0;
        out_text_xy(l_win/2+290,w_win/2+180,(char*)"                  ",3,3);
	    out_text_xy(l_win/2+290,w_win/2+210,(char*)"                  ",3,3);		
	}
}
void inform1(int& s,int sub_tt,char* SID_text, int& print_s){
	settextstyle(font_text,0,sizeS);
	if(--s) {
		if(s<199) return; 
		else if(sub_tt==1) {
	    	out_text_xy(l_win/2+290,w_win/2+180,(char*)"Da them SV: ",3,black);
	    	out_text_xy(l_win/2+370,w_win/2+210,SID_text,3,red);
    	}
    	else if(sub_tt==2){ 
	    	out_text_xy(l_win/2+290,w_win/2+180,(char*)"Da xoa SV: ",3,black);
	    	out_text_xy(l_win/2+370,w_win/2+210,SID_text,3,red);    		
		}
		else if(sub_tt==3){
	    	out_text_xy(l_win/2+290,w_win/2+180,(char*)"Da luu SV: ",3,black);
	    	out_text_xy(l_win/2+370,w_win/2+210,SID_text,3,red);    		
		}
		else if(sub_tt==4){
			out_text_xy(l_win/2+290,w_win/2+180,(char*)"Sinh vien da thi",3,darkRed);
			out_text_xy(l_win/2+290,w_win/2+210,(char*)"Khong the xoa !",3,darkRed);
		} 
	}
	else {
		print_s = 0;
        out_text_xy(l_win/2+290,w_win/2+180,(char*)"                 ",3,3);
	    out_text_xy(l_win/2+290,w_win/2+210,(char*)"                 ",3,3);		
	}
}
void inform2(int& s,int sub_tt,char* subjID, int& print_s){
	settextstyle(font_text,0,sizeS);
	if(--s) {
		if(s<199) return; 
		else if(sub_tt==1) {
	    	out_text_xy(l_win/2+290,w_win/2+180,(char*)"Da them MH: ",3,black);
	    	out_text_xy(l_win/2+370,w_win/2+210,subjID,3,red);
    	}
    	else if(sub_tt==2){ 
	    	out_text_xy(l_win/2+290,w_win/2+180,(char*)"Da xoa MH: ",3,black);
	    	out_text_xy(l_win/2+370,w_win/2+210,subjID,3,red);    		
		}
		else if(sub_tt==3){
	    	out_text_xy(l_win/2+290,w_win/2+180,(char*)"Da luu MH: ",3,black);
	    	out_text_xy(l_win/2+370,w_win/2+210,subjID,3,red);    		
		}
		else if(sub_tt==4){
			out_text_xy(l_win/2+290,w_win/2+180,(char*)"MH co CH da thi",3,darkRed);
			out_text_xy(l_win/2+290,w_win/2+210,(char*)"Khong the xoa !",3,darkRed);
		} 
	}
	else {		
		print_s = 0;
        out_text_xy(l_win/2+290,w_win/2+180,(char*)"                  ",3,3);
	    out_text_xy(l_win/2+290,w_win/2+210,(char*)"                  ",3,3);		
	}
}
bool is_delete(char* text,int i){
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
	out_text_xy(l_win/2+290,w_win/2+180,(char*)"Ban co muon xoa",3,black);
	if(i == 1) out_text_xy(l_win/2+290+strlen("Ban co muon xoa ")*(lth_sizeM-2),w_win/2+180,(char*)"lop: ",3,black);
	else if(i ==2) out_text_xy(l_win/2+290+strlen("Ban co muon xoa ")*(lth_sizeM-2),w_win/2+180,(char*)"SV: ",3,black);
	else if(i==3) out_text_xy(l_win/2+290+strlen("Ban co muon xoa ")*(lth_sizeM-2),w_win/2+180,(char*)"MH: ",3,black);
	else if(i==4) out_text_xy(l_win/2+290+strlen("Ban co muon xoa ")*(lth_sizeM-2),w_win/2+180,(char*)"CH: ",3,black);
	out_text_xy(l_win/2+370,w_win/2+205,text,3,red); 
	while(1){
		delay(0);
		if(s){
			s--;
			if(s%5==0){
				if(k==0){
					setcolor(3);
	             	k=1;
	 			}
	 			else{
	 				setcolor(red);
	             	k=0;
				}	
			}
			rectangle(l_win/2+270,w_win/2+170,l_win/2+580,w_win/2+280);
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
				create_1_bar(l_win/2+275,w_win/2+175,300,100,3,black);
				return true;
			} 
			else if(is_area(No.area,x,y)){
				create_1_bar(l_win/2+275,w_win/2+175,300,100,3,black);
             	return false;
			}
			else if((x<l_win/2+280)||(y<w_win/2+175)||(x>l_win/2+570)||(y>w_win/2+280)){
				s = 46;
			}			
		}
	}
}
void clear_notice_classi4(){
	settextstyle(font_text,0,sizeS);
	out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"                 ",3,3);
	out_text_xy(l_win/2+277,w_win/3+83+30,(char*)"                 ",3,3);
}
void clear_notice_stui4(){
	settextstyle(font_text,0,sizeS);
	out_text_xy(l_win/2+277,w_win/3-37+30,(char*)"                     ",3,3);
	out_text_xy(l_win/2+277,w_win/3+53+30,(char*)"                ",3,3);
	out_text_xy(l_win/2+475,w_win/3+53+30,(char*)"         ",3,black);
	out_text_xy(l_win/2+277,w_win/3+173+30,(char*)"                      ",3,3);
	out_text_xy(l_win/2+270,w_win/3+140,(char*)"                    ",3,3);
}
void clear_notice_subji4(){
	settextstyle(font_text,0,sizeS);
	out_text_xy(l_win/2+277,w_win/3-10+30,(char*)"Ma MH da ton tai",3,3);
	out_text_xy(l_win/2+277,w_win/3+83+30,(char*)"Chua nhap ten MH",3,3);
}
void clear_edit_classi4(char* CID_text,char* CName_text,int idx_start_TL){
	print_text_bar(l_win/2+382,w_win/3-9,CID_text,11,white,white);
    print_text_bar(l_win/2+277,w_win/3+83,CName_text+idx_start_TL,24,white,white);
}
void clear_edit_stui4(char* SID_text,char* LName_text,int idx_start_LN,char* FName_text,int idx_start_FN,char* PW_text){
	print_text_bar(l_win/2+367,w_win/3-37,SID_text,12,white,white);
	print_text_bar(l_win/2+277,w_win/3+53,LName_text+idx_start_LN,15,white,white);
	print_text_bar(l_win/2+487,w_win/3+53,FName_text+idx_start_FN,7,white,white);
	print_text_bar(l_win/2+407,w_win/3+173,PW_text,10,white,white);
	draw_circle(l_win/2+380,w_win/3+125,8,white);
    draw_circle(l_win/2+480,w_win/3+125,8,white);
}
void reset_classi4(char* CID_text, int& cursor_pos_ML,char* CName_text,int& cursor_pos_TL,int& idx_TL,int& idx_start_TL){
    CID_text[0]='\0';
	cursor_pos_ML = 0;
	CName_text[0]='\0';
	cursor_pos_TL = 0;
	idx_TL = 0;
	idx_start_TL = 0;
}
void reset_stui4(char* SID_text, int& cursor_pos_MSV,int& cursor_pos_LN,char* LName_text,int& idx_LN,int& idx_start_LN,char* FName_text, int& cursor_pos_FN,int& idx_FN,int& idx_start_FN, char* sex, char* PW_text,int& cursor_pos_PW){
	SID_text[0]='\0';
	cursor_pos_MSV = 0;
	LName_text[0] ='\0';
	cursor_pos_LN = 0;
	idx_LN = 0;
	idx_start_LN = 0;
	FName_text[0] ='\0';
	cursor_pos_FN = 0;
	idx_FN = 0;
	idx_start_FN = 0;
	sex[0]='\0';
	PW_text[0]='\0';
	cursor_pos_PW = 0;
}
void reset_subji4(char* SID_text, int& cursor_pos_MMH,char* SName_text,int& cursor_pos_TMH,int& idx_TMH,int& idx_start_TMH){
    SID_text[0]='\0';
	cursor_pos_MMH = 0;
	SName_text[0]='\0';
	cursor_pos_TMH = 0;
	idx_TMH = 0;
	idx_start_TMH = 0;
}
void set_bar_edit_classi4(int bdr_color){
	create_1_bar(l_win/2+375,w_win/3-12,170,30,white,bdr_color);
    create_1_bar(l_win/2+270,w_win/3+80,310,30,white,bdr_color);
}
void set_bar_edit_stui4(int bdr_color){
	create_1_bar(l_win/2+360,w_win/3-42,170,30,white,bdr_color);
    create_1_bar(l_win/2+270,w_win/3+48,200,30,white,bdr_color);
	create_1_bar(l_win/2+480,w_win/3+48,100,30,white,bdr_color);
    create_1_bar(l_win/2+400,w_win/3+168,170,30,white,bdr_color);
    draw_circle(l_win/2+380,w_win/3+125,8,white);
    draw_circle(l_win/2+480,w_win/3+125,8,white);
}
void set_bar_edit_subji4(int bdr_color){
	create_1_bar(l_win/2+365,w_win/3-12,210,30,white,bdr_color);
    create_1_bar(l_win/2+270,w_win/3+80,310,30,white,bdr_color);
}
void clear_edit_subji4(char* SID_text,char* SName_text,int idx_start_TMH){
	print_text_bar(l_win/2+372,w_win/3-9,SID_text,15,white,white);
    print_text_bar(l_win/2+277,w_win/3+83,SName_text+idx_start_TMH,24,white,white);
}
void set_buttons_Thi_TN(BUTTON& exit, BUTTON& Enter, BUTTON& subjID, BUTTON& page_after,BUTTON& page_before,AREA& nQuest_bar,AREA& nMinute_bar){
	AREA area;
	set_exit(exit,(char*)"VE TRANG DAU",l_win-25,5,black);
	set_area(area,l_win/2+50,w_win/4+120,(strlen("VAO THI")+1)*lth_sizeM,30);
	set_button(Enter,area,(char*)"VAO THI",sizeM,black,CENTER,white,darkWhite);
	highlight_button(Enter,darkWhite,white,white);
	set_area(area,200,w_win/4,400,30);
	set_button(subjID,area,(char*)"",sizeS,darkRed,LEFT,white,white);
	draw_button_opt(subjID);
	set_area(area,-1,-1,0,0);
	set_button(page_after,area,(char*)"->",sizeM,darkRed,CENTER,white,white);
	set_button(page_before,area,(char*)"<-",sizeM,darkRed,CENTER,white,white);
	set_area(nQuest_bar,l_win/2+270,w_win/4,150,30);
	set_area(nMinute_bar,l_win/2+230,w_win/4+70,150,30);
}	
void xoa5(char* subjID_text,char* nQuest,char* nMinute,int &choose, int chooseNow,int nRow,int& is_click_MMH,BUTTON& THI){
	settextstyle(font_text,0,sizeS);
	if(choose ==1) {
		out_text_xy(207,w_win/4-30,(char*)"                                ",3,3);
		if(strlen(subjID_text)==0) out_text_xy(207,w_win/4+5,(char*)" ",white,white);
		else out_text_xy(207,w_win/4+5,subjID_text,white,black);
		if(is_click_MMH){
			is_click_MMH = 0;
			create_1_bar(200,w_win/4+32,430,(nRow+1)*30,3,3);
		}
	}	
	else if(choose==2){
		out_text_xy(l_win/2+277,w_win/4+5+30,(char*)"                       ",3,3);
		if(strlen(nQuest)==0) out_text_xy(l_win/2+277,w_win/4+5,(char*)" ",white,white);
        else out_text_xy(l_win/2+277,w_win/4+5,nQuest,white,black);
        if(chooseNow!=2&&chooseNow!=3&&(strlen(nQuest)==0||strlen(nMinute)==0)) highlight_button(THI,darkWhite,white,white);
	}	
    else if(choose==3){
		out_text_xy(l_win/2+237,w_win/4+75+30,(char*)"                       ",3,3);
		if(strlen(nMinute)==0) out_text_xy(l_win/2+237,w_win/4+75,(char*)" ",white,white);
        else out_text_xy(l_win/2+237,w_win/4+75,nMinute,white,black);
        if(chooseNow!=2&&chooseNow!=3&&(strlen(nQuest)==0||strlen(nMinute)==0)) highlight_button(THI,darkWhite,white,white);
	}
	choose = chooseNow;
}
void set_hover_Thi_TN(BUTTON* Menu,int nMenu,int &hover,int& j,int tt,int x,int y,BUTTON& Enter,BUTTON buttons[],int nRow){
	j = hover;	
	for(hover=0;hover<nMenu;hover++){
		if(hover==tt) continue;
		if(is_area(Menu[hover].area,x,y)) break;
	}
	if(hover!=nMenu) return;
	for(hover = 100; hover<100+nRow;hover++) 
   	    if(is_area(buttons[hover-100].area,x,y)) break;
   	if(is_area(Enter.area,x,y)) hover = 11;
}
void set_buttons_Thi_TN_2(BUTTON Questions[],BUTTON& submit,AREA& page_after, AREA& page_before,AREA& Quest_after, AREA& Quest_before,CTick DA[]){
	AREA area;
	set_area(page_before,20,w_win-62,20,22);
	set_area(page_after,150,w_win-62,20,22);
	set_area(area,l_win/2+350,w_win-250,150,30);
	set_button(submit,area,(char*)"NOP BAI",sizeM,black,CENTER,white,darkWhite);
	set_area(Quest_before,l_win/4-50,w_win/2+205,strlen("CAU TRUOC")*(lth_sizeM-2),20);
	set_area(Quest_after,l_win/4+370,w_win/2+205,strlen("CAU SAU")*(lth_sizeM-2),20);
	for(int i=0;i<15;i++){
		set_area(area,20,100+32*i,150,30);
		set_button(Questions[i],area,(char*)"Cau ",sizeM,black,CENTER,white,darkWhite);
	}
	for(int i=0;i<4;i++){
		set_CTick(DA[i],250,230+60*i,10);
		draw_CTick(DA[i]);
    }
	draw_button(submit);
	settextstyle(font_text,0,sizeM-1);
}
void print_text(int x, int y, char* text, int limit,int color){
	int len, k;
	if(limit<=0) return;
	while((len = strlen(text))){
		if(len>limit){
			k = limit;
		    while(k>=0 && text[k]!=' ') k--;
		    if(k>=0){
		    	text[k] = '\0';
		        out_text_xy(x,y,text,3,color);
		        text[k] = ' ';
		        y+=30;
		        text = text + k + 1;
			} 
			else return; 
	    }
	    else{
	    	out_text_xy(x,y,text,3,color);
	    	return;
		}
    }
}
void set_buttons_xem_KQ(BUTTON Questions[],AREA& page_after, AREA& page_before,AREA& Quest_after, AREA& Quest_before,CTick DA[]){
	AREA area;
	set_area(page_before,20,w_win-62,20,22);
	set_area(page_after,150,w_win-62,20,22);
	set_area(Quest_before,l_win/4-50,w_win/2+205,strlen("CAU TRUOC")*(lth_sizeM-2),20);
	set_area(Quest_after,l_win/4+370,w_win/2+205,strlen("CAU SAU")*(lth_sizeM-2),20);
	for(int i=0;i<15;i++){
		set_area(area,20,100+32*i,150,30);
		set_button(Questions[i],area,(char*)"Cau ",sizeM,black,CENTER,white,darkWhite);
	}
	for(int i=0;i<4;i++){
		set_CTick(DA[i],250,230+60*i,10);
		draw_CTick(DA[i]);
    }
}
void set_buttons_quesList(BUTTON& exit,rowTable* ROWTBs,int page,int nRow,BUTTON& pageA, BUTTON& pageB,int nPageTable, BUTTON& bar_search,BUTTON& clear, 
AREA& ND, AREA &A, AREA &B,AREA& C,AREA& D,BUTTON& THEM, BUTTON &LUU,BUTTON& XOA,BUTTON& subClear,AREA& pageArea, BUTTON& Return,CTick DAPAN[]){
	AREA area;
	char buff[10];
    set_area(ND,l_win/2+70,w_win/3+23,500,30);
	set_area(A,l_win/2+50,w_win/3+88,230,30);
	set_area(B,l_win/2+340,w_win/3+88,230,30);
	set_area(C,l_win/2+50,w_win/3+153,230,30);
	set_area(D,l_win/2+340,w_win/3+153,230,30);
	set_area(pageArea,l_win/4-70,w_win-70,100,30);
	set_exit(exit,(char*)"VE TRANG DAU",l_win-25,5,black);
	set_area(area,l_win/2-170,w_win-70,14.8*strlen("TRANG SAU"),30);
	set_button(pageA,area,(char*)"TRANG SAU",sizeM,black,CENTER,3,3);
	set_area(area,l_win/7-120,w_win-70,14*strlen("TRANG TRUOC"),30);
	set_button(pageB,area,(char*)"TRANG TRUOC",sizeM,black,CENTER,3,3);
	set_area(area, l_win/16-30+strlen("TIM KIEM:")*lth_sizeM+7,w_win/4,320,30);
	set_button(bar_search,area,(char*)"Nhap tu khoa de tim kiem",sizeM-1,black,LEFT,white,white);
	set_area(area, l_win/16+440,w_win/4,75,30);
	set_button(clear,area,(char*)"CLEAR",sizeM,black,CENTER,white,darkWhite);
	set_area(area,l_win/2+150,w_win-150,(strlen("THEM")+1)*lth_sizeM,30);
	set_button(THEM,area,(char*)"THEM",sizeM,black,CENTER,white,darkWhite);
	set_area(area,l_win/2+80,w_win-100,(strlen("LUU")+1)*lth_sizeM,30);
    set_button(LUU,area,(char*)"SUA",sizeM,black,CENTER,white,darkWhite);
    set_area(area,l_win/2+150,w_win-100,(strlen("XOA")+1)*lth_sizeM,30);
    set_button(XOA,area,(char*)"XOA",sizeM,black,CENTER,white,darkWhite);
    set_exit(Return,(char*)"QUAY LAI",l_win/2-20,w_win/7+10,darkRed);
    set_area(area,l_win/2+50,w_win - 150,(strlen("CLEAR")+1)*lth_sizeM,30);
    set_button(subClear,area,(char*)"CLEAR",sizeM,black,CENTER,white,darkWhite);
    for(int i=0;i<4;i++){
    	set_CTick(DAPAN[i],l_win/2+170+100*i,w_win/3+232,8);
    	draw_CTick(DAPAN[i]);
	} 
	draw_button(bar_search);
	draw_button(clear);
	draw_button(THEM);
	draw_button(subClear);
	highlight_button(XOA,darkWhite,white,white);
	highlight_button(LUU,darkWhite,white,white);	
}
void inform6(int& s,int sub_tt,char* ID, int& print_s){
	settextstyle(font_text,0,sizeS);
	if(--s) {
		if(s<199) return; 
		else if(sub_tt==1) {
	    	out_text_xy(l_win/2+290,w_win/2+180,(char*)"Da them CH: ",3,black);
	    	out_text_xy(l_win/2+370,w_win/2+210,ID,3,red);
    	}
    	else if(sub_tt==2){ 
	    	out_text_xy(l_win/2+290,w_win/2+180,(char*)"Da xoa CH: ",3,black);
	    	out_text_xy(l_win/2+370,w_win/2+210,ID,3,red);    		
		}
		else if(sub_tt==3){
	    	out_text_xy(l_win/2+290,w_win/2+180,(char*)"Da luu CH: ",3,black);
	    	out_text_xy(l_win/2+370,w_win/2+210,ID,3,red);    		
		}
		else if(sub_tt==4){
			out_text_xy(l_win/2+290,w_win/2+180,(char*)"Cau hoi da thi",3,darkRed);
			out_text_xy(l_win/2+290,w_win/2+210,(char*)"Khong the xoa !",3,darkRed);
		} 
		else if(sub_tt==5){
			out_text_xy(l_win/2+290,w_win/2+180,(char*)"Cau hoi da thi",3,darkRed);
			out_text_xy(l_win/2+290,w_win/2+210,(char*)"Khong the sua !",3,darkRed);
		} 
	}
	else {
		print_s = 0;
        out_text_xy(l_win/2+290,w_win/2+180,(char*)"                 ",3,3);
	    out_text_xy(l_win/2+290,w_win/2+210,(char*)"                 ",3,3);		
	}
}
void xoa6(BUTTON& bar_search,char* search_text,int idx_start_search , char* ND,int &idx_start_ND,char* A, int& idx_start_A, char* B, int &idx_start_B,char* C,int& idx_start_C,char* D,int &idx_start_D, int& choose,int chooseNow,char* page_text, int page_tmp){
	settextstyle(font_text,0,sizeS-1);
	if(choose==1) {
		if(strlen(search_text)==0&&chooseNow!=1) draw_button(bar_search);
		else print_text_bar(l_win/16+110,w_win/4+5,search_text+idx_start_search,25,white,black);
	}
	else if(choose==2){
		out_text_xy(l_win/2+77,w_win/3+28+30,(char*)"                    ",3,3);
		if(strlen(ND)==0) out_text_xy(l_win/2+77,w_win/3+28,(char*)" ",white,white);
		else {
			print_text_bar(l_win/2+77,w_win/3+28,ND+idx_start_ND,40,white,white);
			fix_str2(ND);
			idx_start_ND = 0;
     		print_text_bar(l_win/2+77,w_win/3+28,ND+idx_start_ND,40,white,black);	
		}
	}
	else if(choose==3){
		out_text_xy(l_win/2+57,w_win/3+93+30,(char*)"                     ",3,3);
		if(strlen(A)==0) out_text_xy(l_win/2+57,w_win/3+93,(char*)" ",white,white);
		else {
			print_text_bar(l_win/2+57,w_win/3+93,A+idx_start_A,18,white,white);
			fix_str2(A);
			idx_start_A = 0;
     		print_text_bar(l_win/2+57,w_win/3+93,A+idx_start_A,18,white,black);	
		}
	}
	else if(choose==4){
		out_text_xy(l_win/2+347,w_win/3+93+30,(char*)"                      ",3,3);
		if(strlen(B)==0) out_text_xy(l_win/2+347,w_win/3+93,(char*)" ",white,white);
		else {
			print_text_bar(l_win/2+347,w_win/3+93,B+idx_start_B,18,white,white);
			fix_str2(B);
			idx_start_B = 0;
     		print_text_bar(l_win/2+347,w_win/3+93,B+idx_start_B,18,white,black);	
		}
	}
	else if(choose==5){
	    out_text_xy(l_win/2+57,w_win/3+158+30,(char*)"                      ",3,3);
		if(strlen(C)==0) out_text_xy(l_win/2+57,w_win/3+158,(char*)" ",white,white);
		else {
			print_text_bar(l_win/2+57,w_win/3+158,C+idx_start_C,18,white,white);
			fix_str2(C);
			idx_start_C = 0;
     		print_text_bar(l_win/2+57,w_win/3+158,C+idx_start_C,18,white,black);	
		}
	}
	else if(choose==6){
	    out_text_xy(l_win/2+347,w_win/3+158+30,(char*)"                    ",3,3);
		if(strlen(D)==0) out_text_xy(l_win/2+347,w_win/3+158,(char*)" ",white,white);
		else {
			print_text_bar(l_win/2+347,w_win/3+158,D+idx_start_D,18,white,white);
			fix_str2(D);
			idx_start_D = 0;
     		print_text_bar(l_win/2+347,w_win/3+158,D+idx_start_D,18,white,black);	
		}
	}
	else if(choose==7){
		if(strlen(page_text)==0){
			char buff[10];
			strcpy(page_text,itoa(page_tmp,buff,decimal));
		}
		settextstyle(font_text,0,sizeM);
		out_text_xy(l_win/4-20-(lth_sizeM/2)*strlen(page_text),w_win-67,page_text,white,black);
	}
	choose = chooseNow;
}
void clear_notice_quesi4(){
	settextstyle(font_text,0,sizeS);
	out_text_xy(l_win/2+77,w_win/3+28+30,(char*)"                    ",3,3);
	out_text_xy(l_win/2+57,w_win/3+93+30,(char*)"                     ",3,3);
	out_text_xy(l_win/2+347,w_win/3+93+30,(char*)"                    ",3,3);
	out_text_xy(l_win/2+57,w_win/3+158+30,(char*)"                     ",3,3);
	out_text_xy(l_win/2+347,w_win/3+158+30,(char*)"                    ",3,3);
	out_text_xy(l_win/2+150,w_win/3+215+30,(char*)"                                   ",3,3);
}
void set_bar_edit_quesi4(int bdr_color){
	create_1_bar(l_win/2+70,w_win/3+23,500,30,white,bdr_color);
	create_1_bar(l_win/2+50,w_win/3+88,230,30,white,bdr_color);
	create_1_bar(l_win/2+340,w_win/3+88,230,30,white,bdr_color);
	create_1_bar(l_win/2+50,w_win/3+153,230,30,white,bdr_color);
	create_1_bar(l_win/2+340,w_win/3+153,230,30,white,bdr_color);
    for(int i=0;i<4;i++) draw_circle(l_win/2+170+100*i,w_win/3+232,8,white);
}
void clear_edit_quesi4(char* ND,int idx_start_ND,char* A,int idx_start_A,char* B,int idx_start_B,char* C,int idx_start_C,char* D,int idx_start_D){
	print_text_bar(l_win/2+77,w_win/3+28,ND+idx_start_ND ,40,white,white);
	print_text_bar(l_win/2+57,w_win/3+93,A+idx_start_A,18,white,white);
    print_text_bar(l_win/2+347,w_win/3+93,B+idx_start_B,18,white,white);
    print_text_bar(l_win/2+57,w_win/3+158,C+idx_start_C,18,white,white);
	print_text_bar(l_win/2+347,w_win/3+158,D+idx_start_D,18,white,white);
	for(int i=0;i<4;i++) draw_circle(l_win/2+170+100*i,w_win/3+232,8,white);
}
void reset_quesi4(char* ND,int& cursor_pos_ND,int& idx_start_ND,int &idx_ND,char* A, int& cursor_pos_A,int& idx_start_A,int& idx_A,char* B, int& cursor_pos_B,int& idx_start_B,int& idx_B, char* C, int& cursor_pos_C,int& idx_start_C,int& idx_C,char* D, int& cursor_pos_D,int& idx_start_D,int& idx_D,char& da){
    ND[0] = A[0] = B[0] = C[0] = D[0] = '\0'; 
    cursor_pos_ND = cursor_pos_A =cursor_pos_B =cursor_pos_C = cursor_pos_D = 0;
    idx_start_ND = idx_start_A = idx_start_B = idx_start_C = idx_start_D = 0;
    idx_ND = idx_A = idx_B = idx_C = idx_D = 0;
    da = 'X';
}

