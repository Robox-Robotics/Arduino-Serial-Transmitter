

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL; //Remember that this code should be the same for the receiver
RF24 radio(9, 10);  //Set CE and CSN pins
#define SEL0  2
#define SEL1  3
#define SEL2  4

void select();
int Mux1_State[8]={0};
const int mux1_weights[8]={10,20,30,40,50,60,70,0};
const int mux2_weights[8]={20,30,10,40,50,60,70,0};
int Mux2_State[8]={0};
int test=0;
struct Data_to_be_sent {
  byte J1_X;
  byte J1_Y;
  byte J2_X;
  byte J2_Y;
  byte BUT1;
  byte BUT2;
  byte MOD;
};

Data_to_be_sent packet;

#define MUX1_OUT 5
#define MUX2_OUT 6

void setup() {
  // put your setup code here, to run once:
    radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(my_radio_pipe);
  Serial.begin(9600);
  pinMode(SEL0,OUTPUT);
pinMode(SEL1,OUTPUT);
pinMode(SEL2,OUTPUT);

pinMode(MUX1_OUT,INPUT);
pinMode(MUX2_OUT,INPUT);

packet.J1_X = 127;
packet.J1_Y = 127;
packet.J2_X = 127;
packet.J2_Y = 127;
packet.BUT1 = 0;
packet.BUT2 = 0;
packet.MOD = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
    updateMux();
//    for(int i=0;i<8;i++){
//      if(i==7){
//        Serial.print(Mux1_State[i]);
//        Serial.print("|");
//      } else{
//        Serial.print(Mux1_State[i]);
//        Serial.print(":");
//      }
//    }
//      for(int i=0;i<8;i++){
//      if(i==7){
//        Serial.println(Mux2_State[i]);
//      } else{
//        Serial.print(Mux2_State[i]);
//        Serial.print(":");
//      }
//    }
    

packet.J1_X = map( analogRead(A0), 0, 1024, 0, 255);
  packet.J1_Y = map( analogRead(A1), 0, 1024, 0, 255);
  packet.J2_X = map( analogRead(A2), 0, 1024, 0, 255);
  packet.J2_Y = map( analogRead(A3), 0, 1024, 0, 255);
//select();
Serial.print(packet.J1_X);
Serial.print(":");
Serial.print(packet.J1_Y);
Serial.print(":");
Serial.print(packet.J2_X);
Serial.print(":");
Serial.print(packet.J2_Y);
Serial.print(":");
Serial.print(packet.BUT1);
Serial.print(":");
Serial.println(packet.BUT2);
radio.write(&packet, sizeof(Data_to_be_sent));
//delay(200);
}

void updateMux(){
  for(int i=0;i<8;i++){
    digitalWrite(SEL0,HIGH && (i& B00000001));
    digitalWrite(SEL1,HIGH && (i& B00000010));
    digitalWrite(SEL2,HIGH && (i& B00000100));
    Mux1_State[i]= !(digitalRead(MUX1_OUT));
    Mux1_State[i]= Mux1_State[i]*mux1_weights[i];
      if(Mux1_State[i]>0){

packet.BUT1=Mux1_State[i];
  }
        
    Mux2_State[i]= !(digitalRead(MUX2_OUT));
    Mux2_State[i] = Mux2_State[i]*mux2_weights[i];
          if(Mux2_State[i]>0){

packet.BUT2=Mux2_State[i];
  }

  
  }
    for(int i=0;i<8;i++){
     for(int j=0;j<i-1;j++){
      if(Mux1_State[j]<Mux1_State[j+1]){
        Mux1_State[j]=test;
        Mux1_State[j]=Mux1_State[j+1];
        Mux1_State[j+1]=test;
      }
    }
    }


  
}
