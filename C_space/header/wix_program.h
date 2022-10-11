#ifndef WIX_PROGRAM_H
#define WIX_PROGRAM_H
#include<dlfcn.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<limits.h>
#include<stdarg.h>
#include<libgen.h>
#include<errno.h>

//argv位置
#define Target 1
#define Lei 2
#define EXC 3
#define EXCp 4

//argv参数最少数量
#define Dir_Simple_ArgsNum_Min 2
#define Open_ArgsNum_Min 3
#define New_ArgsNum_Min 3

//调试
#define DEBUG_Dir_Simple 0
#define DEBUG_New 0
#define DEBUG_Open 0
#define DEBUG_Read_etc 0
int Err_Echo(int debug,const char *fmt,...);

//DLL
#define DLL_wix_path "/../DLL/wix.so"
typedef int(* DLLFUNC_1)(char *);
typedef int(* DLLFUNC_2)(char *[],int);
//etc 
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
	//Read_etc 读取配置文件，返回值：0(没找到),1(找到了),-1(设备错误)
int Read_etc(Etc_line * Ptrmsg,int Select);



#endif 
