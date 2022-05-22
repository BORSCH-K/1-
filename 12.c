#include <stdio.h>     //०�� � ���᪠����: ��� 1 ���᪠��� �� ���� (������� ⮫쪮 ��⨢ ��)
#include <string.h>    // ��ப 1 | ��ப 2  //�㦭� ⮫쪮 ����� ���浪��� ����� 
#include <stdlib.h>
#include <time.h>
                       
struct data {

    int n;                // ������⢮ 室��
    char guess[5];        // ���������� �᫮ //ᤥ���� �⤥�쭮� ��६�����!!!
    char number[10][5];   // ������ ����⮪
    int k[10], b[10];     // ��᫮ ��஢ � �몮� ��� ������ ����⪨
    int w;                // ����稥 �멣���
};

//������⢮ �몮� � ��஢
void score_bk(struct data *pl, char *guess){

    int i, j;
    int n;
    if (pl->n < 9) n = pl->n;
    else n = 9;

    pl->b[n] = 0;
    pl->k[n] = 0;

    for (i = 0; i < 4; i++){
        for (j = 0; j < 4; j++){
            if (pl->number[n][i] == guess[j]){
                pl->k[n]++;
                if (i == j){
                    pl->b[n]++;
                }
            }
        }
    }  
    pl->k[n] -= pl->b[n];
    pl->n++;

    if (pl->b[n] == 4){
        pl->w = 1;
    }
}

// �஢�ઠ ����� �᫠
int pr_num(char *a){

    int i, j;

    for(i = 0; i < 3; i++){
        for(j = i+1; j < 4; j++){
            if (a[i] == a[j]){
                // printf("+++\n");
                // printf("%i %i\n", a[i], a[j]);
                return 0;
            } 
        }
    }
    // printf("---\n");
    return 1;
    // 0 - �஢�ઠ �� �믮�����
    // 1 - �஢�ઠ �믮�����
}

//�஢�ઠ �� ���� �᫠
int check(char a[]){
    int i, k = 0;
    if (strlen(a) != 4)
        return 1;
    for(i = 0; i < 4; i++){
        if (a[i] >= '0' && a[i] <= '9')
            k++;
    }
    if (k == 4)
        return 0;
    else
        return 1;
    // 0 - �஢�ઠ �믮�����
    // 1 - �஢�ઠ �� �믮�����
}

//���� �᫠
void input(int i, struct data *pl){

    if (i != 0)
        printf ("��ப %i\n", i); 
    printf ("������ �᫮: ");
    if (pl->n < 9)
        scanf ("%s", &pl->number[pl->n]);
    else scanf ("%s", &pl->number[9]);
    printf ("\n"); 

}

// �뢮� ���� ��� ������ ��ப�
void print_table_one(struct data *pl){

    int i, j = 1; //���稪

    if (pl->n > 9){
        j = pl->n - 9;
    }

    #ifdef FINAL
        system("cls");
    #endif

    printf ("  |   ����⪨\n");
    printf ("==|=============\n");

    for(i = 0; (i < pl->n) && (i < 10); i++){
        printf("%2i| %s  %i� %i�\n", i+j, pl->number[i], pl->b[i], pl->k[i]);
    }

    printf("\n");
}

//�뢮� ���� ��� ���� ��ப��
void print_table(struct data *pl_1, struct data *pl_2){ 

    int i;
    int j = 1;

    #ifdef FINAL
        system("cls");
    #endif
    // �뢥�� �窨 
    printf ("  |   ��ப 1   |   ��ப 2   |  \n");
    printf ("==|=============|=============|==\n");
    
    if (pl_1->n > 9){
        j = pl_1->n - 9;
    }
    //j - �᫮ � ��砫� ⠡���� 
    //0-9 : j-pl_1->n+i+1    i+(j-pl_1->n+1) i+1 
    // >9 : i+pl_1->n-9      i+(pl_1->n-9)

    if (pl_1->n > pl_2->n){

        for(i = 0; (i < (pl_1->n - 1)) && (i < 9); i++){ //������⢮ i = 9

            printf ("%2i| %s  %i� %i� |", j+i, pl_1->number[i], pl_1->b[i], pl_1->k[i]);
            printf (" %s  %i� %i� |%2i\n", pl_2->number[i], pl_2->b[i], pl_2->k[i], i+j);
        }
        // i = 9     ����� i - 10
        printf ("%2i| %s  %i� %i� |\n", pl_1->n, pl_1->number[i], pl_1->b[i], pl_1->k[i]);
    }

    else if (pl_1->n == pl_2->n){

        for(i = 0; (i < pl_1->n) && (i < 10); i++){//������⢮ i = 10

            printf ("%2i| %s  %i� %i� |", i+j, pl_1->number[i], pl_1->b[i], pl_1->k[i]);
            printf (" %s  %i� %i� |%2i\n", pl_2->number[i], pl_2->b[i], pl_2->k[i], i+j);
        }
    }
    
    printf("\n");
}

