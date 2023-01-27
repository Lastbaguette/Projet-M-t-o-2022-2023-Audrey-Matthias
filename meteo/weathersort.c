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


/*==============================================================
Extra functions
===============================================================*/


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


int SortABR( char* preFN , char* postFN , int R, int dSort, int mode){   //ABR type sorting function
    FILE* pre = NULL;
    FILE* post = NULL;
    int test;
    char temp[200];
    int ID = 0, year = 0, month = 0, day = 0, hour = 0, utc = 0;
    float N = 0, N2 = 0, x = 0, y = 0;
    Station1* S = NULL;
    Station1* NS = NULL;
    Date* D = malloc(sizeof(Date));
    int d = 0;

    pre = fopen( preFN, "r" );
    post = fopen( postFN, "w" );
    
    if( (pre == NULL) ){ printf("a"); return 2;  }
    if( (post == NULL) ){  return 3;  }
    
    do {
        fgets(temp, 200, pre);
        test = fgetc(pre);
        fseek(pre, -1, SEEK_CUR);
        d = sscanf(temp, "%d %d-%d-%dT%d:00:00+%d:00 %f %f %f %f", &ID, &year, &month, &day, &hour, &utc, &N, &N2, &x, &y);
        //printf("\n\n%d-%d-%d %d:00:00+%d\n",year, month, day, hour, utc);
        if (( d == 10 )){
            D = addDate(year,month,day,hour,utc);
            switch( mode ){
                case(1):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        AveragePStationABR(S, ID, N, D, x, y);
                    }
                    break;
                case(2):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        S = InsertPDateAllStABR(S, ID, N, D, x, y);
                    }
                    break;
                case(3):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        InsertPDatePStABR(S, ID, N, D, x, y);
                    }
                    break;
                case(4):
                    if ( S == NULL ){
                        S = createStation1bis(ID, N, N2, x, y);
                    } else {
                        AveragePStationVectorABR(S, ID, N, N2, x, y);
                    }
                    break;
                case(5):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        SortHeight1(S, ID, N, D, x, y);
                    }
                    break;
                case(6):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        AveragePStationABR(S, ID, N, D, x, y);
                    }
                    break;
                default:
                    return 4;
                    break;
                }
        
        } else {
            fclose(pre);
            fclose(post);
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
                    NS = SortHeight2(S, NS);
                    if ( R == 1 ){
                        displayHeight(NS, post);
                    } else {
                        RdisplayHeight(NS, post);
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
                    return 4;
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
        d = sscanf(temp, "%d %d-%d-%dT%d:00:00+%d:00 %f %f %f %f", &ID, &year, &month, &day, &hour, &utc, &N, &N2, &x, &y);
        if((d == 10)){

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


int SortAVL( char* preFN , char* postFN , int R, int* pH, int dSort, int mode ){     //AVL type sorting function

    FILE* pre = NULL;
    FILE* post = NULL;
    int test;
    char temp[200];
    int ID = 0, year = 0, month = 0, day = 0, hour = 0, utc = 0;
    float N = 0, N2 = 0, x = 0, y = 0;
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
        d = sscanf(temp, "%d %d-%d-%dT%d:00:00+%d:00 %f %f %f %f", &ID, &year, &month, &day, &hour, &utc, &N, &N2, &x, &y);

        if ((d == 10)){
            D = addDate(year,month,day,hour,utc);
            switch( mode ){
                case(1):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        S = AveragePStationAVL(S, ID, N, pH, D, x, y);
                    }
                    break;
                case(2):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        S = InsertPDateAllStAVL(S, ID, N, pH, D, x, y);
                    }
                    break;
                case(3):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        S = InsertPDatePStAVL(S, ID, N, pH, D, x, y);
                    }
                    break;
                case(4):
                    if ( S == NULL ){
                        S = createStation1bis(ID, N, N2, x, y);
                    } else {
                        AveragePStationVectorAVL(S, ID, N, N2, pH, x, y);
                    }
                    break;
                case(5):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        S = SortHeight1AVL(S, ID, N, pH, D, x, y);
                    }
                    break;
                case(6):
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        S = AveragePStationAVL(S, ID, N, pH, D, x, y);
                    }
                    break;
                default:
                    return 4;
                    break;
                }

            } else {
                fclose(pre);
                fclose(post);
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
                    NS = SortHeight2AVL(S, NS, pH);
                    if ( R == 1 ){
                        displayHeight(NS, post);
                    } else {
                        RdisplayHeight(NS, post);
                    }
                    break;
                case(6):
                    NS = SortMoistureAVL(S, NS, pH);
                    if ( R == 1 ){
                        displayMoisture(NS, post);
                    } else {
                        RdisplayMoisture(NS, post);
                    }
                    break;
                default:
                    return 4;
                    break;
            }

    fclose(pre);
    fclose(post);

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
int H = 0;
int* pH = &H;

if ( argc != 6 ) { test = 1; }                   //Check if the number of given arguments in correct

for ( i=1 ; i < argc; i++){

    //printf("%d | %s          \n", i, argv[i]);

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