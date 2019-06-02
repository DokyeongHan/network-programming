client: client.o com.o client_chat.o client_board.o client_user.o client_manage.o ui.o
	gcc -pthread -o client client.o com.o client_chat.o client_board.o client_user.o client_manage.o ui.o

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

ui.o: ui.c
	gcc -c -o ui.o ui.c	

clean: 
	rm *.o client