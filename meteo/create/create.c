#include "../weathersort.h"

/*================================================================================================================================================

Element creating functions

================================================================================================================================================*/

/*=======================================================================

Tree and Tree element creation functions

/=======================================================================*/

Station1* createStation1 ( int ID, float v, Date* D, float x, float y){               //Function to create a station using one value to sort
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

    NewStation -> x = x;
    NewStation -> y = y;

    NewStation -> min2 = 0;
    NewStation -> max2 = 0;
    NewStation -> total2 = 0;
    NewStation -> average2 = 0;

    return NewStation;

}

Station1* createStation1bis( int ID, float v, float v2, float x, float y){            //Function to create a station using two values to sort
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

    NewStation -> x = x;
    NewStation -> y = y;

    return NewStation;

}



Station1* AddLeftSt ( Station1* S, int ID, float v, Date* D, float x, float y){         //Add left son (from one tree (here called a station) to another)
    
    Station1* NewS = createStation1 ( ID, v, D, x, y  );

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

Station1* AddRightSt ( Station1* S, int ID, float v, Date* D, float x, float y ){        //Add right son (from one tree (here called a station) to another)

    Station1* NewS = createStation1 ( ID, v, D, x, y  );

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


Station1* AddLeftSt2 ( Station1* S, Station1* NS ){                     //Add left son (from one tree element into a new one)

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

Station1* AddRightSt2 ( Station1* S, Station1* NS ){                    //Add right son (from one tree element into a new one)

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


Station1* AddLeftStbis  ( Station1* S, int ID, float v, float v2, float x, float y){        //Add left son (if it has two given values)

    Station1* NewS = createStation1bis ( ID, v, v2, x, y  );

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

Station1* AddRightStbis ( Station1* S, int ID, float v, float v2 , float x, float y){        //Add right son (if it has two given values)

    Station1* NewS = createStation1bis ( ID, v, v2, x, y );

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

//=======================================================================



/*=======================================================================

List and List node creation functions

/=======================================================================*/

List* Init(List* L, Node* elt){                //Initialize the beginning and end of the list
    L->pFirst = elt;
    L->pLast = L->pFirst;
    return L;
}

Node* createNode ( int ID, float v, Date* D, float x, float y ){        //Create a list node from one value
    Node* pNode = malloc( sizeof(Node) );
    if (pNode ==  NULL){
        exit(1);
    }
    pNode->ID = ID;

    pNode -> min = v;
    pNode -> max = v;
    pNode -> count = 1;
    pNode -> total = v;
    pNode -> average = v;

    pNode -> date = D;
    pNode->pBefore=NULL;
    pNode->pNext=NULL;

    pNode -> x = x;
    pNode -> y = y;

    pNode -> min2 = 0;
    pNode -> max2 = 0;
    pNode -> total2 = 0;
    pNode -> average2 = 0;

    return pNode;
}

Node* createNodebis ( int ID, float v, float v2, float x, float y ){        //Create a list node from two values
    Node* pNode = malloc( sizeof(Node) );
    if (pNode ==  NULL){
        exit(1);
    }
    pNode->ID = ID;

    pNode -> min = v;
    pNode -> max = v;
    pNode -> total = v;
    pNode -> average = v;

    pNode -> min2 = 0;
    pNode -> max2 = 0;
    pNode -> total2 = 0;
    pNode -> average2 = 0;

    pNode -> count = 1;

    pNode->pBefore=NULL;
    pNode->pNext=NULL;

    pNode -> x = x;
    pNode -> y = y;

    return pNode;
}

//=======================================================================