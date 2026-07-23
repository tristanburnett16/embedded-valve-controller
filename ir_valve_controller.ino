                                  #include <IRremote.hpp>

decode_results results;

// Global Variable 
int sensorPin1 = 1;
const int sensorPin2 = 2;
int sensorPin3 = 3;
int sensorPin4 = 4;
int sensorPin6 = 6;
int sensorPin7 = 7;


unsigned long lastcode = 0;


IRrecv irrecv(sensorPin2);

int VAVLE_OPEN = 0xC;
int VAVLE_CLOSED = 0x18;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Initialize serial monitor communication
  
  // Start the receiver and flash the built-in LED on signal detection
  IrReceiver.begin(sensorPin2, ENABLE_LED_FEEDBACK); 

  //outputs to relay
  pinMode(sensorPin3, OUTPUT);
  pinMode(sensorPin4, OUTPUT);

  digitalWrite(sensorPin3, LOW);
  digitalWrite(sensorPin4, LOW);
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long code = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(code);
    Serial.println(lastcode);
    
      if (lastcode != code) {
        if (IrReceiver.decodedIRData.command == VAVLE_OPEN) {
          Serial.println(code);
          Serial.println(lastcode);
          Serial.println("Vavle open");
          digitalWrite(sensorPin3, HIGH);
          delay(5000);
          digitalWrite(sensorPin3, LOW);
          
        }
        

        //closed mode
        if (IrReceiver.decodedIRData.command == VAVLE_CLOSED) {
          Serial.println("Vavle close");
          digitalWrite(sensorPin4, HIGH);
          delay(5000);
          digitalWrite(sensorPin4, LOW);
          
        }
      }
    lastcode = code;
  }

  
  //resumes next signal
  IrReceiver.resume();
  
  
}
