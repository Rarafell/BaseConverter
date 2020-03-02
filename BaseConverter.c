#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define LENGTH 100

void Menu(void);
void Input(int *originalBase, int *targetBase, int *number, int *numberLength, bool *isNegative);
long long ConvertToDecimal(const int originalBase, int *number, const int numberLength);
void ConvertToTargetBase(const long long temporaryDecimalNumber, const int targetBase, int *result, int *resultLength);
void Output(int *result, const int resultLength, const bool isNegative);

int main(void)
{
    int originalBase, targetBase;
    int number[LENGTH + 1];
    int result[LENGTH + 1];
    int numberLength;
    int resultLength;
    bool isNegative;
    long long temporaryDecimalNumber;
    Menu();
    while (true)
    {
        Input(&originalBase, &targetBase, number, &numberLength, &isNegative);
        temporaryDecimalNumber = ConvertToDecimal(originalBase, number, numberLength);
        ConvertToTargetBase(temporaryDecimalNumber, targetBase, result, &resultLength);
        Output(result, resultLength, isNegative);
    }
    return 0;
}

void Menu(void)
{
    printf("Welcome to BaseConverter v1.0!\n");
    printf("-----------------------------\n");
    printf("Usage:\n");
    printf("Input format:number originalBase targetBase\n");
    printf("For example:255 10 2\n");
    printf("Input \"exit\" to exit.\n");
    printf("-----------------------------\n");
    return;
}

void Input(int *originalBase, int *targetBase, int *number, int *numberLength, bool *isNegative)
{
    char temp[LENGTH + 1];
    int i = 0;
    int offset = 0;
    *isNegative = false;
    scanf("%s", temp);
    if (strcmp(temp, "exit") == 0)
    {
        exit(0);
    }
    scanf("%d %d", originalBase, targetBase);
    if (*originalBase >= 2 && *originalBase <= 16)
    {
        if (*targetBase >= 2 && *targetBase <= 16)
        {
            if (temp[i] == '-')
            {
                *isNegative = true;
                i++;
                offset++;
            }
            if (temp[i] == '0')
            {
                i++;
                offset++;
                if (temp[i] == 'x' || temp[i] == 'X')
                {
                    i++;
                    offset++;
                }
            }
            for (; temp[i] != '\0'; i++)
            {
                if (temp[i] >= '0' && temp[i] <= '9')
                {
                    number[i - offset] = temp[i] - ('0' - 0);
                }
                else if (temp[i] >= 'A' && temp[i] <= 'F')
                {
                    number[i - offset] = temp[i] - ('A' - 10);
                }
                else if (temp[i] >= 'a' && temp[i] <= 'f')
                {
                    number[i - offset] = temp[i] - ('a' - 10);
                }
                else
                {
                    printf("Error:Invalid value -> number.\n");
                    exit(1);
                }
            }
            *numberLength = i - offset;
        }
        else
        {
            printf("Error:Invalid value -> targetBase.\n");
            exit(1);
        }
    }
    else
    {
        printf("Error:Invalid value -> originalBase.\n");
        exit(1);
    }
    return;
}

long long ConvertToDecimal(const int originalBase, int *number, const int numberLength)
{
    int i;
    long long temporaryDecimalNumber = 0;
    for (i = 0; i < numberLength; i++)
    {
        temporaryDecimalNumber += number[i] * pow(originalBase, numberLength - (i + 1));
    }
    return temporaryDecimalNumber;
}

void ConvertToTargetBase(const long long temporaryDecimalNumber, const int targetBase, int *result, int *resultLength)
{
    long long copy = temporaryDecimalNumber;
    int i;
    memset(result, 0, sizeof(result));
    for (i = 0; copy >= targetBase; i++)
    {
        result[i] = copy % targetBase;
        copy /= targetBase;
    }
    if (copy != 0)
    {
        result[i++] = copy;
    }
    *resultLength = i;
    return;
}

void Output(int *result, const int resultLength, const bool isNegative)
{
    int i;
    if (isNegative)
    {
        printf("-");
    }
    for (i = resultLength - 1; i >= 0; i--)
    {
        if (result[i] >= 10 && result[i] <= 15)
        {
            printf("%c", result[i] + ('A' - 10));
        }
        else
        {
            printf("%d", result[i]);
        }
    }
    printf("\n");
    return;
}