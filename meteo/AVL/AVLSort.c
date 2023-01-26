#include "../weathersort.h"

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

    pivot = S->rs;
    pivot->rs = pivot->ls;
    pivot->ls = S;

    return pivot; 
}

Station1* RightRotationSt( Station1* S ){
    Station1* pivot = malloc(sizeof(Station1));

    pivot = S->ls;
    S->ls = pivot->rs;
    pivot->rs = S;

    return pivot; 
}


Station1* correct( Station1* S ){
    if ( S != NULL ){    
    if ( S->balance < -1 || S->balance > 1 ){  
        if ( S->balance < -1 ) { 
            S = RightRotationSt(S); 
            return S;
            }
        else if ( S->balance > 1 ) { 
            S = LeftRotationSt(S); 
            return S;
         }
    }
    S->ls = correct(S->ls);
    S->rs = correct(S->rs);

    return S;
    }
}

int TestBalance(Station1* S){
    if ( S == NULL ){  return 0 ;  }
    if ( S->balance < -1 || S->balance > 1 ){  return 1 ;  }
    return TestBalance( S->ls ) || TestBalance( S->rs );
}


int Balance (Station1* S){
    if (S != NULL){
        int rb = Balance (S->rs);
        int lb = Balance (S->ls);
        S->balance = rb - lb ;
        return ( rb > lb ? rb : lb ) + 1;
    } else {
        return 0;
    }
}

Station1* Test( Station1* S ){
    Balance(S);
    while (TestBalance(S)){         //while Station's balance is < -1 or > 1
        S = correct(S);
        Balance(S);
        printf("%d %d 1 \n", S->balance, S->ID);
    }
    return S;
}

Station1* InsertAVLStation ( Station1* S, int ID, float v, Date* D, float x, float y){    //Inserts the read value into the tree with the AVL sorting method

    if ( S == NULL ){
        return NULL;
    }
    else if ( ID < S->ID ){
        if (S->ls != NULL){
            S->ls = InsertAVLStation( S->ls, ID, v, D, x, y );
        }
        else{
           S = AddLeftSt(S, ID, v, D, x, y);
        }       
    }
    else if ( (ID > S->ID) ){
        if (S->rs != NULL){   
            S->rs = InsertAVLStation ( S->rs, ID, v, D, x, y );
        }
        else{
            S = AddRightSt(S, ID, v, D, x, y); 
        }
    }

    S = Test(S);
    return S; 
}


Station1* AveragePStationAVL( Station1* S, int ID, float v, int* pH, Date* D, float x, float y){  

    if ( S == NULL ){
        exit(1);
    } 

    int T = 0;
    T = search( S, ID );
    printf("%d      %d %d\n", T, S->ID, ID);

    if ( (T == 1) ){
        searchEdit(S, ID, v);
    } else {
        S = InsertAVLStation( S, ID, v, D, x, y );
    }

    return S;

}

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



    return S; 
}

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

    return S; 
}

Station1* InsertAVLStationbis ( Station1* S, int ID, float v, float v2, int* pH, float x, float y){
    if ( S == NULL ){
        *pH = 1;
        return createStation1bis(ID, v, v2, x, y);
    } 
    else if ( ID < S->ID ){
        S->ls = InsertAVLStationbis( S->ls, ID, v, v2, pH, x, y);  
        *pH =  -*pH;   
    }
    else if ( (ID >= S->ID) ){
        S->rs = InsertAVLStationbis( S->rs, ID, v, v2, pH, x, y);
    }

    return S; 
}

Station1* AveragePStationVectorAVL( Station1* S, int ID, float v, float v2 ,int* pH, float x, float y){  

    if ( S == NULL ){
        *pH = 1;
        return createStation1bis(ID, v, v2, x, y);
    } 

    int T = 0;
    T = search( S, ID );

    if ( (T == 1) ){
        searchEditVector(S, ID, v, v2);
    } else {
        S = InsertAVLStationbis( S, ID, v, v2, pH, x, y );
    }

    return S;

}

Station1* InsertHeightAVL(Station1* S, int ID, float v, Date* D, int* pH, float x, float y){
    if ( S == NULL ){
        *pH = 1;
        return createStation1(ID, v, D, x, y);
    }
    else if ( v < S->average ){
        S-> ls = InsertHeightAVL( S->ls, ID, v, D, pH, x, y ); 
        *pH = -*pH;
    }
    else if ( (v >= S->average) ){
        S ->rs = InsertHeightAVL( S->rs, ID, v, D, pH, x, y ); 
    }

    return S;
}

Station1* SortHeightAVL( Station1* S, int ID, float v, Date* D, int* pH, float x, float y){  

    if ( S == NULL ){
        exit(1);
    } 

    int T = 0;
    T = search( S, ID );

    if ( (T != 1) ){
        S = InsertHeightAVL(S, ID, v, D, pH, x, y);
    }

    return S;
}

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
