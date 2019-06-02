#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <pthread.h>

#define BUFSIZE 1024

struct userInfo{
    char ID[20];
    char PW[20];
    char NAME[10];
};

struct socketInfo{
    int sock;
    struct sockaddr_in clntAddr;
};

struct roomUserList{
    struct userInfo userInfo;
    struct socketInfo socketInfo;
};

struct roomList{
    char room_name[30];
    struct roomUserList roomUserList[50];
};

struct userInfo u1;
struct socketInfo s1;
struct roomList *roomList;
char buffer[BUFSIZE+1];
char buffer2[BUFSIZE+1];
char room_name[100];
int room_idx;
int sock;

int shmid;  

// com.c
void receive_packet(char *packet);
void create_packet(char type, char mode, char *data ,char *buf);
void send_packet(int sockfd, char *buf, struct sockaddr_in clntAddr);

// server_chat.c
void server_chat(char *message);
void server_choice_chat_room(char *roomname);
void server_room_search(char *buff);
void server_room_follow(char *buff);
void server_chat2();

// server_board.c
void server_post_act(char CRUD);
void server_comment_act(char CRUD);

// server_manage.c
void server_manage_room(char *CRUD, char *roomname);
void server_manage_board(char *CRUD, char *roomname);

// server_user.c
void server_login();
void server_signup();

// server.c


	// while(tag==0) {
	// 	// accept
	// 	if((clnt_sock = accept(serv_sock,(struct sockaddr*)&clntAddr, &clntAddrLen))<0) {
	// 		perror("Error:accepting failed!");
	// 		exit(1);
	// 	}
	// 	pid = fork();
	// 	if(pid==0){

	// 		//read & write	
	// 		while((len = read(clnt_sock, buffer, MAXBUF))!=0)
	// 		{				
	// 			write(clnt_sock, string, strlen(string));
	// 			printf("RECEIVED : %s\n", buffer);

	// 			sleep(1);
	// 			write(clnt_sock, buffer, len);
	// 			len = read(clnt_sock, buffer, MAXBUF);
	// 			buffer[len]=0;
	// 			printf("CLIENT : %s\n", buffer);
	// 			if(!strcmp(buffer,"quit")) {
	// 				memset(buffer,0,sizeof(buffer));
	// 				tag =1;	
	// 			}
	// 			memset(buffer,0,sizeof(buffer));
	// 		}
	// 	}
	// 	if(pid==-1){
	// 		perror("fork error: ");
	// 		return 1;
	// 	}
	// }
	// close(clnt_sock);
	// return 0;