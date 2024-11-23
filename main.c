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

int checkPlayerLife(void) //player�� ����� Ȯ���ϴ� �Լ�.
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
    int select,select2; //player�� ������ ����(1-5)
    int randturn = N_PLAYER; //turn�� �ٲٱ� ���� ����  
    int turn= randturn%N_PLAYER;  //turn�� 0��1�� �ݺ�(player���� �޶����� ���ϰ� ������ �� �ֵ���)
	int checkdouble,checkdouble2; //player�� ���ü��ڸ� �����Ͽ� x2���� Ȯ���ϱ� ���� ����   
    
    for(k=0;k<N_PLAYER;k++)
	   life[k] = N_LIFE; //ó���� ��� player�� ����� 3���� ����//initialization
    
    //outer loop : multiple games operation
    do
    {
    	checkdouble = 0; //ó���� �ʱ�ȭ  
	    checkdouble2 = 0; 
	
	    cGroup_initCard();
	    
        for(m=0;m<N_PLAYER;m++) //ī�� ������  
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
            	if(checkCardhold(checkdouble) != 0 && checkCardhold(checkdouble2) != 0) //���� player�� ������ ����ī�尡 x2�� �ƴҶ�   
				{	printf("\n\n>>>> Select a card (1-5):");
			        scanf("%i",&select);
			    
			       if(select>=1 && select<=N_CARDHOLD)
				    {
				    	cGroup_pushCard(cardHold[turn][select-1]);  //������ ī�带 card_opened �迭�� ����. 
			    	    break;
				    }
				   else
				    {
					  printf("input is wrong!! choose from 1 to 5!!\n");
				    }
					
					
				}
				else  //���� player�� ������ ī�尡 x2�϶�   
				{
				    printf("\n>>>> Select a card (1-5):");
			        scanf("%i",&select);
			        if(select>=1 && select<=N_CARDHOLD)
				    {
				    	if(cardHold[turn][select-1] > CARDOFFSET_DOUBLE && cardHold[turn][select-1] <= N_TOTAL)
				    	{
				    		printf("input is wrong!! the first card of the double case should be number!!\n"); //������ player�� x2�� �� ��� ���� player�� ó������ x2�� ���� ����. 
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
				      	     printf("input is wrong!! select differnent card!!\n"); //select == select2 �϶� �ٸ� ���ڸ� �����϶�� �޽��� ���. 
					    else
					    {
					    	cGroup_pushCard(cardHold[turn][select2-1]);
							 break; 
					    }
				    }
				    else
				    printf("input is wrong!! choose from 1 to 5!!\n");
				    
				}
			    
			} //select card while(1)���� ��. 
			
			     
		if(checkCardhold(checkdouble) != 0 && checkCardhold(checkdouble2) != 0)  //���� player�� ������ ����ī�尡 x2�� �ƴѰ��. 
            {
            	printf("\n\n>>>> Putting the card ");
            	cType_printCard(cardHold[turn][select-1]);
            	checkdouble = cardHold[turn][select-1];
            	
            	cumNum = cumNum + cType_getCardNum(checkdouble); //���� ���� ���  
            	if(cumNum < 0)
            	{
            		cumNum = 0;
				}
				else if(cumNum >= MAX_CUMNUM)
				{
			        printf("\n!!!! PLAYER %i life lost!! (over 77)",turn);
			        life[turn]--; //����� ���ڰ� �پ���.  
			        cumNum = 0;
			        break;
			        
			    }
			    else if(cumNum == 11 ||cumNum == 22 || cumNum == 33 || cumNum == 44 || cumNum == 55 || cumNum == 66)
			    {
			    	printf("\n!!!! PLAYER %i life lost!! (multiple of 11)",turn);
                    life[turn]--;
				}
					   
            	cardHold[turn][select-1] = cGroup_pullCard(); //�� ī���� �迭��ġ�� flipped card���� ������ ���ο� ������ ����  
            	
			}
			else //������ ����ī�尡 x2�� �ƴ� ���. 
			{
				 printf("\n>>>> Putting the card ");  
            	cType_printCard(cardHold[turn][select-1]);
				checkdouble = cardHold[turn][select-1]; 
            
            	cumNum = cumNum + cType_getCardNum(checkdouble); //cumNum ���  
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
            	
			}  //check putting card (player�� ���� ����ī���� real ����)
            
            if(life[turn] == 0)
            break;
            
            	
			randturn++;
			turn = randturn%N_PLAYER;   //move to next turn
			
			
        }while(checkGameEnd() != 0); //while(checkGameEnd() == 0)���� ��. 
        
        gameCnt++;
        
        if(life[turn] == 0)
            break;

    }while (checkPlayerLife() != 0);  //while (checkPlayerLife() == 0)�� ��. 
    
    
    return 0;
} //main �Լ��� ��. 
