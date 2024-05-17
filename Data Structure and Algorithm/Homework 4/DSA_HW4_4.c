//discuss with b06303131 ¨H®aºÍ
//reference: http://sunmoon-template.blogspot.com/2015/01/split-merge-randomized-binary-search.html

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 1000000001
#define ll long long
#define find_max(a,b) ((a>b)?a:b)

typedef struct treap_node{
    struct treap_node* left;
    struct treap_node* right;
    int priority, size, rev;
    ll time, cov, sum, max, second_max, max_cnt;
} node;

node* new_node(ll time){
    node* cur = (node *)malloc(sizeof(node));
	cur->left = NULL;
	cur->right = NULL;
	cur->priority = rand();
	cur->size = 1;
	cur->rev = 0;
	cur->time = time;
	cur->cov = 0;
	cur->sum = time;
	cur->max = time;
	cur->second_max = -1;
	cur->max_cnt = 1;
	return cur;
}

int get_size(node* n){
	return n ? n->size : 0;
}

ll get_max(node* n){
	return n ? n->max : -1;
}

ll get_second_max(node* n){
	return n ? n->second_max : -1;
}

ll get_sum(node *n){
    return n ? n->sum : 0;
}

void down(node* n, char* s){
	if(n){
		if(n->rev){
			node* temp = n->left;
			n->left = n->right;
			n->right = temp;
			if(n->left)
				(n->left)->rev ^= 1;
			if(n->right)
				(n->right)->rev ^= 1;
			n->rev = 0;
		}
		if(n->cov){
			if(n->time > n->cov) n->time = n->cov;
			if(n->left && (n->left)->max > n->cov){
				(n->left)->sum -= ((n->left)->max - n->cov) * (n->left)->max_cnt;
				(n->left)->max = (n->left)->cov = n->cov;
			}
			if(n->right && (n->right)->max > n->cov){
				(n->right)->sum -= ((n->right)->max - n->cov) * (n->right)->max_cnt;
				(n->right)->max = (n->right)->cov = n->cov;
			}
			n->cov = 0;
		}
	}
}

void update(node* n){
	n->size = 1;
	n->sum = n->time;
	n->max = n->time;
	n->second_max = -1;
	n->max_cnt = 1;
	if(n->left){
		down(n->left, "update");
		n->size += get_size(n->left);
		n->sum += get_sum(n->left);
		if(n->max > (n->left)->max)
			n->second_max = (n->left)->max;
		else if(n->max < (n->left)->max){
			n->second_max = find_max((n->left)->second_max, n->max);
			n->max_cnt = (n->left)->max_cnt;
		}
		else{
			n->second_max = (n->left)->second_max;
			n->max_cnt = (n->left)->max_cnt + 1;
		}
		n->max = find_max((n->left)->max, n->max);
	}
	if(n->right){
		down(n->right, "update");
		n->size += get_size(n->right);
		n->sum += get_sum(n->right);
		if(n->max > (n->right)->max)
			n->second_max = find_max((n->right)->max, n->second_max);
		else if(n->max < (n->right)->max){
			n->second_max = find_max((n->right)->second_max, n->max);
			n->max_cnt = (n->right)->max_cnt;
		}
		else{
			n->second_max = find_max((n->right)->second_max, n->second_max);
			n->max_cnt += (n->right)->max_cnt;
		}
		n->max = find_max((n->right)->max, n->max);
	}
}

node* merge(node* a, node* b){
	if(!a || !b)
		return a ? a : b;
	if(a->priority > b->priority){
		down(a, "merge");
		a->right = merge(a->right, b);
		update(a);
		return a;
	}
	else{
		down(b, "merge");
		b->left = merge(a, b->left);
		update(b);
		return b;
	}
}

