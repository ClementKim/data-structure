#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct node * nodeptr;
typedef struct node {
    int vertex;
    int weight;
    int mark;
    nodeptr link;
} node;

int * visited;

nodeptr adjList = NULL;
nodeptr avail = NULL;
int front, rear;
int number_of_buildings;
int previous_number_of_builidings;
int total_cost;
int * queue;

nodeptr getNode(void);
void retNode(nodeptr);
void is_possible(int);
void bfs(int);
void dfs(int);
void prim(int);
void addq(int);
int popq(void);
void free_adjList(void);

int main(void){
    int * building_arr = malloc(100 * sizeof(int));
    int building_arr_idx = 0;

    int * tunnel_info = malloc(3 * sizeof(int));
    int tunnel_info_idx = 0;

    char temp_number[4] = {0};
    int temp_number_idx = 0;

    int flag1 = FALSE;
    int flag2 = FALSE; // 통로를 구축하는 while문을 순회하면서 언제 break할지 결정하는 flag
    int flag3 = FALSE; // 통로를 구축하는데 있어 중복된 정보가 있는지 확인하는 flag
    int flag4 = FALSE; // 통로를 구축하는데 있어 중복된 정보가 있는지 확인하는 flag
    int flag5 = TRUE;

    int possible = TRUE;

    char temp_building_arr[200] = {0};
    char tunnel[20] = {0};

    nodeptr temp = NULL;

    printf("아주대학교 지하 통로 구축 서비스\n\n");

    while (TRUE){
        printf("건물 수를 입력해주세요\n\n");

        scanf("%d", &number_of_buildings);
        getchar();

        if (number_of_buildings == 0){
            printf("\n서비스를 종료합니다\n\n");
            free(building_arr);
            free(tunnel_info);
            free(visited);
            free(queue);
            return 0;
        }

        else if (number_of_buildings > 20)
            printf("\n입력한 건물 수가 제한을 초과합니다\n\n");

        else if (number_of_buildings < 0)
            printf("\n입력한 건물 수는 존재하지 않는 값입니다\n\n");

        else {
            printf("\n건물 번호를 입력해주세요\n\n");

            fgets(temp_building_arr, 200, stdin);

            printf("\n");

            for (int i = 0; i < strlen(temp_building_arr); i++) {
                if (temp_building_arr[i] == ' ') {
                    building_arr[building_arr_idx++] = atoi(temp_number);
                    temp_number_idx = 0;
                    memset(temp_number, 0, 2 * sizeof(char));
                } else if (temp_building_arr[i] == '\n') {
                    building_arr[building_arr_idx++] = atoi(temp_number);

                    if (building_arr_idx == number_of_buildings)
                        for (int j = 0; j < number_of_buildings; j++) {
                            if (building_arr[j] > 49) {
                                printf("입력한 건물 번호 중 제한 값을 초과하는 값이 존재합니다\n\n");
                                flag1 = FALSE;
                                break;
                            } else if (building_arr[j] < 1) {
                                printf("입력한 건물 번호 중 제한 값 미만인 값이 존재합니다\n\n");
                                flag1 = FALSE;
                                break;
                            } else
                                flag1 = TRUE;
                        }

                    else {
                        if (number_of_buildings > building_arr_idx)
                            printf("제시된 건물 수보다 건물의 개수가 더 적습니다\n\n");
                        else
                            printf("제시된 건물 수보다 건물의 개수가 더 많습니다\n\n");

                        memset(building_arr, 0, 100 * sizeof(int));
                    }

                    temp_number_idx = 0;
                    building_arr_idx = 0;
                    memset(temp_number, 0, 2 * sizeof(char));
                    memset(temp_building_arr, 0, 200 * sizeof(char));
                } else
                    temp_number[temp_number_idx++] = temp_building_arr[i];
            }

            if (flag1) {
                adjList = (nodeptr) malloc(number_of_buildings * sizeof(node));
                for (int i = 0; i < number_of_buildings; i++) {
                    temp = getNode();

                    temp->vertex = building_arr[i];
                    temp->weight = 0;
                    temp->mark = FALSE;
                    temp->link = NULL;

                    adjList[i] = *temp;
                }

                printf("건물 간 통로 구축 정보를 입력하세요\n\n");

                while (TRUE) {
                    fgets(tunnel, 20, stdin);

                    for (int i = 0; i < strlen(tunnel); i++) {
                        if (tunnel[0] == '.') {
                            flag2 = TRUE;
                            memset(tunnel_info, 0, 3 * sizeof(int));
                            memset(temp_number, 0, 4 * sizeof(char));
                            memset(tunnel, 0, 20 * sizeof(char));
                            break;

                        } else if (tunnel[i] == ' ') {
                            tunnel_info[tunnel_info_idx++] = atoi(temp_number);
                            temp_number_idx = 0;
                            memset(temp_number, 0, 4 * sizeof(char));

                        } else if (tunnel[i] == '\n') {
                            tunnel_info[tunnel_info_idx++] = atoi(temp_number);

                            if (tunnel_info[0] < 1 || tunnel_info[0] > 49 || tunnel_info[1] < 1 ||
                                tunnel_info[1] > 49) {
                                printf("잘못된 건물 번호가 존재합니다\n\n");
                                tunnel_info_idx = 0;
                                temp_number_idx = 0;
                                memset(tunnel_info, 0, 3 * sizeof(int));
                                memset(temp_number, 0, 4 * sizeof(char));
                                memset(tunnel, 0, 20 * sizeof(char));
                                break;
                            }

                            for (int j = 0; j < number_of_buildings; j++) {
                                if (adjList[j].vertex == tunnel_info[0]) {
                                    flag3 = TRUE;
                                }

                                else if (adjList[j].vertex == tunnel_info[1]) {
                                    flag4 = TRUE;
                                }

                                if (flag3 && flag4)
                                    break;
                            }

                            if (flag3 && flag4) {
                                for (int j = 0; j < number_of_buildings; j++) {
                                    if (adjList[j].vertex == tunnel_info[0]) {
                                        for (nodeptr node = adjList[j].link; node; node = node->link)
                                            if (node->vertex == tunnel_info[1]) {
                                                printf("중복된 정보입니다\n\n");
                                                flag5 = FALSE;
                                                break;
                                            }
                                    } else if (adjList[j].vertex == tunnel_info[1]) {
                                        for (nodeptr node = adjList[j].link; node; node = node->link)
                                                if (node->vertex == tunnel_info[0]) {
                                                    printf("중복된 정보입니다\n\n");
                                                    flag5 = FALSE;
                                                    break;
                                                }
                                    }

                                    if (!flag5)
                                        break;
                                }

                                if (flag5)
                                    for (int j = 0; j < number_of_buildings; j++) {
                                        if (adjList[j].vertex == tunnel_info[0]) {
                                            for (nodeptr node = &adjList[j]; node; node = node->link) {
                                                if (!(node->link)) {
                                                    node->link = getNode();
                                                    node->link->vertex = tunnel_info[1];
                                                    node->link->weight = tunnel_info[2];
                                                    node->link->mark = FALSE;
                                                    node->link->link = NULL;
                                                    break;
                                                }
                                            }

                                        } else if (adjList[j].vertex == tunnel_info[1]) {
                                            for (nodeptr node = &adjList[j]; node; node = node->link) {
                                                if (!(node->link)) {
                                                    node->link = getNode();
                                                    node->link->vertex = tunnel_info[0];
                                                    node->link->weight = tunnel_info[2];
                                                    node->link->mark = FALSE;
                                                    node->link->link = NULL;
                                                    break;
                                                }
                                            }
                                        }
                                    }

                                else
                                    flag5 = TRUE;

                                flag3 = flag4 = FALSE;

                                tunnel_info_idx = 0;
                                temp_number_idx = 0;
                                memset(tunnel_info, 0, 3 * sizeof(int));
                                memset(temp_number, 0, 4 * sizeof(char));
                                memset(tunnel, 0, 20 * sizeof(char));

                            } else {
                                printf("건물이 잘못 입력되었습니다\n\n");
                                tunnel_info_idx = 0;
                                temp_number_idx = 0;
                                memset(tunnel_info, 0, 3 * sizeof(int));
                                memset(temp_number, 0, 4 * sizeof(char));
                                memset(tunnel, 0, 20 * sizeof(char));
                                flag3 = flag4 = FALSE;
                                break;
                            }
                        } else if (tunnel[i] == ',')
                            continue;

                        else
                            temp_number[temp_number_idx++] = tunnel[i];
                    }

                    if (flag2)
                        break;
                }

                // visited arr
                visited = malloc(number_of_buildings * sizeof(int));

                // Checking whether all buildings are connected or not
                is_possible(0);

                for (int i = 0; i < number_of_buildings; i++)
                    if (!visited[i]) {
                        possible = FALSE;
                    }

                if (possible)
                    printf("성공적인 계획입니다\n\n");
                else
                    printf("전체 건물들을 연결할 수 없습니다\n\n");


                // dfs
                memset(visited, 0, number_of_buildings * sizeof(int));
                printf("dfs: (");
                dfs(adjList[0].vertex);
                printf(")");

                for (int i = 0; i < number_of_buildings; i++)
                    if (!visited[i]) {
                        printf(", (");
                        dfs(adjList[i].vertex);
                        printf(")");
                    }

                printf("\n\n");

                // bfs
                queue = malloc(number_of_buildings * sizeof(int));
                memset(visited, 0, number_of_buildings * sizeof(int));
                printf("bfs: (");
                bfs(adjList[0].vertex);

                for (int i = 0; i < number_of_buildings; i++) {
                    if (!visited[i]) {
                        printf(", (");
                        bfs(adjList[i].vertex);
                    }
                }

                printf("\n\n");

                // prim
                memset(visited, 0, number_of_buildings * sizeof(int));
                total_cost = 0;
                printf("Prim: (");
                prim(adjList[0].vertex);

                printf("), %d\n\n", total_cost);

                // Initialization
                building_arr_idx = 0;
                temp_number_idx = 0;

                free_adjList();

                flag1 = FALSE;
                flag2 = FALSE;
                flag3 = FALSE;
                flag4 = FALSE;
                flag5 = TRUE;
                possible = TRUE;

                // Set previous_number_of_buildings
                previous_number_of_builidings = number_of_buildings;
            }
        }

    }
}

