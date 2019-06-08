/*
최초자성자 : 한도경

최초작성일 : 2019-05-28

최초변경일 : 2019-05-28

프로그램 목적 : 프로젝트

개정이력 :
(2019-05-28) server_choice_chat_room, server_chat 함수 작성
(2019-06-01) 공유메모리를 활용한 채팅방 입장

저작권 : 5조
*/

#include "header.h"
#define BUFSIZE 1024

// 채팅방 입장 처리
void server_choice_chat_room(char *roomname)
{
  int i = 0;
  int index = 0;
  void *shmaddr = (void *)1;

  /* 1234 키의 공유메모리 있으면 접근해서 식별자 얻음 */
  if ((shmid = shmget((key_t)1234, 1024000, IPC_CREAT | 0666)) == -1)
  {
    perror("shmid failed");
    exit(1);
  }

  // /* shmid 공유메모리를 호출 프로세스 메모리 영역으로 첨부 */
  if ((shmaddr = shmat(shmid, (void *)0, 0)) == (void *)-1)
  {
    perror("shmat failed");
    exit(1);
  }

  roomList = (struct roomList *)shmaddr;

  // 방 인덱스 찾는다.
  for (i = 0; i < 3000; i++)
  {
    // 방 없음
    if (roomList[i].room_name[0] == '\0')
    {
      memset(buffer, 0, BUFSIZE + 1);
      memset(buffer2, 0, BUFSIZE + 1);

      // 채팅방 입장 실패 응답
      memset(buffer, 2, 1);                 // 실패 2
      create_packet(3, 2, buffer, buffer2); // 응답패킷 만들어서
      write(s1.sock, buffer2, BUFSIZE);     //전송
      printf("[RES] enter_room failed: ID (%s), ROOM_NAME (%s)\n", u1.ID, roomname);
      break;
    }
    // 방 있음
    if (!strcmp(roomname, roomList[i].room_name))
    {
      room_idx = i;
      // 방에 유저 추가한다.
      for (index = 0; index < 50; index++)
      {
        // 만약 방에 이미 있다면 정보 업데이트
        if (!strcmp(roomList[i].roomUserList[index].userInfo.ID, u1.ID))
        {
          roomList[i].roomUserList[index].socketInfo.sock = s1.sock;
          roomList[i].roomUserList[index].socketInfo.clntAddr = s1.clntAddr;
          break;
        }
        // 방에 없다면 넣음
        if (roomList[i].roomUserList[index].userInfo.ID[0] == '\0')
        {
          strcpy(roomList[i].roomUserList[index].userInfo.ID, u1.ID);
          roomList[i].roomUserList[index].socketInfo.sock = s1.sock;
          roomList[i].roomUserList[index].socketInfo.clntAddr = s1.clntAddr;
          break;
        }
      }
      // 공유메모리에 저장된 데이터 출력
      for (int j = 0; j <= 50; j++)
      {
        if (roomList[i].roomUserList[j].userInfo.ID[0] == '\0')
        {
          break;
        }
        else
        {
          printf("%s : %s\n", roomList[i].room_name, roomList[i].roomUserList[j].userInfo.ID);
        }
      }

      memset(buffer, 0, BUFSIZE + 1);
      memset(buffer2, 0, BUFSIZE + 1);

      // 채팅방 입장 성공 응답
      memset(buffer, 1, 1);                       // 성공 1
      create_packet(3, 2, buffer, buffer2);       // 응답패킷 만들어서
      send_packet(s1.sock, buffer2, s1.clntAddr); // 전송
      printf("[RES] enter_room success: ID (%s), ROOM_NAME (%s)\n", u1.ID, roomname);
      break;
    }
  }

  // 공유메모리에 데이터 쓰기
  memcpy((void *)shmaddr, roomList, sizeof(roomList));

  // /* 공유메모리를 호출 프로세스의 메모리 영역에서 분리 */
  if (shmdt(shmaddr) == -1)
  {
    perror("shmdt failed");
    exit(1);
  }
}

