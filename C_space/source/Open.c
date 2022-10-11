#include "..\header\wix_program.h"
#define  Lei 2
#define cmd 0
#define process 1
#define  Target_Path 1
#define  EXC 3
#define  EXCp 4
/*
function:
打开文件或目录

input:
argv[1]:target_path  
argv[2]:Lei "0"(不打开),"1"(文件),"2"(目录)
argv[3]:EXC
argv[4]:EXCp


output:
无

*/
int File_Doc_Open(char argv[][_MAX_PATH]);
int Read_etc(char argv[][_MAX_PATH],int *Pattern);//返回:-1(不执行打开操作),-2(配置文件错误),0(默认无匹配项),1(匹配到特定项)

int main(int argc,char* argv[]){
    int i;
    char arg_temp[5][_MAX_PATH];
    
    for(i=0;i<5;i++){                                                                       //得到命令行参数
        if(i<argc){strcpy(arg_temp[i],argv[i]);}
        else{arg_temp[i][0]='\0';}
    }

    if(strlen(arg_temp[Target_Path])){
        GetFullPathNameA(argv[Target_Path],_MAX_PATH,arg_temp[Target_Path],NULL);           //得到全路径
    }
    else{
        return 0;
    }

    
    if( (!strcmp(arg_temp[Lei],"1")) ||                                                     
        (!strcmp(arg_temp[Lei],"2")) ){
        hdll = LoadLibraryA(DLL_wix_path);                                                  //加载动态库
        File_Doc_Open(arg_temp);                                                            //打开文件或文件夹
        FreeLibrary(hdll);                                                                  //释放加载的动态库
    }
    else{
    }
}

int File_Doc_Open(char argv[][_MAX_PATH]){
    int Pattern=process;                                                                    //打开模式,默认为process
    if(Read_etc(argv,&Pattern)>=0){                                                         //读取配置文件
        CommandLine=(DLLFUNC_2)GetProcAddress(hdll, "CommandLine");                         //加载函数
        return CommandLine(argv[EXC],argv[EXCp],argv[Target_Path],Pattern);
    }
}

int Read_etc(char argv[][_MAX_PATH],int *Pattern){
    FILE *fp=NULL;                                                                         //文件指针
    char Etc_path[_MAX_PATH];                                                              //配置文件路径变量
    GetModuleFileNameA(NULL,Etc_path,_MAX_PATH);                                           //得到本程序路径
    if(!strcmp(argv[Lei],"1")){strcat(Etc_path,Etc_file_path);}                            //拼接File配置项路径
    else if(!strcmp(argv[Lei],"2")){strcat(Etc_path,Etc_doc_path);}                        //拼接Doc配置项路径
    fp=fopen(Etc_path,"r");                                                                //打开配置文件
    if(fp==NULL){
    #if DEBUG_Open
    printf("err_etc\n");   
    #endif
    return -2;                                                                              //配置文件出错
    }

    char Temp[_MAX_PATH];                                                                   //文件读缓冲区
    while(feof(fp)==0){                                                                     //寻找匹配项
        Temp[0]='\0';
        fscanf(fp,"%*[^\n]s");fgetc(fp);                                                    //跳过一行
        fscanf(fp,"%[^|\n]s",Temp);                                                         //读取行首项

        #if DEBUG_Open
        printf("Temp:%s,%d   EXC:%s,%d\n",Temp,strlen(Temp),argv[EXC],strlen(argv[EXC]));
        printf("point:%d\n",ftell(fp));
        #endif

        if(!strcmp(Temp,argv[EXC])){

        #if DEBUG_Open
        printf("yes\n");
        #endif

        break;}                                                                             //匹配到行首项,跳出行首
    }

    if(feof(fp)!=0){                                                                        //读到文件尾,没找到匹配项
        fclose(fp);
        return 0;
    }

    fgetc(fp);fscanf(fp,"%[^|\n]s",Temp);                                                   //读取Do,N不执行打开,*为不转化
    if(!strcmp(Temp,"N")){fclose(fp);return -1;}

    fgetc(fp);fscanf(fp,"%[^|\n]s",Temp);                                                   //读取EXC_Out,*为不转化
    if(!strcmp(Temp,"*")){}
    else{strcpy(argv[EXC],Temp);}

    fgetc(fp);fscanf(fp,"%[^|\n]s",Temp);                                                   //读取EXCp_Out,*为不转化
    if(!strcmp(Temp,"*")){}
    else{strcpy(argv[EXCp],Temp);}

    fgetc(fp);fscanf(fp,"%[^|\n]s",Temp);                                                   //读取Pattern,*为不转化,cmd为system打开方式,process为进程打开方式
    if(!strcmp(Temp,"*")){}
    else if(!strcmp(Temp,"cmd")){*Pattern=cmd;}
    else if(!strcmp(Temp,"process")){*Pattern=process;}
    
    fclose(fp);
    return 1;                                                                               //正常打开,关闭文件指针
}

#undef  Lei
#undef cmd
#undef process
#undef  Target_Path
#undef  EXC
#undef  EXCp