nodeptr getNode(void){
    nodeptr temp_node = NULL;

    if (avail){
        temp_node = avail;
        avail = avail->link;
    }

    else
        temp_node = (nodeptr)malloc(sizeof(node));

    return temp_node;
}

void retNode(nodeptr temp_node){
    temp_node->link = avail;
}

void is_possible(int v){
    nodeptr node;

    visited[v] = TRUE;

    avail = &adjList[v];

    while (avail){
        node = getNode();

        for (int i = 0; i < number_of_buildings; i++)
            if (adjList[i].vertex == node->vertex){
                if (!(visited[i])){
                    is_possible((i));
                    break;
                }

                else
                    break;
            }
    }
}

void dfs(int building_number){
    int v;
    nodeptr w;

    for (v = 0; v < number_of_buildings; v++)
        if (adjList[v].vertex == building_number)
            break;

    visited[v] = TRUE;
    printf("%d", adjList[v].vertex);
    for (w = &adjList[v]; w; w = w->link)
        for (int i = 0; i < number_of_buildings; i++)
            if (adjList[i].vertex == w->vertex) {
                if (!(visited[i])) {
                    printf(" ");
                    dfs(adjList[i].vertex);
                    break;
                }

                else
                    break;
            }
}

void bfs(int building_number){
    int v;
    nodeptr w;
    front = rear = 0;

    for (v = 0; v < number_of_buildings; v++)
        if (adjList[v].vertex == building_number)
            break;

    printf("%d", adjList[v].vertex);

    addq(v);
    visited[v] = TRUE;

    do{
        v = popq();
        for (w = &adjList[v]; w; w = w->link)
            for (int i = 0; i < number_of_buildings; i++){
                if (adjList[i].vertex == w->vertex){
                    if (!visited[i]) {
                        printf(" %d", w->vertex);
                        addq(i);
                        visited[i] = TRUE;
                        break;
                    }

                    else
                        break;
                }
            }
    } while (front != number_of_buildings);
    printf(")");
}

