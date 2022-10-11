#include "..\header\wix_program.h"
/*function:
�鿴·��ΪĿ¼���ļ�

input:
argv[1]:target_path

output:
1(�ļ�),2(Ŀ¼),0(������)
*/

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 0;                                             //��������
    if (strchr(argv[1], '?') != NULL || strchr(argv[1], '*') != NULL)
    {                                                         //���Ƿ��ַ�
        return 0;
    }
    
    char Target_Path[_MAX_PATH];
    hdll = LoadLibraryA(DLL_wix_path);                        //���ض�̬��
    check_dir = (DLLFUNC_1)GetProcAddress(hdll, "check_dir"); //���غ���
    
    GetFullPathNameA(argv[1], _MAX_PATH, Target_Path, NULL);  //�õ�ȫ·��

#if DEBUG_dir_simple
    printf("Dir_simple:%s\n", argv[1]);
    printf("Dir_simple:%s\n", Target_Path);                   //����
#endif

    int Back = check_dir(Target_Path);
    FreeLibrary(hdll);                                        //�ͷż��صĶ�̬��

#if DEBUG_dir_simple
    printf("Dir_simple:%d\n", Back);                          //����
#endif

    return Back;
}