void perenos(struct data *pl){
    
    for (int i = 0; i < 9; i++){

        for (int j = 0; j < 4; j++){
            pl->number[i][j] = pl->number[i+1][j];
            // pl_2->number[i][j] = pl_2->number[i+1][j];
        }

        pl->k[i] = pl->k[i+1];
        // pl_2->k[i] = pl_2->k[i+1];

        pl->b[i] = pl->b[i+1];
        // pl_2->b[i] = pl_2->b[i+1];
    }
}

// �஢�ઠ ࠭����
int pr(int n, char *a){
    int i;
    for(i = 0; i < n; i++){
        if(a[i] == a[n])
            return 1;
    }
    return 0;
}

// ������� ०��
void game_one(){

    struct data player;

    int i; // ���稪
    int v = 1; // �롮�

    while (v){
        // char a[4], i;
        srand(time(NULL));
        
        for (i = 0; i < 4; i++){
            player.guess[i] = '0' + rand()%10;
            // printf("%i\n", a[i]);
            do{
                player.guess[i] = '0' + rand()%10;
                // printf("%c\n", player.guess[i]);
            } while (pr(i, &player.guess[0]));
            // printf("%i\n", rand()%10);
        }

        for (i = 0; i < 4; i++){
            printf("%c", player.guess[i]);
        }

        printf("\n�������� ������� �᫮. ���஡�� �⣠����!\n");

        player.n = 0;
        player.w = 0;

        int g; // ������ ��᫥����� ᫮�� � ���ᨢ�

        while (!player.w){

            g = player.n;
            if (player.n > 9){
                perenos(&player);
                g = 9;
            }

            do{
                input(0, &player);
            }while(check(player.number[g]) || !(pr_num(&player.number[g][0])));
            // input(0, &player); //ᤥ���� 㭨���ᠫ쭮� 
            score_bk(&player, &player.guess[0]);
            print_table_one(&player); // ᤥ���� ��㣮� �뢮� ����
        }
    //�ਭ⠭��� �᫮ �����

        // printf("����ࠢ�塞! �� �먣ࠫ�!\n\n");
        printf("����ࠢ�塞! �� �먣ࠫ�!\n");
        printf("������⢮ 室��: %i \n\n", player.n);

        do {
            printf("�த������ � �⮬ ०���?\n1 - ��, 0 - ���\n");
            fflush(stdin);
            scanf("%i", &v);
            // scanf("%i", &r);
        } while (v != 0 && v != 1);

        // printf("�த������ � �⮬ ०���?\n1 - ��, 0 - ���\n");
        // scanf("%i", &v);
    }

}