void prim(int building_number){
    int v;
    int flag = FALSE;
    int is_sub = TRUE;
    int min_weight;
    nodeptr w;
    nodeptr start;
    nodeptr end;

    for (v = 0; v < number_of_buildings; v++)
        if (adjList[v].vertex == building_number)
            break;

    visited[v] = TRUE;

    while (!flag) {
        flag = TRUE;
        for (int i = 0; i < number_of_buildings; i++)
            if (!visited[i]) {
                flag = FALSE;
                break;
            }

        min_weight = 2000;
        end = NULL;
        for (int i = 0; i < number_of_buildings; i++) {
            if (visited[i]) {
                for (w = &adjList[i]; w; w = w->link)
                    if (w->weight != 0 && (w->weight < min_weight) && !(w->mark)) {
                        for (int j = 0; j < number_of_buildings; j++) {
                            if (adjList[j].vertex == w->vertex && !(adjList[j].mark)) {
                                min_weight = w->weight;
                                start = &adjList[i];
                                end = w;
                                is_sub = FALSE;
                            }
                        }
                    }
            }
        }

        if (end && start) {
            printf("(%d %d)", start->vertex, end->vertex);
            end->mark = TRUE;
            total_cost += end->weight;

            for (int i = 0; i < number_of_buildings; i++) {
                if (adjList[i].vertex == end->vertex) {
                    visited[i] = TRUE;
                    adjList[i].mark = TRUE;
                }

                else if (adjList[i].vertex == start->vertex) {
                    visited[i] = TRUE;
                    adjList[i].mark = TRUE;
                }
            }

        }

        else if (!is_sub) {
            for (int i = 0; i < number_of_buildings; i++) {
                if (!visited[i])
                    prim(adjList[i].vertex);
            }
        }
    }
}

void addq(int i){
    queue[rear++] = i;
}

int popq(void){
    return queue[front++];
}

// Using retNode
void free_adjList(void){
    nodeptr temp_node;

    // Releasing Linked List memory connected with each index of adjList array
    for (int i = previous_number_of_builidings-1; i > -1; i--) {
        avail = NULL;
        temp_node = &adjList[i];
        retNode(temp_node);
    }

    avail = NULL;

    // Releasing adjList array memory
    free(adjList);
}