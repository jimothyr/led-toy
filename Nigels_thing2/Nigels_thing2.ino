/*
  LED toy
  

*/

#define ELEMENTS(x) (sizeof(x) /sizeof(x[0]))

  int outputPins[] = {7,8,9,10,11,12};
  byte inputPins[] = {A0,A1,A2,A3,A4,A5};
  int switchPins[] = {2,3,5};
  int timer = 100;
  byte inputPinsmatrix[8][6] =  {
    {A0,A1,A2,A3,A4,A5}, //0,0,0 - default
    {A1,A2,A3,A4,A5,A0}, //0,0,1
    {A2,A3,A4,A5,A0,A1}, //0,1,0
    {A3,A4,A5,A0,A1,A2}, //0,1,1
    {A4,A5,A0,A1,A2,A3}, //1,0,0
    {A5,A0,A1,A2,A3,A4}, //1,0,1
    {A5,A4,A3,A2,A1,A0}, //1,1,0
    {A4,A1,A3,A5,A0,A2} //1,1,1
  };
int switchControl[] = {0,0,0};
int switchValue = 0;


// the setup function runs once when you press reset or power the board
void setup() {

    Serial.begin(9600);//show me

    //set output pins
    for (int i = 0; i < 6; i++){
     pinMode(outputPins[i],OUTPUT);
    }

    //set all input posts
    for (int i = 0; i < 6; i++){
    pinMode(inputPins[i],INPUT_PULLUP);
    }

    //set all switch pins
     for (int i = 0; i < 3; i++){
    pinMode(switchPins[i],INPUT_PULLUP);
    }


    //run knight rider hello
    knightRider(outputPins,timer,3);

    
   
}

void knightRider(int ledArray[], int delayTime, int loops) {

      //set all leds to low
           for (int i=0; i < ELEMENTS(ledArray); i++){
            digitalWrite( ledArray[i], LOW);
          }
      for (int kr=0; kr < loops + 1; kr ++){//loop 3 times
              for (int i=0; i <  ELEMENTS(ledArray) ; i++){
                digitalWrite( ledArray[i],HIGH);
                delay(delayTime);
                digitalWrite( ledArray[i],LOW);
                delay(delayTime);
                }
          
               for (int i= ELEMENTS(ledArray) -1 ; i < 0 ; i--){
                digitalWrite( ledArray[i],HIGH);
                delay(delayTime);
                digitalWrite( ledArray[i],HIGH);
                delay(delayTime);
                }
          }//kr
  }
// the loop function runs over and over again forever
void loop() {
//set all lights off

 for (int i = 0; i < 6; i++){
          //set light to off
          digitalWrite(outputPins[i], LOW);
            
         //read 3 control switches 
          for (int j=0; j < 3; j++){
                switchControl[j] = digitalRead(switchPins[j]);
          }
         //convert to decimal to index appropriate output matrix
         switchValue = switchControl[2]*4 + switchControl[1]*2 + switchControl[0];
         
         //read input to check which post has connection
         int Aswitch = HIGH;
         Aswitch = digitalRead(inputPinsmatrix[switchValue][i]);
       
          if (Aswitch == LOW)   
          { digitalWrite(outputPins[i], HIGH);}
    }// i 
}//loop
