#include <stdio.h>
#include <string.h>

// you may ignore the following two lines
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

int main(int argc, char** argv) {
    int i;
    char *str = "hello, world!", ch;
    for (i = 0; i < strlen(str); i++)
        ch = str[i];

    printf("%s\n",str);

    if (argc > 1)
        printf("%s\n", argv[1]);
    return 0;
}
