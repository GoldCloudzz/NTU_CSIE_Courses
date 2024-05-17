//discuss with b06303131
#include <stdio.h>

long long int max2(long long int a, long long int b){
    return (a > b)? a : b;
}

long long int max3(long long int a, long long int b, long long int c){
    return (a > b)? (a > c? a : c) : (b > c? b : c);
}

int main(){
    int t, flag;
    scanf("%d%d", &t, &flag);
    for (int i = 0; i < t; i++){
        int n;
        scanf("%d", &n);
        long long int num[n];
        for (int j = 0; j < n; j++){
            scanf("%lli", &num[j]);
        }
        long long int max_sweetness[2][n];
		for(int j = 0; j < n; j++){
            max_sweetness[0][j] = -1000000001;
			max_sweetness[1][j] = -1000000001;
		}
        int parent[n];
        for (int j = 0; j < n; j++)
            parent[j] = -1;
        int positive_end = -1;
        int negative_end = -1;
		if (num[0] > 0){
			max_sweetness[0][0] = num[0];
			positive_end = 0;
		}
		else if (num[0] < 0){
			max_sweetness[1][0] = num[0];
			negative_end = 0;
		}
		else{
			max_sweetness[0][0] = num[0];
			max_sweetness[1][0] = num[0];
			positive_end = 0;
			negative_end = 0;

		}
		for (int j = 1; j < n; j++){
			if (num[j] > 0){
				max_sweetness[0][j] = max3((max_sweetness[1][j - 1] + num[j]), num[j], max_sweetness[0][j - 1]);
				max_sweetness[1][j] = max_sweetness[1][j - 1];
				if (max_sweetness[0][j] == (max_sweetness[1][j - 1] + num[j])){
                    parent[j] = negative_end;
                    positive_end = j;
				}
				else if (max_sweetness[0][j] == num[j])
                    positive_end = j;
			}
			else if (num[j] < 0){
				max_sweetness[0][j] = max_sweetness[0][j - 1];
				max_sweetness[1][j] = max3((max_sweetness[0][j - 1] + num[j]), num[j], max_sweetness[1][j - 1]);
				if (max_sweetness[1][j] == (max_sweetness[0][j - 1] + num[j])){
                    parent[j] = positive_end;
                    negative_end = j;
				}
				else if (max_sweetness[1][j] == num[j])
                    negative_end = j;
			}
			else{
				max_sweetness[0][j] = max3(max_sweetness[0][j - 1], max_sweetness[1][j - 1], num[j]);
				max_sweetness[1][j] = max3(max_sweetness[0][j - 1], max_sweetness[1][j - 1], num[j]);
				if (max_sweetness[0][j] == max_sweetness[0][j - 1]){
                    parent[j] = positive_end;
				}
				else if (max_sweetness[0][j] == max_sweetness[1][j - 1]){
                    parent[j] = negative_end;
				}
				positive_end = j;
                negative_end = j;
			}
		}
		long long int result = max2(max_sweetness[0][n - 1], max_sweetness[1][n - 1]);
        printf("%lli\n", result);
        if (flag){
            int index[n];
            int k;
            int number = 0;
            if (result == max_sweetness[0][n - 1]){
                k = positive_end;
                while (k != -1){
                    index[number] = k + 1;
                    k = parent[k];
                    number++;
                }
            }
            else{
                k = negative_end;
                while (k != -1){
                    index[number] = k + 1;
                    k = parent[k];
                    number++;
                }
            }
            printf("%d ", number);
            for (int j = (number - 1); j >= 0; j--)
                printf("%d ", index[j]);
            printf("\n");
        }
    }
    return 0;
}
