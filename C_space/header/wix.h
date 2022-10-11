#ifdef BUILD_DLL
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif
#define DEBUG_Command 0

EXPORT int check_dir(char* Target_Path);
/*
function:查看路径为目录或文件
input:target_path(全路径)
output:1(文件),2(目录),0(不存在)
*/
EXPORT int CreateFL(char* Target_Path);
/*
function:创建文件,路径不合法或父文件夹不存在时失败,否则成功
input:target_path(全路径)
output:0(失败),1(成功)
*/
EXPORT int CreateDoc(char* Target_Path);
/*
function:创建目录,路径不合法或父文件夹不存在时失败,否则成功
input:target_path(全路径)
output:0(失败),1(成功)
*/

EXPORT int CommandLine(char argv_EXC[],char argv_EXCp[],char argv_Target_Path[],int select);
/*
function:创建目录,路径不合法或父文件夹不存在时失败,否则成功
input:target_path(全路径)
output:0(失败),1(成功)
*/                                 
//运行函数,select=cmd/porcess

EXPORT int Q_Path(char Path_in[],char Path_out[]);
/*
function:路径名加""
*/                                 
