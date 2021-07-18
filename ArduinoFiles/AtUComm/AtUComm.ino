void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(19200);
}

void loop() {
  //Sending value
  Serial.print("Hallo Unity\n");
  delay(1000);

  //Receiving value
  if (Serial.available()) {
    String s = Serial.readStringUntil('\n');
    //Serial.println("> Received:" + String(s));

    if (String(s) == "blink") {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
    }
  }
}
