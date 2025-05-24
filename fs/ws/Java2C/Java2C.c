/*****************************

    Name : Or Beruven

    Reviewed By : Neviu

    Date Test: 26.06.2023

    Description : C File for Java2C Test

*****************************/
#include <stdio.h>	/*printf*/
#include <assert.h>	/*assert*/

#include "Animal.h"

#define SIZE (5)
#define LENGTH (30)

#define SUCCESS 0
#define FAIL 1

/*******************************************************************************
                    Test Function Declarations
*******************************************************************************/
typedef int (*get_num_masters_t)(animal_t *animal);
typedef void (*finalize_t)(object_t *object);
typedef char *(*animal_to_string_t)(animal_t *animal, char *result);
typedef void(*say_hello_t)(object_t *obj);

/*******************************************************************************

*******************************************************************************/


/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/


/*******************************************************************************

*******************************************************************************/
static void foo(animal_t *a)
{
    char result[LENGTH] = {0};
    toString((object_t *)a, result);
    printf("%s\n", result);
}

/********************************************************************
*                            Main Function                            *
*********************************************************************/

int main()
{
    say_hello_t say_hello = NULL;
    get_num_masters_t get_masters = NULL;
    size_t i = 0;
    object_t *obj = CreateObject();
    animal_t *animal = CreateAnimal();
    dog_t *dog = CreateDog();
    cat_t *cat = CreateCat();
    la_t *la = CreateLegendaryAnimal();

/*
    ShowCounter();
    printf("%d\n", animal->ID);
    printf("%d\n", dog->animal.ID);
    printf("%d\n", cat->animal.ID);
    printf("%d\n", la->cat.animal.ID);*/

    /*animal_t *array[SIZE] = 
    {
        (animal_t *)CreateDog(),
        (animal_t *)CreateCat(),
        (animal_t *)CreateCatWithColors("white"),
        (animal_t *)CreateLegendaryAnimal(),
        CreateAnimal()
    };*/

    /*for (i = 0; i < SIZE; ++i)
    {
        say_hello = array[i]->object.obj_class->func_table[SAY_HELLO_FUNC];
        say_hello((object_t *)array[i]);
        get_masters = array[i]->object.obj_class->func_table[GET_MASTERS_FUNC];
        printf("num of masters : %d\n\n", get_masters(array[i]));
    }
    
    for (i = 0; i < SIZE; ++i)
    {
        foo(array[i]);
    }*/
    
    printf("HERE\n");
    finalize(obj);
    finalize((object_t *)animal); 
    finalize((object_t *)dog);
    finalize((object_t *)cat);
    finalize((object_t *)la);

    /*for (i = 0; i < SIZE; ++i)
    {
        finalize = array[i]->object.obj_class->func_table[FINALIZE_FUNC];
        finalize((object_t *)array[i]);
    }*/
    
    return 0;
}

/*******************************************************************************
                    Test Function Implementation
*******************************************************************************/


/*******************************************************************************

*******************************************************************************/