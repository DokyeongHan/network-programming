/*
최초자성자 : 한도경

최초작성일 : 2019-05-28

최초변경일 : 2019-05-28

프로그램 목적 : 프로젝트

개정이력 :
(2019-05-28) server_choice_chat_room, server_chat 함수 작성

저작권 : 5조
*/

#include "header.h"
#define BUFSIZE 1024

// 채팅방 입장 처리
void server_choice_chat_room(){
    char buf[BUFSIZE+1];
    memset(buf, 0, BUFSIZE+1);
    // 채팅방에 정보 등록

    // 채팅방 입장 성공 응답
    create_packet(3,2,"1", buf); // 응답패킷 만들어서
    send_packet(s1.sockfd, buf, s1.clntAddr); // 전송
}

// 채팅 메시지 처리
void server_chat(char *message){
    char buf[BUFSIZE+1];
    char buf2[BUFSIZE+1];
    memset(buf, 0, BUFSIZE+1);
    memset(buf2, 0, BUFSIZE+1);

    // 채팅 메시지 수신 성공 응답
    printf("message rcv success\n"); 
    create_packet(4, 2, "1", buf); // 응답패킷 만들어서
    send_packet(s1.sockfd, buf, s1.clntAddr); // 전송

    sleep(1);

    // 채팅 메시지 방에 뿌리기
    memset(buf, 0, BUFSIZE+1);
    memset(buf2, 0, BUFSIZE+1);

    memset(buf, strlen(message), 1);
    strcat(buf, message);
    create_packet(5, 1, buf, buf2);
    send_packet(s1.sockfd, buf2, s1.clntAddr);
    printf("뿌리기\n");

    // 채팅 메시지 수신 실패
}

void server_room_search(char *buff){
    char buf[BUFSIZE+1];
    memset(buf, 0, BUFSIZE+1);
    // 채팅방 검색

    // 채팅방 검색 성공 응답
    create_packet(10, 2, "1", buf); // 응답패킷 만들어서
    send_packet(s1.sockfd, buf, s1.clntAddr); // 전송
}

void server_room_follow(char *buff){
    char buf[BUFSIZE+1];
    memset(buf, 0, BUFSIZE+1);
    // 채팅방 팔로우

    // 채팅방 팔로우 성공 응답
    create_packet(11, 2, buff, buf); // 응답패킷 만들어서
    send_packet(s1.sockfd, buf, s1.clntAddr); // 전송
}