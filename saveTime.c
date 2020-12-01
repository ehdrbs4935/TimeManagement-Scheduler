#include "saveTime.h"

int input() {
    char c;
    while (getchar() != '\n')
        ;
    fflush(stdin);
    printf(
        "# Will you Record the time ? (Y/N): "); //사용시간을 기록할 것인가?..
    scanf("%c", &c);

    return (c == 'Y' || c == 'y');
}

void FileData() {
    memset(date, '\0', 100);
    time_t t = time(NULL);
    struct tm *p = localtime(&t);
    char temp[5] = "";

    sprintf(temp, "%d", (p->tm_year + 1900));
    strcat(date, temp);
    strcat(date, ".");

    sprintf(temp, "%d", p->tm_mon + 1);
    strcat(date, temp);
    strcat(date, ".");

    sprintf(temp, "%d", p->tm_mday);
    strcat(date, temp);

    // strcat(date, ".txt");   //text형태로 굳이 만들지 않아도 됨.
}

void calculateTime(int isStart) {
    time_t t = time(NULL);
    struct tm *p = localtime(&t);
    char temp[5] = "", timeArr[100] = "";

    sprintf(temp, "%d", p->tm_hour);
    strcat(timeArr, temp);
    strcat(timeArr, ":");
    sprintf(temp, "%d", p->tm_min);
    strcat(timeArr, temp);
    strcat(timeArr, "\n");

    if (isStart == 1) {
        memset(startTime, '\0', 100);
        strcat(startTime, "begin: ");
        strcat(startTime, timeArr);

    } else {
        memset(endTime, '\0', 100);
        strcat(endTime, "end: ");
        strcat(endTime, timeArr);
    }
}

void showStartMessage() {
    printf("\n################################\n");
    printf("# Now Recording Time...................\n");
    printf("# Enter 'quit' to finish Record\n");
}

void showEndMessage() {
    printf("# Terminate Recoring Time....!\n");
    printf("##################################\n\n");
}

void writeMessage() {
    showStartMessage();
    fflush(stdin);
    char c;
    while (1) {
        char buf[CONTENT_SIZE] = "";
        int i = 0;

        while (1) {
            scanf("%c", &c);
            buf[i++] = c;

            if (c == '\n')
                break;
        }

        if (strcmp(buf, "quit\n") == 0)
            break;
    }

    showEndMessage();
}

void recordTime() {
    if (input()) {

        FileData(); //현재 날짜를 data에

        int fd = open(date, O_CREAT | O_RDWR | O_APPEND,
                      0777); //현재날짜에 해당하는 파일 생성, 여기서 사용시간을
                             //읽고 쓸 것.

        record *record1 = (record *)malloc(sizeof(record));
        memset(record1->name, '\0', 20);

        char buf[30];
        printf("# Enter your working message :  ");
        getchar(); //입력버퍼 비우기위해.
        fgets(buf, sizeof(buf), stdin);
        strcpy(record1->name, buf);

        // write(fd, buf, sizeof(buf));

        calculateTime(1); //시작 시간 저장

        writeMessage();

        calculateTime(0); //끝나는 시간 저장

        strcpy(record1->startTimeSet, startTime);
        strcpy(record1->endTimeSet, endTime);

        // write(fd, startTime, strlen(startTime));
        write(fd, (record *)record1, sizeof(record));

        // 총합 시간 계산
        printf("## Time record \n\n");
        printf("# %s\n", buf);
        printf("# %s\n", startTime);
        printf("# %s\n", endTime);

        free(record1);

        close(fd);
    } else
        printf("Cancel Record ! \n");
}

void readTime() {

    printf("####  Show All recored time #### \n\n");
    printf("######################### \n");

    record *record1 = (record *)malloc(sizeof(record));

    int fd = open(date, O_RDWR);
    if (fd == -1) {
        printf("# You must Record Time First! \n");
        return;
    }

    char buf[1000];
    while (read(fd, (record *)record1, sizeof(record)) > 0) {
        printf("\n");
        printf("#Task name : %s\n", record1->name);
        printf("#Task %s\n", record1->startTimeSet);
        printf("#Task %s\n", record1->endTimeSet);
        printf("######################### \n");
    }

    free(record1);

    close(fd);
}
