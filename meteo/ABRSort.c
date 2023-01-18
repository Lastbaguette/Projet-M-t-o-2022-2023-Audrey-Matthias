#include "weathersort.h"


int search( Station1* S , int ID ){

    if( S != NULL ){  
        if ( ID == S -> ID ){
            return 1;
        }
        if ( ( ID > S -> ID ) && ( S -> rs != NULL) ){
                return search( S->rs, ID );
        }
        else if ( ( ID < S -> ID ) && ( S -> ls != NULL)){
                return search( S->ls, ID );
        }
        else {
            return 0;
        }
    }

}

void searchEdit( Station1* S , int ID, float v){

    if( S != NULL ){  
        if ( ID == S -> ID ){
            if ( v < S -> min ){
                S -> min = v;
            } else if ( v > S -> max){
                S -> max = v;
            }
        S -> count = S -> count + 1;
        S -> total = S -> total + v;
        S -> average = S -> total/ S -> count;

        }
        else if ( ( ID > S -> ID ) && ( S -> rs != NULL) ){

            return searchEdit( S->rs, ID, v );
        }
        else if ( ( ID < S -> ID ) && ( S -> ls != NULL)){

            return searchEdit( S->ls, ID, v );
        }

    }
}

void searchEditVector( Station1* S , int ID, float v, float v2){

    if( S != NULL ){  
        if (ID == S->ID){
        S -> count = S -> count + 1;

        S -> total = S -> total + v;
        S -> average = S -> total/ S -> count;

        S -> total2 = S -> total2 + v2;
        S -> average2 = S -> total2/ S -> count;
        }
        if ( ( ID > S -> ID ) && ( S -> rs != NULL) ){
                return searchEditVector( S->rs, ID, v , v2);
        }
        else if ( ( ID < S -> ID ) && ( S -> ls != NULL)){
                return searchEditVector( S->ls, ID, v , v2);
        }

    }
}

void InsertABRStation ( Station1* S, int ID, float v, Date* D){
    if ( S == NULL ){
        exit(1);
    }
    else if ( ID < S->ID ){
        if (S->ls != NULL){
            InsertABRStation( S->ls, ID, v, D );
        }
        else{
           S = AddLeftSt(S, ID, v, D);
        }       
    }
    else if ( (ID > S->ID) ){
        if (S->rs != NULL){
            
            InsertABRStation ( S->rs, ID, v, D );
        }
        else{
            
            S = AddRightSt(S, ID, v, D);
            
        }
    }
}

void InsertPDateAllStABR( Station1* S, int ID, float v, Date* D ){

    if ( S == NULL ){
        exit(1);
    } 

    int comp = 0;
    comp = dateComp( D, S->date );

    switch (comp)
    {
    case -1:
        if (S->ls != NULL){
            InsertPDateAllStABR( S->ls, ID, v, D);
        }
        else{
            S = AddLeftSt(S , ID, v, D );
        }       
        break;
    case 1:
        if (S->rs != NULL){
            InsertPDateAllStABR( S->rs, ID, v, D );
        }
        else{
            S = AddRightSt(S, ID, v, D );
        }
        break;
    case 0:
        S -> count = S -> count + 1;
        S -> total = S -> total + v;
        S -> average = S -> total/ S -> count;
        break;
    default:
        break;
    }
}

void InsertPDatePStABR( Station1* S, int ID, float v, Date* D ){

    if ( S == NULL ){
        exit(1);
    } 

    int comp = 0;
    comp = dateComp( D, S->date );

    switch (comp)
    {
    case -1:
        if (S->ls != NULL){
            InsertPDatePStABR( S->ls, ID, v, D);
        }
        else{
            S = AddLeftSt(S , ID, v, D );
        }       
        break;
    case 1:
        if (S->rs != NULL){
            InsertPDatePStABR( S->rs, ID, v, D );
        }
        else{
            S = AddRightSt(S, ID, v, D );
        }
        break;
    case 0:
        if ( ID < S -> ID ){
            if (S->ls != NULL){
            InsertPDatePStABR( S->ls, ID, v, D);
            }
            else{
                S = AddLeftSt(S , ID, v, D );
            } 
        } else {
            if (S->rs != NULL){
            InsertPDatePStABR( S->rs, ID, v, D );
            }
            else{
                S = AddRightSt(S, ID, v, D );
            }
        }
        break;
    default:
        break;
    }
}

void InsertABRStationbis ( Station1* S, int ID, float v, float v2){
    if ( S == NULL ){
        exit(1);
    }
    else if ( ID < S->ID ){
        if (S->ls != NULL){
            InsertABRStationbis( S->ls, ID, v, v2);
        }
        else{
           S = AddLeftStbis(S, ID, v, v2);
        }       
    }
    else if ( (ID > S->ID) ){
        if (S->rs != NULL){
            InsertABRStationbis( S->rs, ID, v, v2);
        }
        else{
            S = AddRightStbis(S, ID, v, v2);
        }
    }
}

void InsertHeightABR(Station1* S, int ID, float v, Date* D){
    if ( S == NULL ){
        exit(1);
    }
    else if ( v < S->average ){
        if (S->ls != NULL){
            InsertHeightABR( S->ls, ID, v, D );
        }
        else{
           S = AddLeftSt(S, ID, v, D);
        }       
    }
    else if ( (v > S->average) ){

        if (S->rs != NULL){
            InsertHeightABR( S->rs, ID, v, D );
        }
        else{
            S = AddRightSt(S, ID, v, D);
        }
    }
}

Station1* InsertMoistureABR(Station1* S, Station1* NS){
    if(NS == NULL){
        NS = S;
    }
    else if (S != NULL){
        if ( S->max < NS->max ){
            if (NS->ls != NULL){
                InsertMoistureABR( S, NS->ls );
            }
            else{
                //NS = AddLeftSt2(S, NS);
                NS->ls = S;
            }       
        }
        else {
            if (NS->rs != NULL){
                InsertMoistureABR ( S, NS->rs );
            }
            else{
                //NS = AddRightSt2(S, NS);
                NS->rs = S;
            }
        }
    }

    return NS;
}

void AveragePStationABR( Station1* S, int ID, float v, Date* D){  

    if ( S == NULL ){
        exit(1);
    } 

    int T = 0;
    T = search( S, ID );

    if ( (T == 1) ){
        searchEdit(S, ID, v);
    } else {
        InsertABRStation( S, ID, v, D );
    }

}

void AveragePStationVectorABR( Station1* S, int ID, float v, float v2 ){  

    if ( S == NULL ){
        exit(1);
    } 

    int T = 0;
    T = search( S, ID );

    if ( (T == 1) ){
        searchEditVector(S, ID, v, v2);
    } else {
        InsertABRStationbis( S, ID, v, v2 );
    }

}

void SortHeight( Station1* S, int ID, float v, Date* D){  

    if ( S == NULL ){
        exit(1);
    } 

    int T = 0;
    T = search( S, ID );


    if ( (T != 1) ){
        InsertHeightABR(S, ID, v, D);
    }

}

Station1* SortMoisture( Station1* S, Station1* NS){ 

    if ( S != NULL ){
        Station1* temp = createStation1( S->ID, S->max, S->date );
        NS = SortMoisture(S->ls, NS);
        NS = InsertMoistureABR(temp, NS);
        NS = SortMoisture(S->rs, NS);
    }

    return NS;
}

