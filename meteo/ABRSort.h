#ifndef ABRDEF
#define ABRDEF


#include "weathersort.h"

//=======================================================================

int search( Station1* S , int ID );
void searchEdit( Station1* S , int ID, float v);
void searchEditVector( Station1* S , int ID, float v, float v2);

void InsertABRStation ( Station1* S, int ID, float v, Date* D);
void InsertPDateAllStABR( Station1* S, int ID, float v, Date* D );
void InsertPDatePStABR( Station1* S, int ID, float v, Date* D );
void InsertABRStationbis ( Station1* S, int ID, float v, float v2);
void InsertHeightABR(Station1* S, int ID, float v, Date* D);
Station1* InsertMoistureABR(Station1* S, Station1* NS);

void AveragePStationABR( Station1* S, int ID, float v, Date* D);
void AveragePStationVectorABR( Station1* S, int ID, float v, float v2 );
void SortHeight( Station1* S, int ID, float v, Date* D);
Station1* SortMoisture( Station1* S, Station1* NS);

//=======================================================================

#endif