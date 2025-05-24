/*****************************

    Name : Or Beruven

    Reviewed By : Neviu

    Date Test: 25.06.2023

    Description : C File For Java2C Implemantation

*****************************/
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*NULL*/
#include <assert.h>	/*assert*/

#include "Animal.h"

#define MAX_FUNCS (10)
#define SUCCESS 0
#define FAIL 1
#define TO_STRING (30)

#define TRUE (1)
#define FALSE (0)

#define TO_STRING_FUNC (0)
#define FINALIZE_FUNC (1)
#define SAY_HELLO_FUNC (2)
#define GET_MASTERS_FUNC (3)
#define SHOW_COUNTER_FUNC (4)

/*******************************************************************************
 *                              TYPEDEFS
*******************************************************************************/
typedef void(*finalize_t)(object_t *object);
typedef char *(*to_string_t)(object_t *object, char *result);
typedef void(*show_counter_t)(void);
typedef void (*SayHello_t)();
/*******************************************************************************/

/*******************************************************************************
                    Animal Help Functions Declerations
*******************************************************************************/
static void InitAnimal(animal_t *animal);
static void StaticAnimalInit(void);
static void InitAnimalMaster(animal_t *animal, int num_of_masters);
static void AnimalStaticInit1(void);
static void AnimalStaticInit2(void);
static void AnimalInitBlock(void);
/*******************************************************************************/

/*******************************************************************************
                    Dog Help Functions Declerations
*******************************************************************************/
static void InitDog(dog_t *dog);
static void StaticDogInit(void);
static void InstanceDogInit(dog_t *dog);
/*******************************************************************************/

/*******************************************************************************
                    Cat Help Functions Declerations
*******************************************************************************/
static void StaticCatInit(void);
static void InitCat(cat_t *cat);
static void InitCatColored(cat_t *cat, char *colors);
/*******************************************************************************/


/*******************************************************************************
                LegendaryAnimal Help Functions Declerations
*******************************************************************************/
static void InitLegendaryAnimal(la_t *la);
static void StaticLegendaryAnimal(void);

/*******************************************************************************
                    Global Variables Declerations
*******************************************************************************/
int counter = 0;
int static_animal = FALSE;
int static_dog = FALSE;
int static_cat = FALSE;
int static_la = FALSE;


void *obj_func_table[MAX_FUNCS] = {&ToStringObj, &FinalizeObj};
static class_t obj_class = {obj_func_table, "Object", NULL};

void *animal_func_table[MAX_FUNCS] = {&ToStringAnimal, &FinalizeAnimal, &SayHelloAnimal, &GetNumMasters, &ShowCounter};
static class_t animal_class = {animal_func_table, "Animal", &obj_class};

void *dog_func_table[MAX_FUNCS] = {&ToStringDog, &FinalizeDog, &SayHelloDog, &GetNumMasters, &ShowCounter};
static class_t dog_class = {dog_func_table, "Dog", &animal_class};

void *cat_func_table[MAX_FUNCS] = {&ToStringCat, &FinalizeCat, &SayHelloAnimal, &GetNumMasters, &ShowCounter};
static class_t cat_class = {cat_func_table, "Cat", &cat_class};

void *la_func_table[MAX_FUNCS] = {&ToStringLegendaryAnimal, &FinalizeLegendaryAnimal, &SayHelloLegendaryAnimal, &GetNumMasters, &ShowCounter};
static class_t la_class = {la_func_table, "LegendaryAnimal", &la_class};

/*******************************************************************************/

/*******************************************************************************
                    Polymorphic Function Implementation
*******************************************************************************/
char *toString(object_t *obj, char *result)
{
    to_string_t func = (to_string_t)obj->obj_class->func_table[TO_STRING_FUNC];
    return func(obj, result);
}

void finalize(object_t *obj)
{
    finalize_t func = (finalize_t)obj->obj_class->func_table[FINALIZE_FUNC];
    func(obj);
}

void SayHello(object_t *obj)
{
    SayHello_t func = (SayHello_t)obj->obj_class->func_table[SAY_HELLO_FUNC];
    func();
}
/*******************************************************************************/

/*******************************************************************************
                    Object Function Implementation
*******************************************************************************/
void ToStringObj(object_t *obj, char *str)
{
    sprintf(str, "%s@%x", obj->obj_class->c_name, *(unsigned int *)&obj);
}

void FinalizeObj(object_t *obj)
{
    free(obj);
}

void ShowCounter(void)
{
    printf("%d\n", counter);
}

