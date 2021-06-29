#include <CapacitiveSensor.h>

CapacitiveSensor Sensor = CapacitiveSensor(2, 4);
long val;                         // Value from capacitive reading
int state;                        // State to allow press and release function to be executed 1 time after another
const int threshhold = 400;       // Threshold for when capacitive reading reading counts as a press or a release
float timestampOnPress = 0;       // timestampOnPress is used to get presstime
float timestampOnRelease = 0;     // timestampOnRelease is used to get releasetime


void setup() {
  Serial.begin(9600);
  state = 0;
}

void loop() {
  val = Sensor.capacitiveSensor(30);
  Serial.println(val);

  //PRESS
  if (val >= threshhold && state == 0) {   
    timestampOnPress = millis();                        //Gets time since execution start and current time in ms
    float releaseTime = millis() - timestampOnRelease;  //get release time in ms by subtracting the timestamp from the current time

    Serial.print("DIY Sensor Pressed. Release time was: ");
    Serial.println(releaseTime);

    state = 1;
  }
  //RELEASE
  else if (val < threshhold && state == 1) {
    timestampOnRelease = millis();                      
    float pressTime = millis() - timestampOnPress;      //get press time in ms by subtracting the timestamp from the current time
    
    Serial.print("DIY Sensor released. Press time was: ");
    Serial.println(pressTime);
    
    state = 0;
  }
  
  delay(50); //Delay between readings
}

