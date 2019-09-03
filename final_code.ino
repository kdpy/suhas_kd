 #include <Servo.h>
 #include <dht.h>


dht DHT;
#define DHT11_PIN 10

// Customize here pulse lengths as needed
#define MIN_PULSE_LENGTH 1000 // Minimum pulse length in µs
#define MAX_PULSE_LENGTH 2000 
#define MOD_PULSE_LENGTH 1500 // Maximum pulse length in µs

// ---------------------------------------------------------------------------
Servo throtle, roll, pitch, yaw,toggle;
String recived_data;


//***********here this functions will turn the drone to diiffrent directions
void yawl()
{
yaw.writeMicroseconds(1350);  
} 
void front()
{
pitch.writeMicroseconds(1650);  
}
void rolr()
{
roll.writeMicroseconds(1350); 
}
//**************** pin detail ***************************************//
// pin->4  = for throtle
// pin->5  = for roll
// pin->6  = for pitch
// pin->7  = for yaw
// pin->8  = for toggle
// pin->10 = for Humidity sensor

//*************** some information *******************************//
// function(MOD_PULSE_LENGTH);
// here some functions are declaired with "MOD_PULSE_LENGTH" 
// because as a default remote controller swtuches are in middle position so that 
// remote will transmit a 50% duty cycle PWM wave constantly thats why i also mimicking this 
// these declaration shown with "<--" these symbol in belowe codes 
void setup() {

//***********baud rate for communication ****************//
    Serial.begin(9600);
    
//*******************assigning pins to motors************//
    throtle.attach(4);
    roll.attach(5);
    pitch.attach(6);
    yaw.attach(7); 
    toggle.attach(8); 
}

void loop() {
  // sends the data to reciver
     int chk = DHT.read11(DHT11_PIN);
     Serial.print("Temperature = ");
     Serial.println(DHT.temperature);
     Serial.print("Humidity = ");
     Serial.println(DHT.humidity);
     delay(1000);
     
  while (Serial.available()) //Check if there is an available byte to read from seral device
  {     
    delay(10); //Delay added to make thing stable
    char c = Serial.read(); //Conduct a serial read
    if (c == '#') {
      break; //Exit the loop when the # is detected after the word
    }
    recived_data += c; //Shorthand for recived_data = recived_data + c
  }
  if (recived_data.length() > 0) {
    Serial.println(recived_data);
    //----------Control motors----------//
    if (recived_data == "arm") 
    {
     Serial.println("arm");
     
     // this function will arm the drone means ready to take comands 
     throtle.writeMicroseconds(MIN_PULSE_LENGTH);  
     yaw.writeMicroseconds(MIN_PULSE_LENGTH);  
    }
    else if(recived_data == "min")
    {
      Serial.println("MOD");
     roll.writeMicroseconds(MOD_PULSE_LENGTH); // <--
     pitch.writeMicroseconds(MOD_PULSE_LENGTH); // <--
     yaw.writeMicroseconds(MOD_PULSE_LENGTH); // <--
     toggle.writeMicroseconds(MIN_PULSE_LENGTH); // toggle should  be minimum so that we can contole easy mode

     // mimiking the remote controler switch position as a physical movents 
     // by giving PWM signals with respect to modified movements 
     //         ____
     //       *      *
     //      *        *
     //     *          *
     // ****            ***** <-- this graph shows how drone raises 

     //   *--->---*
     //   |       |
     // ->*       |
     //   |       |
     //   *---<---*   <----this shows how drone movements in air
    
     throtle.writeMicroseconds(1200);     
     delay(1000);
     throtle.writeMicroseconds(1300);
     delay(1000);
     throtle.writeMicroseconds(1400);
     delay(4000); // untill here drone raises slowly towards up 
     front();
     delay(1000);
     pitch.writeMicroseconds(MOD_PULSE_LENGTH); 
     delay(1000); 
     rolr(); // move towards left
     delay(1000);
     roll.writeMicroseconds(MOD_PULSE_LENGTH);
     delay(1000);
     yawl(); // move towards front
     delay(2000);
     yaw.writeMicroseconds(MOD_PULSE_LENGTH);
     delay(1000);
     rolr();
     delay(1000);
     roll.writeMicroseconds(MOD_PULSE_LENGTH);
     delay(1000);
     yawl();
     delay(2000);
     yaw.writeMicroseconds(MOD_PULSE_LENGTH);
     delay(1000);
     rolr();
     delay(1000);
     roll.writeMicroseconds(MOD_PULSE_LENGTH);
     delay(1000);
     yawl();
     delay(2000);
     yaw.writeMicroseconds(MOD_PULSE_LENGTH);
     delay(1000);
     rolr();
     delay(1000);
     roll.writeMicroseconds(MOD_PULSE_LENGTH);
     delay(1000);
     yawl();
     delay(2000);
     yaw.writeMicroseconds(MOD_PULSE_LENGTH);
     delay(1000);
     rolr();
     delay(1000);
     roll.writeMicroseconds(MOD_PULSE_LENGTH);
     delay(1000);
     throtle.writeMicroseconds(1380);
     delay(3000);
     throtle.writeMicroseconds(1360);
     delay(3000);
     throtle.writeMicroseconds(1340);
     delay(2000);
     throtle.writeMicroseconds(1300);
     delay(2000);
     throtle.writeMicroseconds(1280);
     delay(2000);
     throtle.writeMicroseconds(MIN_PULSE_LENGTH);
    }
    else if(recived_data == "mov")
    {
     // this function used to stop the drone for emergency situation
     throtle.writeMicroseconds(MIN_PULSE_LENGTH); // mimicking as switch in lower position
     roll.writeMicroseconds(MOD_PULSE_LENGTH); // <--
     pitch.writeMicroseconds(MOD_PULSE_LENGTH); // <--
     yaw.writeMicroseconds(MOD_PULSE_LENGTH); // <--
     toggle.writeMicroseconds(MIN_PULSE_LENGTH); // toggle should  be minimum so that we can contole easy mode    
    }

    recived_data = "";
  }
}
