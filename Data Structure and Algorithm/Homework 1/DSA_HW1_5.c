#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

//discuss with b06303131 ¨H®aºÍ

typedef struct USB{ //xor linked list
    int id;
    struct USB* addr;
} node_usb;

typedef struct Group{ //doubly linked list
    int id;
    struct Group* prev;
    struct Group* next;
    node_usb* head;
    node_usb* tail;
} node_group;

typedef struct Bathroom{ //array
    int id;
    int prev;
    int next;
    node_group* head;
    node_group* tail;
} node_bathroom;

node_usb* XOR(node_usb* a, node_usb* b){
    return (node_usb*) ((uintptr_t) a ^ (uintptr_t) b);
}

node_usb* usb_init(int id){
    node_usb* new_usb = malloc(sizeof(node_usb));
    new_usb->id = id;
    return new_usb;
}

void usb_insert(node_usb* usb, node_group* group){
    usb->addr = XOR(group->tail, NULL);
    if (!group->head)
        group->head = usb;
    else
        group->tail->addr = XOR(usb, XOR(group->tail->addr, NULL));
    group->tail = usb;
}

void usb_remove_head(node_group* group, node_bathroom* bathroom, int k, node_group* group_ptr[][k]){
    node_usb* new_head = XOR(group->head->addr, NULL);
    if (new_head){
        new_head->addr = XOR(XOR(new_head->addr, group->head), NULL);
        group->head = new_head;
    }
    else{
        group_ptr[bathroom->id][bathroom->head->id] = NULL;
        bathroom->head = bathroom->head->next;
        if (bathroom->head)
            bathroom->head->prev = NULL;
        else
            bathroom->tail = NULL;
    }
}


void usb_remove_tail(node_group* group, node_bathroom* bathroom, int k, node_group* group_ptr[][k]){
    node_usb* new_tail = XOR(group->tail->addr, NULL);
    if (new_tail){
        new_tail->addr = XOR(XOR(new_tail->addr, group->tail), NULL);
        group->tail = new_tail;
    }
    else{
        group_ptr[bathroom->id][bathroom->tail->id] = NULL;
        bathroom->tail = bathroom->tail->prev;
        if (bathroom->tail)
            bathroom->tail->next = NULL;
        else
            bathroom->head = NULL;
    }
}

node_group* group_init(int id){
    node_group* new_group = malloc(sizeof(node_group));
    new_group->id = id;
    new_group->prev = NULL;
    new_group->next = NULL;
    new_group->head = NULL;
    new_group->tail = NULL;
    return new_group;
}

void group_insert(node_group* group, node_bathroom* bathroom){
    group->prev = bathroom->tail;
    if (!bathroom->head)
        bathroom->head = group;
    else
        bathroom->tail->next = group;
    bathroom->tail = group;
}

node_bathroom* bathroom_init(int id, int m){
    node_bathroom* new_bathroom = malloc(sizeof(node_bathroom));
    new_bathroom->id = id;
    if (id == 0)
        new_bathroom->prev = m - 1;
    else
        new_bathroom->prev = id - 1;
    if (id == (m - 1))
        new_bathroom->next = 0;
    else
        new_bathroom->next = id + 1;
    new_bathroom->head = NULL;
    new_bathroom->tail = NULL;
    return new_bathroom;
}

int main(){
    int m, n, k;
    scanf("%d%d%d", &m, &n, &k); // m bathrooms, n situations and k groups
    int i, j;
    int bathroom_close[m]; // 0: open, 1: close
    for (i = 0; i < m; i++)
        bathroom_close[i] = 0;
    node_group* group_ptr[m][k];
    for (i = 0; i < m; i++){
        for (j = 0; j < k; j++)
            group_ptr[i][j] = NULL;
    }
    node_bathroom* bathrooms[m];
    for (i = 0; i < m; i++)
        bathrooms[i] = bathroom_init(i, m);
    char operation[8];
    int usb_id, group_id, bathroom_id;
    int new_bathroom;
    node_usb* new_usb;
    node_group *new_group, *prev_group, *old_group;
    for (i = 0; i < n; i++){
        scanf("%s", operation);
        if (operation[0] == 'e'){ //enter
            scanf("%d%d%d", &group_id, &usb_id, &bathroom_id);
            if (!group_ptr[bathroom_id][group_id]){
                new_group = group_init(group_id);
                group_insert(new_group, bathrooms[bathroom_id]);
                group_ptr[bathroom_id][group_id] = new_group;
            }
            new_usb = usb_init(usb_id);
            usb_insert(new_usb, group_ptr[bathroom_id][group_id]);
        }
        else if (operation[0] == 'l'){ //leave
            scanf("%d", &bathroom_id);
            usb_remove_tail(bathrooms[bathroom_id]->tail, bathrooms[bathroom_id], k, group_ptr);
        }
        else if (operation[0] == 'g'){ //go
            scanf("%d", &bathroom_id);
            usb_remove_head(bathrooms[bathroom_id]->head, bathrooms[bathroom_id], k, group_ptr);
        }
        else if (operation[0] == 'c'){ //close
            scanf("%d", &bathroom_id);
            new_bathroom = bathrooms[bathroom_id]->prev;
            if (bathrooms[bathroom_id]->head != NULL){
                new_group = bathrooms[bathroom_id]->tail;
                while (new_group){
                    prev_group = new_group->prev;
                    if (group_ptr[new_bathroom][new_group->id]){
                        old_group = group_ptr[new_bathroom][new_group->id]; // new insert into old
                        old_group->tail->addr = XOR(XOR(old_group->tail->addr, NULL), new_group->tail);
                        new_group->tail->addr = XOR(XOR(new_group->tail->addr, NULL), old_group->tail);
                        old_group->tail = new_group->head;
                    }
                    else{
                        group_ptr[new_bathroom][new_group->id] = new_group;
                        new_usb = new_group->head;
                        new_group->head = new_group->tail;
                        new_group->tail = new_usb;
                        new_group->prev = bathrooms[new_bathroom]->tail;
                        if (!bathrooms[new_bathroom]->head)
                            bathrooms[new_bathroom]->head = new_group;
                        else
                            bathrooms[new_bathroom]->tail->next = new_group;
                        bathrooms[new_bathroom]->tail = new_group;
                        bathrooms[new_bathroom]->tail->next = NULL;
                    }
                    new_group = prev_group;
                }
            }
            bathrooms[bathrooms[bathroom_id]->prev]->next = bathrooms[bathroom_id]->next;
            bathrooms[bathrooms[bathroom_id]->next]->prev = bathrooms[bathroom_id]->prev;
            bathroom_close[bathroom_id] = 1;
        }
    }
    node_usb *prev_usb, *cur_usb, *next_usb;
    for (i = 0; i < m; i++){
        if (!bathroom_close[i]){
            new_group = bathrooms[i]->head;
            while (new_group){
                prev_usb = NULL;
                cur_usb = new_group->head;
                next_usb;
                while (cur_usb){
                    printf("%d ", cur_usb->id);
                    next_usb = XOR(prev_usb, cur_usb->addr);
                    prev_usb = cur_usb;
                    cur_usb = next_usb;
                }
                new_group = new_group->next;
            }
        }
        printf("\n");
    }
    return 0;
}
