#include <stdio.h>
#include <stdlib.h>


int main() {
    char *filename1 = malloc(41 * sizeof(char));
    if (filename1 == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    char *filename2 = malloc(41 * sizeof(char));
    if (filename2 == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    char choice;
    printf("Would you like to encode od decode text file?(E/d):");
    scanf("%c",&choice);


    if(choice!='e' && choice!='E' && choice!='d' && choice!='D') {
        printf("Incorrect input data");
        return 2;
    }




    printf("Enter name of the first file(max 40 characters):");
    scanf("%40s", filename1);

    while (getchar() != '\n');

    printf("Enter name of the second file(max 40 characters):");
    scanf("%40s", filename2);



    return 0;
}
