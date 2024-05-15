#include<bits/stdc++.h>

using namespace std;

class Date{
public:
    enum Month{jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};
    class Bad_date {  };
    //constructor, 0 means “pick a default”
    Date(int y = 0, Month m = Month(0), int d = 0);
    //获取日期的年月日数据
    int day() const;
    Month month() const;
    int year() const;
    //获取日期数据的字符串表示
    string string_rep() const;
    void char_rep(char s[]) const;
    //默认日期
    static void set_default(int, Month, int); 
    //日期操作
    void set_date(int y, Month m, int d);
    Date& add_year(int n);
    Date& add_month(int n);
    Date& add_day(int n);
    //获取星期
    int getWeek() const; 
    void printWeek() const;
    //获取别的日期
    Date getNextMonday();
    int getNext_m1_d1_w1_year(); //获取下一个一月一日是星期一的年份
    int getLast_m1_d1_w1_year(); //获取上一个一月一日是星期一的年份
    //打印日历
    void printCalendar();
    //获取日期间隔
    int getInterval(const Date &date) const;
    bool isLeapYear(int year) const;
    bool isEarlier(const Date &date) const;
private:
    //日期数据
    int y, m, d; //year,month,day
    static Date default_date;
};

//constructor
Date::Date(int y, Month m, int d){
    if(d == 0){
        d = default_date.day();
    }
    if(m == 0){
        m = default_date.month();
    }
    if(y == 0){
        y = default_date.year();
    }
    if(m < 1 || m > 12){
        throw Bad_date();
    }
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(isLeapYear(y)){
        daysInMonth[1] = 29;
    }
    int max = daysInMonth[m - 1];
    if(d < 1 || d > max){
        throw Bad_date();
    }
    this->y = y; this->m = m; this->d = d;
}

//获取日期间距
bool Date::isEarlier(const Date &date) const{
    if (this->year() < date.year()) {
        return true;
    } else if (this->year() == date.year()) {
        if (this->month() < date.month()) {
            return true;
        } else if (this->month() == date.month()) {
            if (this->day() < date.day()) {
                return true;
            }
        }
    }
    return false;
}

bool Date::isLeapYear(int year) const{
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}

int Date::getInterval(const Date &earlierDate) const{
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = 0;
    for (int year = earlierDate.year() + 1; year < this->year(); year++) { //计算年份间隔: 将两个日期的年份间隔的天数加到days中
        if (isLeapYear(year)) {
            days += 366;
        } else {
            days += 365;
        }
    }
    if(earlierDate.year() != this->year()){ //如果年份不同
        if(isLeapYear(earlierDate.year())){
            daysInMonth[1] = 29;
        }
        for (int month = earlierDate.month(); month <= 12; month++) { //计算前一个日期的年份的剩余天数
            if (month == earlierDate.month()) { //如果是前一个日期的月份
                days += daysInMonth[month - 1] - earlierDate.day(); //计算前一个日期的月份的剩余天数
            } else {
                days += daysInMonth[month - 1];
            }
        }
        daysInMonth[1] = 28;
        if(isLeapYear(this->year())){
            daysInMonth[1] = 29;
        }
        for (int month = 1; month < this->month(); month++) { //计算后一个日期的年份的天数
            days += daysInMonth[month - 1];
        }
        days += this->day();
    } else{ //如果年份相同
        if(earlierDate.month() != this->month()){ //如果月份不同
            if(isLeapYear(this->year())){
                daysInMonth[1] = 29;
            }
            for (int month = earlierDate.month(); month < this->month(); month++) { //计算月份间隔的天数
                if (month == earlierDate.month()) { //如果是前一个日期的月份
                    days += daysInMonth[month - 1] - earlierDate.day(); //计算前一个日期的月份的剩余天数
                } else {
                    days += daysInMonth[month - 1];
                }
            }
            days += this->day();
        }
        else{ //如果月份相同
            days += this->day() - earlierDate.day(); //计算天数间隔
        }
    }
    return days;
}

//获取星期
int Date::getWeek() const{
    if(isEarlier(default_date)){
        int days = default_date.getInterval(*this);
        return (7 - days % 7 + 1) > 7 ? 1 : (7 - days % 7 + 1);
    } else{
        int days = getInterval(default_date);
        return (days % 7 + 1);
    }
}

void Date::printWeek() const{
    switch(getWeek()){
        case 1: cout << "Monday" << endl; break;
        case 2: cout << "Tuesday" << endl; break;
        case 3: cout << "Wednesday" << endl; break;
        case 4: cout << "Thursday" << endl; break;
        case 5: cout << "Friday" << endl; break;
        case 6: cout << "Saturday" << endl; break;
        case 7: cout << "Sunday" << endl; break;
    }
}

//获取别的日期
Date Date::getNextMonday(){
    int week = this->getWeek();
    int gap = 8 - week;
    Date nextMonday(this->year(), this->month(), this->day());
    switch(nextMonday.m){
        case 2: {
            if(isLeapYear(nextMonday.y)){
                if(nextMonday.d + gap > 29){
                    nextMonday.d += gap - 29;
                    nextMonday.m ++;
                } else{
                    nextMonday.d += gap;
                }
            } else{
                if(nextMonday.d + gap > 28){
                    nextMonday.d += gap - 28;
                    nextMonday.m ++;
                } else{
                    nextMonday.d += gap;
                }
            }
            break;
        }
        case 4: case 6: case 9: case 11: {
            if(nextMonday.d + gap > 30){
                nextMonday.d += gap - 30;
                nextMonday.m ++;
            } else{
                nextMonday.d += gap;
            }
            break;
        }
        default: {
            if(nextMonday.d + gap > 31){
                nextMonday.d += gap - 31;
                nextMonday.m ++;
            } else{
                nextMonday.d += gap;
            }
            break;
        }
    }
    if(nextMonday.m > 12){
        nextMonday.m = 1;
        nextMonday.y ++;
    }
    return nextMonday;
}

