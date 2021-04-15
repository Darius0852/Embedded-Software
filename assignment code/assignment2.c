/*
 * Name: Darius Ghomashchian
 * HW-ID: H00133128
 * ASSIGNMNET 2 B31DG
 */

// Include Arduino FreeRTOS library
#include <Arduino_FreeRTOS.h>

// Include semaphore supoport
#include <semphr.h>

/* 
 * Declaring a global variable of type SemaphoreHandle_t 
 */
//semaphores to handle motor speeds
SemaphoreHandle_t interruptPlusASem;
SemaphoreHandle_t interruptMinusASem;
SemaphoreHandle_t interruptPlusBSem;
SemaphoreHandle_t interruptMinusBSem;
SemaphoreHandle_t interruptBreaks;
SemaphoreHandle_t interruptDiagMode;

//Tasks not triggered by interrupts need to be declared here
void monitorMode(void *pvParameters);
void sensorProMode(void *pvParameters);

//Global Variables
signed int speedA = 0;
signed int speedB = 0;

//Pin values for Motor A
const int keyPlusA = 10;
const int keyMinusA = 16;
const int keyBreaks = 5;
const int pwmAPin = 6;
const int dirAPin = 12;
const int brakeAPin = 8;

//Pin values for Motor B
const int keyPlusB = 2;
const int keyMinusB = 3;
const int keyDiag = 7;
const int pwmBPin = 11;
const int dirBPin = 13;
const int brakeBPin = 9;

//initialise variable to track diagnostic mode state and breaking mode state
bool diagnosticMode = false;
bool breakingMode = false;

//initialise variable to track of how many times sensors are monitored
int monitorCounter = 0;

void setup() {

  Serial.begin(9600);
  // Configure I/O for buttons
   pinMode(keyPlusA, INPUT);
   pinMode(keyMinusA, INPUT);
   pinMode(keyBreaks, INPUT);
   pinMode(keyPlusB, INPUT);
   pinMode(keyMinusB, INPUT);
   pinMode(keyDiag, INPUT);
   
   // configure I/O for motors
   pinMode(pwmAPin, OUTPUT);
   pinMode(pwmBPin, OUTPUT);
   pinMode(dirAPin, OUTPUT);
   pinMode(dirBPin, OUTPUT);
   pinMode(brakeAPin, OUTPUT);
   pinMode(brakeBPin, OUTPUT);

 // Create task for breaking both motors (highest priority)
  xTaskCreate(breaks, // Task function
              "BREAKS", // Task name
              128, // Stack size 
              NULL, 
              3, // Priority
              NULL );
  // Create task for diagnostic mode (high priority)
  xTaskCreate(diagMode, // Task function
              "BREAKS", // Task name
              128, // Stack size 
              NULL, 
              2, // Priority
              NULL ); 
 // Create task for increasing motor A speed (low priority)
  xTaskCreate(checkPlusA, // Task function
              "Check Plus A Button", // Task name
              128, // Stack size 
              NULL, 
              0, // Priority
              NULL );
 // Create task for decreasing motor A speed (low priority)
  xTaskCreate(checkMinusA, // Task function
              "Check Minus A Button", // Task name
              128, // Stack size 
              NULL, 
              0, // Priority
              NULL );  
 // Create task for increasing motor B speed (low priority)
  xTaskCreate(checkPlusB, // Task function
              "Check Plus B Button", // Task name
              128, // Stack size 
              NULL, 
              0, // Priority
              NULL );
 // Create task for decreasing motor B speed (low priority)
  xTaskCreate(checkMinusB, // Task function
              "Check Minus B Button", // Task name
              128, // Stack size 
              NULL, 
              0, // Priority
              NULL );      
 // Create task for monitor mode (medium priority)
  xTaskCreate(monitorMode, // Task function
              "Check Minus B Button", // Task name
              128, // Stack size 
              NULL, 
              1, // Priority
              NULL );    
 // Create task for sensor processing (low priority)
  xTaskCreate(sensorProMode, // Task function
              "Check Minus B Button", // Task name
              128, // Stack size 
              NULL, 
              0, // Priority
              NULL );                           

  /**
   * Create a binary semaphore.
   * https://www.freertos.org/xSemaphoreCreateBinary.html
   */
  interruptBreaks = xSemaphoreCreateBinary();
  interruptDiagMode = xSemaphoreCreateBinary();
  interruptPlusASem = xSemaphoreCreateBinary();
  interruptMinusASem = xSemaphoreCreateBinary();
  interruptPlusBSem = xSemaphoreCreateBinary();
  interruptMinusBSem = xSemaphoreCreateBinary();

  if (interruptBreaks != NULL) {
    // Attach interrupt for breaks
    attachInterrupt(digitalPinToInterrupt(keyBreaks), interruptHandler5, LOW);
  }
  if (interruptDiagMode != NULL) {
    // Attach interrupt fordiagnostic mode
    attachInterrupt(digitalPinToInterrupt(keyDiag), interruptHandler6, LOW);
  }
  if (interruptPlusASem != NULL) {
    // Attach interrupt for increasing A
    attachInterrupt(digitalPinToInterrupt(keyPlusA), interruptHandler1, LOW);
  }
  if (interruptMinusASem != NULL) {
    // Attach interrupt for decreasing A
    attachInterrupt(digitalPinToInterrupt(keyMinusA), interruptHandler2, LOW);
  }  
  if (interruptPlusBSem != NULL) {
    // Attach interrupt for increasing B
    attachInterrupt(digitalPinToInterrupt(keyPlusB), interruptHandler3, LOW);
  }
  if (interruptMinusBSem != NULL) {
    // Attach interrupt for decreasing B
    attachInterrupt(digitalPinToInterrupt(keyMinusB), interruptHandler4, LOW);
  }

  
}

