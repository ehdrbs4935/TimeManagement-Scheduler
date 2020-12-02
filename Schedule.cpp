#include "Schedule.hpp"
#include <algorithm>
#include <fcntl.h>
#include <iostream>
#include <list>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#define MAX_ID_LEN 10
#define MAX_PWD_LEN 10

Schedule::Schedule() {
    memset(this->text, 0x00, MAX_TEXT_LEN + 1);
    this->date = -1;
    this->time = -1;
    memset(this->category, 0x00, MAX_CATEGORY_LEN + 1);
    this->importance = -1;
}

Schedule::Schedule(string text, int date, int time, string category,
                   int importance) {
    memcpy(this->text, text.c_str(), MAX_TEXT_LEN);
    this->date = date;
    this->time = time;
    memcpy(this->category, category.c_str(), MAX_CATEGORY_LEN);
    this->importance = importance;
}

void Schedule::setText(string text) {
    memcpy(this->text, text.c_str(), MAX_TEXT_LEN);
}

void Schedule::setDate(int date) { this->date = date; }

void Schedule::setTime(int time) { this->time = time; }

void Schedule::setCategory(string category) {
    memcpy(this->category, category.c_str(), MAX_CATEGORY_LEN);
}

void Schedule::setImportance(int importance) { this->importance = importance; }

string Schedule::getText(void) { return string(this->text); }

int Schedule::getDate(void) { return this->date; }

int Schedule::getTime(void) { return this->time; }

string Schedule::getCategory(void) { return string(this->category); }

int Schedule::getImportance(void) { return this->importance; }

// 스케줄의 정보를 출력하는 함수
void Schedule::print(void) {
    // 시간의 자릿수를 number에 저장합니다.
    int number = 0;
    int temp = this->time;
    while (temp > 0) {
        number++;
        temp /= 10;
    }
    // int 형의 date와 time을 string 형으로 변경합니다.
    string date = to_string(this->date);
    string time = to_string(this->time);

    if (number == 3) {
        cout << "Date/Time: " << date.insert(4, "-").insert(7, "-") << " / "
             << time.insert(1, ":") << endl;
    }
    if (number == 4) {
        cout << "Date/Time: " << date.insert(4, "-").insert(7, "-") << " / "
             << time.insert(2, ":") << endl;
    }

    cout << "Category: " << this->category << endl;
    cout << "Content: " << this->text << endl;
    if (this->importance == 0)
        cout << "Important" << endl;
    else
        cout << "Unimportant" << endl;
}

/*
//
// 프로그램 계정 클래스
//
*/

class Account {
  public:
    Account() {
        memset(this->id, 0x00, MAX_ID_LEN + 1);
        memset(this->pwd, 0x00, MAX_PWD_LEN + 1);
    }
    Account(string id, string pwd) {
        memcpy(this->id, id.c_str(), MAX_ID_LEN);
        memcpy(this->pwd, pwd.c_str(), MAX_PWD_LEN);
    }
    string getid() { return string(this->id); }
    string getpwd() { return string(this->pwd); }

  private:
    char id[MAX_ID_LEN];
    char pwd[MAX_PWD_LEN];
};

// 로그인 기능
void signin() {
    system("clear");
    string id;
    string pwd;
    list<Account> lst;
    // 계정들의 정보가 저장된 Accounts.dat 파일을 open 합니다.
    int fd = open("./Accounts.dat", O_RDONLY);
    if (fd == -1) {
        cout << "<No account exist>" << endl;
        return;
    }
    Account acc = Account();
    ssize_t rsize = 0;

    while (1) {
        cout << "****************************" << endl;
        cout << "# Enter ID: ";
        cin >> id;
        cout << "# Enter Password: ";
        cin >> pwd;

        while (1) {
            rsize = read(fd, &acc, sizeof(Account));
            if (rsize == -1) {
                perror("read() error!");
                return;
            }
            // 올바른 ID와 비밀번호를 입력했을 경우
            if (id == acc.getid()) {
                if (pwd == acc.getpwd()) {
                    close(fd);
                    chdir(id.c_str()); // 작업 디렉토리를 ID이름의 디렉토리로
                                       // 변경합니다.
                    return;
                } else // 잘못된 비밀번호를 입력했을 경우
                {
                    system("clear");
                    cout << "<Password error>" << endl;
                    lseek(fd, (off_t)0, SEEK_SET);
                    break;
                }
            }
            // 등록되지 않은 ID를 입력했을 경우
            else if (rsize == 0 && id != acc.getid()) {
                system("clear");
                lseek(fd, (off_t)0, SEEK_SET);
                cout << "<ID does not exist>" << endl;
                break;
            }
        }
    }
    close(fd);
}

