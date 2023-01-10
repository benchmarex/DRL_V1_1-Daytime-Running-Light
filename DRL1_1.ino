//#include  <Wire.h>
//#include <avr/wdt.h>


//TC74 address. 
//int address = 0x48;




const int pwm_halogen = 10; //pb2 (digital 10)
const int p_led = 5; //pd5 (digital 5)

const int msr_vin = 2; //pc2 (analog in 2)
const int p_postojowki = 1; //pc1 (analog in 1)
const int p_drogowe = 0; //pc0 (analog in0)
const int p_jumper=17;


float uref=1.1;  
float udiv=15.634; 

float postojowki=0.0;
float drogowe=0.0;
float vin=0.0;
//float temperature=0.0;

int duty;

//byte val = 0;




void setup() {

analogReference(INTERNAL);
pinMode(pwm_halogen, OUTPUT);
pinMode(p_led, OUTPUT);
pinMode(msr_vin, INPUT);
pinMode(p_postojowki, INPUT);
pinMode(p_drogowe, INPUT);
pinMode(p_jumper, INPUT);


analogWrite(pwm_halogen, 0);
//Wire.begin();



}

void loop() 
{
  
/////////////////////////////////////////////// uwaga w protypie napiecie rzczywiste jest zawyżone o 0,2V ustawion 12,1 a wylacza na 12,3

 
  u_msr();
 _blink(); //digitalWrite(p_led,HIGH);

 
  //if (vin>12.9 && vin<16 && postojowki<10 && drogowe<10 &&temperature<45)
  
  if (vin>13.3 && vin<15 && postojowki<5 && drogowe<10) //ZAŁĄCZENIE
  
 { 
 jumper();
 sw_halogen (duty);
  while (vin>12.4 && vin<15.5 && postojowki<11) //WYŁACZENIE 
 
 // while (vin>12.4 && vin<15.5 && postojowki<4)
  
 
 {
 
 u_msr();
  //_tc();
  delay(500);
 }
 
 analogWrite(pwm_halogen, 0);
 _blink();}
}


/*
void _tc(){
  
// Set TC74 for read
Wire.beginTransmission(address);
Wire.write(val);
Wire.endTransmission();
// Read from TC74
Wire.requestFrom(address, 1);
temperature=Wire.read();
return;
}
*/



void jumper()
{
duty=255;
 if (digitalRead(p_jumper) == 1)
duty=85; //duty=85;//(jeżeli założona zworka to wypełenie nie 30% tylko 100% dla lamp led


}



 void _blink()
 
 {
digitalWrite(p_led,HIGH);
delay(30);
digitalWrite(p_led,LOW);
delay(1000);
 }
//pomiar napięć

void u_msr()
{
//vin=analogRead(msr_vin)*uref/1024*udiv;
postojowki=analogRead(p_postojowki)*uref/1024*udiv;
drogowe=analogRead(p_drogowe)*uref/1024*udiv;
vin=analogRead(msr_vin)*uref/1024*udiv;
}
// załączenie/wyłączenie halogenu, podać wartość wypełniania duty

void sw_halogen (int duty)
{
 // zwarcie();
  
  
  
//miekki start halogenu
for (int fadeValue = 0 ; fadeValue <= duty; fadeValue += 1)
{    analogWrite(pwm_halogen, fadeValue);
     delay(20);}
    
}

/*
//funkcja sprawdza czy jest zwarcie jesli tak to nie wraca



void zwarcie()

{

digitalWrite(pwm_halogen,HIGH);
delay(5);

  
  
//  analogWrite(pwm_halogen, 1);
//delay(100);
u_msr(); 
 digitalWrite(pwm_halogen,LOW); 
 
 
while (drogowe<0.08)
{
digitalWrite(pwm_halogen,LOW); //analogWrite(pwm_halogen, 0);
delay(5000);
digitalWrite(pwm_halogen,HIGH); //analogWrite(pwm_halogen, 1);
//_blink();
delay(5);
u_msr();
digitalWrite(pwm_halogen,LOW);
digitalWrite(p_led,LOW);
//delay(300);
}
digitalWrite(pwm_halogen,LOW);//analogWrite(pwm_halogen, 0);
digitalWrite(p_led,LOW);
}
*/

//===========================================
//void software_Reset()
//{asm volatile ("jmp 0");}  
 
