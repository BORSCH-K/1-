#include <stdio.h>     //०�� � ���᪠����: ��� 1 ���᪠��� �� ���� (������� ⮫쪮 ��⨢ ��)
#include <string.h>    // ��ப 1 | ��ப 2  //�㦭� ⮫쪮 ����� ���浪��� ����� 
                       // _ _ _ _ | _ _ _ _
struct data {

    int n;                // ������⢮ 室��
    char guess[5];        // ���������� �᫮ //ᤥ���� �⤥�쭮� ��६�����!!!
    char number[10][5];   // ������ ����⮪
    int k[10], b[10];     // ��᫮ ��஢ � �몮� ��� ������ ����⪨

};

//������⢮ �몮� � ��஢
int score_bk(struct data *pl, char *guess){

    int i, j;

    pl->b[pl->n] = 0;
    pl->k[pl->n] = 0;

    for (i = 0; i < 4; i++){
        for (j = 0; j < 4; j++){
            if (pl->number[pl->n][i] == guess[j]){
                pl->k[pl->n]++;
                if (i == j){
                    pl->b[pl->n]++;
                }
            }
        }
    }  
    pl->k[pl->n] -= pl->b[pl->n];
    pl->n++;
}

//���� �᫠
char input(int i, struct data *pl){ 

    printf ("��ப %i\n", i); 
    printf ("������ �᫮: ");
    scanf ("%s", &pl->number[pl->n]);
    printf ("\n"); 

}

void print_table(struct data *pl_1, struct data *pl_2){ 

    int i;

    // printf("//// pl_1->n = %i; pl_2->n = %i\n", pl_1->n, pl_2->n);

    printf ("  |   ��ப 1   |   ��ப 2   |  \n");
    printf ("==|=============|=============|==\n");
    
    if (pl_1->n > pl_2->n ){

        for(i = 0; i < (pl_1->n-1); i++){ 

            printf ("%2i| %s  %i� %i� |", i+1, pl_1->number[i], pl_1->b[i], pl_1->k[i]);
            printf (" %s  %i� %i� |%2i\n", pl_2->number[i], pl_2->b[i], pl_2->k[i], i+1);
        }

        printf ("%2i| %s  %i� %i� |\n", pl_1->n, pl_1->number[i], pl_1->b[i], pl_1->k[i]); 
    }

    else if (pl_1->n == pl_2->n){

        for(i = 0; i < pl_1->n; i++){

            printf ("%2i| %s  %i� %i� |", i+1, pl_1->number[i], pl_1->b[i], pl_1->k[i]);
            printf (" %s  %i� %i� |%2i\n", pl_2->number[i], pl_2->b[i], pl_2->k[i], i+1);
        }
    }
    
    printf("\n");
}

void main(){

    struct data player_1;
    struct data player_2;

    int i;

    printf("����� ����! �� ��� \"�모 � ��஢�!\"\n");
    printf("�ࠢ��� ����:\n");
    printf("��ப� �����뢠�� ����姭�筮� �᫮ ��� ����� ���.\n��⮬ ��� ������ ��� ���� ��㣨� ⠪�� ����姭��� �᫠, ����� �� �� ����� � ��⨢����.\n�᫨ ᮢ���� ���� � �᫮, � �� �� (�). �᫨ ᮢ���� ⮫쪮 �᫮, � �� ��஢� (�).\n");
//// + �ࠢ��: �� �࠭� ���� �������� ���� 10 �।���� ����⮪
//// +? ������ �᫮ ��� ���� 

    printf("��ப 1, ������ ��������� �᫮: ");
    scanf("%s", player_1.guess);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("��ப 2, ������ ��������� �᫮: ");
    scanf("%s", player_2.guess);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    
    player_1.n = 0;
    player_2.n = 0;


    while ((player_1.b [player_1.n - 1] != 4) && (player_2.b [player_2.n - 1] != 4)){

        input(1, &player_1);
        score_bk(&player_1, &player_2.guess[0]);
        print_table(&player_1, &player_2);
        
        input(2, &player_2);
        score_bk(&player_2, &player_1.guess[0]);
        print_table(&player_1, &player_2);

    }

    if ((player_1.b [player_1.n - 1] == 4) && (player_2.b [player_2.n - 1] == 4)){
        printf("�����! \n������⢮ 室��: %i\n", player_1.n);
    }

    else if (player_1.b [player_1.n - 1] == 4){
        printf("��ப 1 �멣ࠫ! \n������⢮ 室��: %i\n", player_1.n);
    }

    else if (player_2.b [player_2.n - 1] == 4){
        printf("��ப 2 �멣ࠫ! \n������⢮ 室��: %i\n", player_2.n);
    }

}