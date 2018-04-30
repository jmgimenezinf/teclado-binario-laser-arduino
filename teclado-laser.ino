#include <Morse.h>
#include <Wire.h>
#include <BH1750.h>

Morse morse(2);

int tecla_cero;
int tecla_uno;
int j=0;
unsigned char num = 0;
char msjSalida[]=" ";

void setup() {
    pinMode(2,OUTPUT); //OUTPUT LASER VCC
    pinMode(4,INPUT); // PULL DOWN 1
    pinMode(7,INPUT);//  PULL UP 0
    Serial.begin(9600);
}


void loop() {
  tecla_uno = digitalRead(4);
  tecla_cero = digitalRead(7);
  delay(250);

  if ((tecla_cero == LOW) or (tecla_uno == HIGH)) {
      Serial.print("bit ");
      Serial.print(8-(j+1), DEC);
      
      if(tecla_cero == LOW){
        Serial.print(": 0");
      }
      
      if (tecla_uno == HIGH){
        num = num | (1 << (7-j));
        Serial.print(": 1");
      }

      Serial.println("");
      j++;
      
      if (j==8) {
        j=0;
        Serial.print("El caracter ingresado es: ");
        Serial.println(char(num));
        Serial.print("El binario ingresado es: ");
        if(num & (1 << 7) == 0) {
          Serial.print("0");
        }
        Serial.println(num, BIN);
        Serial.print("El numero ingresado es: ");
        Serial.println(num, DEC);
        msjSalida[0]=char(num);
        Serial.print(msjSalida);
        signal_envio();
        morse.Write(msjSalida);
        signal_end_transmission();
        num = 0;
      }
   }
}

void signal_envio(){
    digitalWrite(2,1);
    delay(5000);
    //digitalWrite(2,0);
}
void signal_end_transmission(){
    digitalWrite(2,0);
    delay(5000);
    digitalWrite(2,1);
    delay(5000);
    digitalWrite(2,0);
    //digitalWrite(2,1);
    //delay(3000);
}
