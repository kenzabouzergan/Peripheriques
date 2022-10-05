#include "stm32f10x.h"
#include "Driver_GPIO.h"

int main(void)
{
MyGPIO_Struct_TypeDef GPIO_Struct;
MyGPIO_Struct_TypeDef GPIO_Struct2;
	
GPIO_Struct.GPIO=GPIOC;
GPIO_Struct.GPIO_Pin=8;
GPIO_Struct.GPIO_Conf = In_Floating;
	
GPIO_Struct2.GPIO=GPIOC;
GPIO_Struct2.GPIO_Pin=10;
GPIO_Struct2.GPIO_Conf = Out_Ppull;
	
MyGPIO_Init(& GPIO_Struct);
MyGPIO_Init(& GPIO_Struct2);
	


while(1) {
	//Code vérifier les fonctions (à utiliser en faisant un step over pour vérifier chaque fonction à son tour)	
	MyGPIO_Set(GPIO_Struct2.GPIO,GPIO_Struct2.GPIO_Pin);
	MyGPIO_Read(GPIO_Struct.GPIO,GPIO_Struct.GPIO_Pin);
	MyGPIO_Reset(GPIO_Struct2.GPIO,GPIO_Struct2.GPIO_Pin);
	MyGPIO_Read(GPIO_Struct.GPIO,GPIO_Struct.GPIO_Pin);
	MyGPIO_Toggle(GPIO_Struct2.GPIO,GPIO_Struct2.GPIO_Pin);
	MyGPIO_Read(GPIO_Struct.GPIO,GPIO_Struct.GPIO_Pin);

	
	
}
}