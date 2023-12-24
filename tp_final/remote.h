
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>
#include <fcntl.h> 
#include <unistd.h> 




int serialPort;

void send(){
	
	int seqsend, rts;

	if ((serialPort = serialOpen ("/dev/ttyS0", 9600)) < 0)
	{
		fprintf (stderr, "ERROR: %s\n", strerror (errno));
		delay (1000);
		return;
	}

	if (wiringPiSetup () == -1)
	{
		fprintf (stdout, "ERROR: %s\n", strerror (errno));
		delay (1000);
		return;
	}
	
	
	do{
	system ("clear");
	printf("Seleccione la secuencia a TRANSMITIR y presione ENTER\n");
	printf("Ingrese un numero del 1 al 8 para elegir la secuencia a realizar \n");
            printf("1: Auto fantastico \n");
            printf("2: Carrera \n");
            printf("3: Apilada\n");
            printf("4: Choque\n");
            printf("5: Par impar \n");
            printf("6: Blinker \n");
            printf("7: Danza kuduro\n");
            printf("8: Test Bronco\n");
	scanf("%d",&seqsend);
	
	printf("%d \n",seqsend);
	
	serialPutchar (serialPort, (char) seqsend);

	
	switch(seqsend){
	/*	case 1: autof();
				break;
				
		case 2: choque();
				break;
	
		case 3: apilada();
				break;
	
		case 4: carrera();
				break;
	
		case 5: seq5();
				break;
	
		case 6: seq6();
				break;
	
		case 7: seq7();
				break;
	
		case 8: seq8();
				break;
	*/			
		case '9': printf("Saliendo del programa\n");
				break;			
	
		default: printf("Seleccion invalida\n");
				break;
			}
	
	
}while(seqsend!=9);
	
	
	}
	
char receive(){
	
	char seqreceive;

	if ((serialPort = serialOpen ("/dev/ttyS0", 9600)) < 0)
	{
		fprintf (stderr, "ERROR: %s\n", strerror (errno));
		delay (1000);
		return 'a';
	}

wiringPiSetup ();
	
	
	
		
	system ("clear");
	printf("Recibiendo secuencia a ejecutar\n");
    printf("*******************************\n");
    printf("*******************************\n");
	
 

	seqreceive = serialGetchar (serialPort);
	
	printf("Ejecutando secuencia\n");
	return seqreceive;
	
	

}
	
	
	
	
char remote (){
	
	int com;
	char control_remoto ='a';
	
	system ("clear");
	
	do{
	
	printf("1-Enviar a otro dispositivo\n");
	printf("2-Recibir de otro dispositivo\n");
	printf("3-Volver al modo local\n");
	scanf ("%d", &com);

	switch(com){
		case 1: send();
				break;
				
		case 2: control_remoto = receive();
				break;
	
		case 3: 
				break;
	
		default: printf("Seleccion invalida\n");
				break;
			}
	}while(com!=3);
	
	
	return control_remoto;

	
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
