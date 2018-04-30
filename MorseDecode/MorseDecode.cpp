#include "Arduino.h"
#include "MorseDecode.h"
  MorseDecode::MorseDecode()
  {

  } 
char MorseDecode::aCaracter(int subcadena)
{

  char caracter;
  switch (subcadena){
  case 12999 : caracter='a';
    break;
  case 21119 : caracter='b';
    break;
  case 21219 : caracter='c';
    break;
  case 21199: caracter='d';
    break;
  case 19999: caracter='e';
    break;
  case 11219: caracter='f';
    break;
  case 22199: caracter='g';
    break;
  case 11119: caracter='h';
    break;
  case 11999: caracter='i';
    break;
  case 12229: caracter='j';
    break;
  case 21299: caracter='k';
    break;
  case 12119: caracter='l';
    break;
  case 22999: caracter='m';
    break;
  case 21999: caracter='n';
    break;
  case 22299: caracter='o';
    break;
  case 12219: caracter='p';
    break;
  case 22129: caracter='q';
    break;
  case 12199: caracter='r';
    break; 
  case 11199: caracter='s';
    break; 
  case 29999: caracter='t';
    break; 
  case 11299: caracter='u';
    break; 
  case 11129: caracter='v';
    break; 
  case 12299: caracter='w';
    break; 
  case 21129: caracter='x';
    break; 
  case 21229: caracter='y';
    break;
  case 22119: caracter='z';
    break;
  default:
    break;
  }
  return caracter;
}