// 회원 가입 기능
void signup() {
    system("clear");
    string id;
    string pwd;

    // Accounts.dat 파일에 입력한 사용자의 정보를 저장합니다.
    int fd = open("./Accounts.dat", O_CREAT | O_APPEND | O_RDWR, 0644);
    Account acc = Account();
    ssize_t rsize = 0;
    while (1) {
        cout << "****************************" << endl;
        cout << "# Enter ID: ";
        cin >> id;
        while (1) {
            // Accounts.dat 파일에서 계정정보를 읽어서 입력한 ID가 이미 존재할
            // 경우 다시 입력을 받습니다.
            rsize = read(fd, &acc, sizeof(Account));
            if (rsize == -1) {
                perror("read() error!");
                return;
            }
            if (id == acc.getid()) {
                system("clear");
                lseek(fd, off_t(0), SEEK_SET);
                cout << "< Duplicate ID exists. >" << endl;
                break;
            }
            if (rsize == 0) {
                break;
            }
        }
        if (id != acc.getid())
            break;
    }
    cout << "# Enter Password: ";
    cin >> pwd;
    acc = Account(id, pwd);
    if (write(fd, &acc, sizeof(Account)) == -1) {
        perror("write() error!");
        return;
    }
    close(fd);

    // 입력한 id의 디렉토리를 생성합니다.
    mkdir(id.c_str(), 0755);
}

// 스케줄 추가 기능
void addschedule() {

    system("clear");

    list<Schedule> scheduler; // 입력한 스케줄을 저장할 리스트입니다.
    while (1) {
        cout << "********** Add Schedule **********" << endl;
        int date;
        cout << "# Enter Date(enter 0 to quit): ";
        cin >> date;
        if (date == 0) {
            break;
        }

        int temp = date;

        // 입력한 날짜의 자릿수를 구하여 number에 저장합니다.
        int number = 0;
        while (temp > 0) {
            number++;
            temp /= 10;
        }
        // 날짜의 자릿수가 8이 아닐 경우 경고문을 출력하고 다시 입력을 받습니다.
        if (number != 8) {
            system("clear");
            cout << "< Enter 8 digits(Example: 20200101) >" << endl;
            continue;
        }

        int time;
        cout << "# Time: ";
        cin >> time;

        // 입력한 시간의 자릿수를 구하여 number에 저장합니다.
        temp = time;
        number = 0;
        while (temp > 0) {
            number++;
            temp /= 10;
        }
        // 시간의 자릿수가 3 또는 4가 아닐 경우 경고문을 출력하고 다시 입력을
        // 받습니다.
        if (number < 3 || number > 4) {
            system("clear");
            cout << "< Enter Correct time >" << endl;
            continue;
        }

        cin.ignore();
        string category;
        cout << "# Category: ";
        getline(cin, category);

        string text;
        cout << "# Content: ";
        getline(cin, text);

        int importance;
        cout << "# Importance(0 is important.): ";
        cin >> importance;

        char check;
        while (1) {
            cout << "# Will you Record the schedule ? (Y/N) ";
            cin >> check;
            if (check == 'y' || check == 'Y') {
                Schedule sche(text, date, time, category, importance);
                scheduler.push_back(sche);
                system("clear");
                break;
            } else if (check == 'n' || check == 'N') {
                system("clear");
                break;
            } else {
                cout << "< Enter 'y' or 'n'. >" << endl;
            }
        }
    }

    // Schedule.txt 파일에 입력한 스케줄을 추가합니다.
    string filepath = "./Schedule.txt";
    int fd = open(filepath.c_str(), O_CREAT | O_APPEND | O_RDWR, 0644);
    if (fd == -1) {
        perror("open() error!");
        return;
    }

    list<Schedule>::iterator iter;
    for (iter = scheduler.begin(); iter != scheduler.end(); ++iter) {
        if (write(fd, &(*iter), sizeof(Schedule)) == -1) {
            perror("write() error!");
            return;
        }
    }
    close(fd);
}

