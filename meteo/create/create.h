#ifndef CREATE
#define CREATE

#include "../weathersort.h"

//=======================================================================

Station1* createStation1 ( int ID, float v, Date* D, float x, float y);
Station1* createStation1bis( int ID, float v, float v2, float x, float y);
Station1* AddLeftSt ( Station1* S, int ID, float v, Date* D, float x, float y);
Station1* AddRightSt ( Station1* S, int ID, float v, Date* D, float x, float y );
Station1* AddLeftSt2 ( Station1* S, Station1* NS );
Station1* AddRightSt2 ( Station1* S, Station1* NS );
Station1* AddLeftStbis  ( Station1* S, int ID, float v, float v2, float x, float y );
Station1* AddRightStbis ( Station1* S, int ID, float v, float v2, float x, float y );

void Init(List* L);
Node* createNode ( int ID, float v, Date* D, float x, float y );

//=======================================================================

#endif