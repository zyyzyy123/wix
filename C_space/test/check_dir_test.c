#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include <dlfcn.h>
#define DLL_Path "/home/zyy/我的程序/wix_tool/DLL/wix.so"
typedef int(* DLLFUNC_1)(char *);
int main(int argc,char *argv[]){
//这里的路径解析明显与windows系统相同，都是把命令行当前路径当成起始路径
	DLLFUNC_1 check_dir;
	void *handle=NULL;
	handle=dlopen(DLL_Path,RTLD_LAZY);
	if(handle==NULL){
		printf("err\n");
		printf("%s\n",dlerror());
		return -1;
	}
//	check_dir=(DLLFUNC_1)dlsym(handle,"check_dir");
        *(void **) (&check_dir) = dlsym(handle, "check_dir");
	printf("文件类别:%d\n",check_dir(argv[1]));
	dlclose(handle);
}