// 카테고리별 스케줄 보기 기능
void cviewschedule() {
    system("clear");
    cout << "********** Category View **********" << endl << endl;
    string filepath = "./Schedule.txt";
    int fd = open(filepath.c_str(), O_RDONLY);
    if (fd == -1) {
        cout << "Schedule is not exist." << endl;
        return;
    }

    list<Schedule> scheduler;
    list<string> category; // 저장된 스케줄의 카테고리를 저장할 리스트입니다.

    Schedule sche = Schedule();
    ssize_t rsize = 0;
    while (1) {
        rsize = read(fd, &sche, sizeof(Schedule));
        if (rsize == -1) {
            perror("read() error!");
            return;
        }
        if (rsize == 0)
            break;

        scheduler.push_back(sche);
        category.push_back(sche.getCategory());
    }

    // 카테고리를 정렬하고 중복된 카테고리를 제거합니다.
    category.sort();
    category.unique();

    close(fd);

    list<string>::iterator iter;
    list<Schedule>::iterator siter;

    for (iter = category.begin(); iter != category.end(); ++iter) {
        cout << "<" << *iter << ">" << endl;
        for (siter = scheduler.begin(); siter != scheduler.end(); ++siter) {
            if ((*siter).getCategory() == (*iter)) {
                (*siter).print();
                cout << endl;
            }
        }
        cout << endl;
    }

    while (1) {

        cout << "# Categories: ";
        for (iter = category.begin(); iter != category.end(); ++iter) {
            cout << (*iter) << " ";
        }
        cout << endl;
        cout << "# Enter Category.(Enter 'quit' to finish.): ";
        string input;
        cin >> input;
        if (input == "quit")
            break;
        // find 함수를 사용하여 입력한 카테고리가 category리스트에 있는지
        // 확인합니다.
        iter = find(category.begin(), category.end(), input);
        if (iter == category.end()) {
            system("clear");
            cout << "< Enter correct category >" << endl;
            continue;
        }
        system("clear");
        cout << "********** Category View **********" << endl << endl;
        cout << "<" << input << ">" << endl;
        for (siter = scheduler.begin(); siter != scheduler.end(); ++siter) {
            if ((*siter).getCategory() == input) {
                (*siter).print();
                cout << endl;
            }
        }
        cout << endl;
    }
}

