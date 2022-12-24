#include <stdio.h>     
#include <string.h>   
#include <stdlib.h>
#include <time.h>

// Данные для одного игрока
struct data {

    int n;                // Количество ходов
    char guess[5];        // Загаданное число //сделать отдельной переменной!!!
    char number[10][5];   // Запись попыток
    int k[10], b[10];     // Число коров и быков для каждой попытки
    int w;                // Наличие выигрыша
};

//количество быков и коров
void score_bk(int a, int n, struct data *pl, char *guess){

    int i, j;
    if (a){
        if (pl->n < 9) n = pl->n;
        else n = 9;
    }

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
    if (a) pl->n++;

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
                return 0;
            } 
        }
    }
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
}

// вывод поля для одного игрока
void print_table_one(struct data *pl){

    int i, j = 1; //счетчики

    if (pl->n > 9){
        j = pl->n - 9;
    }

    system("cls");

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

    system("cls");

    printf ("  |   Игрок 1   |   Игрок 2   |  \n");
    printf ("==|=============|=============|==\n");
    
    if (pl_1->n > 9){
        j = pl_1->n - 9;
    }

    if (pl_1->n > pl_2->n){

        for(i = 0; (i < (pl_1->n - 1)) && (i < 9); i++){ 

            printf ("%2i| %s  %iБ %iК |", j+i, pl_1->number[i], pl_1->b[i], pl_1->k[i]);
            printf (" %s  %iБ %iК |%2i\n", pl_2->number[i], pl_2->b[i], pl_2->k[i], i+j);
        }
        printf ("%2i| %s  %iБ %iК |\n", pl_1->n, pl_1->number[i], pl_1->b[i], pl_1->k[i]);
    }

    else if (pl_1->n == pl_2->n){

        for(i = 0; (i < pl_1->n) && (i < 10); i++){

            printf ("%2i| %s  %iБ %iК |", i+j, pl_1->number[i], pl_1->b[i], pl_1->k[i]);
            printf (" %s  %iБ %iК |%2i\n", pl_2->number[i], pl_2->b[i], pl_2->k[i], i+j);
        }
    }
    
    printf("\n");
}

void save(struct data *pl_1, struct data *pl_2){

    FILE *fil;
    fil = fopen("game.txt", "w");

    fprintf(fil, "%i\n", pl_1->n);
    fprintf(fil, "%s\n", pl_1->guess);

    for (int i = 0; i < pl_1->n && i < 10; i++){
        fprintf(fil, "%s ", pl_1->number[i]);
    }
    fprintf(fil, "\n");

    fprintf(fil, "%i\n", pl_2->n);
    fprintf(fil, "%s\n", pl_2->guess);

    for (int i = 0; i < pl_2->n && i < 10; i++){
        fprintf(fil, "%s ", pl_2->number[i]);
    }
    fclose(fil);
}