int Date::getNext_m1_d1_w1_year(){
    Date date(this->year() + 1, Date::jan, 1);
    while(date.getWeek() != 1){
        date.add_year(1);
    }
    return date.year();
}

int Date::getLast_m1_d1_w1_year(){
    Date date(this->year() - 1, Date::jan, 1);
    while(date.getWeek() != 1){
        date.add_year(-1);
    }
    return date.year();
}

//打印日历
void Date::printCalendar(){
    cout << "Year " << y << endl << endl;
    Date date(y, Date::jan, 1);
    int week = date.getWeek();
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(isLeapYear(y)){
        daysInMonth[1] = 29;
    }
    for(int i = 1; i <= 12; i ++){
        cout << "Month " << i << endl;
        cout << "w1\tw2\tw3\tw4\tw5\tw6\tw7" << endl;
        for(int j = 1; j < week; j ++){
            cout << "  \t";
        }
        int max = daysInMonth[i - 1];
        for(int j = 1; j <= max; j ++, week ++){
            if(week > 7){
                week = 1;
                cout << endl;
            }
            cout << (j < 10 ? "0" : "") << j << "\t";
        }
        if(week == 8){
            week = 1;
        }
        cout << endl << endl;
    }
}

//获取日期的年月日数据
int Date::day() const{
    return d;
}

Date::Month Date::month() const{
    return Month(m);
}

int Date::year() const{
    return y;
}

//获取日期数据的字符串表示
void Date::char_rep(char s[]) const{
    if(m < 10 && d < 10){
        sprintf(s, "%d-0%d-0%d", y, m, d);
    } else if(m < 10){
        sprintf(s, "%d-0%d-%d", y, m, d);
    } else if(d < 10){
        sprintf(s, "%d-%d-0%d", y, m, d);
    } else{
        sprintf(s, "%d-%d-%d", y, m, d);
    }
}

string Date::string_rep() const{
    char s[11];
    char_rep(s);
    return s;
}

//日期操作
void Date::set_date(int y, Month m, int d){
    if(d == 0){
        d = default_date.day();
    }
    if(m == 0){
        m = default_date.month();
    }
    if(y == 0){
        y = default_date.year();
    }
    if(m < 1 || m > 12){
        throw Bad_date();
    }
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(isLeapYear(y)){
        daysInMonth[1] = 29;
    }
    int max = daysInMonth[m - 1];
    if(d < 1 || d > max){
        throw Bad_date();
    }
    this->y = y; this->m = m; this->d = d;
}

Date& Date::add_year(int n){
    y += n;
    return *this;
}

Date& Date::add_month(int n){
    int new_month = m + n;
    int old_month = m;
    if(new_month > 12){ //如果月份大于12
        y += new_month / 12; //年份增加
        m = new_month % 12; //月份变为余数
    }else if(new_month < 1){ //如果月份小于1
        y += new_month / 12 - 1; //年份减少
        m = new_month % 12 + 12; //月份变为余数加12
    }else{ //如果月份在1到12之间
        m = new_month; //月份直接改变
    }
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(isLeapYear(y)){
        daysInMonth[1] = 29;
    }
    if(d < daysInMonth[m - 1] && d == daysInMonth[old_month - 1]){ //如果日期为该月的最后一天且下个月小于其最大日期 (比如4月30日加1个月变为5月30日)
        cout << endl << "The date should be the last day of the month." << endl;
        d = daysInMonth[m - 1]; //日期变为下个月的最后一天 (即5月31日)
        cout << "The date has been automatically corrected." << endl;
    } else if(d > daysInMonth[m - 1]){ //如果日期大于该月的最大日期 (比如5月31日加1个月变为6月31日)
        cout << endl << "The date exceeds the last day of the next month." << endl;
        d = daysInMonth[m - 1]; //日期变为该月的最大日期 (即6月30日)
        cout << "The date has been automatically corrected." << endl;
    }
    return *this;
}

Date& Date::add_day(int n){
    int new_day = d + n; //新日期
    int max; //最大日期
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(isLeapYear(y)){
        daysInMonth[1] = 29;
    }
    max = daysInMonth[m - 1];
    if(new_day > max){ //如果新日期大于该月的最大日期
        m ++; //月份加1
        if(m > 12){ //如果月份大于12, 年份加1, 月份变为1
            y ++;
            m = 1;
        }
        d = new_day - max; //日期变为新日期减去该月的最大日期
        return add_day(0); //递归
    } else if(new_day < 1){ //如果新日期小于1
        m --; //月份减1
        if(m < 1){ //如果月份小于1, 年份减1, 月份变为12
            y --;
            m = 12;
        }
        daysInMonth[1] = 28;
        if(isLeapYear(y)){
            daysInMonth[1] = 29;
        }
        max = daysInMonth[m - 1];
        d = new_day + max; //日期变为新日期加上该月的最大日期
        return add_day(0); //递归
    } else{ //如果新日期在1到该月的最大日期之间
        d = new_day; //日期不变
        return *this; //返回
    }
}

//默认日期
Date Date::default_date(2001, Date::jan, 1);

void Date::set_default(int y, Month m, int d){
    default_date = Date(y, m, d); //设置默认日期
}