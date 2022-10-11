wix.so : header/wix.c
	gcc -shared -fPIC -o DLL/wix.so header/wix.c
clean:
	rm DLL/wix.so
