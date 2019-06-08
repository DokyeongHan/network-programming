#include "header.h"
#define BUFF_SIZE 1024

//시작 선택 화면
void start(){
	system("clear");
	logo_head();
	printf("시작 화면\n");
	printf("--------------------\n\n");
	printf(" 1. 회원가입\n\n");
	printf(" 2. 로그인\n\n");
	printf("-1. 프로그램 종료\n\n");  
	printf("--------------------\n\n");
	printf("원하는 작업을 입력 하세요 : ");
	scanf("%d", &sel);
	while (getchar() != '\n');
	if(sel == -1){
		exit(-1);
	}
	else if(sel == 1){
		join();
	}
	else if(sel == 2){
		login();
	}
}

//회원가입
void join(){
	char ID[BUFF_SIZE+1];
	char PW[BUFF_SIZE+1];
	char NAME[BUFF_SIZE+1];

	memset(ID, 0, BUFF_SIZE);
	memset(PW, 0, BUFF_SIZE);
	memset(NAME, 0, BUFF_SIZE);
	
	system("clear");
	logo_head();
	printf("회원가입\n");
	printf("--------------------\n\n");
	printf("1. ID : ");
	scanf("%s", ID);
	printf("\n\n");
	while (getchar() != '\n');
	printf("2. PW : ");
	scanf("%s", PW);
	printf("\n\n");
	printf("3. Name : ");
	scanf("%s", NAME);
	printf("\n\n");
	printf("--------------------\n\n");
	sel = client_signup(ID, PW, NAME);
	if(sel == 0){
		printf("join failed\n");
		sleep(1);
		join();
	}
	else if(sel == 1){
		printf("join success\n");
		sleep(1);
		start();
	}
}

//로그인
void login(){
	char ID[BUFF_SIZE+1];
	char PW[BUFF_SIZE+1];

	memset(ID, 0, BUFF_SIZE);
	memset(PW, 0, BUFF_SIZE);
	
	system("clear");
	logo_head();
	printf("로그인\n");
	printf("--------------------\n\n");
    printf("   ID : ");
    scanf("%s", ID); 
    printf("\n\n");
   	printf("   PW : ");
    scanf("%s", PW); 
    printf("\n\n");
	printf("--------------------\n\n");
	sel = client_login(ID, PW);
	if(sel == 0){
		printf("login failed\n");
		sleep(1);
		login();
	}
	else if(sel == 1){
		sleep(1);
		ls();
	}
	else if(sel == 2){
		sleep(1);
		manage();
	}	
}

// 관리자 화면
void manage(){
	system("clear");
	logo_head2();
	printf("--------------------\n\n");
	printf(" 1. 채팅방 생성  \n\n");
	printf(" 2. 게시판 관리  \n\n");
	printf("-1. 로그아웃  \n\n");
	printf("--------------------\n\n");
	printf("원하는 작업을 입력 하세요 : ");
	scanf("%d", &sel);
	while (getchar() != '\n');
	if(sel == -1){
		start();
	}
	else if(sel == 1){
		manage_room();
	}
	else if(sel == 2){
		manage();
	} 
	else{
		manage();
	}
}

// 채팅방 생성 화면
void manage_room(){
	char roomname[BUFF_SIZE+1];
	memset(roomname, 0, BUFF_SIZE);
	system("clear");
	logo_head2();
	printf("--------------------\n\n");
	client_manage_room('R');
	printf("\n\n");
	printf("-1. 뒤로가기\n\n");	
	printf("--------------------\n\n");
	printf("생성할 방의 이름을 입력하세요 : ");
	sel = client_manage_room('C');
	if(sel = 1){
		manage();
	}
	else if(sel == 0){
		manage_room();
	}
	else if(sel == -1){
		manage();
	}
}

//로그인 성공시
void ls(){
	system("clear");
	logo_head2();
	printf("--------------------\n\n");
	printf(" 1. 채팅  \n\n");
	printf(" 2. 게시판  \n\n");
	printf("-1. 로그아웃  \n\n");
	printf("--------------------\n\n");
	printf("원하는 작업을 입력 하세요 : ");
	scanf("%d", &sel);
	while (getchar() != '\n');
	if(sel == -1){
		start();
	}
	else if(sel == 1){
		chatroom();
	}
	else if(sel == 2){
		board();
	} 
	else{
		ls();
	}
}

