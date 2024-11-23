#ifndef cardType_h
#define cardType_h

#define N_2TO9          3
#define N_TEN           8
#define N_11N           1
#define N_76            1
#define N_ZERO          4
#define N_MINUS         4
#define N_DOUBLE        4


#define CARDOFFSET_2TO9     0                   
#define CARDOFFSET_TEN      (N_2TO9*8)                          //24  offset=start point
#define CARDOFFSET_11N      (CARDOFFSET_TEN+N_TEN)              //32
#define CARDOFFSET_76       (CARDOFFSET_11N+N_11N*6)            //38
#define CARDOFFSET_ZERO     (CARDOFFSET_76+N_76)                //39
#define CARDOFFSET_MINUS    (CARDOFFSET_ZERO+N_ZERO)            //43
#define CARDOFFSET_DOUBLE   (CARDOFFSET_MINUS+N_MINUS)          //47

#define N_TOTAL             (CARDOFFSET_DOUBLE+N_DOUBLE)        //51



#define CARDNUM_DOUBLE      100
#define CARDNUM_MINUS       -10

int cType_getCardNum(int cardType);
void cType_printCard(int cardType);

#endif /* cardType_h */
