#include "../header/test.h"



	
int main(int argc,char *argv[]){
	// Etc_line msg;
	// msg.EXCp_Out=NULL;
	// msg.EXC_Out=NULL;
	// msg.EXC_In=argv[1];
	// int Back=Read_etc(&msg,2);
	// if(Back==1){
	// 				if(msg.EXCp_Out==NULL||msg.EXC_Out==NULL)printf("err\n");
	// 				printf("main:\n");
	// 				printf("%s\tEXC_in\n",msg.EXC_In);
	// 				printf("%s\tEXC_Out\n",msg.EXC_Out);
	// 				printf("%s\tEXCp_Out\n",msg.EXCp_Out);
	// 				printf("%d\tEXCp_Out_Num\n",msg.EXCp_Out_num);
	// 				printf("%d\tDo\n",msg.Do);
	// 				printf("%d\tPattern\n",msg.Pattern);
	// 				free(msg.EXC_Out);
	// 				free(msg.EXCp_Out);
	// }
	// else if(Back==0){
	// }
/*	char *m=strdup("");
	char *dupm=m;
	char *temp=NULL;
	while((temp=strsep(&dupm," "))!=NULL)printf("%s\n",temp);
	free(m);*/
	printf("enter main\n");
	pid_t child_pid=fork();
	if(child_pid<0){
		printf("fork err\n");
	}
	else if(child_pid==0){

		int ret=fcntl(2,F_SETFD,FD_CLOEXEC);
		if(ret==-1){
			perror("fcntl err\n");
		}
		ret=fcntl(1,F_SETFD,FD_CLOEXEC);
		if(ret==-1){
			perror("fcntl err\n");
		}
		ret=fcntl(0,F_SETFD,FD_CLOEXEC);
		if(ret==-1){
			perror("fcntl err\n");
		}
		int val;
		val =execlp("notepadqq","notepadqq","./arg_test.c",NULL);
		if(val==-1){
		perror("execlp err\n");
		}
		
	}
	else{
		while(waitpid(child_pid,NULL,WUNTRACED | WCONTINUED)<0){}
		printf("exit main\n");
	}
	return 0;
}
