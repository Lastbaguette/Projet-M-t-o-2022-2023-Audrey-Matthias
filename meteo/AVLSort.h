#ifndef AVLDEF
#define AVLDEF


#include "weathersort.h"


//=======================================================================

int min( int a, int b );
int max( int a, int b );
Station1* LeftRotationSt( Station1* S );
Station1* RightRotationSt( Station1* S );
Station1* DoubleRightRotationSt ( Station1* S );
Station1* DoubleLeftRotationSt ( Station1* S );
Station1* StationBalance ( Station1* S );
Station1* InsertAVLStation ( Station1* S, int ID, float v, int* pH, Date* D);
Station1* AveragePStationAVL( Station1* S, int ID, float v, int* pH, Date* D);
Station1* InsertPDateAllStAVL( Station1* S, int ID, float v, int* pH, Date* D );
Station1* InsertPDatePStAVL( Station1* S, int ID, float v, int* pH, Date* D );
Station1* InsertAVLStationbis ( Station1* S, int ID, float v, float v2, int* pH);
Station1* AveragePStationVectorAVL( Station1* S, int ID, float v, float v2 ,int* pH);

//=======================================================================


#endif