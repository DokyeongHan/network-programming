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

void *t_function(){
	char buf[BUFF_SIZE+1];
	int server_addr_size;
	server_addr_size = sizeof(s1.servAddr);

	while(1){
		memset(buf, 0, BUFF_SIZE);
		read(s1.sock, buf, BUFF_SIZE);
		receive_packet(buf);
	}
}

int main( int argc, char **argv)
{
	int   server_addr_size;
	struct sockaddr_in server_addr;

	
	int shmid;
    void *shmaddr;
    struct shmid_ds shm_stat;

	//TCP 연결
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

	// client_manage_room('C');
	// 시작
	start();
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
