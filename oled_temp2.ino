#include <max6675.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 OLED display connected to I2C (SDA, SCL pins)
#define OLED_RESET 16 // Reset pin # (or -1 if sharing Arduino reset pin)

TwoWire twi = TwoWire(1); // our own TwoWire instance on bus 1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &twi, OLED_RESET);
 
int thermoDO = 19; //called SO on the max6675
int thermoCS = 23; //called CS on the max6675
int thermoCLK = 18; //called SCK on the max6675

int thermoCS2 = 5;

bool unit_F = false; //true = °F - false = °C
 
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
MAX6675 thermocouple2(thermoCLK, thermoCS2, thermoDO); 

void setup() {
  Serial.begin(115200);
  Serial.println("MAX6675 test");

  twi.begin(4,15);  // Needs to come before display.begin is used
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    // for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("start");
  display.println("display..");
  display.display();

  delay(500);
}

void Display_WRITE(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("ET ");
  if (unit_F) {
    display.println(thermocouple.readFahrenheit());
    display.print("BT ");
    display.println(thermocouple2.readFahrenheit());
    }
  else if (!unit_F) {
    display.println(thermocouple.readCelsius());
    display.print("BT ");
    display.println(thermocouple2.readCelsius());
  }
  //display.println("Message");
  display.display();
}

//Send Data
void Command_WRITE(){
    Serial.print("0.00,");
    if (unit_F) {
        Serial.print(thermocouple.readFahrenheit());
        Serial.print(",");
        Serial.print(thermocouple2.readFahrenheit());
    }
    else if (!unit_F) {
        Serial.print(thermocouple.readCelsius());
        Serial.print(",");
        Serial.print(thermocouple2.readCelsius());
    }
    Serial.println(",0.00,0.00");
}

//Parsing Serial Commands
void handleSerialCommand(){   

   if (Serial.available()>0){
        String msg = Serial.readStringUntil('\n');

        if (msg.indexOf("CHAN;")== 0){  //Ignore this Setting
            Serial.print("#OK");
        }
        else if (msg.indexOf("UNITS;")== 0){

            if (msg.substring(6,7)=="F"){   //Change to Farenheit
                unit_F = true;
                Serial.println("#OK Farenheit");
            }
            else if (msg.substring(6,7)=="C"){  //Change to Celsius
                unit_F = false;
                Serial.println("#OK Celsius");
            }

        }
        else if (msg.indexOf("READ")==0){   //Send Temps
           Command_WRITE();

       }
   }

}


void loop()
{

    handleSerialCommand();
 
    Display_WRITE();

    delay(500);
}
