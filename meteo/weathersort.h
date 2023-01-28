#ifndef MAINDEF
#define MAINDEF


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct _date {
    int year;
    int month;
    int day;
    int hour;
    int utc;
}Date;

typedef struct _station1 {
    int ID;

    float min;
    float max;
    float min2;
    float max2;
    int count;
    float total;
    float total2;
    float average;
    float average2;

    Date* date;

    struct _station1* rs;
    struct _station1* ls;

    int balance;

    float x;
    float y;

} Station1;

typedef struct _node {
    int ID;

    float min;
    float max;
    float min2;
    float max2;
    int count;
    float total;
    float total2;
    float average;
    float average2;

    Date* date;   
    struct _node* pNext;
    struct _node* pBefore;

    float x;
    float y;
}Node;

typedef struct _list {
    Node* pFirst;
    Node* pLast;
}List;


#include "./create/create.h"
#include "./display/display.h"
#include "./ABR/ABRSort.h"
#include "./AVL/AVLSort.h"
#include "./List/List.h"


//=======================================================================

int TestFileExist ( char* FN );

Date* addDate( int year, int month, int day, int hour, int utc);
int dateComp ( Date* NewDate, Date* currDate );

int SortABR( char* preFN , char* postFN , int R, int dSort, int mode);
int SortLIST(char* preFN , char* postFN , int R, int dSort, int mode);
int SortAVL( char* preFN , char* postFN , int R, int* pH, int dSort, int mode );

//=======================================================================

#endif