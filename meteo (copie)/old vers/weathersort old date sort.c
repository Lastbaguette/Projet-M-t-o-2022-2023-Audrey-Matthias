#include "weathersort.h"

/*============================================================
ERRORS: - 1 : Incorrect arguments
        - 2 : Pre-Sorting file issues
        - 3 : Post-Sorting file issues
        - 4 : Others
=============================================================*/

/*============================================================
File existence test function
=============================================================*/

int TestFileExist ( char* FN ){                 //Function to check if file exists
    int exist = 0;
    FILE* F = fopen( FN ,"r" );

    if ( F != NULL ){
        exist = 1;
        fclose(F);
    }
    return exist;
}

/*============================================================
Doubly linked list functions
=============================================================*/

void Init(List* L){
    L->pFirst = NULL;
    L->pLast = NULL;
}

Node* createNode ( int ID, float value, Date* D, float x, float y, float extra1, float extra2){
    Node* pNode = malloc( sizeof(Node) );
    if (pNode ==  NULL){
        exit(1);
    }
    pNode->ID = ID;
    pNode->elt=value;
    pNode->date = D;
    pNode->x = x;
    pNode->y = y;
    pNode->e1 = extra1;
    pNode->e2 = extra2;
    pNode->pBefore=NULL;
    pNode->pNext=NULL;

    return pNode;
}

void displayList(FILE* post, Node* pNode){
    if (pNode == NULL){
        printf("end\n");
    }
    while(pNode != NULL){
        //printf("%.3f > ", pNode->elt);
        fprintf(post, "%d %.3f %d-%d-%dT%d:00:00+%d:00 %f %f %f %f\n", pNode->ID, pNode->elt, pNode->date->year, pNode->date->month, pNode->date->day, pNode->date->hour, pNode->date->utc, pNode->x, pNode->y, pNode->e1, pNode->e2);
        pNode = pNode->pNext;
    }
    
}

void RdisplayList(FILE* post, Node* pNode){
    if (pNode == NULL){
        printf("end\n");
    }
    while(pNode != NULL){
        //printf("%.3f > ", pNode->elt);
        fprintf(post, "%d %.3f %d-%d-%dT%d:00:00+%d:00 %f %f %f %f\n", pNode->ID, pNode->elt, pNode->date->year, pNode->date->month, pNode->date->day, pNode->date->hour, pNode->date->utc, pNode->x, pNode->y, pNode->e1, pNode->e2);
        pNode = pNode->pBefore;
    }
    
}

/*============================================================
Tree creation and lecture functions
=============================================================*/

Tree* CreateTree( int ID, float N, Date* D, float x, float y, float extra1, float extra2 ){                      //Create a tree
    Tree* NewTree = malloc(sizeof(Tree));
    if (NewTree ==  NULL){
        exit(4);
    }

    NewTree->ID = ID;
    NewTree->value = N;
    NewTree->date = D;
    NewTree->x = x;
    NewTree->y = y;
    NewTree->e1 = extra1;
    NewTree->e2 = extra2;

    NewTree->rs = NULL;
    NewTree->ls = NULL;
    NewTree->balance = 0;

    return NewTree;
}

Station* createStation ( int ID, float v ){
    Station* NewStation = malloc(sizeof(Station));
    if (NewStation == NULL){
        exit(4);
    }
    
    NewStation -> ID = ID;
    NewStation -> min = v;
    NewStation -> max = v;
    NewStation -> count = 1;
    NewStation -> total = v;
    NewStation -> average = v;
    NewStation -> rs = NULL;
    NewStation -> ls = NULL;

    return NewStation;

}

int IsEmpty( Tree* pTree ){                         //Check if tree is empty
    if ( pTree ==  NULL ){
        return 1;
    }
    else {
        return 0;
    }
}

int LsExists ( Tree* pTree ){                       //Check if left son exists
    if ( IsEmpty(pTree) == 1){
        exit(1);
    }    

    if ( pTree->ls == NULL ){
        return 0;
    }
    else {
        return 1;
    }
}

