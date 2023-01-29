#include "../weathersort.h"


//=======================================================================
// Station and Balancing functions

int min( int a, int b ){
    if (a>b){ return b; }
    if (b>a){ return a; }

    return 0;
}

int max( int a, int b ){
    if (a>b){ return a; }
    if (b>a){ return b; }

    return 0;
}


Station1* LeftRotationSt( Station1* S ){
    Station1* pivot = malloc(sizeof(Station1));
    int eqA = 0, eqP = 0;

    pivot = S->rs;
    S->rs = pivot->ls;
    pivot->ls = S;

    eqA = S->balance;
    eqP = pivot->balance;

    S->balance = eqA - max( eqP, 0 ) - 1;
    pivot->balance = min( min(eqA-2, eqA+eqP-2), eqP-1 );
    S = pivot;
    return S; 
}

Station1* RightRotationSt( Station1* S ){
    Station1* pivot = malloc(sizeof(Station1));
    int eqA = 0, eqP = 0;

    pivot = S->ls;
    S->ls = pivot->rs;
    pivot->rs = S;

    eqA = S->balance;
    eqP = pivot->balance;

    S->balance = eqA - min( eqP, 0 ) + 1;
    pivot->balance = max( max(eqA+2, eqA+eqP+2), eqP+1 );
    S = pivot;
    return S; 
}

Station1* DoubleRightRotationSt ( Station1* S ){
    S->ls = LeftRotationSt(S->ls);
    return RightRotationSt(S);
}

Station1* DoubleLeftRotationSt ( Station1* S ){
    S->rs = RightRotationSt(S->rs);
    return LeftRotationSt(S);
}

Station1* StationBalance ( Station1* S ){
    if(S != NULL){
        if( S->balance >= 2 ){
            if( S->rs->balance >= 0 ){
                return LeftRotationSt(S);
            }
            else{
                return DoubleLeftRotationSt(S);
            }
        }

        if( S->balance <= -2 ){
            if( S->ls->balance <=0 ){
                return RightRotationSt(S);
            }
            else{
                return DoubleRightRotationSt(S);
            }
        }
    return S;
    }
    return S;
}

//=======================================================================

//=======================================================================
// Mode 1 Sort for temperature and pressure

Station1* InsertAVLStation ( Station1* S, int ID, float v, int* pH, Date* D, float x, float y){    //Inserts the read value into the tree with the AVL sorting method

    if ( S == NULL ){
        *pH = 1;
        return createStation1(ID, v, D, x, y);
    }
    else if ( ID < S->ID ){
        S->ls = InsertAVLStation(S->ls, ID, v, pH, D, x, y);
        *pH =  -(*pH);
    }
    else if (( ID > S->ID ) || ( ID == S->ID )){
        S->rs = InsertAVLStation(S->rs, ID, v, pH, D, x, y);
    }
    else {
        *pH = 0;
        return S;
    }

    if ( *pH != 0 ){

        S->balance = S->balance + *pH;
        S = StationBalance(S);
        if (S->balance == 0){
            *pH = 0;
        }
        else {
            *pH = 1;
        }    

    }
    return S; 
}

Station1* AveragePStationAVL( Station1* S, int ID, float v, int* pH, Date* D, float x, float y){  

    if ( S == NULL ){
        exit(1);
    } 

    int T = 0;
    T = search( S, ID );

    if ( (T == 1) ){
        searchEdit(S, ID, v);
    } else {
        S = InsertAVLStation( S, ID, v, pH, D, x, y );
    }

    return S;

}

//=======================================================================

//=======================================================================
// Mode 2 Sort for temperature and pressure

Station1* InsertPDateAllStAVL( Station1* S, int ID, float v, int* pH, Date* D, float x, float y ){

    if ( S == NULL ){
        *pH = 1;
        return createStation1(ID, v, D, x, y);
    }

    int comp = 0;
    comp = dateComp( D, S->date );

    if ( comp == -1 ){
        S->ls = InsertPDateAllStAVL(S->ls, ID, v, pH, D, x, y);
        *pH =  -*pH;
    }
    else if ( comp == 1 ){
        S->rs = InsertPDateAllStAVL(S->rs, ID, v, pH, D, x, y);
    }
    else if ( comp == 0 ){
        S -> count = S -> count + 1;
        S -> total = S -> total + v;
        S -> average = S -> total/ S -> count;
        *pH = 0;
        return S;
    }

    if ( *pH != 0 ){
        S->balance = S->balance + *pH;
        S = StationBalance(S);
        if (S->balance == 0){
            *pH = 0;
        }
        else {
            *pH = 1;
        }    
    }

    return S; 
}

//=======================================================================

//=======================================================================
// Mode 3 Sort for temperature and pressure