//채팅
void chatroom(){
	system("clear");
	logo_head2();
	printf(" 채팅\n");
	printf("--------------------\n\n");
	printf(" 1. 전체 채팅방  \n\n");
	printf(" 2. 팔로우한 채팅방  \n\n");
	printf(" 3. 채팅방 검색  \n\n");
	printf("-1. 뒤로가기  \n\n");
	printf("--------------------\n\n");
	printf("원하는 작업을 입력 하세요 : ");
	scanf("%d", &sel);
	while (getchar() != '\n');
	if(sel == -1){
		ls();
	}
	else if(sel == 1){
		allchatroom();
	}
	else if(sel == 2){
		client_search_room_follow();
	}
	else if(sel == 3){
		client_room_search();
	}
	else{
		chatroom();
	}
}

//게시판
void board(){
	system("clear");
	logo_head2();
	printf("게시판\n");
	printf("--------------------\n\n");
	printf(" 1. 자유 게시판  \n\n");
	printf(" 2. 정보 게시판  \n\n");
	printf(" 3. 홍보 게시판  \n\n");
	printf("-1. 뒤로가기  \n\n");
	printf("--------------------\n\n");
	printf("원하는 작업을 입력 하세요 : ");
	scanf("%d", &sel);
	while (getchar() != '\n');
	if(sel == -1){
		ls();
	}
	else if(sel == 1){
		board_idx = sel;
		post1();
	}
	else if(sel == 2){
		board_idx = sel;
		post1();
	}
	else if(sel == 3){
		board_idx = sel;
		post1();
	}
	else{
		board();
	}
}

//전체 채팅방
void allchatroom(){
	char roomname[BUFF_SIZE+1];

	memset(roomname, 0, BUFF_SIZE);

	system("clear");
	logo_head2();
	printf(" 채팅\n");
	printf("--------------------\n\n");
	printf("전체 채팅방\n\n");
	client_manage_room('R');
	printf("-1. 뒤로가기  \n\n");
	printf("--------------------\n\n");
	printf("입장할 채팅방의 이름을 입력하세요: ");
	scanf("%s", roomname);
	if(!strncmp(roomname, "-1", 2)){
        chatroom();
    }
	else{
		sel = client_choice_chat_room(roomname);
		if(sel = 1){
			room();
		}
		else{
			allchatroom();
		}
	}
}

// 채팅방
void room(){
	char message[BUFF_SIZE+1];
	system("clear");
	logo_head3();
	printf("--------------------\n\n");
	while(1){
		memset(message, 0, BUFF_SIZE);
		scanf(" %[^\n]s", message);
		if(!strncmp(message, "-1", 2)){
			int status;			
			kill(pidd, SIGINT);			
			close(recv_sock);
			wait(&status);
      		exit(1);
   		}
		else{
			client_chat(message);
		}
	}
}

//팔로우한 채팅방
void followchatroom(){
	char roomname[BUFF_SIZE+1];

	memset(roomname, 0, BUFF_SIZE);
	system("clear");
	logo_head2();
	printf(" 채팅\n");
	printf("--------------------\n\n");
	printf("팔로우한 채팅방\n\n");
	client_room_follow('R', roomname);
	printf("-2. 팔로우 하기  \n\n");
	printf("-1. 뒤로가기  \n\n");
	printf("--------------------\n\n");
	printf("입장할 채팅방의 이름을 입력하세요: ");
	scanf("%s", roomname);
	if(!strncmp(roomname, "-1", 2)){
        chatroom();
    }
	else if(!strncmp(roomname, "-2", 2)){
		client_room_follow(roomname);
	}
	else{
		sel = client_choice_chat_room(roomname);
		if(sel == 1){
			room();
		}
		else{
			followchatroom();
		}		
	}
}

//채팅방 팔로우
void follow(char *room1){
	char roomname[BUFF_SIZE+1];

	memset(roomname, 0, BUFF_SIZE);
	system("clear");
	logo_head2();
	printf(" 채팅\n");
	printf("--------------------\n\n");
	printf("채팅방 팔로우\n\n");
	printf("-1. 뒤로가기  \n\n");
	printf("--------------------\n\n");
	printf("팔로우 할 수업 이름을 입력하세요 : ");
	scanf("%s", roomname);
	if(!strncmp(roomname, "-1", 2)){
        chatroom();
    }
	else{
		client_room_follow('C', roomname);
		followchatroom();
	}
}

//채팅방 검색
//채팅방 검색
void chatroomsearch(){
   char roomname[BUFF_SIZE+1];

   memset(roomname, 0, BUFF_SIZE);
   system("clear");
   logo_head2();
   printf(" 채팅\n");
   printf("--------------------\n\n");
   printf("채팅방 검색\n\n");
   printf("-1. 뒤로가기  \n\n");
   printf("--------------------\n\n");
   printf("검색 할 수업 이름을 입력하세요 : ");
   scanf("%s", roomname);
   if(!strncmp(roomname, "-1", 2)){
        chatroom();
    }
   else{
      client_room_search(roomname);
      searchroom(roomname);
   }
}

