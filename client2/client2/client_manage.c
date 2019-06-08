/*
최초작성자: 한도경

최초작성일: 2019-05-26

최초변경일: 2019-05-26

프로그램 목적: 채팅방, 게시판 생성, 삭제를 위한 요청

개정이력: 
(2019-05-26) client_manage_room, client_manage_board 함수 작성

저작권: 5조
*/ 

#include "header.h"
#define BUFF_SIZE 1024

int client_manage_room(char CRUD){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];
    char roomname[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);
    memset(roomname, 0, sizeof(roomname));
    
    // 채팅방 생성
    if(CRUD == 'C'){
        // 방 이름 입력
        scanf("%s", roomname); 
        if(!strncmp(roomname, "-1", 2)){
            return -1;
        }
        
        // data 만들기
        memset(data, CRUD, 1);
        memset(data + 1, strlen(roomname), 1); // roomname 길이 붙이고
        strcat(data, roomname); // roomname 붙인다.

        // 방만들기 패킷 만들어서 전송
        create_packet(8, 1, data, buf); 
        write(s1.sock, buf, BUFF_SIZE);
        memset(buf, 0, BUFF_SIZE+1);    
        read(s1.sock, buf, BUFF_SIZE);
        return receive_packet(buf);
    }    
    // 채팅방 목록
    if(CRUD == 'R'){        
        // data 만들기
        memset(data, CRUD, 1);

        // 패킷 만들어서 전송
        create_packet(8, 1, data, buf); 
        write(s1.sock, buf, BUFF_SIZE);
        memset(buf, 0, BUFF_SIZE+1);    
        read(s1.sock, buf, BUFF_SIZE);
        return receive_packet(buf);
    }
}

void client_manage_board(char CRUD){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];
    char boardname[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);
    memset(boardname, 0, sizeof(boardname));

    // 방 이름 입력
    scanf("%s", boardname);
    
    // data 만들기
    memset(data, CRUD, 1);
    memset(data + 1, strlen(boardname), 1); // roomname 길이 붙이고
    strcat(data, boardname); // roomname 붙인다.

    // 로그인 패킷 만들어서 전송
    create_packet(9, 1, data, buf); 
    write(s1.sock, buf, BUFF_SIZE);
    memset(buf, 0, BUFF_SIZE+1);    
    read(s1.sock, buf, BUFF_SIZE);
    receive_packet(buf);
}