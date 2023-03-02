#include "prcstring.h"
void upper_chr( char& chr){
	if( chr<='z'&&chr>='a') chr = chr -'a'+'A';
}
void lower_chr( char& chr){
	if( chr<='Z'&&chr>='A') chr = chr -'A'+'a';
}
void upper_str( char* str){
	if(str == NULL) return;
	for( int i=0; str[i]!='\0'; i++) upper_chr(str[i]);
}
void delete_blks_str_first( char* str){// xoa khoang trang o dau
	if(str == NULL) return;
	while( *str == ' ') strcpy( str, str + 1);
}
void delete_blks_str(char* str){ //xoa tat ca khoang trang
	if(str==NULL) return;
	while( *str != '\0'){
		while( *str == ' ') strcpy(str,str+1);
		if( *str != '\0') str++;
	}
}
void delete_blks_str_last( char* str){// xoa khaong trang o cuoi
	if(str==NULL) return;
	int len = strlen(str);
	if(len>0)
		while(str[len-1]==' ') str[--len]= '\0';
}
void fix_str1( char* str){ //xoa space dau cuoi, dinh dang chuoi vd:Cao Thanh Nhan
	if(str==NULL) return;
	delete_blks_str_last( str);
	while( *str!='\0'){
		delete_blks_str_first(str);
		if( *str!='\0') upper_chr( *str++);
		while( *str !=' ' && *str != '\0') lower_chr(*str++);
		if( *str==' ') str++;
	}		
}
void fix_str2(char* str){//xoa all space, dinh dang chuoi vd:N19DCCN125
	if(str==NULL) return;
	delete_blks_str_last(str);
	delete_blks_str_first(str);
	upper_chr(*str);
	while( *str!='\0'){
		while( *(++str) !=' ' && *str != '\0');
		if( *str==' ') {
			str++;
		    delete_blks_str_first(str);
		}
	}		
}
int str_is_alpAndNum( char* str){//kiem tra 1 chuoi co gom ca so va chu hay k
	if(str==NULL) return -1; // return -1 if str = NULL
	for( int i=0; str[i]!='\0'; i++){
		if(str[i]>='A'&&str[i]<='Z'||str[i]>='a'&&str[i]<='z'||str[i]>='0'&&str[i]<='9')
		   continue;
		else return 0;   
	}
	return 1;
}
void insert_chr_to_str( char* str, char chr, int idx){// chen ki tu vao chuoi tai 1 vi tri 
	if(str==NULL) return;
	int len = strlen(str);
	for(int i=len; i>idx; i--) str[i]=str[i-1];
	str[idx]=chr;
	str[len+1] = '\0'; 
}




