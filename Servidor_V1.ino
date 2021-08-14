/**
 *  Modbus master example 1:
 *  The purpose of this example is to query an array of data
 *  from an external Modbus slave device. 
 *  The link media can be USB or RS232.
 *
 *  Recommended Modbus slave: 
 *  diagslave http://www.modbusdriver.com/diagslave.html
 *
 *  In a Linux box, run 
 *  "./diagslave /dev/ttyUSB0 -b 19200 -d 8 -s 1 -p none -m rtu -a 1"
 * 	This is:
 * 		serial port /dev/ttyUSB0 at 19200 baud 8N1
 *		RTU mode and address @1
 */

#include <ModbusRtu.h>
#define regSize 1
#define TxRxEnable 2

byte ledPin = 13;
byte buttonPin = 12;
char bl = 'A'; // Define o cliente que será acessado
uint16_t au16data[regSize];
uint8_t u8state;

Modbus master(0,Serial,TxRxEnable); 

/**
 * This is an structe which contains a query to an slave device
 */
modbus_t telegram;

unsigned long u32wait;

void setup() {
  Serial.begin( 19200 ); // baud-rate at 19200
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  master.start();
  digitalWrite(ledPin, HIGH);
  master.setTimeOut( 2000 ); // if there is no answer in 2000 ms, roll over
  u32wait = millis() + 1000;
  u8state = 0; 
}

void loop() {
  switch( u8state ) {
  case 0: 
    if (millis() > u32wait) u8state++; // wait state
    break;
  case 1: 
    if (digitalRead(buttonPin)){au16data[0] = 49;} //Muda a mensagem dependendo se o botão é pressionado ou não
    else{au16data[0] = 48;}
    //digitalWrite(ledPin, LOW);
    if (bl == 'A'){telegram.u8id = 1;}// Endereço cliente 1
    if (bl == 'B'){telegram.u8id = 2;}// Endereço cliente 2
    if (bl == 'C'){telegram.u8id = 3;}// Endereço cliente 3
    if (bl == 'D'){telegram.u8id = 4;}// Endereço cliente 4
    telegram.u8fct = 6; // código da função (6 é escrita de registrador)
    telegram.u16RegAdd = 0; // Que endereço que começa a ler o registrador do cliente
    telegram.u16CoilsNo = regSize; // Número de registradores a serem lidos (função 6 aceita apenas 1 e função 16 aceita n)
    telegram.au16reg = au16data; // aponta para o local da memória que foi definido acima

    master.query( telegram ); // Pergunta o dado
    u8state++;
    break;
  case 2:
    //digitalWrite(ledPin, HIGH);
    master.poll(); // checa messagens
    if (master.getState() == COM_IDLE) {
      Serial.println("");
      u8state = 0;
      u32wait = millis() + 100; 
    }
    break;
  }
}