Station1* InsertPDatePStAVL( Station1* S, int ID, float v, int* pH, Date* D, float x, float y ){

    if ( S == NULL ){
        *pH = 1;
        return createStation1(ID, v, D, x, y);
    } 

    int comp = 0;
    comp = dateComp( D, S->date );


    if ( comp == -1 ){
        S->ls = InsertPDatePStAVL(S->ls, ID, v, pH, D, x, y);
        *pH =  -*pH;
    }
    else if ( comp == 1 ){
        S->rs = InsertPDatePStAVL(S->rs, ID, v, pH, D, x, y);
    }
    else if ( comp == 0 ){
        if ( ID < S -> ID ){
            S->ls = InsertPDatePStAVL( S->ls, ID, v, pH, D, x, y);
            *pH =  -*pH;
        } else {
            S->rs = InsertPDatePStAVL( S->rs, ID, v, pH, D, x, y);
        }
    }

    if ( *pH != 0 ){

        S->balance = S->balance + *pH;
        S = StationBalance(S);
        if (S->balance == 0){
            *pH = 0;
        }
        else {
            *pH = 1;
        }    

    }
    return S; 
}

//=======================================================================

//=======================================================================
// Wind Sort

Station1* InsertAVLStationbis ( Station1* S, int ID, float v, float v2, int* pH, float x, float y){

    if ( S == NULL ){
        *pH = 1;
        return createStation1bis(ID, v, v2, x, y);
    } 
    else if ( ID < S->ID ){
        S->ls = InsertAVLStationbis( S->ls, ID, v, v2, pH, x, y);  
        *pH =  -(*pH);   
    }
    else if (( ID > S->ID ) || ( ID == S->ID )){
        S->rs = InsertAVLStationbis( S->rs, ID, v, v2, pH, x, y);
    } 
    else {
        *pH = 0;
        return S;
    }

    if ( *pH != 0 ){
        S->balance = S->balance + *pH;
        S = StationBalance(S);
        if (S->balance == 0){
            *pH = 0;
        }
        else {
            *pH = 1;
        }    
    }
    return S; 
}

Station1* AveragePStationVectorAVL( Station1* S, int ID, float v, float v2 ,int* pH, float x, float y){  

    int T = 0;
    T = search( S, ID );

    if ( (T == 1) ){
        searchEditVector(S, ID, v, v2);
    } else {
        S = InsertAVLStationbis( S, ID, v, v2, pH, x, y );
    }

    return S;

}

//=======================================================================

//=======================================================================
// Height Sort

Station1* InsertHeightAVL(Station1* S, Station1* NS, int* pH){
    if(NS == NULL){
        *pH = 1;
        return NS = S;
    }
    else if (S != NULL){
        if ( S->average < NS->average ){
            NS->ls = InsertHeightAVL( S, NS->ls, pH );
            *pH = -*pH;
        }
        else {
            NS->rs = InsertHeightAVL( S, NS->rs, pH );
        }
    }

    if(*pH != 0){
        NS-> balance = NS->balance + *pH;
        NS = StationBalance(NS);
        if ( NS -> balance == 0 ){
            *pH = 0;
        } else {
            *pH = 1;
        }
    }

    return NS;
}

Station1* SortHeight1AVL( Station1* S, int ID, float v ,int* pH, Date* D, float x, float y){  

    if ( S == NULL ){
        exit(1);
    } 

    int T = 0;
    T = search( S, ID );


    if ( (T != 1) ){
        S = InsertAVLStation( S, ID, v, pH, D, x, y );
    }
     
    return S;

}

Station1* SortHeight2AVL( Station1* S, Station1* NS, int* pH){ 

    if ( S != NULL ){
        Station1* temp = createStation1( S->ID, S->average, S->date, S->x, S->y );
        NS = SortHeight2AVL(S->ls, NS, pH);
        NS = InsertHeightAVL(temp, NS, pH);
        NS = SortHeight2AVL(S->rs, NS, pH);
    }

    return NS;
}

//=======================================================================

//=======================================================================
// Moisture Sort

Station1* InsertMoistureAVL(Station1* S, Station1* NS, int* pH){

    if(NS == NULL){
        *pH = 1;
        NS = S;
    }
    else if (S != NULL){
        if ( S->max < NS->max ){
            NS->ls = InsertMoistureAVL( S, NS->ls, pH );
            *pH = -*pH;
        }
        else {
            NS->rs = InsertMoistureAVL( S, NS->rs, pH );
        }
    }

    if(*pH != 0){
        NS-> balance = NS->balance + *pH;
        NS = StationBalance(NS);
        if ( NS -> balance == 0 ){
            *pH = 0;
        } else {
            *pH = 1;
        }
    }

    return NS;
}

Station1* SortMoistureAVL( Station1* S, Station1* NS, int* pH){ 

    if ( S != NULL ){
        Station1* temp = createStation1( S->ID, S->max, S->date, S->x, S->y );
        NS = SortMoistureAVL(S->ls, NS, pH);
        NS = InsertMoistureAVL(temp, NS, pH);
        NS = SortMoistureAVL(S->rs, NS, pH);
    }

    return NS;
}

//=======================================================================
