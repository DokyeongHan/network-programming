/*
최초작성자: 

최초작성일: 

최초변경일: 2019-03-24

프로그램 목적: UDP echo 클라이언트 프로그램 

개정이력: 
(2019-03-24)  표준코딩 규칙 적용 

저작권: 
*/ 

#include "header.h"

#define BUFF_SIZE 1024

int main( int argc, char **argv)
{
	int   sock;
	int   server_addr_size;
	struct sockaddr_in   server_addr;
	char buff_rcv[BUFF_SIZE+1];
	char buff_snd[BUFF_SIZE+1];
	char data[BUFF_SIZE+1];
	int test;
	

	// init (server) addr_size	
	server_addr_size  = sizeof(server_addr);
	
	
	// Build local (server) socket address
	memset(&server_addr, 0, server_addr_size);
	server_addr.sin_family     = AF_INET;
	server_addr.sin_port       = htons(50000);
	server_addr.sin_addr.s_addr= inet_addr("127.0.0.1");
	
	
	// Create socket
	if((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		printf( "socket 생성 실패\n");
		exit( 1);
	}

	// 소켓 정보 저장
	s1.servAddr = server_addr;
    s1.sockfd = sock;
	
	while(1){
		memset(buff_rcv, 0, sizeof(buff_rcv));

		// char CRUD[1];
		// memset(CRUD, 'C', 1);
		// client_manage_board('C');

		

		// // Send echo string
		// test = sendto(sock, buff_snd, strlen(buff_snd)+1, 0,    // +1: NULL까지 포함해서 전송
		// 			(struct sockaddr*)&server_addr, sizeof(server_addr));
		
		// Receive echo string
		recvfrom(sock, buff_rcv, BUFF_SIZE, 0 , 
				(struct sockaddr*)&server_addr, &server_addr_size);
		
		// Print echoed string
		printf("receive: %s\n", buff_rcv);
		sleep(1);
	}
		
	// Close the socket
	close(sock);
	
	// Stop the program
	return 0;
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
