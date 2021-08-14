#include <Keypad.h>

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

byte ledPin = 13;
char apto[5];
int n = 0;
boolean blink = false;
boolean envia = false;

void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      
  digitalWrite(ledPin, HIGH);   
  Teclas.addEventListener(keypadEvent); //Cria um ouvinte de eventos do teclado
}

void loop(){
  char tecla = Teclas.getKey(); //Recebe a tecla pressionada

  if (envia) { //Apenas envia a mensagem se toda a palavra foi escrita
    Serial.println(apto); //Imprime as teclas pressionadas (Apenas verificação) 
    digitalWrite(ledPin,!digitalRead(ledPin)); //Inverte o LED
    envia = false;  //Prepara o código para esperar por novas mensagens
  }
  if (blink){
    digitalWrite(ledPin,!digitalRead(ledPin));
    delay(100);
  }
}

// Eventos especiais
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
            envia = true;
            digitalWrite(ledPin,!digitalRead(ledPin));
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
