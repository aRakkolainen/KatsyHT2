#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        printf("%s\n", inputFileName);
        if ((file = fopen(inputFileName, "r")) == NULL) {
            fprintf(stderr, "my-zip: cannot open file\n");
            exit(1);
        }
        int counter=0; 
        do {
            if ((r = getline(&line, &len, file)) != -1) {
                if ((str = (char*)malloc(r*sizeof(char))) == NULL) {
                    fprintf(stderr, "malloc failed");
                }
                strcpy(str, line);
                // How to get first character of string pointer: https://www.tek-tips.com/viewthread.cfm?qid=1435212
                char firstChar = *str; 
                //strcpy(firstChar, &str[0]);
                for (int i=0; i < strlen(str); i++) {
                    while ((scanf("%c", &str[i]))!= firstChar) {
                        counter++; 
                        //scanf("%c", &str[i]);
                        //if (str[i] == firstChar) {
                          //  break; 
                        //}
                    
                    }
                    printf("%d\n", counter);
                    //scanf("%c", &str[i]);
                    
                }
            }
        } while(1);
        // The exact format of the compressed file must be 4-byte integer in binary
        // Example: aaaaaaaaaabbbb would be 10a4b
        
    }
}
