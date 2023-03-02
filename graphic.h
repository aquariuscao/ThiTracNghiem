#ifndef _MY_GRAPHIC
#define _MY_GRAPHIC
#define l_win 1250
#define w_win 650
#define decimal 10
#define height_bar 30
#define max_tt 2
#define max_str_time 8
#define max_lentitle 50
#define black			0
#define darkBlue		1
#define darkGreen		2
#define darkCyan		3
#define darkRed		    4
#define darkPink		5
#define darkYellow	 	6
#define darkWhite		7
#define grey			8
#define blue			9
#define green			10
#define cyan			11
#define red				12
#define pink			13
#define yellow			14
#define white			15
#define no_text         NULL
#define font_text       8
#define sizeL           5
#define sizeM           3
#define lth_sizeM       14
#define sizeS           2
#define wth_rw_table    30
#define len_optbar      30
#define MAX_TEXT   50
#define nostyle    0
#define LEFT       1
#define CENTER     0
#define bothCaH    2  
#define T_cursor   80 
#define MAX_BUTTON  6 
#include <winbgim.h>
#include <cstdlib>
#include "prcstring.h"
#define key_Up		2072
#define key_Down	2080
#define key_Left	2075
#define key_Right	2077
#define key_Enter   13
#define key_Esc     27
#define key_BS	    8
#define key_SP      32
#define LECTURER    1
#define STUDENT     0
#define nLecMenu    4
#define nStuMenu    2
struct AREA{
	int x;
	int y;
	int length;
	int width;
}; 
struct BUTTON{
	AREA area;
	char text[MAX_TEXT+1];
	int sizechr;
	int text_color;
	int align;
	int bdr_color;
	int bk_color;
};
struct rowTable{
	int nbutton;
	BUTTON buttons[MAX_BUTTON];
};
struct CTick{
	int x;
	int y;
	int R;
};

	
bool is_area_CTick(CTick& Tick,int x,int y);
void set_CTick(CTick& Tick,int x,int y,int R);
void draw_CTick(CTick& Tick);
void Tick_CTick(CTick& Tick,int color);
void delete_CTick(CTick& Tick,int color);
void set_rowTable(rowTable &rowTB, BUTTON* buttons, int nButton);
bool is_rowTable(rowTable &rowTable,int x,int y);
void draw_rowTable(rowTable &rowTable);
void draw_rowTable2(rowTable &rowTable);
void highlight_rowTable(rowTable &rowTable,int bk_color, int bdr_color, int text_color);
void highlight_rowTable2(rowTable &rowTable,int bk_color, int bdr_color, int text_color);
void highlight_button2(BUTTON &BT, int bk_color, int bdr_color, int text_color);
void set_area(AREA &area,int x,int y,int lth,int wth);
bool is_area(AREA &area,int x,int y);
void highlight_button(BUTTON &BT, int bk_color, int bdr_color,int text_color);
void set_button(BUTTON &BT, AREA &area, char* text,int sizechr,int text_color, int align, int bdr_color, int bk_color);
void draw_button(BUTTON &BT);
void draw_button2(BUTTON &BT);
void delete_button(BUTTON &BT, int color);
int left(int x);
int center(int x, int length, int lentext,int lenchr);
void append_tt_stime(char* str_time,int tt);
void set_time(int seconds,int& hh,int& mm,int& ss);
void out_text_xy( int x, int y, char* text, int bk_color, int text_color);
void create_1_bar( int x, int y, int length, int width, int bk_color, int bdr_color);
void create_1_bar_text( int x, int y, int length, int width, int bk_color, int bdr_color, char text[], int sizechr, int text_color, int isCenter);
void create_1_bar_text2( int x, int y, int length, int width, int bk_color, int bdr_color, char text[], int sizechr, int text_color, int isCenter);
void create_1_row_of_table( int x, int y, int lengths[], int width, int nColumn,int bk_color,int bdr_color);
void create_1_row_of_table_text(int x, int y, int lengths[], int width, int nColumn,int bk_color,int bdr_color,char titles[][max_lentitle],int sizechr, int text_color);
void create_table( int x, int y, int lengths[], int width, int nColumn, int nRow, char titles[][max_lentitle],int lenchr,int text_color,int color_row1, int bdr_color);
void print_time( int x, int y, int time);	
void draw_circle(int x,int y,int R,int color);
void create_solid_polygon(int x_y[],int n_xy,int bk_color);
void create_1_bar_opt( int x, int y, int length, int width, int bk_color,int bdr_color);
void draw_button_opt(BUTTON &BT);
void login_interface();
void draw_cursor(int x,int y,int color);	
void print_cursor(int x,int y, int &n);	
bool is_area_opt(BUTTON& BT,int x,int y);
void highlight_button_opt(BUTTON &BT,int bk_color,int bdr_color,int text_color);
void print_text_bar(int x,int y, char* start,int n, int bk_color,int text_color);	
void set_exit(BUTTON &exit,char* text,int x,int y,int color);	
void set_buttons_markList(BUTTON& exit,BUTTON& LOC,BUTTON& ML,BUTTON& MMH,BUTTON& XEM,BUTTON& LOC2,	BUTTON& page_after,BUTTON& page_before); 
void set_buttons_classList(BUTTON& exit,int page,int nRow,BUTTON& pageA, BUTTON& pageB,int nPageTable, BUTTON& bar_search,BUTTON& clear, 
AREA &classID, AREA &className,BUTTON& THEM, BUTTON &LUU,BUTTON& XOA,BUTTON& subClear,AREA& pageArea, AREA* DSSV);      
void set_buttons_StuList(BUTTON& exit,int page,int nRow,BUTTON& pageA, BUTTON& pageB,int nPageTable, BUTTON& bar_search,BUTTON& clear, 
AREA& studentID, AREA &LName, AREA &FName,AREA& password,BUTTON& THEM, BUTTON &LUU,BUTTON& XOA,BUTTON& subClear,AREA& pageArea,CTick& male,CTick& female, BUTTON& Return);
void set_buttons_markList1(BUTTON& exit,int page,int nRow,BUTTON& pageA, BUTTON& pageB,int nPageTable, BUTTON& bar_search,BUTTON& clear, AREA& pageArea,BUTTON& Return,AREA CTBT[]);
void set_buttons_markList2(BUTTON& exit,int page,int nRow,BUTTON& pageA, BUTTON& pageB,int nPageTable, BUTTON& bar_search,BUTTON& clear, AREA& pageArea, BUTTON& Return, AREA CTBT[], int user);
void set_buttons_subjList(BUTTON& exit,int page,int nRow,BUTTON& pageA, BUTTON& pageB,int nPageTable, BUTTON& bar_search,BUTTON& clear, 
AREA &subjID, AREA &subjName,BUTTON& THEM, BUTTON &LUU,BUTTON& XOA,BUTTON& subClear,AREA& pageArea, AREA* DSMH);
void set_hover_CList(BUTTON* Menu,rowTable* ROWTBs,int &hover,int& j,int tt,int x,int y,int nRow,BUTTON& clear,BUTTON& LUU,BUTTON& subClear,BUTTON& THEM,BUTTON& XOA);
void set_hover_markList1(BUTTON* Menu,rowTable* ROWTBs,int &hover,int& j,int tt,int x,int y,int nRow,BUTTON& clear);
void set_hover_markList2(BUTTON* Menu,int nMenu,rowTable* ROWTBs,int &hover,int& j,int tt,int x,int y,int nRow,BUTTON& clear);
void set_hover_markList(BUTTON* Menu,int &hover,int& j,int tt,int x,int y,BUTTON& XEM,BUTTON& LOC2,BUTTON buttons[],int nRow);
void set_nPageTable(int &nRow,int &nPageTable,int n_index,int& page,int is_search);
void xoa(BUTTON& bar_search, int& choose,char* search_text,char* CID_text,char* CName_text,int idx_start_search,int& idx_start_TL, int chooseNow,char* page_text, int page_tmp);
void xoa1(BUTTON& bar_search,char* search_text,int idx_start_search , char* SID_text,char* LName_text, int& idx_start_LN, char* FName_text, int idx_start_FN,char* PW_text, int& choose,int chooseNow,char* page_text, int page_tmp);
void xoa2(BUTTON& bar_search, int& choose,char* search_text,char* SID_text,char* SName_text,int idx_start_search,int& idx_start_TMH, int chooseNow,char* page_text, int page_tmp);
void xoa3(BUTTON& bar_search,char* search_text,int idx_start_search, int& choose,int chooseNow,char* page_text, int page_tmp);
void xoa4(char* text1,char* text2,int& choose,int chooseNow,int nRow,int& is_click_filter,int& is_click_text1,int& is_click_text2,BUTTON& LOC2,BUTTON& XEM);
void inform(int& s,int sub_tt,char* CID_text, int& print_s);
void inform1(int& s,int sub_tt,char* SID_text, int& print_s);
void inform2(int& s,int sub_tt,char* subjID, int& print_s);
bool is_delete(char* text,int i);
void clear_notice_classi4();
void clear_notice_stui4();
void clear_notice_subji4();
void clear_edit_classi4(char* CID_text,char* CName_text,int idx_start_TL);
void clear_edit_stui4(char* SID_text,char* LName_text,int idx_start_LN,char* FName_text,int idx_start_FN,char* PW_text);
void reset_classi4(char* CID_text, int& cursor_pos_ML,char* CName_text,int& cursor_pos_TL,int& idx_TL,int& idx_start_TL);
void reset_stui4(char* SID_text, int& cursor_pos_MSV,int& cursor_pos_LN,char* LName_text,int& idx_LN,int& idx_start_LN,char* FName_text, int& cursor_pos_FN,int& idx_FN,int& idx_start_FN, char* sex, char* PW_text,int& cursor_pos_PW);
void reset_subji4(char* SID_text, int& cursor_pos_MMH,char* SName_text,int& cursor_pos_TMH,int& idx_TMH,int& idx_start_TMH);
void set_bar_edit_classi4(int bdr_color);
void set_bar_edit_stui4(int bdr_color);
void set_bar_edit_subji4(int bdr_color);
void clear_edit_subji4(char* SID_text,char* SName_text,int idx_start_TMH);
void set_buttons_Thi_TN(BUTTON& exit, BUTTON& Enter, BUTTON& subjID, BUTTON& page_after,BUTTON& page_before,AREA& nQuest_bar,AREA& nMinute_bar);
void xoa5(char* subjID_text,char* nQuest,char* nMinute,int &choose, int chooseNow,int nRow,int& is_click_MMH,BUTTON& THI);
void set_hover_Thi_TN(BUTTON* Menu,int nMenu,int &hover,int& j,int tt,int x,int y,BUTTON& Enter,BUTTON buttons[],int nRow);
void set_buttons_Thi_TN_2(BUTTON Questions[],BUTTON& submit,AREA& page_after, AREA& page_before,AREA& Quest_after, AREA& Quest_before,CTick DA[]);
void print_text(int x, int y, char* text, int limit,int color);
void set_buttons_xem_KQ(BUTTON Questions[],AREA& page_after, AREA& page_before,AREA& Quest_after, AREA& Quest_before,CTick DA[]);
void set_buttons_quesList(BUTTON& exit,rowTable* ROWTBs,int page,int nRow,BUTTON& pageA, BUTTON& pageB,int nPageTable, BUTTON& bar_search,BUTTON& clear, AREA& ND, AREA &A, AREA &B,AREA& C,AREA& D,BUTTON& THEM, BUTTON &LUU,BUTTON& XOA,BUTTON& subClear,AREA& pageArea, BUTTON& Return,CTick DAPAN[]);
void inform6(int& s,int sub_tt,char* ID, int& print_s);
void xoa6(BUTTON& bar_search,char* search_text,int idx_start_search , char* ND,int &idx_start_ND,char* A, int& idx_start_A, char* B, int &idx_start_B,char* C,int& idx_start_C,char* D,int &idx_start_D, int& choose,int chooseNow,char* page_text, int page_tmp);
void clear_notice_quesi4();
void set_bar_edit_quesi4(int bdr_color);
void clear_edit_quesi4(char* ND,int idx_start_ND,char* A,int idx_start_A,char* B,int idx_start_B,char* C,int idx_start_C,char* D,int idx_start_D);
void reset_quesi4(char* ND,int& cursor_pos_ND,int& idx_start_ND,int &idx_ND,char* A, int& cursor_pos_A,int& idx_start_A,int& idx_A,char* B, int& cursor_pos_B,int& idx_start_B,int& idx_B, char* C, int& cursor_pos_C,int& idx_start_C,int& idx_C,char* D, int& cursor_pos_D,int& idx_start_D,int& idx_D,char& da);
#endif

