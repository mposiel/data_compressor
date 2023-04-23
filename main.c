#include <stdio.h>
#include <stdlib.h>
#include "file_extension.h"
#include "decoder.h"
#include "encoder.h"
#include "file_size.h"


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

    if (choice == 'd' || choice == 'D') {
        if (valid_type(filename1) != 1) {
            printf("Incorrect file format");
            return 3;
        }

        char *filename2 = filename_decoded(filename1);
        if (filename2 == NULL) {
            printf("Failed to allocate memory");
            return 8;
        }


        int err1 = decode(filename1, filename2);
        if (err1 == 2) {
            printf("Couldn't open file");
            return 2;
        } else if (err1 == 3) {
            printf("Failed to allocate memory");
            return 8;
        } else if (err1 == 4) {
            printf("File corrupted");
            return 5;
        }


        long size_before = file_size(filename1);
        float size_before_in_kB = (float) size_before / 1000;
        long size_after = file_size(filename2);
        float size_after_in_kB = (float) size_after / 1000;

        printf("File saved!\nSize before: %ld B\nSize after: %ld B", size_before, size_after);

    } else if (choice == 'e' || choice == 'E') {
        if (valid_type(filename1) != 2) {
            printf("Incorrect file format");
            return 3;
        }

        char *filename2 = filename_encoded(filename1);
        if (filename2 == NULL) {
            printf("Failed to allocate memory");
            return 8;
        }


        int err1 = encode(filename1, filename2);
        if (err1 == 2) {
            printf("Couldn't open file");
            return 2;
        } else if (err1 == 3) {
            printf("Failed to allocate memory");
            return 8;
        } else if (err1 == 4) {
            printf("File corrupted");
            return 5;
        }

        long size_before = file_size(filename1);
        float size_before_in_kB = (float) size_before / 1000;
        long size_after = file_size(filename2);
        float size_after_in_kB = (float) size_after / 1000;

        printf("File saved!\nSize before: %ld B\nSize after: %ld B", size_before, size_after);

    }



    // ADD SUFFIX AT THE END OF OUTPUT FILENAME
    // ADD ERROR HANDLING
    // ADD SIZES OF FILES AND HOW MUCH % IT REDUCED
    // ADD PATH OF THE NEW FILE



    return 0;
}
