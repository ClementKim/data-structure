#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

#define MAX_QUEUE_SIZE 5
#define MAX_ARR_SIZE 5

#define BELL_1 101
#define BELL_2 102
#define BELL_3 103
#define BELL_4 104
#define BELL_5 105

typedef struct{
    int key;
} element;

void initializing_bell_arr(int **queue);
void initializing_order_queue(element **queue);

int initial_menu(void);
int check_waiting(int **bell_arr);
int ask_to_order(int number_of_waiting);
int bell_select(void);
int valid_bell_number_or_not(int bell_number);
int add_order_q(element ** queue, int ** arr, int * queue_index, int target_number);

void complete_order(element **queue, int ** arr, int * queue_index);

void error_message(void);
void impossible_to_order(void);

int main(void){
    int initial_selection;
    int number_of_waiting;
    int order_selection;
    int bell_number_selection;
    int possible;
    int order_queue_index_to_put = 0;
    int order_queue_index_to_out = 0;
    
    int *bell_arr = malloc(MAX_ARR_SIZE * sizeof(int));
    element *order_queue = malloc(MAX_QUEUE_SIZE * sizeof(element));
    
    if (bell_arr == NULL || order_queue == NULL){
        fprintf(stderr, "Failed memory allocation\n");
        exit(1);
    }
    
    initializing_bell_arr(&bell_arr);
    initializing_order_queue(&order_queue);
    
    while (TRUE){
        initial_selection = initial_menu();
        
        if (initial_selection == 1){
            number_of_waiting = check_waiting(&bell_arr);
            
            if (number_of_waiting >= 5)
                impossible_to_order();
            
            else{
                while (TRUE){
                    order_selection = ask_to_order(number_of_waiting);
                    
                    if (order_selection == 1){
                        while (TRUE){
                            bell_number_selection = bell_select();
                            
                            if (valid_bell_number_or_not(bell_number_selection)){
                                
                                possible = add_order_q(&order_queue, &bell_arr, &order_queue_index_to_put, bell_number_selection);
                                
                                if (possible){
                                    printf("주문이 완료되었습니다.\n\n");
                                    break;
                                }
                                else
                                    printf("\n사용 중인 진동벨 번호입니다.\n\n");
                            }
                            
                            else
                                error_message();
                        }
                        
                        break;
                    }
                    
                    else if (order_selection == 2){
                        printf("\n************************\n");
                        printf("주문을 취소하셨습니다.\n");
                        printf("************************\n\n");
                        break;
                    }
                    
                    else
                        error_message();
                }
            }
        }
        
        else if (initial_selection == 2){
            complete_order(&order_queue, &bell_arr, &order_queue_index_to_out);
        }
        
        else if (initial_selection == 3){
            printf("서비스를 종료합니다.\n");
            
            free(bell_arr);
            free(order_queue);
            
            break;
        }
        
        else
            error_message();
    }
    
    return 0;
}

// Initialize bell arr
void initializing_bell_arr(int **arr){
    int bell_number = 101;
    
    for (int i = 0; i < MAX_ARR_SIZE; i++){
        (*arr)[i] = bell_number++;
    }
}

// Initialize all elements in order queue to 0
void initializing_order_queue(element **queue){
    for (int i = 0; i < MAX_QUEUE_SIZE; i++){
        (*queue)[i].key = 0;
    }
}

// Displaying initial menu
int initial_menu(void){
    int selection;
    printf("Ajou 푸드코트에 오신 것을 환영합니다. 원하는 기능을 선택해 주세요.\n");
    printf("1. 주문\n2. 서빙 완료\n3. 종료\n\n");
    printf("입력: ");
    
    scanf("%d", &selection);
    
    return selection;
}

// Check how many people are waiting
int check_waiting(int **bell_arr){
    int cnt = 0;
    for (int i = 0; i < MAX_ARR_SIZE; i++)
        if ((*bell_arr)[i] == 0)
            cnt++;
    
    return cnt;
}

// Display how many people are waiting and then asking if continue ordering
int ask_to_order(int number_of_waiting){
    int selection;
    
    printf("\n현재 대기자 수는 %d명입니다. 계속 주문하시겠습니까?\n", number_of_waiting);
    printf("1. 계속\n2. 취소\n\n");
    printf("입력: ");
    
    scanf("%d", &selection);
    
    return selection;
}

// Display the statement that asking to type a bell number
int bell_select(void){
    int bell_number;
    
    printf("진동벨 번호를 입력해주세요.\n\n");
    printf("입력: ");
    
    scanf("%d", &bell_number);
    
    return bell_number;
}

// Check whether typed bell number is valid or not
int valid_bell_number_or_not(int bell_number){
    if (bell_number == BELL_1 || bell_number == BELL_2 || bell_number == BELL_3 || bell_number == BELL_4 || bell_number == BELL_5)
        return TRUE;
    return FALSE;
}

// ADD function for queue
// Check whether bell number could be used or not and then add to queue
// When the queue_index exceeds queue size, change queue_index to 0
int add_order_q(element ** queue, int ** arr, int * queue_index, int target_number){
    int possible = FALSE;
    for (int i = 0; i < MAX_ARR_SIZE; i++)
        if ((*arr)[i] == target_number){
            (*arr)[i] = 0;
            possible = TRUE;
            break;
        }
    
    if (!possible)
        return FALSE;
    
    (*queue)[(*queue_index)++].key = target_number;
    
    if (*queue_index >= MAX_QUEUE_SIZE)
        *queue_index = 0;
    
    return TRUE;
}

// POP function for queue
// Check whether order is existed or not
// If exist, change 0 to bell number in bell number array, or display requested order is not existed and make possible variable False.
// And then check possible variable is true or not
// If possible variable is true, make target bell number 0 and increase queue index
// Before complete this function, check queue index exceed maximum queue size.
// If exceeded, make queue index 0, start index number of queue.
void complete_order(element **queue, int ** arr, int * queue_index){
    int completed_bell_number = (*queue)[*queue_index].key;
    int possible = TRUE;
    
    switch (completed_bell_number) {
        case 101:
            (*arr)[0] = 101;
            break;
            
        case 102:
            (*arr)[1] = 102;
            break;
            
        case 103:
            (*arr)[2] = 103;
            break;
            
        case 104:
            (*arr)[3] = 104;
            break;
        
        case 105:
            (*arr)[4] = 105;
            break;
            
        default:
            printf("\n주문 내역이 없습니다.\n");
            printf("************************\n\n");
            possible = FALSE;
            
    }
    
    if (possible){
        (*queue)[(*queue_index)++].key = 0;
        
        if ((*queue_index) >= MAX_QUEUE_SIZE)
            (*queue_index) = 0;
        
        printf("\n%d번 님의 주문을 처리 중입니다.\n", completed_bell_number);
        printf("************************\n\n");
    }
}

// Error message 1 - Using this function when user typed wrong number
void error_message(void){
    printf("\n************************\n");
    printf("잘못 누르셨습니다.\n");
    printf("************************\n\n");
}

// error message 2 - Using this function when usable bell_number is nothing
void impossible_to_order(void){
    printf("\n************************\n");
    printf("주문이 불가능합니다.\n");
    printf("감사합니다.\n");
    printf("************************\n\n");
}
