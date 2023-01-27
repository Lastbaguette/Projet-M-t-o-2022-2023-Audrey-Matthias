#ifndef ListDEF
#define ListDEF


#include "../weathersort.h"

//=======================================================================

int searchList( List* L , int ID );
void searchEditList( Node* pHead, int ID, float v );
void AvPStationList( List* L, int ID, float v, Date* D, float x, float y );
void InsertListSt( Node* pHead, int ID, float v, Date* D, float x, float y );

//=======================================================================

#endif