// 채팅 메시지 처리
void server_chat(char *message)
{
  int a;
  int i = 0;
  int index = 0;
  pid_t pid;
  void *shmaddr = (void *)1;

  a = sizeof(s1.clntAddr);
  memset(buffer, 0, BUFSIZE + 1);
  memset(buffer2, 0, BUFSIZE + 1);

  // 채팅 메시지 수신 성공 응답
  memset(buffer, 1, 1);                       // 성공 1
  create_packet(4, 2, buffer, buffer2);       // 응답패킷 만들어서
  send_packet(s1.sock, buffer2, s1.clntAddr); // 전송
  printf("[RES] message(room -> user) success: MESSAGE (%s), ROOM_NAME (%s)\n", message, room_name);

  sleep(0.1);

  /* 1234 키의 공유메모리 있으면 접근해서 식별자 얻음 */
  if ((shmid = shmget((key_t)1234, 1024000, IPC_CREAT | 0666)) == -1)
  {
    perror("shmid failed");
    exit(1);
  }

  // /* shmid 공유메모리를 호출 프로세스 메모리 영역으로 첨부 */
  if ((shmaddr = shmat(shmid, (void *)0, 0)) == (void *)-1)
  {
    perror("shmat failed");
    exit(1);
  }

  roomList = (struct roomList *)shmaddr;

  for (i = 0; i < 50; i++)
  {
    // 끝이면
    if (roomList[room_idx].roomUserList[i].userInfo.ID[0] == '\0')
    {
      break;
    }
    memset(buffer, 0, BUFSIZE + 1);
    memset(buffer2, 0, BUFSIZE + 1);

    memset(buffer, strlen(message), 1);
    strcat(buffer, message);
    create_packet(5, 1, buffer, buffer2);

    pid = fork();

    if (pid == 0)
    {
      send_packet(roomList[room_idx].roomUserList[i].socketInfo.sock, buffer2, roomList[room_idx].roomUserList[i].socketInfo.clntAddr);
      // send_packet(s1.sock, buffer2, s1.clntAddr);
      printf("[REQ] message(room -> user): MESSAGE (%s), ROOM_NAME (%s)\n", buffer, room_name);

      // 여기 타이머 두어서 시간 내에 응답 없으면 채팅방에서 내보내기
      memset(buffer, 0, BUFSIZE + 1);
      // read(s1.sock, buffer, BUFSIZE);
      // receive_packet(buffer);
      exit(1);
    }
  }

  // /* 공유메모리를 호출 프로세스의 메모리 영역에서 분리 */
  if (shmdt(shmaddr) == -1)
  {
    perror("shmdt failed");
    exit(1);
  }
}

void server_chat2()
{
  // 응답처리
}

void server_room_search(char *room_name)
{
  // 변수 선언
  char data[BUFSIZE + 1];
  char buf[BUFSIZE + 1];
  char query[BUFSIZE + 1] = "call searchChat(\"";
  char chat_list[BUFSIZE + 1] = "";

  // 초기화
  memset(data, 0, BUFSIZE + 1);
  memset(buf, 0, BUFSIZE + 1);

  // 채팅방 검색
  strcat(query, room_name);
  strcat(query, "\")");

  if (runQuery(query) < 0) { // 쿼리실행 실패시
    printf("[ERR] Procedure query fail \n");
  }
  // 쿼리 실행 성공시
  else {
    printf("Running Query : %s \n", query);

    row = mysql_fetch_row(res);
    printf("return : %s\n", row[0]);

    closeDB();
    connectDB();
    // 채팅방 존재 여부 확인 존재 : 1, 부재 : 0
    if (!strcmp(row[0], "1")) {
      // 채팅방 검색 성공 응답
      memset(query, 0, BUFSIZE+1);

      strcat(query, "SELECT * FROM chatroom WHERE c_name LIKE \"%%");
      strcat(query, room_name);
      strcat(query, "%%\"");

      if (runQuery(query) < 0) { // 쿼리실행 실패시
        printf("[ERR] SELECT query fail \n");
      }
      
      while ((row = mysql_fetch_row(res)) != NULL ) {
        printf("%50s \n", row[0]);
        strcat(chat_list, row[0]);
        strcat(chat_list, "\n");
      }
      
      // 
      memset(data, 1, 1);
      memset(&data[1], strlen(chat_list), 1); // 채팅방 존재
      //chat list 길이, 내용 붙이기
      strcat(data, chat_list);

      create_packet(10, 2, data, buf);    // 응답패킷 만들어서
      write(s1.sock, buf, BUFSIZE);

      printf("[RES] search_room success: ROOM_NAME (%s)\n", chat_list);
    }
    else {
      memset(data, 2, 1);                  // 채팅방 부재
      create_packet(10, 2, data, buf);
      write(s1.sock, buf, BUFSIZE);
      printf("[RES] search_room fail. no exist room \n");
    }
  }
}

