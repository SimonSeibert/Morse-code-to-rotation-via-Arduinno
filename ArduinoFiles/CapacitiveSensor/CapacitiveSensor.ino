#include <CapacitiveSensor.h>

CapacitiveSensor Sensor = CapacitiveSensor(2, 4);
long val;
int state;
const int threshhold = 400;
float timestampOnPress = 0;       // timestampOnPress is used to get presstime
float timestampOnRelease = 0;     // timestampOnRelease is used to get releasetime


void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  state = 0;
}

void loop() {
  val = Sensor.capacitiveSensor(30);
  //Serial.println(val);

  //PRESS
  if (val >= threshhold && state == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    
    timestampOnPress = millis();                        //Gets time since execution start and current time in ms
    float releaseTime = millis() - timestampOnRelease;  //get release time in ms by subtracting the timestamp from the current time

    Serial.print("DIY Sensor Pressed. Release time was: ");
    Serial.println(releaseTime);

    state = 1;
  }
  //RELEASE
  else if (val < threshhold && state == 1) {
    digitalWrite(LED_BUILTIN, LOW);

    timestampOnRelease = millis();
    float pressTime = millis() - timestampOnPress;
    
    Serial.print("DIY Sensor released. Press time was: ");
    Serial.println(pressTime);
    
    state = 0;
  }
  delay(50);
}

