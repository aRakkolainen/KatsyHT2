#include <stdio.h>
#include <stdlib.h>
int main(int argc, char * argv[]) { 
    if (argc == 2) {
        printf("Searching the word from standard input..\n");
    } else if (argc > 2) {
        printf("Searching the word from file..\n");
        for (int i=2; i < argc; i++) {
            FILE *file; 
            char *line;
            size_t len;
        if ((file = fopen(argv[i], "r")) == NULL) {
            perror("my-grep: cannot open file");
            printf("\n");
            exit(1);
        } else {
            while ((getline(&line, &len, file)) != -1) {
                if (line == argv[1]) {
                    printf("%s", line);
            }
            printf("\n");
            fclose(file);
        }
        }

    }
    return(0);
}