#ifndef _PROCESS_CSTRING 
#define _PROCESS_CSTRING
#define decimal 10 
#include <string.h>
void upper_chr( char& chr);
void lower_chr( char& chr);
void upper_str(char* str);
void delete_blks_str_first( char* str);
void delete_blks_str_last( char* str);
void fix_str1(char* str);
void fix_str2(char* str);
void insert_chr_to_str( char* str, char chr, int idx);
void delete_blks_str(char* str);
#endif
