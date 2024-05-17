#include <stdio.h>

long long int gcd_value(long long int a, long long int b){
    while(b != 0) {
        long long int c = a % b;
        a = b;
        b = c;
    }
    return a;
}

long long int max4(long long int a, long long int b, long long int c, long long int d){
    long long int e = (a > b)? a : b;
    long long int f = (c > d)? c : d;
    return (e > f)? e : f;
}

int main(){
    int n;
    scanf("%d", &n);
    long long int num[n];
    int i, j;
    for (i = 0; i < n; i++)
        scanf("%lld", &num[i]);
    long long int gcd[n][n];
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++)
            gcd[i][j] = gcd_value(num[i], num[j]);
    }
    long long int dp[n][n];
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++)
            dp[i][j] = -1;
    }
    for (i = 0; i < (n - 1); i++){
        if (gcd[i][i + 1] != 1)
            dp[i][i + 1] = gcd[i][i + 1];
    }
    for (i = 0; i < (n - 2); i++){
        if (gcd[i][i + 1] != 1 && gcd[i + 1][i + 2] != 1 && gcd[i][i + 2] != 1)
            dp[i][i + 2] = gcd[i][i + 1] + gcd[i + 1][i + 2];
    }
    int len, m;
    long long int max, max1, max2, max3, temp;
    for (len = 3; len < n; len++){
        for (i = 0; i < (n - len); i++){
            j = i + len;
            max1 = -1;
            max2 = -1;
            max3 = -1;
            if (gcd[i][j] != 1 && dp[i + 1][j - 1] != -1)
                max1 = dp[i + 1][j - 1] + gcd[i][j];
            for (m = (i + 1); m < j; m++){
                if (m == (i + 1)){
                    if (gcd[i][m] != 1 && gcd[m][j] != 1 && gcd[i][j] != 1 && dp[m + 1][j - 1] != -1){
                        temp = dp[m + 1][j - 1] + gcd[i][m] + gcd[m][j];
                        if (temp > max2)
                            max2 = temp;
                    }
                }
                else if (m == (j - 1)){
                    if (gcd[i][m] != 1 && gcd[m][j] != 1 && gcd[i][j] != 1 && dp[i + 1][m - 1] != -1){
                        temp = dp[i + 1][m - 1] + gcd[i][m] + gcd[m][j];
                        if (temp > max2)
                            max2 = temp;
                    }
                }
                else{
                    if (gcd[i][m] != 1 && gcd[m][j] != 1 && gcd[i][j] != 1 && dp[i + 1][m - 1] != -1 && dp[m + 1][j - 1] != -1){
                        temp = dp[i + 1][m - 1] + dp[m + 1][j - 1] + gcd[i][m] + gcd[m][j];
                        if (temp > max2)
                            max2 = temp;
                    }
                }
            }
            for (m = (i + 1); m < (j - 1); m++){
                if (dp[i][m] != -1 && dp[m + 1][j] != -1){
                    temp = dp[i][m] + dp[m + 1][j];
                    if (temp > max3)
                        max3 = temp;
                }
            }
            dp[i][j] = max4(-1, max1, max2, max3);
        }
    }
    printf("%lld", dp[0][n - 1]);
    return 0;
}
