int ledArray[] = {5,6,9};
boolean balanceSet = false;
int red = 0;
int green = 0;
int blue = 0;
float colors[] = {0,0,0};
float whitevals[] = {0,0,0};
float blackvals[] = {0,0,0};
int averageVal;
void setup(){
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  Serial.begin(9600);
}
void loop(){
    calibrateTrue();
    readColor();
    printConsole();
}
void calibrateTrue(){
  if(balanceSet == false){
    calibrate();
  }
}
 void calibrate(){
   Serial.println("place white sample over");
   delay(5000); 
  for(int i = 0;i<=2;i++){
     digitalWrite(ledArray[i],HIGH);
     delay(100);
     getReading(5);          
     whitevals[i] = averageVal;
     digitalWrite(ledArray[i],LOW);
     delay(100);
  }
    Serial.println("place black sample over");
    delay(5000);              
  for(int i = 0;i<=2;i++){
     digitalWrite(ledArray[i],HIGH);
     delay(100);
     getReading(5);
     blackvals[i] = averageVal;

     digitalWrite(ledArray[i],LOW);
     delay(100);
  }
  balanceSet = true;
  delay(5000);     
  }
void readColor(){
    for(int i = 0;i<=2;i++){
     digitalWrite(ledArray[i],HIGH);  
     delay(100);                      
     getReading(5);                  
     colors[i] = averageVal;        
     float greyDiff = whitevals[i] - blackvals[i];                    
     colors[i] = (colors[i] - blackvals[i])/(greyDiff)*255; 
     digitalWrite(ledArray[i],LOW);   
     delay(100);
  } 
}
void getReading(int times){
  int reading;
  int tally=0;
for(int i = 0;i < times;i++){
   reading = analogRead(0);
   tally = reading + tally;
   delay(10);
}
averageVal = (tally)/times;
}
void printConsole(){
Serial.print("R = ");
Serial.println(int(colors[0]));
Serial.print("G = ");
Serial.println(int(colors[1]));
Serial.print("B = ");
Serial.println(int(colors[2]));
//delay(2000);
}
