#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct three
{
    char data[10], temp[7];
} s[30];
int main()
{
    char d1[7], d2[7] = "t"; // two arrays one initialized to t for temporary variable
    int i = 0, j = 1, len = 0;
    FILE *f1, *f2;

    //clrscr();
    f1 = fopen("inputTAC.txt", "r");
    f2 = fopen("out.txt", "w");
    while (fscanf(f1, "%s", s[len].data) != EOF) //%s reads up to white space and stores the string read in s struct data
    {

      //  fprintf(f2, "%s \n", s[len].data);

        ++len;

        //printf("%d ", len);
    }

    itoa(j, d1, 7);        //converts int j to a string and stores it in the buffer d1
    strcat(d2, d1);        //concatinates the string to buffer d2
    strcpy(s[j].temp, d2); //store the string in temp 1 variable at structure position j
    strcpy(d1, "");
    strcpy(d2, "t");

    if (strcmp(s[3].data, "+") == 0)
    {
        fprintf(f2, "%s=%s+%s", s[j].temp, s[i + 2].data, s[i + 4].data);
        j++;
    }
    else if (strcmp(s[3].data, "-") == 0)
    {
        fprintf(f2, "%s=%s-%s", s[j].temp, s[i + 2].data, s[i + 4].data);
        j++;
    }
    else if (strcmp(s[0].data, "int") == 0)
    {
        fprintf(f2, "%s=%s \n ", s[j].temp, s[i + 1].data);
        j++;
    }
     if (strcmp(s[0].data, "float") == 0)
        {
            fprintf(f2, "%s=%s \n ", s[j].temp, s[i + 1].data);
            j++;
        }

    for (i = 2; i < len; ++i)
    {
        itoa(j, d1, 7);
        strcat(d2, d1);
        strcpy(s[j].temp, d2);

        if (strcmp(s[i].data, "float") == 0)
        {
            fprintf(f2, "%s=%s \n ", s[j].temp, s[i + 1].data);
            j++;
        }
        else if (strcmp(s[i].data, "int") == 0)
        {
            fprintf(f2, "%s=%s \n ", s[j].temp, s[i + 1].data);
            j++;
        }
        else if (strcmp(s[i].data, "<") == 0)
        {
            fprintf(f2, "%s=%s<%s \n ", s[j].temp, s[i - 1].data, s[i + 1].data);
            j++;
            


        }
        else if (strcmp(s[i].data, ")") == 0)
        {
            fprintf(f2, "  %s = NOT %s \n", s[j].temp, s[j - 1].temp);
            j++;
        }
        else if (strcmp(s[i].data, "1") == 0)
        {
            fprintf(f2, "if( %s ) GOTO L1  \n", s[j - 1].temp);
            //j++;
        }
        else if (strcmp(s[i].data, "+") == 0)
        {
            fprintf(f2, "%s=%s+%s \n", s[j].temp, s[i - 1].data, s[i + 1].data);
            j++;
        }
        else if (strcmp(s[i].data, "else") == 0)
        {
            fprintf(f2, " L1:  \n", s[j - 1].temp);

            //j++;
        }

        else if (strcmp(s[i].data, "-") == 0)
        {

            fprintf(f2, " %s=%s-%s \n", s[j].temp, s[i - 1].data, s[i + 1].data);

            j++;
        }

        strcpy(d1, "");
        strcpy(d2, "t");
        // j++;
    }
    printf("THREE ADREESS OUTPUT GENERATED IN FILE: OUT.TXT");
       
    // fprintf(f2, "\n%s=%s", s[0].data, s[j - 1].temp);
    fclose(f1);
    fclose(f2);
    getch();

}
