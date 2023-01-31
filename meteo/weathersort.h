#ifndef MAINDEF
#define MAINDEF


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


typedef struct _date {
    int year;
    int month;
    int day;
    int hour;
    int utc;
}Date;

typedef struct _station1 {
    int ID;     //Station ID

    float min;      //Will contain min value reached for a certain date or ID
    float max;      //Will contain max value reached for a certain date or ID

    int count;      //All sorts : will contain the number of times a certain date or ID has been encountered

    float total;        //All sorts : will contain the total of the currently sorted elements for a given ID or date
    float total2;       

    float average;      //All sorts : will contain the average value of the currently sorted elements for a given ID or date
    float average2;     //Only used in wind : wind vector's average y coordinate

    float cos;      //Only used in wind : wind vector's x coordinate
    float sin;      //Only used in wind : wind vector's y coordinate

    Date* date;     //Date

    struct _station1* rs;   //Right son
    struct _station1* ls;   //Left son

    int balance;    //Only used in AVL : element balance

    float x;        //Longitude coordinates
    float y;        //Latitude coordinates

} Station1;

typedef struct _node {
    int ID;     //Station ID

    float min;      //Will contain min value reached for a certain date or ID
    float max;      //Will contain max value reached for a certain date or ID

    int count;      //All sorts : will contain the number of times a certain date or ID has been encountered

    float total;        //All sorts : will contain the total of the currently sorted elements for a given ID or date
    float total2;       //Only used in wind : total of the wind vector's y coordinate

    float average;          //All sorts : will contain the average value of the currently sorted elements for a given ID or date
    float average2;         //Only used in wind : wind vector's average y coordinate
    
    float cos;      //Only used in wind : wind vector's x coordinate
    float sin;      //Only used in wind : wind vector's y coordinate

    Date* date;     //Date

    struct _node* pNext;        //Next element
    struct _node* pBefore;      //Previous element

    float x;        //Longitude coordinates
    float y;        //Latitude coordinates
}Node;

typedef struct _list {
    Node* pFirst;       //List's first element
    Node* pLast;        //List's last element
}List;


#include "./create/create.h"
#include "./display/display.h"
#include "./ABR/ABRSort.h"
#include "./AVL/AVLSort.h"
#include "./List/List.h"


//=======================================================================

int TestFileExist ( char* FN );         //Check if given files exist

Date* addDate( int year, int month, int day, int hour, int utc);        //Create a date structure with given values
int dateComp ( Date* NewDate, Date* currDate );             //Compare new date and current date

int SortABR( char* preFN , char* postFN , int R, int dSort, int mode);          //Sort using ABR method
int SortLIST(char* preFN , char* postFN , int R, int dSort, int mode);          //Sort using Doubly linked list method
int SortAVL( char* preFN , char* postFN , int R, int* pH, int dSort, int mode );    //Sort using AVL method

//=======================================================================

#endif