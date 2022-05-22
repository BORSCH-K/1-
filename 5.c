#include <stdio.h>     //режим с подсказкой: мол 1 подсказка на игру (воможно только против пк)
#include <string.h>    // Игрок 1 | Игрок 2  //нужно только ввести порядковый номер 
                       // _ _ _ _ | _ _ _ _
struct data {

    int n;                // Количество ходов
    char guess[5];        // Загаданное число //сделать отдельной переменной!!!
    char number[10][5];   // Запись попыток
    int k[10], b[10];     // Число коров и быков для каждой попытки

};

//количество быков и коров
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

//ввод числа
char input(int i, struct data *pl){ 

    printf ("Игрок %i\n", i); 
    printf ("Введите число: ");
    scanf ("%s", &pl->number[pl->n]);
    printf ("\n"); 

}

void print_table(struct data *pl_1, struct data *pl_2){ 

    int i;

    // printf("//// pl_1->n = %i; pl_2->n = %i\n", pl_1->n, pl_2->n);

    printf ("  |   Игрок 1   |   Игрок 2   |  \n");
    printf ("==|=============|=============|==\n");
    
    if (pl_1->n > pl_2->n ){

        for(i = 0; i < (pl_1->n-1); i++){ 

            printf ("%2i| %s  %iБ %iК |", i+1, pl_1->number[i], pl_1->b[i], pl_1->k[i]);
            printf (" %s  %iБ %iК |%2i\n", pl_2->number[i], pl_2->b[i], pl_2->k[i], i+1);
        }

        printf ("%2i| %s  %iБ %iК |\n", pl_1->n, pl_1->number[i], pl_1->b[i], pl_1->k[i]); 
    }

    else if (pl_1->n == pl_2->n){

        for(i = 0; i < pl_1->n; i++){

            printf ("%2i| %s  %iБ %iК |", i+1, pl_1->number[i], pl_1->b[i], pl_1->k[i]);
            printf (" %s  %iБ %iК |%2i\n", pl_2->number[i], pl_2->b[i], pl_2->k[i], i+1);
        }
    }
    
    printf("\n");
}

void main(){

    struct data player_1;
    struct data player_2;

    int i;

    printf("Добрый день! Это игра \"Быки и коровы!\"\n");
    printf("Правила игры:\n");
    printf("игроки загадывают четырехзначное число без повтора цифр.\nПотом они задают друг другу другие такие четырехзначные числа, какие на их взгляд у противника.\nЕсли совпало место и число, то это бык (Б). Если совпало только число, то это корова (К).\n");
//// + справка: на экране будут показаны макс 10 предыдущих попыток
//// +? Введите число или цифру 

    printf("Игрок 1, введите загадоное число: ");
    scanf("%s", player_1.guess);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("Игрок 2, введите загадоное число: ");
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
        printf("Ничья! \nКоличество ходов: %i\n", player_1.n);
    }

    else if (player_1.b [player_1.n - 1] == 4){
        printf("Игрок 1 выйграл! \nКоличество ходов: %i\n", player_1.n);
    }

    else if (player_2.b [player_2.n - 1] == 4){
        printf("Игрок 2 выйграл! \nКоличество ходов: %i\n", player_2.n);
    }

}