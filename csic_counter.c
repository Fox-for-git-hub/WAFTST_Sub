#include <stdio.h>
#include <string.h>

#define BUFSIZE 512

int main() {

    char *target1 = "GET";
    char *target2 = "POST";
    char *adr1;
    char *adr2;
    int counter1 = 0;
    int counter2 = 0;
    char str_buf[BUFSIZE];

    //ファイル構造体へのポインタを宣言
    FILE *fp;

    printf("[TARGET STRING : %s %s]\n\n", target1, target2);

    //ファイルを読み込みモードで開く
    fp = fopen("../../datasets/csic2010/anomalousTrafficTest.txt","r");

    //ファイルオープンに失敗した場合
    if(fp == NULL){
        printf("file open failed\n");
        return -1;
    }

    while((fgets(str_buf,BUFSIZE,fp)) != NULL){

        printf("%s", str_buf);

        // 指定文字列での文字列検索
        adr1 = strstr(str_buf, target1);
        if(adr1 != NULL) counter1++;
        printf("文字列の検索結果: %s\n", adr1); //test
    
        // 指定文字列での文字列検索(該当文字列なしの場合)
        adr2 = strstr(str_buf, target2);
        if(adr2 != NULL) counter2++;
        printf("文字列の検索結果: %s\n", adr2); //test

        //test
        printf("TARGET 1 : %d\n", counter1);
        printf("TARGET 2 : %d\n", counter2);

    }

    //Result
    printf("TARGET 1 : %d\n", counter1);
    printf("TARGET 2 : %d\n", counter2);
    

    //ファイルを閉じる
    fclose(fp);

    return 0;
}