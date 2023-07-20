#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct item {
    int number;
    char character;
}; 
// countChar function is based on this website: https://javatutoring.com/c-program-to-count-occurrences-of-character-in-string/
int countChar(char, char *);

int countChar(char character, char *str) {
    int count = 0; 
    for (int i=0; str[i]; i++ ) {
        if (str[i] == character) {
            count++; 
        } 
    }
    return count; 

}


void writeToStdout(char character, int number) {
    //Writing the integer in binary form and writing char simultaneously: https://stackoverflow.com/questions/10810593/two-consecutive-fwrites-operation  
    //Info about using fwrite(): https://lutpub.lut.fi/bitstream/handle/10024/162908/Nikula2021-COhjelmointiopasV21.pdf?sequence=1&isAllowed=y
    fwrite(&number, sizeof(int), 1, stdout); 
    fwrite(&character, sizeof(char), 1, stdout);

}

int main(int argc, char * argv[]) { 
    FILE * file; 
    char *line;
    char *str; 
    size_t len;
    char inputFileName[30];
    int r; 
    int counter=0; 
    int total=0;
    if (argc == 1) {
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        exit(1);
    } else if (argc >= 2) {
        //for (int i=1; i < argc; i++) {
            strcpy(inputFileName, argv[1]);
            if ((file = fopen(inputFileName, "r")) == NULL) {
                fprintf(stderr, "my-zip: cannot open file\n");
                exit(1);
            } else {
                do {
                    if ((r = getline(&line, &len, file)) != -1) {
                        if ((str = (char*)malloc(r*sizeof(char))) == NULL) {
                            fprintf(stderr, "malloc failed");
                        }
                        strcpy(str, line);
                        char character = str[total];
                        while (total < r) {
                            total += counter; 
                            character = str[total];
                            if (character == '\0') {
                                break; 
                            }
                            counter = countChar(character, str);
                            //Writing the integer in binary form and writing char simultaneously: https://stackoverflow.com/questions/10810593/two-consecutive-fwrites-operation  
                            //Info about using fwrite(): https://lutpub.lut.fi/bitstream/handle/10024/162908/Nikula2021-COhjelmointiopasV21.pdf?sequence=1&isAllowed=y
                            fwrite(&counter, sizeof(int), 1, stdout); 
                            fwrite(&character, sizeof(char), 1, stdout);

                            
                    }
                }
            } while(r > 1);
            fclose(file);
            total=0; 
            counter=0; 
            //}
        
        
    }
}
}