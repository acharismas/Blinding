//Dev: acharismas

#define DEFAULT_MAX_FEEDRATE {500, 500, 2, 45} // (mm/sec) 
#define DEFAULT_MAX_ACCELERATION {180,180,10,200}
#define DEFAULT_ACCELERATION 60
#define DEFAULT_RETRACT_ACCELERATION 60
#include <AFMotor.h>
#include <SoftwareSerial.h>

SoftwareSerial BTserial(10, 11); // RX | TX
int sensorValue = 0;
int junk = 0;
String inputString = "";
int StoreString = 0;
int serialInput;
char chArray[2];
String xxx = "";
int value_tran = 0;
int y;
int inChar;
int finaal;
boolean led = false;
char command;
unsigned long currentPosition;
unsigned long steps;
String string="off";
int calculation;
int ldrPin = A0;
const int ledPin = 13;

AF_Stepper motor(40, 1);

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Stepper Test");
  motor.setSpeed(130);  // 10 rpm
  pinMode(ledPin, OUTPUT);


}
void loop()
{
  if (Serial.available() > 0) //check for input data

  {
    string = "";
  }

  while (Serial.available() > 0)
  {
    command = ((byte)Serial.read());
    if (command == ':')
    {
      break;
    }
    else
    {
      string += command;
      finaal = string.toInt();
      Serial.println("Finall");
      Serial.println(finaal);

    }
    delay(3);
  }
    if ((string.toInt() >= 0) && (string.toInt() <= 100))
    {
      if (finaal == StoreString)
      {
        Serial.println("You are in correct position!");
      }
      else
      {
        if (finaal > StoreString)
        {
          //digitalWrite(directionPin, HIGH);
          steps = finaal - StoreString;
          Serial.println("Steps Move Forward");

          calculation = steps / 1.6;
          Serial.println(calculation);
          MotorControlBackward(calculation);
          Serial.println("Reach destination!");
          delay(50);
        }
        else
        {
          //digitalWrite(directionPin, LOW);
          steps = StoreString - finaal;
          Serial.println("Steps Move Backward");
          calculation = steps / 1.6;
          Serial.println(calculation);
          MotorControlForward(calculation);
          Serial.println("Reach destination!");
          delay(50);
        }
        //moveRelative(steps);
        StoreString = finaal;
      }
    
      // analogWrite(6, string.toInt());//type casting to integer
      Serial.println(string);//printing the int value
      delay(1000);
    }
      
    else
    {
      Serial.println("Automatic");
    }




      led = false;
      digitalWrite(ledPin, LOW);
      delay(1000);
      digitalWrite(ledPin, HIGH);

    //LDR sensor
    int ldrStatus = analogRead(ldrPin);
    if (ldrStatus <= 100) {
      Serial.println("Close light!"); 
    }    
    else {

      Serial.println("Open light!");
      
    }
    Serial.println(ldrStatus);
    delay(500);
    StoreString = finaal;
  }
          


void MotorControlForward(int motorsteps)
{
  for ( int x = 0; x < motorsteps; x++)
  {
    motor.step(50, FORWARD, DOUBLE);
  }
}

void MotorControlBackward(int motorstepsb)
{
  for ( int x = 0; x < motorstepsb; x++)
  {
    motor.step(50, BACKWARD, DOUBLE);
  }
}






