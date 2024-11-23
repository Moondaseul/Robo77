#include <stdio.h>
#include "cardGroup.h"
#include "cardType.h"

#define N_LIFE          3
#define N_PLAYER        2
#define N_CARDHOLD      5
#define MAX_CUMNUM      77

static int cumNum=0;
static int cardHold[N_PLAYER][N_CARDHOLD];
static int life[N_PLAYER];

int checkCardhold(int cardType)
{
	if(cardType > CARDOFFSET_DOUBLE && cardType <= N_TOTAL)
	   return 0;
	else
	   return 1;
}

int checkPlayerLife(void) //player의 목숨을 확인하는 함수.
{
	int i;
	
	for(i=0;i<N_PLAYER;i++)
	{
		if(life[i] == 0)
	     break;
	    else 
	      return 1;
	}
	return 0;
		printf("\n\nGAME OVER!! PLAYER %i IS LOSE!!",i);
} 



int checkGameEnd(void)
{
    if (cumNum >= MAX_CUMNUM)
        return 0;
    else
      return 1;
}


int main(int argc, const char * argv[]) {
    
    int i,j,k,n,m;
    int gameCnt=0;
    int select,select2; //player가 선택한 숫자(1-5)
    int randturn = N_PLAYER; //turn을 바꾸기 위한 변수  
    int turn= randturn%N_PLAYER;  //turn은 0과1을 반복(player수가 달라지면 편리하게 변경할 수 있도록)
	int checkdouble,checkdouble2; //player의 선택숫자를 저장하여 x2인지 확인하기 위한 변수   
    
    for(k=0;k<N_PLAYER;k++)
	   life[k] = N_LIFE; //처음에 모든 player의 목숨을 3개로 지정//initialization
    
    //outer loop : multiple games operation
    do
    {
    	checkdouble = 0; //처음에 초기화  
	    checkdouble2 = 0; 
	
	    cGroup_initCard();
	    
        for(m=0;m<N_PLAYER;m++) //카드 나누기  
        {
        	for(n=0;n<N_CARDHOLD;n++)
        	cardHold[m][n] = cGroup_pullCard();
		}

        //one game initialization
        
        
        printf("\n\n\t [[[[[ %i'th game start!!! ]]]]]\n\n", gameCnt);
        
        
        
        //inner loop : one game operation
        do
        {
            printf("\n\n\nPLAYER %i (life %i) turn :::: (accum count : %i)\n", turn, life[turn], cumNum);
            
            printf("Current cards -------------------------------------------\n");
            for(i=0;i<N_CARDHOLD;i++)
            {   
            	printf("%i. ",i+1);
                cType_printCard(cardHold[turn][i]); 
				printf("\t");
                
			}
            printf("\n---------------------------------------------------------\n");
              //print card     
                   
            while(1)
            {
            	if(checkCardhold(checkdouble) != 0 && checkCardhold(checkdouble2) != 0) //이전 player가 선택한 숫자카드가 x2가 아닐때   
				{	printf("\n\n>>>> Select a card (1-5):");
			        scanf("%i",&select);
			    
			       if(select>=1 && select<=N_CARDHOLD)
				    {
				    	cGroup_pushCard(cardHold[turn][select-1]);  //선택한 카드를 card_opened 배열에 저장. 
			    	    break;
				    }
				   else
				    {
					  printf("input is wrong!! choose from 1 to 5!!\n");
				    }
					
					
				}
				else  //이전 player가 선택한 카드가 x2일때   
				{
				    printf("\n>>>> Select a card (1-5):");
			        scanf("%i",&select);
			        if(select>=1 && select<=N_CARDHOLD)
				    {
				    	if(cardHold[turn][select-1] > CARDOFFSET_DOUBLE && cardHold[turn][select-1] <= N_TOTAL)
				    	{
				    		printf("input is wrong!! the first card of the double case should be number!!\n"); //이전의 player가 x2를 낸 경우 다음 player는 처음으로 x2를 내지 못함. 
				    	    continue;
						}
				    	
				    	else
				    	cGroup_pushCard(cardHold[turn][select-1]);
						
				    }
				    else
				    {
				    	printf("input is wrong!! choose from 1 to 5!!\n");
                        continue;
					}
			        printf(">>>> Select a card (1-5):");
			        scanf("%i",&select2);
			        if(select2>=1 && select2<=N_CARDHOLD)
				    {
				        if(select2 == select)
				      	     printf("input is wrong!! select differnent card!!\n"); //select == select2 일때 다른 숫자를 선택하라는 메시지 출력. 
					    else
					    {
					    	cGroup_pushCard(cardHold[turn][select2-1]);
							 break; 
					    }
				    }
				    else
				    printf("input is wrong!! choose from 1 to 5!!\n");
				    
				}
			    
			} //select card while(1)문의 끝. 
			
			     
		if(checkCardhold(checkdouble) != 0 && checkCardhold(checkdouble2) != 0)  //이전 player가 선택한 숫자카드가 x2가 아닌경우. 
            {
            	printf("\n\n>>>> Putting the card ");
            	cType_printCard(cardHold[turn][select-1]);
            	checkdouble = cardHold[turn][select-1];
            	
            	cumNum = cumNum + cType_getCardNum(checkdouble); //누적 숫자 계산  
            	if(cumNum < 0)
            	{
            		cumNum = 0;
				}
				else if(cumNum >= MAX_CUMNUM)
				{
			        printf("\n!!!! PLAYER %i life lost!! (over 77)",turn);
			        life[turn]--; //목숨의 숫자가 줄어든다.  
			        cumNum = 0;
			        break;
			        
			    }
			    else if(cumNum == 11 ||cumNum == 22 || cumNum == 33 || cumNum == 44 || cumNum == 55 || cumNum == 66)
			    {
			    	printf("\n!!!! PLAYER %i life lost!! (multiple of 11)",turn);
                    life[turn]--;
				}
					   
            	cardHold[turn][select-1] = cGroup_pullCard(); //낸 카드의 배열위치에 flipped card에서 가져온 새로운 정수값 저장  
            	
			}
			else //선택한 숫자카드가 x2가 아닌 경우. 
			{
				 printf("\n>>>> Putting the card ");  
            	cType_printCard(cardHold[turn][select-1]);
				checkdouble = cardHold[turn][select-1]; 
            
            	cumNum = cumNum + cType_getCardNum(checkdouble); //cumNum 계산  
            	if(cumNum < 0)
				{
					 cumNum = 0;
				} 
				
				cardHold[turn][select-1] = cGroup_pullCard();
				
            	printf("\n>>>> Putting the card ");
            	cType_printCard(cardHold[turn][select2-1]);
            	checkdouble2 = cardHold[turn][select2-1];
            	 
            	cumNum = cumNum + cType_getCardNum(checkdouble2);
            	if(cumNum < 0)
            	{
            		cumNum = 0;
				}
				else if(cumNum >= MAX_CUMNUM)
				{
			        printf("\n!!!! PLAYER %i life lost!! (over 77)",turn);
			        life[turn]--;
			        cumNum = 0;
			        break;
			    }
			    else if(cumNum == 11 ||cumNum == 22 || cumNum == 33 || cumNum == 44 || cumNum == 55 || cumNum == 66)
			    {
			    	printf("\n!!!! PLAYER %i life lost!! (multiple of 11)",turn);
                    life[turn]--;
				}
				
				cardHold[turn][select2-1] = cGroup_pullCard();
            	
			}  //check putting card (player가 뽑은 숫자카드의 real 숫자)
            
            if(life[turn] == 0)
            break;
            
            	
			randturn++;
			turn = randturn%N_PLAYER;   //move to next turn
			
			
        }while(checkGameEnd() != 0); //while(checkGameEnd() == 0)문의 끝. 
        
        gameCnt++;
        
        if(life[turn] == 0)
            break;

    }while (checkPlayerLife() != 0);  //while (checkPlayerLife() == 0)의 끝. 
    
    
    return 0;
} //main 함수의 끝. 
