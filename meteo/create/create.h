#ifndef CREATE
#define CREATE

#include "../weathersort.h"

//=======================================================================

Station1* createStation1 ( int ID, float v, Date* D, float x, float y);              //Function to create a station using one value to sort
Station1* createStation1bis( int ID, float v, float v2, float x, float y);           //Function to create a station using two values to sort

Station1* AddLeftSt ( Station1* S, int ID, float v, Date* D, float x, float y);         //Add left son (from one tree (here called a station) to another)
Station1* AddRightSt ( Station1* S, int ID, float v, Date* D, float x, float y );       //Add right son (from one tree (here called a station) to another)
Station1* AddLeftSt2 ( Station1* S, Station1* NS );             //Add left son (from one tree element into a new one)
Station1* AddRightSt2 ( Station1* S, Station1* NS );            //Add right son (from one tree element into a new one)
Station1* AddLeftStbis  ( Station1* S, int ID, float v, float v2, float x, float y );       //Add left son (if it has two given values)
Station1* AddRightStbis ( Station1* S, int ID, float v, float v2, float x, float y );       //Add right son (if it has two given values)


List* Init(List* L, Node* elt);             //Initialize the beginning and end of the list
Node* createNode ( int ID, float v, Date* D, float x, float y );            //Create a list node from one value

//=======================================================================

#endif