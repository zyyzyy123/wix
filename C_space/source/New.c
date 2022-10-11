#include "..\header\wix_program.h"
/*
function:
�����ļ��С��ļ�,argv[1]·�����Ϸ����ļ��в�����ʱʧ��,����ɹ�

input:
argv[1]:target_path  
argv[2]:1(����),0(���Խ���)

output:
0(ʧ��),1(�ɹ�)
*/
int main(int argc,char* argv[]){
    
    if(argc<3)return 0;                                         //�����в�������
    if(!strlen(argv[1]))return 0;                               //argv[1]Ϊ�� 
    if(strcmp(argv[2],"0"))return 0;                            //argv[2]��Ϊ"0"
    
    char Target_Path[_MAX_PATH];
    char Target_Ext[_MAX_EXT];
    hdll = LoadLibraryA(DLL_wix_path);                        //���ض�̬��

    GetFullPathNameA(argv[1],_MAX_PATH,Target_Path,NULL);       //�õ�ȫ·��
//    _splitpath(Target_Path,NULL,NULL,NULL,Target_Ext);          //�õ���׺
    
//   if(!strlen(Target_Ext)){                                    //�жϺ�׺  
	if(Target_Path[strlen(Target_Path)-1]=='\\'){
        CreateDF = (DLLFUNC_1)GetProcAddress(hdll, "CreateDoc");//���غ���
    }
    else{
        CreateDF = (DLLFUNC_1)GetProcAddress(hdll, "CreateFL"); //���غ���
    }
    int Back=CreateDF(Target_Path);
    FreeLibrary(hdll);                                          //�ͷż��صĶ�̬��
    return Back;                         
}