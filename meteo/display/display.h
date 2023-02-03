#ifndef DISPLAYDEF
#define DISPLAYDEF


#include "../weathersort.h"

/*================================================================================================================================================

Writing functions prototypes

================================================================================================================================================*/

//=======================================================================
//File writing functions for ABR and AVL modes

void processAvPerSt( Station1* S, FILE* post, int count);             //M1 for temperature and pressure
void processAvPerDateAllSt( Station1* S, FILE* post );      //M2 for temperature and pressure
void processPerDatePSt( Station1* S, FILE* post );          //M3 for temperature and pressure
void processWind( Station1* S, FILE* post );                //Wind
void processHeight( Station1* S, FILE* post );              //Height
void processMoisture( Station1* S, FILE* post );            //Moisture

//=======================================================================

//=======================================================================
//Functions to go across the tree

void displayAvPerSt( Station1* S, FILE* post, int count);              //M1 for temperature and pressure
void displayAvPerDateAllSt( Station1* S, FILE* post);       //M2 for temperature and pressure
void displayPerDatePSt( Station1* S, FILE* post);           //M3 for temperature and pressure
void displayWind( Station1* S, FILE* post);                 //Wind

void displayHeight( Station1* S, FILE* post);               //Height
void RdisplayHeight( Station1* S, FILE* post);              //Height in reverse

void displayMoisture( Station1* S, FILE* post);             //Moisture
void RdisplayMoisture( Station1* S, FILE* post);            //Moisture in reverse

//=======================================================================
//File writing functions for List mode

void displayListAvPerSt(FILE* post, Node* pNode, int count);           //M1 for temperature and pressure
void displayListAvPerDateAllSt(FILE* post, Node* pNode);    //M2 for temperature and pressure
void displayListAvPerDatePerSt(FILE* post, Node* pNode);    //M3 for temperature and pressure
void displayListWind(FILE* post, Node* pNode);              //Wind

void displayListHeight(FILE* post, Node* pNode);            //Height
void RdisplayListHeight(FILE* post, Node* pNode);           //Height in reverse

void displayListMoisture(FILE* post, Node* pNode);          //Moisture
void RdisplayListMoisture(FILE* post, Node* pNode);         //Moisture in reverse

//=======================================================================

#endif
