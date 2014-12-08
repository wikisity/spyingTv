                                                                                                                                                           
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
int statpin = 13;  // instruction needed to connected to analog pin 13

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

void loop()  // the loop routine runs over and over again forever:
{                            
 motorGo(0, CW, 6000);  //CW command means motor zero or actuator zero runs out with a pulse width modulation of 6000.
 motorGo(1, CW, 6000); // actuator one runs at the same speed as actuator zero. Actuator zero is connected to the entry A1B1 of the monstor shield.
 delay(8000);         // both motors run forward for 8s. Also,delay in between reads for stability. Actuator 1 is connected to the entry A2B2 of the monster shield.
 
 motorGo(0, CCW, 3000); // CCW commands means actuator zero runs back in. Pulse width modulation equals to 3000.
 motorGo(1, CCW, 3000); // actuator one follow the same movement as actuator zero. Both run all the way in.
 delay(8000);   // run backward for 8s.
 
 motorGo(0, CW, 3000); // Actuator zero runs out.
 motorGo(1, CCW, 3000); // Actuator one runs in. Both run opposite directions, but maintain sAme distance
 delay(8000);   // Both run opposite direction for 8s.
 
 motorGo(0, CCW, 3000); // Actuator zero run in.
 motorGo(1, CW, 3000);  // Actuator one runs out.
 delay(8000);  // Both maintain opposite directions for 8s.
 
 motorGo(0, CCW, 3000); 
 motorGo(1, CW, 3000);
 delay(8000);   // Third time that both actuator run in the opposite direction.
 
 motorGo(0, CW, 3000);
 motorGo(1, CCW, 3000);
 delay(8000);  // Here is the fourth times.
 
 motorGo(0, CCW, 7000); // Here the two actuators run all the way in.
 motorGo(1, CCW, 7000);  // they kept the same distance and run back in at the same time.
 delay(14000); // the time expanded allow the actuator to run all the way in.


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































