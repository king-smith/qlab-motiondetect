/*
  IR Reader/Output 

  Used to read analog input from two Duinotech PIR Motion Sensor Modules
  Outputs serial via USB when the IR's are activated/deactivated

  created 4 Jun 2017
  by Mirren King-Smith

 */

/*******Constants********/

// seconds to wait for fade down (600 for 10 minutes)
const int timeToReset = 30;  

/************************/

const int analogInA = A0; 
const int analogInB = A1;

int sensorA = 0;
int sensorB = 0;

int timeStart = 0;
int timeCurrent = 0;

int triggerCount = 0;

bool active = false;

void setup() {
  Serial.begin(9600);
  delay(1000); // Give time to set up
}

void loop() {
  
  analyseSensors();

  if (!active) {
    if (triggerCount > 2) {
      active = true;
      timeStart = millis()/1000;
      triggerCount = 0;
      Serial.write("1");
    }
    
  } else {
         
    if (triggerCount < 4) { 
      timeCurrent = millis()/1000 - timeStart;
    } else {
      timeStart = millis()/1000;
      timeCurrent = 0;
      triggerCount = 0;
    }
    
    if (timeCurrent > timeToReset) 
    {
      active = false;
      triggerCount = 0;
      Serial.write("2");
    }
  }
}

void analyseSensors() {
  sensorA = analogRead(analogInA);
  sensorB = analogRead(analogInB);
  
  if (sensorA > 0) {
    triggerCount++;
  }
  if (sensorB > 0) {
    triggerCount++;
  }
}

void serialDebug() {
  Serial.write(sensorA);
  Serial.write(sensorB);
  //Serial.print("SensorA: ");
 // Serial.print(sensorA);
 // Serial.print(" : SensorB: ");
 // Serial.print(sensorB);
 // Serial.print("\n");
}

