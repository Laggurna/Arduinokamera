// Include should also have all of the codes required for the camera, but the camera broke so we didn't put them here.

#include <NewPing.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int startpos = 90;    // variable to store the servo position
int ledPin = 7;                // choose the pin for the LED
int pos1 = 45;
int pos2 = 135;
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(startpos);
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(3, INPUT);
}

void loop()

{
if (digitalRead(3) == HIGH)
{
  Serial.println("** All clear **");
  val = digitalRead(inputPin);  // read input value
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

  if (sonar.ping_cm() < 40 && (sonar.ping_cm() > 0))
  {
    // Camera code would start here if ultrasonic sensor detects movement.
    

    myservo.write(pos2);
    Serial.print("Motion detected on sonar at ");
    Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
    Serial.println("cm");
    Serial.println("Angling camera...");
    Serial.println("Image captured!");
    digitalWrite(ledPin, HIGH);  // turn LED ON
    delay(50);
    digitalWrite(ledPin, LOW); // turn LED OFF
    delay(50);
    digitalWrite(ledPin, HIGH);  // turn LED ON
    delay(50);
    digitalWrite(ledPin, LOW); // turn LED OFF
    delay(50);
    digitalWrite(ledPin, HIGH);  // turn LED ON
    delay(200);
    digitalWrite(ledPin, LOW); // turn LED OFF

    // Camera code would end here, now it is replaced with blinking led.
   }
  
  if (val == HIGH)           // check if the input is HIGH
  {
    
    // Camera code would start here if passive infrared sensor (PIR) detects movement
    
    digitalWrite(ledPin, HIGH);  // turn LED ON
    delay(50);
    digitalWrite(ledPin, LOW); // turn LED OFF
    delay(50);
    digitalWrite(ledPin, HIGH);  // turn LED ON
    delay(50);
    digitalWrite(ledPin, LOW); // turn LED OFF
    delay(50);
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW)
    {
      // we have just turned on
      Serial.println("Motion detected on pir!");
      Serial.println("Angling camera...");
      Serial.println("Image captured!");
      // We only want to print on the output change, not state
      pirState = HIGH;
      myservo.write(pos1);
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned off
      Serial.println("Motion ended on pir!");
      // We only want to print on the output change, not state
      pirState = LOW;
  } 
    delay(200);
    digitalWrite(ledPin, LOW); // turn LED OFF
 }
 delay(1000);
 myservo.write(startpos);
}
else
{
  // The led is blinking to indicate us that system is on standby mode. 
  
  digitalWrite(ledPin, HIGH);  // turn LED ON
  delay(2000);
  digitalWrite(ledPin, LOW); // turn LED OFF
  delay(2000);
}
}
