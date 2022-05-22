#include <stdio.h>     //режим с подсказкой: мол 1 подсказка на игру (воможно только против пк)
#include <string.h>    // Игрок 1 | Игрок 2  //нужно только ввести порядковый номер 
#include <stdlib.h>
#include <time.h>
                       
struct data {

    int n;                // Количество ходов
    char guess[5];        // Загаданное число //сделать отдельной переменной!!!
    char number[10][5];   // Запись попыток
    int k[10], b[10];     // Число коров и быков для каждой попытки
    int w;                // Наличие выйгрыша
};

//количество быков и коров
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

// проврерка ввода числа
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
    // 0 - проверка не выполнена
    // 1 - проверка выполнена
}

//проверка на ввод числа
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
    // 0 - проверка выполнена
    // 1 - проверка не выполнена
}

//ввод числа
void input(int i, struct data *pl){

    if (i != 0)
        printf ("Игрок %i\n", i); 
    printf ("Введите число: ");
    if (pl->n < 9)
        scanf ("%s", &pl->number[pl->n]);
    else scanf ("%s", &pl->number[9]);
    printf ("\n"); 

}

// вывод поля для одного игрока
void print_table_one(struct data *pl){

    int i, j = 1; //счетчик

    if (pl->n > 9){
        j = pl->n - 9;
    }

    #ifdef FINAL
        system("cls");
    #endif

    printf ("  |   Попытки\n");
    printf ("==|=============\n");

    for(i = 0; (i < pl->n) && (i < 10); i++){
        printf("%2i| %s  %iБ %iК\n", i+j, pl->number[i], pl->b[i], pl->k[i]);
    }

    printf("\n");
}