void server_search_room_follow()
{
  // 변수 선언
  char data[BUFSIZE + 1];
  char buf[BUFSIZE + 1];
  char query[BUFSIZE + 1] = "SELECT c_name FROM follow WHERE u_id = \"";
  char chat_list[BUFSIZE + 1] = "";

  // 초기화
  memset(data, 0, BUFSIZE + 1);
  memset(buf, 0, BUFSIZE + 1);

  // 쿼리문 생성
  strcat(query, "hyunsu");
  strcat(query, "\"");

  if (runQuery(query) < 0) { // 쿼리실행 실패시
    printf("[ERR] Procedure query fail \n");
  }
  // 쿼리 실행 성공시
  else {
    printf("Running Query : %s \n", query);

    if ((row = mysql_fetch_row(res)) != NULL ) {

      printf("%50s \n", row[0]);
      strcat(chat_list, row[0]);
      strcat(chat_list, "\n");
      
      while ((row = mysql_fetch_row(res)) != NULL ) {
        printf("%50s \n", row[0]);
        strcat(chat_list, row[0]);
        strcat(chat_list, "\n");
      }

      // search 에서 3 성공 / 4 실패
      memset(data, 3, 1);
      memset(&data[1], strlen(chat_list), 1); // 채팅방 길이
      //chat list 길이, 내용 붙이기
      strcat(data, chat_list);

      create_packet(11, 2, data, buf);    // 응답패킷 만들어서
      write(s1.sock, buf, BUFSIZE);

      printf("[RES] follow_room success: ROOM_NAME (%s)\n", chat_list);
    }
    else {
      memset(data, 4, 1);                  // 채팅방 부재
      create_packet(11, 2, data, buf);
      write(s1.sock, buf, BUFSIZE);
      printf("[RES] search_room fail. no exist room \n");
    }
  }

  closeDB();
  connectDB();
}

void server_room_follow(char *room_name)
{
  // 변수 선
  char data[BUFSIZE + 1];
  char buf[BUFSIZE + 1];
  char query[BUFSIZE+1] = "INSERT INTO follow VALUES (\"";

  strcat(query, room_name);
  strcat(query, "\",\"");
  strcat(query, "hyunsu");
  strcat(query, "\")");

  // 초기화
  memset(data, 0, BUFSIZE + 1);
  memset(buf, 0, BUFSIZE + 1);
  printf("here\n");

  printf("Run Query : %s \n", query);
  
  closeDB();
  connectDB();

  if (runQuery(query) < 0) { // Query 실행 실패시 ErrMsg 출력
    printf("[ERR] Procedure query fail \n");

    memset(data, 2, 1); // 실패 2
    create_packet(11, 2, data, buf); // 응답패킷 만들어서
    write(s1.sock, buf, BUFSIZE);
    printf("[RES] follow_room fail: ROOM_NAME (%s)\n", room_name);
  }
  else { // Query 성공적 실행 시
    memset(data, 1, 1); // 성공 1
    memset(&data[1], strlen(room_name), 1);
    strcat(data, room_name);

    create_packet(11, 2, data, buf); // 응답패킷 만들어서
    write(s1.sock, buf, BUFSIZE);
    printf("[RES] follow_room success: ROOM_NAME (%s)\n", room_name);
  }
}