// 검색된 채팅방
void searchroom(char * room1){
	char roomname[BUFF_SIZE+1];

	memset(roomname, 0, BUFF_SIZE);

	system("clear");
	logo_head2();
	printf("채팅\n");
	printf("--------------------\n\n");
	printf("검색된 채팅방\n\n");
	client_room_search(room1);
	printf("-1. 뒤로가기  \n\n");
	printf("--------------------\n\n");
	printf("검색할 채팅방의 이름을 입력하세요: ");
	scanf("%s", roomname);
	if(!strncmp(roomname, "-1", 2)){
        chatroom();
    }
	else{
		searchroom(roomname);
	}
}

//게시글 목록
void post1(){
	// char post[BUFF_SIZE]; // post index
	system("clear");
	logo_head2();
	printf("게시글 목록\n");
	printf("--------------------\n\n");
	client_post_act('R', board_idx, 0, 0);
	printf("--------------------\n\n");
	printf("-2. 글쓰기 \n\n");
	printf("-1. 뒤로가기  \n\n");
	scanf("%d", &post_idx);
	while (getchar() != '\n');
	if(post_idx == -1){
        board();
    }
	else if(post_idx == -2){
		mkpost();
	}
	else{
		post1();
	}
}

//게시글
void post2(){
	system("clear");
	logo_head2();
	printf("--------------------\n\n");
	printf("1. Title \n\n");
	printf("Description \n\n");
	printf("--------------------\n\n");
	printf("Comment \n\n");
	printf("1. Comment \n\n");
	printf("-1. 뒤로가기  \n\n");
}

//게시글 작성
void mkpost(){
	char Title[BUFF_SIZE+1];
	char Description[BUFF_SIZE+1];

	memset(Title, 0, BUFF_SIZE);
	memset(Description, 0, BUFF_SIZE);

	system("clear");
	logo_head2();
	printf("게시글 작성\n");
	printf("--------------------\n\n");
	printf("1. Title : ");
	scanf(" %[^\n]s", Title);
	printf("\n\n");
	printf("2. Description : ");
	scanf(" %[^\n]s", Description);
	printf("\n\n");
	printf("--------------------\n\n");
	sel = client_post_act('C', board_idx, Title, Description);

	if(sel == 1){
		post1();
	}
	else if(sel == 0){
		post1();
	}
}

//LECTIO 로고 print
void start_1() {
  printf("-----------------------------------------------------------\n");
  printf("------#-------######---#####----#######---###-----####-----\n");
  printf("-----#-------#-------##-----------#-------#-----#----#-----\n");
  printf("----#-------######--#------------#-------#-----#----#------\n");
  printf("---#-------#-------##-----------#-------#-----#----#-------\n");
  printf("--######--######----#####------#------###-----####---------\n");
  printf("-----------------------------------------------------------\n");
  sleep(1);
  system("clear");
  start_2();
}

void start_2() {
  printf("                                                           \n");
  printf("------#-------######---#####----#######---###-----####-----\n");
  printf("-----#-------#-------##-----------#-------#-----#----#-----\n");
  printf("----#-------######--#------------#-------#-----#----#------\n");
  printf("---#-------#-------##-----------#-------#-----#----#-------\n");
  printf("--######--######----#####------#------###-----####---------\n");
  printf("-----------------------------------------------------------\n");
  sleep(1);
  system("clear");
  start_3();
}

void start_3() {
  printf("                                                           \n");
  printf("      #       ######   #####    #######   ###     ####     \n");
  printf("-----#-------#-------##-----------#-------#-----#----#-----\n");
  printf("----#-------######--#------------#-------#-----#----#------\n");
  printf("---#-------#-------##-----------#-------#-----#----#-------\n");
  printf("--######--######----#####------#------###-----####---------\n");
  printf("-----------------------------------------------------------\n");
  sleep(1);
  system("clear");
  start_4();
}

void start_4() {
  printf("                                                          \n");
  printf("      #       ######   #####    #######   ###     ####    \n");
  printf("     #       #       ##           #       #     #    #    \n");
  printf("----#-------######--#------------#-------#-----#----#------\n");
  printf("---#-------#-------##-----------#-------#-----#----#-------\n");
  printf("--######--######----#####------#------###-----####---------\n");
  printf("-----------------------------------------------------------\n");
  sleep(1);
  system("clear");
  start_5();
}

