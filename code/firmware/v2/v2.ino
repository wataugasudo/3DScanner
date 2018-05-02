#include <LiquidCrystal.h>
#include <LiquidMenu.h>
#include <TimerOne.h>
#include <ClickEncoder.h>

#define BAUD_RATE 9600

// Init display w/ interface pin #s
// (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(16, 17, 18, 19, 20, 21);

// ClickEncoder defs
ClickEncoder *encoder;
int16_t last, value;
boolean oneFocused;
void timerIsr() {
    encoder->service();
}

// Welcome Screen
LiquidLine welcome_line1(0, 0, "TTFS 3D Scanner");
LiquidLine welcome_line2(8, 1, "Press ->");
LiquidScreen welcome_screen(welcome_line1, welcome_line2);
// Run Screen
LiquidLine scan_line(1, 0, "Scan to Serial");
LiquidLine home_line(1, 1, "Home Axes");
LiquidScreen run_screen(scan_line, home_line);
// Full Menu
LiquidMenu menu(lcd, welcome_screen, run_screen);

byte rightArrow[8] = { // right arrow LCD char for focus
	0b01000,
	0b01100,
	0b00110,
	0b00011,
	0b00110,
	0b01100,
	0b01000,
	0b00000
};


////////////////////////////////////////
void scan() {
    // Serial.println("scanning");
}

void home() {
    // Serial.println("homing");
}
////////////////////////////////////////

void setup() {
    // ClickEncoder setup
    encoder = new ClickEncoder(A2, A1, A0, 4);
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
    // ClickEncoder Handler
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
