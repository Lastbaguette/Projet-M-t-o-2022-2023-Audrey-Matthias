#ifndef CREATE
#define CREATE

#include "weathersort.h"

//=======================================================================

Station1* createStation1 ( int ID, float v, Date* D);
Station1* createStation1bis( int ID, float v, float v2);
Station1* AddLeftSt ( Station1* S, int ID, float v, Date* D);
Station1* AddRightSt ( Station1* S, int ID, float v, Date* D );
Station1* AddLeftSt2 ( Station1* S, Station1* NS );
Station1* AddRightSt2 ( Station1* S, Station1* NS );
Station1* AddLeftStbis  ( Station1* S, int ID, float v, float v2 );
Station1* AddRightStbis ( Station1* S, int ID, float v, float v2 );

//=======================================================================

#endif