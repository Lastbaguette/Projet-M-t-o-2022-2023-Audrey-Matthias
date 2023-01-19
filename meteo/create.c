#include "weathersort.h"


Station1* createStation1 ( int ID, float v, Date* D){               //Function to create a station using one value to sort
    Station1* NewStation = malloc(sizeof(Station1));
    if (NewStation == NULL){
        exit(4);
    }
    
    NewStation -> ID = ID;
    NewStation -> min = v;
    NewStation -> max = v;
    NewStation -> count = 1;
    NewStation -> total = v;
    NewStation -> average = v;
    NewStation -> date = D;
    NewStation -> rs = NULL;
    NewStation -> ls = NULL;
    NewStation -> balance = 0;

    return NewStation;

}

Station1* createStation1bis( int ID, float v, float v2){            //Function to create a station using two values to sort
    Station1* NewStation = malloc(sizeof(Station1));
    if (NewStation == NULL){
        exit(4);
    }
        
    NewStation -> ID = ID;

    NewStation -> min = v;
    NewStation -> max = v;
    NewStation -> total = v;
    NewStation -> average = v;

    NewStation -> min2 = v2;
    NewStation -> max2 = v2;
    NewStation -> total2 = v2;
    NewStation -> average2 = v2;

    NewStation -> count = 1;

    NewStation -> rs = NULL;
    NewStation -> ls = NULL;
    NewStation -> balance = 0;

    return NewStation;

}


Station1* AddLeftSt ( Station1* S, int ID, float v, Date* D){         //Add left son
    
    Station1* NewS = createStation1 ( ID, v, D );

    if (S == NULL){
        S = NewS;
    }
    else if ( S->ls == NULL ){
        S->ls = NewS;
    }
    else {
        printf("cannot add here\n");
        exit(1);
    }
    
    return S;
}

Station1* AddRightSt ( Station1* S, int ID, float v, Date* D ){        //Add right son (from one tree (here called a station) to another)

    Station1* NewS = createStation1 ( ID, v, D );

    if (S == NULL){
        S = NewS;
    }
    else if ( S->rs == NULL ){
        S->rs = NewS;
    }
    else{
        printf("cannot add here\n");
        exit(1);
    }

    return S;
}

Station1* AddLeftSt2 ( Station1* S, Station1* NS ){                     //Add left son (from one tree (here called a station) to another)

    if (NS == NULL){
        NS = S;
    }
    else if ( NS->ls == NULL ){
        NS->ls = S;
    }
    else{
        printf("cannot add here\n");
        exit(1);
    }

    return NS;
}

Station1* AddRightSt2 ( Station1* S, Station1* NS ){                    //Add right son

    if (NS == NULL){
        NS = S;
    }
    else if ( NS->rs == NULL ){
        NS->rs = S;
    }
    else{
        printf("cannot add here\n");
        exit(1);
    }

    return NS;
}

Station1* AddLeftStbis  ( Station1* S, int ID, float v, float v2 ){        //Add left son (if it has two given values)

    Station1* NewS = createStation1bis ( ID, v, v2 );

    if (S == NULL){
        S = NewS;
    }
    else if ( S->ls == NULL ){
        S->ls = NewS;
    }
    else {
        printf("cannot add here\n");
        exit(1);
    }
    
    return S;

}

Station1* AddRightStbis ( Station1* S, int ID, float v, float v2 ){        //Add right son (if it has two given values)

    Station1* NewS = createStation1bis ( ID, v, v2 );

    if (S == NULL){
        S = NewS;
    }
    else if ( S->rs == NULL ){
        S->rs = NewS;
    }
    else {
        printf("cannot add here\n");
        exit(1);
    }
    
    return S;
}

