#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<stdarg.h>
#include<limits.h>
#include<string.h>
#include<libgen.h>
//#include<malloc.h>
#define DLL_Path "/home/zyy/我的程序/wix_tool/DLL/wix.so"
typedef int(* DLLFUNC_2)(char *[],int);
#define DEBUG_Dir_Simple 1
#define DEBUG_Read_etc 1
int Err_Echo(int debug,const char *fmt,...);


#define Etc_file_path "/../etc/File.txt"
#define Etc_doc_path "/../etc/Doc.txt"
typedef struct{
	char *EXC_In;
	char *EXC_Out;
	char *EXCp_Out;
	int EXCp_Out_num;
	int Do;
	int Pattern;
}Etc_line;

int Read_etc(Etc_line * Ptrmsg,int Select);