//вывод поля для двух игроков
void print_table(struct data *pl_1, struct data *pl_2){ 

    int i;
    int j = 1;

    #ifdef FINAL
        system("cls");
    #endif
    // Вывести очки 
    printf ("  |   Игрок 1   |   Игрок 2   |  \n");
    printf ("==|=============|=============|==\n");
    
    if (pl_1->n > 9){
        j = pl_1->n - 9;
    }
    //j - число в начале таблицы 
    //0-9 : j-pl_1->n+i+1    i+(j-pl_1->n+1) i+1 
    // >9 : i+pl_1->n-9      i+(pl_1->n-9)

    if (pl_1->n > pl_2->n){

        for(i = 0; (i < (pl_1->n - 1)) && (i < 9); i++){ //количество i = 9

            printf ("%2i| %s  %iБ %iК |", j+i, pl_1->number[i], pl_1->b[i], pl_1->k[i]);
            printf (" %s  %iБ %iК |%2i\n", pl_2->number[i], pl_2->b[i], pl_2->k[i], i+j);
        }
        // i = 9     номер i - 10
        printf ("%2i| %s  %iБ %iК |\n", pl_1->n, pl_1->number[i], pl_1->b[i], pl_1->k[i]);
    }

    else if (pl_1->n == pl_2->n){

        for(i = 0; (i < pl_1->n) && (i < 10); i++){//количество i = 10

            printf ("%2i| %s  %iБ %iК |", i+j, pl_1->number[i], pl_1->b[i], pl_1->k[i]);
            printf (" %s  %iБ %iК |%2i\n", pl_2->number[i], pl_2->b[i], pl_2->k[i], i+j);
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

// проверка рандома
int pr(int n, char *a){
    int i;
    for(i = 0; i < n; i++){
        if(a[i] == a[n])
            return 1;
    }
    return 0;
}

// одиночный режим
void game_one(){

    struct data player;

    int i; // счетчик
    int v = 1; // выбор

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

        printf("\nКомпьютер загадал число. Попробуйте отгадать!\n");

        player.n = 0;
        player.w = 0;

        int g; // индекс последнего слова в массиве

        while (!player.w){

            g = player.n;
            if (player.n > 9){
                perenos(&player);
                g = 9;
            }

            do{
                input(0, &player);
            }while(check(player.number[g]) || !(pr_num(&player.number[g][0])));
            // input(0, &player); //сделать универсальной 
            score_bk(&player, &player.guess[0]);
            print_table_one(&player); // сделать другой вывод поля
        }
    //принтануть число компа

        // printf("Поздравляем! Вы выиграли!\n\n");
        printf("Поздравляем! Вы выиграли!\n");
        printf("Количество ходов: %i \n\n", player.n);

        do {
            printf("Продолжить в этом режиме?\n1 - да, 0 - нет\n");
            fflush(stdin);
            scanf("%i", &v);
            // scanf("%i", &r);
        } while (v != 0 && v != 1);

        // printf("Продолжить в этом режиме?\n1 - да, 0 - нет\n");
        // scanf("%i", &v);
    }

}

// с другом
void game_friend(){

    struct data player_1;
    struct data player_2;

    int i; //счетчик
    int v = 1; //выбор

    while (v){ //пока "да"

        system("cls");
        printf("\n");
        do{
            printf("Игрок 1, введите загаданное число: ");
            scanf("%s", player_1.guess);
        } while (check(player_1.guess) || !(pr_num(&player_1.guess[0])));
        system("cls");
        printf("\n");
        do{
            printf("Игрок 2, введите загаданное число: ");
            scanf("%s", player_2.guess);
        } while (check(player_2.guess) || !(pr_num(&player_2.guess[0])));
        // scanf("%s", player_2.guess);
        system("cls");
        printf("\n");
        
        player_1.n = 0;
        player_2.n = 0;

        player_1.w = 0;
        player_2.w = 0;

        int g; // индекс последнего слова в массиве

        //пока один из игроков не наберет 4х быков

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

        // вывод победителя
        if ((player_1.w) && (player_2.w)){
            printf("Ничья! \nКоличество ходов: %i\n\n", player_1.n);
        }

        else if (player_1.w){
            printf("Игрок 1 выйграл! \nКоличество ходов: %i\n\n", player_1.n);
            printf("Число Игрока 1: ");
            for (i = 0; i < 4; i++){
                printf("%c", player_1.guess[i]);
            }
            printf("\n");
            printf("Число Игрока 2: ");
            for (i = 0; i < 4; i++){
                printf("%c", player_2.guess[i]);
            }
            printf("\n\n");
        }

        else if (player_2.w){
            printf("Игрок 2 выйграл! \nКоличество ходов: %i\n\n", player_2.n);

            printf("Число Игрока 1: ");
            for (i = 0; i < 4; i++){
                printf("%c", player_1.guess[i]);
            }
            printf("\n");

            printf("Число Игрока 2: ");
            for (i = 0; i < 4; i++){
                printf("%c", player_2.guess[i]);
            }
            printf("\n\n");
        }
        do {
            printf("Продолжить в этом режиме?\n1 - да, 0 - нет\n");
            // printf("Желаете сыграть еще?\n1 - да, 0 - нет\n");
            fflush(stdin);
            scanf("%i", &v);
            // scanf("%i", &r);
        } while (v != 0 && v != 1);
        // scanf("%i", &v);

        player_1.n = 0;
        player_2.n = 0;

    }


    // printf("Хотите сохраинть игру?\n1 - да, 0 - нет\n");
    // scanf("%i", &v);

    // if (v){
        
    //     FILE *fil;
    //     char name[20];
        
    //     printf("Введите имена игроков: ");
    //     fil = fopen("game.txt", "w");
    //     scanf("%s", &name);
    //     for (int i = 0; name[i] != '\0'; i++){
    //         fprintf(fil, "%c", name[i]);
    //     }
    //     fprintf(fil,"\n");
    // }

    //Хотите сохранить игру?

    //////ФАЙЛ/////
    //1 ВАРИАНТ//(сохранение счета)
    // 0 - нет записей, 1 - есть сохранение (1 строка)
    // счет: 1 и 2 игрока

    //2 ВАРИАНТ//(незапланированный выход)
    // 0 - нет записей, 1 - есть сохранение (1 строка)
    // счет, загаданные числа
}

void main(){

    int i; // счетчик
    int r, v = 1; // r - режим

    printf("Добрый день! Это игра \"Быки и коровы!\"\n");
    printf("Правила игры:\n");
    printf("игроки загадывают четырехзначное число без повтора цифр.\nПотом они задают друг другу другие такие четырехзначные числа, какие на их взгляд у противника.\nЕсли совпало место и число, то это бык (Б). Если совпало только число, то это корова (К).\n");
//// + справка: на экране будут показаны макс 10 предыдущих попыток
//// +?- Введите число или цифру 

    while (v == 1){

        // printf("\nВыберете режим:\n1 - одиночный\n2 - с другом\n");
        // scanf("%i", &r);
        do {
            // printf("\nДанные введены некорректно!\n");
            printf("\nВыберете режим:\n1 - одиночный\n2 - с другом\n");
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
            // printf("\nДанные введены некорректно!\n");
            // printf("\nВыберете режим:\n1 - одиночный\n2 - с другом\n");
            printf("Желаете сыграть еще?\n1 - да, 0 - нет\n");
            fflush(stdin);
            scanf("%i", &v);
            // scanf("%i", &r);
        } while (v != 0 && v != 1);
    }


    //Желаете сохранить результат? (если игра была c другом)
}