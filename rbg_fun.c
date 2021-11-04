/*
1 - инициализация
2 - заполнение дельт
3 - сортировка по возрастанию дельт (так отбираем 5 лучших, здесь же проверка выхода)
4 - скрещивание (1-5=6, 2-4=7, 1-4=8, 2-5=9, 3^мутация^=10)
5 - снова этап 2 для нового поколения

нужно допилить процесс скрещивания
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

struct entity
{
    unsigned char r, g, b;
    unsigned delta;
};
typedef struct entity entity; //переименование типа для укорачивания записей

void check_malloc(void *pointer);//проверяет успешность выделения памяти

//получает целевое значение {R, G, B}, максимально допустимое отклонение наилучшего варианта, лимит итераций
void get_initaial_values(entity *target, unsigned char *max_delta, unsigned *iter_limit);

void init_1st_generation(entity *generation); //созданёт 10 особей {Ri, Gi, Bi}, где i[0; 9], R,G,B - rand(0, 255)

void compare_entities_with_target(entity *target, entity *current_generation) //заполняются соответсвующие отклонения от целевого значения
{
    unsigned char dr, dg, db;
    for(int i = 0; i < 10; i++)
    {
        dr = abs(target->r - (current_generation + i)->r);
        dg = abs(target->g - (current_generation + i)->g);
        db = abs(target->b - (current_generation + i)->b);
        (current_generation + i)->delta = dr + dg + db;
    }
}

void swap(entity *first, entity *second); //меняет местами два элемента массива структур - текущего поколения

void print_last_generation(entity *generation); //вывод финального поколения


//сходится плохо и мутация не даёт ничего,  нужно продумать процесс скрещивания
void selection(entity *generation, entity *target, unsigned char max_delta, unsigned iter_limit)
{
    static unsigned iter_counter;
    iter_counter++;
    for(int i = 0; i < 10; i++)
        for(int j = 1; j < 10; j++)
            if((generation + i)->delta >= (generation + j)->delta)
                swap(generation + i, generation + j);
    //max_delta = 0 значит необходимо достигнуть такого же точно значения как целевое
    //следовательно сумма дельт каждого значения RGB (поле delta) должно быть равно 0
    //либо количество итераций максимальное
    if((!max_delta && !generation->delta) || (iter_counter == iter_limit))
    {
        printf("\nLast generation was gotten by %u iterations\n\a", iter_counter);
        print_last_generation(generation);
        printf("Target value {%hhu %hhu %hhu}", target->r, target->g, target->b);
        exit(EXIT_SUCCESS);
    }
    else //случай если разрешили, чтобы подобранное значение не в точности совпадало с целевым (max_delta > 0)
    {
        //проверяем максимальное количество итераций или отличие лучшего подобранного от целевого в дельта диапозоне
        if((generation->delta <= max_delta) || (iter_counter == iter_limit))
        {
            printf("\nLast generation was gotten by %u iterations\n\a", iter_counter);
            print_last_generation(generation);
            printf("Target value {%hhu %hhu %hhu}", target->r, target->g, target->b);
            exit(EXIT_SUCCESS);
        }
    }
}

//допилить скрещивание
void create_descendant(entity *parent_1, entity *parent_2, entity *descendant)
{
    static char flag = 0;
    flag = !flag;
    if(flag) //для выбора 1 раз + потом - и так всё время чередуются
    {
        descendant->r = parent_1->r + abs(parent_1->r - parent_2->r);
        descendant->g = parent_1->g - abs(parent_1->g - parent_2->g);
        descendant->b = parent_1->b + abs(parent_1->b - parent_2->b);
    }
    else
    {
        descendant->r = parent_1->r - abs(parent_1->r - parent_2->r);
        descendant->g = parent_1->g + abs(parent_1->g - parent_2->g);
        descendant->b = parent_1->b - abs(parent_1->b - parent_2->b);
    }
}



void mutation(entity *mutant)
{
    mutant->r = (unsigned char)(255.0f * rand() / (RAND_MAX + 1.0f));
    mutant->g = (unsigned char)(255.0f * rand() / (RAND_MAX + 1.0f));
    mutant->b = (unsigned char)(255.0f * rand() / (RAND_MAX + 1.0f));
}


//кроссовер доработать
void crossover(entity *generation)
{
    create_descendant(generation, generation + 4, generation + 5);
    create_descendant(generation, generation + 3, generation + 6);
    create_descendant(generation + 1, generation + 4, generation + 7);
    create_descendant(generation + 1, generation + 3, generation + 8);
    mutation(generation + 3);
    mutation(generation + 9);
}


int main()
{
    entity target, *generation = (entity *)malloc(sizeof(entity)*10); //популяция будет из 10 особей всегда
    check_malloc(generation);
    unsigned char max_delta; //максимально допустипое отклоение по сумме дельт значения каждого цвета (r, g, b)
    unsigned iter_limit; //лимит итераций

    get_initaial_values(&target, &max_delta, &iter_limit); //получение целового значения {R, G, B} макс отклонения (max_delta), предела итераций
    srand(time(NULL));
    init_1st_generation(generation); //создание 1-го поколения, со случайнмы значениями
    while(1)
    {
        //каждая особь сравнивается с целевым значением (получаем Dr, Dg, Db и основную дельту = Dr + Dg + Db)
        compare_entities_with_target(&target, generation);
        //внутри функции selection рано или поздно программа завершится (по совпадению с целевым либо по лимиму итераций)
        selection(generation, &target, max_delta, iter_limit);
        crossover(generation); //формуруем 5 новых особей из 5 лучших
    }
    return 0;
}



void check_malloc(void *pointer)
{
    if(NULL == pointer)
    {
        printf("Error with memory allocation!\n\a");
        exit(EXIT_FAILURE);
    }
}

void get_initaial_values(entity *target, unsigned char *max_delta, unsigned *iter_limit)
{
    unsigned char val;
    unsigned limit;
    printf("Enter RED value -> ");
    scanf("%hhu", &val);
    target->r = val;
    printf("Enter GREEN value -> ");
    scanf("%hhu", &val);
    target->g = val;
    printf("Enter BLUE value -> ");
    scanf("%hhu", &val);
    target->b = val;
    printf("Enter *MAX delta value* -> ");
    scanf("%hhu", &val);
    *max_delta = val;
    printf("Enter *MAX number of iterations* -> ");
    scanf("%u", &limit);
    *iter_limit = limit;
}

void init_1st_generation(entity *generation) //созданёт 10 особей {Ri, Gi, Bi}, где i[0; 9], R,G,B - rand(0, 255)
{
    for(int i = 0; i < 10; i++)
    {
        (generation + i)->r = (unsigned char)(255.0f * rand() / (RAND_MAX + 1.0f));
        (generation + i)->g = (unsigned char)(255.0f * rand() / (RAND_MAX + 1.0f));
        (generation + i)->b = (unsigned char)(255.0f * rand() / (RAND_MAX + 1.0f));
        //generation[i]->delta = -1; Нужно инициализировать или нет пока не решил
    }
}

void swap(entity *first, entity *second) //меняет местами два элемента массива структур - текущего поколения
{
    unsigned char tmp;
    tmp = first->r;
    first->r = second->r;
    second->r = tmp;

    tmp = first->g;
    first->g = second->g;
    second->g = tmp;

    tmp = first->b;
    first->b = second->b;
    second->b = tmp;

    tmp = first->delta;
    first->delta = second->delta;
    second->delta = tmp;
}

void print_last_generation(entity *generation) //вывод финального поколения
{
    for(int i = 9; i >= 0; i--)
        printf("[%hhu] {%hhu %hhu %hhu}\n", i+1, (generation + i)->r, (generation + i)->g, (generation + i)->b);
}
