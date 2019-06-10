/*
최초작성자: 한도경

최초작성일: 2019-05-26

최초변경일: 2019-05-26

프로그램 목적: 서버와 통신을 위한 함수

개정이력: 
(2019-05-26) create_packet, send_packet 함수 작성
(2019-05-28) receive_packet 함수 작성
(2019-05-30) receive_packet 함수에서 응답 처리

저작권: 5조
*/

#include "header.h"
#define BUFF_SIZE 1024

// 패킷 받으면 확인해서 타입별로 처리
int receive_packet(char *packet){
    // 변수 선언
    char type[2];
    char mode[2];
    char len[2];
    char n[2];

    char login = 1;
    char signup = 2;
    char chat_link = 3;
    char chat_message_rcv = 4;
    char chat_message_snd = 5;
    char post = 6;
    char comment = 7;
    char manage_room = 8;
    char manage_board = 9;
    char room_search = 10;
    char room_follow = 11;

    char req = 1;
    char res = 2;

    char T = 1;
    char F = 2;
    char M = 3;
    
	int server_addr_size;

    // 초기화
    memset(type, 0, 2);
    memset(mode, 0, 2);
    memset(len, 0, 2);

    // type, mode 파싱
    strncpy(type, &packet[0], 1);
    strncpy(mode, &packet[1], 1);

    // 01 로그인 패킷
    if(!strncmp(type, &login, 1) && !strncmp(mode, &res, 1)){
        // 초기화
        memset(n, 0, sizeof(n));
        memset(buffer, 0, sizeof(buffer));
        memset(buffer2, 0, sizeof(buffer2));

        // 성공, 실패 부분 가져오기
        memset(n, packet[2], 1);

        // 성공
        if(!strncmp(n, &T, 1)){
            memset(buffer2, packet[3], 1);
            strncpy(buffer, &packet[4], *buffer2);
            strcpy(u1.NAME, buffer);
            printf("%s 님 안녕하세요!\n", u1.NAME);
            return 1;
        }
        // 실패
        else if(!strncmp(n, &F, 1)){
            return 0;
        }
        // 관리자
        else if(!strncmp(n, &M, 1)){
            memset(buffer2, packet[3], 1);
            strncpy(buffer, &packet[4], *buffer2);
            strcpy(u1.NAME, buffer);
            printf("%s 님 안녕하세요!\n", u1.NAME);
            return 2;
        }
    }

    // 02 회원가입 패킷
    else if(!strncmp(type, &signup, 1) && !strncmp(mode, &res, 1)){
        // 초기화
        memset(n, 0, sizeof(n));
        memset(buffer, 0, sizeof(buffer));
        memset(buffer2, 0, sizeof(buffer2));

        // 성공, 실패 부분 가져오기
        memset(n, packet[2], 1);

        // 성공
        if(!strncmp(n, &T, 1)){
            return 1;
        }
        // 실패
        else if(!strncmp(n, &F, 1)){
            return 0;
        }
    }

    // 03 채팅방 입장 패킷
    else if(!strncmp(type, &chat_link, 1) && !strncmp(mode, &res, 1)){
        // 초기화
        memset(n, 0, sizeof(n));
        memset(buffer, 0, sizeof(buffer));
        memset(buffer2, 0, sizeof(buffer2));

        // 성공, 실패 부분 가져오기
        memset(n, packet[2], 1);

        // 성공
        if(!strncmp(n, &T, 1)){
            char len[2];
            char port[10];
            int po =0;
            memset(port, 0, sizeof(port));
            memset(len, packet[3], 1);
            strncpy(port, &packet[4], *len);
            po = atoi(port);
            printf("%d\n", po);

            // 멀티 캐스팅 소켓 생성, 
            recv_sock=socket(PF_INET, SOCK_DGRAM, 0); /*멀티캐스트를 위해 UDP소켓 생성 */  
            if(recv_sock == -1)  {
                printf("socket() error\n");  
            }
            memset(&addr, 0, sizeof(addr));  
            addr.sin_family=AF_INET;  
            addr.sin_addr.s_addr=htonl(INADDR_ANY);     
            addr.sin_port=htons(po);       /* 멀티캐스트 port 설정 */  
            int option = 1;
            setsockopt(recv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
            
            if(bind(recv_sock, (struct sockaddr*) &addr, sizeof(addr))==-1){  
                printf("bind() error\n");  
            }
            join_addr.imr_multiaddr.s_addr=inet_addr("224.1.1.2");  
            join_addr.imr_interface.s_addr=htonl(INADDR_ANY);  

            state=setsockopt(recv_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*)&join_addr, sizeof(join_addr));  
            if(state){
                printf("setsockopt() error\n");  
            }

            pidd = fork();

            if(pidd == 0){
                while(1){
                    char b2[BUFSIZE+1];
                    memset(b2, 0, BUFSIZE);
                    recvfrom(recv_sock, b2, BUFSIZE, 0 , NULL, 0);
                    receive_packet(b2);
                }
            }

            else if(pidd > 0 ){
                return 1;
            }
        }
        // 실패
        else if(!strncmp(n, &F, 1)){
            return 0;
        }
    }    
    
    // 04 채팅 메시지 패킷 (채팅방으로 보낸 메시지)
    else if(!strncmp(type, &chat_message_rcv, 1) && !strncmp(mode, &res, 1)){
        // 초기화
        memset(n, 0, sizeof(n));
        memset(buffer, 0, sizeof(buffer));
        memset(buffer2, 0, sizeof(buffer2));

        // 성공, 실패 부분 가져오기
        memset(n, packet[2], 1);

        // 성공
        if(!strncmp(n, &T, 1)){
            return 1;
        }
        // 실패
        else if(!strncmp(n, &F, 1)){
            return 0;
        }
    }

    // 05 채팅 메시지 패킷 (채팅방으로부터 들어온 메시지)
    else if(!strncmp(type, &chat_message_snd,1) && !strncmp(mode, &req, 1)){
        char buf[BUFF_SIZE+1];
        char buf2[BUFF_SIZE+1];
        int sum = 0;

        memset(buf, 0, sizeof(buf));
        memset(buf2, 0, sizeof(buf));

        memset(n, packet[2], 1);
        strncpy(buf, &packet[3], *n);
        sum = n[0];

        memset(n, packet[3+sum], 1);
        strncpy(buf2, &packet[4+sum], *n);

        client_chat2(buf, buf2);
    }
    
    // 06 게시글 패킷
    else if(!strncmp(type, &post,1) && !strncmp(mode, &res, 1)){
        // 초기화
        memset(n, 0, sizeof(n));
        memset(buffer, 0, sizeof(buffer));
        memset(buffer2, 0, sizeof(buffer2));

        // 성공, 실패 부분 가져오기
        memset(n, packet[2], 1);

        // 성공
        if(!strncmp(n, &T, 1)){
            printf("success %d\n", board_idx);
            return 1;
        }
        // 실패
        else if(!strncmp(n, &F, 1)){
            return 0;
        }
    }    
    
    // 07 댓글 패킷
    else if(!strncmp(type, &comment,1) && !strncmp(mode, &res, 1)){
        // 초기화
        memset(n, 0, sizeof(n));
        memset(buffer, 0, sizeof(buffer));
        memset(buffer2, 0, sizeof(buffer2));

        // 성공, 실패 부분 가져오기
        memset(n, packet[2], 1);

        // 성공
        if(!strncmp(n, &T, 1)){
            printf("success\n");
            return 1;
        }
        // 실패
        else if(!strncmp(n, &F, 1)){
            return 0;
        }
    }    
    
    // 08 방 관리 패킷
    else if(!strncmp(type, &manage_room,1) && !strncmp(mode, &res, 1)){
        // 초기화
        memset(n, 0, sizeof(n));
        memset(buffer, 0, sizeof(buffer));
        memset(buffer2, 0, sizeof(buffer2));

        // 성공, 실패 부분 가져오기
        memset(n, packet[2], 1);

        // 성공
        if(!strncmp(n, &T, 1)){
            if(packet[3] == 'R'){
                strcpy(buffer, &packet[4]);
                printf("%s\n", buffer);
                return 1;
            }
            else{
                printf("success\n");
                return 1;
            }
        }
        // 실패
        else if(!strncmp(n, &F, 1)){
            printf("failed\n");
            return 0;
        }
    }
    
    // 09 게시판 관리 패킷
    else if(!strncmp(type, &manage_board,1) && !strncmp(mode, &res, 1)){
        // 초기화
        memset(n, 0, sizeof(n));
        memset(buffer, 0, sizeof(buffer));
        memset(buffer2, 0, sizeof(buffer2));

        // 성공, 실패 부분 가져오기
        memset(n, packet[2], 1);

        // 성공
        if(!strncmp(n, &T, 1)){
            printf("success \n");
            return 1;
        }
        // 실패
        else if(!strncmp(n, &F, 1)){
            return 0;
        }
    }
    
    // 10 채팅방 검색 패킷
    else if(!strncmp(type, &room_search,1) && !strncmp(mode, &res, 1)){
        char list[BUFF_SIZE+1];
        char nn[2];
        // 초기화
        memset(n, 0, sizeof(n));
        memset(nn, 0, sizeof(nn));
        memset(buffer, 0, sizeof(buffer));
        memset(buffer2, 0, sizeof(buffer2));
        memset(list, 0, sizeof(list));

        // 성공, 실패 부분 가져오기
        memset(n, packet[2], 1);
        memset(nn, packet[3], 1);
        strncpy(list, &packet[4], *nn);

        // 성공
        if(!strncmp(n, &T, 1)){
            printf("success\n");
            printf("%s\n", list);
            return 1;
        }
        // 실패
        else if(!strncmp(n, &F, 1)){
            printf("fail\n");
            return 0;
        }
    }    

    // 11 채팅방 팔로우 패킷
    else if(!strncmp(type, &room_follow,1) && !strncmp(mode, &res, 1)){
        char list[BUFF_SIZE+1];
        char nn[2];
        char follow_length[2];

        // 초기화
        memset(n, 0, sizeof(n));
        memset(buffer, 0, sizeof(buffer));
        memset(buffer2, 0, sizeof(buffer2));

        // 성공, 실패 부분 가져오기
        memset(n, packet[2], 1);
        memset(nn, packet[3], 1); // follow 출력
        memset(follow_length, packet[4], 1);
        strncpy(list, &packet[5], *follow_length); // length

        // 성공
        if(!strncmp(n, &T, 1)){
            if(packet[3] == 'R'){
                // printf("Here is your follow \n");
                printf("%s \n", list);
                return 1;
            }
            else{
                return 1;
            }
        }
        // 실패
        else if(!strncmp(n, &F, 1)){
            printf("            fail! \n");
            return 0;
        }
    }

    else {
        printf("%d", packet[0]);
        printf("없음");
        exit(1);
    }
}

// data 앞에 type과 mode를 붙임
void create_packet(char type, char mode, char *data ,char *buf){
	strncat(buf, &type, 1); // type 붙여주고
	strncat(buf, &mode, 1); // mode 붙여주고
    strcat(buf, data); // data 붙여주고
}

// 패킷을 전송
void send_packet(int sockfd, char *buf, struct sockaddr_in servAddr){
    if(!sendto(sockfd, buf, BUFF_SIZE, 0, (struct sockaddr*) &servAddr, sizeof(servAddr))) {
        perror("sendto failed");
        exit(1);
    }
}