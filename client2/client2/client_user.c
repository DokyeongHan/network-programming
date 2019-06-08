/*
최초작성자: 한도경

최초작성일: 2019-05-26

최초변경일: 2019-05-26

프로그램 목적: 로그인, 회원가입을 위한 요청

개정이력: 
(2019-05-26) client_login, client_signup 함수 작성
(2019-06-07) 코드 정리

저작권: 5조
*/ 

#include "header.h"
#define BUFF_SIZE 1024

int client_login(char *ID, char *PW){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];

    // 변수 초기화
    memset(&u1, 0, sizeof(struct userInfo));
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);

    // userInfo 구조체에 정보 저장
    strcpy(u1.ID, ID);
    strcpy(u1.PW, PW);
    
    // data 만들기
    memset(data, strlen(ID), 1); // ID 길이 붙이고
    strcat(data, ID); // ID 붙이고
    memset(data+strlen(ID)+1, strlen(PW), 1); // PW 길이 붙이고
    strcat(data, PW); // PW 붙인다

    // 로그인 패킷 만들어서 전송하고 응답 수신
    create_packet(1, 1, data, buf); 
    write(sock, buf, BUFF_SIZE);
    memset(buf, 0, BUFF_SIZE+1);   
    read(sock, buf, BUFF_SIZE);

    return receive_packet(buf);
}

int client_signup(char *ID, char *PW, char *NAME){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];

    int result=0;

    // 변수 초기화
    memset(&u1, 0, sizeof(struct userInfo));
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);

    // userInfo 구조체에 정보 저장
    strcpy(u1.ID, ID);
    strcpy(u1.PW, PW);
    strcpy(u1.NAME, NAME);
    printf("userInfo: %s, %s, %s\n", u1.ID, u1.PW, u1.NAME);
    
    // data 만들기
    memset(data, strlen(ID), 1); // ID 길이 붙이고
    strcat(data, ID); // ID 붙이고
    memset(data+strlen(ID)+1, strlen(PW), 1); // PW 길이 붙이고
    strcat(data, PW); // PW 붙이고
    memset(data+strlen(ID)+strlen(PW)+2, strlen(NAME), 1); // NAME 길이 붙이고
    strcat(data, NAME); // NAME 붙인다

    // 회원가입 패킷 만들어서 전송
    create_packet(2, 1, data, buf); 
    write(s1.sock, buf, BUFF_SIZE);
    memset(buf, 0, BUFF_SIZE+1);    
    read(s1.sock, buf, BUFF_SIZE);
    result = receive_packet(buf);

    return result;
}