int R=8; 
int Gnd=9; 
int G=10;
int B=11;

void setup() {
  // put your setup code here, to run once:
  pinMode (Gnd, OUTPUT);
  pinMode (R, OUTPUT);
  pinMode (G, OUTPUT);
  pinMode (B, OUTPUT);
  digitalWrite(Gnd, LOW);
}

void loop() {
//  analogWrite(G, 100);
//  delay(5000);
//  analogWrite(G, 0);
  
  analogWrite(R, 255);
  analogWrite(G, 3);
  delay(1000);
//  analogWrite(R, 0);
//  analogWrite(G, 0);

//  analogWrite(R, 255);
//  delay(5000);
//  analogWrite(R, 0);

  
}
