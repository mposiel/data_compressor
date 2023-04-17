#include <stdio.h>
#include <stdlib.h>


int main() {
    char *filename1 = malloc(41 * sizeof(char));
    if (filename1 == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    char choice;
    printf("Would you like to encode od decode text file?(E/d):");
    scanf("%c", &choice);


    if (choice != 'e' && choice != 'E' && choice != 'd' && choice != 'D') {
        printf("Incorrect input data");
        return 2;
    }


    printf("Enter name of the file(max 40 characters):");
    scanf("%40s", filename1);

    while (getchar() != '\n');

    // ADD SUFFIX AT THE END OF OUTPUT FILENAME
    // ADD ERROR HANDLING
    // ADD SIZES OF FILES AND HOW MUCH % IT REDUCED
    // ADD PATH OF THE NEW FILE



    return 0;
}
