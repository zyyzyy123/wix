#include "../header/wix_program.h"
/*function:
创建文件夹、文件,argv[1]路径不合法或父文件夹不存在时失败,否则成功

input:
argv[1]:target_path  
argv[2]:Lei(1(强行创建文件),2(强行创建目录),0(自动模式))

output:
0(失败),1(成功)
*/
int main(int argc,char *argv[]){
	
	//检查参数个数
	if(argc<New_ArgsNum_Min||strlen(argv[Target])==0){
		Err_Echo(DEBUG_New,"%s:return 0,num of args is too few\n",__FILE__);
		return 0;
	}
	
	//获得wix库的绝对路径	
	char Buf[PATH_MAX]="";
	if(readlink("/proc/self/exe",Buf,PATH_MAX)==-1){
		Err_Echo(DEBUG_New,"%s:return 0,get lib path err(%s)\n",__FILE__,strerror(errno));
		return 0;
	}
	dirname(Buf);
	strcat(Buf,DLL_wix_path);
	
	//加载wix库
	void *handle=dlopen(Buf,RTLD_LAZY);
	if(handle==NULL){
		Err_Echo(DEBUG_New,"%s:return 0,load lib err(%s)\n",__FILE__,dlerror());
		return 0;
	}



	DLLFUNC_1 Create=NULL;
	if(strcmp(argv[Lei],"1")==0){
//强制创建文件
		*(void **) (&Create) = dlsym(handle, "CreateFL");
	}		
	else if(strcmp(argv[Lei],"2")==0){
//强制创建目录
		*(void **) (&Create) = dlsym(handle, "CreateDoc");
	}
	else if(strcmp(argv[Lei],"0")==0){
//自动模式(通过判断最后一个字符是否为/，可以用Dir_simple先预判一下，降低创建错误率)
		if(argv[Target][strlen(argv[Target])-1]=='/'){
			*(void **) (&Create) = dlsym(handle, "CreateDoc");
		}
		else{
			*(void **) (&Create) = dlsym(handle, "CreateFL");
		}
	}
	else{
//其他错误参数
		Err_Echo(DEBUG_New,"%s:return 0,mode args is wrong\n",__FILE__);
		return 0;
	}
		
//检查库函数是否加载成功
	if(Create==NULL){
		Err_Echo(DEBUG_New,"%s:return 0,load function err\n",__FILE__);
		return 0;
	}

//执行库函数
	int Back=0;
	Back=Create(argv[Target]);
	Err_Echo(DEBUG_New,"%s:return %d\n",__FILE__,Back);
	dlclose(handle);
	return Back;
}