void perenos(struct data *pl){
    
    for (int i = 0; i < 9; i++){

        for (int j = 0; j < 4; j++){
            pl->number[i][j] = pl->number[i+1][j];
        }

        pl->k[i] = pl->k[i+1];
        pl->b[i] = pl->b[i+1];
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

void old_game(struct data *pl_1, struct data *pl_2){

    FILE *f;
    f = fopen("game.txt", "r");

    int i;

    fscanf(f, "%d\n", &pl_1->n);
    fscanf(f, "%s\n", &pl_1->guess);

    for (i = 0; i < pl_1->n && i < 10; i++)
        fscanf(f, "%s", &pl_1->number[i]);
    
    fscanf(f, "%d\n", &pl_2->n);
    fscanf(f, "%s\n", &pl_2->guess);

    for (i = 0; i < pl_2->n && i < 10; i++)
        fscanf(f, "%s", &pl_2->number[i]);

    for (i = 0; i < pl_1->n && i < 10; i++){
        score_bk(0, i, pl_1, pl_2->guess);
    }
    for (i = 0; i < pl_2->n && i < 10; i++){
        score_bk(0, i, pl_2, pl_1->guess);
    }
    fclose(f);
}

// одиночный режим
void game_one(){

    struct data player;

    int i; // счетчик
    int v = 1; // выбор

    while (v){

        srand(time(NULL));
        
        for (i = 0; i < 4; i++){
            player.guess[i] = '0' + rand()%10;
            do{
                player.guess[i] = '0' + rand()%10;
            } while (pr(i, &player.guess[0]));
        }

        for (i = 0; i < 4; i++){ // вывод числа компа
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

            input(0, &player);
            while(check(player.number[g]) || !(pr_num(&player.number[g][0]))){
                printf("Данные введены некорректно!\n");
                input(0, &player);
            }
            score_bk(1, player.n, &player, &player.guess[0]);
            print_table_one(&player); // сделать другой вывод поля
        }

        printf("Поздравляем! Вы выиграли!\n");
        printf("Количество ходов: %i \n\n", player.n);

        printf("Продолжить в этом режиме?\n1 - да, 0 - нет\n");
        scanf("%i", &v);
        while (v != 0 && v != 1){
            printf("Данные введены некорректно!\n");
            printf("Продолжить в этом режиме?\n1 - да, 0 - нет\n");
            fflush(stdin);
            scanf("%i", &v);
        }
    }
}

// с другом
void game_friend(int ex){

    struct data player_1;
    struct data player_2;

    int i; //счетчик
    int v = 1; //выбор
    int g; // индекс последнего слова в массиве

    while (v){ //пока "да"

        player_1.n = 0;
        player_2.n = 0;

        player_1.w = 0;
        player_2.w = 0;

        if (ex){
            old_game(&player_1, &player_2);
            print_table(&player_1, &player_2);
            ex = 0;
            if (player_1.n > player_2.n){
                g = player_2.n;
                if (player_2.n > 9)
                    g = 9;

                input(2, &player_2);
                while(check(player_2.number[g]) || !(pr_num(&player_2.number[g][0]))){
                    printf("Данные введены некорректно!\n");
                    input(2, &player_2);
                }
                score_bk(0, player_2.n, &player_2, &player_1.guess[0]);                 
                player_2.n++;
                
                print_table(&player_1, &player_2);
                save(&player_1, &player_2);
            }
        }
        else{
            system("cls");
            printf("\n");
            printf("Игрок 1, введите загаданное число: ");
            scanf("%s", player_1.guess);
            while (check(player_1.guess) || !(pr_num(&player_1.guess[0]))){
                printf("Данные введены некорректно!\n");
                printf("Игрок 1, введите загаданное число: ");
                fflush(stdin);
                scanf("%s", player_1.guess);
            }
            system("cls");
            printf("\n");

            printf("Игрок 2, введите загаданное число: ");
            scanf("%s", player_2.guess);
            while (check(player_2.guess) || !(pr_num(&player_2.guess[0]))){
                printf("Данные введены некорректно!\n");
                printf("Игрок 2, введите загаданное число: ");
                fflush(stdin);
                scanf("%s", player_2.guess);
            }
            system("cls");
            printf("\n");
        }

        //пока один из игроков не наберет 4х быков
        while ((!player_1.w) && (!player_2.w)){

            g = player_1.n;

            if (player_1.n > 9){
                perenos(&player_1);
                perenos(&player_2);
                g = 9;
            }
            //____1____//
            input(1, &player_1);
            while(check(player_1.number[g]) || !(pr_num(&player_1.number[g][0]))){
                printf("Данные введены некорректно!\n");
                input(1, &player_1);
            }
            score_bk(1, player_1.n, &player_1, &player_2.guess[0]);
            print_table(&player_1, &player_2);

            save(&player_1, &player_2);
            
            //____2____//
            input(2, &player_2);
            while(check(player_2.number[g]) || !(pr_num(&player_2.number[g][0]))){
                printf("Данные введены некорректно!\n");
                input(2, &player_2);
            }
            score_bk(1, player_2.n, &player_2, &player_1.guess[0]);
            print_table(&player_1, &player_2);

            save(&player_1, &player_2);
        }

        // вывод победителя
        if ((player_1.w) && (player_2.w)){
            printf("Ничья! \nКоличество ходов: %i\n\n", player_1.n);
            printf("Числа Игроков: ");
            for (i = 0; i < 4; i++){
                printf("%c", player_1.guess[i]);
            }
            printf("\n");
            // remove("game.txt");
        }

        else if (player_1.w){
            printf("Игрок 1 выиграл! \nКоличество ходов: %i\n\n", player_1.n);
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
            // remove("game.txt");
        }

        else if (player_2.w){
            printf("Игрок 2 выиграл! \nКоличество ходов: %i\n\n", player_2.n);

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
        remove("game.txt");
        printf("Продолжить в этом режиме?\n1 - да, 0 - нет\n");
        scanf("%i", &v);
        while (v != 0 && v != 1){
            printf("Продолжить в этом режиме?\n1 - да, 0 - нет\n");
            fflush(stdin);
            scanf("%i", &v);
        }

        player_1.n = 0;
        player_2.n = 0;

    }
}

void main(){

    int i; // счетчик
    int r, v = 1; // r - режим

    printf("Добрый день! Это игра \"Быки и коровы!\"\n");
    printf("Правила игры:\n");
    printf("игроки загадывают четырехзначное число без повтора цифр.\nПотом они задают друг другу другие такие четырехзначные числа, какие на их взгляд у противника.\nЕсли совпало место и число, то это бык (Б). Если совпало только число, то это корова (К).\n");

    FILE *f;
    f = fopen("game.txt", "r");

    while (v == 1){

        if (f){
            fclose(f);

            printf("\nВыберете режим:\n0 - Продолжить\n1 - одиночный\n2 - с другом\n");
            scanf("%i", &r);

            while (r != 1 && r != 2 && r != 0){
                printf("Данные введены некорректно!\n");
                printf("Выберете режим:\n0 - Продолжить\n1 - одиночный\n2 - с другом\n");
                fflush(stdin);
                scanf("%i", &r);
            }
        }
        else{

            printf("\nВыберете режим:\n1 - одиночный\n2 - с другом\n");
            scanf("%i", &r);

            while (r != 1 && r != 2){
                printf("Данные введены некорректно!\n");
                printf("Выберете режим:\n1 - одиночный\n2 - с другом\n");
                fflush(stdin);
                scanf("%i", &r);
            }
        }

        if (r == 1){
            game_one();
        }

        else if (r == 2){
            game_friend(0);
        }

        else if (r == 0){
            game_friend(1);
        }

        printf("Желаете сыграть еще?\n1 - да, 0 - нет\n");
        scanf("%i", &v);
        while (v != 0 && v != 1){
            printf("Данные введены некорректно!\n");
            printf("Желаете сыграть еще?\n1 - да, 0 - нет\n");
            fflush(stdin);
            scanf("%i", &v);
        }
    }
}
