#include "test.h"
int Err_Echo(int debug,const char *fmt,...){

	if(debug){
		va_list ptr;
		va_start(ptr,fmt);
		vprintf(fmt,ptr);
		va_end(ptr);
	}
	return 0;
}

int Read_etc(Etc_line * Ptrmsg,int Select){
	char Buf[PATH_MAX]="";
	//获得运行程序路径
	if(readlink("/proc/self/exe",Buf,PATH_MAX)==-1){
		Err_Echo(DEBUG_Read_etc,"%s:return -1,get pathname err\n",__func__);
		return -1;
	}
	//获得运行程序所在目录
	dirname(Buf);	
	//拼接etc文件路径
	if(Select==1){
		strcat(Buf,Etc_file_path);
	}
	else if(Select==2){
		strcat(Buf,Etc_doc_path);
	}
	else{
		Err_Echo(DEBUG_Read_etc,"%s:return -1,Select is err\n",__func__);
		return -1;
	}
	Err_Echo(DEBUG_Read_etc,"%s:reading %s\n",__func__,Buf);

	//etc文件指针
	FILE *fp=fopen(Buf,"r");
	if(fp==NULL){
		Err_Echo(DEBUG_Read_etc,"%s:return -1,read etc err\n",__func__);
		return -1;
	}
	//查找匹配项
	int Buf_int=0,i=0,Find=0;
	while(feof(fp)==0){
		//读取首项EXC_in
		Buf[0]='\0';
		fscanf(fp,"%[^\t]s",Buf);
		//找到匹配项
		if(strcmp(Buf,Ptrmsg->EXC_In)==0){
			Find=1;
			break;
		}
		//没找到跳过7个"\n"
		for(i=0;i<7;i++){
			fscanf(fp,"%*[^\n]s");fgetc(fp);
		}
	}

	//对匹配项处理
	if(Find==0){
	}
	else if(Find==1){
		for(i=1;i<=6;i++){		
			switch(i){
				case 1:
					printf("%s\tEXC_in\n",Buf);
					break;
				case 2:
					Buf[0]='\0';
					fscanf(fp,"%[^\t]s",Buf);
					printf("%s\tEXC_Out\n",Buf);
					Ptrmsg->EXC_Out=strdup(Buf);
					break;
				case 3:
					Buf[0]='\0';
					fscanf(fp,"%[^\t]s",Buf);
					printf("%s\tEXCp_Out\n",Buf);
					Ptrmsg->EXCp_Out=strdup(Buf);
					break;
				case 4:
					fscanf(fp,"%d",&Buf_int);
					printf("%d\tEXCp_Out_Num\n",Buf_int);
					Ptrmsg->EXCp_Out_num=Buf_int;
					break;
				case 5:
					fscanf(fp,"%d",&Buf_int);
					printf("%d\tDo\n",Buf_int);
					Ptrmsg->Do=Buf_int;
					break;
				case 6:
					fscanf(fp,"%d",&Buf_int);
					printf("%d\tPattern\n",Buf_int);
					Ptrmsg->Pattern=Buf_int;
					break;
			}
			fgetc(fp);
			fscanf(fp,"%*[^\n]s");
			fgetc(fp);
		}
	}
	
	//返回查找结果
	if(Find==0){
		Err_Echo(DEBUG_Read_etc,"%s:return 0,%s is not found\n",__func__,Ptrmsg->EXC_In);
	}
	else if(Find==1){
		Err_Echo(DEBUG_Read_etc,"%s:return 1,%s is found\n",__func__,Ptrmsg->EXC_In);
	}
	fclose(fp);
	return Find;
}
