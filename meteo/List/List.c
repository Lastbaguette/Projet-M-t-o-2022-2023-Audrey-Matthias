#include "../weathersort.h"

/*================================================================================================================================================

Doubly linked list method sorting functions

================================================================================================================================================*/

//=======================================================================

// Searching and average calculation (called editing) functions

int searchList( Node* pHead, int ID ){              //Searching if an element with given ID exists. Will return 1 if yes, otherwise will return 0

    if( pHead != NULL ){  

        if ( ID == pHead -> ID ){
            return 1;
        }
        if ( ( ID > pHead -> ID ) && ( pHead->pNext != NULL) ){
            pHead = pHead->pNext;
            return searchList( pHead, ID );
        }
        else {
            return 0;
        }
    }

}

void searchEditList( Node* pHead, int ID, float v ){            //Searching for an element with given ID to edit it (for one value).

    if( pHead != NULL ){  

        if ( ID == pHead -> ID ){
            if ( v < pHead -> min ){
                pHead -> min = v;
            } else if ( v > pHead -> max){
                pHead -> max = v;
            }
        pHead -> count = pHead -> count + 1;
        pHead -> total = pHead -> total + v;
        pHead -> average = pHead -> total/ pHead -> count;

        }
        if ( ( ID > pHead -> ID ) && ( pHead->pNext != NULL) ){
            pHead = pHead->pNext;
            return searchEditList( pHead, ID, v );
        }
    }
}

void searchEditListBis( Node* pHead, int ID, float v, float v2){                //Searching for an element with given ID to edit it (for two values).

    if( pHead != NULL ){  

        if ( ID == pHead -> ID ){

            pHead -> count = pHead -> count + 1;
            
            pHead -> total = pHead -> total + cos(v)*v2;
            pHead -> total2 = pHead -> total2 + sin(v)*v2;
            pHead -> average = pHead -> total/ pHead -> count;
            pHead -> average2 = pHead -> total2/ pHead -> count;

        }
        if ( ( ID > pHead -> ID ) && ( pHead->pNext != NULL) ){
            pHead = pHead->pNext;
            return searchEditList( pHead, ID, v );
        }
    }
}

//=======================================================================

// Mode 1 Sort for temperature and pressure

void AvPStationList( List* L, int ID, float v, Date* D, float x, float y ){             //Will travel across the list to create new element at its given place. (Sorting by ID)

    if ( L == NULL ){ 
        exit(1);
    } 
    Node* pHead = L -> pFirst;
    int T = 0;
    T = searchList( pHead, ID );

    if ( (T == 1) ){
        searchEditList(pHead, ID, v);
    } else {
        InsertListSt(L, pHead, ID, v, D, x, y );
    }

}

void InsertListSt( List* L, Node* pHead, int ID, float v, Date* D, float x, float y ){                 //Search if given ID exists. If yes will edit it, else will create a new element with given values 

    Node* pNew = createNode(ID, v , D , x , y); 

    if (pNew == NULL){
        exit(1);
    }

    else if ( (pHead->ID >= pNew->ID) ){
        L->pFirst = pNew;
        pNew->pNext = pHead;
        pHead->pBefore = pNew;
        pHead = pNew;
    }   
    else if ( ( pHead->ID < pNew->ID ) ){

        while ((pHead->ID < pNew->ID) && (pHead->pNext != NULL)){
            pHead = pHead->pNext;   
        }

        if ((pHead-> pNext == NULL) && (pHead->ID < pNew->ID)){
            pNew -> pBefore = pHead;
            pHead -> pNext = pNew;
            L -> pLast = pNew;
        }
        else {
            pNew -> pNext = pHead;
            pNew -> pBefore = pHead -> pBefore;
            pHead -> pBefore -> pNext = pNew;
            pHead -> pBefore = pNew;
        }
    }
}

//=======================================================================

// Mode 2 Sort for temperature and pressure

