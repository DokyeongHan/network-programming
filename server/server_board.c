/*
최초작성자: 한도경

최초작성일: 2019-05-28

최초변경일: 2019-05-28

프로그램 목적: 게시글과 댓글 CRUD 처리 및 응답

개정이력: 
(2019-05-28) server_post_act, server_comment_act 함수 작성

저작권: 5조
*/ 

#include "header.h"
#define BUFSIZE 1024

// 게시글 요청
void server_post_act(char CRUD){
    char data[BUFSIZE+1];
    char buf[BUFSIZE+1];
    memset(data, 0, BUFSIZE+1);
    memset(buf, 0, BUFSIZE+1);

    // 게시글 요청 처리
    



    // 게시글 요청 처리 성공 응답
    memset(&data[0], 1, 1); // 성공 1
    create_packet(6, 2, data, buf); // 응답 패킷 만들어서
    write(s1.sock, buf, BUFSIZE);
    printf("[RES] POST_ACT success: CRUD (%c)\n", CRUD);
}

// 댓글 요청
void server_comment_act(char CRUD){
    char data[BUFSIZE+1];
    char buf[BUFSIZE+1];
    memset(data, 0, BUFSIZE+1);
    memset(buf, 0, BUFSIZE+1);

    // 댓글 요청 처리

    // 댓글 요청 처리 성공 응답
    memset(&data[0], 1, 1); // 성공 1
    create_packet(7, 2, data, buf); // 응답 패킷 만들어서
    write(s1.sock, buf, BUFSIZE);
    printf("[RES] COMMENT_ACT success: CRUD (%c)\n", CRUD);
}