//discuss with b06303131 ¨H®aºÍ

#include <stdio.h>
#include <stdlib.h>
#define ll long long
typedef struct Stack_element{
    int x;
    int *x_ptr;
    char attr;
    struct Stack_element *pre, *next;
}stack_node;

typedef struct Stack {
    struct Stack_element *head, *tail;
    int size;
}stack;

typedef struct DSU{
	int *parent, *height;
	struct Stack stk;
}dsu;


typedef struct INT_LL{
	struct INT_LL *next;
	int data;
}list;

typedef struct GraphNode{
	char op;
	int x, y, k;
	int visited;
	int num;
	int flag;
	struct INT_LL *adj_head, *adj_tail;
}Node;

typedef struct Ans_Node{
	int day;
	int num;
}ans_node;

list* New_List_Node(int data){
	list *cur = malloc(sizeof(list));
	cur->data = data;
	cur->next = NULL;
	return cur;
}

void list_insert(Node *graph, int v1, int v2){
	list *cur = New_List_Node(v2);
	if(graph[v1].adj_head == NULL) graph[v1].adj_head = graph[v1].adj_tail = cur;
	else{
		graph[v1].adj_tail->next = cur;
		graph[v1].adj_tail = cur;
	}
}

void add_edge(Node *graph, int v1, int v2){
	list_insert(graph, v1, v2);
	list_insert(graph, v2, v1);
}

void stack_init(stack *stk) {
    stk->head = malloc(sizeof(stack_node));
    stk->tail = malloc(sizeof(stack_node));
    stk->head->next = stk->tail;
    stk->head->pre = NULL;
    stk->tail->pre = stk->head;
    stk->tail->next = NULL;
    stk->size = 0;
}

void stack_push(stack *stk, int x, int *y, char attr) {
    stack_node* cur = malloc(sizeof(stack_node));
    cur->x = x;
    cur->x_ptr = y;
    cur->attr = attr;
    stk->tail->pre->next = cur;
    cur->pre = stk->tail->pre;
    cur->next = stk->tail;
    stk->tail->pre = cur;
    ++stk->size;
}


stack_node* stack_pop(stack *stk){
	stack_node *res = stk->tail->pre;
    stk->tail->pre = stk->tail->pre->pre;
    stk->tail->pre->next = stk->tail;
    --stk->size;
    return res;
}

dsu* djs_init(int n) {
	dsu *dsu_set = malloc(sizeof(dsu));
    dsu_set->parent = malloc((n+1) * sizeof(int));
    dsu_set->height = malloc((n+1) * sizeof(int));
    for (int i = 0; i <= n; ++i) {
        dsu_set->parent[i] = i;
        dsu_set->height[i] = 1;
    }
    stack_init(&dsu_set->stk);
    return dsu_set;
}

void undo_dsu(dsu *dsu_set){
	stack_node *top = stack_pop(&dsu_set->stk);
	*(top->x_ptr) = top->x;
	if(top->attr == 'h'){
		top = stack_pop(&dsu_set->stk);
		*(top->x_ptr) = top->x;
	}
}

void djs_assign(dsu *dsu_set, int *x, int v, char attr) {
    stack_push(&dsu_set->stk, *x, x, attr);
    *x = v;
}
int djs_find(dsu *dsu_set, int x) {
    return dsu_set->parent[x] == x ? x : djs_find(dsu_set, dsu_set->parent[x]);
}
int union_by_height(dsu *dsu_set, int x, int y){
	int parent1 = djs_find(dsu_set, x);
	int parent2 = djs_find(dsu_set, y);
	if(parent1 == parent2) return 0;//union fail

	if(dsu_set->height[parent1] > dsu_set->height[parent2])
		djs_assign(dsu_set, &dsu_set->parent[parent2], parent1, 'p');
	else if(dsu_set->height[parent1] < dsu_set->height[parent2])
		djs_assign(dsu_set, &dsu_set->parent[parent1], parent2, 'p');
	else{
		djs_assign(dsu_set, &dsu_set->parent[parent2], parent1, 'p');
		djs_assign(dsu_set, &dsu_set->height[parent1], dsu_set->height[parent1]+1, 'h');
	}
	return 1;//union successful
}

void DFS(Node *graph, int v, ans_node *ans_ary, int cur_num, dsu *dsu_set, int *ans_cnt){
	graph[v].visited = 1;
	if(graph[v].op == 'm'){
		int flag = union_by_height(dsu_set, graph[v].x, graph[v].y);
		graph[v].flag = flag;
		if(flag){
			cur_num--;
			graph[v].num = cur_num;
		}
		else graph[v].num = cur_num;
	}
	else if(graph[v].op == 'q'){
		ans_ary[*ans_cnt].day = v;
		ans_ary[(*ans_cnt)++].num = cur_num;
		graph[v].num = cur_num;
	}
	else if(graph[v].op == 'b'){
		graph[v].num = cur_num;
	}
	for(list* i = graph[v].adj_head;i != NULL;i = i->next){
		int next = i->data;
		if(graph[next].visited == 0) DFS(graph, next, ans_ary, graph[v].num, dsu_set, ans_cnt);
	}
	if(graph[v].op == 'm' && graph[v].flag == 1) undo_dsu(dsu_set);
}

int cmp(const void *a ,const void *b){return (*(ans_node *)a).day > (*(ans_node *)b).day ? 1 : -1;}

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	Node graph[m+1];
	graph[0].op = 'n';
	graph[0].x = graph[0].y = graph[0].k = -1;
	graph[0].visited = graph[0].flag = 0;
	graph[0].num = n;
	graph[0].adj_head = graph[0].adj_tail = NULL;
	int query_num = 0;
	for(int i = 1;i <= m;++i){
		char operation[8];
		scanf("%s", operation);
		if(operation[0] == 'q'){
			graph[i].op = 'q';
			graph[i].x = graph[i].y = graph[i].k = -1;
			graph[i].visited = 0;
			graph[i].flag = 0;
			graph[i].num = 0;
			graph[i].adj_head = graph[i].adj_tail = NULL;
			query_num++;
		}
		else if(operation[0] == 'm'){
			int x, y;
			scanf("%d%d", &x, &y);
			graph[i].op = 'm';
			graph[i].x = x;
			graph[i].y = y;
			graph[i].k = -1;
			graph[i].visited = graph[i].num = graph[i].flag = 0;
			graph[i].adj_head = graph[i].adj_tail = NULL;
		}
		else if(operation[0] == 'b'){
			int k;
			scanf("%d", &k);
			graph[i].op = 'b';
			graph[i].x = graph[i].y = -1;
			graph[i].k = k;
			graph[i].visited = graph[i].num = graph[i].flag = 0;
			graph[i].adj_head = graph[i].adj_tail = NULL;
		}
	}
	ans_node *ans_ary = malloc(query_num * sizeof(ans_node));
	for(int i = m;i >= 1;--i){
		if(graph[i].op == 'b') add_edge(graph, i, graph[i].k);
		else add_edge(graph, i-1, i);
	}
	dsu *dsu_set = djs_init(n);
	int ans_cnt = 0;
	DFS(graph, 0, ans_ary, graph[0].num, dsu_set, &ans_cnt);
	qsort(ans_ary, query_num, sizeof(ans_node), cmp);
	for(int i = 0;i < query_num;i++) printf("%d\n", ans_ary[i].num);
}

