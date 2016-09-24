
int Left_Light_Pin = 2;     // analog 2
int Right_Light_Pin = 5;    // analog 5

int QRE_Value_L = 0;
int QRE_Value_R = 0;

float val0;
float val1;
float val2;
float val3;
float val4;
float val5;
float val6;
float val7;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);

    // initialize serial communication:
  Serial.begin(9600);
  
  Serial.println("Setup");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Loop");
  
//  QRE_Value_L = analogRead(A2);
//  Serial.print(QRE_Value_L);
//  Serial.print(' ');
//
//  QRE_Value_R = analogRead(A5);
//  Serial.print(QRE_Value_R);
//  Serial.print(' ');

  val0 = analogRead(A0);
  val1 = analogRead(A1)* (5.0 / 1023.0);
  val2 = analogRead(A2)* (5.0 / 1023.0);
  val3 = analogRead(A3) * (5.0 / 1023.0);
  val4 = analogRead(A4) * (5.0 / 1023.0);
  val5 = analogRead(A5) * (5.0 / 1023.0);
  val6 = analogRead(A6)* (5.0 / 1023.0);
  val7 = analogRead(A7)* (5.0 / 1023.0);

  Serial.print(A0); //14
  Serial.print(" ");
  Serial.print(val0);
  Serial.print(" ");
  Serial.print(A1); //15
  Serial.print(" ");
  Serial.print(val1);
  Serial.print(" ");
  Serial.print(A2); //16
  Serial.print(" ");
  Serial.print(val2);
  Serial.print(" ");
  Serial.print(A3); //17
  Serial.print(" ");
  Serial.print(val3);
  Serial.print(" ");
  Serial.print(A4); //18
  Serial.print(" ");
  Serial.print(val4);
  Serial.print(" ");
  Serial.print(A5); //19
  Serial.print(" ");
  Serial.print(val5);
  Serial.print(" ");
  Serial.print(A6); //20
  Serial.print(" ");
  Serial.print(val6);
  Serial.print(" ");
  Serial.print(A7); //21
  Serial.print(" ");
  Serial.print(val7);
  Serial.println();
  delay(1000);

}
