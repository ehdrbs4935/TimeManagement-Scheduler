#include "calendar.h"
#include "saveTime.h"

int start() {
    int N;
    fflush(stdin);
    printf("####### Time Scheduler ####### \n");
    printf("-------------------------------\n");
    printf("# 0. Exit             \n");
    printf("# 1. Check Calendar   \n");
    printf("# 2. Record Time        \n");
    printf("# 3. Read Time       \n");
    printf("# 4. .........        \n");
    printf("\n");
    printf("* Select Number : ");
    scanf("%d", &N);
    printf("\n");
    return N;
}

int main(void) {

    while (1) {

        int menu = start();

        if (menu == 0)
            break;

        else if (menu == 1) {
            mainCalendar();
        }

        else if (menu == 2)
            recordTime();

        else if (menu == 3) {
            readTime();
        }

        else if (menu == 4) { //기능추가..
        }

        printf("\n");
    }

    return 0;
}
