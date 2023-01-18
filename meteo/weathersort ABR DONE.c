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

Station1* createStation1 ( int ID, float v, Date* D){
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

    return NewStation;

}

Station1* createStation1bis( int ID, float v, float v2){
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

Station1* AddRightSt ( Station1* S, int ID, float v, Date* D ){        //Add right son

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

Station1* AddLeftSt2 ( Station1* S, Station1* NS ){        //Add left son

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

Station1* AddRightSt2 ( Station1* S, Station1* NS ){        //Add right son

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

Station1* AddLeftStbis  ( Station1* S, int ID, float v, float v2 ){        //Add left son

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

Station1* AddRightStbis ( Station1* S, int ID, float v, float v2 ){        //Add right son

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



/*==============================================================
Extra functions
===============================================================*/


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
    fprintf( post, "%d %d %f %f\n", S -> ID,S ->count, S -> average, S->average2);
}

void processHeight( Station1* S, FILE* post ){
    fprintf( post, "%d %f\n", S -> ID, S -> average);
}

void processMoisture( Station1* S, FILE* post ){
    fprintf( post, "%d %f\n", S -> ID, S -> max);
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
                else if( NewDate->hour == currDate->hour ){
                    return 0;
                }
            }
        }
    }
}

/*==============================================================
ABR sorting functions
===============================================================*/

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
        if ( S -> ID > ID ){
            Station1* NS = createStation1( ID, v, D );
            NS->ls = S->ls;
            S->ls = NS;
        } else {
            Station1* NS = createStation1( ID, v, D );
            NS->rs = S->rs;
            S->rs = NS;
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
            InsertABRStation( S->ls, ID, v, D );
        }
        else{
           S = AddLeftSt(S, ID, v, D);
        }       
    }
    else if ( (v > S->average) ){
        if (S->rs != NULL){
            InsertABRStation ( S->rs, ID, v, D );
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

int SortABR( char* preFN , char* postFN , int R, int dSort, int mode){   //ABR type sorting function
    FILE* pre = NULL;
    FILE* post = NULL;
    int test;
    char temp[200];
    int ID = 0, year = 0, month = 0, day = 0, hour = 0, utc = 0;
    float N = 0, x = 0, y = 0;
    Tree* T = NULL;
    Station1* S = NULL;
    Station1* NS = NULL;
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
        d = sscanf(temp, "%d %f %d-%d-%dT%d:00:00+%d:00 %f %f", &ID, &N, &year, &month, &day, &hour, &utc, &x, &y);
        if (( d == 9 )){
            D = addDate(year,month,day,hour,utc);
            switch( mode ){
                case(1):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D);
                    } else {
                        AveragePStationABR(S, ID, N, D);
                    }
                    break;
                case(2):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D);
                    } else {
                        InsertPDateAllStABR(S, ID, N, D);
                    }
                    break;
                case(3):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D);
                    } else {
                        InsertPDatePStABR(S, ID, N, D);
                    }
                    break;
                case(4):
                    if ( S == NULL ){
                        S = createStation1bis(ID, x, y);
                    } else {
                        AveragePStationVectorABR(S, ID, x, y);
                    }
                    break;
                case(5):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D);
                    } else {
                        SortHeight(S, ID, N, D);
                    }
                    break;
                case(6):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D);
                    } else {
                        AveragePStationABR(S, ID, N, D);
                    }
                    break;
                default:
                    
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


    switch( mode ){
                case(1):
                    displayAvPerSt(S, post);
                    break;
                case(2):
                    displayAvPerDateAllSt(S, post);
                    break;
                case(3):
                    displayPerDatePSt(S, post);
                    break;
                case(4):
                    displayWind(S, post);
                    break;
                case(5):
                    if ( R == 1 ){
                        displayHeight(S, post);
                    } else {
                        RdisplayHeight(S, post);
                    }
                    break;
                case(6):

                    NS = SortMoisture(S, NS);
                    if ( R == 1 ){
                        displayMoisture(NS, post);
                    } else {
                        RdisplayMoisture(NS, post);
                    }
                    break;
                default:
                    
                    break;
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
    float N = 0, x = 0, y = 0;
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
        d = sscanf(temp, "%d %f %d-%d-%dT%d:00:00+%d:00 %f %f", &ID, &N, &year, &month, &day, &hour, &utc, &x, &y);
        if((d == 9)){

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


Station1* LeftRotationSt( Station1* S ){
    Station1* pivot = malloc(sizeof(Station1));
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

Station1* RightRotationSt( Station1* S ){
    Station1* pivot = malloc(sizeof(Station1));
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

Station1* InsertAVLStation ( Station1* S, int ID, float v, int* pH, Date* D){    //Inserts the read value into the tree with the AVL sorting method

    if ( S == NULL ){
        *pH = 1;
        return createStation1( ID, v, D);
    }

    if ( ID < S->ID ){
        S->ls = InsertAVLStation(S->ls, ID, v, pH, D);
        *pH =  -*pH;
    }
    else if ( (ID > S->ID) || ( ID = S->ID ) ){
        S->rs = InsertAVLStation(S->rs, ID, v, pH, D);
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

Station1* AveragePStationAVL( Station1* S, int ID, float v, int* pH){  

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
    Station1* S = NULL;
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


            } else {
                fclose(pre);
                fclose(post);

                free(T);
                free(D);
                return 2;
            }

    } while ( test != EOF );

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
    

    if ( (i == 4) ){
        tr = strcmp ( "-m1" , argv[i] );                            //temp or pressure m1
        if ( (tr == 0) ){
            mode = 1;
        } else {
            tr = strcmp ( "-m2" , argv[i] );                        //temp or pressure m2
            if ( (tr == 0) ){
                mode = 2;
            } else {
                tr = strcmp ( "-m3" , argv[i] );                    //temp or pressure m3
                if ( (tr == 0) ){
                    mode = 3;
                } else {
                    tr = strcmp ( "-w" , argv[i] );                 //wind
                    if ( (tr == 0) ){
                        mode = 4;
                    } else {
                        tr = strcmp ( "-h" , argv[i] );             //altitude
                        if ( (tr == 0) ){
                            mode = 5;
                        } else {
                            tr = strcmp ( "-m" , argv[i] );         //Moisture
                            if ( (tr == 0) ){
                                mode = 6;
                            } else {
                                
                            }
                        }
                    }
                }
            }
        }
    }


    if ( (i == 5) ){                            //Check chosen sorting method if none is given default is AVL

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
    printf("|    Program terminated with error code < 4 > :      Other issues    |\n");
    break;

case 3:
    printf("|    Program terminated with error code < 3 > :      Post-sorting file issues    |\n");
    break;

case 2:
    printf("|    Program terminated with error code < 2 > :      Pre-sorting file issues    |\n");
    break;

case 1:
    printf("|    Program terminated with error code < 1 > :      Given arguments incorrect    |\n");
    break;

case 0:
    printf("|    Program correctly executed    |\n");
    break;


default:
    break;
}


return 0;

}