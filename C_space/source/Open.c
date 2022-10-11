#include "../header/wix_program.h"
/*
function:
打开文件或目录

input:
argv[1]:target_path  
argv[2]:Lei "0"(不打开),"1"(文件),"2"(目录)
argv[3]:EXC
argv[4..n]:EXCp[]
output:
无
*/

int main(int argc,char *argv[]){

//---------------------------------------检查阶段-------------------------------------------------
	//检查参数个数,值
	if(argc<Open_ArgsNum_Min||strlen(argv[Target])==0){
		Err_Echo(DEBUG_Open,"%s,num of args is too few\n",__FILE__);
		return 0;
	}
	int Select=0;
	if(strcmp(argv[Lei],"1")==0){
		Select=1;
	}
	else if(strcmp(argv[Lei],"2")==0){
		Select=2;
	}
	else{
		Err_Echo(DEBUG_Open,"%s,argv[Lei] is wrong\n",__FILE__);
		return 0;
	}
//----------------------------------------查找配置阶段----------------------------------------------
	//查找配置信息
	Etc_line msg;char empty[2]="";
	msg.Pattern=1;//没找到匹配项的情况下独立进程启动
	if(argc==Open_ArgsNum_Min){
		msg.EXC_In=empty;
	}
	else{
		msg.EXC_In=argv[EXC];
	}
	int Find=Read_etc(&msg,Select);
	
	//读取配置文件失败
	if(Find==-1){
		Err_Echo(DEBUG_Open,"%s,read etc err\n",__FILE__);
		return 0;
	}
	//配置文件要求不执行打开动作
	if((Find==1)&&(msg.Do==0)){
		Err_Echo(DEBUG_Open,"%s,do nothing\n",__FILE__);
		return 0;
	}
//----------------------------------加载函数-------------------------------------------------------
	//获得wix库的绝对路径	
	char Buf[PATH_MAX]="";
	if(readlink("/proc/self/exe",Buf,PATH_MAX)==-1){
		Err_Echo(DEBUG_Open,"%s,get lib path err(%s)\n",__FILE__,strerror(errno));
		return 0;
	}
	dirname(Buf);
	strcat(Buf,DLL_wix_path);
	
	//加载wix库
	void *handle=dlopen(Buf,RTLD_LAZY);
	if(handle==NULL){
		Err_Echo(DEBUG_Open,"%s,load lib err(%s)\n",__FILE__,dlerror());
		return 0;
	}
	
	//获取CommandLine函数
	DLLFUNC_2 CommandLine;
	*(void **) (&CommandLine) = dlsym(handle, "CommandLine");
	if(CommandLine==NULL){
		Err_Echo(DEBUG_Open,"%s,load CommadLine err\n",__FILE__);
		return 0;
	}
	
//----------------------------------生成执行信息---------------------------------------------------------
	int i=0;
	//声明指针
	char **ptrBuf=NULL;
	int lenth=0;
	char *Temp_EXCp_Out=NULL;
	
	if((Find==1)&&(msg.EXCp_Out_num>=0)){
	//分配内存 EXC_out+EXCp_Out_num+target+NULL
		lenth=1+msg.EXCp_Out_num+1+1;
	}
	else{
	//分配内存 EXC_in+(argc-open-target-Lei-EXC_in)+target+NULL
		lenth=1+(argc-4)+1+1;
		if(lenth<3){
			lenth=3;
		}
	}
	
	ptrBuf=(char **)malloc(sizeof(char *)*lenth);
	
	//填充
	//EXC位
	if((Find==1)&&(strcmp(msg.EXC_Out,"*")!=0)){
		ptrBuf[0]=msg.EXC_Out;
	}
	else{
		ptrBuf[0]=msg.EXC_In;
	}
	//EXCp[]组
	//计算公式i-1=j-EXCp
	if((Find==1)&&(msg.EXCp_Out_num>=0)){
		Temp_EXCp_Out=msg.EXCp_Out;
		for(i=1;i<=lenth-3;i++){
			ptrBuf[i]=strsep(&Temp_EXCp_Out," ");
		}
	}
	else{
		for(i=1;i<=lenth-3;i++){
			ptrBuf[i]=argv[i-1+EXCp];
		}
	}
	//target
	ptrBuf[lenth-2]=argv[Target];
	//最后一位填NULL
	ptrBuf[lenth-1]=NULL;
//----------------------------------------执行CommanLine-------------------------------------------
	CommandLine(ptrBuf,msg.Pattern);
//----------------------------------------清理内存--------------------------------------------------	
	if(Find==1){
		free(msg.EXC_Out);
		free(msg.EXCp_Out);
	}
	dlclose(handle);
	free(ptrBuf);
}