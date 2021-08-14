#include <ModbusRtu.h>
#define regSize 1    //Tamanho do registrador em bytes
#define TxRxEnable 2 //Define o pino 2 para ser utilizado como habilitador da leitura e escrita

byte ledPin = 13;
byte buttonPin = 12;
char bl = 'A'; // Define o cliente que será acessado entre blocos 'A', 'B', 'C' ou 'D'
uint16_t au16data[regSize];
uint8_t u8state;

Modbus master(0,Serial,TxRxEnable); //Cria o objeto do Servidor

/**
 * This is an structe which contains a query to an slave device
 */
modbus_t telegram;  //Cria o objeto do datagrama

unsigned long u32wait;

void setup() {
  Serial.begin( 19200 ); // baud-rate 19200
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  master.start();
  digitalWrite(ledPin, HIGH);
  master.setTimeOut( 2000 ); // Se não houver resposta em 2000 ms, faz outra requisição 
  u32wait = millis() + 1000;
  u8state = 0; 
}

void loop() {
  switch( u8state ) {
  case 0: 
    if (millis() > u32wait) u8state++; // Estado de espera
    break;
  case 1: 
    if (digitalRead(buttonPin)){au16data[0] = 49;} //Muda a mensagem dependendo se o botão é pressionado ou não
    else{au16data[0] = 48;}
    if (bl == 'A') telegram.u8id = 1; // Endereço cliente 1
    if (bl == 'B') telegram.u8id = 2; // Endereço cliente 2
    if (bl == 'C') telegram.u8id = 3; // Endereço cliente 3
    if (bl == 'D') telegram.u8id = 4; // Endereço cliente 4
    telegram.u8fct = 6; // código da função (6 é escrita de registrador)
    telegram.u16RegAdd = 0; // Endereço que começa a ser lido o registrador do cliente
    telegram.u16CoilsNo = regSize; // Número de registradores a serem lidos (função 6 aceita apenas 1 e função 16 aceita n)
    telegram.au16reg = au16data; // aponta para o local da memória que foi definido a cima

    master.query( telegram ); // Faz requisição para o cliente
    u8state++;
    break;
  case 2:
    //digitalWrite(ledPin, HIGH);
    master.poll(); // checa messagens
    if (master.getState() == COM_IDLE) { // Caso a mensagem tenha sido lida
      Serial.println("");
      u8state = 0;
      u32wait = millis() + 100; 
    }
    break;
  }
}
