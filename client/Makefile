client: client.o com.o client_chat.o client_board.o client_user.o client_manage.o
	gcc -o client client.o com.o client_chat.o client_board.o client_user.o client_manage.o

client.o: client.c 
	gcc -c -o client.o client.c

com.o: com.c
	gcc -c -o com.o com.c

client_chat.o: client_chat.c
	gcc -c -o client_chat.o client_chat.c

client_board.o: client_board.c
	gcc -c -o client_board.o client_board.c	

client_manage.o: client_manage.c
	gcc -c -o client_manage.o client_manage.c	

client_user.o: client_user.c
	gcc -c -o client_user.o client_user.c	

clean: 
	rm *.o client