// � ��㣮�
void game_friend(){

    struct data player_1;
    struct data player_2;

    int i; //���稪
    int v = 1; //�롮�

    while (v){ //���� "��"

        system("cls");
        printf("\n");
        do{
            printf("��ப 1, ������ ���������� �᫮: ");
            scanf("%s", player_1.guess);
        } while (check(player_1.guess) || !(pr_num(&player_1.guess[0])));
        system("cls");
        printf("\n");
        do{
            printf("��ப 2, ������ ���������� �᫮: ");
            scanf("%s", player_2.guess);
        } while (check(player_2.guess) || !(pr_num(&player_2.guess[0])));
        // scanf("%s", player_2.guess);
        system("cls");
        printf("\n");
        
        player_1.n = 0;
        player_2.n = 0;

        player_1.w = 0;
        player_2.w = 0;

        int g; // ������ ��᫥����� ᫮�� � ���ᨢ�

        //���� ���� �� ��ப�� �� ������ 4� �몮�

        while ((!player_1.w) && (!player_2.w)){
        // while ((player_1.b [player_1.n - 1] != 4) && (player_2.b [player_2.n - 1] != 4)){

            g = player_1.n;

            if (player_1.n > 9){
                perenos(&player_1);
                perenos(&player_2);
                g = 9;
            }
            do{
                input(1, &player_1);
            }while(check(player_1.number[g]) || !(pr_num(&player_1.number[g][0])));
            score_bk(&player_1, &player_2.guess[0]);
            print_table(&player_1, &player_2);
            
            do{
                input(2, &player_2);
            }while(check(player_2.number[g]) || !(pr_num(&player_2.number[g][0])));
            score_bk(&player_2, &player_1.guess[0]);
            print_table(&player_1, &player_2);
           
        }

        // �뢮� ������⥫�
        if ((player_1.w) && (player_2.w)){
            printf("�����! \n������⢮ 室��: %i\n\n", player_1.n);
        }

        else if (player_1.w){
            printf("��ப 1 �멣ࠫ! \n������⢮ 室��: %i\n\n", player_1.n);
            printf("��᫮ ��ப� 1: ");
            for (i = 0; i < 4; i++){
                printf("%c", player_1.guess[i]);
            }
            printf("\n");
            printf("��᫮ ��ப� 2: ");
            for (i = 0; i < 4; i++){
                printf("%c", player_2.guess[i]);
            }
            printf("\n\n");
        }

        else if (player_2.w){
            printf("��ப 2 �멣ࠫ! \n������⢮ 室��: %i\n\n", player_2.n);

            printf("��᫮ ��ப� 1: ");
            for (i = 0; i < 4; i++){
                printf("%c", player_1.guess[i]);
            }
            printf("\n");

            printf("��᫮ ��ப� 2: ");
            for (i = 0; i < 4; i++){
                printf("%c", player_2.guess[i]);
            }
            printf("\n\n");
        }
        do {
            printf("�த������ � �⮬ ०���?\n1 - ��, 0 - ���\n");
            // printf("������ ����� ��?\n1 - ��, 0 - ���\n");
            fflush(stdin);
            scanf("%i", &v);
            // scanf("%i", &r);
        } while (v != 0 && v != 1);
        // scanf("%i", &v);

        player_1.n = 0;
        player_2.n = 0;

    }


    // printf("���� ��ࠨ��� ����?\n1 - ��, 0 - ���\n");
    // scanf("%i", &v);

    // if (v){
        
    //     FILE *fil;
    //     char name[20];
        
    //     printf("������ ����� ��ப��: ");
    //     fil = fopen("game.txt", "w");
    //     scanf("%s", &name);
    //     for (int i = 0; name[i] != '\0'; i++){
    //         fprintf(fil, "%c", name[i]);
    //     }
    //     fprintf(fil,"\n");
    // }

    //���� ��࠭��� ����?

    //////����/////
    //1 �������//(��࠭���� ���)
    // 0 - ��� ����ᥩ, 1 - ���� ��࠭���� (1 ��ப�)
    // ���: 1 � 2 ��ப�

    //2 �������//(���������஢���� ��室)
    // 0 - ��� ����ᥩ, 1 - ���� ��࠭���� (1 ��ப�)
    // ���, ��������� �᫠
}

void main(){

    int i; // ���稪
    int r, v = 1; // r - ०��

    printf("����� ����! �� ��� \"�모 � ��஢�!\"\n");
    printf("�ࠢ��� ����:\n");
    printf("��ப� �����뢠�� ����姭�筮� �᫮ ��� ����� ���.\n��⮬ ��� ������ ��� ���� ��㣨� ⠪�� ����姭��� �᫠, ����� �� �� ����� � ��⨢����.\n�᫨ ᮢ���� ���� � �᫮, � �� �� (�). �᫨ ᮢ���� ⮫쪮 �᫮, � �� ��஢� (�).\n");
//// + �ࠢ��: �� �࠭� ���� �������� ���� 10 �।���� ����⮪
//// +?- ������ �᫮ ��� ���� 

    while (v == 1){

        // printf("\n�롥�� ०��:\n1 - �������\n2 - � ��㣮�\n");
        // scanf("%i", &r);
        do {
            // printf("\n����� ������� �����४⭮!\n");
            printf("\n�롥�� ०��:\n1 - �������\n2 - � ��㣮�\n");
            fflush(stdin);
            scanf("%i", &r);
        } while (r != 1 && r != 2);

        if (r == 1){
            game_one();
        }

        if (r == 2){
            game_friend();
        }

        do {
            // printf("\n����� ������� �����४⭮!\n");
            // printf("\n�롥�� ०��:\n1 - �������\n2 - � ��㣮�\n");
            printf("������ ����� ��?\n1 - ��, 0 - ���\n");
            fflush(stdin);
            scanf("%i", &v);
            // scanf("%i", &r);
        } while (v != 0 && v != 1);
    }


    //������ ��࠭��� १����? (�᫨ ��� �뫠 c ��㣮�)
}