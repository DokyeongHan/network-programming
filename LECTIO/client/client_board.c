/*
최초작성자: 한도경

최초작성일: 2019-05-27

최초변경일: 2019-05-27

프로그램 목적: 게시글과 댓글 CRUD 요청

개정이력: 
(2019-05-27) client_post_act, client_comment_act 함수 작성

저작권: 5조
*/ 

#include "header.h"
#define BUFF_SIZE 1024

// 게시글 요청 (쓰기 읽기 완성)
int client_post_act(char CRUD, int idx, char *title, char * description){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);

    // 게시글 추가
    if(CRUD == 'C'){        
        // data 만들기
        memset(data, CRUD, 1); // CRUD 붙이고
        memset(data + 1, idx, 1); // 게시판 인덱스 붙이고
        memset(data + 2, strlen(title), 1); // title 길이 붙이고
        strcat(data, title); // title 붙인다.
        memset(data + strlen(title) + 3, strlen(description), 1); // description 길이 붙이고
        strcat(data, description); // description 붙인다.

        // 패킷 만들어서 전송
        create_packet(6, 1, data, buf); 
        write(s1.sock, buf, BUFF_SIZE);
        memset(buf, 0, BUFF_SIZE+1);
        read(s1.sock, buf, BUFF_SIZE);
        return receive_packet(buf);
    }
    // 게시글 읽기
    else if(CRUD == 'R'){
        // data 만들기
        memset(data, CRUD, 1); // CRUD 붙이고
        memset(data + 1, idx, 1); // 게시판 인덱스 붙이고

        // 패킷 만들어서 전송
        create_packet(6, 1, data, buf); 
        write(s1.sock, buf, BUFF_SIZE);
        memset(buf, 0, BUFF_SIZE+1);
        read(s1.sock, buf, BUFF_SIZE);
        return receive_packet(buf);
    }
}

// 댓글 요청
void client_comment_act(char CRUD, int idx, int idx2, char *comment){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);
    
    // data 만들기
    memset(data, CRUD, 1);
    memset(data + 1, strlen(comment), 1); // comment 길이 붙이고
    strcat(data, comment); // comment 붙인다.

    // 댓글 패킷 만들어서 전송
    create_packet(7, 1, data, buf); 
    write(s1.sock, buf, BUFF_SIZE);
    memset(buf, 0, BUFF_SIZE+1);
    read(s1.sock, buf, BUFF_SIZE);
    receive_packet(buf);


    // 댓글 추가
    if(CRUD == 'C'){        
        // data 만들기
        memset(data, CRUD, 1); // CRUD 붙이고
        memset(data + 1, idx, 1); // 게시판 인덱스 붙이고
        memset(data + 3, strlen(comment), 1); // comment 길이 붙이고
        strcat(data, comment); // comment 붙인다.

        // 패킷 만들어서 전송
        create_packet(7, 1, data, buf); 
        write(s1.sock, buf, BUFF_SIZE);
        memset(buf, 0, BUFF_SIZE+1);
        read(s1.sock, buf, BUFF_SIZE);
        receive_packet(buf);
    }
}