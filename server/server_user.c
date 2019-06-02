/*
최초자성자 : 한도경

최초작성일 : 2019-05-24

최초변경일 : 2019-05-24

프로그램 목적 : 프로젝트

개정이력 :
(2019-05-24) ODBC 연결 필요함. 로그인, 회원가입 함수 작성
(2019-05-30) 로그인 회원가입 응답 패킷 생성 

저작권 : 5조
*/

#include "header.h"
#define BUFSIZE 1024

// 로그인 처리
void server_login(){
    char buf[BUFSIZE+1];
    memset(buffer, 0, sizeof(buffer));
    memset(buffer2, 0, sizeof(buffer2));

    // 로그인 성공
    if(!strcmp(u1.ID, "hdk0521") && !strcmp(u1.PW, "123123")){
        strcpy(u1.NAME, "123");
        memset(&buffer[0], 1, 1); // 성공 1
        memset(&buffer[1], 3, 1); // 이름 길이
        strcat(buffer, u1.NAME); // 이름
        
        create_packet(1, 2, buffer, buffer2); // 응답 패킷 만들어서
        write(s1.sock, buffer2, BUFSIZE);
        printf("[RES] login success: ID (%s), PW (%s), NAME (%s)\n", u1.ID, u1.PW, u1.NAME); 
    }
    // 로그인 실패
    else{
        memset(&buffer[0], 2, 1);
        create_packet(1,2,buffer, buffer2); // 응답 패킷 만들어서
        write(s1.sock, buffer2, BUFSIZE);
        printf("[RES] login failed: ID (%s), PW (%s)\n", u1.ID, u1.PW);    
    }
}

// 회원가입 처리
void server_signup(){
        memset(buffer, 0, BUFSIZE+1);
        memset(buffer2, 0, BUFSIZE+1);

        // 회원가입 성공
        memset(buffer, 1, 1); // 성공 1

        create_packet(2, 2, buffer, buffer2); // 응답패킷 만들어서
        write(s1.sock, buffer2, BUFSIZE);
        printf("[RES] signup success: ID (%s), PW (%s), NAME (%s)\n", u1.ID, u1.PW, u1.NAME); 
}