#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>

#define BUFSIZE 512

int main(int argc, char *argv[]){

    //ファイル構造体へのポインタを宣言
    FILE *fp;
    int s;
    int con_flag;
    struct sockaddr_in server;
    u_short port;
    int len = 0;
    int counter = 0;
    int con_counter = 1;
    char send_buf[BUFSIZE];
    int send_len;
    char recv_buf[BUFSIZE];
    int recv_len;

    char *adr1;
    char *adr2;

    //ファイルを読み込みモードで開く
    fp = fopen("../../datasets/csic2010/anomalousTrafficTest.txt","r");

    //ファイルオープンに失敗した場合
    if(fp == NULL){
        printf("file open failed\n");
        return -1;
    }

    //argument check
    if(argc != 3){
        printf("Usage: %s ipaddr port\n", argv[0]);
        exit(1);
    }

    //create socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s<0){
        perror("Socket Error\n");
        exit(1);
    }

    //set socket addr of server
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    port = atoi(argv[2]);
    server.sin_port = htons(port);

    //create connection to server
    con_flag = connect(s, (struct sockaddr *)&server, sizeof(server));
    if(con_flag < 0){
        perror("Connect Error\n");
        exit(1);
    }
    printf("Connected to %s\n", inet_ntoa(server.sin_addr));
    printf("1st conection.\n");


    while((fgets(send_buf,BUFSIZE,fp)) != NULL){

        adr1 = strstr(send_buf, "GET");
        //if(adr1 != NULL) counter++;

        adr2 = strstr(send_buf, "POST");
        //if(adr2 != NULL) counter++;

        if(adr1 != NULL || adr2 != NULL){
            
            counter++;
            close(s);
            printf("**************************************\n");

            s = socket(AF_INET, SOCK_STREAM, 0);
            if(s<0){
                perror("Socket Error\n");
                exit(1);
            }

            //set socket addr of server
            memset(&server, 0, sizeof(server));
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = inet_addr(argv[1]);
            port = atoi(argv[2]);
            server.sin_port = htons(port);

            //create connection to server
            con_flag = connect(s, (struct sockaddr *)&server, sizeof(server));
            if(con_flag < 0){
                perror("Connect Error\n");
                exit(1);
            }
            printf("Connected to %s\n", inet_ntoa(server.sin_addr));
        
            printf("%d th conection.\n", counter);

            printf("%s", send_buf);
            
            send_len = strlen(send_buf);
            printf("%d\n",send_len);
            send(s, send_buf, send_len, 0);        

        } else {
            
            printf("%s", send_buf);
            
            send_len = strlen(send_buf);
            printf("%d\n",send_len);
            send(s, send_buf, send_len, 0);   
        }
       
    }

    close(s);

    //ファイルを閉じる
    fclose(fp);

    return 0;
}
