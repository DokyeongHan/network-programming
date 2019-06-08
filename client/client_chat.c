/*
최초작성자: 한도경

최초작성일: 2019-05-27

최초변경일: 2019-05-27

프로그램 목적: 채팅방, 채팅, 검색, 팔로우 관련 요청 

개정이력: 
(2019-05-27) client_choice_chat_room, client_chat, 
client_chat_search, client_chat_follow  함수 작성

저작권: 5조
*/

#include "header.h"
#define BUFF_SIZE 1024

// 채팅방 입장 요청
void client_choice_chat_room(){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];
    char roomname[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);
    memset(roomname, 0, BUFF_SIZE+1);

    // 채팅방 이름 입력
    scanf("%s", roomname);
    
    // data 만들기
    memset(data, strlen(roomname), 1); // roomname 길이 붙이고
    strcat(data, roomname); // roomname 붙인다.

    // 패킷 만들어서 전송
    create_packet(3, 1, data, buf); 
    write(s1.sock, buf, BUFF_SIZE);
    memset(buf, 0, BUFF_SIZE+1);    
    read(s1.sock, buf, BUFF_SIZE);
    receive_packet(buf);
}

// 채팅 메시지 요청
void client_chat(){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];
    char message[BUFF_SIZE+1];

    int server_addr_size;
    server_addr_size = sizeof(s1.servAddr);

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);
    memset(message, 0, BUFF_SIZE+1);

    // 메시지 입력
    scanf("%s", message);

    // 메시지 패킷 만들어서 전송
    memset(data, strlen(message), 1); // message 길이 붙이고
    strcat(data, message); // message 붙인다.
    create_packet(4, 1, data, buf); 
    send_packet(s1.sock, buf, s1.servAddr);

    // 첫 번째 응답 수신, 처리
    // memset(buf, 0, BUFF_SIZE+1);
    // recvfrom(s1.sock, buf, BUFF_SIZE, 0 , (struct sockaddr*)&s1.servAddr, &server_addr_size);
    // receive_packet();

    // 첫 번째 응답 처리
    // printf("%c\n", buf[2]);
    // receive_packet(buf);

    // 두 번째 응답 수신, 처리
    // memset(buf, 0, sizeof(buf));
    // recvfrom(s1.sock, buf, BUFF_SIZE, 0 , (struct sockaddr*)&s1.servAddr, &server_addr_size);
    // receive_packet();
    
    // 두 번째 응답 처리
    // receive_packet(buf);
}

void client_chat2(char *message){
    char buf[BUFF_SIZE];
    memset(buf, 0, BUFF_SIZE+1);
    memset(buffer, 0, BUFF_SIZE+1);

    printf("message: %s\n", message);
    memset(buffer, 1, 1);
    create_packet(5, 2, buffer, buf); // 응답 패킷 만들어서
    // printf("%d %d %d\n", buf[0], buf[1], buf[2]);
    send_packet(s1.sock, buf, s1.servAddr); // 전송
}


// 채팅방 검색 요청
void client_room_search(){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];
    char roomname[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);
    memset(roomname, 0, sizeof(roomname));

    // 채팅방 이름 입력
    printf("insert your chat room \n");
    scanf("%s", roomname);
    
    // data 만들기
    memset(data, strlen(roomname), 1); // roomname 길이 붙이고
    strcat(data, roomname); // roomname 붙인다.

    // 패킷 만들어서 전송
    create_packet(10, 1, data, buf); 
    write(s1.sock, buf, BUFF_SIZE);
    memset(buf, 0, BUFF_SIZE+1);    
    read(s1.sock, buf, BUFF_SIZE);
    receive_packet(buf);
}

// 채팅방 팔로우 요청
void client_room_follow(){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];
    char roomname[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);
    memset(roomname, 0, sizeof(roomname));

    // 채팅방 이름 입력
    printf("팔로우 하고싶은 채팅방을 입력하세요. \n");
    scanf("%s", roomname);
    
    // data 만들기
    memset(data, 4, 1);
    memset(&data[1], strlen(roomname), 1); // roomname 길이 붙이고
    strcat(data, roomname); // roomname 붙인다.

    // 패킷 만들어서 전송
    create_packet(11, 1, data, buf); 
    write(s1.sock, buf, BUFF_SIZE);
    memset(buf, 0, BUFF_SIZE+1);    
    read(s1.sock, buf, BUFF_SIZE);
    receive_packet(buf);
}

// 채팅방 팔로우 검색
void client_search_room_follow(){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);

    // 채팅방 이름 입력
    printf("My following chatroom : \n");
    

    // R : search
    memset(data, 3, 1); // search라는 패킷
    // strcat(data, "R"); // roomname 붙인다.

    // 패킷 만들어서 전송
    create_packet(11, 1, data, buf); 
    write(s1.sock, buf, BUFF_SIZE);
    memset(buf, 0, BUFF_SIZE+1);    
    read(s1.sock, buf, BUFF_SIZE);
    receive_packet(buf);
}