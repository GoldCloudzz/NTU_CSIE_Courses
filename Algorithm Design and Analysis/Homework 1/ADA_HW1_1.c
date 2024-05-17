#include <stdio.h>

long long int count = 0;
void Hanoi(int [], long long int [], int, int, int, int);

int main(){
    int n;
    scanf("%d", &n);
    long long int two[n + 1];
    long long int a = 1;
    for (int i = 0; i < n; i++){
        two[i] = a;
        a = (2 * a) % 998244353;
    }
    int disk[n + 1];
    disk[0] = 0;
    for (int i = 0; i < 3; i++){
        int x;
        scanf("%d", &x);
        for (int j = 0; j < x; j++){
            int y;
            scanf("%d", &y);
            disk[y] = i;
        }
    }
    Hanoi(disk, two, n, 0, 1, 2);
    count %= 998244353;
    printf("%lld", count);
    return 0;
}

void Hanoi(int disk[], long long int two[], int n, int a, int b, int c){
    if (n > 0){
        if (disk[n] == a){
            count = (count + two[n - 1]) % 998244353;
            Hanoi(disk, two, (n - 1), a, c, b);
        }
        else if (disk[n] == c){
            Hanoi(disk, two, (n - 1), b, a, c);
        }
        else{
            count = -1;
        }
    }
}
