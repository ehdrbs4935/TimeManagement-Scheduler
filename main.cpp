#include "Schedule.hpp"
#include "calendar.hpp"
#include "saveTime.hpp"

int initial() {
    int N;
    fflush(stdin);
    printf("####### Time Scheduler ####### \n");
    printf("-------------------------------\n");
    printf("# 0. Exit             \n");
    printf("# 1. Sign in   \n");
    printf("# 2. Sign up        \n");
    printf("\n");
    printf("* Select Number : ");
    scanf("%d", &N);
    printf("\n");
    return N;
}

int start() {
    int N;
    fflush(stdin);
    printf("####### Time Scheduler ####### \n");
    printf("-------------------------------\n");
    printf("# 0. Exit             \n");
    printf("# 1. Check Calendar   \n");
    printf("# 2. Record Time        \n");
    printf("# 3. Read Time       \n");
    printf("# 4. Add Schedule       \n");
    printf("# 5. Category View      \n");
    printf("# 6. Date View         \n");
    printf("# 7. Delete Schedule   \n");
    printf("\n");
    printf("* Select Number : ");
    scanf("%d", &N);
    printf("\n");
    return N;
}

int main(void) {

    while (1) {
        int input = initial();

        if (input == 0)
            return 0;
        else if (input == 1) {
            system("clear");
            signin();
            break;
        } else if (input == 2) {
            system("clear");
            signup();
            system("clear");
        }
    }

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

        else if (menu == 4) {
            system("clear");
            addschedule();
        } else if (menu == 5) {
            system("clear");
            cviewschedule();
        } else if (menu == 6) {
            system("clear");
            dviewschedule();
        } else if (menu == 7) {
            system("clear");
            delschedule();
        }

        printf("\n");
    }

    return 0;
}
