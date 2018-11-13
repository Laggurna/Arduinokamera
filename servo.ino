// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int startpos = 90;    // variable to store the servo position
int ledPin2 = 7;                // choose the pin for the LED
int pos1 = 45;
int pos2 = 135;

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN2  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);

void setup() {
  myservo.attach(11);  // attaches the servo on pin 9 to the servo object
  myservo.write(startpos);
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(3, OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(ledPin2, OUTPUT);      // declare LED as output
}

void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping1: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  Serial.print("Ping2: ");
  Serial.print(sonar2.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

    


  if (sonar.ping_cm() < 40)
  {
    digitalWrite (3, HIGH);
    digitalWrite(ledPin2, HIGH);  // turn LED ON
    myservo.write(pos2);
    delay(15);
    }
    delay(1000);
    digitalWrite (3, LOW);
    digitalWrite(ledPin2, LOW); // turn LED OFF
  
  if (sonar2.ping_cm() < 15)
  {
    digitalWrite (4, HIGH);
    myservo.write(pos1);
    delay(15);
  } 
    delay(1000);
    digitalWrite (4,LOW);
    digitalWrite(ledPin2, LOW); // turn LED OFF  
 }
  

