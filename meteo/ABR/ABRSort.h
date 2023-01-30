#ifndef ABRDEF
#define ABRDEF


#include "../weathersort.h"

/*================================================================================================================================================

ABR method sorting functions prototypes

================================================================================================================================================*/

//=======================================================================

// Searching and average calculation (called editing) functions
int search( Station1* S , int ID );
void searchEdit( Station1* S , int ID, float v);
void searchEditVector( Station1* S , int ID, float v, float v2);

//=======================================================================

// Mode 1 Sort for temperature and pressure
void InsertABRStation ( Station1* S, int ID, float v, Date* D, float x, float y);
void AveragePStationABR( Station1* S, int ID, float v, Date* D, float x, float y);

//=======================================================================

// Mode 2 Sort for temperature and pressure
Station1* InsertPDateAllStABR( Station1* S, int ID, float v, Date* D , float x, float y);

//=======================================================================

// Mode 3 Sort for temperature and pressure
void InsertPDatePStABR( Station1* S, int ID, float v, Date* D, float x, float y );

//=======================================================================

// Wind Sort
void InsertABRStationbis ( Station1* S, int ID, float v, float v2, float x, float y);
void AveragePStationVectorABR( Station1* S, int ID, float v, float v2 , float x, float y);

//=======================================================================

// Height Sort
Station1* InsertHeightABR(Station1* S, Station1* NS);
void SortHeight1( Station1* S, int ID, float v, Date* D, float x, float y);
Station1* SortHeight2( Station1* S, Station1* NS);

//=======================================================================

// Moisture Sort
Station1* InsertMoistureABR(Station1* S, Station1* NS);
Station1* SortMoisture( Station1* S, Station1* NS);

//=======================================================================

#endif