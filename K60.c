#include <stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#define MAX_DAYS 100
#define PRODUCTS_COUNT 3

//BAN HANG - QUEUE
typedef struct Node{
    char Name[30];
    char Phone[15];
    int A;
    int B;
    int C;
    struct Node* next;
}Node;
Node* first, *last;

typedef struct TongSP{
    int Tong_A;
    int Tong_B;
    int Tong_C;
}TongSP;
TongSP SUM[1000];

Node* makeNode(char* name, char* phone){
    Node* tmp = (Node*)malloc(sizeof(Node));
    strcpy(tmp->Phone, phone);
    strcpy(tmp->Name, name);
    tmp->A = 0; tmp->B = 0; tmp->C = 0;
    tmp->next = NULL; 
    return tmp;
}

void Init(){
    first = NULL; 
    last = NULL;
}

int listEmpty(){
    return ((first == NULL) && (last == NULL));
}


void Push(char* name, char* phone){
    Node* tmp = makeNode(name, phone);
    if(listEmpty()){
        first = tmp; last = tmp;
    }else{
        last->next = tmp; last = tmp;
    }
}

Node* Pop(){
    if(listEmpty()){
        return NULL;
    }
    else{
        Node *p = first;
        first = first->next;
        return p;
        free(p);
    }
}

void InsertFirst(char *name, char *phone){
    Node *tmp = makeNode(name, phone);
    if(listEmpty()){
        first = tmp; last = tmp;
    }else{
        tmp->next = first; first = tmp;
    }
}

void processVIP(){
    char name[30], phone[15];
    printf("Hay nhap ten khach VIP: ");
    scanf("%s", name);
    printf("Hay nhap so dien thoai khach VIP: ");
    scanf("%s", phone);
    InsertFirst(name, phone);
    printf("Khach VIP da duoc them vao dau danh sach\n");
}

void printList(){
    for(Node* p = first; p != NULL; p = p->next){
         printf("%s %s\n",p->Name, p->Phone);
    }
}

void LoadFile(){
    FILE *f1 = fopen("danhsach.txt", "r");
    if(f1 == NULL){
        printf("Khong the mo file\n");
    }
    else{
        while (!feof(f1)){
            char name[30], phone[15];
            fscanf(f1, "%s %s", name, phone);
            Push(name, phone);
        } 
    }
    fclose(f1);
}

void Add_Customer(){
    char name[30], phone[15];
    printf("Hay nhap ten nguoi mua hang: ");
    scanf("%s", name);
    printf("Hay nhap SDT nguoi mua hang: ");
    scanf("%s", phone);
    phone[strlen(phone) - 1] = '\0';
    Push(name, phone);
}

void Sell(){
    Node *tmp = Pop();
    printf("Khach hang: %s %s. Ban muon mua bao nhieu sp loai A, B, C?: ",tmp->Name, tmp->Phone);
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    while(a < 0 || b < 0 || c < 0){
        printf("Loi! Hay nhap lai: ");
        scanf("%d %d %d", &a, &b, &c);
    }
    tmp->A = a; tmp->B = b; tmp->C = c;
    FILE *f2 = fopen("banhang.txt", "a");
    fprintf(f2, "\n%d %d %d",a, b, c);
    fclose(f2);
}

void Infor_1_day(){
    FILE *f3 = fopen("danhsach.txt", "w");
    FILE *f4 = fopen("banhang.txt", "a");
    for(Node *p = first; p != NULL; p = p->next){
        printf("%s %s\n", p->Name, p->Phone);
        fprintf(f3, "%s %s\n", p->Name, p->Phone);
    }
    fprintf(f4, "\n%d", -1);
    fclose(f3);
    fclose(f4);
}

void Total_sp(){
    FILE *file = fopen("banhang.txt", "r");
    int count = 0;
    while(!feof(file)){
        char s[100];
        if(fgets(s, 100, file) != NULL){
            if(strstr(s, "-1") == NULL){
                int a, b, c;
                if(sscanf(s, "%d %d %d", &a, &b, &c) == 3){
                    SUM[count].Tong_A += a;
                    SUM[count].Tong_B += b;
                    SUM[count].Tong_C += c;
                }
                else{
                    printf("Dong %d trong file khong hop le!\n", count+1);
                }
            }
            else{
                count++;
            }
        }
    }
    fclose(file);
    for(int i = 0; i < count; i++){
        printf("Ngay %d: San pham A ban duoc: %d, San pham B ban duoc: %d, San pham C ban duoc: %d; Tong so tien thu duoc la: %d trieu\n", i+1, SUM[i].Tong_A, SUM[i].Tong_B, SUM[i].Tong_C, 10*SUM[i].Tong_A + 50*SUM[i].Tong_B + 80* SUM[i].Tong_C);
    }
}

void Menu(){
    printf("\n------------------MENU-------------------\n");
    printf("|1) Doc file danhsach.txt               |\n");
    printf("|2) Them nguoi mua vao hang doi         |\n");
    printf("|3) Ban hang                            |\n");
    printf("|4) Ghi thong tin sau 1 ngay            |\n");
    printf("|5) Total                               |\n");
    printf("|6) Khach VIP                           |\n");
    printf("-----------------------------------------\n");
    printf("Moi ban chon chuc nang: ");
}

int main(){
    Init();
    while(1){
        Menu();
        int k;
        scanf("%d", &k);
        while (k < 1 || k > 6){
            printf("Ban hay chon lai chuc nang(1->6): ");
            scanf("%d", &k);
        }
        switch (k)
        {
        case 1:
            Init();
            LoadFile();
            printList();
            break;
        case 2:
            Add_Customer();
            break;
        case 3:
            Sell();
            break;
        case 4:
            Infor_1_day();
            break;
        case 5:
            for(int i = 0; i < 1000; i++){
                SUM[i].Tong_A = 0;
                SUM[i].Tong_B = 0;
                SUM[i].Tong_C = 0;
            }
            Total_sp();
            break;
        case 6:
            processVIP();
            break;
        default:
            break;
        }
    }
    return 0;
}
