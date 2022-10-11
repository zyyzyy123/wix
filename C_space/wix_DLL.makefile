DLL\wix.dll : header\wix.c
	gcc -shared -o DLL\wix.dll header\wix.c
clean :
	del DLL\wix.dll