/*
최초작성자: 

최초작성일: 

최초변경일: 2019-03-24

프로그램 목적: UDP echo 클라이언트 프로그램 

개정이력: 
(2019-03-24)  표준코딩 규칙 적용 

저작권: 5조
*/ 

#include "header.h"

#define BUFF_SIZE 1024

void print_post(){

        if (runQuery("select title, content from posts limit 5") < 0) {
                return -2;
        }

        printf("%+50s   %-15s \n", "title", "content");
        while ((row = mysql_fetch_row(res)) != NULL )
        {
                printf("%+50s   %-15s", row[0], row[1]);
                printf("\n");
        }

}

void header_main_logo() {
  system("clear");
  logo_head();
  printf("%70s, Hello !\n", u1.ID);
}

void *t_function(){
	char buf[BUFF_SIZE+1];
	int server_addr_size;
	server_addr_size = sizeof(s1.servAddr);

	while(1){
		memset(buf, 0, BUFF_SIZE);
		recvfrom(s1.sock, buf, BUFF_SIZE, 0 , (struct sockaddr*)&s1.servAddr, &server_addr_size);
		receive_packet(buf);
	}
}

int main( int argc, char **argv)
{
	// int   sock;
	int sel;
  int loginflag = 0;
	int tag1 = 0, tag2 = 0 , tag3 = 0;
	int   server_addr_size;
	struct sockaddr_in server_addr;
	char buff_rcv[BUFF_SIZE+1];
	char buff_snd[BUFF_SIZE+1];
	char data[BUFF_SIZE+1];
	int test;
	pthread_t firstThread;
	
	int shmid;
    void *shmaddr;
    struct shmid_ds shm_stat;

	//TCP
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		printf("socket 생성 실패\n");
    	exit(1);	
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family     = AF_INET;
	server_addr.sin_port       = htons(50000);
	server_addr.sin_addr.s_addr= inet_addr("127.0.0.1");

	if( -1 == connect( sock, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
	{
		printf("접속 실패\n");
		exit( 1);
	}
	s1.sock = sock;
	s1.servAddr = server_addr;
  
  printf("success\n");
  start_1();

  if (connectDB() < 0) {
    printf("DB Connect fail\n");
    return -1;
  }

  // UI 시작
	while(tag1 == 0){
    system("clear");
    logo_head();
		start();
		scanf("%d", &sel);
		// while (getchar() != '\n');


    // case -1 : 퇴장 / 1 : 회원가입 / 2 : 로그인
    switch(sel) {
      case -1:
        tag1 = -1;
        break;
      case 1:
        join();
        break;
      case 2:
        login();
        loginflag = client_login();
        if(loginflag == 1) {
          header_main_logo();
          sleep(1);

          while(tag2 == 0) {
            ls();
            scanf("%d", &sel);

            // case 1 : 채팅방 / 2 : 게시판
            switch(sel) {
              case 1:
                header_main_logo();
                chatroom();
                print_post();

                scanf("%d", &sel);
                break;
              case 2:
                header_main_logo();
                board();

                scanf("%d", &sel);
                break;
            }
          }
        }
        // login fail
        else {
          printf("Login fail\n");
        }
    }
	}
  printf("why?\n");

  closeDB();

	// pthread_create(&firstThread, NULL, t_function, NULL);
	// while(1){
	// 	client_login();
	// 	// client_signup();
	// 	// client_manage_room('C');
	// 	// client_choice_chat_room();

	// 	// while(1){
	// 	// 	client_chat();
	// 	// }
	// 		// client_post_act('C');
	// 		// client_comment_act('C');
	// 		// client_manage_room('C');
	// 		// client_manage_board('C');
	// 		// client_room_search();
	// 		// client_room_follow();
	// }
	// close( sock);

	// UDP
	// // init (server) addr_size	
	// server_addr_size  = sizeof(server_addr);
	
	// // Build local (server) socket address
	// memset(&server_addr, 0, server_addr_size);
	// server_addr.sin_family     = AF_INET;
	// server_addr.sin_port       = htons(50000);
	// server_addr.sin_addr.s_addr= inet_addr("127.0.0.1");
	
	
	// // Create socket
	// if((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
	// 	printf( "socket 생성 실패\n");
	// 	exit( 1);
	// }

	// while(1){
	// 	memset(buff_rcv, 0, sizeof(buff_rcv));
		
	// 	client_login();
	// 	// client_signup();
	// 	client_choice_chat_room();
	// 	while(1){
	// 		client_chat();
	// 	}
	// 	// client_post_act('C');
	// 	// client_comment_act('C');
	// 	// client_manage_room('C');
	// 	// client_manage_board('C');
	// 	// client_room_search();
	// 	// client_room_follow();

	// 	// // Send echo string
	// 	// test = sendto(sock, buff_snd, strlen(buff_snd)+1, 0,    // +1: NULL까지 포함해서 전송
	// 	// 			(struct sockaddr*)&server_addr, sizeof(server_addr));
		
	// 	// Receive echo string
	// 	// recvfrom(sock, buff_rcv, BUFF_SIZE, 0 , (struct sockaddr*)&server_addr, &server_addr_size);
				
	// 	// Print echoed string
	// 	// printf("receive: %d\n", buff_rcv[2]);
	// 	// sleep(1);
	// }
		
	// // Close the socket
	// close(sock);
	
	// // Stop the program
	// return 0;
}
/*
수정한 부분
1. 코드 첫 부분에 최초작성자, 작성일, 변경일 등 주석 추가.
2. main 내의 코드에 주석 추가.
3. 시작 중괄호 위치 변경. 
4. BUFF_SIZE 256 에서 1024 로 변경
5. Create socket 에서 socket() 을 if 문에 넣어 Bind socket 과 일관성을 맞춤.
6. Create socket 의 if(-1 == socket()) 을 if((sock = socket()) < 0) 로 변경.
7. Bind socket 의 if(-1 == bind()) 를 if(bind() <0) 로 변경.
8. Create socket 의 위치를 뒤로 이동.
9. Create socket 에서 ("socket 생성 실패n" => "socket 생성 실패\n") 으로 오타수정.
10. sizeof( server_addr) 가 쓰이는 곳을 server_addr_size 로 대체함. 
*/ 
