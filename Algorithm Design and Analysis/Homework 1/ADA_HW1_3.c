//discuss with b06303131 ¨H®aºÍ

#include <stdio.h>
long long int count = 0;

void merge(int [], int [], int [], int [], int [], int [], int, int, int);

void merge_sort(int [], int [], int [], int [], int [], int [], int, int);

void divide(int [], int [], int [], int [], int [], int [], int, int);

void conquer(int [], int [], int [], int [], int [], int [], int, int, int, double);

int top_left_x = -1;
int top_left_y = -1;
int top_right_x = -1;
int top_right_y = -1;

void push_left_x(int[], int);
void push_left_y(int[], int);
void push_right_x(int[], int);
void push_right_y(int[], int);

void pop_left_x(int[]);
void pop_left_y(int[]);
void pop_right_x(int[]);
void pop_right_y(int[]);

int binary_search(int [], int, int, int);

int main(){
    int n;
    scanf("%d", &n);
    int x[n], y[n];
    for (int i = 0; i < n; i++)
        scanf("%d%d", &x[i], &y[i]);
    int x1[n], x2[n], y1[n], y2[n];
    merge_sort(x, y, x1, x2, y1, y2, 0, n - 1);
    divide(x, y, x1, x2, y1, y2, 0, n - 1);
    printf("%lli", count);
    return 0;
}

void merge(int x[], int y[], int x1[], int x2[], int y1[], int y2[], int head, int mid, int tail){
    int lenA = mid - head + 1;
    int lenB = tail - mid;
    int i, j;
    for(i = 0; i < lenA; i++){
        x1[i] = x[head + i];
        y1[i] = y[head + i];
    }
    for(j = 0; j < lenB; j++){
        x2[j] = x[mid + 1 + j];
        y2[j] = y[mid + 1 + j];
    }
    i = 0;
    j = 0;
    int k = head;
    while(i < lenA && j < lenB){
        if(x1[i] < x2[j]){
            x[k] = x1[i];
            y[k] = y1[i];
            i++;
        }
        else{
            x[k] = x2[j];
            y[k] = y2[j];
            j++;
        }
        k++;
    }
    while(i < lenA){
        x[k] = x1[i];
        y[k] = y1[i];
        i++;
        k++;
    }
    while(j < lenB){
        x[k] = x2[j];
        y[k] = y2[j];
        j++;
        k++;
    }
}

void merge_sort(int x[], int y[], int x1[], int x2[], int y1[], int y2[], int head, int tail){
    if(head < tail){
        int mid = (head + tail) / 2;
        merge_sort(x, y, x1, x2, y1, y2, head, mid);
        merge_sort(x, y, x1, x2, y1, y2, mid + 1, tail);
        merge(x, y, x1, x2, y1, y2, head, mid, tail);
    }
}

void divide(int x[], int y[], int x1[], int x2[], int y1[], int y2[], int head, int tail){
    if (head < tail){
        int mid = (head + tail) / 2;
        double center = (x[mid] + x[mid + 1]) / 2.0;
        divide(x, y, x1, x2, y1, y2, head, mid);
        divide(x, y, x1, x2, y1, y2, mid + 1, tail);
        conquer(x, y, x1, x2, y1, y2, head, mid, tail, center);
    }
}

void conquer(int x[], int y[], int x1[], int x2[], int y1[], int y2[], int head, int mid, int tail, double center){
    int len = tail - head + 1;
    int lenA = mid - head + 1;
    int lenB = tail - mid;
    int i, j;
    for(i = 0; i < lenA; i++){
        x1[i] = x[head + i];
        y1[i] = y[head + i];
    }
    for(j = 0; j < lenB; j++){
        x2[j] = x[mid + 1 + j];
        y2[j] = y[mid + 1 + j];
    }
    i = 0;
    j = 0;
    int k = head;
    while(i < lenA && j < lenB){
        if(y1[i] < y2[j]){
            x[k] = x1[i];
            y[k] = y1[i];
            i++;
        }
        else{
            x[k] = x2[j];
            y[k] = y2[j];
            j++;
        }
        k++;
    }
    while(i < lenA){
        x[k] = x1[i];
        y[k] = y1[i];
        i++;
        k++;
    }
    while(j < lenB){
        x[k] = x2[j];
        y[k] = y2[j];
        j++;
        k++;
    }
    int stack_left_x[len], stack_left_y[len], stack_right_x[len], stack_right_y[len];
    top_left_x = -1;
    top_left_y = -1;
    top_right_x = -1;
    top_right_y = -1;
    for (i = head; i <= tail; i++){
        if (x[i] > center){
            while (top_right_x != -1){
                if (stack_right_x[top_right_x] > x[i]){
                    pop_right_x(stack_right_x);
                    pop_right_y(stack_right_y);
                }
                else
                    break;
            }
            if (top_right_y == -1){
                count += (top_left_y + 1);
            }
            else{
                count += (top_left_y - binary_search(stack_left_y, 0, top_left_y + 1, stack_right_y[top_right_y]) + 1);
            }
            push_right_x(stack_right_x, x[i]);
            push_right_y(stack_right_y, y[i]);
        }
        else {
            while (top_left_x != -1){
                if (stack_left_x[top_left_x] < x[i]){
                    pop_left_x(stack_left_x);
                    pop_left_y(stack_left_y);
                }
                else
                    break;
            }
            if (top_left_y == -1){
                count += (top_right_y + 1);
            }
            else{
                count += (top_right_y - binary_search(stack_right_y, 0, top_right_y + 1, stack_left_y[top_left_y]) + 1);
            }
            push_left_x(stack_left_x, x[i]);
            push_left_y(stack_left_y, y[i]);
        }
    }
}

void push_left_x(int stack_left_x[], int n){
    top_left_x++;
    stack_left_x[top_left_x] = n;
}

void push_left_y(int stack_left_y[], int n){
    top_left_y++;
    stack_left_y[top_left_y] = n;
}

void push_right_x(int stack_right_x[], int n){
    top_right_x++;
    stack_right_x[top_right_x] = n;
}

void push_right_y(int stack_right_y[], int n){
    top_right_y++;
    stack_right_y[top_right_y] = n;
}

void pop_left_x(int stack_left_x[]){
    top_left_x--;
}

void pop_left_y(int stack_left_y[]){
    top_left_y--;
}

void pop_right_x(int stack_right_x[]){
    top_right_x--;
}

void pop_right_y(int stack_right_y[]){
    top_right_y--;
}

int binary_search(int array[], int head, int tail ,int n){
    while (head < tail) {
        int mid = head + (tail - head) / 2;
        if (n <= array[mid]) {
            tail = mid;
        } else {
            head = mid + 1;
        }
    }
    return head;
}
