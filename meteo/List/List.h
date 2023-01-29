#ifndef ListDEF
#define ListDEF


#include "../weathersort.h"

//=======================================================================

// Searching and average calculation (called editing) functions
int searchList( Node* pHead, int ID );
void searchEditList( Node* pHead, int ID, float v );
void searchEditListBis( Node* pHead, int ID, float v, float v2);

//=======================================================================

// Mode 1 Sort for temperature and pressure
void AvPStationList( List* L, int ID, float v, Date* D, float x, float y );
void InsertListSt( List* L, Node* pHead, int ID, float v, Date* D, float x, float y );

//=======================================================================

// Mode 2 Sort for temperature and pressure
void InsertPerDateAllStList(List* L, Node* pHead, int ID, float value, Date* D, float x, float y);

//=======================================================================

// Mode 3 Sort for temperature and pressure
void InsertPerDatePerStList(List* L, Node* pHead, int ID, float v, Date* D, float x, float y);

//=======================================================================

// Wind Sort
void AvPStationVectorList( List* L, int ID, float v, float v2, float x, float y );
void InsertListStBis( List* L, Node* pHead, int ID, float v, float v2, float x, float y );

//=======================================================================

// Height Sort

//=======================================================================

// Moisture Sort

//=======================================================================


#endif