#define LIGHT_THRESH 200 // greater than = black

int Left_Pin = A6;     // analog 6
int Right_Pin = A0;    // analog 0
int Led_Pin = 13;

float Left_Val = 0;
float Right_Val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Left_Pin, INPUT);
  pinMode(Right_Pin, INPUT);

  pinMode(Led_Pin, OUTPUT);

//  Serial.begin(9600);
}

void loop() {
  
  Left_Val = analogRead(Left_Pin);
//  Serial.print(Left_Val);
//  Serial.print(' ');

//  if(Left_Val < LIGHT_THRESH)
//  {//white
//    digitalWrite(Led_Pin, HIGH);
//  }
//  else
//  {//black
//    digitalWrite(Led_Pin, LOW);
//  }

  Right_Val = analogRead(Right_Pin);
//  Serial.print(Right_Val);
//  Serial.print(' ');

  if(Right_Val < LIGHT_THRESH)
  {//white
    digitalWrite(Led_Pin, HIGH);
  }
  else
  {//black
    digitalWrite(Led_Pin, LOW);
  }


  Serial.println();
  delay(1000);

}
