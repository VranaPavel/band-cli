#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *cpy(const char *source)
{
    char *copy = strdup(source);
    if (copy == NULL)
    {
        return NULL;
    }
    return copy;
}

void replace_char(char *string, char torep, char new)
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == torep)
        {
            string[i] = new;
        }
    }
}

char *get_name(char *file, int day, int month)
{
    FILE *fp;
    fp = fopen(file, "r");

    // Get size of file
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    rewind(fp);

    // Get data
    char *allData = (char *)malloc((sz + 1) * sizeof(char));
    allData[0] = '\0';
    char *line = (char *)malloc(sz * sizeof(char));

    while (fgets(line, sz * sizeof(char), fp))
    {
        strcat(allData, line);
    }

    replace_char(allData, '\n', ',');

    // Make array of strings from string
    int lenghtOfArr = 0;
    char **allDataArr = (char **)malloc((sz + 1) * sizeof(char *));
    char *part = strtok(allData, ",");

    while (part != NULL)
    {
        allDataArr[lenghtOfArr] = part;
        lenghtOfArr++;
        part = strtok(NULL, ",");
    }
    lenghtOfArr = lenghtOfArr - 1;

    // Make three arrays (day, month, name)
    char **dates = (char **)malloc(lenghtOfArr * sizeof(char *));
    int k = 0;
    for (int i = 0; i <= lenghtOfArr; i = i + 2)
    {
        dates[k] = allDataArr[i];
        k++;
    }

    char **names = (char **)malloc(sz - (k - 1) * 3 * sizeof(char));
    k = 0;
    for (int i = 1; i <= lenghtOfArr; i = i + 2)
    {
        names[k] = allDataArr[i];
        k++;
    }

    char *d[k * 2 * sizeof(char)];
    char **m = (char **)malloc(k * 2 * sizeof(char) * 4);
    for (int i = 0; i < k; i++)
    {
        d[i] = strtok(dates[i], "/");
        m[i] = strtok(NULL, "/");
    }

    int days[k * 2 * sizeof(int)];
    int months[k * 2 * sizeof(int)];

    for (int i = 0; i < k; i++)
    {
        if (m[i][1] == 0)
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
    char *name = NULL;
    for (int i = 0; i < k; i++)
    {
        if (day == days[i] && month + 1 == months[i])
        {
            name = cpy(names[i]);
            break;    
        }
    }
    
    fclose(fp);
    free(line);
    free(allDataArr);
    free(dates);
    free(m);
    free(names);
    free(allData);

    return name;
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

    // Birthday - today
    char *name = get_name("birthdays.csv", gmt->tm_mday, gmt->tm_mon);
    if (name == NULL)
    {
        printf("Today isn't anyone you know's birthday.\n");
    }
    else
    {
        printf("Today is %s's birthday.\n", name);
    }

    // Name day - today
    name = get_name("namedays.csv", gmt->tm_mday, gmt->tm_mon);
    printf("Today is %s's name day.\n\n", name);
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
    name = get_name("birthdays.csv", gmt->tm_mday + 1, gmt->tm_mon);
    if (name == NULL)
    {
        printf("Tomorrow isn't anyone you know's birthday.\n");
    }
    else
    {
        printf("Tomorrow is %s's birthday.\n", name);
    }
    
    // Name day - tomorrow
    name = get_name("namedays.csv", gmt->tm_mday + 1, gmt->tm_mon);
    printf("Tomorrow is %s's name day\n\n", name);
    free(name);

    return 0;
}