#include "header.h"

// 패킷 받으면 확인해서 타입별로 처리
void receive_packet(char *packet){
    char type[2];
    char mode[2];
    char len[2];

    memset(type, 0, 2);
    memset(mode, 0, 2);
    memset(len, 0, 2);

    strncpy(type, &packet[0], 1);
    strncpy(mode, &packet[1], 1);

    char login = 1;
    char signup = 2;
    char chat = 3;
    char manage_room = 8;
    char manage_board = 9;

    char req = 1;
    char res = 2;
    
    char *n;

    // 로그인 요청 패킷
    if(!strncmp(type, &login,1) && !strncmp(mode, &req, 1)){
        printf("로그인\n");
        struct userInfo u1;
        memset(u1.ID, 0, sizeof(u1.ID));
        
        int sum = 0;

        strncpy(n, &packet[2], 1);
        printf("ID length: %d\n", *n);
        strncpy(u1.ID, &packet[3], *n);
        printf("ID: %s\n",u1.ID);
        sum += *n;

        strncpy(n, &packet[3+sum], 1);
        printf("PW length: %d\n", *n);
        strncpy(u1.PW, &packet[4+sum], *n+1);
        printf("PW: %s\n",u1.PW);
        sum += *n;

        printf("sum: %d\n",sum);
        server_login(u1);
    }

    // 회원가입 요청 패킷
    else if(!strncmp(type, &signup ,1) && !strncmp(mode, &req, 1)){
        printf("회원가입\n");
        struct userInfo u1;
        memset(&u1, 0, sizeof(struct userInfo));
        
        int sum = 0;

        strncpy(n, &packet[2], 1);
        printf("ID length: %d\n", *n);
        strncpy(u1.ID, &packet[3], *n);
        printf("ID: %s\n",u1.ID);
        sum += *n;

        strncpy(n, &packet[3+sum], 1);
        printf("PW length: %d\n", *n);
        strncpy(u1.PW, &packet[4+sum], *n);
        printf("PW: %s\n",u1.PW);
        sum += *n;

        strncpy(n, &packet[4+sum], 1);
        printf("NAME length: %d\n", *n);
        strncpy(u1.NAME, &packet[5+sum], *n);
        printf("NAME: %s\n",u1.NAME);
        sum += *n;

        printf("sum: %d\n",sum);
        server_signup(u1);
    }

    // 채팅 패킷
    else if(!strncmp(type, &chat, 1)){
        printf("채팅");
    }
    
    // 채팅방 생성/삭제 패킷
    else if(!strncmp(type, &manage_room, 1) && !strncmp(mode, &req, 1)){
        printf("채팅방 생성/삭제\n");
        memset(roomname, 0, sizeof(roomname));

        strncpy(n, &packet[2], 1);
        printf("CRUD: %c\n", *n);
        strncpy(n, &packet[3], 1);
        printf("room_name length: %d\n", *n);
        strncpy(roomname, &packet[4], *n);
        printf("room_name: %s\n", roomname);
        
        server_manage_room();  
        printf("%s\n", roomList[0].room_name);
        int cnt =0;
        while(roomList[0].roomUserList[cnt].ID[0] != 0){
            printf("ID: %s\n", roomList[0].roomUserList[cnt].ID);
            cnt+=1;
        }
    }

        // 채팅방 생성/삭제 패킷
    else if(!strncmp(type, &manage_board, 1) && !strncmp(mode, &req, 1)){
        printf("게시판 생성/삭제\n");
        memset(roomname, 0, sizeof(roomname));

        strncpy(n, &packet[2], 1);
        printf("CRUD: %c\n", *n);
        strncpy(n, &packet[3], 1);
        printf("room_name length: %d\n", *n);
        strncpy(roomname, &packet[4], *n);
        printf("room_name: %s\n", roomname);
        
        server_manage_board();  
    }

    else {
        printf("없음");
    }
}

// data 앞에 type과 mode를 붙임
void create_packet(char type, char mode, char *data ,char *buf){
	strncat(buf, &type, 1); // type 붙여주고
	strncat(buf, &mode, 1); // mode 붙여주고
    strcat(buf, data); // data 붙여주고
}

void send_packet(int sockfd, char *buf, struct sockaddr_in clntAddr){
    if(!sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*) &clntAddr, sizeof(clntAddr))) {
        perror("sendto failed");
        exit(1);
    }
}