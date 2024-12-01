#include <stdio.h>
#include <stdlib.h>

#define MAXIMUM_STACK_SIZE 11
#define TRUE 1
#define FALSE 0

typedef struct node * treepointer;
typedef struct node{
    char data;
    treepointer left_child, right_child;
} node;

void free_tree(treepointer ptr);
treepointer T1(void);
void postorder(treepointer ptr, int *, char *);
void iter_postorder(treepointer ptr);
void push(treepointer * stack, int * top, treepointer item);
treepointer pop(treepointer * stack, int * top);

int main(void){
    int idx = 0;
    char * arr = malloc(11 * sizeof(char));
    treepointer root = T1();

    printf("postorder traversal recursive version is executed\n\n");

    postorder(root, &idx, arr);

    
    printf("postorder traversal iterative version is executed\n");
    iter_postorder(root);
    printf("\n");

    free_tree(root);
    free(arr);

    return 0;
}

treepointer T1(void){
    treepointer treeptr_A = (treepointer)malloc(sizeof(node));
    treepointer treeptr_B = (treepointer)malloc(sizeof(node));
    treepointer treeptr_C = (treepointer)malloc(sizeof(node));
    treepointer treeptr_D = (treepointer)malloc(sizeof(node));
    treepointer treeptr_E = (treepointer)malloc(sizeof(node));
    treepointer treeptr_F = (treepointer)malloc(sizeof(node));
    treepointer treeptr_G = (treepointer)malloc(sizeof(node));
    treepointer treeptr_H = (treepointer)malloc(sizeof(node));
    treepointer treeptr_I = (treepointer)malloc(sizeof(node));
    treepointer treeptr_J = (treepointer)malloc(sizeof(node));
    treepointer treeptr_K = (treepointer)malloc(sizeof(node));
    
    treeptr_A->data = 'A';
    treeptr_B->data = 'B';
    treeptr_C->data = 'C';
    treeptr_D->data = 'D';
    treeptr_E->data = 'E';
    treeptr_F->data = 'F';
    treeptr_G->data = 'G';
    treeptr_H->data = 'H';
    treeptr_I->data = 'I';
    treeptr_J->data = 'J';
    treeptr_K->data = 'K';
    
    treeptr_A->left_child = treeptr_B;
    treeptr_A->right_child = NULL;
    
    treeptr_B->left_child = treeptr_F;
    treeptr_B->right_child = treeptr_C;
    
    treeptr_C->left_child = NULL;
    treeptr_C->right_child = treeptr_D;
    
    treeptr_D->left_child = NULL;
    treeptr_D->right_child = treeptr_E;
    
    treeptr_E->left_child = treeptr_H;
    treeptr_E->right_child = NULL;
    
    treeptr_F->left_child = treeptr_K;
    treeptr_F->right_child = treeptr_G;
    
    treeptr_G->left_child = NULL;
    treeptr_G->right_child = NULL;
    
    treeptr_H->left_child = NULL; 
    treeptr_H->right_child = treeptr_I;
    
    treeptr_I->left_child = NULL;
    treeptr_I->right_child = treeptr_J;
    
    treeptr_J->left_child = NULL;
    treeptr_J->right_child = NULL;
    
    treeptr_K->left_child = NULL;
    treeptr_K->right_child = NULL;
    
    return treeptr_A;
}

void postorder(treepointer ptr, int * idx, char * arr){
    int prev_idx = (*idx);
    if (ptr){
        printf("Visited root: %c\n", ptr->data);
        postorder(ptr->left_child, &(*idx), arr);
        postorder(ptr->right_child, &(*idx), arr);
        arr[(*idx)++] = ptr->data;
        printf("Leaving root: %c\n", ptr->data);
    }

    if ((*idx) > 0 && prev_idx < (*idx)){
        printf("recursive traversal result: ");
        for (int i = 0; i < (*idx); i++)
            printf("%c ", arr[i]);
        printf("\n\n");
    }
}


void iter_postorder(treepointer ptr){
    int top = -1;
    treepointer stack[MAXIMUM_STACK_SIZE];
    treepointer prev = (treepointer)malloc(sizeof(node));
    prev->data = '\0';
    
    if (!ptr)
        return;

    printf("iterative traversal result: ");
    while(TRUE){
        while (ptr){
            if (ptr->data == prev->data)
                break;
            push(stack, &top, ptr);
            ptr = ptr->left_child;
        }
        
        if (top == -1)
            break;
        
        ptr = pop(stack, &top);
        
        if (ptr->right_child){
            if (ptr->right_child->data != prev->data){
                push(stack, &top, ptr);
                ptr = ptr->right_child;
                continue;
            }
        }
        
        printf("%c ", ptr->data);
        prev = ptr;
    }
}

void push(treepointer * stack, int * top, treepointer item){
    if (*top == MAXIMUM_STACK_SIZE){
        printf("stack overflow");
        exit(1);
    }
    stack[++(*top)] = item;
    
}

treepointer pop(treepointer * stack, int * top){
    treepointer temp = stack[(*top)];
    stack[(*top)--] = NULL;
    
    return temp;
}

void free_tree(treepointer ptr){
    if (ptr){
        free_tree(ptr->left_child);
        free_tree(ptr->right_child);
        free(ptr);
    }
}
