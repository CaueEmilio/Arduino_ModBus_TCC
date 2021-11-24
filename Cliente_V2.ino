#include <ModbusRtu.h>
#define regSize 4
#define TxRxEnable 2
#define S0 10
#define S1 9
#define S2 8
#define Din 7
#define comPin 13
#define tempoBuzzer 500

uint16_t au16data[regSize];
int8_t state = 0; 
uint16_t result[8];
int setAdd = 0;
char Bl;
char achaBloco;
char achaApto[3];
unsigned long inicioBuzzer;

Modbus slave(8,Serial,TxRxEnable); //Colocado um numero qualquer pro cliente, dentro do setup ele é mudado. Esta função não pode ser declarada dentro do setup.

void setup() {
  pinMode(comPin , OUTPUT );
  pinMode(S0 , OUTPUT );
  pinMode(S1 , OUTPUT );
  pinMode(S2 , OUTPUT );
  pinMode(Din , OUTPUT );
  pinMode(6 , INPUT_PULLUP );
  pinMode(5 , INPUT_PULLUP );
  Serial.begin( 19200 ); // baud-rate 19200
  digitalWrite(comPin, HIGH); //Sinaliza que a comunicação foi iniciada
  digitalWrite(Din, LOW); //Começa com todos os buzzers desligados
  //Cada um dos quatro clientes estará em um dos 4 estados (00,01,10,11) definidos pela ligação das portas 5 e 6
  int valIn1 = digitalRead( 6 ); 
  int valIn2 = digitalRead( 5 );
  setAdd = valIn1*2 + valIn2 + 1; //Converte de binário para decimal e soma 1 (endereços variam de 1 a 4)
  if (setAdd == 1) Bl = 'A';
  if (setAdd == 2) Bl = 'B';
  if (setAdd == 3) Bl = 'C';
  if (setAdd == 4) Bl = 'D';
  slave.start();
  slave.setID(setAdd); //Muda o endereço do cliente para o definido
  Serial.println(Bl); //Imprime no monitor serial a letra do bloco. Usado apenas para fácil diferenciação no simulador durante a validação
}

void loop() {
  state = slave.poll( au16data, regSize );
  if (state>4){ // Verifica se a comunicação foi feita com sucesso
    digitalWrite(comPin, HIGH);
    achaBloco = au16data[0];
    if (achaBloco == Bl){ //confere bloco do cliente e caso esteja errado, há um problema com a mensagem
      achaApto[0]=  au16data[1];
      achaApto[1]=  au16data[2];
      achaApto[2]=  au16data[3];
      if (achaApto[1] == '0'){ //Confere que o terceiro digito do registrador é zero antes de verificar o andar e o apartamento
        switch (achaApto[0]) { //Lê o segundo digito do registrador e define que campainha tocar de acordo com o segundo e último digitos do registrador
          case '1':
            if (achaApto[2] == '1'){ 
              digitalWrite(S0, LOW);
              digitalWrite(S1, LOW);
              digitalWrite(S2, LOW);
              inicioBuzzer = millis();
              digitalWrite(Din, HIGH);
              } //Liga o primeiro buzzer
            if (achaApto[2] == '2'){
              digitalWrite(S0, HIGH);
              digitalWrite(S1, LOW);
              digitalWrite(S2, LOW);
              inicioBuzzer = millis();
              digitalWrite(Din, HIGH);
              }//Liga o segundo buzzer
          break;
          case '2':
            if (achaApto[2] == '1'){
              digitalWrite(S0, LOW);
              digitalWrite(S1, HIGH);
              digitalWrite(S2, LOW);
              inicioBuzzer = millis();
              digitalWrite(Din, HIGH);
              }//Liga o terceiro buzzer
            if (achaApto[2] == '2'){
              digitalWrite(S0, HIGH);
              digitalWrite(S1, HIGH);
              digitalWrite(S2, LOW);
              inicioBuzzer = millis();
              digitalWrite(Din, HIGH);
              }//Liga o quarto buzzer  
          break;
          case '3':
          if (achaApto[2] == '2'){
            digitalWrite(S0, LOW);
            digitalWrite(S1, LOW);
            digitalWrite(S2, HIGH);
            inicioBuzzer = millis();
            digitalWrite(Din, HIGH);
            }//Liga o quinto buzzer
          if (achaApto[2] == '2'){
            digitalWrite(S0, HIGH);
            digitalWrite(S1, LOW);
            digitalWrite(S2, HIGH);
            inicioBuzzer = millis();
            digitalWrite(Din, HIGH);
            } //Liga o sexto buzzer
          break;   
          case '4':
          if (achaApto[2] == '1'){
            digitalWrite(S0, LOW);
            digitalWrite(S1, HIGH);
            digitalWrite(S2, HIGH);
            inicioBuzzer = millis();
            digitalWrite(Din, HIGH);
            }//Liga o sétimo buzzer
          if (achaApto[2] == '2'){
            digitalWrite(S0, HIGH);
            digitalWrite(S1, HIGH);
            digitalWrite(S2, HIGH);
            inicioBuzzer = millis();
            digitalWrite(Din, HIGH);
          }//Liga o oitavo buzzer
          break;
        }
      }
    }
  }
    else digitalWrite(comPin, LOW);
  if ((unsigned long)(inicioBuzzer-millis())>tempoBuzzer) digitalWrite(Din, LOW);
}
