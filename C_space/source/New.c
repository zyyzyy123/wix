#include "..\header\wix_program.h"
/*
function:
创建文件夹、文件,argv[1]路径不合法或父文件夹不存在时失败,否则成功

input:
argv[1]:target_path  
argv[2]:1(不建),0(尝试建立)

output:
0(失败),1(成功)
*/
int main(int argc,char* argv[]){
    
    if(argc<3)return 0;                                         //命令行参数过少
    if(!strlen(argv[1]))return 0;                               //argv[1]为空 
    if(strcmp(argv[2],"0"))return 0;                            //argv[2]不为"0"
    
    char Target_Path[_MAX_PATH];
    char Target_Ext[_MAX_EXT];
    hdll = LoadLibraryA(DLL_wix_path);                        //加载动态库

    GetFullPathNameA(argv[1],_MAX_PATH,Target_Path,NULL);       //得到全路径
//    _splitpath(Target_Path,NULL,NULL,NULL,Target_Ext);          //得到后缀
    
//   if(!strlen(Target_Ext)){                                    //判断后缀  
	if(Target_Path[strlen(Target_Path)-1]=='\\'){
        CreateDF = (DLLFUNC_1)GetProcAddress(hdll, "CreateDoc");//加载函数
    }
    else{
        CreateDF = (DLLFUNC_1)GetProcAddress(hdll, "CreateFL"); //加载函数
    }
    int Back=CreateDF(Target_Path);
    FreeLibrary(hdll);                                          //释放加载的动态库
    return Back;                         
}