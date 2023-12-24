/*
"El auto fantástico", "El choque", "La apilada" y "La carrera"

Auto fantástico: una luz que se desplaza de izquierda a derecha y de derecha a izquierda.

El choque: una luz desde la izquierda y otra desde la derecha comienzan su recorrido en forma opuesta y por lo tanto al medio se cruzan y 
continúan hasta los extremos opuestos. En la visualización de la misma parece que las luces chocan y se repelen.

La apilada: Una luz arranca de izquierda a derecha y cuando alcanza el extremo derecho, parpàdea y se queda encendida en la última posición; 
a partir de allí una nueva luz comienza su recorrido desde la izquierda y se desplaza hacia la derecha hasta llegar a la posición anterior 
a la que está fija, parpadea y también se queda quieta como la anterior. Ahora son dos las luces quietas y se repite el mismo proceso para 
una nueva luz arrancando por la izquierda y llegando a la posición anterior a las dos quietas. La secuencia termina cuando los ocho lugares 
han sido ocupados de la forma descripta.

La carrera: Una luz arranca por la izquierda a una determinada velocidad, y cuando va por la mitad del recorrido arranca una nueva luz por la izquierda pero al 
doble de velocidad lo que produce que arriben al extremo derecho al mismo tiempo.

La técnica de tabla de datos consiste en simplemente un bucle de programa que saca por los puertos de salida el 
contenido de una tabla preestablecida con valores que reproducen la secuencia deseada.


La técnica de tabla de datos consiste en simplemente un bucle de programa que saca por los puertos de salida el contenido de una tabla 
preestablecida con valores que reproducen la secuencia deseada.


*/

#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <termios.h>
//#include "updatedspeed.h"


    
    int ledPins[6] = {0, 1, 2, 3, 4, 5}; // Pines GPIO utilizados para los LED
    //const int botonesVel [2]={6,7};
    //const int numbotonesVel = sizeof(botonesVel) / sizeof(botonesVel[0]);
    int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);
    
    struct termios t_old1 , t_new1 ;
    char teclado1 = 0;
    int rd ;


int auto_fantastico (int velocidad){
    
printf("Se encuentra dentro del auto fantastico.\n");
wiringPiSetup();
    
    // Configurar los pines de los LED como pines de salida
for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
    }
    

        
tcgetattr (0 , & t_old1 );
t_new1 = t_old1 ;
t_new1 . c_lflag &= ~( ECHO | ICANON ) ;
t_new1 . c_cc [ VMIN ]=0;
t_new1 . c_cc [ VTIME ]=0;
tcsetattr (0 , TCSANOW , & t_new1 ) ;

    while (1) {
        // Secuencia de izquierda a derecha
        for (int i = 0; i < numLeds; i++) {
            digitalWrite(ledPins[i], HIGH);
            usleep(velocidad);
            digitalWrite(ledPins[i], LOW);
            usleep(velocidad);
            
            rd = read (0 , &teclado1 , 1) ;
            if ( rd > 0)
            {
                tcsetattr (0 , TCSANOW , & t_old1 ) ;
                return 0;
            }
        }

        // Secuencia de derecha a izquierda
        for (int i = numLeds - 1; i >= 0; i--) {
            digitalWrite(ledPins[i], HIGH);
            usleep(velocidad);
            digitalWrite(ledPins[i], LOW);
             usleep(velocidad);
             
             rd = read (0 , &teclado1 , 1) ;
            if ( rd > 0)
            {
                tcsetattr (1 , TCSANOW , & t_old1 ) ;
                return 0;
            }
        }
        printf("Secuencia de luces completada.\n");
    }

    // Opcional: Restaurar la configuración de la terminal
    // tcsetattr(0, TCSANOW, &oldSettings);

    return 0;
}

int carrera (int velocidad){

const int numPasos = 12; // Nmero de pasos de tiempo para la secuencia (ajustado a 12)
const int velocidad_carrera = velocidad/2; // Velocidad de la segunda luz

const int secuencia [][6] = {
{1, 0, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0},
{0, 0, 1, 0, 0, 0},
{1, 0, 0, 1, 0, 0},
{0, 1, 0, 1, 0, 0},
{0, 0, 1, 0, 1, 0},
{0, 0, 0, 1, 1, 0},
{0, 0, 0, 0, 1, 1},
{0, 0, 0, 0, 0, 1}
};

wiringPiSetup();
    // Configurar los pines de los LED como pines de salida
for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
}

tcgetattr (0 , & t_old1);
t_new1 = t_old1 ;
t_new1 . c_lflag &= ~( ECHO | ICANON ) ;
t_new1 . c_cc [ VMIN ]=0;
t_new1 . c_cc [ VTIME ]=0;
tcsetattr (1 , TCSANOW , & t_new1 ) ;

