#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

// TODO: Fix memory errors
// TODO: Add some comments
char **get_name(char *file, int day, int month)
{
    FILE *fp;
    fp = fopen(file, "r");

    // Get size of file
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    rewind(fp);

    if (sz == 0)
    {
        fclose(fp);
        return NULL;
    }

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

    char **names = (char **)malloc((sz - (k - 1) * 3) * sizeof(char *));
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
    char **name = (char **)malloc(sizeof(char *));

    char b = '0';
    name[0] = &b;

    int a = 1;
    for (int i = 0; i < k; i++)
    {
        if (day == days[i] && month + 1 == months[i])
        {
            name = (char **)realloc(name, sizeof(char *) * (a + 1));
            name[a] = names[i];
            a++;
        }
    }
    a--;
    *name[0] = a + '0';

    if (a == 0)
    {
        free(name);
        name = NULL;
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

void add_birthday()
{
    FILE *fp;
    fp = fopen("data/birthdays.csv", "a");

    char name[50];
    printf("Enter name: ");
    fgets(name, sizeof name, stdin);
    replace_char(name, '\n', '\0');

    char date[6];
    printf("Enter date (in format day/month): ");
    fgets(date, sizeof date, stdin);
    for (int i = 0; i < strlen(date); i++)
    {
        if (date[i] == '\n')
        {
            date[i] = '\0';
        }
    }
    printf("\n");

    // Check date
    int slash;
    int d;
    int m;
    for (int i = 0; i < strlen(date); i++)
    {
        if (date[i] == '/')
        {
            slash = i;
        }
    }
    if (slash == 1)
    {
        int d = date[0] - '0';
        if (date[3] != '\0')
        {
            m = (date[2] - '0') * 10 + date[3] - '0';
        }
        else if (date[3] == '\0')
        {
            m = date[2] - '0';
        }
        else
        {
            printf("Error: bad input. You entered a date that doesn't exist.\n");
            exit(1);
        }
    }
    else if (slash == 2)
    {
        int d = (date[0] - '0') * 10 + date[1] - '0';
        if (date[4] != '\0')
        {
            m = (date[3] - '0') * 10 + date[4] - '0';
        }
        else if (date[4] == '\0')
        {
            m = date[3] - '0';
        }
        else
        {
            printf("Error: bad input. You entered a date that doesn't exist.\n");
            exit(1);
        }
    }

    // Date checking and input sanitization while adding birthday
    for (int i = 0; i < strlen(name); i++)
    {
        if (name[i] == ',' || name[i] == '/')
        {
            printf("Error: bad input. You entered a forbidden symbol.\n");
            fclose(fp);
            exit(1);
        }
    }
    for (int i = 0; i < strlen(date); i++)
    {
        if (date[i] == ',')
        {
            printf("Error: bad input. You entered a forbidden symbol.\n");
            fclose(fp);
            exit(1);
        }
    }

    for (int i = 1; i < 13; i = i + 2)
    {
        if (d > 31 && m == i)
        {
            printf("Error: bad input (wrong date). You entered a date that doesn't exist.\n");
            fclose(fp);
            exit(1);
        }
        if (i == 7)
        {
            i = i - 1;
        }
    }
    for (int i = 4; i < 12; i = i + 2)
    {
        if (d > 30 && m == i)
        {
            printf("Error: bad input (wrong date). You entered a date that doesn't exist.\n");
            fclose(fp);
            exit(1);
        }
        if (i == 6)
        {
            i = i + 1;
        }
    }
    if (d > 29 && m == 2)
    {
        printf("Error: bad input (wrong date). You entered a date that doesn't exist.\n");
        fclose(fp);
        exit(1);
    }
    if (m > 12)
    {
        printf("Error: bad input (wrong date). You entered a date that doesn't exist.\n");
        fclose(fp);
        exit(1);
    }

    fprintf(fp, "%s,%s", date, name);
    fprintf(fp, "\n");
    fclose(fp);
    printf("New birthday added succesfully.\n");
}

// WARNING: This function is not working properly
// TODO: Finish this function
void remove_name(char *string)
{
    FILE *fpr;
    FILE *fpw;
    fpr = fopen("data/birthdays.csv", "r");

    fseek(fpr, 0L, SEEK_END);
    int sz = ftell(fpr);
    rewind(fpr);

    if (sz == 0)
    {
        fclose(fpr);
        exit(1);
    }

    // Get data
    char *allData = (char *)malloc((sz + 1) * sizeof(char));
    allData[0] = '\0';
    char *line = (char *)malloc(sz * sizeof(char));

    while (fgets(line, sz * sizeof(char), fpr))
    {
        strcat(allData, line);
    }
    fclose(fpr);
    fpw = fopen("data/birthdays.csv", "W");

    int k = 0;
    int n = 1;
    for (int i = 0; i < strlen(allData); i++)
    {
        if (allData[i] == ',' || allData[i] == '\n')
        {
            if (n == 0)
            {
                // Delete name from allData and write allData into file
                k = i;
                i--;
                while (allData[i] != '\n')
                {
                    i--;
                }

                while (allData[i] != '\0')
                {
                    allData[i] = allData[k];
                    i++;
                    k++;
                }
                /* while (allData[i] == '')
                {
                } */

                fprintf(fpw, "%s", allData);
                break;
            }
            n = 0;
            k = i + 1;
            continue;
        }

        if (n == 1)
        {
            continue;
        }

        if (allData[i] != string[i - k])
        {
            n = 1;
        }
    }
    // free(allData);
    free(line);
    fclose(fpw);
}