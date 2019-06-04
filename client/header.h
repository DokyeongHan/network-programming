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
#include <mysql/mysql.h>

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

MYSQL_RES *res;
MYSQL_ROW row;
MYSQL *conn;
//DB var

// com.c
int receive_packet(char *packet);
void create_packet(char type, char mode, char *data ,char *buf);
void send_packet(int sockfd, char *buf, struct sockaddr_in servAddr);

// client_chat.c
void client_choice_chat_room();
void client_chat();
void client_chat2(char *message);
void client_room_search();
void client_room_follow();

// client_board.c
void client_post_act(char CRUD);
void client_comment_act(char CRUD);

// client_manage.c
void client_manage_room(char CRUD);
void client_manage_board(char CRUD);

// client_user.c
int client_login();
void client_signup();

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
void start_6();
void start_7();
void start_8();
void logo_head();
// client.c (main)

int runQuery(char *query);
int connectDB();
void closeDB();
void errorMsg(char *errMsg);
int fetchRow(void);
void fetchfieldbyID(int id, char *buffer, int len);
void fetchfieldbyName(const char *name, char *buffer, int len);
//client_odbc.c