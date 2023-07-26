#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char *name = NULL;

void replace_char(char *string, char torep, char new)
{
    for (int i = 0; i <= strlen(string); i++)
    {
        if (string[i] == torep)
        {
            string[i] = new;
        }
    }
}

int getBirthday(int day, int month)
{
    FILE *fp;
    fp = fopen("birthdays.csv", "r");

    // Get size of file
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    rewind(fp);

    // Get data
    char *allData = (char *)calloc(sz, sizeof(char));
    char *line = (char *)calloc(sz, sizeof(char));

    while (fgets(line, sz * sizeof(char), fp))
    {
        strcat(allData, line);
    }

    // free(line);       when 10 or more it is ok, when 9 or lower, it call abort()
    fclose(fp);
    replace_char(allData, '\n', ',');

    // Make array of strings from string
    char *part = strtok(allData, ",");
    char **allDataArr = (char **)calloc(sz, sizeof(char *));
    int LenghtOfArr = 0;

    while (part != NULL)
    {
        allDataArr[LenghtOfArr++] = strdup(part);
        part = strtok(NULL, ",");
    }

    free(allData);
    LenghtOfArr = LenghtOfArr - 1;

    // Make three arrays (day, month, name)
    char **dates = (char **)calloc(5, sizeof(char *));
    int k = 0;
    for (int i = 0; i <= LenghtOfArr; i = i + 2)
    {
        dates[k] = allDataArr[i];
        k++;
    }

    int namesSize = sz - (k - 1) * 5 * sizeof(char);
    k = 0;
    char **names = (char **)calloc(1, namesSize);
    for (int i = 1; i <= LenghtOfArr; i = i + 2)
    {
        names[k] = allDataArr[i];
        k++;
    }
    free(allDataArr);

    char *d[k * 2 * sizeof(char)];
    char **m = (char **)calloc(k, 2 * sizeof(char));
    for (int i = 0; i < k; i++)
    {
        d[i] = strtok(dates[i], "/");
        m[i] = strtok(NULL, "/");
    }
    int days[k * 2 * sizeof(int)];
    int months[k * 2 * sizeof(int)];
    int a;

    for (int i = 0; i < k; i++)
    {
        if (m[i][1] == '\0')
        {
            months[i] = (m[i][0] - '0');
        }
        else
        {
            months[i] = (m[i][0] - '0') * 10 + (m[i][1] - '0');
        }
    }
    for (int i = 0; i < k; i++)
    {
        if (d[i][1] == '\0')
        {
            days[i] = (d[i][0] - '0');
        }
        else
        {
            days[i] = (d[i][0] - '0') * 10 + (d[i][1] - '0');
        }
    }

    // Get name by day and month
    for (int i = 0; i < k; i++)
    {
        if (day == days[i] && month + 1 == months[i])
        {
            name = names[i];
        }
    }

    return 0;
}

// TODO: Functions
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
    printf("Today is %d.%d.\n\n", gmt->tm_mday, gmt->tm_mon + 1);

    // Birthday today
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
    /* getNameDay(gmt->tm_mday, gmt->tm_mon);
    printf("Today is %s's name day\n\n", name); */

    // Leap year check
    gmt->tm_year = gmt->tm_year + 1900;
    int leapyear;
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

    // TODO: Print - Birthday tomorrow
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