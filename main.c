#include <stdio.h>
#include <string.h>
#include <time.h>

// TODO: Functions
int getBirthday(int day, int month)
{
    return 0;
}

int getNameDay(int day, int month)
{
    return 0;
}

void addBirthday()
{
}

int main()
{
    // Time - today
    time_t now = time(NULL);
    struct tm *gmt = gmtime(&now);

    // Welcome
    printf("Welcome in the Band (Birthdays and name days) app.\n");
    printf("Today is %d.%d.\n\n", gmt->tm_mday, gmt->tm_mon);
    char *name = "Pavel";

    // TODO: Birthday today
    getBirthday(gmt->tm_mday, gmt->tm_mon);
    if (name == NULL)
    {
        printf("Today isn't anyone you know's birthday.\n");
    }
    else
    {
        printf("Today is %s's birthday.\n", name);
    }

    // TODO: Name day today
    getNameDay(gmt->tm_mday, gmt->tm_mon);
    printf("Today is %s's name day\n\n", name);

    // TODO: Leap year check
    int leapyear = 0;

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

    // TODO: Print - tomorrow
    // Birthday tomorrow
    /* getBirthday(day + 1, month);
    if (name == NULL)
    {
        printf("Today isn't anyone you know's birthday.\n");
    }
    else
    {
        printf("Today is %s's birthday.\n", name);
    }
    // Name day today
    getNameDay(day + 1, month);
    printf("Today is %s's name day\n\n", name); */

    return 0;
}