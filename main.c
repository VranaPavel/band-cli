#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int getValueSvatek()
{
}

int getValueNarozeniny()
{
    /* FILE *fp;
    fp = fopen("svatky.csv", "r");

    malloc // malloc size of file

    fopen(); */
}

void addbirthday()
{
    FILE *fp = fopen("", "w");
}

int main()
{
    time_t now = time(NULL);
    struct tm *gmt = gmtime(&now);
    int day = gmt->tm_mday;
    int month = gmt->tm_mon;

    printf("Vítejte v aplikaci Narozeniny a svátky\n\n");
    printf("Today is %d.%d.\n", day, month);

/*     int birthday;
    int nameDay;
    char name[20];

    if (birthday == NULL)
    {
        printf("Today isn't anyone you know's birthday.\n");
    }
    else
    {
        printf("Today is %s's birthday.\n", name);
    }
    printf("Today is %s's name day\n\n", name);

    if (birthday + 1 == NULL)
    {
        printf("Tomorrow isn't anyone you know's birthday.\n");
    }
    else
    {
        printf("Tomorrow is %s's birthday.\n", name);
    }
    printf("Tomorrow is %s's name day\n", name); */

    return 0;
}