#include <stdio.h>
int main(int argc,char *argv[]){
//char *test[]={"gedit","test.c",NULL};
//	CommandLine(test,1);
	printf("argc:%d\n",argc);
	int i=0;
	for(i=0;i<argc;i++){
		printf("argv[%d]:(%s)\n",i,argv[i]);
	}
}