int RsExists ( Tree* pTree ){                       //Check if right son exists
    if ( IsEmpty(pTree) == 1){
        exit(1);
    }    

    if ( pTree->rs == NULL ){
        return 0;
    }
    else {
        return 1;
    }
}

Tree* AddLeft ( Tree* pTree, int ID, float value, Date* D, float x, float y, float e1, float e2 ){         //Add left son
    
    Tree* NewTree = CreateTree ( ID, value, D, x, y, e1, e2 );

    if (IsEmpty(pTree) == 1){
        pTree = NewTree;
    }
    if ( LsExists(pTree) == 0){
        pTree->ls = NewTree;
    }
    else{
        printf("cannot add here\n");
        exit(1);
    }
    
    return pTree;
}

Tree* AddRight ( Tree* pTree, int ID, float value, Date* D, float x, float y, float e1, float e2 ){        //Add right son

    Tree* NewTree = CreateTree ( ID, value , D , x , y, e1, e2 );

    if (IsEmpty(pTree) == 1){
        pTree = NewTree;
    }
    if ( RsExists(pTree) == 0){
        pTree->rs = NewTree;
    }
    else{
        printf("cannot add here\n");
        exit(1);
    }

    return pTree;
}

Station* AddLeftSt ( Station* S, int ID, float v ){         //Add left son
    
    Station* NewS = createStation ( ID, v );

    if (S == NULL){
        S = NewS;
    }
    if ( S->ls != NULL ){
        S->ls = NewS;
    }
    else{
        printf("cannot add here\n");
        exit(1);
    }
    
    return S;
}

Station* AddRightSt ( Station* S, int ID, float v ){        //Add right son

    Station* NewS = createStation ( ID, v );

    if (S == NULL){
        S = NewS;
    }
    if ( S->rs != NULL ){
        S->rs = NewS;
    }
    else{
        printf("cannot add here\n");
        exit(1);
    }

    return S;
}

void process( Tree* pTree, FILE* post){             //Gets the value of the current node and writes it in the post-sorting file
    //printf ("%.3f > ", pTree->value);
    fprintf(post, "%d %.3f %d-%d-%dT%d:00:00+%d:00 %f %f %f %f\n", pTree->ID, pTree->value, pTree->date->year, pTree->date->month, pTree->date->day, pTree->date->hour, pTree->date->utc, pTree->x, pTree->y, pTree->e1, pTree->e2);
}

void WalkthroughInfix( Tree* pTree, FILE* post ){           
    if (pTree != NULL){
        WalkthroughInfix( pTree->ls, post );
        process(pTree, post);
        WalkthroughInfix( pTree->rs, post );
    } 
}

void RWalkthroughInfix( Tree* pTree, FILE* post ){           
    if (pTree != NULL){
        RWalkthroughInfix( pTree->rs, post );
        process(pTree, post);
        RWalkthroughInfix( pTree->ls, post );
    } 
}


/*==============================================================
Average functions
===============================================================*/


void processAvPerSt( Station* S, FILE* post ){
    fprintf( post, "%d %f %f %f", S -> ID, S -> average, S -> min, S-> max);
}

void displayAvPerSt( Station* S, FILE* post){
    if ( S != NULL ){
        displayAvPerSt( S -> ls, post);
        processAvPerSt( S, post );
        displayAvPerSt( S -> rs, post);
    }

}

Date* addDate( int year, int month, int day, int hour, int utc){
    Date* Date = malloc(sizeof(Date));

    Date->year = year;
    Date->month = month;
    Date->day = day;
    Date->hour = hour;
    Date->utc = utc;
}