void start_5() {
  printf("                                                          \n");
  printf("      #       ######   #####    #######   ###     ####    \n");
  printf("     #       #       ##           #       #     #    #    \n");
  printf("    #       ######  #            #       #     #    #     \n");
  printf("---#-------#-------##-----------#-------#-----#----#-------\n");
  printf("--######--######----#####------#------###-----####---------\n");
  printf("-----------------------------------------------------------\n");
  sleep(1);
  system("clear");
  start_6();
}

void start_6() {
  printf("                                                          \n");
  printf("      #       ######   #####    #######   ###     ####    \n");
  printf("     #       #       ##           #       #     #    #    \n");
  printf("    #       ######  #            #       #     #    #     \n");
  printf("   #       #       ##           #       #     #    #      \n");
  printf("--######--######----#####------#------###-----####---------\n");
  printf("-----------------------------------------------------------\n");
  sleep(1);
  system("clear");
  start_7();
}

void start_7() {
  printf("                                                          \n");
  printf("      #       ######   #####    #######   ###     ####     \n");
  printf("     #       #       ##           #       #     #    #     \n");
  printf("    #       ######  #            #       #     #    #      \n");
  printf("   #       #       ##           #       #     #    #       \n");
  printf("  ######  ######    #####      #      ###     ####         \n");
  printf("-----------------------------------------------------------\n");
  sleep(1);
  system("clear");
  start_8();
}

void start_8() {
  printf("                                                          \n");
  printf("      #       ######   #####    #######   ###     ####     \n");
  printf("     #       #       ##           #       #     #    #     \n");
  printf("    #       ######  #            #       #     #    #      \n");
  printf("   #       #       ##           #       #     #    #       \n");
  printf("  ######  ######    #####      #      ###     ####         \n");
  printf("                                                           \n");
  system("clear");
}

void logo_head() {
  printf("┎──────────────────────────────────────────────────────────────────────────────┒\n");
  printf("┃                                                                              ┃\n");
  printf("┃                #       ######   #####    #######   ###     ####              ┃\n");
  printf("┃               #       #       ##           #       #     #    #              ┃\n");
  printf("┃              #       ######  #            #       #     #    #               ┃\n");
  printf("┃             #       #       ##           #       #     #    #                ┃\n");
  printf("┃            ######  ######    #####      #      ###     ####                  ┃\n");
  printf("┃                                                                              ┃\n");
  printf("┃                                                                              ┃\n");
  printf("┃                                                                              ┃\n");
  printf("┃                                                  Created by Team 5           ┃\n");
  printf("┃                                                Goo, Ahn, Song, Han           ┃\n");
  printf("┃                                                                              ┃\n");
  printf("┖──────────────────────────────────────────────────────────────────────────────┚\n");
}

void logo_head2() {
  printf("┎──────────────────────────────────────────────────────────────────────────────┒\n");
  printf("┃                                                                              ┃\n");
  printf("┃                #       ######   #####    #######   ###     ####              ┃\n");
  printf("┃               #       #       ##           #       #     #    #              ┃\n");
  printf("┃              #       ######  #            #       #     #    #               ┃\n");
  printf("┃             #       #       ##           #       #     #    #                ┃\n");
  printf("┃            ######  ######    #####      #      ###     ####                  ┃\n");
  printf("┃                                                                              ┃\n");
  printf("┃                                                                              ┃\n");
  printf("┃                                                                              ┃\n");
  printf("┃                                                  Created by Team 5           ┃\n");
  printf("┃                                                Goo, Ahn, Song, Han           ┃\n");
  printf("┃                                                                              ┃\n");
  printf("┖──────────────────────────────────────────────────────────────────────────────┚\n");
  printf("ID: %s    NAME: %s \n", u1.ID, u1.NAME);
}

void logo_head3() {
  printf("┎──────────────────────────────────────────────────────────────────────────────┒\n");
  printf("┃                                                                              ┃\n");
  printf("┃                #       ######   #####    #######   ###     ####              ┃\n");
  printf("┃               #       #       ##           #       #     #    #              ┃\n");
  printf("┃              #       ######  #            #       #     #    #               ┃\n");
  printf("┃             #       #       ##           #       #     #    #                ┃\n");
  printf("┃            ######  ######    #####      #      ###     ####                  ┃\n");
  printf("┃                                                                              ┃\n");
  printf("┃                                                                              ┃\n");
  printf("┃                                                                              ┃\n");
  printf("┃                                                  Created by Team 5           ┃\n");
  printf("┃                                                Goo, Ahn, Song, Han           ┃\n");
  printf("┃                                                                              ┃\n");
  printf("┖──────────────────────────────────────────────────────────────────────────────┚\n");
  printf("ID: %s    NAME: %s  room: %s\n", u1.ID, u1.NAME, room_name);
}