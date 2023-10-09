#include "Keyboard.h"
#include <SD.h>
#include <SPI.h>

File myFile;

int pinCS = 10;
int runPin = 3;
int injectionModePin = 4;
String urlSouce = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";
String editedUrl = "";

void setup() 
{
  delay(10000);
  Serial1.begin(9600);
  Serial.begin(9600);

  pinMode(pinCS, OUTPUT);
  pinMode(runPin, INPUT_PULLUP);
  pinMode(injectionModePin, INPUT_PULLUP);

  if (SD.begin())
    Serial.println("SD card is ready to use.");
    else
    Serial.println("SD card initialization failed");
}

void loop() 
{
  if(digitalRead(injectionModePin) == HIGH)
  {    
    if(digitalRead(runPin) == HIGH)
    {
      if(editedUrl != "")
      {
        urlSouce = editedUrl;
        editedUrl = "";
      }
      Keyboard.begin();
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      Keyboard.release(KEY_LEFT_GUI);
      Keyboard.release('r');
      delay(200);
      Keyboard.print(urlSouce);
      Keyboard.press(224);
      Keyboard.release(224);

      Keyboard.releaseAll();
      Keyboard.end();
    }
  }
  else
  {
    if(digitalRead(runPin) == HIGH)
    {
      myFile = SD.open("Macro.txt");
      if(myFile)
      {
        String Macro;
        while (myFile.available())
        {
          Macro += (char)myFile.read();
          if(Macro.endsWith("\n"))
          {
            if(Macro.startsWith("KD"))
            {
              Keyboard.press(Macro[3]);
            }
            else if(Macro.startsWith("KU"))
            {
              Keyboard.release(Macro[3]);
            }
            else if(Macro.startsWith("Dl"))
            {
              Macro.remove(0,3);
              Macro.remove(Macro.length()-2 ,2);
              delay(Macro.toInt());
            }
            else if(Macro.startsWith("Pr"))
            {
              Macro.remove(0,3);
              Macro.remove(Macro.length()-2 ,2);
              Keyboard.print(Macro);
            }
            Macro = "";
          }
        }
      }
      myFile.close();
      delay(100);
    }
  }
  
  if(Serial1.available() > 0 && digitalRead(runPin) == LOW)
  {
    editedUrl += (char)Serial1.read();
    Serial.println(editedUrl);
  }

}
