#include<bits/stdc++.h>
#include "date_calculator.cpp"

int functions(Date &today);

int main(){
    try{
        cout << "Date Calculator" << endl;
        cout << endl;
        int year, month, day;
        cout << "Enter the current date (yyyy mm dd): ";
        cin >> year >> month >> day;
        Date today(year, Date::Month(month), day);
        today.set_default(2001, Date::Month(1), 1);
        while(true){
            if(functions(today) == 0){
                break;
            }
        }
    } catch (Date::Bad_date) {
        cout << endl << "A bad date!\n" << endl;
        system("pause");
    }
    return 0;
}

int functions(Date &today){
    system("cls");
    cout << "Date Calculator" << endl;
    cout << endl;
    cout << "Current date: ";
    cout << today.string_rep() << endl;
    cout << endl;
    cout << "Please select a function: " << endl;
    cout << "1. Add days to the date (Can be negative)" << endl;
    cout << "2. Add months to the date (Can be negative)" << endl;
    cout << "3. Add years to the date (Can be negative)" << endl;
    cout << "4. Jump to a date quickly" << endl;
    cout << "5. Get the day of the week" << endl;
    cout << "6. Get the date of the next Monday" << endl;
    cout << "7. Get the year whose January 1 is Monday" << endl;
    cout << "8. Calculate the date interval" << endl;
    cout << "9. Print the calendar of this year" << endl;
    cout << "0. Exit" << endl;
    int choice;
    cin >> choice;
    cout << endl;
    switch(choice){
        case 0: {
            system("cls");
            cout << "Goodbye!" << endl;
            break;
        }
        case 1: {
            cout << "Enter days to add: ";
            int days;
            cin >> days;
            today.add_day(days);
            cout << endl <<"succeed!" << endl;
            break;
        }
        case 2: {
            cout << "Enter months to add: ";
            int months;
            cin >> months;
            today.add_month(months);
            cout << endl <<"succeed!" << endl;
            break;
        }
        case 3: {
            cout << "Enter years to add: ";
            int years;
            cin >> years;
            today.add_year(years);
            cout << endl <<"succeed!" << endl;
            break;
        }
        case 4: {
            cout << "Enter the date to jump to (yyyy mm dd): ";
            int year, month, day;
            cin >> year >> month >> day;
            today.set_date(year, Date::Month(month), day);
            cout << endl <<"succeed!" << endl;
            break;
        }
        case 5:{
            cout << "The day of the week is: ";
            cout << today.getWeek() << " -> ";
            today.printWeek();
            break;
        }
        case 6: {
            Date nextMonday = today.getNextMonday();
            cout << "The date of the next Monday is: ";
            cout << nextMonday.string_rep() << endl;
            break;
        }
        case 7: {
            cout << "Get the last / next this kind of year (L/N): ";
            char jud_year;
            cin >> jud_year;
            cout << endl;
            if(jud_year == 'L' || jud_year == 'l'){
                cout << "The last this kind of year is: ";
                cout << today.getLast_m1_d1_w1_year() << endl;
            } else if(jud_year == 'N' || jud_year == 'n'){
                cout << "The next this kind of year is: ";
                cout << today.getNext_m1_d1_w1_year() << endl;
            } else{
                cout << "Invalid choice" << endl;
            }
            break;
        }
        case 8: {
            cout << "Enter the date to calculate the interval (yyyy mm dd): ";
            int year, month, day;
            cin >> year >> month >> day;
            Date date(year, Date::Month(month), day);
            if(!date.isEarlier(today) && date.string_rep() != today.string_rep()){
                cout << date.getInterval(today) << endl;
            } else{
                cout << "-" << today.getInterval(date) << endl;
            }
            break;
        }
        case 9: {
            system("cls");
            today.printCalendar();
            break;
        }
        default: {
            cout << "Invalid choice" << endl;
            break;
        }
    }
    cout << endl;
    system("pause");
    return choice;
}