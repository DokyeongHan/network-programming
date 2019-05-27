/*
최초자성자 : 한도경

최초작성일 : 2019-05-25

최초변경일 : 2019-05-25

프로그램 목적 : 프로젝트

개정이력 :
(2019-05-25) 채팅방 생성기능

저작권 : 5조
*/

#include "header.h"
#define BUFSIZE 1024

// 방 만들기
void server_manage_room(){
    char buf[BUFSIZE+1];
    memset(buf, 0, BUFSIZE+1);

    // 방 만든다.
    strcpy(roomList[0].room_name, roomname);

    // 임의 사용자 추가
    strcpy(roomList[0].roomUserList[0].ID, "hdk0521");
    strcpy(roomList[0].roomUserList[1].ID, "hdk0521");

    // 방만들기 성공
    printf("create success\n");
    create_packet(8, 2,"성공", buf); // 응답패킷 만들어서
    send_packet(s1.sockfd, buf, s1.clntAddr); // 전송

    // 방만들기 실패
}

// // 게시판 처리
void server_manage_board(){
    char buf[BUFSIZE+1];
    memset(buf, 0, BUFSIZE+1);

    // 게시판 만든다.

    // 게시판 만들기 성공
    printf("create success\n");
    create_packet(9, 2,"성공", buf); // 응답패킷 만들어서
    send_packet(s1.sockfd, buf, s1.clntAddr); // 전송

    // 방만들기 실패
}