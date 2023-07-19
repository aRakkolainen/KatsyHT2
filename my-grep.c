#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int checkWord(char *searchWord, char *tempLine) {
    // How to split the line in C with strcmp: https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
    // Searching for substring with strstr: https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/search-within-a-string and linux manual
    // Comparing two strings: https://www.programiz.com/c-programming/library-function/string.h/strcmp 
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
    int r=0; 
    int result;
    char *tempLine; 
    if (argc == 1) {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    } 
    else if (argc == 2) {
        FILE *tempFile; 
        if ((tempFile = fopen("temp.txt", "w")) == NULL) {
                fprintf(stderr, "my-grep: cannot open file\n");
                exit(1);
        }
            //Reading the input stream to temporary file
        do {
                    r = getline(&line, &len, stdin); 
                    if ((r != -1) && (strcmp(line, "\n") != 0)) {
                        fprintf(tempFile, "%s", line); 
                    }

                } while (r > 1);
            fclose(tempFile);
        //Reading the temporary file and searching for the word: 
        if ((tempFile = fopen("temp.txt", "r")) == NULL) {
                fprintf(stderr, "my-grep: cannot open file\n");
                exit(1);
        } else {
            do {
            if ((r = getline(&line, &len, stdin)) != -1) {
                if ((tempLine = (char *)malloc(r*sizeof(char))) == NULL) {
                    fprintf(stderr, "malloc failed");
                    exit(1);
                }
                    strcpy(tempLine, line);
                    printf("%s", line);
                    result = checkWord(argv[1], tempLine);
                    if (result == 1) {
                        printf("%s", line);
                    }
                }

            } while (r > 1);
            fclose(tempFile);
        }

        
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