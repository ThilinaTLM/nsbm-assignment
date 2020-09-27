#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PERSONS_COUNT 100

struct Person
{
    char name[100];
    char address[100];
    char IDnumber[20];
    int age;
};

void printPerson(struct Person *p)
{
    printf("Person Details:\n");
    printf("\tName: %s\n", p->name);
    printf("\tAddress: %s\n", p->address);
    printf("\tID Number: %s\n", p->IDnumber);
    printf("\tAge: %d\n\n", p->age);
}

void fillPersons(struct Person persons[], FILE *source)
{
    char ch;
    int personInd = 0, propertyInd = 0, bufferInd = 0;

    while (((ch = fgetc(source)) != EOF) && (personInd < MAX_PERSONS_COUNT))
    {
        switch (ch)
        {
        case ',':
            propertyInd++;
            bufferInd = 0;
            break;
        case '\n':
            personInd++;
            propertyInd = 0;
            bufferInd = 0;
            break;
        default:
            switch (propertyInd)
            {
            case 0:
                persons[personInd].name[bufferInd] = ch;
                break;
            case 1:
                persons[personInd].address[bufferInd] = ch;
                break;
            case 2:
                persons[personInd].IDnumber[bufferInd] = ch;
                break;
            case 3:
                persons[personInd].age = (persons[personInd].age * 10) + (ch - 48);
                break;
            default:
                printf("Error!");
                break;
            }
            bufferInd++;
            break;
        }
    }

    // mark end of persons array
    persons[personInd+1].name[0] = 0;
}

void swapPersons(struct Person persons, x, y) {
    struct Person temp;
    temp = persons[x];
    persons[x] = persons[y]
    persons[y] = temp;
}

bool comparePerson(struct Person *p1, struct Person *p2) {
    return strcmp(p1->name, p2->name);
}

int main(int argc, char *argv[])
{
    FILE *source, *output;
    struct Person persons[MAX_PERSONS_COUNT + 1];

    if (argc < 3)
    {
        printf("Please specify both input and output files!\n");
        exit(0);
    }

    source = fopen((char *)argv[1], "r");
    output = fopen((char *)argv[2], "w");

    if (source == NULL || output == NULL)
    {
        printf("Unable to open file.\n");
        exit(EXIT_FAILURE);
    }

    fillPersons(persons, source);

    int personInd = 0;
    while (persons[personInd].name[0] != 0)
    {
        printPerson(&persons[personInd++]);
    }

    printf("Success!\n");

    fclose(source);
    fclose(output);

    return 0;
}