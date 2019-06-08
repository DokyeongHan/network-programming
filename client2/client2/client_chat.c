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
int client_choice_chat_room(char *roomname){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);

    // 채팅방 이름 입력
    strcpy(room_name, roomname);
    
    // data 만들기
    memset(data, strlen(roomname), 1); // roomname 길이 붙이고
    strcat(data, roomname); // roomname 붙인다.

    // 패킷 만들어서 전송
    create_packet(3, 1, data, buf); 
    write(s1.sock, buf, BUFF_SIZE);
    memset(buf, 0, BUFF_SIZE+1);    
    read(s1.sock, buf, BUFF_SIZE);
    return receive_packet(buf);
}

// 채팅 메시지 요청
int client_chat(char *message){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);

    // data 만들기
    memset(data, strlen(message), 1); // message 길이 붙이고
    strcat(data, message); // message 붙인다.

    // 메시지 패킷 만들어서 전송
    create_packet(4, 1, data, buf);
    write(s1.sock, buf, BUFF_SIZE);
    return 1;
}

// 채팅방에 뿌린 메시지 처리
void client_chat2(char *name, char *message){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char buf2[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(buf2, 0, BUFF_SIZE+1);

    // 메시지 출력
    printf("%s: %s\n\n", name, message);

    // data 만들기
    memset(buf2, 1, 1);

    // 패킷 만들어서 전송
    create_packet(5, 2, buf2, buf); // 응답 패킷 만들어서
    write(s1.sock, buf, BUFF_SIZE); // 전송
}


// 채팅방 검색 요청
void client_room_search(char* roomname){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);
    
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
void client_room_follow(char* roomname){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);
    
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