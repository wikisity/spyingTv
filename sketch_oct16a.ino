                                                                                                                                                            
// when inittializing the variables, make sure to not using the same Pin for different variables.
#include <Ultrasonic.h> // include sensor library named ultrasonic.h
Ultrasonic ultrasonic(12,13); // instruction to tell which pin the sensor control from the arduino or motorshield
// Defined Variables
#define BRAKEVCC 0  // 0: Brake to VCC
#define CW   1      // 1: Clockwise
#define CCW  2      // 2: CounterClockwise
#define BRAKEGND 3  // Brake to GND
#define CS_THRESHOLD 100  // Value to be compared to AnalogRead(int Pin)

int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int cspin[2] = {2, 3}; // CS: Current sense ANALOG input
int enpin[2] = {0, 1}; // EN: Status of switches output (Analog pin)
int statpin = 11;  // instruction needed to connected to analog pin 13
int dist = 0;
void setup() // the setup routine runs once when you press reset:
{
 Serial.begin(9600);  // initialize serial communication at 9600 bits per second:
 pinMode(statpin, OUTPUT); // this line make the pin 13, or the variable statpin, 
                           // with the onboard LED. an output
 // Initialize digital pins as outputs
 for (int i=0; i<2; i++) // for routine initialize i to 0, compare value of i to 2, 
                         // execute{...} then incremente value of i to 1
 {
   pinMode(inApin[i], OUTPUT); // sets the digital pin inApin[ivalue] as output
   pinMode(inBpin[i], OUTPUT); // sets the digital pin inBpin[ivalue] as output
   pinMode(pwmpin[i], OUTPUT); // sets the digital pin pwmpin[ivalue] as output
 }

 // Initialize braked
 for (int i=0; i<2; i++)
 {
   digitalWrite(inApin[i], LOW); // sets the LED off or the inApin[ivalue] off
   digitalWrite(inBpin[i], LOW); // sets the LED off
 }
}

/*----------------------------
 pmw value has to be < 1023.
 CCW=CounterClockwise
 CW=ClockWise
-----------------------------*/


/* motorGo()will set a motor going in a specific direction 
 the motor wll continue going in that firection, at the speed
  specified by pwm value. pwm value should be between 0 and 255
  the higher the number, the faster the motor will go
  */
/*
the value sent by ultransonic.Ranging() is the distance between the person and the TV.
Throuhg this void loop() function I am controlling Both actuators's movements by sensing a human presence.
*/
void loop()  // the loop routine runs over and over again forever:
{                            
  if ((ultrasonic.Ranging(CM)) >= 100){ // ultrasonic.Ranging() sends a value and compares that value to 100.
     motorGo(0, CW, 600);  // Here actuator 1 run clockwise or will run out
     motorGo(1, CW, 600); // Actuator 2 run alsoi clockwise or simply will run out too.
     Serial.println("cm");   // This line is for testing phase. To ensure that the code prints out the distance. 
     delay(100); // The result is displayed faster because less than a second.
    
      }         
  else if ((ultrasonic.Ranging(CM)) < 100){ // This If statement tells if someone is closer enough to the TV.
     motorGo(0, CCW, 600); // Actuator 1 run counter clockwise or run in.
     motorGo(1, CCW, 600); // Actuator  2 run counter clockwise or run in.
     Serial.println("cm");    
     delay(100); // The distance sensed by the sensor is displayed in a time less than a second.
      
     }

// value from analogRead(int value) is compared to CS_THRESHOLD value
 if ((analogRead(cspin[0]) < CS_THRESHOLD) && (analogRead(cspin[1]) < CS_THRESHOLD))
   digitalWrite(statpin, HIGH);
}
 


void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
 if (motor <= 1) // first test. Value of motor compared to 1
 {
   if (direct <=4) // first test works, then second test upon motor's direction
   {
     /*this below bolck of instruction
       Set inA[motor] on or off according to the test result
       and adjust motor's speed
     */
     if (direct <=1)
       digitalWrite(inApin[motor], HIGH);
     else
       digitalWrite(inApin[motor], LOW);

     /* this below bolck of instruction
     Set inB[motor] on or off accroding to the test result and
     adjust motor's speed
     */
     if ((direct==0)||(direct==2))
       digitalWrite(inBpin[motor], HIGH);
     else
       digitalWrite(inBpin[motor], LOW);
     analogWrite(pwmpin[motor], pwm);
   }
 }
}

void motorOff(int motor) // function to turn a specified motor off
{
 // Initialize braked
 for (int i=0; i<2; i++)
 {
   digitalWrite(inApin[i], LOW);
   digitalWrite(inBpin[i], LOW);
 }
 analogWrite(pwmpin[motor], 0); // this instruction turns a specified motor off.
}


