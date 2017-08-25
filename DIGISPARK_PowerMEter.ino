/* ATtiny85 as an I2C Master   Ex2        BroHogan                           1/21/11
 * Modified for Digistump - Digispark LCD Shield by Erik Kettenburg 11/2012
 * SETUP:
 * ATtiny Pin 1 = (RESET) N/U                      ATtiny Pin 2 = (D3) N/U
 * ATtiny Pin 3 = (D4) to LED1                     ATtiny Pin 4 = GND
 * ATtiny Pin 5 = SDA on DS1621  & GPIO            ATtiny Pin 6 = (D1) to LED2
 * ATtiny Pin 7 = SCK on DS1621  & GPIO            ATtiny Pin 8 = VCC (2.7-5.5V)
 * NOTE! - It's very important to use pullups on the SDA & SCL lines!
 * PCA8574A GPIO was used wired per instructions in "info" folder in the LiquidCrystal_I2C lib.
 * This ex assumes A0-A2 are set HIGH for an addeess of 0x3F
 * LiquidCrystal_I2C lib was modified for ATtiny - on Playground with TinyWireM lib.
 * TinyWireM USAGE & CREDITS: - see TinyWireM.h
 */

//#define DEBUG
#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI - comment this out to use with standard arduinos
#include <LiquidCrystal_I2C.h>          // for LCD w/ GPIO MODIFIED for the ATtiny85
unsigned long voltage = 0;
unsigned long current = 0;
unsigned long power = 0;
int front = 0;
int back = 0;


#define GPIO_ADDR     0x27             // (PCA8574A A0-A2 @5V) typ. A0-A3 Gnd 0x20 / 0x38 for A - 0x27 is the address of the Digispark LCD modules.


LiquidCrystal_I2C lcd(GPIO_ADDR,16,2);  // set address & 16 chars / 2 lines


void setup(){
  TinyWireM.begin();                    // initialize I2C lib - comment this out to use with standard arduinos
  lcd.init();                           // initialize the lcd 
  lcd.backlight();                      // Print a message to the LCD.
  lcd.print("   PSUMON V1.0   ");
  delay(1000);
  lcd.clear();
}


void loop(){
    lcd.setCursor(0,0);
  
  voltage = analogRead(2);
  current = analogRead(0);
  //voltage = 900;
  //current = 1;
  voltage =2762*voltage; //0.0152717 * 1,000,000
  front = voltage/100000;
  back = (voltage-((voltage/100000)*100000))/1000;

  lcd.print(front);
  lcd.print(".");
  lcd.print(back);
  lcd.print("V");
  
  if (front >= 10) {
   lcd.print("   ");
  }
  else {
   lcd.print("    ");
  }  
  
  current = 2539*current;
  front = current/100000;
  back = (current-((current/100000)*100000))/1000;
  lcd.print(front);
  lcd.print(".");
  lcd.print(back);
  lcd.print("A  ");
  
  
  lcd.setCursor(0,1);
  
  power = (voltage/1000)*(current/1000);
  front = power/10000;
  back = (power-((power/10000)*10000))/1000;
  lcd.print(front);
  lcd.print(".");
  lcd.print(back);
  lcd.print("W  ");
  delay(500);
}

