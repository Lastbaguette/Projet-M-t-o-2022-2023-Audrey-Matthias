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

    return Date;
}

int dateComp ( Date* NewDate, Date* currDate ){         //date comparing function. will return -1 if new date is older or will return 1 if new date is more recent or equal to current date
    if ((NewDate == NULL)||(currDate == NULL)){
        exit(4);
    }

    int comp = 0;
    
    if( NewDate->year > currDate->year ){   comp = 1;   } 
    else if ( NewDate->year < currDate->year ){   comp = -1;   }
    else if ( NewDate->year == currDate->year ){
        if( NewDate->month > currDate->month ){   comp = 1;   } 
        else if ( NewDate->month < currDate->month ){   comp = -1;   }
        else if ( NewDate->month == currDate->month ){
            if( NewDate->day > currDate->day ){   comp = 1;   } 
            else if ( NewDate->day < currDate->day ){   comp = -1;   }
            else if ( NewDate->day == currDate->day ){
                if( NewDate->hour > currDate->hour ){   comp = 1;   } 
                else if ( NewDate->hour < currDate->hour ){   comp = -1;   }
                else if( NewDate->hour == currDate->hour ){
                    comp = 0;
                }
            }
        }
    }

    return comp;
}

/*==============================================================
ABR sorting functions
===============================================================*/


