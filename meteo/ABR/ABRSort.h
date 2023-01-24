#ifndef ABRDEF
#define ABRDEF


#include "../weathersort.h"

//=======================================================================

int search( Station1* S , int ID );
void searchEdit( Station1* S , int ID, float v);
void searchEditVector( Station1* S , int ID, float v, float v2);

void InsertABRStation ( Station1* S, int ID, float v, Date* D, float x, float y);
void InsertPDateAllStABR( Station1* S, int ID, float v, Date* D , float x, float y);
void InsertPDatePStABR( Station1* S, int ID, float v, Date* D, float x, float y );
void InsertABRStationbis ( Station1* S, int ID, float v, float v2, float x, float y);
Station1* InsertHeightABR(Station1* S, Station1* NS);
Station1* InsertMoistureABR(Station1* S, Station1* NS);

void AveragePStationABR( Station1* S, int ID, float v, Date* D, float x, float y);
void AveragePStationVectorABR( Station1* S, int ID, float v, float v2 , float x, float y);
void SortHeight1( Station1* S, int ID, float v, Date* D, float x, float y);
Station1* SortHeight2( Station1* S, Station1* NS);
Station1* SortMoisture( Station1* S, Station1* NS);

//=======================================================================

#endif