int dateComp ( Date* NewDate, Date* currDate ){         //date comparing function. will return -1 if new date is older or will return 1 if new date is more recent or equal to current date
    if ((NewDate == NULL)||(currDate == NULL)){
        exit(4);
    }
    
    if( NewDate->year > currDate->year ){   return 1;   } 
    else if ( NewDate->year < currDate->year ){   return -1;   }
    else if ( NewDate->year == currDate->year ){
        if( NewDate->month > currDate->month ){   return 1;   } 
        else if ( NewDate->month < currDate->month ){   return -1;   }
        else if ( NewDate->month == currDate->month ){
            if( NewDate->day > currDate->day ){   return 1;   } 
            else if ( NewDate->day < currDate->day ){   return -1;   }
            else if ( NewDate->day == currDate->day ){
                if( NewDate->hour > currDate->hour ){   return 1;   } 
                else if ( NewDate->hour < currDate->hour ){   return -1;   }
                else {
                    return 1;
                }
            }
        }
    }
}

/*==============================================================
ABR sorting functions
===============================================================*/

void InsertABR (Tree* pTree, int ID, float value, Date* D, float x, float y, float e1, float e2){              //Inserts the read value into the tree with the ABR sorting method

    if ( IsEmpty(pTree) == 1){
        exit(1);
    } 

    else if ( value < pTree->value ){
        if (LsExists(pTree) == 1){
            InsertABR( pTree->ls, ID, value, D , x , y, e1, e2);
        }
        else{
            AddLeft(pTree, ID, value, D , x , y, e1, e2);
        }       
    }

    else if ( (value > pTree->value) || (value == pTree->value) ){
        if (RsExists(pTree) == 1){
            InsertABR ( pTree->rs, ID, value, D , x, y, e1, e2);
        }
        else{
            AddRight(pTree, ID, value, D , x , y, e1, e2);
        }
    }
}

void InsertABRdate (Tree* pTree, int ID, float value, Date* D, float x, float y, float e1, float e2){              //Inserts the read value into the tree with the ABR sorting method

    if ( IsEmpty(pTree) == 1){
        exit(1);
    } 

    int comp = 0;
    comp = dateComp( D, pTree->date );

    switch (comp)
    {
    case -1:
        if (LsExists(pTree) == 1){
            InsertABRdate( pTree->ls, ID, value, D , x , y, e1, e2);
        }
        else{
            AddLeft(pTree, ID, value, D , x , y, e1, e2);
        }       
        break;
    
    default:
        if (RsExists(pTree) == 1){
            InsertABRdate( pTree->rs, ID, value, D , x, y, e1, e2);
        }
        else{
            AddRight(pTree, ID, value, D , x , y, e1, e2);
        }
        break;
    }
}

void InsertABRStation ( Station* S, int ID, float v){
    if ( S == NULL ){
        exit(1);
    }
    else if ( ID < S->ID ){
        if (S->ls != NULL){
            InsertABRStation( S->ls, ID, v );
        }
        else{
            AddLeftSt(S, ID, v);
        }       
    }

    else if ( (ID > S->ID) || (ID == S->ID) ){
        if (S->rs != NULL){
            InsertABRStation ( S->rs, ID, v );
        }
        else{
            AddRightSt(S, ID, v);
        }
    }
}

int search( Station* S , int ID ){

    if( S != NULL ){  
        if ( ID == S -> ID ){
            return 1;
        }
        if ( ( ID > S -> ID ) && ( S -> rs != NULL) ){
                return search( S->rs, ID );
        }
        if ( ( ID < S -> ID ) && ( S -> ls != NULL)){
                return search( S->ls, ID );
        }
        else {
            return 0;
        }
    }

}

void AveragePStationABR( Station* S, int ID, float v ){  

    int T = 0;
    T = search( S, ID );

    if ( (T == 1) ){
        if ( v < S -> min ){
        S -> min = v;
        } else if ( v > S -> max){
        S -> max = v;
        }
        S -> count = S -> count + 1;
        S -> total = S -> total + v;
        S -> average = S -> total/ S -> count;
    } else {
        InsertABRStation( S, ID, v );
    }
}


