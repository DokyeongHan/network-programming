server: server.o com.o server_chat.o server_board.o server_user.o server_manage.o server_odbc.o
	gcc -pthread -o server server.o com.o server_chat.o server_board.o server_user.o server_manage.o server_odbc.o -lmysqlclient -L/database/mysql/lib/mysql

server.o: server.c 
	gcc -c -o server.o server.c

com.o: com.c
	gcc -c -o com.o com.c

server_chat.o: server_chat.c
	gcc -c -o server_chat.o server_chat.c

server_board.o: server_board.c
	gcc -c -o server_board.o server_board.c	

server_manage.o: server_manage.c
	gcc -c -o server_manage.o server_manage.c	

server_user.o: server_user.c
	gcc -c -o server_user.o server_user.c	

server_odbc.o: server_odbc.c
	gcc -D_REENTRANT -D_PTHREADS -Wno-deprecated -fPIC -DOMP_UNIX -c server_odbc.c -I. -I/database/mysql/include

clean: 
	rm *.o server