void InsertPerDateAllStList(List* L, Node* pHead, int ID, float v, Date* D, float x, float y){                 //Will compare the current date and the new element's date. If the date is the same value will be edited, otherwise new element will be created.

    Node* pNew = createNode(ID, v , D , x , y); 

    if (pNew == NULL){
        exit(1);
    }

    int comp = 0;
    comp = dateComp( D, pHead->date );

    switch (comp)
    {
    case 0:
        (pHead -> count) = ((pHead -> count) + 1);
        (pHead -> total) = ((pHead -> total) + v);
        (pHead -> average) = (( pHead -> total)/ (pHead -> count));
        break;

    case 1:
        if( pHead -> pNext != NULL ){
            InsertPerDateAllStList(L, pHead->pNext, ID, v, D, x, y );
        } 
        else if (pHead-> pNext == NULL){
            pNew -> pBefore = pHead;
            pHead -> pNext = pNew;
            L -> pLast = pNew;
        }
        break;
    
    case -1:
        if  ( pHead->pBefore == NULL ){
            L->pFirst = pNew;
            pNew->pNext = pHead;
            pHead->pBefore = pNew;
            pHead = pNew;
        } else {
            pNew->pBefore = pHead->pBefore;
            pNew->pNext = pHead;
            pHead->pBefore->pNext = pNew;
            pHead->pBefore = pNew;
        }
        break;    
    
    default:
        break;
    }
    
}

//=======================================================================

// Mode 3 Sort for temperature and pressure

void InsertPerDatePerStList(List* L, Node* pHead, int ID, float v, Date* D, float x, float y){                 //Will compare the current date and the new element's date. If the date is the same, IDs will be compared and the new element will be placed by rising ID order.

    Node* pNew = createNode(ID, v , D , x , y); 

    if (pNew == NULL){
        exit(1);
    }

    int comp = 0;
    comp = dateComp( D, pHead->date );

    switch (comp)
    {
    case 0:
        if ( pHead->ID >= ID ){
            if  ( pHead->pBefore == NULL ){
                L->pFirst = pNew;
                pNew->pNext = pHead;
                pHead->pBefore = pNew;
                pHead = pNew;
            } else {
                pNew->pBefore = pHead->pBefore;
                pNew->pNext = pHead;
                pHead->pBefore->pNext = pNew;
                pHead->pBefore = pNew;
            }
        } else {
            if( pHead -> pNext != NULL ){
                InsertPerDatePerStList(L, pHead->pNext, ID, v, D, x, y );
            } 
            else if (pHead-> pNext == NULL){
                pNew -> pBefore = pHead;
                pHead -> pNext = pNew;
                L -> pLast = pNew;
            }
        }
        break;

    case 1:
        if( pHead -> pNext != NULL ){
            InsertPerDatePerStList(L, pHead->pNext, ID, v, D, x, y );
        } 
        else if (pHead-> pNext == NULL){
            pNew -> pBefore = pHead;
            pHead -> pNext = pNew;
            L -> pLast = pNew;
        }
        break;
    
    case -1:
        if  ( pHead->pBefore == NULL ){
            L->pFirst = pNew;
            pNew->pNext = pHead;
            pHead->pBefore = pNew;
            pHead = pNew;
        } else {
            pNew->pBefore = pHead->pBefore;
            pNew->pNext = pHead;
            pHead->pBefore->pNext = pNew;
            pHead->pBefore = pNew;
        }
        break;    
    
    default:
        break;
    }
    
}

//=======================================================================

// Wind Sort

void AvPStationVectorList( List* L, int ID, float v, float v2, float x, float y ){                  //Will travel across the list to create new element at its given place. (Sorting by ID)

    if ( L == NULL ){ 
        exit(1);
    } 
    Node* pHead = L -> pFirst;
    int T = 0;
    T = searchList( pHead, ID );

    if ( (T == 1) ){
        searchEditListBis(pHead, ID, v, v2);
    } else {
        InsertListStBis(L, pHead, ID, v, v2, x, y );
    }

}

void InsertListStBis( List* L, Node* pHead, int ID, float v, float v2, float x, float y ){                 //Search if given ID exists. If yes will edit it else will create a new element with given values

    Node* pNew = createNodebis(ID, v , v2 , x , y); 

    if (pNew == NULL){
        exit(1);
    }

    else if ( (pHead->ID >= pNew->ID) ){
        L->pFirst = pNew;
        pNew->pNext = pHead;
        pHead->pBefore = pNew;
        pHead = pNew;
    }   
    else if ( ( pHead->ID < pNew->ID ) ){

        while ((pHead->ID < pNew->ID) && (pHead->pNext != NULL)){
            pHead = pHead->pNext;   
        }

        if ((pHead-> pNext == NULL) && (pHead->ID < pNew->ID)){
            pNew -> pBefore = pHead;
            pHead -> pNext = pNew;
            L -> pLast = pNew;
        }
        else {
            pNew -> pNext = pHead;
            pNew -> pBefore = pHead -> pBefore;
            pHead -> pBefore -> pNext = pNew;
            pHead -> pBefore = pNew;
        }
    }
}

