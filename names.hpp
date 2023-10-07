#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

void get_name(string file, int day, int month, bool d, bool t)
{
    ifstream fp(file);
    if (!fp.is_open())
    {
        cerr << "Error opening file: " << file << endl;
        return;
    }

    // Get data
    list<string> data;
    list<string> names;

    string line;
    while (getline(fp, line, '/'))
    {
        data.push_back(line);
        getline(fp, line, ',');
        data.push_back(line);
        getline(fp, line);
        data.push_back(line);
    }
    fp.close();

    string sday = to_string(day);
    string smonth = to_string(month + 1);
    for (auto it = data.begin(); it != data.end(); it = next(it, 3))
    {
        if (*it == sday && *next(it) == smonth)
        {
            names.push_back(*next(next(it)));
        }
    }

    if (names.size() == 0 && d == 0 && t == 0)
    {
        cout << "Today isn't anyone you know's birthday." << endl;
    }
    else if (names.size() == 0 && d == 0 && t == 1)
    {
        cout << "Today isn't anyone you know's name day." << endl;
    }
    else if (names.size() == 0 && d == 1 && t == 0)
    {
        cout << "Tomorrow isn't anyone you know's birthday." << endl;
    }
    else if (names.size() == 0 && d == 1 && t == 1)
    {
        cout << "Tomorrow isn't anyone you know's name day." << endl;
    }
    else
    {
        for (const auto &element : names)
        {
            if (d == 0 && t == 0)
            {
                cout << "Today is " << element << "'s birthday." << endl;
            }
            else if (d == 0 && t == 1)
            {
                cout << "Today is " << element << "'s name day." << endl;
            }
            else if (d == 1 && t == 0)
            {
                cout << "Tomorrow is " << element << "'s birthday." << endl;
            }
            else
            {
                cout << "Tomorrow is " << element << "'s name day." << endl;
            }
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

    ofstream fp("data/birthdays.csv", ios::app);
    if (!fp.is_open())
    {
        cerr << "Error opening file: data/birthdays.csv" << endl;
        return;
    }

    fp << day << "/" << month << "," << name << endl;
    fp.close();
}