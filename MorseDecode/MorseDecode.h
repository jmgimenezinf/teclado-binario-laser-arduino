#ifndef MorseDecode_h
#define MorseDecode_h

#include "Arduino.h"

class MorseDecode
{
public:
  MorseDecode();
  //String Decode (String message);
  char aCaracter(int subcadena);
private:
 int i;
};
#endif
