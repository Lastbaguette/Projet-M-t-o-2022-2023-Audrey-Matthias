#include "../weathersort.h"


//=======================================================================
//File writing functions for ABR and AVL modes

void processAvPerSt( Station1* S, FILE* post ){
    fprintf( post, "%d    %f   %f %f\n", S -> ID, S -> average, S -> min, S-> max);
}

void processAvPerDateAllSt( Station1* S, FILE* post ){
    fprintf( post, "%d-%d-%d   %d:00:00+%d          %f \n", S->date->year, S->date->month, S->date->day, S->date->hour, S->date->utc, S -> average);
}

void processPerDatePSt( Station1* S, FILE* post ){
    fprintf( post, "%d-%d-%d    %d:00:00+%d     %d   %f \n", S->date->year, S->date->month, S->date->day, S->date->hour, S->date->utc, S -> ID, S -> average);
}

void processWind( Station1* S, FILE* post ){
    fprintf( post, "%d    %f %f    %f %f\n", S -> ID, S -> average, S->average2, S->x, S->y);
}

void processHeight( Station1* S, FILE* post ){
    fprintf( post, "%d %f    %f %f\n", S -> ID, S -> average, S->x, S->y);
}

void processMoisture( Station1* S, FILE* post ){
    fprintf( post, "%d %f    %f %f\n", S -> ID, S -> max, S->x, S->y);
}

//=======================================================================

//=======================================================================
//Functions to go across the tree

void displayAvPerSt( Station1* S, FILE* post){
    if ( S != NULL ){
        displayAvPerSt( S -> ls, post);
        processAvPerSt( S, post );
        displayAvPerSt( S -> rs, post);
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

void displayListAvPerSt(FILE* post, Node* pNode){

    while(pNode != NULL){
        //printf("%.3f > ", pNode->elt);
        fprintf( post, "%d    %f   %f %f\n", pNode -> ID, pNode -> average, pNode -> min, pNode-> max);
        pNode = pNode->pNext;
    }
    
}


/*
void displayList(FILE* post, Node* pNode){

    while(pNode != NULL){
        //printf("%.3f > ", pNode->elt);
        fprintf(post, "%d %.3f %d-%d-%dT%d:00:00+%d:00 %f %f %f %f\n", pNode->ID, pNode->elt, pNode->date->year, pNode->date->month, pNode->date->day, pNode->date->hour, pNode->date->utc, pNode->x, pNode->y, pNode->e1, pNode->e2);
        pNode = pNode->pNext;
    }
    
}

void RdisplayList(FILE* post, Node* pNode){

    while(pNode != NULL){
        //printf("%.3f > ", pNode->elt);
        fprintf(post, "%d %.3f %d-%d-%dT%d:00:00+%d:00 %f %f %f %f\n", pNode->ID, pNode->elt, pNode->date->year, pNode->date->month, pNode->date->day, pNode->date->hour, pNode->date->utc, pNode->x, pNode->y, pNode->e1, pNode->e2);
        pNode = pNode->pBefore;
    }
    
}
*/