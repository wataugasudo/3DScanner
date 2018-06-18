#include "src/LiquidCrystal/src/LiquidCrystal.h"
#include "src/LiquidMenu/src/LiquidMenu.h"
#include "src/TimerOne/TimerOne.h"
#include "src/ClickEncoder/ClickEncoder.h"
#include "Routines.h"
#include "Configuration.h"

#ifndef DEMO_MODE // for normal mode

// ClickEncoder defs
ClickEncoder *encoder;
int16_t last, value;
boolean oneFocused;
void timerIsr() {
    encoder->service();
}

// Init display w/ interface pin #s
// (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
// Welcome Screen
LiquidLine welcome_line1(0, 0, SCANNER_NAME);
LiquidLine welcome_line2(8, 1, "Press ->");
LiquidScreen welcome_screen(welcome_line1, welcome_line2);
// Run Screen
LiquidLine scan_line(1, 0, "Scan to Serial");
LiquidLine home_line(1, 1, "Home Axes");
LiquidScreen run_screen(scan_line, home_line);
// Full Menu
LiquidMenu menu(lcd, welcome_screen, run_screen);
// Right arrow LCD char for focus
byte rightArrow[8] = {
	0b01000,
	0b01100,
	0b00110,
	0b00011,
	0b00110,
	0b01100,
	0b01000,
	0b00000
};

Routines routines;

//////////

void scan() {
    Serial.println("Scanning");
    routines.setLEDs(false, true, false);
}

void home() {
    Serial.println("Homing");
    routines.setLEDs(true, false, false);
}

//////////

void setup() {
    // ClickEncoder setup
    encoder = new ClickEncoder(ENC_CLK, ENC_DT, ENC_SW, ENC_STEPS_PER_NOTCH);
    encoder->setAccelerationEnabled(false);
    Timer1.initialize(1000);
    Timer1.attachInterrupt(timerIsr);
    last = 0;

    // Display welcome screen until click => run screen
    lcd.begin(16, 2);
    menu.update();
    while (encoder->getButton() != ClickEncoder::Clicked) {
        delay(10);
    }
    menu.next_screen();
    menu.set_focusPosition(Position::LEFT);
    menu.set_focusSymbol(Position::LEFT, rightArrow);
    oneFocused = true;

    // Attach scanner routines to run screen lines
    scan_line.attach_function(1, scan);
    home_line.attach_function(1, home);

    Serial.begin(BAUD_RATE); // begin serial comms
    menu.switch_focus(); // align focus highlight w/ menu
}

void loop() {
    // ClickEncoder Handler (scroll w/ turn & select w/ click)
    value += encoder->getValue();
    if (value != last) {
        if (value < last && !oneFocused) {
            menu.switch_focus(false);
            oneFocused = !oneFocused;
        } else if (value > last && oneFocused) {
            menu.switch_focus();
            oneFocused = !oneFocused;
        }
        last = value;
    }
    if (encoder->getButton() == ClickEncoder::Clicked) {
        menu.call_function(1);
    }
}

#else // for demo mode

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
Routines routines;

void setup() {
    lcd.begin(16, 2);
    lcd.noCursor();
}

void loop() {
    lcd.setCursor(0, 0);
    lcd.print("3D Scanner Demo");
    routines.setLEDs(true, false, false);
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("Homing...");
    routines.home();
    lcd.setCursor(0, 0);
    while (routines.getZ() <= Z_MAX_UNITS) {
        lcd.clear();
        lcd.print("Scanning (DEMO)");
        lcd.setCursor(0, 1);
        lcd.print("H:");
        lcd.print(routines.readH());
        lcd.print(" V:");
        lcd.print(routines.readV());
        routines.step();
    }
    lcd.setCursor(0, 1);
    lcd.print("Scan Complete");
    routines.setLEDs(false, false, true);
    delay(3000);
}

#endif
