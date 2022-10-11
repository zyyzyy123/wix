#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <windows.h>
#define DEBUG_dir_simple 0
#define DEBUG_Open 0
#define DLL_wix_path "..\\DLL\\wix.dll"                                         //wix.dll相对路径
#define Etc_file_path "/../../etc/File.txt"                                     //File配置文件相对路径
#define Etc_doc_path "/../../etc/Doc.txt"                                       //Doc配置文件相对路径
HINSTANCE hdll;                                                                 //加载DLL所用到的句柄
typedef int(* DLLFUNC_1)(char *);                                               //函数指针类型
typedef int(* DLLFUNC_2)(char [],char [],char [],int);
DLLFUNC_1 check_dir;                                                            //指向DLL中check_dir函数的指针
DLLFUNC_1 CreateDF;                                                             //指向DLL中CreateDF函数的指针
DLLFUNC_2 CommandLine;                                                          //指向DLL中CommandLine函数的指针