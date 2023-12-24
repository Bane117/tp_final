# include <pcf8591.h>
#include <stdio.h>
#include <wiringPi.h>

#define BASE 64
#define adress 0x48
#define A0 BASE+0
#define LECTURAS 16

//extern int convertidor (int *);


int adc (){
  //  int valor;
    int vel;
    pcf8591Setup(BASE,adress);

    vel=0;
    vel= analogRead(A0);
    printf("%d \n", vel);
   // valor = convertidor(AnalogRead(A0));


    if (vel<=26){
        printf("Velocidad inicial 1 \n");
        return 2000000;}
    else if (vel<=51){
        printf("Velocidad inicial 2 \n");
        return 1800000;}
    else if (vel<=77){
        printf("Velocidad inicial 3 \n");
        return 1600000;}
    else if (vel<=102){
        printf("Velocidad inicial 4 \n");
        return 1400000;}
    else if (vel<=128){
        printf("Velocidad inicial 5 \n");
        return 1200000;}
    else if (vel<=154){
        printf("Velocidad inicial 6 \n");
        return 1000000;}
    else if (vel<=179){
        printf("Velocidad inicial 7 \n");
        return 800000;}
    else if (vel<=205){
        printf("Velocidad inicial 8 \n");
        return 600000;}
    else if (vel<=230){
        printf("Velocidad inicial 9 \n");
        return 400000;}
    else if (vel<=256){
        printf("Velocidad inicial 10 \n");
        return 200000;}
return 0;

}
/*
    switch (valor)
    {

    case 1:
        vel = 2000000;
        break;
    
    case 2:
        vel = 1800000;
        break;

    case 3:
        vel = 1600000;
        break;

    case 4:
        vel = 1400000;
        break;

    case 5:
        vel = 1200000;
        break;

    case 6:
        vel = 1000000;
        break;

    case 7:
        vel = 800000;
        break;

    case 8:
        vel = 600000;
        break;

    case 9:
        vel = 400000;
        break;

    case 10:
        vel = 200000;
        break;

    default:
        vel = 200000;
        break;
    }


    return vel;
    */
