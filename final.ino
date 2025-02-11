#include "arduinoFFT.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,10,9,8,7);//RS, E, D4 - D7

#define SAMPLES 128         //Must be a power of 2
#define SAMPLING_FREQUENCY 1000 //Hz, must be less than 10000 due to ADC


#define TOO_LOW 3
#define PERFECT 4
#define TOO_HIGH 5

 
unsigned int sampling_period_us;
 
void setup() {
  
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));

    pinMode(TOO_LOW, OUTPUT);
    pinMode(PERFECT, OUTPUT);
    pinMode(TOO_HIGH, OUTPUT);
    Serial.begin(9600);
    lcd.begin(16,2);
}
 
void loop() {
    DisplayNoteAndBar(FindDominantFrequency());
}

double FindDominantFrequency(){
    double vReal[SAMPLES];
    double vImag[SAMPLES];
    unsigned long microseconds;
    for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();    //Overflows after around 70 minutes!
        vReal[i] = analogRead(0);
        vImag[i] = 0;
        while(micros() < (microseconds + sampling_period_us));
    }
 
    /*FFT*/
    arduinoFFT FFT = arduinoFFT();
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    
    peak = peak * 0.990;
    return peak;
}


void DisplayNoteAndBar(double frequency){

  int ArrayWithNoteAndBarWidth[2];
  DetectClosestNote(frequency, ArrayWithNoteAndBarWidth);
  NoteNumberToString(ArrayWithNoteAndBarWidth[0]);
  Serial.println(frequency);

    if(ArrayWithNoteAndBarWidth[1] < 14){
      lcd.setCursor(0,1);
      lcd.print("Mai sus!");
      analogWrite(TOO_LOW, map(ArrayWithNoteAndBarWidth[1], 0, 16, 255, 0));
      digitalWrite(PERFECT, LOW);
      digitalWrite(TOO_HIGH, LOW);
    }else if(ArrayWithNoteAndBarWidth[1] > 18){
      lcd.setCursor(0,1);
      lcd.print("Mai jos!");
      analogWrite(TOO_HIGH, map(ArrayWithNoteAndBarWidth[1], 16, 32, 0, 255));
      digitalWrite(PERFECT, LOW);
      digitalWrite(TOO_LOW, LOW);
    }else{
      lcd.setCursor(0,1);
      lcd.print("PERFECT!");
      digitalWrite(PERFECT, HIGH);
      digitalWrite(TOO_LOW, LOW);
      digitalWrite(TOO_HIGH, LOW);
    }

}


int* DetectClosestNote(double frequency, int *arr){
  if(InRange(frequency, 62, 102)){
    arr[0] = 6;
    arr[1] = map(frequency, 62, 102, 1, 32);
  }else if(InRange(frequency, 100, 120)){
    arr[0] = 5;
    int value = map(frequency, 100, 120, 1, 32);
    Serial.print(value);
    arr[1] = value;
  }else if(InRange(frequency, 120, 165)){
    arr[0] = 4;
    arr[1] =  map(frequency, 127, 167, 1, 32);
  }else if(InRange(frequency, 165, 210)){
    arr[0] = 3;
    arr[1] = map(frequency, 176, 216, 1, 32);
  }else if(InRange(frequency, 210, 290)){
    arr[0] = 2;
    arr[1] = map(frequency, 217, 277, 1, 32);
  }else if(InRange(frequency, 290, 380)){
    arr[0] = 1;
    arr[1] = map(frequency, 290, 370, 1, 32);
  }
}

  bool InRange(double frequency, int low_limit, int high_limit){
    if(frequency < high_limit && frequency > low_limit){
      return true;
    }else{
      return false;
    }
  }


  char NoteNumberToString(int note_number){
  
    switch(note_number){
  case 1:
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Mi 2");
    return 'E';
  break;
  case 2:
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Si");
    return 'B';
  break;
  case 3:
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Sol");
    return 'G';
  break;
  case 4:
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Re");
    return 'D';
  break;
  case 5:
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("La");
    return 'A';
  break;
  case 6:
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Mi 1");
    return 'e';
  break;
}
}
