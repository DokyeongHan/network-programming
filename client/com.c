/*
최초작성자: 한도경

최초작성일: 2019-05-26

최초변경일: 2019-05-26

프로그램 목적: 서버와 통신을 위한 함수

개정이력: 
(2019-05-26) create_packet, send_packet 함수 작성
(2019-05-28) receive_packet 함수 작성
저작권: 5조
*/

#include "header.h"
#define BUFF_SIZE 1024

// 패킷 받으면 확인해서 타입별로 처리
void receive_packet(char *packet){
    char type[2];
    char mode[2];
    char len[2];

    memset(type, 0, 2);
    memset(mode, 0, 2);
    memset(len, 0, 2);

    strncpy(type, &packet[0], 1);
    strncpy(mode, &packet[1], 1);

    char login = 1;
    char signup = 2;
    char chat_link = 3;
    char chat_message_rcv = 4;
    char chat_message_snd = 5;
    char post = 6;
    char comment = 7;
    char manage_room = 8;
    char manage_board = 9;
    char room_search = 10;
    char room_follow = 11;

    char req = 1;
    char res = 2;
    
    char n[2];
    memset(n, 0, 2);


    printf("%d\n", packet[0]);

    // 05 채팅 메시지 패킷 (채팅방으로부터 들어온 메시지)
    if(!strncmp(type, &chat_message_snd,1) && !strncmp(mode, &req, 1)){
        printf("메시지 송신 됨\n");
        printf("%c\n", packet[3]);
        char buf[BUFF_SIZE+1];
        memset(buf, 0, sizeof(buf));
        
        memset(n, packet[2], 1);
        printf("message length: %d\n", *n);
        
        strncpy(buf, &packet[3], *n);
        printf("message: %s\n", buf);

        client_chat2(buf);
    }
}

// data 앞에 type과 mode를 붙임
void create_packet(char type, char mode, char *data ,char *buf){
	strncat(buf, &type, 1); // type 붙여주고
	strncat(buf, &mode, 1); // mode 붙여주고
    strcat(buf, data); // data 붙여주고
}

// 패킷을 전송
void send_packet(int sockfd, char *buf, struct sockaddr_in servAddr){
    if(!sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*) &servAddr, sizeof(servAddr))) {
        perror("sendto failed");
        exit(1);
    }
}