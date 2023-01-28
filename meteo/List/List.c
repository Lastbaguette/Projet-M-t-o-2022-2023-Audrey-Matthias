#include "../weathersort.h"

int searchList( Node* pHead, int ID ){

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

void searchEditList( Node* pHead, int ID, float v ){

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


void AvPStationList( List* L, int ID, float v, Date* D, float x, float y ){

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

void InsertListSt( List* L, Node* pHead, int ID, float v, Date* D, float x, float y ){                 //Inserts the read value into the doubly linked list in ascending order

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





/*

void addList(List* L, int ID, float value, Date* D, float x, float y, float e1, float e2){                 //Inserts the read value into the doubly linked list in ascending order

    Node* pHead = L -> pFirst;
    Node* pNew = createNode(ID, value , D , x , y, e1, e2); 

    if (pNew == NULL){
        exit(1);
    }

    if( (L->pFirst == NULL) && (L->pLast == NULL) ){
        L->pFirst = pNew;
        L->pLast = L->pFirst;
    }
    else if ( (pHead->elt >= pNew->elt) ){
        L->pFirst = pNew;
        pNew->pNext = pHead;
        pHead->pBefore = pNew;
        pHead = pNew;
    }   
    else if ( ( pHead->elt < pNew->elt ) ){

        while ((pHead->elt < pNew->elt) && (pHead->pNext != NULL)){
            pHead = pHead->pNext;   
        }

        if ((pHead-> pNext == NULL) && (pHead->elt < pNew->elt)){
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

void addListdate(List* L, int ID, float value, Date* D, float x, float y, float e1, float e2){                 //Inserts the read value into the doubly linked list in ascending order
    
    Node* pHead = L -> pFirst;
    Node* pNew = createNode(ID, value , D , x , y, e1, e2); 

    if (pNew == NULL){
        printf;
        exit(1);
    }
    else if( (L->pFirst == NULL) && (L->pLast == NULL) ){
        L->pFirst = pNew;
        L->pLast = L->pFirst;
    }
    else { 
        int comp = 0;
        comp = dateComp( D, L->pFirst->date );
        switch (comp) {
        case -1:
            L->pFirst = pNew;
            pNew->pNext = pHead;
            pHead->pBefore = pNew;
            pHead = pNew;
            break;
            
        default:
            while ((comp == 1) && (pHead->pNext != NULL)){
                pHead = pHead->pNext;
                comp = dateComp( D, pHead->date );
            }
            if ((pHead-> pNext == NULL) && (comp == 1)){
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
            break;
        }
    }
}

*/