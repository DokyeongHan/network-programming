/*
최초작성자: 한도경

최초작성일: 2019-05-26

최초변경일: 2019-05-26

프로그램 목적: 로그인, 회원가입을 위한 요청

개정이력: 
(2019-05-26) client_login, client_signup 함수 작성
(2019-05-30) 

저작권: 5조
*/ 

#include "header.h"
#define BUFF_SIZE 1024

int client_login(){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];
    char ID[BUFF_SIZE+1];
    char PW[BUFF_SIZE+1];

    // 변수 초기화
    memset(&u1, 0, sizeof(struct userInfo));
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);
    memset(ID, 0, sizeof(ID));
    memset(PW, 0, sizeof(PW));
    
    // ID, PW 입력
    printf("   ID : ");
    scanf("%s", ID); 
    printf("\n\n");
   	printf("   PW : ");
    scanf("%s", PW); 
    printf("\n\n");
	printf("--------------------\n\n");

    // userInfo 구조체에 정보 저장
    strcpy(u1.ID, ID);
    strcpy(u1.PW, PW);
    printf("userInfo: %s, %s\n", u1.ID, u1.PW);
    
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
    receive_packet(buf);

    return 1;
}

void client_signup(){
    // 변수 선언
    char buf[BUFF_SIZE+1];
    char data[BUFF_SIZE+1];
    char ID[BUFF_SIZE+1];
    char PW[BUFF_SIZE+1];
    char NAME[BUFF_SIZE+1];

    int result;

    // 변수 초기화
    memset(&u1, 0, sizeof(struct userInfo));
    memset(buf, 0, BUFF_SIZE+1);
    memset(data, 0, BUFF_SIZE+1);
    memset(ID, 0, sizeof(ID));
    memset(PW, 0, sizeof(PW));
    memset(NAME, 0, sizeof(NAME));
    
    // ID, PW 입력
    scanf("%s", ID); 
    scanf("%s", PW); 
    scanf("%s", NAME);

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
    receive_packet(buf);
    // result = receive_packet();

    // 회원가입 성공시 바로 로그인 하게
    // if(result == 1){
    //     create_packet(1, 1, data, buf); 
    //     send_packet(s1.sockfd, buf, s1.servAddr);
    //     receive_packet(s1.sockfd, s1.servAddr);
    // }
}