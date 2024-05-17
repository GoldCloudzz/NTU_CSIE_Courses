// reference: https://leetcode.com/problems/shortest-palindrome/discuss/60141/C%2B%2B-8-ms-KMP-based-O(n)-time-and-O(n)-memory-solution
#include <stdio.h>
#include <string.h>

#define MAX 10000000

char string[MAX], string_reverse[MAX], kmp_string[2 * MAX + 1];
int pi[2 * MAX + 1];

int main(){
    scanf("%s", string);
    int len = strlen(string);
    int i, j;
    for (i = 0; i < len; i++)
        string_reverse[i] = string[len - 1 - i];
    strcpy(kmp_string, string);
    kmp_string[len] = ' ';
    strcpy((kmp_string + len + 1), string_reverse);
    pi[0] = 0;
    for (i = 1; i < (2 * len + 1); i++){
        j = pi[i - 1];
        while (j > 0 && kmp_string[i] != kmp_string[j])
            j = pi[j - 1];
        pi[i] = j;
        if (kmp_string[i] == kmp_string[j])
            pi[i]++;
    }
    int front = len - pi[2 * len];
    strcpy(kmp_string, string_reverse);
    kmp_string[len] = ' ';
    strcpy((kmp_string + len + 1), string);
    for (i = 1; i < (2 * len + 1); i++){
        j = pi[i - 1];
        while (j > 0 && kmp_string[i] != kmp_string[j])
            j = pi[j - 1];
        pi[i] = j;
        if (kmp_string[i] == kmp_string[j])
            pi[i]++;
    }
    int back = len - pi[2 * len];
    if (front < back){
        printf("%d\n", front);
        for (i = 0; i < front; i++)
            printf("%c", string[len - 1 - i]);
        printf("%s\n", string);
    }
    else if (front == back){
        if (front == 0){
            printf("%d\n", front);
            printf("%s\n", string);
        }
        else{
            printf("%d\n", front);
            for (i = 0; i < front; i++)
                printf("%c", string[len - 1 - i]);
            printf("%s\n", string);
            printf("%s", string);
            for (i = (back - 1); i >= 0; i--)
                printf("%c", string[i]);
            printf("\n");
        }

    }
    else{
        printf("%d\n", back);
        printf("%s", string);
        for (i = (back - 1); i >= 0; i--)
            printf("%c", string[i]);
        printf("\n");
    }
    return 0;
}