while (1) {
    for (int paso = 0; paso < numPasos; paso++) {
        for (int led = 0; led < numLeds; led++) {
            digitalWrite(ledPins[led], secuencia[paso][led]);
            usleep((led == 1) ? velocidad_carrera : velocidad);
            
            rd = read (0 , &teclado1 , 1) ;
            if ( rd > 0)
            {
                tcsetattr (0 , TCSANOW , & t_old1 ) ;
                return 0;
            }
        }
    }   
    printf("Secuencia de luces completada.\n");
}


    return 0;
}

int apilada (int velocidad){

const int numPasos2 = 30; // Nmero de pasos de tiempo para la secuencia (ajustado a 30)

const int secuencia [][6] = {
{1, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0},
{0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 1, 0},
{0, 0, 0, 0, 0, 1},
{0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 1},
{0, 1, 0, 0, 0, 1},
{0, 0, 1, 0, 0, 1},
{0, 0, 0, 1, 0, 1},
{0, 0, 0, 0, 1, 1},
{0, 0, 0, 0, 0, 1},
{0, 0, 0, 0, 1, 1},
{1, 0, 0, 0, 1, 1},
{0, 1, 0, 0, 1, 1},
{0, 0, 1, 0, 1, 1},
{0, 0, 0, 1, 1, 1},
{0, 0, 0, 0, 1, 1},
{0, 0, 0, 1, 1, 1},
{1, 0, 0, 1, 1, 1},
{0, 1, 0, 1, 1, 1},
{0, 0, 1, 1, 1, 1},
{0, 0, 0, 1, 1, 1},
{1, 0, 1, 1, 1, 1},
{0, 1, 1, 1, 1, 1},
{0, 0, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1},
{0, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1}
};

wiringPiSetup();
    // Configurar los pines de los LED como pines de salida
for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
}

tcgetattr (0 , & t_old1);
t_new1 = t_old1 ;
t_new1 . c_lflag &= ~( ECHO | ICANON ) ;
t_new1 . c_cc [ VMIN ]=0;
t_new1 . c_cc [ VTIME ]=0;
tcsetattr (1 , TCSANOW , & t_new1 ) ;

printf("Se encuentra dentro de la apilada.\n");

while (1) {
    for (int paso = 0; paso < numPasos2; paso++) {
        for (int led = 0; led < numLeds; led++) {
            
            digitalWrite(ledPins[led], secuencia[paso][led]);
            
            usleep(velocidad);
           
            rd = read (0 , &teclado1 , 1) ;
            if ( rd > 0)
            {
                tcsetattr (0 , TCSANOW , & t_old1 ) ;
                return 0;
            }
        }
    } 
    printf("Secuencia de luces completada.\n");  
}
    return 0;
}

int choque (int velocidad){
    
const int numPasos3 = 5; // Nmero de pasos de tiempo para la secuencia (ajustado a 5)

const int secuencia [][6] = {
{1, 0, 0, 0, 0, 1},
{0, 1, 0, 0, 1, 0},
{0, 0, 1, 1, 0, 0},
{0, 1, 0, 0, 1, 0},
{1, 0, 0, 0, 0, 1}
};

wiringPiSetup();
    // Configurar los pines de los LED como pines de salida
for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
}

tcgetattr (0 , & t_old1);
t_new1 = t_old1 ;
t_new1 . c_lflag &= ~( ECHO | ICANON ) ;
t_new1 . c_cc [ VMIN ]=0;
t_new1 . c_cc [ VTIME ]=0;
tcsetattr (1 , TCSANOW , & t_new1 ) ;

printf("Se encuentra dentro del choque.\n");

while (1) {
    for (int paso = 0; paso < numPasos3; paso++) {
        for (int led = 0; led < numLeds; led++) {
            
            digitalWrite(ledPins[led], secuencia[paso][led]);
            
            usleep(velocidad);
           
            rd = read (0 , &teclado1 , 1) ;
            if ( rd > 0)
            {
                tcsetattr (0 , TCSANOW , & t_old1 ) ;
                return 0;
            }
        }
    } 
    printf("Secuencia de luces completada.\n");  
}
    return 0;
}

int parimpar(int velocidad4) {

printf("Se encuentra dentro de par impar.\n");
wiringPiSetup();
    
// Configurar los pines de los LED como pines de salida
for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
    }
       
tcgetattr (0 , & t_old1 );
t_new1 = t_old1 ;
t_new1 . c_lflag &= ~( ECHO | ICANON ) ;
t_new1 . c_cc [ VMIN ]=0;
t_new1 . c_cc [ VTIME ]=0;
tcsetattr (0 , TCSANOW , & t_new1 ) ;

while (1) {
        digitalWrite(ledPins[0], HIGH);
        digitalWrite(ledPins[3], HIGH);
        digitalWrite(ledPins[5], HIGH);
        usleep(velocidad4);
        digitalWrite(ledPins[0], LOW);
        digitalWrite(ledPins[3], LOW);
        digitalWrite(ledPins[5], LOW);
        usleep(velocidad4);
        digitalWrite(ledPins[2], HIGH);
        digitalWrite(ledPins[4], HIGH);
        digitalWrite(ledPins[6], HIGH);
        usleep(velocidad4);
        digitalWrite(ledPins[2], LOW);
        digitalWrite(ledPins[4], LOW);
        digitalWrite(ledPins[6], LOW);
        usleep(velocidad4);

            rd = read (0 , &teclado1 , 1) ;
            if ( rd > 0)
            {
                tcsetattr (0 , TCSANOW , & t_old1 ) ;
                return 0;
            }
        printf("Secuencia de luces completada.\n");
        usleep(velocidad4); // Tiempo de espera antes de la siguiente secuencia
    }
    return 0;
}

