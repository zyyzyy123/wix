app:
	gcc -o bin/Dir_Simple source/Dir_Simple.c header/wix_program.c -ldl
	gcc -o bin/New source/New.c header/wix_program.c -ldl
	gcc -o bin/Open source/Open.c header/wix_program.c -ldl
clean:
	rm bin/*
