#include <Arduino.h>
#include <U8g2lib.h>

// instances de Classes
U8G2_SSD1306_128X64_NONAME_F_HW_I2C afficheur(U8G2_R2,      /* orientation */
                                              SCL,          /* clock=*/
                                              SDA,          /* data=*/
                                              U8X8_PIN_NONE /* reset=*/
);

const uint32_t INTERVALLE = 100;

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
  afficheur.drawPixel(10, 20);
  afficheur.sendBuffer();

  analogReadResolution(12);
  pinMode(D6, OUTPUT);
  pinMode(D4, INPUT);
}

void setup()
{

  initAfficheur();
}

void loop()
{

  uint32_t static V;
  uint32_t static tempsActuel = 0;
  uint32_t static tempsEcoule = 0;
  uint32_t static tempsPrecedent = 0;
  uint32_t static cpt = 0;
  uint32_t static timerActuel = 0;
  uint32_t static timerEcoule = 0;
  uint32_t static timerPrecedent = 0;
  float timerNum;
  bool etatBouton;
  tempsActuel = millis();
  tempsEcoule = tempsActuel - tempsPrecedent;
  etatBouton = digitalRead(D4);
  

  if (tempsEcoule > INTERVALLE)
  {
    //Serial.println(etatBouton);
    if (etatBouton == 0)
    {
      cpt = cpt + 1;
      timerActuel = millis();
    }
    else
    {
      if (cpt != 0)
      {
        timerEcoule = timerActuel - timerPrecedent;
        timerNum = timerEcoule/1000.00;
        timerPrecedent = timerActuel;
        Serial.print("temps depuis le dernier appui : ");
        Serial.println(timerNum);
      }
    }

    tempsPrecedent = tempsActuel;
  }
  V = analogRead(A2);
  //Serial.println(V / 1240);

  if (V >= 2481)
  {
    digitalWrite(D6, HIGH);
  }
  else
  {
    digitalWrite(D6, LOW);
  }
}
