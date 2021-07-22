#include <stdio.h>
#include <string.h>

struct Student
{
    char name[100];
    char id[10];
    int phoneNumber;
};

int main()
{
    struct Student S[10];
    for (int i = 0; i < 10; i++)
    {
        printf("\n****************************************************");
        printf("\nEnter Data for Student %d:", i + 1);
        printf("\n----------------------------------------------------");
        printf("\nEnter Id: \n");
        scanf("%*c");
        fgets(S[i].id, 10, stdin);
        printf("Enter Name: \n");
        scanf("%*c");
        fgets(S[i].name, 100, stdin);
        printf("Enter Phone Number: \n");
        scanf("%d", &S[i].phoneNumber);
        scanf("%*c");
        printf("\n****************************************************");
        printf("\n");
    }
    printf("Do you Want to display the data[Y/N]?\n");
    char ans[1];
    scanf("%*c");
    fgets(ans, 1, stdin);
    if (strcmp(ans, "y") || strcmp(ans, "y"))
    {
        for (int i = 0; i < 10; i++)
        {
            printf("\n****************************************************");
            printf("\nData for Student %d:", i + 1);
            printf("\n----------------------------------------------------");
            printf("\nID: ");
            puts(S[i].id);
            printf("Name: ");
            puts(S[i].name);
            printf("Phone Number: %d", S[i].phoneNumber);
            printf("\n****************************************************");
            printf("\n");
        }
    }
    else
    {
        printf("\nThank you\n");
    }

    return 0;
}