int blinker (int velocidad5){
    
printf("Se encuentra dentro de blinker.\n");
wiringPiSetup();
    
// Configurar los pines de los LED como pines de salida
for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
    }
            
tcgetattr (0 , & t_old1 );
t_new1 = t_old1 ;
t_new1 . c_lflag &= ~( ECHO | ICANON ) ;
t_new1 . c_cc [ VMIN ]=0;
t_new1 . c_cc [ VTIME ]=0;
tcsetattr (0 , TCSANOW , & t_new1 ) ;

    while (1) {
        digitalWrite(ledPins[0], HIGH);
        digitalWrite(ledPins[1], HIGH);
        digitalWrite(ledPins[2], HIGH);
        digitalWrite(ledPins[3], HIGH);
        digitalWrite(ledPins[4], HIGH);
        digitalWrite(ledPins[5], HIGH);
        usleep(velocidad5);  // Tiempo para mostrar la secuencia
        digitalWrite(ledPins[0], LOW);
        digitalWrite(ledPins[1], LOW);
        digitalWrite(ledPins[2], LOW);
        digitalWrite(ledPins[3], LOW);
        digitalWrite(ledPins[4], LOW);
        digitalWrite(ledPins[5], LOW);
        usleep(velocidad5);  // Tiempo de espera antes de la siguiente secuencia
        
            rd = read (0 , &teclado1 , 1) ;
            if ( rd > 0)
            {
                tcsetattr (0 , TCSANOW , & t_old1 ) ;
                return 0;
            }
        
        printf("Secuencia de luces completada.\n");
    }
    return 0;
}

int danzakuduro (int velocidad6){

const int numPasos4 = 14; // Nmero de pasos de tiempo para la secuencia (ajustado a 5)

const int secuencia [][6] = {
{1, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1},
{0, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 0},
{1, 0, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 0},
{0, 0, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 0},
{0, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1}
};

wiringPiSetup();
    // Configurar los pines de los LED como pines de salida
for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
}

tcgetattr (0 , & t_old1);
t_new1 = t_old1 ;
t_new1 . c_lflag &= ~( ECHO | ICANON ) ;
t_new1 . c_cc [ VMIN ]=0;
t_new1 . c_cc [ VTIME ]=0;
tcsetattr (1 , TCSANOW , & t_new1 ) ;


printf("Se encuentra dentro de danzakuduro.\n");

while (1) {
    for (int paso = 0; paso < numPasos4; paso++) {
        for (int led = 0; led < numLeds; led++) {
            
            digitalWrite(ledPins[led], secuencia[paso][led]);
            
            usleep(velocidad6);
           
            rd = read (0 , &teclado1 , 1) ;
            if ( rd > 0)
            {
                tcsetattr (0 , TCSANOW , & t_old1 ) ;
                return 0;
            }
        }
    }  
    printf("Secuencia de luces completada.\n"); 
}
    return 0;
}

int testbronco (int velocidad7){

const int numPasos5 = 30; // Nmero de pasos de tiempo para la secuencia (ajustado a 5)

const int secuencia [][6] = {
{1, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0},
{0, 0, 0, 1, 0, 0},
{0, 0, 1, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0},
{0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 1, 0},
{0, 0, 0, 1, 0, 0},
{0, 0, 1, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0},
{0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 1, 0},
{0, 0, 0, 0, 0, 1},
{0, 0, 0, 0, 1, 0},
{0, 0, 0, 1, 0, 0},
{0, 0, 1, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0},
};

wiringPiSetup();
    // Configurar los pines de los LED como pines de salida
for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
}

tcgetattr (0 , & t_old1);
t_new1 = t_old1 ;
t_new1 . c_lflag &= ~( ECHO | ICANON ) ;
t_new1 . c_cc [ VMIN ]=0;
t_new1 . c_cc [ VTIME ]=0;
tcsetattr (1 , TCSANOW , & t_new1 ) ;


printf("Se encuentra dentro de test bronco.\n");

while (1) {
    for (int paso = 0; paso < numPasos5; paso++) {
        for (int led = 0; led < numLeds; led++) {
            
            digitalWrite(ledPins[led], secuencia[paso][led]);
            
            usleep(velocidad7);
           
            rd = read (0 , &teclado1 , 1) ;
            if ( rd > 0)
            {
                tcsetattr (0 , TCSANOW , & t_old1 ) ;
                return 0;
            }
        }
    }   
    printf("Secuencia de luces completada.\n");
}
    return 0;
}

void salir (){
    
wiringPiSetup();
    
// Configurar los pines de los LED como pines de salida
for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], 0);
    }
   
}