void split_by_size(node* n, node** a, node** b, int size){
	if(!n){
		*a = NULL;
		*b = NULL;
	}
	else{
		down(n, "split_by_size");
		if(size >= (get_size(n->left) + 1)){
			*a = n;
			int residual_size = size - (get_size(n->left) + 1);
			split_by_size(n->right, &((*a)->right), b, residual_size);
		}
		else{
			*b = n;
			split_by_size(n->left, a, &((*b)->left), size);
		}
		update(n);
	}
}

void insert(node** root, long long time, int pos){
	node* a = NULL;
	node* b = NULL;
	split_by_size(*root, &a, &b, pos);
	*root = merge(a, merge(new_node(time), b));
}

void del(node** root, int k){
	node* a = NULL;
	node* b = NULL;
	node* c = NULL;
	split_by_size(*root, &b, &c, k);
	split_by_size(b, &a, &b, (k - 1));
	down(b, "del");
	*root = merge(a, c);
}

void reverse(node** root, int l, int r){
	if(l != r){
        node* a = NULL;
        node* b = NULL;
        node* c = NULL;
        split_by_size(*root, &b, &c, r);
        split_by_size(b, &a, &b, (l - 1));
        b->rev ^= 1;
        *root = merge(a, merge(b, c));
	}
}

void swap(node** root, int l, int r, int x, int y){
    node* a = NULL;
    node* b = NULL;
    node* c = NULL;
    node* d = NULL;
    node* e = NULL;
    split_by_size(*root, &d, &e, y);
    split_by_size(d, &c, &d, (x - 1));
    split_by_size(c, &b, &c, r);
    split_by_size(b, &a, &b, (l - 1));
    *root = merge(a, merge(d, merge(c, merge(b, e))));
}
void DFS(node** root, ll k){
	if(!(*root)) return;
	if((*root)->max < k) return;
	if((*root)->second_max < k){
		(*root)->sum -= ((*root)->max - k) * (*root)->max_cnt;
		(*root)->cov = (*root)->max = k;
		return;
	}
	(*root)->cov = k;
	down(*root, "DFS");
	DFS(&((*root)->left), k);
	DFS(&((*root)->right), k);
	update(*root);
}
void cover(node** root, int l, int r, ll k){
    node* a = NULL;
    node* b = NULL;
    node* c = NULL;
    split_by_size(*root, &b, &c, r);
    split_by_size(b, &a, &b, (l - 1));
    DFS(&b, k);
    *root = merge(a, merge(b, c));
}

long long get_ans(node** root, int l, int r){
    node* a = NULL;
	node* b = NULL;
	node* c = NULL;
	split_by_size(*root, &b, &c, r);
	split_by_size(b, &a, &b, (l - 1));
	long long ans = b->sum;
	*root = merge(a, merge(b, c));
	return ans;
}

int main(){
    int i, n, q;
    long long time;
    srand(750);
    scanf("%d%d", &n, &q);
    node* root = NULL;
    for (i = 0; i < n; i++){
        scanf("%lld", &time);
        insert(&root, time, i);
    }
    int id, p, l, r, x, y, temp;
    ll k;
    for (i = 0; i < q; i++){
        scanf("%d", &id);
        switch(id){
            case 1:
                scanf("%d%lld", &p, &k);
                insert(&root, k, p);
                break;
            case 2:
                scanf("%d", &p);
                del(&root, p);
                break;
            case 3:
                scanf("%d%d", &l, &r);
                reverse(&root, l, r);
                break;
            case 4:
                scanf("%d%d%d%d", &l, &r, &x, &y);
                if (l > x){
                    temp = l;
                    l = x;
                    x = temp;
                }
                if (r > y){
                    temp = r;
                    r = y;
                    y = temp;
                }
                swap(&root, l, r, x, y);
                break;
            case 5:
                scanf("%d%d%lld", &l, &r, &k);
                cover(&root, l, r, k);
                break;
            case 6:
                scanf("%d%d", &l, &r);
                printf("%lld\n", get_ans(&root, l, r));
                break;
        }
    }
    return 0;
}

