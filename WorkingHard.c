#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLINE 256

int main()
{
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
    
    //running check program
    dp1 = popen("cat result", "r");
    dp2 = popen("cat answer", "r");
    
    while(fgets(buff, MAXLINE, dp1) != NULL && fgets(buff2, MAXLINE, dp2) != NULL) {
        if(strcmp(buff, buff2) != 0)
            flag = 1;
        printf("============> %s", buff);
    }
    if(flag)
        result = 0;
    else
        result = 1;
    printf("====> %d\n", result);
    printf("state is %d\n", state);
}
