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


static void cGroup_shuffleCard(int Ncard, int clearOption) //flipped card�� ����� �Լ�  (51�� ī�带 ǥ���ϴ� �������� �迭�� ����)  
{
	int i,j,k,l,n,m,s,p;
	int inflipped[Ncard];
	
	if(clearOption == 1) 
	{
		for(i=0;i<Ncard;i++) //1~N-1 ���� ���� �� flipped card�� �迭�� ����.
		{
			card_flipped[i] = 1+rand()%Ncard;
			
			for(j=0;j<i;j++) //���ڰ� �ߺ����� �ʰ� ����Ǿ����. 
			{
				if(card_flipped[i] == card_flipped[j])  
				    i--;
			}
		}
		
		
	}
	else if(clearOption == 0) //opened card������ ���� �Լ�  
	{
		for(k=0;k<Ncard;k++)
		{
			inflipped[k] = 1+rand()%Ncard; //opened card�� �迭 ��ȣ�� �������� ����  
			for(l=0;l<k;l++)
			{
				if(inflipped[k] == inflipped[l]) //�ߺ����� �ʵ��� ����  
				    k--;
			}

		}
		
		for(n=0;n<Ncard;n++)  //card_opened�� �������� card_flipped�� �����ϰ� ���� (opened �迭���� flipped �迭�� �ű��)
		{
			card_flipped[n] = card_opened[inflipped[k]];
		}
		
		cnt_opened = 0;
		cnt_flipped = Ncard; 
	
	}
		    
}  


void cGroup_initCard(void) //�ʱ�ȭ (���ο� ���� ����) 
{
	cnt_flipped = N_TOTAL;
    cnt_opened = 0;
    
    srand((unsigned int)time(NULL));
    cGroup_shuffleCard(N_TOTAL, 1); //���� ���ڸ� flipped �迭�� ������. 
}

int cGroup_pullCard(void)   //flipped card ���� ������ ������  
{	
	
	cnt_flipped--;
	if(cnt_flipped == 0) //flipped ���̿� ī�尡 ���� �� opened card���� �ٽ� ����. 
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

void cGroup_pushCard(int cardType)  //opened card�� ������ �������� 
{
	card_opened[cnt_opened] = cardType;
	cnt_opened++;
}  
