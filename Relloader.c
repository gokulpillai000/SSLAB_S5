#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void convert(char h[12]);

char bitmask[12];
char bit[48] = {0};  // Adjusted to allow sufficient space for binary bitmask

int main() {
    char add[6], length[10], input[10], binary[12], relocbit, ch, pn[5];
    int start, inp, len, i, address, opcode, addr, actualadd, tlen;

    FILE *fp1, *fp2;

    printf("\n\nEnter the actual starting address: ");
    scanf("%x", &start);

    fp1 = fopen("RInput.txt", "r");
    if (fp1 == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    fp2 = fopen("ROutput.txt", "w");
    if (fp2 == NULL) {
        printf("Error opening output file.\n");
        fclose(fp1);
        return 1;
    }

    fscanf(fp1, "%s", input);

    fprintf(fp2, "----------------\n");
    fprintf(fp2, "ADDRESS\t\tCONTENT\n");
    fprintf(fp2, "----------------\n");

    while (strcmp(input, "E") != 0) {
        if (strcmp(input, "H") == 0) {
            fscanf(fp1, "%s", pn);
            fscanf(fp1, "%s", add);
            fscanf(fp1, "%s", length);
            fscanf(fp1, "%s", input);
        }

        if (strcmp(input, "T") == 0) {
            fscanf(fp1, "%x", &address);
            fscanf(fp1, "%x", &tlen);
            fscanf(fp1, "%s", bitmask);

            address += start;
            convert(bitmask);

            len = strlen(bit);
            if (len >= 11) len = 10;  // Adjust length for safety

            for (i = 0; i < len; i++) {
                fscanf(fp1, "%x", &opcode);
                fscanf(fp1, "%x", &addr);

                relocbit = bit[i];

                if (relocbit == '0') {
                    actualadd = addr;
                } else {
                    actualadd = addr + start;
                }

                fprintf(fp2, "%x\t\t%x%x\n", address, opcode, actualadd);
                address += 3;
            }
            fscanf(fp1, "%s", input);
        }
    }

    fprintf(fp2, "----------------\n");

    fclose(fp1);
    fclose(fp2);

    printf("\n\nThe contents of output file (ROutput.txt):\n");

    fp2 = fopen("ROutput.txt", "r");
    if (fp2 == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    ch = fgetc(fp2);
    while (ch != EOF) {
        printf("%c", ch);
        ch = fgetc(fp2);
    }
    fclose(fp2);

    return 0;
}

void convert(char h[12]) {
    int i, len;

    strcpy(bit, "");

    len = strlen(h);

    for (i = 0; i < len; i++) {
        switch (h[i]) {
            case '0': strcat(bit, "0000"); break;
            case '1': strcat(bit, "0001"); break;
            case '2': strcat(bit, "0010"); break;
            case '3': strcat(bit, "0011"); break;
            case '4': strcat(bit, "0100"); break;
            case '5': strcat(bit, "0101"); break;
            case '6': strcat(bit, "0110"); break;
            case '7': strcat(bit, "0111"); break;
            case '8': strcat(bit, "1000"); break;
            case '9': strcat(bit, "1001"); break;
            case 'A': strcat(bit, "1010"); break;
            case 'B': strcat(bit, "1011"); break;
            case 'C': strcat(bit, "1100"); break;
            case 'D': strcat(bit, "1101"); break;
            case 'E': strcat(bit, "1110"); break;
            case 'F': strcat(bit, "1111"); break;
        }
    }
}
