#include <stdio.h>
#include "cardGroup.h"
#include "cardType.h"
#include "stdlib.h"
#include "time.h"

#define CARD_NONE       -1

int card_flipped[N_TOTAL];
int card_opened[N_TOTAL];
int cnt_flipped;
int cnt_opened;


static void cGroup_shuffleCard(int Ncard, int clearOption) //flipped card를 만드는 함수  (51개 카드를 표현하는 정수값을 배열로 저장)  
{
	int i,j,k,l,n,m,s,p;
	int inflipped[Ncard];
	
	if(clearOption == 1) 
	{
		for(i=0;i<Ncard;i++) //1~N-1 난수 생성 후 flipped card에 배열로 저장.
		{
			card_flipped[i] = 1+rand()%Ncard;
			
			for(j=0;j<i;j++) //숫자가 중복되지 않게 저장되어야함. 
			{
				if(card_flipped[i] == card_flipped[j])  
				    i--;
			}
		}
		
		
	}
	else if(clearOption == 0) //opened card끼리만 섞는 함수  
	{
		for(k=0;k<Ncard;k++)
		{
			inflipped[k] = 1+rand()%Ncard; //opened card의 배열 번호를 랜덤으로 섞음  
			for(l=0;l<k;l++)
			{
				if(inflipped[k] == inflipped[l]) //중복되지 않도록 저장  
				    k--;
			}

		}
		
		for(n=0;n<Ncard;n++)  //card_opened의 정수값을 card_flipped에 랜덤하게 저장 (opened 배열에서 flipped 배열로 옮긴다)
		{
			card_flipped[n] = card_opened[inflipped[k]];
		}
		
		cnt_opened = 0;
		cnt_flipped = Ncard; 
	
	}
		    
}  


void cGroup_initCard(void) //초기화 (새로운 게임 시작) 
{
	cnt_flipped = N_TOTAL;
    cnt_opened = 0;
    
    srand((unsigned int)time(NULL));
    cGroup_shuffleCard(N_TOTAL, 1); //랜덤 숫자를 flipped 배열에 저장함. 
}

int cGroup_pullCard(void)   //flipped card 에서 한장을 가져옴  
{	
	
	cnt_flipped--;
	if(cnt_flipped == 0) //flipped 더미에 카드가 없을 때 opened card끼리 다시 섞음. 
	{
		srand((unsigned int)time(NULL));
        cGroup_shuffleCard(cnt_opened, 0);
        
        return card_flipped[cnt_flipped];
	}
	else
	{
		return card_flipped[cnt_flipped];
	}
}

void cGroup_pushCard(int cardType)  //opened card에 한장을 내려놓음 
{
	card_opened[cnt_opened] = cardType;
	cnt_opened++;
}  
