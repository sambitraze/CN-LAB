#include <stdio.h>
#include <string.h>
int main()
{
    char str[500];
    printf("Enter String\n");
    fgets(str, 500, stdin);

    float charCount = 0;
    float wordCount = 0;
    float avg = 0.0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == ' ')
        {
            wordCount++;            
        }
        else
        {
            charCount++;
        }        
    }
    charCount--;
    wordCount++;

    avg = (float) charCount / wordCount;
    printf("\nAvg character count: %f",avg);
    printf("\n");
    return 0;
}
