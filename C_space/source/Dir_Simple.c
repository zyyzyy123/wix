#include "../header/wix_program.h"
/*function:
查看路径为目录或文件

input:
argv[1]:target_path

output:
1(文件),2(目录),0(不存在)
*/


int main(int argc, char *argv[]){
	
	//检查参数个数
	if(argc<Dir_Simple_ArgsNum_Min||strlen(argv[Target])==0){
		Err_Echo(DEBUG_Dir_Simple,"%s:return 0,num of args is too few\n",__FILE__);
		return 0;
	}

	//获得wix库的绝对路径	
	char Buf[PATH_MAX]="";
	if(readlink("/proc/self/exe",Buf,PATH_MAX)==-1){
		Err_Echo(DEBUG_Dir_Simple,"%s:return 0,get lib path err(%s)\n",__FILE__,strerror(errno));
		return 0;
	}
	dirname(Buf);
	strcat(Buf,DLL_wix_path);
	
	//加载wix库
	void *handle=dlopen(Buf,RTLD_LAZY);
	if(handle==NULL){
		Err_Echo(DEBUG_Dir_Simple,"%s:return 0,load lib err(%s)\n",__FILE__,dlerror());
		return 0;
	}
	
	//执行check_dir
	DLLFUNC_1 check_dir=NULL;
        *(void **) (&check_dir) = dlsym(handle, "check_dir");
	int Back=0;
	Back=check_dir(argv[Target]);
	Err_Echo(DEBUG_Dir_Simple,"%s:return %d\n",__FILE__,Back);
	
	//关闭wix库
	dlclose(handle);
	return Back;
}
