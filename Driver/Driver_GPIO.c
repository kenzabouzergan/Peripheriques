#include "Driver_GPIO.h"
#include "stm32f10x.h"
 
// Initialise un GPIO avec la configuration souhait�e
void MyGPIO_Init ( MyGPIO_Struct_TypeDef* GPIOStructPtr )
{
    // VERIFIER INIT TIMER DU GPIO CONCERNE
    if (GPIOStructPtr->GPIO == GPIOA)
    {
        RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    }     
    else if (GPIOStructPtr->GPIO == GPIOB)
    {
        RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    }
    else
    {
        RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    }
    
    // D�termination CRH/CRL en fonction du pin
    if(GPIOStructPtr->GPIO_Pin < 8)
    {
        GPIOStructPtr->GPIO->CRL &= ~(0xF << ((GPIOStructPtr->GPIO_Pin%8)*4));
        
        // Configuration
        if (GPIOStructPtr->GPIO_Conf == In_PullUp)
        {
            // Cas sp�cifique Pullup : on place le bit ODR correspondant � 1
            MyGPIO_Set(GPIOStructPtr->GPIO, GPIOStructPtr->GPIO_Pin);
            GPIOStructPtr->GPIO->CRL |= (In_PullDown << ((GPIOStructPtr->GPIO_Pin%8)*4));
        }
        else if (GPIOStructPtr->GPIO_Conf == In_PullDown)
        {
            // Cas sp�cifique Pulldown : on place le bit ODR correspondant � 0
            MyGPIO_Reset(GPIOStructPtr->GPIO, GPIOStructPtr->GPIO_Pin);
            GPIOStructPtr->GPIO->CRL |= (In_PullDown << ((GPIOStructPtr->GPIO_Pin%8)*4));
        }
        else
        {
            GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << ((GPIOStructPtr->GPIO_Pin%8)*4));
        }
    }
    else
    {
        GPIOStructPtr->GPIO->CRH &= ~(0xF << ((GPIOStructPtr->GPIO_Pin%8)*4));
        
        // Configuration
        if (GPIOStructPtr->GPIO_Conf == In_PullUp)
        {
            // Cas sp�cifique Pullup : on place le bit ODR correspondant � 1
            MyGPIO_Set(GPIOStructPtr->GPIO, GPIOStructPtr->GPIO_Pin);
            GPIOStructPtr->GPIO->CRH |= (In_PullDown << ((GPIOStructPtr->GPIO_Pin%8)*4));
        }
        else if (GPIOStructPtr->GPIO_Conf == In_PullDown)
        {
            // Cas sp�cifique Pulldown : on place le bit ODR correspondant � 0
            MyGPIO_Reset(GPIOStructPtr->GPIO, GPIOStructPtr->GPIO_Pin);
            GPIOStructPtr->GPIO->CRH |= (In_PullDown << ((GPIOStructPtr->GPIO_Pin%8)*4));
        }
        else
        {
            GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << ((GPIOStructPtr->GPIO_Pin%8)*4));
        }
    }
}
//Lire l'�tat initial d'un pin (true si 1)
int MyGPIO_Read (GPIO_TypeDef * GPIO, char GPIO_Pin)
{
	return GPIO->IDR & (1<<GPIO_Pin); 
}

//Set l'output � 1
void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) 
{
	GPIO->ODR |= (1<<GPIO_Pin);
}

//Set l'output � 0
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) 
{
	GPIO->ODR&=~(1<<GPIO_Pin);
}

//Toggle 
void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) 
{
	if (MyGPIO_Read(GPIO, GPIO_Pin))
	{
		MyGPIO_Reset(GPIO, GPIO_Pin); 
	}
	else
	{
		MyGPIO_Set(GPIO, GPIO_Pin);
	}
}