object_t *CreateObject()
{
    object_t *obj = (object_t *)malloc(sizeof(object_t));
    if (obj == NULL)
    {
        perror("Allocation error\n");
        return NULL;
    }

    obj->obj_class = &obj_class;
    return obj;
}
/*******************************************************************************/

/*******************************************************************************
                    Animal Function Implementation
*******************************************************************************/
animal_t *CreateAnimal(void)
{
    animal_t *animal = (animal_t *)malloc(sizeof(animal_t));
    if (animal == NULL)
    {
        perror("Allocation error\n");
        return NULL;
    }

    animal->object.obj_class = &animal_class;
    InitAnimal(animal);

    return animal;
}

animal_t *CreateAnimalMaster(int num_of_masters)
{
    animal_t *animal = (animal_t *)malloc(sizeof(animal_t));
    if (animal == NULL)
    {
        perror("Allocation error\n");
        return NULL;
    }

    animal->object.obj_class = &animal_class;
    InitAnimalMaster(animal, num_of_masters);
    return animal;
}

static void InitAnimal(animal_t *animal)
{
    to_string_t this_to_string = animal->object.obj_class->func_table[TO_STRING_FUNC];
    to_string_t super_to_string = animal_class.super->func_table[TO_STRING_FUNC];
    void (*sayHello)(animal_t*) = (void (*)(animal_t*))(animal->object.obj_class->func_table[SAY_HELLO_FUNC]);
    char buffer[TO_STRING] = {0};
    char buffer2[TO_STRING] = {0};

    StaticAnimalInit();
    AnimalInitBlock();

    animal->num_legs = 5;
    animal->num_of_masters = 1;

    printf("Animal Ctor\n");
    animal->ID = ++counter;
    sayHello(animal);
    ShowCounter();

    this_to_string((object_t*)animal, buffer);
    printf("%s\n", buffer);

    super_to_string(&animal->object, buffer);
    printf("%s\n", buffer);
}

static void InitAnimalMaster(animal_t *animal, int num_of_masters)
{
    StaticAnimalInit();
    AnimalInitBlock();

    printf("Animal Ctor int\n");
    animal->ID = ++counter;
    animal->num_legs = 5;
    animal->num_of_masters = num_of_masters;

}

static void StaticAnimalInit(void)
{
    static int static_init = 0;
    if (!static_init)
    {
        AnimalStaticInit1();
        AnimalStaticInit2();
        ++static_init;
    }
}

static void AnimalStaticInit1(void)
{
    static int static_init = 0;
    if (!static_init)
    {
        printf("Static block Animal 1\n");
        ++static_init;
    }
}

static void AnimalStaticInit2(void)
{
    static int static_init = 0;
    if (!static_init)
    {
        printf("Static block Animal 2\n");
        ++static_init;
    }
}

static void AnimalInitBlock(void)
{
    printf("Instance initialization block Animal\n");
}

void SayHelloAnimal(object_t *obj)
{
    animal_t *animal = (animal_t *)obj;
    printf("Animal Hello!\n");
    printf("I have %d legs\n", animal->num_legs);
}

void ToStringAnimal(object_t *obj, char *buffer)
{
    animal_t *animal = (animal_t *)obj;
    sprintf(buffer, "Animal with ID: %d", animal->ID);
}

void FinalizeAnimal(object_t *obj)
{  
    animal_t *animal = (animal_t *)obj;
    finalize_t final_super_func = (void (*)(object_t*)) animal->object.obj_class->super->func_table[FINALIZE_FUNC];
    printf("finalize Animal with ID: %d\n", animal->ID);

    final_super_func(&animal->object);
}

int GetNumMasters(animal_t *animal)
{
    return animal->num_of_masters;
}
/*******************************************************************************/


/*******************************************************************************
                    Dog Function Implementation
*******************************************************************************/
dog_t *CreateDog(void)
{
    dog_t *dog = (dog_t *)malloc(sizeof(dog_t));
    if (dog == NULL)
    {
        perror("Allocation error\n");
        return NULL;
    }

    dog->animal.object.obj_class = &dog_class;
    InitDog(dog);
    printf("Dog Ctor\n");

    return dog;
}

static void InitDog(dog_t *dog)
{
    StaticAnimalInit();
    StaticDogInit();
    InitAnimalMaster(&dog->animal, 2);
    InstanceDogInit(dog);
}

static void StaticDogInit(void)
{
    static int static_init = 0;
    if (!static_init)
    {
        printf("Static block Dog\n");
        ++static_init;
    }
}

static void InstanceDogInit(dog_t *dog)
{
    dog->animal.num_legs = 4;
    printf("Instance initialization block Dog\n");
}

