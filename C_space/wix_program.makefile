app :
	gcc -o bin\Dir_Simple source\Dir_Simple.c
	gcc -o bin\New source\New.c
	gcc -o bin\Open source\Open.c
clean :
	del bin\Dir_Simple.exe
	del bin\New.exe
	del bin\Open.exe
	