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

int main(int argc, char * argv[]) { 
    FILE * file; 
    char *line;
    char *str; 
    size_t len;
    char inputFileName[30];
    int r; 
    if (argc == 1) {
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        exit(1);
    } else {
        strcpy(inputFileName, argv[1]);
        if ((file = fopen(inputFileName, "r")) == NULL) {
            fprintf(stderr, "my-zip: cannot open file\n");
            exit(1);
        }
        int counter=0; 
        //int *finalCounter;
        do {
            if ((r = getline(&line, &len, file)) != -1) {
                if ((str = (char*)malloc(r*sizeof(char))) == NULL) {
                    fprintf(stderr, "malloc failed");
                }
                strcpy(str, line);
                // How to get first character of string pointer: https://www.tek-tips.com/viewthread.cfm?qid=1435212
                //char character = *str; 
                int total=0;
                char character = str[total];

                /*counter = countChar(character, str); 
                printf("%d%c\n", counter, character);
                total += counter;  
                character = str[total]; 
                counter = countChar(character, str); 
                printf("%d%c\n", counter, character); 
                total += counter;
                character = str[total]; 
                counter = countChar(character, str); 
                printf("%d%c\n", counter, character);*/ 
                while (total < r) {
                    total += counter; 
                    character = str[total];
                    if (character == '\0') {
                        break; 
                    }
                    counter = countChar(character, str);
                    //printf("%d%c", counter, character);
                    //Writing the integer in binary form and writing char simultaneously: https://stackoverflow.com/questions/10810593/two-consecutive-fwrites-operation  
                    //Info about using fwrite(): https://lutpub.lut.fi/bitstream/handle/10024/162908/Nikula2021-COhjelmointiopasV21.pdf?sequence=1&isAllowed=y
                    fwrite(&counter, sizeof(int), 1, stdout); 
                    fwrite(&character, sizeof(char), 1, stdout);
                    //fprintf(stdout, "%c", character);
                    //printf("%d%c", counter, character); 
                    //fwrite(&counter, sizeof(counter), 1, file);
                }
            }
        } while(r > 1);
        // The exact format of the compressed file must be 4-byte integer in binary
        // Example: aaaaaaaaaabbbb would be 10a4b
        
    }
}
