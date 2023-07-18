#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkWord(char *, char *);

int checkWord(char *searchWord, char *tempLine) {
    // How to split the line in C with strcmp: https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
    // Searching for substring with strstr: https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/search-within-a-string and linux manual
    char *token = strtok(tempLine, " ");
        while (token != NULL ){
            if ((strcmp(token, searchWord) == 0) || (strstr(token, searchWord) != NULL)) {
                return(1); // 1=true
            }
            token = strtok(NULL, " ");
    }
    return(0); // 0 = false
} 

int main(int argc, char * argv[]) {
    FILE *file; 
    char *line;
    size_t len;
    int r; 
    int result;
    char *tempLine; 
    if (argc == 1) {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    } 
    else if (argc == 2) {
        printf("Searching the word from standard input..\n");
        do {
            r = getline(&line, &len, stdin);
            if ((tempLine = (char *)malloc(r*sizeof(char))) == NULL) {
                fprintf(stderr, "malloc failed");
                exit(1);
            }
            strcpy(tempLine, line);
            result = checkWord(argv[1], tempLine);
            if (result == 1) {
                printf("%s", line);
            }
        } while (r > 1);
    } else if (argc > 2) {
        printf("Searching the word from file..\n");
        for (int i=2; i < argc; i++) {
            if ((file = fopen(argv[i], "r")) == NULL) {
                fprintf(stderr, "my-grep: cannot open file\n");
                exit(1);
            } else {
                do {
                    if ((r = getline(&line, &len, file)) != -1) {
                        if ((tempLine = (char *)malloc(r*sizeof(char))) == NULL) {
                            fprintf(stderr, "malloc failed");
                            exit(1);
                        }
                        strcpy(tempLine, line);
                        result = checkWord(argv[1], tempLine);
                        if (result == 1) {
                            printf("%s", line);
                        }
                    }

                } while (r > 1);                
            }
            //printf("\n");
            free(tempLine); 
            free(line);
            fclose(file);
        }
        }

    return(0);
}