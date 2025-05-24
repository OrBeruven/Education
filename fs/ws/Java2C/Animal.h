/*****************************

    Name : Or Beruven

    Reviewed By : Neviu

    Date Test: 25.06.2023

    Description : H File For Java2C Implemantation

*****************************/
#ifndef __ANIMAL_JAVA2C__
#define __ANIMAL_JAVA2C__

#define MAX_NAME (20)
#define COLOR_LENGTH (8)

typedef struct class_s class_t;
typedef struct object_s object_t;
typedef struct animal_s animal_t;
typedef struct dog_s dog_t;
typedef struct cat_s cat_t;
typedef struct legendaryanimal_s la_t;

struct class_s
{
    void **func_table;
    char c_name[MAX_NAME];
    class_t *super;
};

/***Object Struct***/
struct object_s
{
    class_t *obj_class;
};

/***Animal Struct***/
struct animal_s
{
    object_t object;
    int num_legs;
    int num_of_masters;
    int ID;
};

/***Dog Struct***/
struct dog_s                        /*Extends Animal*/
{
    animal_t animal;
};

/***Cat Struct***/
struct cat_s                        /*Extends Animal*/
{
    animal_t animal;
    char *colors;
    int num_of_masters;
};

/***LegendaryAnimal Struct***/
struct legendaryanimal_s            /*Extends Cat*/
{
    cat_t cat;
};
/*******************************************************************************
                    Object Function Declarations
*******************************************************************************/
void ToStringObj(object_t *obj, char *str);
void FinalizeObj(object_t *obj);
void ShowCounter(void);
object_t *CreateObject();
void SayHello(object_t *obj);
void finalize(object_t *obj);
char *toString(object_t *obj, char *result);

/*******************************************************************************/

/*******************************************************************************
                    Animal Function Declarations
*******************************************************************************/
animal_t *CreateAnimal(void);
animal_t *CreateAnimalMaster(int num_of_masters);
void SayHelloAnimal(object_t *obj);
void ToStringAnimal(object_t *obj, char *buffer);
int GetNumMasters(animal_t *animal);
void FinalizeAnimal(object_t *obj);
/*******************************************************************************/

/*******************************************************************************
                    Dog Function Declarations
*******************************************************************************/
dog_t *CreateDog(void);
void SayHelloDog(object_t *obj);
void FinalizeDog(object_t *obj);
void ToStringDog(object_t *obj, char *buffer);
/*******************************************************************************/

/*******************************************************************************
                    Cat Function Declarations
*******************************************************************************/
cat_t *CreateCat(void);
cat_t *CreateCatWithColors(char *color);
void ToStringCat(object_t *obj, char *buffer);
void FinalizeCat(object_t *obj);
/*******************************************************************************/

/*******************************************************************************
                    LegendaryAnimal Function Declarations
*******************************************************************************/
la_t *CreateLegendaryAnimal(void);
void ToStringLegendaryAnimal(object_t *obj, char *buffer);
void SayHelloLegendaryAnimal(object_t *obj);
void FinalizeLegendaryAnimal(object_t *obj);
/*******************************************************************************/

#endif