void SayHelloDog(object_t *obj)
{
    dog_t *dog = (dog_t *)obj;
    printf("Dog Hello!\n");
    printf("I have %d legs\n", dog->animal.num_legs);
}

void ToStringDog(object_t *obj, char *buffer)
{
    dog_t *dog = (dog_t *)obj;
    sprintf(buffer, "Dog with ID: %d", dog->animal.ID);
}

void FinalizeDog(object_t *obj)
{
    dog_t *dog = (dog_t *)obj;
    finalize_t final_super_func = (void (*)(object_t *)) dog->animal.object.obj_class->super->func_table[FINALIZE_FUNC];
    printf("finalize Dog with ID: %d\n", dog->animal.ID);

    dog->animal.object.obj_class = &animal_class;
    final_super_func((object_t *)&dog->animal);

}
/*******************************************************************************/

/*******************************************************************************
                    Cat Function Implementation
*******************************************************************************/
cat_t *CreateCat(void)
{
    cat_t *cat = (cat_t *)malloc(sizeof(cat_t));
    if (cat == NULL)
    {
        perror("Allocation error\n");
        return NULL;
    }
    cat->animal.object.obj_class = &cat_class;

    InitCat(cat);
    return cat;
}

cat_t *CreateCatWithColors(char *color)
{
    cat_t *cat = (cat_t *)malloc(sizeof(cat_t));
    if (cat == NULL)
    {
        perror("Allocation error\n");
        return NULL;
    }
    cat->animal.object.obj_class = &cat_class;
    InitCatColored(cat, color);

    return cat;
}

static void InitCat(cat_t *cat)
{
    char *colors = "black";

    StaticCatInit();

    InitCatColored(cat, colors);
    printf("Cat Ctor\n");
    
    cat->num_of_masters = 2;
}

static void InitCatColored(cat_t *cat, char *colors)
{
    StaticCatInit();

    InitAnimal(&cat->animal);
    cat->colors = colors;
    cat->num_of_masters = 2;
    printf("Cat Ctor with color: %s\n", cat->colors);
}

static void StaticCatInit(void)
{
    static int static_init = 0;
    if (!static_init)
    {
        printf("Static block Cat\n");
        ++static_init;
    }
}

void ToStringCat(object_t *obj, char *buffer)
{
    cat_t *cat = (cat_t *)obj;
    sprintf(buffer, "Cat with ID: %d", cat->animal.ID);
}

void FinalizeCat(object_t *obj)
{
    cat_t *cat = (cat_t *)obj;
    cat->animal.object.obj_class = &animal_class;
    finalize_t final_super_func = (void (*)(object_t *)) cat->animal.object.obj_class->func_table[FINALIZE_FUNC];
    printf("finalize Cat with ID: %d\n", cat->animal.ID);

    final_super_func((object_t *)&cat->animal);
}
/*******************************************************************************/

/*******************************************************************************
                    LegendayAnimal Function Implementation
*******************************************************************************/
la_t *CreateLegendaryAnimal(void)
{
    la_t *la = (la_t *)malloc(sizeof(la_t));
    if (la == NULL)
    {
        perror("Allocation error\n");
        return NULL;
    }
    la->cat.animal.object.obj_class = &la_class;
    InitLegendaryAnimal(la);
    
    return la;
}

static void InitLegendaryAnimal(la_t *la)
{
    StaticAnimalInit();
    StaticCatInit();
    StaticLegendaryAnimal();
    InitCat(&la->cat);
    printf("Legendary Ctor\n");
}

static void StaticLegendaryAnimal(void)
{
    static int static_init = 0;
    if (!static_init)
    {
        printf("Static block Legendary Animal\n");
        ++static_init;
    }
}

void ToStringLegendaryAnimal(object_t *obj, char *buffer)
{
    la_t *la = (la_t *)obj;
    sprintf(buffer, "LegendaryAnimal with ID: %d", la->cat.animal.ID);
}

void SayHelloLegendaryAnimal(object_t *obj)
{
    (void)obj;
    printf("Legendary Hello!\n");
}

void FinalizeLegendaryAnimal(object_t *obj)
{
    la_t *la = (la_t *)obj;
    la->cat.animal.object.obj_class = &cat_class;
    finalize_t final_super_func = (void (*)(object_t *)) la->cat.animal.object.obj_class->func_table[FINALIZE_FUNC];
    printf("finalize LegendaryAnimal with ID: %d\n", la->cat.animal.ID);

    final_super_func((object_t *)&la->cat);
}
/*******************************************************************************/


/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/


/*******************************************************************************

*******************************************************************************/