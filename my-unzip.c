#include <stdio.h>



int main(int argc, char * argv[]) {
    if (argc == 1) {
        perror("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

    return(0);
}