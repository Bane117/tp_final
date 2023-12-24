#include <wiringPi.h>

const int botonesVel [2]={6,7};
const int numbotonesVel = sizeof(botonesVel) / sizeof(botonesVel[0]);

int speed (){


    if(digitalRead(botonesVel [0])){
        velocidad = velocidad + 200000;
    }

    if(digitalRead(botonesVel [1])){
        velocidad = velocidad - 200000;
    }


	if(speed>2000000){
		speed=2000000;	}
	if(speed<200000){
		speed=200000;	}


return velocidad;
}  
