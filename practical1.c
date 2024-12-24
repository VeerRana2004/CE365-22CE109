#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_valid_string(const char *str) {
    int len = strlen(str);
    int i = 0;

    while (i < len && str[i] == 'a') {
        i++;
    }

    if (i < len - 1 && str[i] == 'b' && str[i + 1] == 'b' && i + 2 == len) {
        return 1;
    }

    return 0;
}

int main() {
    char input[100];

    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    if (is_valid_string(input)) {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }

    return 0;
}