void loop() {}

void interruptHandler1() {
  xSemaphoreGiveFromISR(interruptPlusASem, NULL);
}

void interruptHandler2() {
  xSemaphoreGiveFromISR(interruptMinusASem, NULL);
}

void interruptHandler3() {
  xSemaphoreGiveFromISR(interruptPlusBSem, NULL);
}

void interruptHandler4() {
  xSemaphoreGiveFromISR(interruptMinusBSem, NULL);
}

void interruptHandler5() {
  xSemaphoreGiveFromISR(interruptBreaks, NULL);
}

void interruptHandler6() {
  xSemaphoreGiveFromISR(interruptDiagMode, NULL);
}

/* 
 * Increase speed on Motor A task
 */
void checkPlusA(void *pvParameters)
{
  (void) pvParameters;
  for (;;) {
    /**
     * Take the semaphore and increase motor A by 50 (20%)
     */
    if (xSemaphoreTake(interruptPlusASem, portMAX_DELAY) == pdPASS) {
      speedA += 50;
      if (speedA > 250) {speedA = 250;}
      if (speedA > 0) {digitalWrite(dirAPin, 1);}
      else if (speedA < 0) {digitalWrite(dirAPin, 0);}
      analogWrite(pwmAPin, speedA);
      digitalWrite(brakeAPin, 0);
      Serial.write("Speed A Increased to \r\n");
      Serial.print(speedA);
    } 
    //delay added for stability (debounce)
    vTaskDelay(1);
  }
}

/* 
 * decrease speed motor A task 
 */
void checkMinusA(void *pvParameters)
{
  (void) pvParameters;
  for (;;) {   
    /**
     * Take the semaphore and decrease speed A by 50 (20%)
     */
    if (xSemaphoreTake(interruptMinusASem, portMAX_DELAY) == pdPASS) {
      speedA = speedA - 50;
      if (speedA < -250) {speedA = -250;} //don't let speed go below 250
      if (speedA > 0) {digitalWrite(dirAPin, 1);} //set direction forward if speed +'ve
      else if (speedA < 0) {digitalWrite(dirAPin, 0);} //set direction negative if speed -'ve
      analogWrite(pwmAPin, speedA); //write speed to pwm pin
      digitalWrite(brakeAPin, 0); //set breaks to 0
      Serial.write("Speed A Decreased to \r\n");  
      Serial.print(speedA);
    }
    //delay added for stability (debounce)
    vTaskDelay(1);
  }
}

/* 
 * Increase speed Motor B task
 */
