#include <stdio.h>
#include <stdlib.h>
#include "file_extension.h"
#include "decoder.h"
#include "encoder.h"


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


    printf("Enter name of the file(max 20 characters):");
    scanf("%40s", filename1);

    while (getchar() != '\n');

    if(choice == 'd' || choice == 'D') {
        if(valid_type(filename1)!=1) {
            printf("Incorrect file format");
            return 3;
        }

        char *filename2;

        int err1 = decode(filename1,filename2);

    }






    // ADD SUFFIX AT THE END OF OUTPUT FILENAME
    // ADD ERROR HANDLING
    // ADD SIZES OF FILES AND HOW MUCH % IT REDUCED
    // ADD PATH OF THE NEW FILE



    return 0;
}
