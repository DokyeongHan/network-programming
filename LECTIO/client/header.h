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
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <pthread.h>

#define BUFSIZE 1024

struct userInfo{
    char ID[20];
    char PW[20];
    char NAME[10];
};

struct socketInfo{
    struct sockaddr_in servAddr;
    int sock;
};

struct userInfo u1;
struct socketInfo s1;
char buffer[BUFSIZE+1];
char buffer2[BUFSIZE+1];
int sock;
char room_name[BUFSIZE+1];


// 게시판, 게시글 위치
int board_idx;
int post_idx;

// 화면전환
int sel;

// 멀티캐스팅 UDP 소켓
int recv_sock;  
int state;  
struct sockaddr_in addr;  
struct ip_mreq join_addr;
pid_t pidd;

// com.c
int receive_packet(char *packet);
void create_packet(char type, char mode, char *data ,char *buf);
void send_packet(int sockfd, char *buf, struct sockaddr_in servAddr);

// client_chat.c
int client_choice_chat_room(char *roomname);
int client_chat(char *message);
void client_chat2(char *name, char *message);
int client_room_search(char *roomname);
void client_room_follow(char CRUD, char *roomname);

// client_board.c
int client_post_act(char CRUD, int idx, char *title, char * description);
void client_comment_act(char CRUD, int idx, int idx2, char *comment);

// client_manage.c
int client_manage_room(char CRUD);
void client_manage_board(char CRUD);

// client_user.c
int client_login(char *ID, char *PW);
int client_signup(char *ID, char *PW, char *NAME);

// ui.c
void start();
void join();
void login();
void ls();
void chatroom();
void board();
void allchatroom();
void followchatroom();
void chatroomsearch();
void post1();
void post2();
void mkpost();
void start_1();
void start_2();
void start_3();
void start_4();
void start_5();
void start_6();
void start_7();
void start_8();
void logo_head();
void logo_head2();
void logo_head3();
void room();
void searchroom(char * room);
void manage_room();
void follow(char *room1);
void manage();

// client.c (main)
