#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

#include <string>

#define MAX_TEXT_LEN 100
#define MAX_CATEGORY_LEN 20
using namespace std;

class Schedule {
  public:
    Schedule();
    Schedule(string text, int date, int time, string categoty, int importance);

    void setText(string text);
    void setDate(int date);
    void setTime(int time);
    void setCategory(string category);
    void setImportance(int importance);

    string getText(void);
    int getDate(void);
    int getTime(void);
    string getCategory(void);
    int getImportance(void);
    void print(void);

  private:
    char text[MAX_TEXT_LEN];
    int date;
    int time;
    char category[MAX_CATEGORY_LEN];
    int importance;
};

void signin();        //  프로그램 로그인 함수
void signup();        //  프로그램 회원가입 함수
void addschedule();   //  스케줄 추가 함수
void cviewschedule(); //  카테고리로 분류된 스케줄 보기 함수
void dviewschedule(); //  날짜별로 분류된 스케줄 보기 함수
void delschedule();   //  저장된 스케줄을 삭제하는 함수

#endif
