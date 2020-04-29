#include <ESP8266WiFi.h>

//int a = 5, b = 255;
float a = 5.05, b = 255.0255,  result = 0.0;
float Array_A [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float Array_C [5][5] = {
  {1,2,3,4,5}, {1,2,3,4,5},
  {1,2,3,4,5}, {1,2,3,4,5},
  {1,2,3,4,5}};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  pinMode(2, OUTPUT);
  ESP.wdtDisable();

  timer1_enable(TIM_DIV256, TIM_EDGE, TIM_SINGLE);
  timer1_write(600000);
  
  toggle();
  add(a,b);
  multiply(a,b);
  divide(a,b);
  ArrayMath(a);
  Shift(a,b);

  ESP.wdtEnable(1000);
}

void toggle()
{
  float timerStart = 0.0, timerEnd = 0.0;
  float resultTime = 0.0;
  
  timerStart = timer1_read();
  digitalWrite(2, HIGH);
  digitalWrite(2, LOW);
  timerEnd = timer1_read();

  Serial.print("Ticks to toggle: ");
  Serial.print(timerStart - timerEnd);
  Serial.print("  Time: ");
  resultTime = ((timerStart - timerEnd)/312592)*1000000;
  Serial.print(resultTime);
  Serial.println();
}

void add(float a, float b)
{
  float timerStart = 0.0, timerEnd = 0.0;
  double resultTime = 0.0;
  
  timerStart = timer1_read();
  result = a + b;
  timerEnd = timer1_read();

  Serial.print("Ticks to add: ");
  Serial.print(timerStart - timerEnd);
  Serial.print("  Time: ");
  resultTime = ((timerStart - timerEnd)/312592)*1000000;
  Serial.print(resultTime);
  Serial.println();
}

void multiply(float a, float b)
{
  float timerStart = 0.0, timerEnd = 0.0;
  double resultTime = 0.0;

  timerStart = timer1_read();
  result = a * b;
  timerEnd = timer1_read();

  Serial.print("Ticks to multiply: ");
  Serial.print(timerStart - timerEnd);
  Serial.print("  Time: ");
  resultTime = ((timerStart - timerEnd)/312592)*1000000;
  Serial.print(resultTime);
  Serial.println();
}

void divide(float a, float b)
{
  float timerStart = 0.0, timerEnd = 0.0;
  double resultTime = 0.0;

  timerStart = timer1_read();
  result = a / b;
  timerEnd = timer1_read();

  Serial.print("Ticks to divide: ");
  Serial.print(timerStart - timerEnd);
  Serial.print("  Time: ");
  resultTime = ((timerStart - timerEnd)/312592)*1000000;
  Serial.print(resultTime);
  Serial.println();
}

void Shift(float A, float B)
{
  float timerStart = 0.0, timerEnd = 0.0;
  double resultTime = 0.0;
  
  timerStart = timer1_read();
  result = B << A;
  timerEnd = timer1_read();

  Serial.print("Ticks after shifting: ");
  Serial.print(timerStart - timerEnd);
  Serial.print("  Time: ");
  resultTime = ((timerStart - timerEnd)/312592)*1000000;
  Serial.print(resultTime);
  Serial.println();
}

void ArrayMath(float A)
{
  float result = 0.0;
  float timerStart = 0.0, timerEnd = 0.0;
  double resultTime = 0.0;
  
  timerStart = timer1_read();
  for (int i = 0; i < 10; i++){ //populate Arrays
      Array_A [i] = A - i;
  }
      
  for (int i = 0; i < 10; i ++){  //search array, find middle, toggle LED
      if(Array_A[i] == (A - 5)){
          break;
      }
  }
  
  for (int i = 0; i < 5; i++){ //cross the values
         for(int j = 0; j < 5;  j++){
               C = Array_C[i][j];
               Array_C[i][j] = Array_C[j][i];
               Array_C[j][i] = C;
         }
  }
  timerEnd = timer1_read();

  Serial.print("Ticks after array manipulation: ");
  Serial.print(timerStart - timerEnd);
  Serial.print("  Time: ");
  resultTime = ((timerStart - timerEnd)/312592)*1000000;
  Serial.print(resultTime);
  Serial.println();
}

void loop() {
  
}