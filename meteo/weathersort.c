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

/*==============================================================
Date functions
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


int SortLIST(char* preFN , char* postFN , int R, int dSort, int mode){    //Doubly linked list sorting function

    FILE* pre = NULL;
    FILE* post = NULL;
    int test;
    char temp[200];
    int ID = 0, year = 0, month = 0, day = 0, hour = 0, utc = 0;
    float N = 0, N2 = 0, x = 0, y = 0;
    Date* D = malloc(sizeof(Date));
    List* L = NULL;
    Node* elt = malloc(sizeof(Node));
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
        if (( d == 10 )){
            D = addDate(year,month,day,hour,utc);
            switch( mode ){
                case(1):
                    if ( L == NULL ){
                        elt = createNode(ID, N, D, x, y);
                        L->pFirst = elt;
                        L->pLast = elt;
                    } else {
                        AvPStationList(L, ID, N, D, x, y);
                    }
                    break;
                case(2):
                    if ( L == NULL ){
                        elt = createNode(ID, N, D, x, y);
                        L->pFirst = elt;
                        L->pLast = elt;
                    } else {
                    }
                    break;
                case(3):
                    if ( L == NULL ){
                        elt = createNode(ID, N, D, x, y);
                        L->pFirst = elt;
                        L->pLast = elt;
                    } else {

                    }
                    break;
                case(4):
                    if ( L == NULL ){
                        elt = createNode(ID, N, D, x, y);
                        L->pFirst = elt;
                        L->pLast = elt;
                    } else {

                    }
                    break;
                case(5):
                    if ( L == NULL ){
                        elt = createNode(ID, N, D, x, y);
                        L->pFirst = elt;
                        L->pLast = elt;
                    } else {

                    }
                    break;
                case(6):
                    if ( L == NULL ){
                        elt = createNode(ID, N, D, x, y);
                        L->pFirst = elt;
                        L->pLast = elt;
                    } else {

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
                    //displayAvPerSt(S, post);
                    break;
                case(2):
                    //displayAvPerDateAllSt(S, post);
                    break;
                case(3):
                    //displayPerDatePSt(S, post);
                    break;
                case(4):
                    //displayWind(S, post);
                    break;
                case(5):
                    if ( R == 1 ){
                        //displayHeight(NS, post);
                    } else {
                        //RdisplayHeight(NS, post);
                    }
                    break;
                case(6):

                    if ( R == 1 ){
                        //displayMoisture(NS, post);
                    } else {
                        //RdisplayMoisture(NS, post);
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
                        S = AveragePStationVectorAVL(S, ID, N, N2, pH, x, y);
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
    printf("\n|    Program terminated with error code < 4 > :      Other issues    |\n");
    break;

case 3:
    printf("\n|    Program terminated with error code < 3 > :      Post-sorting file issues    |\n");
    break;

case 2:
    printf("\n|    Program terminated with error code < 2 > :      Pre-sorting file issues    |\n");
    break;

case 1:
    printf("\n|    Program terminated with error code < 1 > :      Given arguments incorrect    |\n");
    break;

case 0:
    printf("\n|    Program correctly executed    |\n");
    break;


default:
    break;
}


return 0;

}