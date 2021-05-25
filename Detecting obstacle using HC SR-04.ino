 int k,l,m,n;   //k=front  l=back   m=left   n=right
void setup() {
  pinMode(2, INPUT);//trig
  pinMode(3, OUTPUT);//echo
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A0, OUTPUT);
  //Serial.begin(9600);
  
}
void loop()
{
  //int k=distanced();//front ultrasonic
 
  //int l=distancee();//back ultrasonic
 
  //int m=distancef();//left ultrasonic
  
  //int n=distanceg();//right ultrasonic
  
  
 // Serial.print(k);Serial.print("   ");Serial.print(l);Serial.print("   ");Serial.print(m);Serial.print("   ");Serial.println(n);
  if((k=distanced())<=60){digitalWrite(10,HIGH);}else{digitalWrite(10,LOW);}
  if((l=distancee())<=60){digitalWrite(11,HIGH);}else{digitalWrite(11,LOW);}
  if((m=distancef())<=60){digitalWrite(12,HIGH);}else{digitalWrite(12,LOW);}
  if((n=distanceg())<=60){ digitalWrite(A0,HIGH);}else{digitalWrite(A0,LOW);}
}
int distanced()
{
  digitalWrite(9, LOW);
  delayMicroseconds(2);
  digitalWrite(9, HIGH);
  delayMicroseconds(10);
  digitalWrite(9, LOW);
  int q = pulseIn(2, HIGH); //gives time after which high pulse is coming
  int d = (q * 0.034) / 2; //front
  //delay(10);
  return d;
}
int distancee()
{
  digitalWrite(3, LOW);
  delayMicroseconds(2);
  digitalWrite(3, HIGH);
  delayMicroseconds(10);
  digitalWrite(3, LOW);
  delayMicroseconds(2);
  int r = pulseIn(4, HIGH); //gives time after which high pulse is coming
  int e = (r * 0.034) / 2; //back
  //delay(10);
  return e;
}
int distancef()
{
  digitalWrite(5, LOW);
  delayMicroseconds(2);
  digitalWrite(5, HIGH);
  delayMicroseconds(10);
  digitalWrite(5, LOW);
  delayMicroseconds(2);
  int s = pulseIn(6, HIGH); //gives time after which high pulse is coming
  int f = (s * 0.034) / 2; //left
 // delay(10);
  return f;
}
int distanceg()
{
  digitalWrite(7, LOW);
  delayMicroseconds(2);
  digitalWrite(7, HIGH);
  delayMicroseconds(10);
  digitalWrite(7, LOW);
  delayMicroseconds(2);
  int t = pulseIn(8, HIGH); //gives time after which high pulse is coming
  int g = (t * 0.034) / 2; //right
 // delay(10);
  return g;
}
