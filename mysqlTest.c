#include "/usr/include/mysql/mysql.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define DB_HOST "211.189.127.127"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "teamAlgo"
#define CHOP(x) x[strlen(x) - 1] = ' '

int main(){
	
    FILE *fp;
    FILE *dp1;
    FILE *dp2;
    int state;
    int result = -1;

    int flag = 0;
    char buff[MAXLINE];
    char buff2[MAXLINE];
    char py_cmd[20] = "python test.py ";
    char pro_num[10];
    char pro_code[100000];
    
    MYSQL		*connection = NULL;
	MYSQL		conn;
	MYSQL_RES	*sql_result;
	MYSQL_ROW	sql_row;
	int			query_stat;

	char query[6000];

	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS,
							DB_NAME, 3306 /*port*/, (char *)NULL, 0);
	
	if(connection == NULL) {
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return 1;
	}

	query_stat = mysql_query(connection, "select * from submitcode where result = 0");
	if(query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	sql_result = mysql_store_result(connection);

	while( (sql_row = mysql_fetch_row(sql_result)) != NULL) {
		printf("%+11s %-10s\n", sql_row[2], sql_row[3]);
	}//2:code, 3:num

    pro_num = sql_row[3];
    CHOP(pro_num);
    pro_code = sql_row[2];
    CHOP(pro_code);

    //merge string by strcat
    strcat(py_cmd, pro_num);
    strcat(py_cmd, " ");
    strcat(py_cmd, pro_code);
    fp = popen(py_cmd, "r");
    if (fp == NULL)
    {
        perror("erro : ");
        exit(0);
    }

    state = pclose(fp);

    dp1 = popen("cat result", "r");
    dp2 = popen("cat answer", "r");
    
    while(fgets(buff, MAXLINE, dp1) != NULL && fgets(buff2, MAXLINE, dp2) != NULL) {
        if(strcmp(buff, buff2) != 0)
            flag = 1;
        printf("============> %s", buff);
    }
    if(flag)
        result = 2;//wrong
    else
        result = 1;//accept
    printf("====> %d\n", result);
    printf("state is %d\n", state);
    //update submitcode set result = where code = sql_row[2] and num = sql_row[3]
	mysql_free_result(sql_result);

	query_stat = mysql_query(connection, query);
	if(query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	mysql_close(connection);
}
