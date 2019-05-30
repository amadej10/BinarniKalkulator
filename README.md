# Binarni Kalkulator 
**Projekt pri predmetu AIR na ŠCC-KER**   
**Datum: 28. 5. 2016**

Z mikrokrmilnikom sem izdelal osem bitno binarno računalo, ki zna seštevati in odštevati
števila med 0 in 256.


# Načrtovanje
Izdelavo sem začel z izbiro električnih delov, ki jih bom uporabil v vezju. Za mikrokrmilnik sem izbral Arduino Nano, ker je majhen in ima zadostno število nožic za to nalogo. Za prikaz števil sem izbral osem zelenih LED diod. Zaradi izhodne napetosti 5V na nožicah sem izbral še 300Ohmske upore, ki ščitijo LED diode pred previsoko napetostjo. Za vnos podatkov sem uporabil 4 tipke, ki so ravno tako potrebovale upore. Uporabil sem 150K Ohmske upore, da porabijo odvečno napetost. Nato sem iz izbranih delov narisal električno shemo.

![Shema](https://github.com/amadej10/BinarniKalkulator_Arduino/blob/master/shema_slika.jpg)

# Izdelava

## Vezje
Izdelavo sem začel s testiranjem električnih komponent na preiskuševalni plošči, ko sem ugotovil, da vsi elemnti pravilno delujejo sem pričel s spajkanjem električnih elementov na prototipno ploščo. Elemente sem spajkal tako kot sem si narisal na shemi. Med spajkanjem sem preverjal, da med povezavami ni kratkih stikov in skrbel, da je vezje urejeno. Po končanem spajkanju sem se lotil programiranja.

## Program
Na začetku programa sem definiral vse spremenljivke in vse vhodne in izhodne nožice.
```C++
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
```
Na razpolago sem imel štiri tipke. Odločil sem se, da bom eno tipko sprogramiral za izbiranje binarne številke. Gumb šteje število pritiskov in istočasno prikazuje to isto število binarno na osmih ledicah. Program za štetje pritiskov in prikazovanje:
```C++
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
```
Potem moramo izbrano število shraniti in resetirati zaslon, da lahko ponovno izberemo drugo število. To storimo s to kodo:
```C++
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
```
Ko je prvo število shranjeno in zaslon resetiran lahko ponovno izberemo število s prvim programom. Imamo dve števili s katerima lahko seštevamo ali odštevamo, ker pa število ne sme biti večje od 256 ali manjše od 0 sem programu dodal error animacijo, ki zavaruje program pred zrušitvijo. Programu sem dodal komentarje, da nam preko serijske komunikacije v konzoli izpisuje kaj počne. S tem sem lahko videl vrednosti spremenljivk in lažje ugotavljal vzroke napak, ki so se pojavljale med programiranjem. Program tipke za seštevanje:
```C++
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
```
Ta program sešteje shranjeno število pritiskov, ki smo jo shranili s prejšnjim programom in število novih pritiskov na tipko za izbiranje števila. Nato številko pretvori v binarno in jo prikaže na zaslonu. Program tipke za odštevanje:
```C++
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
```
Princip pri odštevanju je enak kot pri seštevanju le, le da tukaj od shranjenega števila pritiskov odštejemo število novih pritiskov na tipko za izbiranje števila. Število zopet pretvorimo v binarno število in ga prikažemo na zaslonu.

## Končan izdelek
![Izdelano](https://github.com/amadej10/BinarniKalkulator_Arduino/blob/master/ScreenSho.jpg)

# Viri
Arduino. (4. 6 2016). ARDUINO. Pridobljeno iz Reference: https://www.arduino.cc/en/Reference/HomePage

P.Marian. (4. 6 2016). ELECTRO SCHEMATICS. Pridobljeno iz ELECTRO SCHEMATICS: http://www.electroschematics.com/9809/arduino-8-bit-binary-led/

