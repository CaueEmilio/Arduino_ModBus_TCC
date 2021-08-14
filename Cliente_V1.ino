/**
 *  Modbus slave example 1:
 *  The purpose of this example is to link a data array
 *  from the Arduino to an external device.
 *
 *  Recommended Modbus Master: QModbus
 *  http://qmodbus.sourceforge.net/
 */

#include <ModbusRtu.h>
#define regSize 1
#define TxRxEnable 2

// data array for modbus network sharing
uint16_t au16data[regSize];
int8_t state = 0; 
uint16_t result[8];
int setAdd = 0;
byte ledPin = 11;
byte comPin = 12;


Modbus slave(8,Serial,TxRxEnable); //Colocado um numero qualquer pro clicente, dentro do setup ele é mudado, pois esta funão não pode ser declarada dentro do setup

void setup() {
  pinMode(ledPin , OUTPUT ); 
  pinMode(comPin , OUTPUT );
  pinMode(6 , INPUT_PULLUP );
  pinMode(5 , INPUT_PULLUP );
  Serial.begin( 19200 ); // baud-rate 19200
  digitalWrite(comPin, HIGH);
  int valIn1 = digitalRead( 6 );
  int valIn2 = digitalRead( 5 );
  setAdd = valIn1*2 + valIn2 + 1; //Converte de binário para decimal e soma 1 (endereços variam de 1 a 4)
  slave.start();
  slave.setID(setAdd); //Muda o endereço do cliente para o definido
}

void loop() {
  state = slave.poll( au16data, regSize );
  if (state>4){
    Serial.println("");
    if (au16data[0] == '1') digitalWrite(ledPin, HIGH);
    else digitalWrite(ledPin, LOW);
    }
}
