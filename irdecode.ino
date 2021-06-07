int ifRead;
String _functions[5][2] = {{"Light on", "0xFFA25D"}, {"Light off", "0xFF629D"}, {"Fan Speed Down", "0xFFE21D"}, {"Fan Speed Up", "0xFF22DD"}};
bool isFanOn = false;
int fanSpeed = 0;
bool isLightOn = false;


// -------------- On Board Infrared Code --------------------------
void setup(){
  Serial.begin(9600);
  pinMode(A0, INPUT);
  Particle.function("executeAction", executeAction);
 }

 void loop(){
  ifRead = analogRead(A0); // Reads the input from the IR reciever
 }

 // ------------------ Mock Fan Code --------------------------------
  
 String checkSignal(String value){
  for(int i = 0; i < 3; i++){
    if(_functions[i][1] == value){
      return _functions[i][1]; // The Signal matches one of my stored values.
      }
     }
     return "-1"; // Fan does not recognise signal
 }

 bool executeAction(String value){
  if(checkSignal(value) != "-1"){
    Serial.write("Running action: " + value);
    if(value == "Light on"){
        isLightOn = true;
    }else if(value == "Light off"){
        isLightOn = false;
    }else if(value == "Fan Speed Down"){
        if(fanSpeed >= 0 && fanSpeed <= 5){
          fanSpeed++;
         }
    }else if(value == "Fan Speed Up"){
        if(fanSpeed >= 0 && fanSpeed <= 5){
          fanSpeed--;
        }
    }
  }
    fanStatus();
    return true;
}

 void fanStatus(){
  if(isFanOn && fanSpeed < 1){ // If the fan has no speed and is apperently on - turn it off
    isFanOn = false;
    }else if(isFanOn == false && fanSpeed > 0){
      isFanOn = true;
      }
  
  if(isFanOn){
    Serial.write("The Fan is On");
    Serial.write("Fan is at speed: " + fanSpeed);
    Particle.publish("The Fan is On");
    Particle.publish("Fan is at speed: " + fanSpeed);
    }else{
      Serial.write("The Fan is Off");
      Particle.publish("The Fan is Off");
    }

    if(isLightOn){
      Serial.write("The Light is On");
      Particle.publish("The Light is On");
    }
    else{
      Serial.write("The Light is Off");
      Particle.publish("The Light is Off");
      }
}
