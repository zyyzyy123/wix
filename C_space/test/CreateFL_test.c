#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include <dlfcn.h>
#include <fcntl.h>
#define DLL_Path "/home/zyy/我的程序/wix_tool/DLL/wix.so"
//int CreateFL(char* Target_Path){
///* 	创建rw-rw-r--文件
// */
//	int fd=open(Target_Path,O_CREAT|O_EXCL,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
//	if(fd==-1){
//		#if DEBUG_CreateFL
//		printf("the path is err or path exist or you don't have authority\n");
//		#endif
//		return 0;
//	}
//	else{
//		#if DEBUG_CreateFL
//		printf("%s\n",Target_Path);
//		#endif
//		close(fd);
//		return 1;
//	}
//}
typedef int(* DLLFUNC_1)(char *);
int main(int argc,char *argv[]){
//这里的路径解析明显与windows系统相同，都是把命令行当前路径当成起始路径
	DLLFUNC_1 CreateFL;
	void *handle=NULL;
	handle=dlopen(DLL_Path,RTLD_LAZY);
	if(handle==NULL){
		printf("err\n");
		printf("%s\n",dlerror());
		return -1;
	}
//	check_dir=(DLLFUNC_1)dlsym(handle,"check_dir");
        *(void **) (&CreateFL) = dlsym(handle, "CreateFL");
	printf("return for CreateFL:%d\n",CreateFL(argv[1]));
	dlclose(handle);
}
