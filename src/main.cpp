#include <Arduino.h>
#define CLK_PIN 15
#define DT_PIN 4
#define LED_PIN 13

float WHEEL_CIRCUMFERENCE = 2.0;
const unsigned long INACTIVITY_TIMEOUT = 2000; // זמן חוסר פעילות לפני כיבוי הלד (במילישניות)

//int maxSpeed = 130;

float MAX_SPEED_KMH = 4; // מהירות מקסימלית בקילומטרים לשעה
const float SPEED_OVER_LIMIT = 20.0; // תוספת מהירות בקילומטרים לשעה

volatile unsigned long lastMillis = 0;
volatile unsigned long interval = 0;
volatile unsigned long lastInterruptTime = 0;
volatile unsigned long currentMillis = 0;
volatile float rps = 0;
float maxRPS; // מספר סיבובים מותרים לשנייה
float limitRPS; // מספר סיבובים המותרות לשנייה עם תוספת
unsigned long lastChangeTime = 0; // הזמן האחרון שבו חל שינוי במהירות


void IRAM_ATTR handleEncoder() 
{
  Serial.println("i in handleEncoder");
  currentMillis = millis();
  if (currentMillis - lastInterruptTime > 1000) { // כל שנייה
    interval = currentMillis - lastMillis;
    lastMillis = currentMillis;
    rps = 1000.0 / interval; // חישוב RPS
    lastInterruptTime = currentMillis;
    lastChangeTime = currentMillis; // עדכון זמן שינוי האחרון
  }
}


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(DT_PIN,INPUT);
  pinMode(CLK_PIN,INPUT);
  pinMode(LED_PIN,OUTPUT);


   float rpm = (MAX_SPEED_KMH * 1000.0) / (WHEEL_CIRCUMFERENCE * 60.0); // RPM
  maxRPS = rpm / 60.0; // RPS


  // חישוב מספר הסיבובים המותרים לשנייה עם תוספת
  float rpmOverLimit = ((MAX_SPEED_KMH + SPEED_OVER_LIMIT) * 1000.0) / (WHEEL_CIRCUMFERENCE * 60.0); // RPM
  limitRPS = rpmOverLimit / 60.0; // RPS

  // הדפסת מספר הסיבובים המותרים לשנייה
  Serial.print("Max allowed RPS is set to: ");
  Serial.println(maxRPS);
  
  attachInterrupt(digitalPinToInterrupt(CLK_PIN), handleEncoder, RISING);
 
}

void loop()
{
  currentMillis = millis();

  // בדיקה אם לא היה שינוי במהירות בשנייה האחרונה
  if ((currentMillis - lastChangeTime) > INACTIVITY_TIMEOUT) 
    digitalWrite(LED_PIN, LOW); // כיבוי הלד אם לא היה שינוי
   else if (rps > maxRPS) { // תנאי למהירות גבוהה
    digitalWrite(LED_PIN, HIGH); // הפעלת הלד
    if (rps > limitRPS)  // תנאי למהירות גבוהה ב-20 קמ"ש
    Serial.println("Speed exceeds the limit by 20 km/h!");
   }
  else 
    digitalWrite(LED_PIN, LOW); // כיבוי הלד
    
  delay(100); // המתנה קצרה לפני הבדיקה הבאה
}
