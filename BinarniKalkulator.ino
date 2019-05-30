int gumb1 = 2;
int gumb2 = 3;
int gumb3 = 13;
int gumb4 = 4;
int pritiski=1;
long time = 0;
long debounce = 100;
const byte ledice = 8;
int stanje;
int vrednost=0;
int rezultat=0;
byte pini[] = {5, 6, 7, 8, 9, 10, 11, 12};
String presledek="   ";
String presledek1=" ";

void setup() 
{
  Serial.begin(9600);
  pinMode(gumb1,INPUT);
  pinMode(gumb2,INPUT);
  pinMode(gumb3,INPUT);
  pinMode(gumb4,INPUT);
  for(int i = 0; i < ledice; i++) 
  {
    pinMode(pini[i], OUTPUT);
  }
}

void loop() 
{
  
  String binarnaSt = String(pritiski,BIN);
  int dolzinaBin = binarnaSt.length();
  if(digitalRead(gumb1)==HIGH)
  {
    if(pritiski <=255)
    {
      for(int i = 0, x=1; i < dolzinaBin; i++, x+=2)
      {
        if(binarnaSt[i] == '0') stanje = LOW;
        if(binarnaSt[i] == '1') stanje = HIGH;
        digitalWrite(pini[i] + dolzinaBin - x, stanje);
        
      }
      pritiski++;
        Serial.print(pritiski-1);
        Serial.print(presledek1);
        delay(250);  
    }
  }
  if(digitalRead(gumb4)==HIGH)
  {
      for(int a=0; a<ledice;a++)
        {
        digitalWrite(pini[a],LOW);
        }
        delay(100);
        vrednost=pritiski -1;
        Serial.print(presledek);
        Serial.print(vrednost);
        Serial.print(presledek);
        delay(500);
        pritiski=1; 
  }

  if(digitalRead(gumb3)==HIGH)
  {                    
      delay(300);
      for(int a=0; a<ledice;a++)
        {
        digitalWrite(pini[a],LOW);
        }
        delay(100);
        rezultat=vrednost+pritiski-1;
        if(rezultat>255){
          Serial.print(" Napaka ");
           for(int a=0; a<ledice;a++)
        {
        digitalWrite(pini[a],HIGH);
        delay(100);
        }
        delay(100);
         for(int a=0; a<ledice;a++)
        {
        digitalWrite(pini[a],LOW);
        delay(100);
        }
        delay(100);
        }
        else{
        Serial.print(presledek);
        Serial.print(" + "); 
        Serial.print(pritiski-1); 
        Serial.print(" = "); 
        Serial.print(presledek);
        Serial.print(rezultat);
        
        String binRezultat = String(rezultat, BIN);
        int binRezLength = binRezultat.length();
        Serial.print(presledek);
        Serial.print(binRezultat);
        for(int i = 0, b = 1; i < binRezLength; i++, b+=2) 
        { 
        if(binRezultat[i] == '0') stanje = LOW;
        if(binRezultat[i] == '1') stanje = HIGH;
        digitalWrite(pini[i] + binRezLength - b, stanje);
        }
        } 
  }
  
  if(digitalRead(gumb2)==HIGH)
  {
      delay(300);
      for(int a=0; a<ledice;a++)
        {
        digitalWrite(pini[a],LOW);
        }
        delay(100);
        rezultat=vrednost-pritiski+1;
        if(rezultat<0){
          Serial.print(" Napaka ");
           for(int a=0; a<ledice;a++)
        {
        digitalWrite(pini[a],HIGH);
        delay(100);
        }
        delay(100);
         for(int a=0; a<ledice;a++)
        {
        digitalWrite(pini[a],LOW);
        delay(100);
        }
        delay(100);
        }
        else{
        Serial.print(presledek);
        Serial.print(" - "); 
        Serial.print(pritiski-1); 
        Serial.print(" = "); 
        Serial.print(presledek);
        Serial.print(rezultat);
         
        String binRezultat = String(rezultat, BIN);
        int binRezLength = binRezultat.length(); 
        Serial.print(presledek);
        Serial.print(binRezultat);
        for(int i = 0, b = 1; i < binRezLength; i++, b+=2) 
        { 
        if(binRezultat[i] == '0') stanje = LOW;
        if(binRezultat[i] == '1') stanje = HIGH;
        digitalWrite(pini[i] + binRezLength - b, stanje);
        }
        }
   }
  
 
}


