#define mot_speed 180 //motor speed
#define IR_left 12  //left IR uses pin 12
#define IR_right 11  //right IR uses pin 11
#define Delay 100 //Delay constant

//Right Motor H-Bridge to arduino
int ENA = 6; //speed pin
int IN1 = 7; //direction pin
int IN2 = 8; //direction pin

//Left Motor H-Bridge to arduino
int ENB = 5; //speed pin
int IN3 = 9; //direction pin
int IN4 = 10; //direction pin

void setup() {
  // put your setup code here, to run once:
   pinMode(ENA, OUTPUT); //speed control pin for right motor on h-bridge
   pinMode(IN1, OUTPUT); //goes to right motor
   pinMode(IN2, OUTPUT); //goes to right motor
   pinMode(IN3, OUTPUT); //goes to left motor
   pinMode(IN4, OUTPUT); //goes to left motor
   pinMode(ENB, OUTPUT); //speed control pin for left motor on h-bridge
   pinMode(IR_left, INPUT); //IR left pin on arduino receives sensor input
   pinMode(IR_right, INPUT); //IR right pin on arduino receives sensor input
   analogWrite(ENA, mot_speed); //Setting ENA pin to motor speed constant
   analogWrite(ENB, mot_speed); //Setting ENB pin to motor speed constant
   Serial.begin(9600); //used to display print statements on serial monitor for debugging
}

//ENA, IN1, IN2 control right motor
//ENB, IN3, IN4 control left motor
 
void loop(){
  //reads states of right sensor and left sensor (whether or not its over the line)
  int readIR_R = digitalRead(IR_right); 
  int readIR_L = digitalRead(IR_left);

  //If both sensors are low (meaning the bot is centered on the line), move forward
  if (readIR_R == LOW && readIR_L == LOW){
    forward(); //call forward function (defined later in code))
  }

  //If right sensor is on line, turn right
  else if (readIR_R == HIGH && readIR_L == LOW){
    right_turn(); //call right turn function (defined later in code)
  }

  //If left sensor is on line, turn left
  else if (readIR_R == LOW && readIR_L == HIGH){
    left_turn(); //call left turn function (defined later in code)
  }

  else
  {
    STOP(); //If both sensor are on the line, call the stop function
  }
  //set the speed of the motors again after the functions are called so they remain unchanged
  analogWrite(ENA, mot_speed);
  analogWrite(ENB, mot_speed); 
}

//movement functions used in the if statements
void forward(){ //forward function
  //makes right wheel spin clockwise 
  digitalWrite(IN1, HIGH); //H bridge sends a high and low signal indicating clockwise rotation
  digitalWrite(IN2, LOW);
  
  //makes left wheel spin clockwise -> they both spin the same direction
  digitalWrite(IN3, HIGH); //H bridge sends a high and low signal indicating clockwise rotation
  digitalWrite(IN4, LOW); 
  Serial.println("FOWARD"); //prints "FORWARD" to monitor
}

void left_turn(){ //left turn function
  digitalWrite(IN1, LOW); //Turns the right motor off so that the right wheel becomes a pivot
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH); //Moves the left wheel clockwise for a left turn
  digitalWrite(IN4, LOW); 
  Serial.println("Right motor should be turning"); //prints the message to the monitor
  }

void right_turn(){ //right turn function
  digitalWrite(IN1, HIGH); //Moves the right wheel clockwise for a right turn
  digitalWrite(IN2, LOW); 

  digitalWrite(IN3, LOW); //Turns the left wheel off so that it acts as a pivot
  digitalWrite(IN4, LOW); 
  
  Serial.println("Left motor should be turning"); //prints the message to the monitor
  }

void STOP(){ //Stop function
  digitalWrite(IN1, LOW); //Turns right wheel off
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW); //Turns left wheel off
  digitalWrite(IN4, LOW); 
  
  Serial.println("Stop"); //prints the message to the monitor
  delay(Delay); //Ensures that the bot doesn't call any other functions
  
  }