// 날짜별 스케줄 보기 기능
void dviewschedule() {
    string filepath = "./Schedule.txt";
    int fd = open(filepath.c_str(), O_RDONLY);
    if (fd == -1) {
        cout << "Schedule is not exist." << endl;
        return;
    }

    list<Schedule> scheduler;
    list<int> date; // 스케줄의 날짜 정보를 저장할 리스트입니다.

    Schedule sche = Schedule();
    ssize_t rsize = 0;
    while (1) {
        rsize = read(fd, &sche, sizeof(Schedule));
        if (rsize == -1) {
            perror("read() error!");
            return;
        }
        if (rsize == 0)
            break;
        scheduler.push_back(sche);
        date.push_back(sche.getDate());
    }

    close(fd);

    // 날짜를 정렬하고 중복된 날짜를 제거합니다.
    date.sort();
    date.unique();

    int input;
    cout << "************ Date View ************" << endl << endl;
    while (1) {
        cout << "# Enter Date(enter 0 to quit): ";
        cin >> input;

        if (input == 0)
            break;

        system("clear");
        cout << "************ Date View ************" << endl << endl;
        cout << "<" << input << ">" << endl;

        // 입력한 날짜의 자릿수를 구해서 연만 입력했는지 연,월을 입력했는지
        // 연,월,일 모두 입력했는지를 구별한다.
        int temp = input;
        int number = 0;
        while (temp > 0) {
            number++;
            temp /= 10;
        }

        int start;
        int end;

        // 연만 입력했을 경우, start는 입력한 연도이고 end는 다음 연도가 됩니다.
        if (number == 4) {
            start = input * 10000;
            end = (input + 1) * 10000;
        }
        // 연,월을 입력했을 경우, start는 입력한 연/월이고 end는 다음 달이
        // 됩니다.
        else if (number == 6) {
            start = input * 100;
            end = (input + 1) * 100;
        }
        // 연,월,일 모두 입력했을 경우, start는 입력한 연/월/일 이고 end는 다음
        // 날이 됩니다.
        else if (number == 8) {
            start = input;
            end = input + 1;
        }

        list<int>::iterator iter;
        list<Schedule>::iterator siter;

        // 스케줄 리스트에서 start날짜 end날짜 사이에 있는 날짜의 스케줄을
        // 출력합니다.
        for (iter = date.begin(); iter != date.end(); ++iter) {
            if ((*iter) >= start && (*iter) < end) {
                for (siter = scheduler.begin(); siter != scheduler.end();
                     ++siter) {
                    if ((*siter).getDate() == (*iter)) {
                        (*siter).print();
                        cout << endl;
                    }
                }
            }
        }
    }
}

// 스케줄 삭제 기능 (카테고리별 보기에서 삭제)
void delschedule() {

    system("clear");
    cout << "********** Delete Schedule **********" << endl;
    string filepath = "./Schedule.txt";
    int fd = open(filepath.c_str(), O_RDONLY);
    if (fd == -1) {
        cout << "Schedule is not exist." << endl;
        return;
    }

    list<Schedule> scheduler;
    list<string> category;

    Schedule sche = Schedule();
    ssize_t rsize = 0;
    while (1) {
        rsize = read(fd, &sche, sizeof(Schedule));
        if (rsize == -1) {
            perror("read() error!");
            return;
        }
        if (rsize == 0)
            break;
        scheduler.push_back(sche);
        category.push_back(sche.getCategory());
    }

    category.sort();
    category.unique();

    close(fd);

    list<string>::iterator iter;
    list<Schedule>::iterator siter;
    vector<list<Schedule>::iterator>
        vec; // 삭제할 스케줄의 iterator를 저장합니다. (번호로 iterator에
             // 접근하기 위함.)

    int i = 1;

    for (iter = category.begin(); iter != category.end(); ++iter) {
        cout << "<" << *iter << ">" << endl;
        for (siter = scheduler.begin(); siter != scheduler.end(); ++siter) {
            if ((*siter).getCategory() == (*iter)) {
                vec.push_back(siter);
                cout << i << endl;
                (*siter).print();
                cout << endl;
                i++;
            }
        }
        cout << endl;
    }

    int input = 0;

    while (1) {
        cout << "# Enter schedule number to delete(enter 0 to quit): ";
        cin >> input;
        if (input == 0)
            return;
        if (input < 1 || input > i) {
            cout << "< Enter correct number . >" << endl;
        } else {
            break;
        }
    }

    scheduler.erase(
        vec[input - 1]); // (입력한 번호 -1)위치에 저장된 스케줄 iterator 를
                         // scheduler 리스트에서 삭제합니다.

    fd = open(filepath.c_str(), O_TRUNC | O_WRONLY);
    // Schedule.txt 파일을 새로 생성하고 scheduler에 저장된 스케줄을 작성합니다.

    for (siter = scheduler.begin(); siter != scheduler.end(); ++siter) {
        write(fd, &(*siter), sizeof(Schedule));
    }

    close(fd);
}
