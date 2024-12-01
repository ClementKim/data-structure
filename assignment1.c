#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 100

typedef struct{
    char name[20]; // 이름
    char phone[MAX_SIZE]; // 전화번호
    char code; // 수강코드
    
    union {
        double record; // 수영 기록
        int score; // 골프 기록
        char spinal[5]; // 척추질환
    } addition; // 추가 정보
} customer;

int main(void){
    int idx = 0, swim_student = 0, golf_student = 0, yoga_student = 0;
    
    // 수영
    double swim_best_record = 9999.99, swim_avg_record = 0.0;
    char swim_best_student[20];
    
    // 골프
    int golf_lowest_score = 9999;
    double golf_avg_score = 0.0;
    char golf_lowest_student[20];
    
    // 요가
    int yoga_spinal_patient = 0;

    customer list[MAX_SIZE]; // 고객 리스트 선언
    
    while (idx != 100){
        scanf("%s", list[idx].name); // 이름 입력
        
        if (!(strcmp(list[idx].name, "end"))) // 만약 종료 키워드인 end가 입력된다면 종료
            break;
        
        scanf("%s %c", list[idx].phone, &list[idx].code); // 아니면 전화번호와 수강코드 입력
        
        switch (list[idx].code) {
            case 'S':
                scanf("%lf", &list[idx].addition.record); // 수영 기록 입력
                break;
                
            case 'G':
                scanf("%d", &list[idx].addition.score); // 골프 기록 입력
                break;
                
            case 'Y':
                scanf("%s", list[idx].addition.spinal); // 척추질환 유무 입력
                break;
        }
        
        idx++;
    }
    
    for (int i = 0; i < idx; i++){
        switch (list[i].code) {
            case 'S':
                swim_student++; // 수영 수강자 인원 추가
                swim_avg_record += list[i].addition.record; // 전체 수영 수강자 기록
                
                // 수강자의 기록이 더 좋은 기록이면 사전에 저장되어 있던 기록 변경
                if (list[i].addition.record < swim_best_record){
                    swim_best_record = list[i].addition.record; // 기록
                    strcpy(swim_best_student, list[i].name); // 이름
                }
                
                break;
                
            case 'G':
                golf_student++;
                golf_avg_score += list[i].addition.score; // 전체 골프 수강자 기록
                
                // 수강자의 기록이 더 좋은 기록이면 사전에 저장되어 있던 최고 기록 변경
                if (list[i].addition.score < golf_lowest_score){
                    golf_lowest_score = list[i].addition.score; // 기록
                    strcpy(golf_lowest_student, list[i].name); // 이름
                }
                
                break;
                
            case 'Y':
                yoga_student++; // 요가 수강자 인원 추가
                
                // 척추질환이 있으면 척추질환자 수 증가
                if (!(strcmp(list[i].addition.spinal, "TRUE")))
                    yoga_spinal_patient++;
                
                break;
        }
        
    }
    
    printf("수강생 인원: 골프 %d명, 수영 %d명, 요가 %d명\n", golf_student, swim_student, yoga_student);
    
    if (swim_student){
        printf("최고 수영 실력자: %s %.1lf초\n", swim_best_student, floor(swim_best_record * 10)/10); // 소수점 둘째 자리 이하 버림
        printf("수영 평균 기록: %.1lf초\n", floor(swim_avg_record/swim_student * 10)/10); // 소수점 둘째 자리 이하 버림
    }
    
    if (golf_student){
        printf("골프 최저타 기록 보유자: %s %d타\n", golf_lowest_student, golf_lowest_score);
        printf("골프 평균 타수: %d타\n", (int)(golf_avg_score/golf_student)); // 소수점 이하 버림
    }
    
    if (yoga_student){
        printf("요가 척추질환 보유자: %d명\n", yoga_spinal_patient);
    }
    
    return 0;
}
