/*
최초작성자: 한도경

최초작성일: 2019-05-26

최초변경일: 2019-05-26

프로그램 목적: 클라이언트와 통신을 위한 함수

개정이력: 
(2019-05-26) create_packet, send_packet, receive_packet 함수 작성
(2019-05-29) 모든 패킷 parse 완료
(2019-05-30) receive_packet 함수 내에서 recvfrom 사용하게 변경 -> 실패


저작권: 5조
*/ 

#include "header.h"
#define BUFF_SIZE 1024

// 패킷 받으면 확인해서 타입별로 처리
void receive_packet(char *packet){
    // 변수 선언
    char type[2];
    char mode[2];
    char len[2];
    char n[2];

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
    

    // 초기화
    memset(type, 0, 2);
    memset(mode, 0, 2);
    memset(len, 0, 2);
    memset(n, 0, 2);

    // type, mode 파싱
    strncpy(type, &packet[0], 1);
    strncpy(mode, &packet[1], 1);

    // 01 로그인 요청 패킷
    if(!strncmp(type, &login, 1) && !strncmp(mode, &req, 1)){
        memset(&u1, 0, sizeof(struct userInfo));
        int sum = 0;

        strncpy(n, &packet[2], 1);
        strncpy(u1.ID, &packet[3], *n);
        sum += *n;

        strncpy(n, &packet[3+sum], 1);
        strncpy(u1.PW, &packet[4+sum], *n+1);

        printf("[REQ] login: ID (%s), PW (%s)\n",u1.ID, u1.PW);

        server_login();
    }

    // 02 회원가입 요청 패킷
    else if(!strncmp(type, &signup ,1) && !strncmp(mode, &req, 1)){
        memset(&u1, 0, sizeof(struct userInfo));
        int sum = 0;

        strncpy(n, &packet[2], 1);
        strncpy(u1.ID, &packet[3], *n);
        sum += *n;
        strncpy(n, &packet[3+sum], 1);
        strncpy(u1.PW, &packet[4+sum], *n);
        sum += *n;
        strncpy(n, &packet[4+sum], 1);
        strncpy(u1.NAME, &packet[5+sum], *n);

        printf("[REQ] signup: ID (%s), PW (%s), NAME (%s)\n", u1.ID, u1.PW, u1.NAME);
        server_signup();
    }

    // 03 채팅방 접속 패킷
    else if(!strncmp(type, &chat_link, 1) && !strncmp(mode, &req, 1)){        
        memset(room_name, 0, sizeof(room_name));

        strncpy(n, &packet[2], 1);
        strncpy(room_name, &packet[3], *n);

        printf("[REQ] enter_room: ROOM_NAME (%s)\n", room_name);
        server_choice_chat_room(room_name); 
    }
    
    // 04 채팅 메시지 패킷 (들어온 요청 처리)
    else if(!strncmp(type, &chat_message_rcv, 1) && !strncmp(mode, &req, 1)){
        char buf[BUFF_SIZE+1];
        memset(buf, 0, sizeof(buf));

        strncpy(n,&packet[2],1);
        strncpy(buf, &packet[3], *n);

        printf("[REQ] message(room <- user): MESSAGE (%s), ROOM_NAME (%s)\n", buf, room_name);
        server_chat(buf);
    }

    // 05 채팅 메시지 패킷 (뿌린거 응답 처리)
    else if(!strncmp(type, &chat_message_snd, 1) && !strncmp(mode, &res, 1)){
        printf("[RES] message(room <- user) success: ROOM_NAME (%s)\n", room_name);
        server_chat2();
    }

    // 06 게시글 패킷 처리
    else if(!strncmp(type, &post, 1) && !strncmp(mode, &req, 1)){
        int sum = 0;
        char CRUD[2];
        char TITLE[BUFF_SIZE+1];
        char DESCRIPTION[BUFF_SIZE+1];

        memset(CRUD, 0, sizeof(CRUD));
        memset(TITLE, 0, sizeof(TITLE));
        memset(DESCRIPTION, 0, sizeof(DESCRIPTION));

        strncpy(CRUD, &packet[2], 1);
        strncpy(n, &packet[3], 1);
        strncpy(TITLE, &packet[4], *n);
        sum += *n;
        strncpy(n, &packet[4+sum], 1);
        strncpy(DESCRIPTION, &packet[5+sum], *n);
        
        printf("[REQ] post_act: CRUD (%s), TITLE (%s), DESCRIPTION (%s)\n", CRUD, TITLE, DESCRIPTION);
        server_post_act('C');
    }

    // 07 댓글 패킷 처리
    else if(!strncmp(type, &comment, 1) && !strncmp(mode, &req, 1)){
        char CRUD[2];
        char COMMENT[BUFF_SIZE+1];
        
        memset(CRUD, 0, sizeof(CRUD));
        memset(COMMENT, 0, sizeof(COMMENT));

        strncpy(CRUD, &packet[2], 1);
        strncpy(n, &packet[3], 1);
        strncpy(COMMENT, &packet[4], *n);

        printf("[REQ] comment_act: CRUD (%s), COMMENT (%s)\n", CRUD, COMMENT);
        server_comment_act('C');
    }

    // 08 채팅방 생성/삭제 패킷
    else if(!strncmp(type, &manage_room, 1) && !strncmp(mode, &req, 1)){
        char CRUD[2];
        char room_name[BUFF_SIZE+1];

        memset(CRUD, 0, sizeof(CRUD));
        memset(room_name, 0, sizeof(room_name));

        strncpy(CRUD, &packet[2], 1);
        strncpy(n, &packet[3], 1);
        strncpy(room_name, &packet[4], *n);
        
        printf("[REQ] manage_room: CRUD (%s), ROOM_NAME (%s)\n", CRUD, room_name);
        server_manage_room(CRUD, room_name);  

        // printf("%s\n", roomList[0].room_name);
        // int cnt =0;
        // while(roomList[0].roomUserList[cnt].ID[0] != 0){
        //     printf("ID: %s\n", roomList[0].roomUserList[cnt].ID);
        //     cnt+=1;
        // }
    }

    // 09 게시판 생성/삭제 패킷
    else if(!strncmp(type, &manage_board, 1) && !strncmp(mode, &req, 1)){
        char CRUD[2];
        char board_name[BUFF_SIZE+1];

        memset(CRUD, 0, sizeof(CRUD));
        memset(board_name, 0, sizeof(board_name));

        strncpy(CRUD, &packet[2], 1);
        strncpy(n, &packet[3], 1);
        strncpy(board_name, &packet[4], *n);
        
        printf("[REQ] manage_board: CRUD (%s), BOARD_NAME (%s)\n", CRUD, board_name);
        server_manage_board(CRUD, board_name);  
    }

    // 10 채팅방 검색 패킷
    else if(!strncmp(type, &room_search, 1) && !strncmp(mode, &req, 1)){
        char room_name[BUFF_SIZE+1];

        memset(room_name, 0, sizeof(room_name));

        strncpy(n, &packet[2], 1);
        strncpy(room_name, &packet[3], *n);

        printf("[REQ] search_room: ROOM_NAME (%s)\n", room_name);
        server_room_search(room_name);
    }

    // 11 채팅방 팔로우 패킷
    else if(!strncmp(type, &room_follow, 1) && !strncmp(mode, &req, 1)){
        char room_name[BUFF_SIZE+1];

        memset(room_name, 0, sizeof(room_name));
        strncpy(n, &packet[2], 1);
        
        if (strncmp(n, "3", 1)) {
          server_search_room_follow();
          printf("[REQ] search_follow_room \n");

        }
        else if (strncmp(n, "4", 1)) {
          strncpy(n, &packet[3], 1);
          strncpy(room_name, &packet[4], *n);

          server_room_follow(room_name);
          printf("[REQ] follow_room: ROOM_NAME (%s)\n", room_name);
        }
    }

    else {
        close(s1.sock);
        exit(1);
    }
}

// data 앞에 type과 mode를 붙임
void create_packet(char type, char mode, char *data ,char *buf){
	strncat(buf, &type, 1); // type 붙여주고
	strncat(buf, &mode, 1); // mode 붙여주고
    strcat(buf, data); // data 붙여주고
}

// UDP 수신
void send_packet(int sockfd, char *buf, struct sockaddr_in clntAddr){
    if(!sendto(sockfd, buf, BUFF_SIZE, 0, (struct sockaddr*) &clntAddr, sizeof(clntAddr))) {
        perror("sendto failed");
        exit(1);
    }
}