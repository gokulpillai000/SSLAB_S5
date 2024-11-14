#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    int i, j, staddr1, addr1;
    char name[10], line[50], name1[10], addr[10], rec[10], ch, staddr[10];

    printf("Enter the name of the program: ");
    scanf("%s", name);

    fp = fopen("objcode.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(fp, "%s", line);
    for (i = 2, j = 0; i < 8; i++, j++) // extract program name
        name1[j] = line[i];
    name1[j] = '\0';

    printf("Program name from obj file: %s\n", name1);

    if (strcmp(name, name1) == 0) { // verify program name
        do {
            fscanf(fp, "%s", line);

            if (line[0] == 'T') {
                for (i = 2, j = 0; i < 8; i++, j++) // extract starting address
                    staddr[j] = line[i];
                staddr[j] = '\0';
                staddr1 = atoi(staddr);

                i = 12; // start object code from column 12

                while (line[i] != '\0') {
                    if (line[i] != '^') {
                        printf("00%d \t %c%c\n", staddr1, line[i], line[i + 1]);
                        staddr1++; // increment memory address
                        i += 2; // move to next object code pair
                    } else {
                        i++; // skip '^' character
                    }
                }
            } else if (line[0] == 'E') {
                printf("\nExecution address: ");
                for (i = 2; i < 8; i++)
                    printf("%c", line[i]);
                break;
            }
        } while (!feof(fp));
    } else {
        printf("Program name does not match.\n");
    }

    fclose(fp);
    return 0;
}
