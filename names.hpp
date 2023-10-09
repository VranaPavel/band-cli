#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <regex>

using namespace std;

void get_data(string file, list<string> &result)
{
    ifstream fp(file);
    if (!fp.is_open())
    {
        cerr << "Error opening file: " << file << endl;
        exit(1);
    }

    string line;
    while (getline(fp, line, '/'))
    {
        result.push_back(line);
        getline(fp, line, ',');
        result.push_back(line);
        getline(fp, line);
        result.push_back(line);
    }
    fp.close();
}

void get_name(string file, int day, int month, list<string> &names)
{
    list<string> data;
    get_data(file, data);
    string sday = to_string(day);
    string smonth = to_string(month + 1);
    for (auto it = data.begin(); it != data.end(); it = next(it, 3))
    {
        if (*it == sday && *next(it) == smonth)
        {
            names.push_back(*next(next(it)));
        }
    }
}

void add_birthday()
{
    string name;
    string day;
    string month;

    cout << "Enter name: ";
    getline(cin, name, '\n');
    cout << "Enter day: ";
    cin >> day;
    cout << "Enter month: ";
    cin >> month;

    regex integer("(\\+|-)?[[:digit:]]+");
    if (name.find(",") != string::npos)
    {
        cout << "This name is invalid. Please try again (don't use ',' symbol)." << endl;
        exit(1);
    }
    else if (!regex_match(day, integer))
    {
        cout << "This day is invalid. Please try again (use numbers only)" << endl;
        exit(1);
    }
    else if (!regex_match(month, integer))
    {
        cout << "This month is invalid. Please try again (use numbers only)" << endl;
        exit(1);
    }
    else if (stoi(day) < 1)
    {
        cout << "This day is invalid. Please try again (use number higher than 0)." << endl;
        exit(1);
    }
    else if (stoi(month) > 12 || stoi(month) < 1)
    {
        cout << "This month is invalid. Please try again (use number from 1 to 12)." << endl;
        exit(1);
    }
    else if (stoi(month) == 2 && stoi(day) > 29)
    {
        cout << "This day is invalid. Please try again (use number from 1 to 29 for this month)." << endl;
        exit(1);
    }
    for (int i = 1; i < 13; i += 2)
    {
        if (stoi(month) == i && stoi(day) > 31)
        {
            cout << "This day is invalid. Please try again (use number from 1 to 31 for this month)." << endl;
            exit(1);
        }
        if (i == 7)
        {
            i = 6;
        }
    }
    for (int i = 4; i < 12; i += 2)
    {
        if (stoi(month) == i && stoi(day) > 30)
        {
            cout << "This day is invalid. Please try again (use number from 1 to 30 for this month)." << endl;
            exit(1);
        }
        if (i == 6)
        {
            i = 7;
        }
    }

    ofstream fp("data/birthdays.csv", ios::app);
    if (!fp.is_open())
    {
        cerr << "Error opening file: data/birthdays.csv" << endl;
        exit(1);
    }

    fp << day << "/" << month << "," << name << endl;
    fp.close();
}

void remove_birthday()
{
    string name;

    cout << "Enter name: ";
    getline(cin, name, '\n');

    list<string> data;
    get_data("data/birthdays.csv", data);

    ofstream fp("data/birthdays.csv");
    if (!fp.is_open())
    {
        cerr << "Error opening file: data/birthdays.csv" << endl;
        exit(1);
    }

    bool found = false;
    for (auto it = data.begin(); it != data.end(); it = next(it, 3))
    {
        if (*next(next(it)) != name)
        {
            fp << *it << "/" << *next(it) << "," << *next(next(it)) << endl;
            found = true;
            cout << "This name has been removed from the database." << endl;
        }
    }
    if (found == false)
    {
        cout << "This name doesn't exist in the database." << endl;
    }
}