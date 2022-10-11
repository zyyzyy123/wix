#include<stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <windows.h>
#define BUILD_DLL
#include "wix.h"
EXPORT int check_dir(char* Target_Path){
    if(access(Target_Path,F_OK)!=0){
        return 0;
    }
    else{
        FILE *P=fopen(Target_Path,"r");
        if(P==NULL){return 2;}
        else{
			fclose(P);
			if(Target_Path[strlen(Target_Path)-1]=='\\')return 0;
			return 1;}
    }
}


EXPORT int CreateFL(char* Target_Path){
    FILE* P=NULL;
    P=fopen(Target_Path,"w");
    if(P!=NULL){fclose(P);return 1;}
    else{return 0;}
}

EXPORT int CreateDoc(char* Target_Path){
    if(CreateDirectoryA(Target_Path,NULL)){return 1;}
    else{return 0;}
}

EXPORT int CommandLine(char argv_EXC[],char argv_EXCp[],char argv_Target_Path[],int select){
    STARTUPINFO si={sizeof(si)};
    PROCESS_INFORMATION pi;
    char Command[_MAX_PATH*4];Command[0]='\0';
    strcat(Command,argv_EXC);strcat(Command," ");
    strcat(Command,argv_EXCp);strcat(Command," ");
    Q_Path(argv_Target_Path,argv_Target_Path);
    strcat(Command,argv_Target_Path);
    switch (select)
    {
    case 0:
        strcat(Command," 2>nul");
        system(Command);
        break;
    case 1:
        CreateProcessA(NULL,Command,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);
        break;
    default:
        break;
    }
    #if DEBUG_Command
    printf("Command:%s\n",Command);                         							//ต๗สิ                                   
    #endif   
    return 0;
}

EXPORT int Q_Path(char Path_in[],char Path_out[]){
    char temp[_MAX_PATH]="\"";
    strcat(temp,Path_in);
    strcat(temp,"\"");
    strcpy(Path_out,temp);
}