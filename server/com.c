/*
최초작성자: 한도경

최초작성일: 2019-05-26

최초변경일: 2019-05-26

프로그램 목적: 클라이언트와 통신을 위한 함수

개정이력: 
(2019-05-26) create_packet, send_packet, receive_packet 함수 작성

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
    
    char *n;

    // 01 로그인 요청 패킷
    if(!strncmp(type, &login,1) && !strncmp(mode, &req, 1)){
        printf("로그인\n");
        memset(&u1, 0, sizeof(struct userInfo));
        
        int sum = 0;

        strncpy(n, &packet[2], 1);
        printf("ID length: %d\n", *n);
        strncpy(u1.ID, &packet[3], *n);
        printf("ID: %s\n",u1.ID);
        sum += *n;

        strncpy(n, &packet[3+sum], 1);
        printf("PW length: %d\n", *n);
        strncpy(u1.PW, &packet[4+sum], *n+1);
        printf("PW: %s\n",u1.PW);
        sum += *n;

        printf("sum: %d\n",sum);
        server_login(u1);
    }

    // 02 회원가입 요청 패킷
    else if(!strncmp(type, &signup ,1) && !strncmp(mode, &req, 1)){
        printf("회원가입\n");
        memset(&u1, 0, sizeof(struct userInfo));
        
        int sum = 0;

        strncpy(n, &packet[2], 1);
        printf("ID length: %d\n", *n);
        strncpy(u1.ID, &packet[3], *n);
        printf("ID: %s\n",u1.ID);
        sum += *n;

        strncpy(n, &packet[3+sum], 1);
        printf("PW length: %d\n", *n);
        strncpy(u1.PW, &packet[4+sum], *n);
        printf("PW: %s\n",u1.PW);
        sum += *n;

        strncpy(n, &packet[4+sum], 1);
        printf("NAME length: %d\n", *n);
        strncpy(u1.NAME, &packet[5+sum], *n);
        printf("NAME: %s\n",u1.NAME);
        sum += *n;

        printf("sum: %d\n",sum);
        server_signup(u1);
    }

    // 03 채팅방 접속 패킷
    else if(!strncmp(type, &chat_link, 1) && !strncmp(mode, &req, 1)){
        printf("채팅방 접속\n");
        memset(buffer, 0, sizeof(buffer));

        strncpy(n, &packet[2], 1);
        printf("room_name length: %d\n", *n);
        strncpy(buffer, &packet[3], *n);
        printf("room_name: %s\n", buffer);
        
        server_choice_chat_room(); 
    }
    
    // 04 채팅 메시지 패킷 (들어온 요청 처리)
    else if(!strncmp(type, &chat_message_rcv, 1) && !strncmp(mode, &req, 1)){
        printf("채팅 메시지 수신\n");
        char buf[BUFF_SIZE+1];
        memset(buf, 0, sizeof(buf));

        strncpy(n,&packet[2],1);
        printf("message length: %d\n", *n);
        strncpy(buf, &packet[3], *n);
        printf("message : %s\n", buf);

        server_chat(buf);
    }

    // 05 채팅 메시지 패킷 (뿌린거 응답 처리)
    else if(!strncmp(type, &chat_message_snd, 1) && !strncmp(mode, &res, 2)){
        printf("채팅 메시지 송신\n");
        server_login(u1);
    }

    // 06 게시글 패킷 처리
    else if(!strncmp(type, &post, 1) && !strncmp(mode, &req, 1)){
        printf("게시글\n");
        int sum = 0;
        memset(buffer, 0, sizeof(buffer));
        memset(buffer2, 0, sizeof(buffer2));

        strncpy(n, &packet[2], 1);
        printf("CRUD: %c\n", *n);

        strncpy(n, &packet[3], 1);
        printf("TITLE length: %d\n", *n);
        strncpy(buffer, &packet[4], *n);
        printf("TITLE: %s\n", buffer);
        sum += *n;

        strncpy(n, &packet[4+sum], 1);
        printf("DES length: %d\n", *n);
        strncpy(buffer2, &packet[5+sum], *n);
        printf("DES: %s\n", buffer2);
        sum += *n;

        printf("sum: %d\n",sum);
        server_post_act('C');
    }

    // 07 댓글 패킷 처리
    else if(!strncmp(type, &comment, 1) && !strncmp(mode, &req, 1)){
        printf("댓글\n");
        strncpy(n, &packet[2], 1);
        printf("CRUD: %c\n", *n);

        strncpy(n, &packet[3], 1);
        printf("COMMENT length: %d\n", *n);
        strncpy(buffer, &packet[4], *n);
        printf("COMMENT: %s\n", buffer);

        server_comment_act('C');
    }

    // 08 채팅방 생성/삭제 패킷
    else if(!strncmp(type, &manage_room, 1) && !strncmp(mode, &req, 1)){
        printf("채팅방 생성/삭제\n");
        memset(buffer, 0, sizeof(buffer));

        strncpy(n, &packet[2], 1);
        printf("CRUD: %c\n", *n);
        strncpy(n, &packet[3], 1);
        printf("room_name length: %d\n", *n);
        strncpy(buffer, &packet[4], *n);
        printf("room_name: %s\n", buffer);
        
        server_manage_room(buffer);  
        printf("%s\n", roomList[0].room_name);
        int cnt =0;
        while(roomList[0].roomUserList[cnt].ID[0] != 0){
            printf("ID: %s\n", roomList[0].roomUserList[cnt].ID);
            cnt+=1;
        }
    }

    // 09 게시판 생성/삭제 패킷
    else if(!strncmp(type, &manage_board, 1) && !strncmp(mode, &req, 1)){
        printf("게시판 생성/삭제\n");
        memset(buffer, 0, sizeof(buffer));

        strncpy(n, &packet[2], 1);
        printf("CRUD: %c\n", *n);
        strncpy(n, &packet[3], 1);
        printf("board_name length: %d\n", *n);
        strncpy(buffer, &packet[4], *n);
        printf("board_name: %s\n", buffer);
        
        server_manage_board(buffer);  
    }

    // 10 채팅방 검색 패킷
    else if(!strncmp(type, &room_search, 1) && !strncmp(mode, &req, 1)){
        printf("채팅방 검색\n");
        memset(buffer, 0, sizeof(buffer));

        strncpy(n, &packet[2], 1);
        printf("room_name length: %d\n", *n);
        strncpy(buffer, &packet[3], *n);
        printf("room_name: %s\n", buffer);
        
        server_room_search(buffer);
    }

    // 11 채팅방 팔로우 패킷
    else if(!strncmp(type, &room_follow, 1) && !strncmp(mode, &req, 1)){
        printf("채팅방 팔로우\n");
        memset(buffer, 0, sizeof(buffer));

        strncpy(n, &packet[2], 1);
        printf("room_name length: %d\n", *n);
        strncpy(buffer, &packet[3], *n);
        printf("room_name: %s\n", buffer);
        
        server_room_follow(buffer);
    }

    else {
        printf("없음");
    }
}

// data 앞에 type과 mode를 붙임
void create_packet(char type, char mode, char *data ,char *buf){
	strncat(buf, &type, 1); // type 붙여주고
	strncat(buf, &mode, 1); // mode 붙여주고
    strcat(buf, data); // data 붙여주고
}

void send_packet(int sockfd, char *buf, struct sockaddr_in clntAddr){
    if(!sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*) &clntAddr, sizeof(clntAddr))) {
        perror("sendto failed");
        exit(1);
    }
}