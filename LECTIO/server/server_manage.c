/*
최초자성자 : 한도경

최초작성일 : 2019-05-25

최초변경일 : 2019-05-25

프로그램 목적 : 프로젝트

개정이력 :
(2019-05-25) server_manage_room, server_manage_board 함수 작성
(2019-06-01) 공유메모리를 활용한 채팅방 생성 기능

저작권 : 5조
*/

#include "header.h"
#define BUFSIZE 1024

// 방 만들기
void server_manage_room(char *CRUD, char *roomname){
    int i=0;
    int index=0;
    void *shmaddr = (void *)1;

    /* 1234 키의 공유메모리 있으면 접근해서 식별자 얻음 */
    if((shmid=shmget((key_t)1234, 1024000, IPC_CREAT|0666)) == -1) {
       perror("shmid failed");
       exit(1);
    }

    // /* shmid 공유메모리를 호출 프로세스 메모리 영역으로 첨부 */
    if((shmaddr=shmat(shmid, (void *)0, 0)) == (void *)-1) {
       perror("shmat failed");
       exit(1);
    }

    roomList = (struct roomList *)shmaddr;
    // roomList = malloc(sizeof(struct roomList)*3000);

    if(*CRUD == 'C'){
        // 새로 만들 방 인덱스 찾는다.
        for(i=0; i<3000 ; i++){
            // 이미 방이 있다면 안만든다.
            if(!strcmp(roomList[i].room_name, roomname)){
                // 방만들기 실패
                printf("[RES] manage_room failed: CRUD (%s), ROOM_NAME (%s)\n", CRUD, roomname); 
                memset(buffer, 0, BUFSIZE+1);
                memset(buffer2, 0, BUFSIZE+1);
                memset(buffer, 2, 1); // 실패 2
                create_packet(8, 2, buffer, buffer2); // 응답패킷 만들어서
                write(s1.sock, buffer2, BUFSIZE);
                break;
            }
            // 방이 없다면 만든다.
            if(roomList[i].room_name[0] == '\0'){
                // 방 만든다.
                strcpy(roomList[i].room_name, roomname);
                roomList[i].port = 5000+i;

                // DB에 INSERT
                server_make_room(roomname);
                // 방만들기 성공
                printf("[RES] manage_room success: CRUD (%s), ROOM_NAME (%s)\n", CRUD, roomname); 
                memset(buffer, 0, BUFSIZE+1);
                memset(buffer2, 0, BUFSIZE+1);
                memset(buffer, 1, 1); // 성공 1
                create_packet(8, 2, buffer, buffer2); // 응답패킷 만들어서
                write(s1.sock, buffer2, BUFSIZE);
                break;
            }
        }

        // 방 개수 초과
        if(i == 3000){
            // 방만들기 실패
            printf("[RES] manage_room success: CRUD (%s), ROOM_NAME (%s)\n", CRUD, roomname); 
            memset(buffer, 0, BUFSIZE+1);
            memset(buffer2, 0, BUFSIZE+1);
            memset(buffer, 2, 1); // 실패 2
            create_packet(8, 2, buffer, buffer2); // 응답패킷 만들어서
            write(s1.sock, buffer2, BUFSIZE);
        }

        // 공유메모리에 데이터 쓰기
        memcpy((void *)shmaddr, roomList, sizeof(roomList));

        // /* 공유메모리를 호출 프로세스의 메모리 영역에서 분리 */
        if(shmdt(shmaddr) == -1) {
        perror("shmdt failed");
        exit(1);
        }
    }

    if(*CRUD == 'R'){
        memset(buffer, 0, BUFSIZE+1);
        memset(buffer2, 0, BUFSIZE+1);
        // 방의 개수를 샌다.
        for(i=0; i<3000 ; i++){
            if(roomList[i].room_name[0] == '\0'){
                break;
            }
        }
        memset(buffer, 1, 1); // 성공 1
        memset(&buffer[1], 'R', 1);
        for(int j=0; j<i; j++){
            strcat(buffer, roomList[j].room_name);
            strcat(buffer, "\n");
        }
        memset(buffer2, 0, BUFSIZE+1);
        create_packet(8, 2, buffer, buffer2); // 응답패킷 만들어서
        // printf("%s\n", buffer2);
        write(s1.sock, buffer2, BUFSIZE);
        printf("[RES] manage_room success: CRUD (%s)\n", CRUD); 

        // /* 공유메모리를 호출 프로세스의 메모리 영역에서 분리 */
        if(shmdt(shmaddr) == -1) {
        perror("shmdt failed");
        exit(1);
        }
    }
}

// // 게시판 처리
void server_manage_board(char *CRUD, char *boardname){
    memset(buffer, 0, BUFSIZE+1);
    memset(buffer2, 0, BUFSIZE+1);

    // 게시판 만든다.
    
    // 게시판 만들기 성공
    memset(buffer, 1, 1); // 성공 1
    create_packet(9, 2, buffer, buffer2); // 응답패킷 만들어서
    write(s1.sock, buffer2, BUFSIZE);
    printf("[RES] manage_board success: CRUD (%s), BOARD_NAME (%s)\n", CRUD, boardname); 

    // 게시판 만들기 실패
}