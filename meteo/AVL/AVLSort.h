#ifndef AVLDEF
#define AVLDEF


#include "../weathersort.h"


//=======================================================================

int min( int a, int b );
int max( int a, int b );
Station1* LeftRotationSt( Station1* S );
Station1* RightRotationSt( Station1* S );
Station1* correct( Station1* S );
int TestBalance(Station1* S);
int Balance (Station1* S);
Station1* Test( Station1* S );

Station1* InsertAVLStation ( Station1* S, int ID, float v, Date* D, float x, float y);
Station1* AveragePStationAVL( Station1* S, int ID, float v, int* pH, Date* D, float x, float y);
Station1* InsertPDateAllStAVL( Station1* S, int ID, float v, int* pH, Date* D, float x, float y);
Station1* InsertPDatePStAVL( Station1* S, int ID, float v, int* pH, Date* D, float x, float y);
Station1* InsertAVLStationbis ( Station1* S, int ID, float v, float v2, int* pH, float x, float y);
Station1* AveragePStationVectorAVL( Station1* S, int ID, float v, float v2 ,int* pH, float x, float y);
Station1* InsertHeightAVL(Station1* S, int ID, float v, Date* D, int* pH, float x, float y);
Station1* SortHeightAVL( Station1* S, int ID, float v, Date* D, int* pH, float x, float y);
Station1* InsertMoistureAVL(Station1* S, Station1* NS, int* pH);
Station1* SortMoistureAVL( Station1* S, Station1* NS, int* pH);

//=======================================================================


#endif