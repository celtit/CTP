#include <Arduino.h>
#include <U8g2lib.h>

// instances de Classes
U8G2_SSD1306_128X64_NONAME_F_HW_I2C afficheur(U8G2_R2,      /* orientation */
                                              SCL,          /* clock=*/
                                              SDA,          /* data=*/
                                              U8X8_PIN_NONE /* reset=*/
);

void initAfficheur()
{
  Serial.begin(115200);
  afficheur.begin();
  afficheur.setFont(u8g2_font_unifont_t_symbols);
  afficheur.setFontDirection(0);
  afficheur.setDrawColor(1);

  afficheur.clearBuffer();
  afficheur.setCursor(30, 40);
  afficheur.print("CTP IE2");
  afficheur.drawPixel(10,20);
  afficheur.sendBuffer();

  analogReadResolution(12);
  pinMode(D6,OUTPUT);

}

void setup()
{

  initAfficheur();
  


}

void loop()
{

  uint32_t static V;
  V = analogRead(A2);
  Serial.println(V/1240);

  if (V >=  2481)
  {
    digitalWrite(D6, HIGH);
  }
  else
  {
    digitalWrite(D6,LOW);
  }
  

}