int SortABR( char* preFN , char* postFN , int R, int dSort, int mode){   //ABR type sorting function
    FILE* pre = NULL;
    FILE* post = NULL;
    int test;
    char temp[300];
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
        char temp[300];
        fgets(temp, 300, pre);
        test = fgetc(pre);
        fseek(pre, -1, SEEK_CUR);
        d = sscanf(temp, "%d %d-%d-%dT%d:00:00+%d:00 %f %f %f %f", &ID, &year, &month, &day, &hour, &utc, &N, &N2, &x, &y);

        if (( d == 10 )){                   //if sscanf gets less outputs than the 10 necessary will return error 2 (to prevent sorting incomplete lines)
            D = addDate(year,month,day,hour,utc);
            switch( mode ){
                case(1):                    //Mode 1 ( Temperature/Pressure ): Sorting per ID for average, min and max values
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        AveragePStationABR(S, ID, N, D, x, y);
                    }
                    break;
                case(2):                    //Mode 2 ( Temperature/Pressure ): Sorting per date for all stations to get the average value
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        S = InsertPDateAllStABR(S, ID, N, D, x, y);
                    }
                    break;
                case(3):                    //Mode 3 ( Temperature/Pressure ): Sorting per date per station to get the value
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        InsertPDatePStABR(S, ID, N, D, x, y);
                    }
                    break;
                case(4):                    //Wind : Sorting per ID to get module and orientation average values
                    if ( S == NULL ){
                        S = createStation1bis(ID, N, N2, x, y);
                    } else {
                        AveragePStationVectorABR(S, ID, N, N2, x, y);
                    }
                    break;
                case(5):                    //Height : Sorting per altitude value
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        SortHeight1(S, ID, N, D, x, y);
                    }
                    break;
                case(6):                    //Moisture : Sorting per max moisture value
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
                case(1):        //Mode 1 ( Temperature/Pressure )
                    displayAvPerSt(S, post);
                    break;
                case(2):        //Mode 2 ( Temperature/Pressure )
                    displayAvPerDateAllSt(S, post);
                    break;
                case(3):        //Mode 3 ( Temperature/Pressure )
                    displayPerDatePSt(S, post);
                    break;
                case(4):        //Wind
                    displayWind(S, post);
                    break;
                case(5):        //Height
                    NS = SortHeight2(S, NS);
                    if ( R == 1 ){
                        displayHeight(NS, post);        //Base order is in decreasing order
                    } else {
                        RdisplayHeight(NS, post);       //Reverse order in in rising order
                    }
                    break;
                case(6):        //Moisture
                    NS = SortMoisture(S, NS);
                    if ( R == 1 ){
                        displayMoisture(NS, post);      //Base order is in decreasing order      
                    } else {
                        RdisplayMoisture(NS, post);     //Reverse order in in rising order
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
    char temp[300];
    int ID = 0, year = 0, month = 0, day = 0, hour = 0, utc = 0;
    float N = 0, N2 = 0, x = 0, y = 0;
    Date* D = malloc(sizeof(Date));
    List* L = malloc(sizeof(List));
    List* L2 = malloc(sizeof(List));
    int d = 0, p = 1;
    int i = 0;
    

    pre = fopen( preFN, "r" );
    post = fopen( postFN, "w" );
    
    if( (pre == NULL) ){  return 2;  }
    if( (post == NULL) ){  return 3;  }

    do {
        fgets(temp, 300, pre);
        test = fgetc(pre);
        fseek(pre, -1, SEEK_CUR);
        d = sscanf(temp, "%d %d-%d-%dT%d:00:00+%d:00 %f %f %f %f", &ID, &year, &month, &day, &hour, &utc, &N, &N2, &x, &y);
        if (( d == 10 )){                   //if sscanf gets less outputs than the 10 necessary will return error 2 (to prevent sorting incomplete lines)
            D = addDate(year,month,day,hour,utc);
            switch( mode ){
                case(1):                    //Mode 1 ( Temperature/Pressure ): Sorting per ID for average, min and max values
                    if ( p == 1 ){      
                        Node* elt = createNode(ID, N, D, x, y);
                        L = Init(L, elt);
                        p = 0;
                    } else {
                        AvPStationList(L, ID, N, D, x, y);
                    }
                    break;
                case(2):                     //Mode 2 ( Temperature/Pressure ): Sorting per date for all stations to get the average value
                    if ( p == 1 ){
                        Node* elt = createNode(ID, N, D, x, y);
                        L = Init(L, elt);
                        p = 0;
                    } else {
                        InsertPerDateAllStList(L, L->pFirst, ID, N, D, x, y);
                    }
                    break;
                case(3):                     //Mode 3 ( Temperature/Pressure ): Sorting per date per station to get the value
                    if ( p == 1 ){
                        Node* elt = createNode(ID, N, D, x, y);
                        L = Init(L, elt);
                        p = 0;
                    } else {
                        InsertPerDatePerStList(L, L->pFirst, ID, N, D, x, y);
                    }
                    break;
                case(4):                     //Wind : Sorting per ID to get module and orientation average values
                    if ( p == 1 ){
                        Node* elt = createNodebis(ID, N, N2, x, y);
                        L = Init(L, elt);
                        p = 0;
                    } else {
                        AvPStationVectorList(L, ID, N, N2, x, y);
                    }
                    break;
                case(5):                     //Height : Sorting per altitude value
                    if ( p == 1 ){
                        Node* elt = createNode(ID, N, D, x, y);
                        L = Init(L, elt);
                        p = 0;
                    } else {
                        SortHeight1List(L, ID, N, D, x, y);
                    }
                    break;
                case(6):                     //Moisture : Sorting per max moisture value
                    if ( p == 1 ){      
                        Node* elt = createNode(ID, N, D, x, y);
                        L = Init(L, elt);
                        p = 0;
                    } else {
                        AvPStationList(L, ID, N, D, x, y);
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
                case(1):        //Mode 1 ( Temperature/Pressure )
                    displayListAvPerSt(post, L->pFirst);
                    break;
                case(2):        //Mode 2 ( Temperature/Pressure )
                    displayListAvPerDateAllSt(post, L->pFirst);
                    break;
                case(3):        //Mode 3 ( Temperature/Pressure )
                    displayListAvPerDatePerSt(post, L->pFirst);
                    break;
                case(4):        //Wind
                    displayListWind(post, L->pFirst);
                    break;
                case(5):        //Height
                    L2 -> pFirst = NULL;
                    L2 = SortHeight2List(L->pFirst, L2);
                    if ( R == 1 ){
                        displayListHeight(post, L2->pLast);     //Base order is in decreasing order
                    } else {
                        RdisplayListHeight(post, L2->pFirst);   //Reverse order in in rising order
                    }
                    break;
                case(6):        //Moisture
                    L2 -> pFirst = NULL;
                    L2 = SortMoistureList(L->pFirst, L2);
                    if ( R == 1 ){
                        displayListMoisture(post, L2->pLast);   //Base order is in decreasing order
                    } else {
                        RdisplayListMoisture(post, L2->pFirst); //Reverse order in in rising order
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
    char temp[300];
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
        fgets(temp, 300, pre);
        test = fgetc(pre);
        fseek(pre, -1, SEEK_CUR);
        d = sscanf(temp, "%d %d-%d-%dT%d:00:00+%d:00 %f %f %f %f", &ID, &year, &month, &day, &hour, &utc, &N, &N2, &x, &y);

        if ((d == 10)){                     //if sscanf gets less outputs than the 10 necessary will return error 2 (to prevent sorting incomplete lines)
            D = addDate(year,month,day,hour,utc);
            switch( mode ){
                case(1):                    //Mode 1 ( Temperature/Pressure ): Sorting per ID for average, min and max values
                    if ( S == NULL ){
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        S = AveragePStationAVL(S, ID, N, pH, D, x, y);
                    }
                    break;
                case(2):                    //Mode 2 ( Temperature/Pressure ): Sorting per date for all stations to get the average value
                    if ( S == NULL ){       
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        S = InsertPDateAllStAVL(S, ID, N, pH, D, x, y);
                    }
                    break;
                case(3):                    //Mode 3 ( Temperature/Pressure ): Sorting per date per station to get the value
                    if ( S == NULL ){       
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        S = InsertPDatePStAVL(S, ID, N, pH, D, x, y);
                    }
                    break;
                case(4):                    //Wind : Sorting per ID to get module and orientation average values
                    if ( S == NULL ){ 
                        S = createStation1bis(ID, N, N2, x, y);
                    } else {
                        S = AveragePStationVectorAVL(S, ID, N, N2, pH, x, y);
                    }
                    break;
                case(5):                    //Height : Sorting per altitude value
                    if ( S == NULL ){       
                        S = createStation1(ID, N, D, x, y);
                    } else {
                        S = SortHeight1AVL(S, ID, N, pH, D, x, y);
                    }
                    break;
                case(6):                    //Moisture : Sorting per max moisture value
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
                case(1):        //Mode 1 ( Temperature/Pressure )
                    displayAvPerSt(S, post);            
                    break;
                case(2):        //Mode 2 ( Temperature/Pressure )
                    displayAvPerDateAllSt(S, post);
                    break;
                case(3):        //Mode 3 ( Temperature/Pressure )
                    displayPerDatePSt(S, post);
                    break;
                case(4):        //Wind
                    displayWind(S, post);
                    break;
                case(5):        //Height
                    NS = SortHeight2AVL(S, NS, pH);
                    if ( R == 1 ){
                        displayHeight(NS, post);        //Base order is in decreasing order
                    } else {
                        RdisplayHeight(NS, post);       //Reverse order in in rising order
                    }
                    break;
                case(6):        //Moisture
                    NS = SortMoistureAVL(S, NS, pH);
                    if ( R == 1 ){
                        displayMoisture(NS, post);      //Base order is in decreasing order
                    } else {
                        RdisplayMoisture(NS, post);     //Reverse order in in rising order
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
            //Pre-sorting File exists
        }
        else { return 2 ; }
    }

    if ( (i == 2) ){                            //Test if post-sorting file exists
        tpost = TestFileExist ( argv[i] );
        if ( tpost == 1 ){
            //Post-sorting File exists
        }
        else { return 3 ; }
    }

    if ( (i == 3) ){                            //Check if reverse sorting has been chosen        
        tr = strcmp ( "-r" , argv[i] );
        if ( (tr == 0) ){
            R = 1;
            //Reverse sorting
        } else {
            //Normal sorting
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
            test = SortABR( argv[1] , argv[2] , R , dsort, mode);           //Sort using ABR method
        }
        else if ( (tabr != 0 && ttab == 0) ){
            test = SortLIST( argv[1] , argv[2] , R , dsort, mode);          //Sort using LIST method
        }
        else {
            test = SortAVL( argv[1] , argv[2] , R , pH, dsort, mode);       //Sort using AVL method
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