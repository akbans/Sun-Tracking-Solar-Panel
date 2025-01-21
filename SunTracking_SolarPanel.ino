/* 
  Solar Tracking System
  Home Page

  This program is designed to track the position of the sun using two LDR sensors and a servo motor.
  It adjusts the servo motor's position to ensure the solar panel is aligned with the light source.

  Components:
  - Two LDR sensors connected to analog pins A0 and A1
  - One servo motor connected to digital PWM pin 11
*/

// Include the servo library to control the servo motor
#include <Servo.h>

// Define the pins connected to the LDR sensors
#define LDR1 A0 // Analog pin for LDR1
#define LDR2 A1 // Analog pin for LDR2

// Define the allowable error margin for comparing LDR readings
#define error 10 // Error value can be adjusted based on sensitivity requirements

// Initialize the starting position for the servo motor
int Spoint = 90; // Initial servo angle, can be modified for different starting positions

// Create a servo object to interact with the servo motor
Servo servo;

// The setup function runs once when the program starts
void setup() {
  // Attach the servo motor to pin 11
  servo.attach(11);

  // Move the servo to its starting position
  servo.write(Spoint);

  // Pause to allow the servo motor to stabilize
  delay(1000);

  // Optional: Print a message to the Serial Monitor for debugging purposes
  Serial.begin(9600); // Initialize Serial Monitor communication at 9600 baud rate
  Serial.println("System Initialized. Starting Position Set.");
}

// The loop function runs continuously after setup
void loop() {
  // Step 1: Read the values from the LDR sensors
  int ldr1 = analogRead(LDR1); // Read analog value from LDR1
  delay(10); // Short delay to stabilize the reading

  int ldr2 = analogRead(LDR2); // Read analog value from LDR2
  delay(10); // Short delay to stabilize the reading

  // Print the LDR readings to the Serial Monitor for debugging
  Serial.print("LDR1 Reading: ");
  Serial.println(ldr1);
  Serial.print("LDR2 Reading: ");
  Serial.println(ldr2);

  // Step 2: Calculate the absolute differences between the readings
  int value1 = abs(ldr1 - ldr2); // Difference when LDR1 is greater
  int value2 = abs(ldr2 - ldr1); // Difference when LDR2 is greater

  // Print the calculated differences to the Serial Monitor
  Serial.print("Difference (value1): ");
  Serial.println(value1);
  Serial.print("Difference (value2): ");
  Serial.println(value2);

  // Step 3: Check if the difference is within the error margin
  if ((value1 <= error) || (value2 <= error)) {
    // Case 1: Differences are small enough to ignore
    Serial.println("No significant movement required. Servo remains in position.");
  } else {
    // Case 2: Adjust the servo based on LDR readings
    if (ldr1 > ldr2) {
      Spoint--; // Decrease the servo angle if LDR1 detects more light
      delay(15); // Add a delay for smooth movement
      Serial.println("Adjusting Servo: Moving Left.");
    }

    if (ldr1 < ldr2) {
      Spoint++; // Increase the servo angle if LDR2 detects more light
      delay(15); // Add a delay for smooth movement
      Serial.println("Adjusting Servo: Moving Right.");
    }
  }

  // Step 4: Write the new position to the servo motor
  servo.write(Spoint);

  // Step 5: Print the current servo position to the Serial Monitor
  Serial.print("Current Servo Position: ");
  Serial.println(Spoint);

  // Step 6: Add a delay to control the update frequency
  delay(100);

  // Optional: End of loop message for clarity
  Serial.println("End of Loop. Rechecking...");
  delay(200); // Additional delay for clarity and control
}