int SortABR( char* preFN , char* postFN , int R, int dSort, int mode){   //ABR type sorting function
    FILE* pre = NULL;
    FILE* post = NULL;
    int test;
    char temp[200];
    int ID = 0, year = 0, month = 0, day = 0, hour = 0, utc = 0;
    float N = 0, x = 0, y = 0, e1 = 0, e2 = 0;
    Tree* T = NULL;
    Station* S = NULL;
    Date* D = malloc(sizeof(Date));
    int d = 0;

    pre = fopen( preFN, "r" );
    post = fopen( postFN, "w" );
    

    if( (pre == NULL) ){  return 2;  }
    if( (post == NULL) ){  return 3;  }
    
    do {
        fgets(temp, 200, pre);
        test = fgetc(pre);
        fseek(pre, -1, SEEK_CUR);
        d = sscanf(temp, "%d %f %d-%d-%dT%d:00:00+%d:00 %f %f %f %f", &ID, &N, &year, &month, &day, &hour, &utc, &x, &y, &e1, &e2);
        if (( d == 9 )||( d == 11 )){
            D = addDate(year,month,day,hour,utc);
            if(( d == 9 )){
                e1 = 0;
                e2 = 0;
            } 
            switch( mode ){
                case(3):
                    break;
                case(2):
                    break;
                case(1):
                    if ( S == NULL ){
                        S = createStation(ID, N);
                    } else {
                        AveragePStationABR(S, ID, N);
                    }
                    break;
                default:
                    if( dSort == 1 ){
                    if( T == NULL ){  
                    T = CreateTree(ID, N , D , x , y, e1, e2); 
                    }
                    else{  
                    InsertABRdate (T, ID, N , D , x , y, e1, e2); 
                    }
                    } else {
                    if( T == NULL ){  
                        T = CreateTree(ID, N , D , x , y, e1, e2); 
                    }
                    else{  
                        InsertABR (T, ID, N , D , x , y, e1, e2); 
                    }
                    }
                    break;
            }
        
        } else {
            fclose(pre);
            fclose(post);

            free(T);
            free(D);
            return 2;
        }
    } while ( test != EOF );

    if ( R == 1 ){
        RWalkthroughInfix(T, post);
    }
    else{
        WalkthroughInfix(T, post);
    }
     
    fclose(pre);
    fclose(post);
    
    return 0;
}

/*===============================================================
Array sorting functions
================================================================*/

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




int SortLIST(char* preFN , char* postFN , int R, int dSort, int mode){    //Doubly linked list sorting function

    FILE* pre = NULL;
    FILE* post = NULL;
    int test;
    char temp[200];
    int ID = 0, year = 0, month = 0, day = 0, hour = 0, utc = 0;
    float N = 0, x = 0, y = 0, e1 = 0, e2 = 0;
    Date* D = malloc(sizeof(Date));
    List* L = malloc(sizeof(List));
    Init(L);
    int d = 0;
    

    pre = fopen( preFN, "r" );
    post = fopen( postFN, "w" );
    
    if( (pre == NULL) ){  return 2;  }
    if( (post == NULL) ){  return 3;  }

    do {
        fgets(temp, 200, pre);
        test = fgetc(pre);
        fseek(pre, -1, SEEK_CUR);
        d = sscanf(temp, "%d %f %d-%d-%dT%d:00:00+%d:00 %f %f %f %f", &ID, &N, &year, &month, &day, &hour, &utc, &x, &y, &e1, &e2);
        if((d == 9)||(d == 11)){
            if(( d == 9 )){
                e1 = 0;
                e2 = 0;
            }
            D = addDate(year,month,day,hour,utc);
            if ( dSort == 1 ){
                
                addListdate(L, ID, N, D, x, y, e1, e2);
            }
            else {
                addList(L, ID, N, D, x, y, e1, e2);
            }
        } else {
            fclose(pre);
            fclose(post);

            free(L);
            free(D);
            return 2;
        }

    } while ( test != EOF );
    

    if ( R == 1 ){
        RdisplayList(post, L->pLast);
    }
    else{
        displayList(post, L->pFirst);
    }
    

    fclose(pre);
    fclose(post);

    return 0;
}

/*===============================================================
AVL sorting functions
================================================================*/

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

