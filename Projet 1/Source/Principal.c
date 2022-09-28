#include "stm32f10x.h"

int main ( void )

{
//RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;
//Poussoir Pullup
GPIOC -> CRH &=~(0xF);
GPIOC -> CRH |= (8 <<0);
//LED Open drain 
GPIOC -> CRH &=~ (0xF << 8);
GPIOC -> CRH |= (6 << 8);	
//Boucle infini 

	//Boucle inf
	
do
	{
		//3.3 allume la led quand on apppuie sur le bouton en opendrain
		if (GPIOC -> IDR & GPIO_IDR_IDR8) //si bouton appuyé 
{
	 GPIOC -> ODR |=GPIO_ODR_ODR10 ;
}
	else 
	{
	GPIOC -> ODR &=~GPIO_ODR_ODR10 ; //laisser led eteinte  
	}
	
	MyGPIO_Init ( MyGPIO_Struct_TypeDef* GPIOStructPtr )
	} while(1);
}
