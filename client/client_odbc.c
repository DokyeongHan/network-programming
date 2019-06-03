#include <mysql/mysql.h>
#include <stdio.h>

MYSQL_RES *res;
MYSQL_ROW row;
MYSQL *conn;

int     runQuery(char *query);
int     fetchRow(void);
void    fetchfieldbyID(int id, char *buffer, int len);
void    fetchfieldbyName(const char *name, char *buffer, int len);
int     connectDB(void);
void    closeDB(void);
void    errorMsg(char *errMsg);

int main() {
        int rt = 0;

        if (connectDB() < 0) {
                return -1;
        }

        printf("원하시는 작업을 입력해 주세요. \n");
        printf("1: 게시판확인   2: 아이디 확인");

        while(1) {
          scanf("%d", &rt);

          switch(rt) {
            case 1:
              print_post();
              break;
            case 2:
              print_user();
              break;
          }

        }


        closeDB();

        return 0;
}

void print_post(){

        if (runQuery("select title, content from posts limit 5") < 0) {
                return -2;
        }

        printf("%+50s   %-15s \n", "title", "content");
        while ((row = mysql_fetch_row(res)) != NULL )
        {
                printf("%+50s   %-15s", row[0], row[1]);
                printf("\n");
        }

}

void print_user(){

        if (runQuery("select u_id, u_pw from auth limit 5") < 0) {
                return -2;
        }

        printf("%+50s   %-15s \n", "user_id", "user_pw");
        while ((row = mysql_fetch_row(res)) != NULL )
        {
                printf("%+50s   %-15s", row[0], row[1]);
                printf("\n");
        }
}
// 쿼리 실행
int runQuery(char *query)
{
        if(mysql_query(conn, query)) {
                errorMsg("MySQL Query Excute failed");
                return -1;
        }

        res = mysql_store_result(conn);
        return 0;
}

//로우 조회
int fetchRow(void)
{
        if(res) {
                row = mysql_fetch_row(res);
                if(!row) {
                        errorMsg("MySQL Fetch failed");
                        return -1;
                }
                return 0;
        }
        errorMsg("MySQL Query Result Null");
        return -2;
}

//로우 아이디별로 값 조회
void fetchfieldbyID(int id, char *buffer, int len)
{
        if(row[id]) {
                strncpy(buffer, row[id], len);
        } else {
                errorMsg("MySQL Query Result Null");
        }
}

// 필드 이름으로 값 조회
void fetchfieldbyName(const char *name, char *buffer, int len)
{
        MYSQL_FIELD *fields;
        int num_fields;
        int i;

        if(res) {
                num_fields = mysql_num_fields(res);
                fields = mysql_fetch_fields(res);

                for(i = 0; i < num_fields; i++) {
                        if(!strcmp(fields[i].name, name)) {
                                if(row[i]) {
                                    strncpy(buffer, row[i], len);
                                    return;
                                }
                        }
                }

        } else {
                errorMsg("MySQL Query Result Null");
        }
}

// 디비 연결
int connectDB(void)
{
        char *server = "114.70.234.223";
        char *user = "root";
        char *password = "ul9968uj";
        char *database = "np_project";       
 
        conn = mysql_init(NULL);       
        if (conn == NULL) {
                errorMsg("MySQL init fail");
                return -1;
        }
        if(!mysql_real_connect(conn, server, 
           user, password, database , 3306, (char *)NULL, 0)) {
                errorMsg("MySQL connect fail");
                return -2;
        }
        return 0;
        
}

// 디비 연결 해제
void closeDB(void)
{
        if (res)
                mysql_free_result(res);
        mysql_close(conn);
} 

// 에러 메세지 출력
void errorMsg(char *errMsg)
{
        printf("t%s",errMsg);
        printf("nntError Meassage : %sn", mysql_error(conn));
}