Tree* LeftRotation( Tree* pTree ){
    Tree* pivot = malloc(sizeof(Tree));
    int eqA = 0, eqP = 0;

    pivot = pTree->rs;
    pTree->rs = pivot->ls;
    pivot->ls = pTree;

    eqA = pTree->balance;
    eqP = pivot->balance;

    eqA = eqA - max( eqP, 0 ) - 1;
    eqP = min( min(eqA-2, eqA+eqP-2), eqP-1 );
    pTree = pivot;
    return pTree; 
}

Tree* RightRotation( Tree* pTree ){
    Tree* pivot = malloc(sizeof(Tree));
    int eqA = 0, eqP = 0;

    pivot = pTree->ls;
    pTree->ls = pivot->rs;
    pivot->rs = pTree;

    eqA = pTree->balance;
    eqP = pivot->balance;

    eqA = eqA - min( eqP, 0 ) + 1;
    eqP = max( max(eqA+2, eqA+eqP+2), eqP+1 );
    pTree = pivot;
    return pTree; 
}

Station* LeftRotationSt( Station* S ){
    Station* pivot = malloc(sizeof(Station));
    int eqA = 0, eqP = 0;

    pivot = S->rs;
    S->rs = pivot->ls;
    pivot->ls = S;

    eqA = S->balance;
    eqP = pivot->balance;

    eqA = eqA - max( eqP, 0 ) - 1;
    eqP = min( min(eqA-2, eqA+eqP-2), eqP-1 );
    S = pivot;
    return S; 
}

Station* RightRotationSt( Station* S ){
    Station* pivot = malloc(sizeof(Station));
    int eqA = 0, eqP = 0;

    pivot = S->ls;
    S->ls = pivot->rs;
    pivot->rs = S;

    eqA = S->balance;
    eqP = pivot->balance;

    eqA = eqA - min( eqP, 0 ) + 1;
    eqP = max( max(eqA+2, eqA+eqP+2), eqP+1 );
    S = pivot;
    return S; 
}

Tree* DoubleRightRotation ( Tree* pTree ){
    pTree->ls = LeftRotation(pTree->ls);
    return RightRotation(pTree);
}

Tree* DoubleLeftRotation ( Tree* pTree ){
    pTree->rs = RightRotation(pTree->rs);
    return LeftRotation(pTree);
}

Station* DoubleRightRotationSt ( Station* S ){
    S->ls = LeftRotationSt(S->ls);
    return RightRotationSt(S);
}

Station* DoubleLeftRotationSt ( Station* S ){
    S->rs = RightRotationSt(S->rs);
    return LeftRotationSt(S);
}

Tree* TreeBalance ( Tree* pTree ){
    if(pTree != NULL){
        if( pTree->balance >= 2 ){
            if( pTree->rs->balance >= 0 ){
                return LeftRotation(pTree);
            }
            else{
                return DoubleLeftRotation(pTree);
            }
        }

        if( pTree->balance <= -2 ){
            if( pTree->ls->balance <=0 ){
                return RightRotation(pTree);
            }
            else{
                return DoubleRightRotation(pTree);
            }
        }
    return pTree;
    }

    return pTree;
}

