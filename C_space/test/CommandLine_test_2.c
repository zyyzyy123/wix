#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <stdlib.h>
#include<string.h>
#include<sys/wait.h>
#define DLL_Path "/home/zyy/我的程序/wix_tool/DLL/wix.so"
typedef int(* DLLFUNC_2)(char *[],int);
//int CommandLine(char *argv[],int select);
int main(int argc,char *argv[]){

	DLLFUNC_2 CommandLine;
	void *handle=NULL;
	handle=dlopen(DLL_Path,RTLD_LAZY);
	if(handle==NULL){
		printf("load lib err\n");
		printf("%s\n",dlerror());
		return -1;
	}
        *(void **) (&CommandLine) = dlsym(handle, "CommandLine");
	char *test[]={"vim",argv[1],NULL};
	CommandLine(test,0);
	dlclose(handle);
}

/*
int CommandLine(char *argv[],int select){
const int mode_num=2,mode_first=0;
	int i=0;

	//检查select模式是否存在
	if(select >= mode_num || select < mode_first){
		#if DEBUG_CommandLine	
		printf("%s:主进程%d,no such select_mode\n",__func__,getpid());
		#endif

		return 0;	
	}
//fork
	pid_t chlid_pid=fork();	
	
	if(chlid_pid<0){
//主进程fork失败
		#if DEBUG_CommandLine
		printf("%s:主进程%d,fork err\n",__func__,getpid());
		#endif
	}
	else if(chlid_pid==0){
//子进程
		#if DEBUG_CommandLine
		printf("%s:执行子进程%d,开始执行:\n",__func__,getpid());
		while(argv[i]!=NULL){
			printf(" (%s)",argv[i]);
			i=i+1;
		}
		printf("。\n");
		#endif
		
//		if(strcmp(argv_EXCp,"")==0){execlp(argv_EXC,argv_EXC,argv_Target_Path,(char *)0);}
//		else{execlp(argv_EXC,argv_EXC,argv_EXCp,argv_Target_Path,(char *)0);}
		execvp(argv[0],argv);
		//当装载程序替换子进程失败时会向下执行,否则子进程就在这里结束

		#if DEBUG_CommandLine
		printf("%s:执行子进程%d,执行任务失败\n",__func__,getpid());
		#endif
	}
	else{	
//主进程fork成功
		//命令行独占启动模式
		if(select==0){
			#if DEBUG_CommandLine
			printf("%s:主进程%d,wait for 子进程\n",__func__,getpid());
			#endif

			while(waitpid(chlid_pid,NULL,WUNTRACED | WCONTINUED)<0){}

			#if DEBUG_CommandLine
			printf("%s:主进程%d,子进程结束\n",__func__,getpid());
			#endif
		}
		//独立进程启动模式
		else if(select==1){
			#if DEBUG_CommandLine
			printf("%s:主进程%d,已独立启动子进程\n",__func__,getpid());
			#endif
		}
	}
	return 0;	
}
*/
