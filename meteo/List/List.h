#ifndef ListDEF
#define ListDEF


#include "../weathersort.h"

//=======================================================================

int searchList( Node* pHead, int ID );
void searchEditList( Node* pHead, int ID, float v );
void AvPStationList( List* L, int ID, float v, Date* D, float x, float y );
void InsertListSt( List* L, Node* pHead, int ID, float v, Date* D, float x, float y );

//=======================================================================

#endif