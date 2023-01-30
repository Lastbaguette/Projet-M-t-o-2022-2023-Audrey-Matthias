#include "../weathersort.h"

/*================================================================================================================================================

ABR method sorting functions

================================================================================================================================================*/

//=======================================================================
// Searching and average calculation (called editing) functions

int search( Station1* S , int ID ){             //Searching if an element with given ID exists. Will return 1 if yes, otherwise will return 0

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

void searchEdit( Station1* S , int ID, float v){             //Searching for an element with given ID to edit it (for one value). 

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

void searchEditVector( Station1* S , int ID, float v, float v2){             //Searching for an element with given ID to edit it (for two values). 

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

//=======================================================================

//=======================================================================
// Mode 1 Sort for temperature and pressure

void InsertABRStation ( Station1* S, int ID, float v, Date* D, float x, float y){               //Will travel across the tree to create new element at its given place. (Sorting by ID)
    if ( S == NULL ){
        exit(1);
    }
    else if ( ID < S->ID ){
        if (S->ls != NULL){
            InsertABRStation( S->ls, ID, v, D, x, y );
        }
        else{
           S = AddLeftSt(S, ID, v, D, x, y);
        }       
    }
    else if ( (ID >= S->ID) ){
        if (S->rs != NULL){
            InsertABRStation ( S->rs, ID, v, D, x, y );
        }
        else{
            S = AddRightSt(S, ID, v, D, x, y);
        }
    }
}

void AveragePStationABR( Station1* S, int ID, float v, Date* D, float x, float y){              //Search if given ID exists. If yes will edit it, else will create a new element with given values 

    if ( S == NULL ){
        exit(1);
    } 

    int T = 0;
    T = search( S, ID );

    if ( (T == 1) ){
        searchEdit(S, ID, v);
    } else {
        InsertABRStation( S, ID, v, D, x, y );
    }

}

//=======================================================================

//=======================================================================
// Mode 2 Sort for temperature and pressure

Station1* InsertPDateAllStABR( Station1* S, int ID, float v, Date* D, float x, float y ){       //Will compare the current date and the new element's date. If the date is the same value will be edited, otherwise new element will be created.

    if ( S == NULL ){
        S = createStation1(ID, v, D, x, y);
        return S;
    } 

    int comp = 0;
    comp = dateComp( D, S->date );

    switch (comp)
    {
    case -1:
        S->ls = InsertPDateAllStABR( S->ls, ID, v, D, x, y);    
        break;
    case 1:
        S->rs = InsertPDateAllStABR( S->rs, ID, v, D, x, y );
        break;
    case 0:
        (S -> count) = ((S -> count) + 1);
        (S -> total) = ((S -> total) + v);
        (S -> average) = (( S -> total)/ (S -> count));
        break;
    default:
        break;
    }

    return S;
}

//=======================================================================

//=======================================================================
// Mode 3 Sort for temperature and pressure

void InsertPDatePStABR( Station1* S, int ID, float v, Date* D, float x, float y ){              //Will compare the current date and the new element's date. If the date is the same, IDs will be compared and the new element will be placed by rising ID order. 

    if ( S == NULL ){
        exit(1);
    } 

    int comp = 0;
    comp = dateComp( D, S->date );

    switch (comp)
    {
    case -1:
        if (S->ls != NULL){
            InsertPDatePStABR( S->ls, ID, v, D, x, y);
        }
        else{
            S = AddLeftSt(S , ID, v, D, x, y );
        }       
        break;
    case 1:
        if (S->rs != NULL){
            InsertPDatePStABR( S->rs, ID, v, D, x, y );
        }
        else{
            S = AddRightSt(S, ID, v, D, x, y );
        }
        break;
    case 0:
        if ( ID < S -> ID ){
            if (S->ls != NULL){
            InsertPDatePStABR( S->ls, ID, v, D, x, y);
            }
            else{
                S = AddLeftSt(S , ID, v, D, x, y );
            } 
        } else {
            if (S->rs != NULL){
            InsertPDatePStABR( S->rs, ID, v, D, x, y );
            }
            else{
                S = AddRightSt(S, ID, v, D, x, y );
            }
        }
        break;
    default:
        break;
    }
}

//=======================================================================

//=======================================================================
// Wind Sort

void InsertABRStationbis ( Station1* S, int ID, float v, float v2, float x, float y){           //Will travel across the tree to create new element at its given place. (Sorting by ID)
    if ( S == NULL ){
        exit(1);
    }
    else if ( ID < S->ID ){
        if (S->ls != NULL){
            InsertABRStationbis( S->ls, ID, v, v2, x, y);
        }
        else{
           S = AddLeftStbis(S, ID, v, v2, x, y);
        }       
    }
    else if ( (ID > S->ID) ){
        if (S->rs != NULL){
            InsertABRStationbis( S->rs, ID, v, v2, x, y);
        }
        else{
            S = AddRightStbis(S, ID, v, v2, x, y);
        }
    }
}

void AveragePStationVectorABR( Station1* S, int ID, float v, float v2, float x, float y ){      //Search if given ID exists. If yes will edit it else will create a new element with given values

    if ( S == NULL ){
        exit(1);
    } 

    int T = 0;
    T = search( S, ID );

    if ( (T == 1) ){
        searchEditVector(S, ID, v, v2);
    } else {
        InsertABRStationbis( S, ID, v, v2, x, y);
    }

}

//=======================================================================

//=======================================================================
// Height Sort

Station1* InsertHeightABR(Station1* S, Station1* NS){               //Will travel across the tree to create new element at its given place. (Sorting by value)
    if(NS == NULL){
        NS = S;
    }
    else if (S != NULL){
        if ( S->average < NS->average ){
            if (NS->ls != NULL){
                InsertHeightABR( S, NS->ls );
            }
            else{
                //NS = AddLeftSt2(S, NS);
                NS->ls = S;
            }       
        }
        else {
            if (NS->rs != NULL){
                InsertHeightABR( S, NS->rs );
            }
            else{
                //NS = AddRightSt2(S, NS);
                NS->rs = S;
            }
        }
    }

    return NS;
}

void SortHeight1( Station1* S, int ID, float v, Date* D, float x, float y){                 //Search if given ID exists. Will only create a new element if new ID doesn't exists. Elements will be sorted per ID first.

    if ( S == NULL ){
        exit(1);
    } 

    int T = 0;
    T = search( S, ID );


    if ( (T != 1) ){
        InsertABRStation( S, ID, v, D, x, y );
    }

}

Station1* SortHeight2( Station1* S, Station1* NS){                  //Will read the previously created tree's element one by one to create a new tree sorted by value (Height)

    if ( S != NULL ){
        Station1* temp = createStation1( S->ID, S->max, S->date, S->x, S->y );
        NS = SortHeight2(S->ls, NS);
        NS = InsertHeightABR(temp, NS);
        NS = SortHeight2(S->rs, NS);
    }

    return NS;
}

//=======================================================================

//=======================================================================
// Moisture Sort

Station1* InsertMoistureABR(Station1* S, Station1* NS){             //Will travel across the tree to create new element at its given place. (Sorting by max value)
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

Station1* SortMoisture( Station1* S, Station1* NS){                 //Will read the previously created tree's element one by one to create a new tree sorted by max value (Moisture)

    if ( S != NULL ){
        Station1* temp = createStation1( S->ID, S->max, S->date, S->x, S->y );
        NS = SortMoisture(S->ls, NS);
        NS = InsertMoistureABR(temp, NS);
        NS = SortMoisture(S->rs, NS);
    }

    return NS;
}

//=======================================================================
