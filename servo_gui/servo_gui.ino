#include "Servo.h"

/*
 * Gui Servo
 * Recibo datos por medio de UART y se convierten a un valor entero
 * para controlar la posicion de un servomot
 * 
 * Creado el 20/02/2022
 * by Noel Dominguez
 */

#define GUI_BAUD_RATE 115200 /* Velocidad de UART para la comunicacion con la interfaz */
#define SERVO_PIN 23 /* Pin donde se conecta el pin de señal del servomotor */
#define SERVO_DEFAULT_POS 0 /*Posicion inicial del servomotor */
Servo my_servo; /*Creamos un objeto Servo */
char gui_buff[256]; /*Buffer donde guardaremos los datos de nuestra gui */

/*Prototipos de funciones*/
static void servo_gui(void);

void setup() {
 
  my_servo.attach(SERVO_PIN);
  Serial.begin(GUI_BAUD_RATE);
  my_servo.write(SERVO_DEFAULT_POS);

}

void loop() {
 servo_gui(); /* Corre la aplicacion de la gui */
}

static void servo_gui(void){
  
    while ( Serial.available() ) { 
      int len = Serial.readBytesUntil('\n',gui_buff,sizeof(gui_buff)); /*https://www.arduino.cc/reference/en/language/functions/communication/serial/readbytesuntil/ */
      char servo_pos[len]; /* Declaro un nuevo array con el tamaño de bytes que recibi por la gui */
      memcpy(servo_pos,gui_buff,len); /* Copeo los bytes recibidos por la gui hacia mi array que declare arriba */
      my_servo.write(atoi(servo_pos)); /* Convierto mi array a valor entero */   
    }
}
