int g = 9, f = 10, a = 11, b =12, e = 5, d = 6, c = 7, dp = 8;
void display(int , boolean);
void setup()
{
  pinMode(g, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(dp, OUTPUT);
}

void display(int num=-1, boolean dp=0)
{
  digitalWrite(8, dp);
  if(num == 0)
  {
    digitalWrite(g, 0);
    digitalWrite(f, 1);
    digitalWrite(a, 1);
    digitalWrite(b, 1);
    digitalWrite(e, 1);
    digitalWrite(d, 1);
    digitalWrite(c, 1);
  } else if(num == 1) {
    digitalWrite(g, 0);
    digitalWrite(f, 1);
    digitalWrite(a, 0);
    digitalWrite(b, 0);
    digitalWrite(e, 1);
    digitalWrite(d, 0);
    digitalWrite(c, 0);
  } else if(num == 2) {
    digitalWrite(g, 1);
    digitalWrite(f, 0);
    digitalWrite(a, 1);
    digitalWrite(b, 1);
    digitalWrite(e, 1);
    digitalWrite(d, 1);
    digitalWrite(c, 0);
  } else if(num == 3) {
    digitalWrite(g, 1);
    digitalWrite(f, 0);
    digitalWrite(a, 1);
    digitalWrite(b, 1);
    digitalWrite(e, 0);
    digitalWrite(d, 1);
    digitalWrite(c, 1);
  } else if(num == 4) {
    digitalWrite(g, 1);
    digitalWrite(f, 1);
    digitalWrite(a, 0);
    digitalWrite(b, 1);
    digitalWrite(e, 0);
    digitalWrite(d, 0);
    digitalWrite(c, 1);
  } else if(num == 5) {
    digitalWrite(g, 1);
    digitalWrite(f, 1);
    digitalWrite(a, 1);
    digitalWrite(b, 0);
    digitalWrite(e, 0);
    digitalWrite(d, 1);
    digitalWrite(c, 1);
  } else if(num == 6) {
    digitalWrite(g, 1);
    digitalWrite(f, 1);
    digitalWrite(a, 1);
    digitalWrite(b, 0);
    digitalWrite(e, 1);
    digitalWrite(d, 1);
    digitalWrite(c, 1);
  } else if(num == 7) {
    digitalWrite(g, 0);
    digitalWrite(f, 0);
    digitalWrite(a, 1);
    digitalWrite(b, 1);
    digitalWrite(e, 0);
    digitalWrite(d, 0);
    digitalWrite(c, 1);
  } else if(num == 8) {
    digitalWrite(g, 1);
    digitalWrite(f, 1);
    digitalWrite(a, 1);
    digitalWrite(b, 1);
    digitalWrite(e, 1);
    digitalWrite(d, 1);
    digitalWrite(c, 1);
  } else if(num == 9) {
    digitalWrite(g, 1);
    digitalWrite(f, 1);
    digitalWrite(a, 1);
    digitalWrite(b, 1);
    digitalWrite(e, 0);
    digitalWrite(d, 0);
    digitalWrite(c, 1);
  } else {
    digitalWrite(g, 0);
    digitalWrite(f, 0);
    digitalWrite(a, 0);
    digitalWrite(b, 0);
    digitalWrite(e, 0);
    digitalWrite(d, 0);
    digitalWrite(c, 0);
  }
}

void loop()
{
  int i, n;
  for (i = 0; i != 10; i++){
    display(i);
    for (n = 0; n != 1; n++){
      digitalWrite(dp, 1);
      delay(500);
      digitalWrite(dp,0);
      delay(500);
    }
    }
  }
