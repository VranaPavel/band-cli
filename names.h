#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

char *get_name(char *file, int day, int month)
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
            name = strdup(names[i]);
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

void add_birthday()
{
    FILE *fp;
    fp = fopen("data/birthdays.csv", "a");

    char name[50];
    printf("Enter name: ");
    scanf("%49s", &name);

    char date[6];
    printf("Enter date (in format day/month): ");
    scanf("%5s", &date);

    // Check date
    int i = (date[3] - '0') * 10 + date[4] - '0';
    int k = (date[0] - '0') * 10 + date[1] - '0';
    
    // TODO: check if date is correct
    /* while (i > 12 || k > )
    {
        printf("Wrong date. Enter date (in format day/month): ");
        scanf("%5s", &date);
    } */
    
    fprintf(fp, "\n%s,%s", date, name);
    fclose(fp);
}