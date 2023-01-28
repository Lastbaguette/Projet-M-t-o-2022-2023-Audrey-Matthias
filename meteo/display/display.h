#ifndef DISPLAYDEF
#define DISPLAYDEF


#include "../weathersort.h"

//=======================================================================
//File writing functions for ABR and AVL modes

void processAvPerSt( Station1* S, FILE* post );             //M1 for temperature and pressure
void processAvPerDateAllSt( Station1* S, FILE* post );      //M2 for temperature and pressure
void processPerDatePSt( Station1* S, FILE* post );          //M3 for temperature and pressure
void processWind( Station1* S, FILE* post );                //Wind
void processHeight( Station1* S, FILE* post );              //Height
void processMoisture( Station1* S, FILE* post );            //Moisture

//=======================================================================

//=======================================================================
//Functions to go across the tree

void displayAvPerSt( Station1* S, FILE* post);              //M1 for temperature and pressure
void displayAvPerDateAllSt( Station1* S, FILE* post);       //M2 for temperature and pressure
void displayPerDatePSt( Station1* S, FILE* post);           //M3 for temperature and pressure
void displayWind( Station1* S, FILE* post);                 //Wind

void displayHeight( Station1* S, FILE* post);               //Height
void RdisplayHeight( Station1* S, FILE* post);              //Height in reverse

void displayMoisture( Station1* S, FILE* post);             //Moisture
void RdisplayMoisture( Station1* S, FILE* post);            //Moisture in reverse

//=======================================================================
//File writing functions for List mode

void displayListAvPerSt(FILE* post, Node* pNode);
void displayListAvPerDateAllSt(FILE* post, Node* pNode);

//=======================================================================

#endif