//=======================================================================

// Height Sort

List* InsertHeightList( Node* pNew, List* L2 ){             //Will travel across the list to create new element at its given place. (Sorting by value)
    if( L2->pFirst == NULL ){
        return L2 = Init(L2, pNew);
    } 
    else {
        Node* pHead = L2->pFirst;

        if (pNew == NULL){
            exit(1);
        }

        else if ( (pHead->average >= pNew->average) ){
            L2->pFirst = pNew;
            pNew->pNext = pHead;
            pHead->pBefore = pNew;
            pHead = pNew;
        }   
        else if ( ( pHead->average < pNew->average ) ){

            while ((pHead->average < pNew->average) && (pHead->pNext != NULL)){
                pHead = pHead->pNext;   
            }

            if ((pHead-> pNext == NULL) && (pHead->average < pNew->average)){
                pNew -> pBefore = pHead;
                pHead -> pNext = pNew;
                L2 -> pLast = pNew;
            }
            else {
                pNew -> pNext = pHead;
                pNew -> pBefore = pHead -> pBefore;
                pHead -> pBefore -> pNext = pNew;
                pHead -> pBefore = pNew;
            }
        }
    }

    return L2;
}

void SortHeight1List( List* L, int ID, float v, Date* D, float x, float y ){            //Search if given ID exists. Will only create a new element if new ID doesn't exists. Elements will be sorted per ID first.

    if ( L == NULL ){ 
        exit(1);
    } 
    Node* pHead = L -> pFirst;
    int T = 0;
    T = searchList( pHead, ID );

    if ( (T != 1) ){
        InsertListSt(L, pHead, ID, v, D, x, y );
    }

}

List* SortHeight2List( Node* pHead, List* L2 ){             //Will read the previously created list's element one by one to create a new list sorted by value (Height)

    if ( pHead != NULL ){
        Node* temp = createNode( pHead->ID, pHead->max, pHead->date, pHead->x, pHead->y );
        L2 = InsertHeightList(temp, L2);
        L2 = SortHeight2List(pHead->pNext, L2);
    }

    return L2;
}

//=======================================================================

// Moisture Sort

List* InsertMoistureList( Node* pNew, List* L2 ){           //Will travel across the list to create new element at its given place. (Sorting by max value)
    if( L2->pFirst == NULL ){
        return L2 = Init(L2, pNew);
    } 
    else {
        Node* pHead = L2->pFirst;

        if (pNew == NULL){
            exit(1);
        }

        else if ( (pHead->max >= pNew->max) ){
            L2->pFirst = pNew;
            pNew->pNext = pHead;
            pHead->pBefore = pNew;
            pHead = pNew;
        }   
        else if ( ( pHead->max < pNew->max ) ){

            while ((pHead->max < pNew->max) && (pHead->pNext != NULL)){
                pHead = pHead->pNext;   
            }

            if ((pHead-> pNext == NULL) && (pHead->max < pNew->max)){
                pNew -> pBefore = pHead;
                pHead -> pNext = pNew;
                L2 -> pLast = pNew;
            }
            else {
                pNew -> pNext = pHead;
                pNew -> pBefore = pHead -> pBefore;
                pHead -> pBefore -> pNext = pNew;
                pHead -> pBefore = pNew;
            }
        }
    }

    return L2;
}

List* SortMoistureList( Node* pHead, List* L2 ){            //Will read the previously created list's element one by one to create a new list sorted by max value (Moisture)

    if ( pHead != NULL ){
        Node* temp = createNode( pHead->ID, pHead->max, pHead->date, pHead->x, pHead->y );
        L2 = InsertMoistureList(temp, L2);
        L2 = SortMoistureList(pHead->pNext, L2);
    }

    return L2;
}

//=======================================================================
