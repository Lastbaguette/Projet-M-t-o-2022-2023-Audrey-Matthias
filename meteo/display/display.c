#include "../weathersort.h"

/*================================================================================================================================================

Writing functions

================================================================================================================================================*/

//=======================================================================
//File writing functions for ABR and AVL modes

void processAvPerSt( Station1* S, FILE* post, int* count ){
    *count = *count + 1;
    fprintf( post, "%d %d    %f   %f %f\n", *count, S -> ID, S -> average, S -> min, S-> max);         // ID  Average Min Max 
}

void processAvPerDateAllSt( Station1* S, FILE* post ){
    fprintf( post, "%d-%d-%d   %d:00:00+%d          %f \n", S->date->year, S->date->month, S->date->day, S->date->hour, S->date->utc, S -> average);        // Date  Average
}

void processPerDatePSt( Station1* S, FILE* post ){
    fprintf( post, "%d-%d-%d    %d:00:00+%d     %d   %f \n", S->date->year, S->date->month, S->date->day, S->date->hour, S->date->utc, S -> ID, S -> average);      // Date  ID Average
}

void processWind( Station1* S, FILE* post ){
    fprintf( post, "%d    %f %f    %f %f\n", S -> ID, S -> average, S->average2, S->x, S->y);       // ID  Average module  Average orientation  Coordinates
}

void processHeight( Station1* S, FILE* post ){
    fprintf( post, "%d %f    %f %f\n", S -> ID, S -> average, S->x, S->y);          // ID  Value Coordinates
}

void processMoisture( Station1* S, FILE* post ){
    fprintf( post, "%d %f    %f %f\n", S -> ID, S -> max, S->x, S->y);          // ID Max value Coordinates
}

//=======================================================================

//=======================================================================
//Functions to go across the tree

void displayAvPerSt( Station1* S, FILE* post, int* count){
    if ( S != NULL ){
        displayAvPerSt( S -> ls, post, count);
        processAvPerSt( S, post, count );
        displayAvPerSt( S -> rs, post, count);
    }
}

void displayAvPerDateAllSt( Station1* S, FILE* post){
    if ( S != NULL ){
        displayAvPerDateAllSt( S -> ls, post);
        processAvPerDateAllSt( S, post );
        displayAvPerDateAllSt( S -> rs, post);
    }
}

void displayPerDatePSt( Station1* S, FILE* post){
    if ( S != NULL ){
        displayPerDatePSt( S -> ls, post);
        processPerDatePSt( S, post );
        displayPerDatePSt( S -> rs, post);
    }
}

void displayWind( Station1* S, FILE* post){
    if ( S != NULL ){
        displayWind( S -> ls, post);
        processWind( S, post );
        displayWind( S -> rs, post);
    }
}


void displayHeight( Station1* S, FILE* post){
    if ( S != NULL ){
        displayHeight( S -> rs, post);
        processHeight( S, post );
        displayHeight( S -> ls, post);
    }
}

void RdisplayHeight( Station1* S, FILE* post){
    if ( S != NULL ){
        RdisplayHeight( S -> ls, post);
        processHeight( S, post );
        RdisplayHeight( S -> rs, post);
    }
}


void displayMoisture( Station1* S, FILE* post){
    if ( S != NULL ){
        displayMoisture( S -> rs, post);
        processMoisture( S, post );
        displayMoisture( S -> ls, post);
    }
}

void RdisplayMoisture( Station1* S, FILE* post){
    if ( S != NULL ){
        RdisplayMoisture( S -> ls, post);
        processMoisture( S, post );
        RdisplayMoisture( S -> rs, post);
    }
}

//=======================================================================

//=======================================================================
//File writing functions for List mode

void displayListAvPerSt(FILE* post, Node* pNode, int* count){

    while(pNode != NULL){
	    *count = *count + 1;
        fprintf( post, "%d %d    %f   %f %f\n", *count, pNode -> ID, pNode -> average, pNode -> min, pNode-> max);     // ID  Average Min Max 
        pNode = pNode->pNext;
    }
    
}

void displayListAvPerDateAllSt(FILE* post, Node* pNode){

    while(pNode != NULL){
        fprintf( post, "%d-%d-%d   %d:00:00+%d          %f \n", pNode->date->year, pNode->date->month, pNode->date->day, pNode->date->hour, pNode->date->utc, pNode -> average);        // Date  Average
        pNode = pNode->pNext;
    }
    
}

void displayListAvPerDatePerSt(FILE* post, Node* pNode){

    while(pNode != NULL){
        fprintf( post, "%d-%d-%d    %d:00:00+%d     %d   %f \n", pNode->date->year, pNode->date->month, pNode->date->day, pNode->date->hour, pNode->date->utc, pNode -> ID, pNode -> average);      // Date  ID Average
        pNode = pNode->pNext;
    }
    
}

void displayListWind(FILE* post, Node* pNode){

    while(pNode != NULL){
        fprintf( post, "%d    %f %f    %f %f\n", pNode -> ID, pNode -> average, pNode -> average2, pNode -> x, pNode ->y );       // ID  Average module  Average orientation  Coordinates
        pNode = pNode->pNext;
    }
    
}

void displayListHeight(FILE* post, Node* pNode){                    //Starting from the end to have decreasing values

    while(pNode != NULL){
        fprintf( post, "%d %f    %f %f\n", pNode -> ID, pNode -> average, pNode->x, pNode->y);      // ID  Value Coordinates
        pNode = pNode->pBefore;
    }
    
}

void RdisplayListHeight(FILE* post, Node* pNode){

    while(pNode != NULL){
        fprintf( post, "%d %f    %f %f\n", pNode -> ID, pNode -> average, pNode->x, pNode->y);      // ID  Value Coordinates
        pNode = pNode->pNext;
    }
    
}

void displayListMoisture(FILE* post, Node* pNode){

    while(pNode != NULL){
        fprintf( post, "%d %f    %f %f\n", pNode -> ID, pNode -> max, pNode->x, pNode->y);          // ID Max value Coordinates
        pNode = pNode->pBefore;
    }
    
}

void RdisplayListMoisture(FILE* post, Node* pNode){

    while(pNode != NULL){
        fprintf( post, "%d %f    %f %f\n", pNode -> ID, pNode -> max, pNode -> x, pNode -> y);      // ID Max value Coordinates
        pNode = pNode->pNext;
    }
    
}

