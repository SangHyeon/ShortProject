#include <stdio.h>
#include<stdlib.h>
#define MAXLINE 256

int main()
{
    FILE *fp;
    int state;

    char buff[MAXLINE];
    fp = popen("python test.py", "r");
    if (fp == NULL)
    {
        perror("erro : ");
        exit(0);
    }
    
    state = pclose(fp);
    

    
    printf("state is %d\n", state);
}
