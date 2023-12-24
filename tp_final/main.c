#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>
#include <string.h>
#include "secuencia.h"
#include <termios.h>
#include "remote.h"
//#include "speed.h"
#include "ADC.h"
//#include "updatedspeed.h"


int main(void){

    int  velocidad;
    char password[] = "12345"; // Contrasena
    char inputPassword[6] = ""; // Almacena la contrasena ingresada por el usuario
    int intentos = 0;
    char teclado;
    struct termios t_old, t_new ;
    int opcion;
    char salida = 'n';
    int modo;
    char control_remoto = 'a';
 
    tcgetattr (0 , & t_old );
    t_new = t_old ;
    t_new . c_lflag &= ~( ECHO | ICANON ) ;
    tcsetattr (0 , TCSANOW , & t_new ) ;

    printf("Ingrese su password de 5 dgitos: ");
    printf("Posee 3 intentos \n");
    while (intentos < 3) {
        for (int i = 0; i < 5; i++) {
            teclado = getchar();
            if (teclado == 10) {
                    break;
            }
            inputPassword[i] = teclado;
            printf("*");
        }
        printf("\n");

        if (strcmp(inputPassword, password) == 0) {
        
        system ("clear");
        printf("Bienvenido al Sistema\n");
        printf("Seleccione el modo de trabajo \n");
        printf("1-Local \n");
        printf("2-Remoto \n");
        modo = getchar();
        
        
		if(modo==2){
			control_remoto = remote();
			modo=1;
		system ("clear");	
			}
            
        while(salida == 'n'){
            
        if (control_remoto == 'a'){
            system ("clear");            
            printf("Ingrese un numero del 1 al 8 para elegir la secuencia a realizar \n");
            printf("1: Auto fantastico \n");
            printf("2: Carrera \n");
            printf("3: Apilada\n");
            printf("4: Choque\n");
            printf("5: Par impar \n");
            printf("6: Blinker \n");
            printf("7: Danza kuduro\n");
            printf("8: Test Bronco\n");
            opcion = getchar();
        }else{
            
            opcion = control_remoto;
            }
            
  /*          
            while (opcion <= 0 || opcion > 2){
                printf("Ingrese un numero \n");
                opcion = getchar();
                }
*/

            switch(opcion) {
                    case '1': {
                        system ("clear");
                        printf("Se esta ejecutando el auto-fantastico, si desea salir pulse algun boton\n");
                        printf("Seleccione la velocidad con el potenciometro, posee 5 segundos\n");
                        usleep(5000000);
                        velocidad= adc();
                        auto_fantastico(velocidad);
                        break;
                        }
                    case '2':{
                        system ("clear");
                        printf("Se esta ejecutando la carrera, si desea salir pulse algun boton\n");
                        printf("Seleccione la velocidad con el potenciometro, posee 5 segundos\n");
                        usleep(500000);
                        velocidad= adc();
                        carrera(velocidad);
                        break;
                        }
                    case '3':{
                        system ("clear");
                        printf("Se esta ejecutando la apilada, si desea salir pulse algun boton\n");
                        printf("Seleccione la velocidad con el potenciometro, posee 5 segundos\n");
                        usleep(5000000);
                        velocidad= adc();
                        apilada(velocidad);
                        break;
                        }
                    case '4':{
                        system ("clear");
                        printf("Se esta ejecutando el choque, si desea salir pulse algun boton\n");
                        printf("Seleccione la velocidad con el potenciometro, posee 5 segundos\n");
                        usleep(5000000);
                        velocidad= adc();
                        choque(velocidad);
                        break;
                        }
                    case '5':{
                        system ("clear");
                        printf("Se esta ejecutando par-impar, si desea salir pulse algun boton\n");
                        printf("Seleccione la velocidad con el potenciometro, posee 5 segundos\n");
                        usleep(5000000);
                        velocidad= adc();
                        parimpar(velocidad);
                        break;
                        }
                    case '6':{
                        system ("clear");
                        printf("Se esta ejecutando bliker, si desea salir pulse algun boton\n");
                        printf("Seleccione la velocidad con el potenciometro, posee 5 segundos\n");
                        usleep(5000000);
                        velocidad= adc();
                        blinker(velocidad);
                        break;
                        }
                    case '7':{
                        system ("clear");
                        printf("Se esta ejecutando danza kuduro, si desea salir pulse algun boton\n");
                        printf("Seleccione la velocidad con el potenciometro, posee 5 segundos\n");
                        usleep(5000000);
                        velocidad= adc();
                        danzakuduro(velocidad);
                        break;
                        }
                    case '8':{
                        system ("clear");
                        printf("Se esta ejecutando testbronco, si desea salir pulse algun boton\n");
                        printf("Seleccione la velocidad con el potenciometro, posee 5 segundos\n");
                        usleep(5000000);
                        velocidad= adc();
                        testbronco(velocidad);
                        break;
                        }
                    default: printf("Error");
            }

system ("clear");
printf("Desea salir? \n  ");
printf("Presione n para seguir \n");
printf("Presione cualquier otra tecla para salir \n");
salida = getchar();

salir();

}
return 0;
    }else{
            printf("Password no valida\n");
            intentos++;
            if (intentos < 3) {
                printf("Intente de nuevo (%d intentos restantes): ", 3 - intentos);
            }

        }
    }

    if (intentos == 3) {
    printf("Tres intentos fallidos.\n");
    }
    tcsetattr(0, TCSANOW, &t_old); //no es necesario debido a que se ejecuta en las sentencias
    
        return 0;
}
