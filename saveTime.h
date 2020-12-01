#ifndef saveTime
#define saveTime

#define _CRT_SECURE_NO_WARNINGS
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define CONTENT_SIZE 1000

char date[100];
char startTime[100], endTime[100];

struct Record {
    char name[20];
    char startTimeSet[100];
    char endTimeSet[100];
};
typedef struct Record record; //이 구조체에 컴퓨터를 이용한 작업의 사용시작
                              //시간, 사용종료 시간, 작업이름이 저장됨.

int input();
void FileData();
void calculateTime(int isStart);
void showStartMessage();
void showEndMessage();
void writeMessage();
void recordTime();
void readTime();
#endif
