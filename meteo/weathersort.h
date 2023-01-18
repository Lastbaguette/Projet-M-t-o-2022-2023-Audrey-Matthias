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
} Station1;

typedef struct _node {
    int ID;
    float elt;
    Date* date;
    float x;
    float y;
    float e1;
    float e2;
    struct _node* pNext;
    struct _node* pBefore;
}Node;

typedef struct _list {
    Node* pFirst;
    Node* pLast;
}List;


#include "create.h"
#include "display.h"
#include "ABRSort.h"
#include "AVLSort.h"


//=======================================================================

Date* addDate( int year, int month, int day, int hour, int utc);
int dateComp ( Date* NewDate, Date* currDate );

//=======================================================================

#endif