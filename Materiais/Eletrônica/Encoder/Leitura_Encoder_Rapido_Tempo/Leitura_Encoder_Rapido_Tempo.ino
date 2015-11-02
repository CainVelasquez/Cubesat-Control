
int clk = 8;
int Data = 4;
int csn = 7;
char D11 = 0;
char D10 = 0;
char D9 = 0;
char D8 = 0;
char D7 = 0;
char D6 = 0;
char D5 = 0;
char D4 = 0;
char D3 = 0;
char D2 = 0;
char D1 = 0;
char D0 = 0;
int Resposta;
float Angulo;
int graus;
int minutos;
int segundos;


void setup() {

  Serial.begin(9600);

  pinMode(clk, OUTPUT);
  pinMode(Data, INPUT);
  pinMode(csn, OUTPUT);

  delay(100);
}



void loop() {

  digitalWrite(clk,HIGH);
  digitalWrite(csn,HIGH);
  delayMicroseconds(1);

  digitalWrite(csn,LOW);
  delayMicroseconds(1);

  digitalWrite(clk,LOW);
  delayMicroseconds(1);
  digitalWrite(clk,HIGH);
  D11 = digitalRead(Data);
  delayMicroseconds(1);

  digitalWrite(clk,LOW);
  delayMicroseconds(1);
  digitalWrite(clk,HIGH);
  D10 = digitalRead(Data);
  delayMicroseconds(1);

  digitalWrite(clk,LOW);
  delayMicroseconds(1);
  digitalWrite(clk,HIGH);
  D9 = digitalRead(Data);
  delayMicroseconds(1);

  digitalWrite(clk,LOW);
  delayMicroseconds(1);
  digitalWrite(clk,HIGH);
  D8 = digitalRead(Data);
  delayMicroseconds(1);

  digitalWrite(clk,LOW);
  delayMicroseconds(1);
  digitalWrite(clk,HIGH);
  D7 = digitalRead(Data);
  delayMicroseconds(1);

  digitalWrite(clk,LOW);
  delayMicroseconds(1);
  digitalWrite(clk,HIGH);
  D6 = digitalRead(Data);
  delayMicroseconds(1);

  digitalWrite(clk,LOW);
  delayMicroseconds(1);
  digitalWrite(clk,HIGH);
  D5 = digitalRead(Data);
  delayMicroseconds(1);

  digitalWrite(clk,LOW);
  delayMicroseconds(1);
  digitalWrite(clk,HIGH);
  D4 = digitalRead(Data);
  delayMicroseconds(1);

  digitalWrite(clk,LOW);
  delayMicroseconds(1);
  digitalWrite(clk,HIGH);
  D3 = digitalRead(Data);
  delayMicroseconds(1);

  digitalWrite(clk,LOW);
  delayMicroseconds(1);
  digitalWrite(clk,HIGH);
  D2 = digitalRead(Data);
  delayMicroseconds(1);

  digitalWrite(clk,LOW);
  delayMicroseconds(1);
  digitalWrite(clk,HIGH);
  D1 = digitalRead(Data);
  delayMicroseconds(1);

  digitalWrite(clk,LOW);
  delayMicroseconds(1);
  digitalWrite(clk,HIGH);
  D0 = digitalRead(Data);
  delayMicroseconds(1);

  Resposta = 2048*D11 + 1024*D10 + 512*D9 + 256*D8 + 128*D7 + 64*D6 + 32*D5 + 16*D4 + 8*D3 + 4*D2 + 2*D1 + 1*D0;

  Angulo = 0.087890625*Resposta;

  Serial.print(Angulo,3);
  Serial.print(" ");
  Serial.println(micros());


}










