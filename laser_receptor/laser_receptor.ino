#include <Wire.h>
#include <BH1750.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// variables globales
BH1750 lightMeter; //sensor de luz

int cont_low; // contador del tiempo de presencia de luz
int cont_hight; // contador del tiempo de ausencia de luz
const int time_max=3000; //tiempo maximo inicio y fin de transmision
int msj_recibido[256]; // almacena el mensaje recibido nivel 1
int msj_filtrado[256]; //mensaje filtrado de la siguiente forma :
int long_msj=0; //longitud del mensaje recibido
// 0=dash 1=dot 2=caracter inicio y fin

boolean bloquear=false; //bloquea la recepcion de un nuevo mensaje

//Declaracion de metodos
void esperarEnvio(){
  int time_actual;
  time_actual=0;
  while (time_actual < time_max ){
      delay(1);
      if (lightMeter.readLightLevel()>0){
          time_actual=time_actual + 1;  
      }else{
          time_actual=0;    
      }
  }
  
  Serial.print("Supero el tiempo maximo de 1: ");
  Serial.println(time_actual);
  Serial.println("Comienza transmision");
}

void bloquearHastaCero(){
  
while (lightMeter.readLightLevel()!=0) {
  
}
  
}

void recibirDatos(){
  int i = 0;
  int cont_hight =0;
  int cont_low = 0;
  
  while (cont_low<time_max) {
    uint16_t lux = lightMeter.readLightLevel();
    cont_hight=0;
    cont_low=0;
   if (lux>0){
      cont_hight=cont_hight +1;
      delay(10);
      while (lightMeter.readLightLevel()>0){
          delay(1);
          cont_hight=cont_hight +1;
      }
        Serial.print("Cantidad de Unos:");
        Serial.println(cont_hight);
        
      if (i<254){
            msj_recibido[i]=cont_hight;
            Serial.print("vector ");
            Serial.print(i);
            Serial.print(" ");
            Serial.println(msj_recibido[i]);
       }
       i++;
    }else {
        cont_low=cont_low + 1;
        delay(10);
        while (lightMeter.readLightLevel()== 0){
          delay(1);
          cont_low=cont_low +1;
        }
        Serial.print("Cantidad de Ceros:");
        Serial.println(cont_low);
        
        if (i<254){
          msj_recibido[i]=cont_low;  
          Serial.print("vector ");
          Serial.print(i);
          Serial.print(" ");
          Serial.println(msj_recibido[i]);
        }
       i++; 
      }
   }
  long_msj=i-1;
}

int strToInt(char * str){
   int val;
   val = atoi(str);
 return val;
}

void filtrarMensaje(){
  
 int i=0; //indice mensaje recibido
 int j=0;// indice mensaje filtrado
 int k=-1;//indice de carac
 
 //String caracter= "99999";
 char str[6];
 strcpy(str,"99999");
 
 while( i<=long_msj){
       if (msj_recibido[i] < 1900){
         k=k+1;
      
         if ((msj_recibido[i] > 300) && (msj_recibido[i] < 600)){
            str[k]='2';
         }
         else{
            str[k]='1';
         }
       }
       else{
         if (strToInt(str) != 99999){
            msj_filtrado[j]= strToInt(str);
            j++;
         }
         strcpy(str,"99999");
         k=-1;  
       }
 i=i+2;
 }
 for (int p=0; p <= j; p++){
        Serial.print("i ");
        Serial.print(p);
        Serial.print(" contenido");
        Serial.println(msj_filtrado[p]);
   } 
 
}

void setup() {
  Serial.begin(9600);
  lightMeter.begin();
  Serial.println(F("LASER RECEPTOR"));
}
void loop() {

    if(!bloquear){
      esperarEnvio();
      bloquearHastaCero();
      recibirDatos();
      for (int i=0; i <= long_msj; i++){
        Serial.print("i ");
        Serial.print(i);
        Serial.print(" contenido");
        Serial.println(msj_recibido[i]);
      } 
      filtrarMensaje();
      bloquear=true;
      Serial.println("Mensaje enviado - entrada bloqueada");
    }

}



