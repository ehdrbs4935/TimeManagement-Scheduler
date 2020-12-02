#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define START_YEAR 1900
#define CYCLE 7

static int months[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int sum_of_range(int low, int high, int (*term)(int), int (*next)(int));
int leapYear(int year);
int inc(int x);
int yearTerm(int year);
int daysOfYear(int low, int high);
int monthTerm(int month);
int daysOfMonth(int low, int high, int year);
void preFixed(int times);
void calendar(int days, int year, int month);
int is_number(char *target);
int mainCalendar();