void checkPlusB(void *pvParameters)
{
  (void) pvParameters;
  for (;;) {
    /**
     * Take the semaphore and increase motor B by 50 (20%)
     */
    if (xSemaphoreTake(interruptPlusBSem, portMAX_DELAY) == pdPASS) {
      speedB += 50;
      if (speedB > 250) {speedB = 250;}
      if (speedB > 0) {digitalWrite(dirBPin, 1);}
      else if (speedB < 0) {digitalWrite(dirBPin, 0);}
      analogWrite(pwmBPin, speedB);
      digitalWrite(brakeBPin, 0);
      Serial.write("Speed B Increased to \r\n");
      Serial.print(speedB);
    } 
    //delay added for stability (debounce)
    vTaskDelay(1);
  }
}

/* 
 * Decrease speed Motor B task
 */
void checkMinusB(void *pvParameters)
{
  (void) pvParameters;
  for (;;) {   
    /**
     * Take the semaphore and decrease motor B by 50 (20%)
     * https://www.freertos.org/a00122.html
     */
    if (xSemaphoreTake(interruptMinusBSem, portMAX_DELAY) == pdPASS) {
      speedB = speedB - 50;
      if (speedB < -250) {speedB = -250;}
      if (speedB > 0) {digitalWrite(dirBPin, 1);}
      else if (speedB < 0) {digitalWrite(dirBPin, 0);}
      analogWrite(pwmBPin, speedB);
      digitalWrite(brakeBPin, 0);
      Serial.write("Speed B Decreased to \r\n");
      Serial.print(speedB);
    }
    //delay added for stability (debounce)
    vTaskDelay(1);
  }
}

/* 
 * break both Motors Task
 */
void breaks(void *pvParameters)
{
  (void) pvParameters;
  for (;;) {  
    /**
     * Take the semaphore.
     * https://www.freertos.org/a00122.html
     */
    if (xSemaphoreTake(interruptBreaks, portMAX_DELAY) == pdPASS) {
      //toggle breaking mode
      breakingMode = !breakingMode;
      
      if (breakingMode == true) {
        speedA = 0;
        speedB = 0;
        digitalWrite(brakeAPin, 1);
        digitalWrite(brakeBPin, 1);
        Serial.write("BREAKS ON");
      } else {
        Serial.write("BREAKS OFF");
      } 
    } 
    //delay added for stability (debounce)
    vTaskDelay(1);
  }
}

/* 
 * Diagnostic mode checks pwm pin readings over last 2 seconds
 */
void diagMode(void *pvParameters)
{
  (void) pvParameters;
  pinMode(pwmAPin, INPUT);
  pinMode(pwmBPin, INPUT); 
  unsigned long currentMillis = millis(); //keep track of start time reading sensors
  for (;;) {
    if (xSemaphoreTake(interruptDiagMode, portMAX_DELAY) == pdPASS) {
      if ((currentMillis % 2000) == 0) {
        int sensorAVal = analogRead(pwmAPin);
        int sensorBVal = analogRead(pwmBPin);
        Serial.print("Sensor A over 2 seconds");
        Serial.print(sensorAVal);
        Serial.print("Sensor B over 2 seconds");
        Serial.print(sensorBVal);
      }
    } 
    vTaskDelay(1);
  }
}

/* 
 * check absolute value of motors A and B (to neglect sign)
   if both motors > 88% (220) then increment monitor counter.
   once reached 6 counts flash LED
 */
void monitorMode(void *pvParameters)
{
  (void) pvParameters;
  for (;;) {
    if (abs(speedA) > 220 && abs(speedB) > 220) {
       //increment counter
        monitorCounter++;  
      if (monitorCounter == 5) {
            //flash at a rate of of 4Hz(4 times per second) for 3 seconds 
            for (int x = 1; x <= 12 ; x++) {
            digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
            vTaskDelay( 250 / portTICK_PERIOD_MS ); // wait for one second
            }
          }
      //set counter back to 0 after reading 6 times
      if (monitorCounter == 5) {
        monitorCounter = 0;
      }
    }
    vTaskDelay(1);
}
}

/* 
 * sensor processing keeps CPU busy for 5 seconds with a delay
 */
void sensorProMode(void *pvParameters)
{
  (void) pvParameters;
  for (;;) {
    vTaskDelay( 5000 / portTICK_PERIOD_MS ); // keep busy for 5 seconds 
  }
}
