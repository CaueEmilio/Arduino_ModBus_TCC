#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char Keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {3, 4, 5, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 8, 9, 10}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad Teclas = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS); 

byte ledPin = 13;
char apto[5];
int n = 0;
boolean blink = false;
boolean envia = false;

void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  digitalWrite(ledPin, HIGH);   // sets the LED on
  Teclas.addEventListener(keypadEvent); //add an event listener for this keypad
}

void loop(){
  char tecla = Teclas.getKey();

  if (envia) {
    Serial.println(apto);
    digitalWrite(ledPin,!digitalRead(ledPin));
    envia = false;
  }
  if (blink){
    digitalWrite(ledPin,!digitalRead(ledPin));
    delay(100);
  }
}

//take care of some special events
void keypadEvent(KeypadEvent tecla){
  switch (Teclas.getState()){
    case PRESSED:
      switch (tecla){
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
        
        case '*': 
          memset(apto, 0, sizeof(apto));
          n = 0;
          break;
      }
    break;
  }
}
