#include <stdio.h>
#include <string.h>
#include <time.h>
#include "names.h"

int main(int argc, char *argv[])
{
    if (argc == 2 && (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--add") == 0))
    {
        add_birthday();
        return 0;
    }
    else if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
    {
        printf("Usage: band [OPTION]\n");
        printf("Show birthdays and name days.\n\n");
        printf("  -a, --add\t\tadd a birthday\n");
        printf("  -h, --help\t\tshow this help message and exit\n");
        return 0;
    }
    else if (argc >= 2)
    {
        printf("band: invalid option -- '%s'\n", argv[1]);
        printf("Try 'band --help' for more information.\n");
        return 1;
    }

    // Time - today
    time_t now = time(NULL);
    struct tm *gmt = gmtime(&now);

    // Welcome
    printf("Welcome in the Band (Birthdays and name days) app.\n");
    printf("Today is %d.%d.\n\n", gmt->tm_mday, gmt->tm_mon + 1);

    // Birthday - today
    char *name = get_name("data/birthdays.csv", gmt->tm_mday, gmt->tm_mon);
    if (name == NULL)
    {
        printf("Today isn't anyone you know's birthday.\n");
    }
    else
    {
        printf("Today is %s's birthday.\n", name);
    }
    free(name);

    // Name day - today
    name = get_name("data/namedays.csv", gmt->tm_mday, gmt->tm_mon);
    if (name == NULL)
    {
        printf("Today isn't anyone you know's name day.\n");
    }
    else
    {
        printf("Today is %s's name day.\n\n", name);
    }
    free(name);

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

    // Birthday - tomorrow
    name = get_name("data/birthdays.csv", gmt->tm_mday + 1, gmt->tm_mon);
    if (name == NULL)
    {
        printf("Tomorrow isn't anyone you know's birthday.\n");
    }
    else
    {
        printf("Tomorrow is %s's birthday.\n", name);
    }
    free(name);

    // Name day - tomorrow
    name = get_name("data/namedays.csv", gmt->tm_mday + 1, gmt->tm_mon);
    if (name == NULL)
    {
        printf("Tomorrow isn't anyone you know's name day\n");
    }
    else
    {
        printf("Tomorrow is %s's name day\n\n", name);
    }
    free(name);

    return 0;
}