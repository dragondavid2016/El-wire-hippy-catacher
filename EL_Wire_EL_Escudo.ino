/* 
   v1.7 -- re-wrote for arbitrary on & off time per channel.  Starts with
           off time.
           6/25/2014, D. Kent

   v1.6 -- re-wrote for staggered lighting of each channel.  Each channel
           on for 2/3 of OFF_TIME (ON_TIME not used).  The inverter seems
           to like this load better and doesn't switch to blink mode.
           6/25/2014, D. Kent

   v1.5 -- Interrupt driven. Interrupt routine tested and working properly.
           6/24/2014, D. Kent
*/
//                                                                                                                                                                                                                                         #include <EL_Escudo.h>
//The EL_Escudo library uses letters A-H to reference each EL string.
//Each EL string output has a corresponding label on the EL Escudo shield.

#define ON_TIME 500   //500 equals 8msec and is minimum stable value in my testing
#define OFF_TIME 31 //166 equals 8msec and is minimum stable value in my testing

byte channel_A = 2, channel_B = 5, channel_C = 4; 

byte channel_A_on = 14;  // time in msec (values that work: 3, 7, 14 use same for off time)
byte channel_B_on = 7;
byte channel_C_on = 7;
byte channel_A_off = 14;
byte channel_B_off = 14;
byte channel_C_off = 7;
byte countA = 1;
byte countB = channel_A_off;
byte countC = 1;

void setup()                    // run once, when the sketch starts
{ // turn all channels off
  pinMode(channel_A, OUTPUT);
  pinMode(channel_B, OUTPUT);
  pinMode(channel_C, OUTPUT);

  digitalWrite(channel_A, LOW); 
  digitalWrite(channel_B, LOW); 
  digitalWrite(channel_C, LOW); 

  // Power ON test of all 3 channels
  digitalWrite(channel_A, HIGH); 
  delay(500);
  digitalWrite(channel_B, HIGH); 
  delay(500);
  digitalWrite(channel_C, HIGH); 
  delay(500);
  digitalWrite(channel_A, LOW);   // this is important to prevent inverted waveform
  digitalWrite(channel_B, LOW);  // this is important to prevent inverted waveform 
  digitalWrite(channel_C, LOW);  // this is important to prevent inverted waveform
  
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 63;               // compare match register 63/(16MHz/256) = 1.008msec
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts

}

//-------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
    noInterrupts();           // disable all interrupts

//    if(OCR1A == OFF_TIME) // was OFF

    if (countA > channel_A_off && countA <= (channel_A_off + channel_A_on) ) 
    {
        digitalWrite(channel_A, HIGH);
    } else
    {
        digitalWrite(channel_A, LOW);
    }
    if (countA == (channel_A_off + channel_A_on) ) countA = 1; else countA++;

//    if (countB > channel_B_off && countA <= (channel_B_off + channel_B_on) ) 
//    {
//        digitalWrite(channel_B, HIGH);
//    } else
//    {
//        digitalWrite(channel_B, LOW);
//    }
//    if (countB == (channel_B_off + channel_B_on) ) countB = channel_A_off; else countB++;
//    
//    if (countC > channel_C_off && countC <= (channel_C_off + channel_C_on) ) 
//    {
//        digitalWrite(channel_C, HIGH);
//    } else
//    {
//        digitalWrite(channel_C, LOW);
//    }
//    if (countC == (channel_C_off + channel_C_on) ) countC = 1; else countC++;

//    {
//      if (toggle == 0) 
//      {
//        digitalWrite(channel_A, digitalRead(channel_A) ^ 1);
//        //digitalWrite(channel_C, digitalRead(channel_C) ^ 1);   
//        digitalWrite(channel_B, digitalRead(channel_B) ^ 1);   
//      }
//        
//      if (toggle == 1) 
//      {
//        digitalWrite(channel_B, digitalRead(channel_B) ^ 1);   
//        //digitalWrite(channel_A, digitalRead(channel_A) ^ 1);
//        digitalWrite(channel_C, digitalRead(channel_C) ^ 1);
//      }
//
//      if (toggle == 2) 
//      {
//        digitalWrite(channel_C, digitalRead(channel_C) ^ 1);
//        //digitalWrite(channel_B, digitalRead(channel_B) ^ 1);   
//        digitalWrite(channel_A, digitalRead(channel_A) ^ 1);
//      }
//      //if (toggle == 1) OCR1A = OFF_TIME; else OCR1A = ON_TIME;
//      if (toggle < 2) toggle++; else toggle = 0;

//      digitalWrite(channel_B, HIGH);   
//      digitalWrite(channel_C, HIGH);   
//      OCR1A = ON_TIME;            // set ON time
//    } else  // was ON
//    {
//      digitalWrite(channel_A, LOW);   
//      digitalWrite(channel_B, LOW);   
//      digitalWrite(channel_C, LOW);   
//      OCR1A = OFF_TIME;            // set OFF time
    interrupts();             // enable all interrupts
}
//--------------------------------------------------------------------------

void loop()                     // run over and over again
{
//  digitalWrite(channel_A, HIGH); 
//  digitalWrite(channel_B, HIGH); 
//  digitalWrite(channel_C, HIGH); 
//  delay(wait_ON);
//  
//  digitalWrite(channel_C, LOW);
//  digitalWrite(channel_A, LOW);
//  digitalWrite(channel_B, LOW);
//  delay(wait_OFF);
}
