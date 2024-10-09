server:server.o
	gcc *.o -o $@
%.o:%.c
	gcc -c $< -o $@
	
clear:
	rm *.o server