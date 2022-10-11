#ifndef WIX_H
#define WIX_H
#define DEBUG_check_dir 0
#define DEBUG_CreateFL 0
#define DEBUG_CreateDoc 0
#define DEBUG_CommandLine 0
int check_dir(char* Target_Path);
/*
function:	看路径为目录或文件
input:		target_path(全路径或相对路径)
output:		1(文件),2(目录),0(不存在)
*/
int CreateFL(char* Target_Path);
/*
function:	创建文件,路径不合法或父文件夹不存在时失败,否则成功
input:		target_path(全路径)
output:		0(失败),1(成功)
*/
int CreateDoc(char* Target_Path);
/*
function:	创建目录,路径不合法或父文件夹不存在时失败,否则成功
input:		target_path(全路径)
output:		0(失败),1(成功)
*/
int CommandLine(char *argv[],int select);
/*	
function:	执行命令
input:		argv[]命令字串组
		select选择模式(0:命令行独占启动模式,1:独立进程启动模式)
output:		无意义
*/
#endif
