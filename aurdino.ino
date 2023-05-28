#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 4); // RX, TX
/* LED strip */
// Pin assignment
int blue = 11;
int red = 10;
int green = 9;
bool ledStripState = false; // on == true; off == false;
/* Bluetooth serial comm. */
char character;
String command;
/* User Functions */
void ledStripOn();
void ledOldColor();
void ledStripOff();
void ledBlink();
void commWithBT()
{
  while (mySerial.available() > 0)
  {
    character = mySerial.read();
    command.concat(character);
    Serial.print(character);
    delay(1);
  }
  if (command == "LED_ON")
  {
    ledStripOn();
    //ledOldColor();
    ledStripState = true;
  }
   else if (command == "LED_BLINK")
  {
    ledBlink();
    ledOldColor();
    ledStripState = true;
  }
  else if (command == "LED_OFF")
  {
    ledStripOff();
    ledStripState = false;
  }
  //RGB_RRRGGGBBB
  else if (command.indexOf("RGB_") == 0)
  {
    Serial.println();
    String cmd = command.substring(4, 7);
    int value = cmd.toInt();
    Serial.println(value);
    analogWrite(red, value);
    cmd = command.substring(7, 10);
    value = cmd.toInt();
    Serial.println(value);
    analogWrite(green, value);
        cmd = command.substring(10, 13);
    value = cmd.toInt();
    Serial.println(value);
    analogWrite(blue, value);    
  }
  command = "";
}
void ledStripOn()
{
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, HIGH);
}
void ledStripOff()
{
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(red, LOW);
}
void ledBlink()
{
   for(int i=0;i<100;i++)
{
  ledStripOn();
  delay(1000);
  ledStripOff();
}
  }
void setup()
{
  Serial.begin(115200);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  mySerial.begin(9600);
 }
void loop()
{

  if (mySerial.available() > 0)
  {
    commWithBT();
  }
}
