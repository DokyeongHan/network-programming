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
struct userInfo{
    char ID[20];
    char PW[20];
    char NAME[10];
};

struct socketInfo{
    struct sockaddr_in clntAddr;
    int sockfd;
};

struct roomUserList{
    char ID[20];
    struct socketInfo so;
};

struct roomList{
    char room_name[30];
    struct roomUserList roomUserList[50];
};

struct userInfo u1;
struct socketInfo s1;
struct roomList roomList[3000];
char roomname[30];


// com.c
void receive_packet(char *packet);
void create_packet(char type, char mode, char *data ,char *buf);
void send_packet(int sockfd, char *buf, struct sockaddr_in clntAddr);

// server_chat.c

// server_board.c

// server_manage.c
void server_manage_room();
void server_manage_board();

// server_user.c
void server_login(struct userInfo);
void server_signup(struct userInfo u1);

// server.c