int m_l_f = 9;
int m_l_b = 10;

int m_r_b = 6;
int m_r_f = 5;

void setup() {
  // put your setup code here, to run once:

   pinMode(m_r_f, OUTPUT);
  pinMode(m_r_b, OUTPUT);
  pinMode(m_l_f, OUTPUT);
  pinMode(m_l_b, OUTPUT);

  analogWrite(m_l_b, 0);
  analogWrite(m_r_b, 0);
  analogWrite(m_l_f, 0);
  analogWrite(m_r_f, 0);


  

}

void loop() {
  
//on
analogWrite(m_r_f, 200);
analogWrite(m_l_f, 175);
delay(17);
analogWrite(m_r_f, 0);
analogWrite(m_l_f, 0);
delay(20);

}