Station* StationBalance ( Station* S ){
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

Tree* InsertAVL (Tree* pTree, int ID, float N, Date* D, int* pH, float x, float y, float e1, float e2){    //Inserts the read value into the tree with the AVL sorting method

    if ( pTree == NULL ){
        *pH = 1;
        return CreateTree(ID, N , D , x , y, e1, e2);
    }


    if ( N < pTree->value ){
        pTree->ls = InsertAVL(pTree->ls, ID, N, D , pH, x , y, e1, e2);
        *pH =  -*pH;
    }
    else if ( (N > pTree->value) || (N = pTree->value) ){
        pTree->rs = InsertAVL(pTree->rs, ID, N, D , pH, x , y, e1, e2);
    }
    
    if( *pH = 0 ){
        return pTree;
    }
    else if ( *pH != 0 ){
        pTree->balance = pTree->balance + *pH;
        pTree = TreeBalance(pTree);
        if (pTree->balance == 0){
            *pH = 0;
        }
        else {
            *pH = 1;
        }    
    }
    return pTree; 
}

Tree* InsertAVLdate (Tree* pTree, int ID, float N, Date* D, int* pH, float x, float y, float e1, float e2){    //Inserts the read value into the tree with the AVL sorting method

    if ( pTree == NULL ){
        *pH = 1;
        return CreateTree(ID, N , D , x , y, e1, e2);
    }

    int comp = 0;
    comp = dateComp( D, pTree->date );

    switch (comp)
    {
    case -1:
        pTree->ls = InsertAVLdate(pTree->ls, ID, N, D , pH, x , y, e1, e2);
        *pH =  -*pH;
        break;
    
    default:
        pTree->rs = InsertAVLdate(pTree->rs, ID, N, D , pH, x , y, e1, e2);
        break;
    }

    if( *pH = 0 ){
        return pTree;
    }
    else if ( *pH != 0 ){
        pTree->balance = pTree->balance + *pH;
        pTree = TreeBalance(pTree);
        if (pTree->balance == 0){
            *pH = 0;
        }
        else {
            *pH = 1;
        }    
    }
    return pTree; 
}

Station* InsertAVLStation ( Station* S, int ID, float v, int* pH ){    //Inserts the read value into the tree with the AVL sorting method

    if ( S == NULL ){
        *pH = 1;
        return createStation( ID, v );
    }

    if ( ID < S->ID ){
        S->ls = InsertAVLStation(S->ls, ID, v, pH);
        *pH =  -*pH;
    }
    else if ( (ID > S->ID) || ( ID = S->ID ) ){
        S->rs = InsertAVLStation(S->rs, ID, v, pH);
    }
    
    if( *pH = 0 ){
        return S;
    }
    else if ( *pH != 0 ){
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

Station* AveragePStationAVL( Station* S, int ID, float v, int* pH){  

    int T = 0;
    T = search( S, ID );

    if ( (T == 1) ){
        if ( v < S -> min ){
        S -> min = v;
        } else if ( v > S -> max){
        S -> max = v;
        }
        S -> count = S -> count + 1;
        S -> total = S -> total + v;
        S -> average = S -> total/ S -> count;
    } else {
        
    }

    if( *pH = 0 ){
        return S;
    }
    else if ( *pH != 0 ){
        S->balance = S->balance + *pH;
        S = StationBalance(S);
        if (S->balance == 0){
            *pH = 0;
        }
        else {
            *pH = 1;
        }    
    }
}

int SortAVL( char* preFN , char* postFN , int R, int* pH, int dSort, int mode ){     //AVL type sorting function

    FILE* pre = NULL;
    FILE* post = NULL;
    int test;
    char temp[200];
    int ID = 0, year = 0, month = 0, day = 0, hour = 0, utc = 0;
    float N = 0, x = 0, y = 0, e1 = 0, e2 = 0;
    Tree* T = NULL;
    Station* S = NULL;
    Date* D = malloc(sizeof(Date));
    int d = 0;

    pre = fopen( preFN, "r" );
    post = fopen( postFN, "w" );
    

    if( (pre == NULL) ){  return 2;  }
    if( (post == NULL) ){  return 3;  }

    do {
        fgets(temp, 200, pre);
        test = fgetc(pre);
        fseek(pre, -1, SEEK_CUR);
        d = sscanf(temp, "%d %f %d-%d-%dT%d:00:00+%d:00 %f %f %f %f", &ID, &N, &year, &month, &day, &hour, &utc, &x, &y, &e1, &e2);
        if ((d == 9)||(d == 11)){
            D = addDate(year,month,day,hour,utc);
            if( d == 9 ){
                e1 = 0;
                e2 = 0;
            }
            switch( mode ){
                case(3):
                    break;
                case(2):
                    break;
                case(1):
                    if ( S == NULL ){
                        S = createStation(ID, N);
                    } else {
                        AveragePStationAVL(S, ID, N, pH);
                    }
                    break;
                default:
                    if(dSort == 1){
                        if( T == NULL ){  
                            T = CreateTree( ID, N , D , x , y, e1, e2); 
                        }
                        else{  
                            InsertAVLdate (T, ID, N, D, pH, x , y, e1, e2); 
                        }
                    } else {
                        if( T == NULL ){  
                            T = CreateTree( ID, N , D , x , y, e1, e2); 
                        }
                        else{  
                            InsertAVL (T, ID, N, D, pH, x , y, e1, e2); 
                        }
                    }
                break;}
            } else {
                fclose(pre);
                fclose(post);

                free(T);
                free(D);
                return 2;
            }

    } while ( test != EOF );


    if ( R == 1 ){
        RWalkthroughInfix(T, post);
    }
    else{
        WalkthroughInfix(T, post);
    }

    fclose(pre);
    fclose(post);

    free(T);
    free(D);
    return 0;
}



/*===============================================================
Main program
================================================================*/

int main( int argc, char* argv[] ){

int i = 0;
int tpre = 0, tpost = 0, tr = 0, tabr = 0, ttab = 0;
int R = 0, dsort = 0, mode = 0;
int test = 0;

int* pH = malloc(sizeof(int));

if ( argc != 6 ) { test = 1; }                   //Check if the number of given arguments in correct

for ( i=1 ; i < argc; i++){

    //printf("%d | %s          ", i, argv[i]);

    if ( (i == 1) ){                            //Test if pre-sorting file exists
        tpre = TestFileExist ( argv[i] );
        if ( tpre == 1 ){
            //printf("Pre-sorting File exists\n");
        }
        else { return 2 ; }
    }

    if ( (i == 2) ){                            //Test if post-sorting file exists
        tpost = TestFileExist ( argv[i] );
        if ( tpost == 1 ){
            //printf("Post-sorting File exists\n");
        }
        else { return 3 ; }
    }

    if ( (i == 3) ){                            //Check if reverse sorting has been chosen        
        tr = strcmp ( "-r" , argv[i] );
        if ( (tr == 0) ){
            R = 1;
            //printf("Reverse sorting\n");
        } else {
            //printf("Normal sorting\n");
        }
    }
    
    if ( (i == 4) ){                            //Check if reverse sorting has been chosen        
        tr = strcmp ( "-dsort" , argv[i] );
        if ( (tr == 0) ){
            dsort = 1;
            //printf("Sort by dates\n");
        } else {
            //printf("Sort by values\n");
        }
    }

    if ( (i == 5) ){
        tr = strcmp ( "-m1" , argv[i] );
        if ( (tr == 0) ){
            mode = 1;
        } else {
            tr = strcmp ( "-m2" , argv[i] );
            if ( (tr == 0) ){
                mode = 2;
            } else {
                tr = strcmp ( "-m3" , argv[i] );
                if ( (tr == 0) ){
                    mode = 3;
                } else {
                    mode = 0;
                }
            }
        }
    }

    if ( (i == 6) ){                            //Check chosen sorting method if none is given default is AVL

        tabr = strcmp ( "--abr" , argv[i] );
        ttab = strcmp ( "--tab" , argv[i] );


        if ( (tabr == 0 && ttab != 0) ){
            //printf("Sort using ABR method\n\n");
            test = SortABR( argv[1] , argv[2] , R , dsort, mode);
        }
        else if ( (tabr != 0 && ttab == 0) ){
            //printf("Sort using LIST method\n\n");
            test = SortLIST( argv[1] , argv[2] , R , dsort, mode);
        }
        else {
            //printf("Sort using AVL method\n\n");
            test = SortAVL( argv[1] , argv[2] , R , pH, dsort, mode);
        }

    }

}


switch (test)
{
case 4:
    printf("|    Program terminated with error code < 4 > :      Other issues    |");
    break;

case 3:
    printf("|    Program terminated with error code < 3 > :      Post-sorting file issues    |");
    break;

case 2:
    printf("|    Program terminated with error code < 2 > :      Pre-sorting file issues    |");
    break;

case 1:
    printf("|    Program terminated with error code < 1 > :      Given arguments incorrect    |");
    break;

case 0:
    printf("|    Program correctly executed    |");
    break;


default:
    break;
}


return 0;

}