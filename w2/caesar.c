#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int encode(char, int);

int main(int argc, string argv[]) {
    if (argc > 2 || argc < 2) {
        return 1;
    }
    
    printf("\n");

    int k = atoi(argv[1]);
    string input = get_string();
    
    printf("ciphertext: ");

    for (int i = 0, n = strlen(input); i < n; i++) {
        char c = input[i];
        if (isalpha(c)) {
            printf("%c", encode(c, k));
        } else {
            printf("%c", c);  
        }
    }

    printf("\n");

    return 0;
}

int encode(char c, int k) {
    char cc = tolower(c);
    int new_pos_cc = (cc - 'a' + k) % 26 + 'a';
    if (islower(c)) {
        return new_pos_cc;
    } else {
        return new_pos_cc - ('a' - 'A');
    }
}
