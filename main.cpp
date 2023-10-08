#include <iostream>
#include <string>
#include <time.h>
#include "names.hpp"
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-a") == 0 || argv[1] == "--add")
    {
        add_birthday();
        return 0;
    }
    if (argc == 2 && strcmp(argv[1], "-h") == 0 || argv[1] == "--help")
    {
        cout << "Usage: band [OPTION]\n";
        cout << "Show birthdays and name days.\n\n";
        cout << "  -a, --add\t\tadd a birthday\n";
        cout << "  -h, --help\t\tshow this help message and exit\n";
        return 0;
    }
    else if (argc >= 3)
    {
        cout << "band: invalid option -- '" << argv[1] << "'" << endl;
        cout << "Try 'band --help' for more information." << endl;
        return 1;
    }

    cout << "You have entered " << argc << " arguments:"
    << "\n";
 
    for (int i = 0; i < argc; ++i)
        cout << argv[i] << "\n";

    // Time - today
    time_t now = time(NULL);
    struct tm *gmt = gmtime(&now);

    // Welcome
    cout << "Welcome in the Band (Birthdays and name days) app." << endl;
    cout << "Today is " << gmt->tm_mday << "." << gmt->tm_mon + 1 << "." << endl << endl;
    list<string> names;

    get_name("data/birthdays.csv", gmt->tm_mday, gmt->tm_mon, names);
    if (names.empty())
    {
        cout << "Today isn't anyone you know's birthday." << endl;
    }
    for (const auto &element : names)
    {
        cout << "Today is " << element << "'s birthday." << endl;
    }
    names.clear();
    get_name("data/namedays.csv", gmt->tm_mday, gmt->tm_mon, names);
    if (names.empty())
    {
        cout << "Today isn't anyone you know's nameday." << endl;
    }
    for (const auto &element : names)
    {
        cout << "Today is " << element << "'s nameday." << endl;
    }
    cout << endl;

    // Leap year check
    gmt->tm_year = gmt->tm_year + 1900;
    int leapyear = 0;
    if (gmt->tm_year % 4 == 0)
    {
        leapyear = 1;
    }
    if (gmt->tm_year % 100 == 0)
    {
        leapyear = 0;
    }
    if (gmt->tm_year % 400 == 0)
    {
        leapyear = 1;
    }

    // Time - tomorrow
    gmt->tm_mday = gmt->tm_mday + 1;
    for (int i = 0; i < 10; i = i + 2)
    {
        if (gmt->tm_mday > 31 && gmt->tm_mon == i)
        {
            gmt->tm_mday = gmt->tm_mday - 31;
            gmt->tm_mon = gmt->tm_mon + 1;
        }
        if (i == 6)
        {
            i = i - 1;
        }
    }
    for (int i = 3; i < 11; i = i + 2)
    {
        if (gmt->tm_mday > 30 && gmt->tm_mon == i)
        {
            gmt->tm_mday = gmt->tm_mday - 30;
            gmt->tm_mon = gmt->tm_mon + 1;
        }
        if (i == 5)
        {
            i = i + 1;
        }
    }
    if (leapyear == 0 && gmt->tm_mon == 1 && gmt->tm_mday > 28)
    {
        gmt->tm_mday = gmt->tm_mday - 28;
        gmt->tm_mon = gmt->tm_mon + 1;
    }
    else if (gmt->tm_mon == 1 && gmt->tm_mday > 29)
    {
        gmt->tm_mday = gmt->tm_mday - 29;
        gmt->tm_mon = gmt->tm_mon + 1;
    }

    if (gmt->tm_mon == 11 && gmt->tm_mday > 31)
    {
        gmt->tm_mday = gmt->tm_mday - 31;
        gmt->tm_mon = gmt->tm_mon - 11;
    }

    names.clear();
    get_name("data/birthdays.csv", gmt->tm_mday, gmt->tm_mon, names);
    if (names.empty())
    {
        cout << "Today isn't anyone you know's birthday." << endl;
    }
    for (const auto &element : names)
    {
        cout << "Tomorrow is " << element << "'s birthday." << endl;
    }
    names.clear();
    get_name("data/namedays.csv", gmt->tm_mday, gmt->tm_mon, names);
    if (names.empty())
    {
        cout << "Tomorrow isn't anyone you know's nameday." << endl;
    }
    for (const auto &element : names)
    {
        cout << "Tomorrow is " << element << "'s nameday." << endl;
    }
    return 0;
}