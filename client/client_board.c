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

// 게시글 요청
void client_post_act(char CRUD){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];
    char title[BUFF_SIZE+1];
    char description[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);
    memset(title, 0, sizeof(title));
    memset(description, 0, sizeof(description));

    // 제목, 글 입력
    scanf("%s", title);
    scanf("%s", description);
    
    // data 만들기
    memset(data, CRUD, 1); // CRUD 붙이고
    memset(data + 1, strlen(title), 1); // title 길이 붙이고
    strcat(data, title); // title 붙인다.
    memset(data + strlen(title) + 2, strlen(description), 1); // description 길이 붙이고
    strcat(data, description); // description 붙인다.

    // 게시글 패킷 만들어서 전송
    create_packet(6, 1, data, buf); 
    send_packet(s1.sockfd, buf, s1.servAddr);
}

// 댓글 요청
void client_comment_act(char CRUD){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];
    char comment[BUFF_SIZE+1];

    // 변수 초기화
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);
    memset(comment, 0, sizeof(comment));

    // 코멘트 입력
    scanf("%s", comment);
    
    // data 만들기
    memset(data, CRUD, 1);
    memset(data + 1, strlen(comment), 1); // comment 길이 붙이고
    strcat(data, comment); // comment 붙인다.

    // 댓글 패킷 만들어서 전송
    create_packet(7, 1, data, buf); 
    send_packet(s1.sockfd, buf, s1.servAddr);
}