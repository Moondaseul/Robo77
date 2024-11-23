#include "cardType.h"
#include <stdio.h>



void cType_printCard(int cardType)//cType_getCardNum 함수의 반환값을 출력 (실제 숫자카드의 number 출력) 
{
	 
	if(cardType > CARDOFFSET_2TO9 && cardType <= CARDOFFSET_MINUS )
	{
	    printf("%i",cType_getCardNum(cardType));  
	}
   	else if(cardType> CARDOFFSET_MINUS && cardType <= CARDOFFSET_DOUBLE )
	{
		printf("-10");
	}
	else if(cardType > CARDOFFSET_DOUBLE && cardType <= N_TOTAL)
	{
		printf("x2");
	}
	 
}

int cType_getCardNum(int cardType)
{
	if(cardType > CARDOFFSET_2TO9 && cardType <= CARDOFFSET_TEN) //1-24
	{
		switch(cardType)
	    {
		   case 1:
	       case 2:
	       case 3:
	    	  return 2;
	    	  break;
	       case 4:
	       case 5:
	       case 6:
	          return 3;
	    	  break;
	       case 7:
	       case 8:
	       case 9:
	    	  return 4;
	    	  break;
	       case 10:
	       case 11:
	       case 12:
	    	  return 5;
	    	  break;
	       case 13:
	       case 14:
	       case 15:
	    	  return 6;
	    	  break;
	       case 16:
	       case 17:
	       case 18:
	    	  return 7;
	    	  break;
	       case 19:
	       case 20:
	       case 21:
	    	  return 8;
	    	  break;
	       case 22:
	       case 23:
	       case 24:
	    	  return 9;
			  break; 
	    }
	}
	else if(cardType > CARDOFFSET_TEN  && cardType <= CARDOFFSET_11N) //25-32
	{
		switch(cardType)
	    {
		   case 25:
		   case 26:
		   case 27:
		   case 28:
		   case 29:
		   case 30:
		   case 31:
		   case 32:
			  return 10;
			  break;
	    }
	}
	else if(cardType > CARDOFFSET_11N && cardType <= CARDOFFSET_ZERO) //33-39
	{
		switch(cardType)
	    {
		   case 33:
			  return 11;
			  break;
		   case 34:
			  return 22;
			  break;
		   case 35:
			  return 33;
			  break;
		   case 36:
			  return 44;
			  break;
		   case 37:
			  return 55;
			  break;
		   case 38:
			  return 66;
			  break;
		   case 39:
			  return 76;
			  break;
	    }
	}
	else if(cardType > CARDOFFSET_ZERO && cardType <= CARDOFFSET_MINUS)//40-43
	{
		switch(cardType)
	    {
		   case 40:
		   case 41:
		   case 42:
		   case 43:
			  return 0;
			  break;
	    }
	}
	else if(cardType > CARDOFFSET_MINUS && cardType <= CARDOFFSET_DOUBLE)//44-47
	{
		switch(cardType)
	    {
		   case 44:
		   case 45:
		   case 46:
		   case 47:
			  return -10;//반환값  
			  break;
	    }
	}
	else if(cardType > CARDOFFSET_DOUBLE && cardType <= N_TOTAL) //48-51
	{
		switch(cardType)
	    {
		   case 48:
		   case 49:
		   case 50:
		   case 51:
			  return 0;//반환값 (cumNum을 계산할 때 편리하게 반환값을 0으로 설정)
			  break;
	    }
	}
	
	

    
    //offset이 0인건 2-9까지의 숫자
	//offset이 24인건 10의 숫자카드
	//offset이 32인건 11의배수 카드(11,22,33,44,55,66)
	//offset이 38인건 76의 숫자카드
	//offset이 39인건 0의 카드
	//offset이 43인건 -10의 숫자카드
	//offset이 47인건 x2의 숫자카드  
}
