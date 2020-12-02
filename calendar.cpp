#include "calendar.hpp"

int sumOfRange(int low, int high, int (*term)(int), int (*next)(int)) {
    int i, result = 0;

    for (i = low; i <= high; i = (*next)(i)) {
        result += (*term)(i);
    }

    return result;
}

int leapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int inc(int x) { return x + 1; }

int yearTerm(int year) { return leapYear(year) ? 366 : 365; }

int daysOfYear(int low, int high) {
    return sumOfRange(low, high, yearTerm, inc);
}

int monthTerm(int month) { return months[month]; }

int daysOfMonth(int low, int high, int year) {
    int days = sumOfRange(low, high, monthTerm, inc);

    return low <= 2 && high >= 2 && leapYear(year) ? days + 1 : days;
}

void preFixed(int times) {
    while (times--)
        printf("\t");
}

void calendar(int days, int year, int month) {
    int i, month_day;
    printf("******************************************************\n");

    printf("\n\t\t%d\t\t%d\n\n", year, month);
    printf("MON\tTUE\tWED\tTHU\tFRI\tSAT\tSUN\n");

    if (month == 2)
        months[month] = leapYear(year) ? 29 : 28;

    preFixed((days) % CYCLE);
    for (i = 1; i <= months[month]; i++) {
        printf("%d%c", i, (days + i) % CYCLE ? '\t' : '\n');
    }

    printf("\n\n");
    printf("******************************************************\n");
}

int is_number(char *target) {
    while (*target != '\0' && *target >= '0' && *target <= '9')
        target++;

    return *target == '\0';
}

int mainCalendar() {
    int year = 0, month = 0;
    int i, days = 0;

    struct tm *time_ptr;
    time_t timeval;

    int number;
    printf("*************** Calendar ****************\n");
    printf("\n");
    printf("# 1. Print Current Month Calendar. \n"); //월을 출력
    printf("# 2. Print Year Calendar that you Choose. \n");
    //특정 년도를 입력하면, 특정 년의 모든 월을 출력

    printf("# 3. Print Month Calendar that you Choose. \n");
    //특정 년도와 월을 입력하면 해당하는 달력을 출력

    printf("\n");
    printf("* Select Number : ");
    scanf("%d", &number);
    printf("\n");

    switch (number) {
    case 1:
        (void)time(&timeval);
        time_ptr = localtime(&timeval);

        year = time_ptr->tm_year + 1900;
        month = time_ptr->tm_mon + 1;
        days += daysOfYear(START_YEAR, year - 1);
        days += daysOfMonth(1, month - 1, year);

        calendar(days, year, month);
        break;

    case 2:
        printf("* Enter Year : ");
        scanf("%d", &year);
        if (year < 1900) {
            printf("# Invailed Year ! \n");
            break;
        }

        days += daysOfYear(START_YEAR, year - 1);
        for (i = 1; i <= 12; i++) {
            calendar(days, year, i);
            days += months[i];
        }
        break;

    case 3:
        printf("* Enter Year : ");
        scanf("%d", &year);
        if (year < 1900) {
            printf("# Invailed Year !\n");
            break;
        }
        printf("* Enter Year : : ");
        scanf("%d", &month);
        if (1 > month || month > 12) {
            printf("# Invailed Month !\n");
            break;
        }
        days += daysOfYear(START_YEAR, year - 1);
        days += daysOfMonth(1, month - 1, year);

        calendar(days, year, month);
        break;

    default:
        fprintf(stderr, "# Invailed Input ! \n");
    }

    return 0;
}
