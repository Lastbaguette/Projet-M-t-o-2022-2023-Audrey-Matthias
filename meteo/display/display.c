#include "../weathersort.h"

void processAvPerSt( Station1* S, FILE* post ){
    fprintf( post, "%d %f %f %f\n", S -> ID, S -> average, S -> min, S-> max);
}

void processAvPerDateAllSt( Station1* S, FILE* post ){
    fprintf( post, "%d-%d-%d    %d:00:00+%d     %f \n", S->date->year, S->date->month, S->date->day, S->date->hour, S->date->utc, S -> average);
}

void processPerDatePSt( Station1* S, FILE* post ){
    fprintf( post, "%d-%d-%d    %d:00:00+%d     %d   %f \n", S->date->year, S->date->month, S->date->day, S->date->hour, S->date->utc, S -> ID, S -> average);
}

void processWind( Station1* S, FILE* post ){
    fprintf( post, "%d %d %f %f %f %f\n", S -> ID,S ->count, S -> average, S->average2, S->x, S->y);
}

void processHeight( Station1* S, FILE* post ){
    fprintf( post, "%d %f %f %f\n", S -> ID, S -> max, S->x, S->y);
}

void processMoisture( Station1* S, FILE* post ){
    fprintf( post, "%d %f %f %f\n", S -> ID, S -> max, S->x, S->y);
}

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

void displayWind( Station1* S, FILE* post){
    if ( S != NULL ){
        displayWind( S -> ls, post);
        processWind( S, post );
        displayWind( S -> rs, post);
    }
}