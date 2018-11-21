#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    string s = get_string("name: ");
    int n = strlen(s);
    printf("%c", toupper(s[0]));
    for (int i = 1; i < n; i++) {
        if (s[i] == ' ' && i < n + 1) {
            printf("%c", toupper(s[i + 1]));
        }
    }
    printf("\n");
} 
