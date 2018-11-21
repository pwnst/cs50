#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int encode(char, int);

int main(int argc, string argv[]) {
    if (argc > 2 || argc < 2) {
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++) {
        if (!isalpha(argv[1][i])) {
            return 1;
        }
    }
    
    printf("\n");

    string k = argv[1];
    string input = get_string();
    
    printf("ciphertext: ");
    int pos = 0;
        
    for (int i = 0, n = strlen(input); i < n; i++) {
        char c = input[i];
        if (isalpha(c)) {
            char en_c = k[pos % strlen(k)];
            int x = encode(c, 'a' - tolower(en_c));
            printf("%c", x);
            pos++;
        } else {
            printf("%c", c);  
        }
    }

    printf("\n");

    return 0;
}

int encode(char c, int k) {
    char cc = tolower(c);
    int new_pos_cc = (cc - 'a' - k) % 26 + 'a';
    if (islower(c)) {
        return new_pos_cc;
    } else {
        return new_pos_cc - ('a' - 'A');
    }
}
