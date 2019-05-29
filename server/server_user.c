/*
최초자성자 : 한도경

최초작성일 : 2019-05-24

최초변경일 : 2019-05-24

프로그램 목적 : 프로젝트

개정이력 :
(2019-05-24) ODBC 연결 필요함

저작권 : 5조
*/

#include "header.h"
#define BUFSIZE 1024

// 로그인 처리
void server_login(struct userInfo u1){
    char buf[BUFSIZE+1];
    memset(buf, 0, BUFSIZE+1);

    // 로그인 성공
    if(!strcmp(u1.ID, "hdk0521") && !strcmp(u1.PW, "123123")){
        printf("[RES] login success: ID (%s), PW (%s)\n", u1.ID, u1.PW); 
        create_packet(1,2,"1", buf); // 응답패킷 만들어서
        send_packet(s1.sockfd, buf, s1.clntAddr); // 전송
    }
    // 로그인 실패
    else{
        printf("[RES] login failed: ID (%s), PW (%s)\n", u1.ID, u1.PW); 
        create_packet(1,2,"2", buf); // 응답패킷 만들어서
        send_packet(s1.sockfd, buf, s1.clntAddr); // 전송
    }
}

// 회원가입 처리
void server_signup(struct userInfo u1){
        char buf[BUFSIZE+1];
        memset(buf, 0, BUFSIZE+1);
    
        printf("[RES] signup success: ID (%s), PW (%s), NAME (%s)\n", u1.ID, u1.PW, u1.NAME); 
        create_packet(2, 2,"1", buf); // 응답패킷 만들어서
        send_packet(s1.sockfd, buf, s1.clntAddr); // 전송
}