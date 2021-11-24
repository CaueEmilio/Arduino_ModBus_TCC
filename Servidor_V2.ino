#include <ModbusRtu.h>
#include <Keypad.h>
#define regSize 4    //Tamanho do registrador em bytes
#define TxRxEnable 2 //Define o pino 2 para ser utilizado como habilitador da leitura e escrita
#define comPin 13    //Define o pino 13 como o pino de comunicação

const byte ROWS = 4; //Quatro linhas
const byte COLS = 4; //Quatro colunas
//define os simbolos em cada botão do teclado
char Keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {3, 4, 5, 6}; //Conecta as linhas à estes pinos do teclado
byte colPins[COLS] = {7, 8, 9, 10}; //Conecta as colunas à estes pinos do teclado

//Inicializa uma nova instância de teclado
Keypad Teclas = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS); 

char apto[5];
int n = 0;
char bl;
boolean envia = false;
uint16_t au16data[regSize];
uint8_t u8state;

Modbus master(0,Serial,TxRxEnable); //Cria o objeto do Servidor
modbus_t telegram;  //Cria o objeto do datagrama
unsigned long u32wait; 

void setup() {
  Serial.begin( 19200 ); // baud-rate 19200
  pinMode(comPin, OUTPUT);
  Teclas.addEventListener(keypadEvent); //Cria um ouvinte de eventos do teclado
  master.start();
  digitalWrite(comPin, LOW);
  master.setTimeOut( 2000 ); // Se não houver resposta em 2000 ms, faz outra requisição 
  u32wait = millis() + 1000; //Define o tempo de espera para 1s
  u8state = 0; 
  
}

void loop() {
  char tecla = Teclas.getKey(); //Recebe teclas pressionadas. É uma interrupção.
  switch( u8state ) {
  case 0: //Retorna ao estado inicial para fazer outra requisição
    telegram.u8id = 45; //Passa a tentar conexão com um cliente inexistente enquanto não recebe o cliente correto
    bl = ' '; //Limpa a variavel bloco 
    if (millis() > u32wait) u8state++; // Estado de espera. Tempo definido no setup
    break;
  case 1: 
    if (envia){
      for (int n =0; n<regSize;n++) {au16data[n] = apto[n];} 
      bl = au16data[0];
      if (bl == 'A') telegram.u8id = 1; // Endereço cliente 1
      if (bl == 'B') telegram.u8id = 2; // Endereço cliente 2
      if (bl == 'C') telegram.u8id = 3; // Endereço cliente 3
      if (bl == 'D') telegram.u8id = 4; // Endereço cliente 4 
      envia = false;
      } //Muda a mensagem dependendo se a mensagem é concluida ou não
    else {au16data[0] = 0;au16data[1] = 0;au16data[2] = 0;au16data[3] = 0;} 
    telegram.u8fct = 16; // código da função (16 é escrita de registradores)
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
      digitalWrite(comPin, HIGH);
      u8state = 0;
      u32wait = millis() + 100; 
    }
    else digitalWrite(comPin, LOW);
    break;
  }
}

// Eventos especiais do teclado. Recebe cinco teclas, a letra do bloco, os três digitos do apartamento e a cerquilha para o fim da mensagem. Asterisco apaga a mensagem.
void keypadEvent(KeypadEvent tecla){
  switch (Teclas.getState()){
    case PRESSED:
      switch (tecla){
      //Numeros só podem ocupar entre o 2º e o 4º espaço da memória
        case '1':
          if (n>0 && n<4){
            apto[n] = 49;
            n++;
            }
          else {
            memset(apto, 0, sizeof(apto));
            n = 0;
            }
          break;
            
        case '2':
          if (n>0 && n<4){
            apto[n] = 50;
            n++;
            }
          else {
            memset(apto, 0, sizeof(apto));
            n = 0;
            }
          break;
            
        case '3':
          if (n>0 && n<4){
            apto[n] = 51;
            n++;
            }
          else {
            memset(apto, 0, sizeof(apto));
            n = 0;
            }
          break;
          
        case '4':
          if (n>0 && n<4){
            apto[n] = 52;
            n++;
            }
          else {
            memset(apto, 0, sizeof(apto));
            n = 0;
            }
          break;
            
        case '5':
          if (n>0 && n<4){
            apto[n] = 53;
            n++;
            }
          else {
            memset(apto, 0, sizeof(apto));
            n = 0;
            }
          break;
            
        case '6':
          if (n>0 && n<4){
            apto[n] = 54;
            n++;
            }
          else {
            memset(apto, 0, sizeof(apto));
            n = 0;
            }
          break;
            
        case '7':
          if (n>0 && n<4){
            apto[n] = 55;
            n++;
            }
          else {
            memset(apto, 0, sizeof(apto));
            n = 0;
            }
          break;
          
        case '8':
          if (n>0 && n<4){
            apto[n] = 56;
            n++;
            }
          else {
            memset(apto, 0, sizeof(apto));
            n = 0;
            }
          break;  
          
        case '9':
          if (n>0 && n<4){
            apto[n] = 57;
            n++;
            }
          else {
            memset(apto, 0, sizeof(apto));
            n = 0;
            }
          break;
          
        case '0':
          if (n>0 && n<4){
            apto[n] = 48;
            n++;
            }
          else {
            memset(apto, 0, sizeof(apto));
            n = 0;
            }
          break;
          
        //Letras só podem ocupar o 1º espaço da memória  
        case 'A':
          if (n==0){
            apto[n] = 65;
            n++;
            }
          else {
            memset(apto, 0, sizeof(apto));
            n = 0;
            }
          break;
          
        case 'B':
          if (n==0){
            apto[n] = 66;
            n++;
            }
          else {
            memset(apto, 0, sizeof(apto));
            n = 0;
            }
          break;
          
        case 'C':
          if (n==0){
            apto[n] = 67;
            n++;
            }
          else {
            memset(apto, 0, sizeof(apto));
            n = 0;
            }
          break;

        case 'D':
          if (n==0){
            apto[n] = 68;
            n++;
            }
          else {
            memset(apto, 0, sizeof(apto));
            n = 0;
            }
          break;
        
        //Cerquilha envia a mensagem se estiver no 5º espaço e apaga a mensagem se estiver em qualquer outro
        case '#': 
          if (n == 4){
            apto[n] = 0;
            envia = true;
            n = 0; 
            }
          else{
            memset(apto, 0, sizeof(apto));
            n = 0;  
          }
          break;
        
        //Asterísco apaga a mensagem  
        case '*': 
          memset(apto, 0, sizeof(apto));
          n = 0;
          break;
      }
    break;
  }
}
