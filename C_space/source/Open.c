#include "..\header\wix_program.h"
#define  Lei 2
#define cmd 0
#define process 1
#define  Target_Path 1
#define  EXC 3
#define  EXCp 4
/*
function:
���ļ���Ŀ¼

input:
argv[1]:target_path  
argv[2]:Lei "0"(����),"1"(�ļ�),"2"(Ŀ¼)
argv[3]:EXC
argv[4]:EXCp


output:
��

*/
int File_Doc_Open(char argv[][_MAX_PATH]);
int Read_etc(char argv[][_MAX_PATH],int *Pattern);//����:-1(��ִ�д򿪲���),-2(�����ļ�����),0(Ĭ����ƥ����),1(ƥ�䵽�ض���)

int main(int argc,char* argv[]){
    int i;
    char arg_temp[5][_MAX_PATH];
    
    for(i=0;i<5;i++){                                                                       //�õ������в���
        if(i<argc){strcpy(arg_temp[i],argv[i]);}
        else{arg_temp[i][0]='\0';}
    }

    if(strlen(arg_temp[Target_Path])){
        GetFullPathNameA(argv[Target_Path],_MAX_PATH,arg_temp[Target_Path],NULL);           //�õ�ȫ·��
    }
    else{
        return 0;
    }

    
    if( (!strcmp(arg_temp[Lei],"1")) ||                                                     
        (!strcmp(arg_temp[Lei],"2")) ){
        hdll = LoadLibraryA(DLL_wix_path);                                                  //���ض�̬��
        File_Doc_Open(arg_temp);                                                            //���ļ����ļ���
        FreeLibrary(hdll);                                                                  //�ͷż��صĶ�̬��
    }
    else{
    }
}

int File_Doc_Open(char argv[][_MAX_PATH]){
    int Pattern=process;                                                                    //��ģʽ,Ĭ��Ϊprocess
    if(Read_etc(argv,&Pattern)>=0){                                                         //��ȡ�����ļ�
        CommandLine=(DLLFUNC_2)GetProcAddress(hdll, "CommandLine");                         //���غ���
        return CommandLine(argv[EXC],argv[EXCp],argv[Target_Path],Pattern);
    }
}

int Read_etc(char argv[][_MAX_PATH],int *Pattern){
    FILE *fp=NULL;                                                                         //�ļ�ָ��
    char Etc_path[_MAX_PATH];                                                              //�����ļ�·������
    GetModuleFileNameA(NULL,Etc_path,_MAX_PATH);                                           //�õ�������·��
    if(!strcmp(argv[Lei],"1")){strcat(Etc_path,Etc_file_path);}                            //ƴ��File������·��
    else if(!strcmp(argv[Lei],"2")){strcat(Etc_path,Etc_doc_path);}                        //ƴ��Doc������·��
    fp=fopen(Etc_path,"r");                                                                //�������ļ�
    if(fp==NULL){
    #if DEBUG_Open
    printf("err_etc\n");   
    #endif
    return -2;                                                                              //�����ļ�����
    }

    char Temp[_MAX_PATH];                                                                   //�ļ���������
    while(feof(fp)==0){                                                                     //Ѱ��ƥ����
        Temp[0]='\0';
        fscanf(fp,"%*[^\n]s");fgetc(fp);                                                    //����һ��
        fscanf(fp,"%[^|\n]s",Temp);                                                         //��ȡ������

        #if DEBUG_Open
        printf("Temp:%s,%d   EXC:%s,%d\n",Temp,strlen(Temp),argv[EXC],strlen(argv[EXC]));
        printf("point:%d\n",ftell(fp));
        #endif

        if(!strcmp(Temp,argv[EXC])){

        #if DEBUG_Open
        printf("yes\n");
        #endif

        break;}                                                                             //ƥ�䵽������,��������
    }

    if(feof(fp)!=0){                                                                        //�����ļ�β,û�ҵ�ƥ����
        fclose(fp);
        return 0;
    }

    fgetc(fp);fscanf(fp,"%[^|\n]s",Temp);                                                   //��ȡDo,N��ִ�д�,*Ϊ��ת��
    if(!strcmp(Temp,"N")){fclose(fp);return -1;}

    fgetc(fp);fscanf(fp,"%[^|\n]s",Temp);                                                   //��ȡEXC_Out,*Ϊ��ת��
    if(!strcmp(Temp,"*")){}
    else{strcpy(argv[EXC],Temp);}

    fgetc(fp);fscanf(fp,"%[^|\n]s",Temp);                                                   //��ȡEXCp_Out,*Ϊ��ת��
    if(!strcmp(Temp,"*")){}
    else{strcpy(argv[EXCp],Temp);}

    fgetc(fp);fscanf(fp,"%[^|\n]s",Temp);                                                   //��ȡPattern,*Ϊ��ת��,cmdΪsystem�򿪷�ʽ,processΪ���̴򿪷�ʽ
    if(!strcmp(Temp,"*")){}
    else if(!strcmp(Temp,"cmd")){*Pattern=cmd;}
    else if(!strcmp(Temp,"process")){*Pattern=process;}
    
    fclose(fp);
    return 1;                                                                               //������,�ر��ļ�ָ��
}

#undef  Lei
#undef cmd
#undef process
#undef  Target_Path
#undef  EXC
#undef  EXCp
