#include <Arduino.h>

#define DCSBIOS_DEFAULT_SERIAL // Use DCSBIOS_DEFAULT_SERIAL if IRQ does not work.
#define USE_MATRIX_SWITCHES
#include <DcsBios.h>

#define BACKLIGHT_LED_PIN  5
#define MASTER_CAUTION_LED_PIN 6
#define DEBUG_HOLD_DURATION 3000 // 3 seconds hold duration
#define DEBUG_ACTIVATE_BUTTON_ROW 0 // Row for the debug activation button
#define DEBUG_ACTIVATE_BUTTON_COL 1 // Column for the debug activation button

volatile unsigned char in_mat[3][13] = {0};
byte rowPins[3] = {2, 3, 4};
byte colPins[13] = {7, 8, 9, 10, 16, 14, 15, 18, 19, 20, 21, 1, 0};
int numRows = sizeof(rowPins) / sizeof(rowPins[0]);
int numCols = sizeof(colPins) / sizeof(colPins[0]);

DcsBios::MatActionButtonSet ufc1("UFC_1", &in_mat[0][1], LOW);
DcsBios::MatActionButtonSet ufc2("UFC_2", &in_mat[0][2], LOW);
DcsBios::MatActionButtonSet ufc3("UFC_3", &in_mat[0][3], LOW);
DcsBios::MatActionButtonSet ufcHack("UFC_HACK", &in_mat[0][4], LOW);
DcsBios::MatActionButtonSet ufcFunc("UFC_FUNC", &in_mat[0][5], LOW);
DcsBios::MatActionButtonSet ufcEnt("UFC_ENT", &in_mat[0][6], LOW);
DcsBios::MatActionButtonSet ufcMasterCaution("UFC_MASTER_CAUTION", &in_mat[0][8], LOW);

DcsBios::Matrix3PosState ufcSteer("UFC_STEER", &in_mat[1][0], &in_mat[2][0], LOW);
DcsBios::Matrix3PosState ufcData("UFC_DATA", &in_mat[0][10], &in_mat[1][10], LOW);
DcsBios::Matrix3PosState ufcSel("UFC_SEL", &in_mat[0][11], &in_mat[1][11], LOW);
DcsBios::Matrix3PosState ufcDepr("UFC_DEPR", &in_mat[1][12], &in_mat[2][12], LOW);
DcsBios::Matrix3PosState ufcInten("UFC_INTEN", &in_mat[2][11], &in_mat[2][10], LOW);

DcsBios::MatActionButtonSet ufc4("UFC_4", &in_mat[1][1], LOW);
DcsBios::MatActionButtonSet ufc5("UFC_5", &in_mat[1][2], LOW);
DcsBios::MatActionButtonSet ufc6("UFC_6", &in_mat[1][3], LOW);
DcsBios::MatActionButtonSet ufc10("UFC_10", &in_mat[1][4], LOW);

DcsBios::MatActionButtonSet ufc7("UFC_7", &in_mat[2][1], LOW);
DcsBios::MatActionButtonSet ufc8("UFC_8", &in_mat[2][2], LOW);
DcsBios::MatActionButtonSet ufc9("UFC_9", &in_mat[2][3], LOW);

DcsBios::MatActionButtonSet ufcClr("UFC_CLR", &in_mat[2][5], LOW);
DcsBios::MatActionButtonSet ufcAltAlrt("UFC_ALT_ALRT", &in_mat[2][6], LOW);
DcsBios::MatActionButtonSet ufcCom1("UFC_COM1", &in_mat[1][7], LOW);
DcsBios::MatActionButtonSet ufcCom2("UFC_COM2", &in_mat[2][7], LOW);
DcsBios::MatActionButtonSet ufcComSec("UFC_COM_SEC", &in_mat[1][8], LOW);
DcsBios::MatActionButtonSet ufcEccm("UFC_ECCM", &in_mat[2][8], LOW);

DcsBios::MatActionButtonSet ufcIdm("UFC_IDM", &in_mat[2][9], LOW);
DcsBios::MatActionButtonSet ufcIff("UFC_IFF", &in_mat[1][9], LOW);
DcsBios::MatActionButtonSet ufcLtr("UFC_LTR", &in_mat[1][5], LOW);

DcsBios::MatActionButtonSet ufcMk("UFC_MK", &in_mat[1][6], LOW);
DcsBios::MatActionButtonSet ufcSpc("UFC_SPC", &in_mat[2][4], LOW);

DcsBios::LED masterCaution(0x1012, 0x0800, MASTER_CAUTION_LED_PIN);

