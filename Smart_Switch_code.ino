#include<EEPROMex.h>
int t,i=0;
float Vmax=0.0,Imax=0.0;
float current=0,voltage=0;
const int voltagePin = A2;
const int currentPin = A0;
int samples=0;
int j=0;
const int adc_zero = 515;  
float a,b,c,A=0,B=0,C=0;
float v,iv;
int baseAdd=0;
int k=0;
//float Ii[1000];

void setup()
{
  Serial.begin(115200);
  pinMode(voltagePin,INPUT);
  pinMode(currentPin,INPUT); 
}
void loop()
{t=millis();
  if(k<80)
  {  
    voltage=analogRead(voltagePin);
    voltage = voltage/3.41;
    if(voltage>Vmax)
     Vmax=voltage;
     
    if(current>Imax)
     Imax=current;
   
    //Serial.println(voltage); 
    EEPROM.writeFloat(baseAdd+(k*4),voltage);
    current = analogRead(currentPin); 
    current=(current-adc_zero)*27.03/1023;
    //Ii[j]=current;
    Serial.println(k);  
    k = k+1;
    //Serial.println(current);              
    Serial.println(k); //Serial.println(++samples);
    EEPROM.writeFloat((baseAdd)+(k*4),current);  
    k++;    
    a=current*voltage;
    A=A+a;                                                 //VI- values 

    b=voltage*voltage;
    B=B+b;                                               //V-rms values

    c=current*current;
    C=C+c;                                                //I-rms values 
      
    i++;         
    j++;// printing the values on serial monitor
 }
     if(k==80)
      { printVI(i);
        Serial.print("No of samples: ");
     Serial.println(i);
     Serial.print("Maximum amount of voltage: ");
     Serial.print(Vmax);
     Serial.print("Maximum amount of current: ");
     Serial.print(Imax);
     B=sqrt(B/i);
     C=sqrt(C/i);
     Serial.print("Power Factor: ");
     Serial.println(A/(B*C));  
     k++;   
     }
}
void printVI(int sample){
    Serial.println("VOLTAGES:");
    for(int i=0;i<sample;i++){
       Serial.println(EEPROM.readFloat(baseAdd+(i*8)));
    }
    
    Serial.println("CURRENTS:");
    for(int i=0;i<sample;i++){
       Serial.println(EEPROM.readFloat(baseAdd+4+(i*8)));
    }
  }

