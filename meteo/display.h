#ifndef DISPLAYDEF
#define DISPLAYDEF


#include "weathersort.h"

//=======================================================================

void processAvPerSt( Station1* S, FILE* post );
void processAvPerDateAllSt( Station1* S, FILE* post );
void processPerDatePSt( Station1* S, FILE* post );
void processWind( Station1* S, FILE* post );
void processHeight( Station1* S, FILE* post );
void processMoisture( Station1* S, FILE* post );

void displayAvPerSt( Station1* S, FILE* post);
void displayAvPerDateAllSt( Station1* S, FILE* post);
void displayPerDatePSt( Station1* S, FILE* post);
void displayHeight( Station1* S, FILE* post);
void RdisplayHeight( Station1* S, FILE* post);
void displayMoisture( Station1* S, FILE* post);
void RdisplayMoisture( Station1* S, FILE* post);
void displayWind( Station1* S, FILE* post);

//=======================================================================

#endif