#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include <dlfcn.h>
#include <fcntl.h>
#define DLL_Path "/home/zyy/我的程序/wix_tool/DLL/wix.so"
#define DEBUG_CreateDoc 1
typedef int(* DLLFUNC_1)(char *);
int main(int argc,char *argv[]){
//这里的路径解析明显与windows系统相同，都是把命令行当前路径当成起始路径
	DLLFUNC_1 CreateDoc;
	void *handle=NULL;
	handle=dlopen(DLL_Path,RTLD_LAZY);
	if(handle==NULL){
		printf("err\n");
		printf("%s\n",dlerror());
		return -1;
	}
        *(void **) (&CreateDoc) = dlsym(handle, "CreateDoc");
	printf("return for CreateDoc:%d\n",CreateDoc(argv[1]));
	dlclose(handle);
}
