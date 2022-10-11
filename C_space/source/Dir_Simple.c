#include "..\header\wix_program.h"
/*function:
查看路径为目录或文件

input:
argv[1]:target_path

output:
1(文件),2(目录),0(不存在)
*/

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 0;                                             //参数过少
    if (strchr(argv[1], '?') != NULL || strchr(argv[1], '*') != NULL)
    {                                                         //含非法字符
        return 0;
    }
    
    char Target_Path[_MAX_PATH];
    hdll = LoadLibraryA(DLL_wix_path);                        //加载动态库
    check_dir = (DLLFUNC_1)GetProcAddress(hdll, "check_dir"); //加载函数
    
    GetFullPathNameA(argv[1], _MAX_PATH, Target_Path, NULL);  //得到全路径

#if DEBUG_dir_simple
    printf("Dir_simple:%s\n", argv[1]);
    printf("Dir_simple:%s\n", Target_Path);                   //调试
#endif

    int Back = check_dir(Target_Path);
    FreeLibrary(hdll);                                        //释放加载的动态库

#if DEBUG_dir_simple
    printf("Dir_simple:%d\n", Back);                          //调试
#endif

    return Back;
}