bool debugMode = false;
unsigned long debugStartTime = 0;
bool debugStartPressed = false;
int backlightIntensity = 16;

void onIntConsoleLightBrightChange(unsigned int newValue) {
    int intensity = map(newValue, 0, 65535, 0, 180);
    backlightIntensity = intensity;
    analogWrite(BACKLIGHT_LED_PIN, intensity);

    if (debugMode) {
        Serial.print("Backlight from DCS-BIOS: ");
        Serial.println(intensity);
    }
}

DcsBios::IntegerBuffer intConsoleLightBuffer(0x1376, 0xffff, 0, onIntConsoleLightBrightChange);

void setup() {
    DcsBios::setup();
    Serial.begin(9600);

    pinMode(BACKLIGHT_LED_PIN, OUTPUT);
    pinMode(MASTER_CAUTION_LED_PIN, OUTPUT);
    analogWrite(BACKLIGHT_LED_PIN, backlightIntensity);

    for (int i = 0; i < numRows; i++) {
        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], HIGH);
    }
    for (int i = 0; i < numCols; i++) {
        pinMode(colPins[i], INPUT_PULLUP);
    }
}

void toggleDebugMode() {
    debugMode = !debugMode;
    Serial.print("Debug mode: ");
    Serial.println(debugMode ? "ON" : "OFF");

    if (debugMode) {
        for (int i = 0; i < 3; i++) {
            analogWrite(BACKLIGHT_LED_PIN, 255);
            delay(250);
            analogWrite(BACKLIGHT_LED_PIN, 0);
            delay(250);
        }
        analogWrite(BACKLIGHT_LED_PIN, backlightIntensity);
    }
}

void testMasterCaution() {
    static bool state = false;
    state = !state;
    analogWrite(MASTER_CAUTION_LED_PIN, state ? 255 : 0);
    Serial.println("Master Caution LED toggled");
}

// Modified Backlight Cycle Function
void testBacklightCycle() {
    static int direction = 1;
    if (in_mat[1][0] == LOW || in_mat[2][0] == LOW) {  // Adjust intensity only when these buttons are pressed
        backlightIntensity += direction * 5;

        if (backlightIntensity > 255) {
            backlightIntensity = 255;
        } else if (backlightIntensity < 0) {
            backlightIntensity = 0;
        }

        if (backlightIntensity == 255 || backlightIntensity == 0) {
            direction *= -1;
        }

        analogWrite(BACKLIGHT_LED_PIN, backlightIntensity);
        Serial.print("Adjusted backlight: ");
        Serial.println(backlightIntensity);
    }
}

void printButtonStates() {
    Serial.println("Button states:");
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            Serial.print(in_mat[row][col] == LOW ? "Pressed " : "Not pressed ");
        }
        Serial.println();
    }
}

void loop() {
    bool ufc1Pressed = in_mat[0][1] == LOW;
    bool ufc2Pressed = in_mat[0][2] == LOW;
    bool ufc3Pressed = in_mat[0][3] == LOW;

    if (ufc1Pressed && ufc2Pressed && ufc3Pressed) {
        if (!debugStartPressed) {
            debugStartPressed = true;
            debugStartTime = millis();
        } else if (millis() - debugStartTime >= DEBUG_HOLD_DURATION) {
            if (!debugMode) {
                toggleDebugMode();
            }
            debugStartPressed = false;
        }
    } else {
        debugStartPressed = false;
    }

    for (int row = 0; row < numRows; row++) {
        digitalWrite(rowPins[row], LOW);

        for (int col = 0; col < numCols; col++) {
            if (digitalRead(colPins[col]) == LOW) {
                in_mat[row][col] = LOW;

                if (debugMode) {
                    if (row == DEBUG_ACTIVATE_BUTTON_ROW && col == DEBUG_ACTIVATE_BUTTON_COL) {
                        testMasterCaution();
                        testBacklightCycle();
                        printButtonStates();
                    }
                    Serial.print("Button pressed at row ");
                    Serial.print(row);
                    Serial.print(", col ");
                    Serial.println(col);
                }
            } else {
                in_mat[row][col] = HIGH;
            }
        }
        digitalWrite(rowPins[row], HIGH);
    }

    if (debugMode) {
        static unsigned long lastBlinkTime = 0;
        if (millis() - lastBlinkTime >= 250) {
            lastBlinkTime = millis();
            digitalWrite(MASTER_CAUTION_LED_PIN, !digitalRead(MASTER_CAUTION_LED_PIN));
        }
    }

    DcsBios::loop();
}