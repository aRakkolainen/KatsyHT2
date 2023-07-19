#include <stdio.h>
#include <stdlib.h>



int main(int argc, char * argv[]) {
    FILE *file; 
    int number;
    char character;
    //char character;  
    if (argc == 1) {
        perror("my-unzip: file1 [file2 ...]\n");
        exit(1);
    } else {
        if ((file = fopen(argv[1], "rb")) == NULL) {
                fprintf(stderr, "my-unzip: cannot open file\n");
                exit(1);
        }
        /*fread(&number, sizeof(int), 1, file);
        printf("%d", number);
        fread(&character, sizeof(char), 1, file);
        printf("%c", character);*/
        // Looping fread with while loop is based on this stackOverFlow discussion: https://stackoverflow.com/questions/15697783/how-does-fread-know-when-the-file-is-over-in-c
        while(fread(&number, sizeof(int), 1, file) == 1 && fread(&character, sizeof(char), 1, file) == 1) {
            //printf("%d%c", number, character);
            for (int i=0; i < number; i++) {
                printf("%c", character);
            }
        }
        printf("\n");
        
        //free(line); 
        fclose(file);

    }
    return(0);
}