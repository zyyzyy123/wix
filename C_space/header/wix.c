#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include "wix.h"
int check_dir(char* Target_Path){
	struct stat sb;
/*
	这里选用fstat不用lstat,因为fstat返回的stat struct针对于链接文
	指向的是实际文件的inode,而不是软链接的inode
*/
	int fd=open(Target_Path,__O_PATH);
	if(fd==-1){
		#if DEBUG_check_dir
		printf("%s:Path err\n",__func__);
		#endif
		return 0;
	}

	fstat(fd,&sb);
	close(fd);

	#if DEBUG_check_dir
	printf("%s:%s exist,the type is:",__func__,Target_Path);
	switch (sb.st_mode & S_IFMT) {
		case S_IFBLK:  printf("block device\n");            break;
		case S_IFCHR:  printf("character device\n");        break;
		case S_IFDIR:  printf("directory\n");               break;
		case S_IFIFO:  printf("FIFO/pipe\n");               break;
		case S_IFLNK:  printf("symlink\n");                 break;
		case S_IFREG:  printf("regular file\n");            break;
		case S_IFSOCK: printf("socket\n");                  break;
		default:       printf("unknown?\n");                break;
	}
	#endif
	
	switch (sb.st_mode & S_IFMT) {
/*		目录
*/
		case S_IFDIR:	
			return 2;
/*		文件
*/
		default:
			return 1;
	}

}

int CreateFL(char* Target_Path){
/* 	创建rw-rw-r--文件
 */
	int fd=open(Target_Path,O_CREAT|O_EXCL,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	if(fd==-1){
		#if DEBUG_CreateFL
		printf("%s:Path err or Path exist or you don't have authority\n",__func__);
		#endif
		return 0;
	}
	else{
		#if DEBUG_CreateFL
		printf("%s:Create %s File sucessfully\n",__func__,Target_Path);
		#endif
		close(fd);
		return 1;
	}
}

int CreateDoc(char* Target_Path){
    if(mkdir(Target_Path,S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH)==-1){
//创建失败
	#if DEBUG_CreateDoc	
	printf("%s:Path err or Path exist or You don't have authority\n",__func__);
	#endif
	return 0;
	}
    else{
	#if DEBUG_CreateDoc	
	printf("%s:Create %s Directory sucessfully\n",__func__,Target_Path);
	#endif
	return 1;
	}
}

int CommandLine(char *argv[],int select){

	const int mode_num=2,mode_first=0;

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
		int i=0;
		while(argv[i]!=NULL){
			printf(" (%s)",argv[i]);
			i=i+1;
		}
		printf("。\n");
		#endif
		
		//在独立进程模式中,关闭exec进程的的标准输入输出和错误输出流到终端
		if(select==1){
			if((fcntl(0,F_SETFD,FD_CLOEXEC)==-1)||(fcntl(1,F_SETFD,FD_CLOEXEC)==-1)||(fcntl(2,F_SETFD,FD_CLOEXEC)==-1)){
				#if DEBUG_CommandLine
				printf("%s:执行子进程:fcntl err\n",__func__,getpid());
				#endif	
			}
		}
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
