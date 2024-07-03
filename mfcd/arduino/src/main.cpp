#include <Arduino.h>

#define DCSBIOS_DEFAULT_SERIAL // Use DCSBIOS_DEFAULT_SERIAL if IRQ does not work.
#define USE_MATRIX_SWITCHES
#define MFCD_RIGHT
//#define MFCD_LEFT

#include <DcsBios.h>
#define COL_PIN_2 (2)
#define COL_PIN_3 (3)
#define COL_PIN_4 (4)
#define COL_PIN_5 (5)
#define COL_PIN_6 (6)
#define COL_PIN_7 (7)
#define COL_PIN_8 (8)

#define ROW_PIN_9  (9 )
#define ROW_PIN_10 (10)
#define ROW_PIN_11 (11)
#define ROW_PIN_12 (12)
#define ROW_PIN_13 (13)
#define ROW_PIN_A0 (14)
#define ROW_PIN_A1 (15)
#define ROW_PIN_A2 (16)
#define ROW_PIN_A3 (17)
#define ROW_PIN_A4 (18)
#define ROW_PIN_A5 (19)

volatile unsigned char in_mat[11][7] = {};
byte rowPins[11] = {ROW_PIN_9, ROW_PIN_10, ROW_PIN_11, ROW_PIN_12, ROW_PIN_13, ROW_PIN_A0, ROW_PIN_A1, ROW_PIN_A2,
                    ROW_PIN_A3, ROW_PIN_A4, ROW_PIN_A5};


byte colPins[7] = {COL_PIN_2, COL_PIN_3, COL_PIN_4, COL_PIN_5, COL_PIN_6, COL_PIN_7, COL_PIN_8};
int numRows = sizeof(rowPins) / sizeof(rowPins[0]);
int numCols = sizeof(colPins) / sizeof(colPins[0]);

#ifdef MFCD_LEFT
DcsBios::MatActionButtonSet lmfd1("LMFD_1", &in_mat[0][1], LOW);
DcsBios::MatActionButtonSet lmfd2("LMFD_2", &in_mat[0][2], LOW);
DcsBios::MatActionButtonSet lmfd3("LMFD_3", &in_mat[0][3], LOW);
DcsBios::MatActionButtonSet lmfd4("LMFD_4", &in_mat[0][4], LOW);
DcsBios::MatActionButtonSet lmfd5("LMFD_5", &in_mat[0][5], LOW);

DcsBios::MatActionButtonSet lmfd6("LMFD_6", &in_mat[3][6], LOW);
DcsBios::MatActionButtonSet lmfd7("LMFD_7", &in_mat[4][6], LOW);
DcsBios::MatActionButtonSet lmfd8("LMFD_8", &in_mat[5][6], LOW);
DcsBios::MatActionButtonSet lmfd9("LMFD_9", &in_mat[6][6], LOW);
DcsBios::MatActionButtonSet lmfd10("LMFD_10", &in_mat[7][6], LOW);

DcsBios::MatActionButtonSet lmfd11("LMFD_11", &in_mat[10][4], LOW);
DcsBios::MatActionButtonSet lmfd12("LMFD_12", &in_mat[10][3], LOW);
DcsBios::MatActionButtonSet lmfd13("LMFD_13", &in_mat[10][2], LOW);
DcsBios::MatActionButtonSet lmfd14("LMFD_14", &in_mat[10][1], LOW);
DcsBios::MatActionButtonSet lmfd15("LMFD_15", &in_mat[10][0], LOW);

DcsBios::MatActionButtonSet lmfd16("LMFD_16", &in_mat[7][0], LOW);
DcsBios::MatActionButtonSet lmfd17("LMFD_17", &in_mat[6][0], LOW);
DcsBios::MatActionButtonSet lmfd18("LMFD_18", &in_mat[5][0], LOW);
DcsBios::MatActionButtonSet lmfd19("LMFD_19", &in_mat[4][0], LOW);
DcsBios::MatActionButtonSet lmfd20("LMFD_20", &in_mat[3][0], LOW);

DcsBios::Matrix3PosState lmfdAdj("LMFD_ADJ", &in_mat[1][0], &in_mat[2][0], LOW);
DcsBios::Matrix3PosState lmfdCon("LMFD_CON", &in_mat[8][0], &in_mat[9][0], LOW);

DcsBios::Matrix3PosState lmfdDsp("LMFD_DSP", &in_mat[1][6], &in_mat[2][6], LOW);
DcsBios::Matrix3PosState lmfdBrt("LMFD_BRT", &in_mat[8][6], &in_mat[9][6], LOW);

DcsBios::Matrix3PosState lmfdSym("LMFD_SYM", &in_mat[10][6], &in_mat[10][5], LOW);

DcsBios::Matrix3PosState lmfdPwr("LMFD_PW", &in_mat[9][1], &in_mat[9][3], LOW);
#endif
#ifdef MFCD_RIGHT
DcsBios::MatActionButtonSet rmfd1("RMFD_1", &in_mat[0][1], LOW);
DcsBios::MatActionButtonSet rmfd2("RMFD_2", &in_mat[0][2], LOW);
DcsBios::MatActionButtonSet rmfd3("RMFD_3", &in_mat[0][3], LOW);
DcsBios::MatActionButtonSet rmfd4("RMFD_4", &in_mat[0][4], LOW);
DcsBios::MatActionButtonSet rmfd5("RMFD_5", &in_mat[0][5], LOW);

DcsBios::MatActionButtonSet rmfd6("RMFD_6", &in_mat[3][6], LOW);
DcsBios::MatActionButtonSet rmfd7("RMFD_7", &in_mat[4][6], LOW);
DcsBios::MatActionButtonSet rmfd8("RMFD_8", &in_mat[5][6], LOW);
DcsBios::MatActionButtonSet rmfd9("RMFD_9", &in_mat[6][6], LOW);
DcsBios::MatActionButtonSet rmfd10("RMFD_10", &in_mat[7][6], LOW);

DcsBios::MatActionButtonSet rmfd11("RMFD_11", &in_mat[10][4], LOW);
DcsBios::MatActionButtonSet rmfd12("RMFD_12", &in_mat[10][3], LOW);
DcsBios::MatActionButtonSet rmfd13("RMFD_13", &in_mat[10][2], LOW);
DcsBios::MatActionButtonSet rmfd14("RMFD_14", &in_mat[10][1], LOW);
DcsBios::MatActionButtonSet rmfd15("RMFD_15", &in_mat[10][0], LOW);

DcsBios::MatActionButtonSet rmfd16("RMFD_16", &in_mat[7][0], LOW);
DcsBios::MatActionButtonSet rmfd17("RMFD_17", &in_mat[6][0], LOW);
DcsBios::MatActionButtonSet rmfd18("RMFD_18", &in_mat[5][0], LOW);
DcsBios::MatActionButtonSet rmfd19("RMFD_19", &in_mat[4][0], LOW);
DcsBios::MatActionButtonSet rmfd20("RMFD_20", &in_mat[3][0], LOW);

DcsBios::Matrix3PosState rmfdAdj("RMFD_ADJ", &in_mat[1][0], &in_mat[2][0], LOW);
DcsBios::Matrix3PosState rmfdCon("RMFD_CON", &in_mat[8][0], &in_mat[9][0], LOW);

DcsBios::Matrix3PosState rmfdDsp("RMFD_DSP", &in_mat[1][6], &in_mat[2][6], LOW);
DcsBios::Matrix3PosState rmfdBrt("RMFD_BRT", &in_mat[8][6], &in_mat[9][6], LOW);

DcsBios::Matrix3PosState rmfdSym("RMFD_SYM", &in_mat[10][6], &in_mat[10][5], LOW);

DcsBios::Matrix3PosState rmfdPwr("RMFD_PW", &in_mat[9][1], &in_mat[9][3], LOW);
#endif

bool debugMode = false;


void setup() {
    DcsBios::setup();
    if (debugMode) {
        Serial.begin(9600);
        Serial.println("");
        Serial.println("[A10C MFCD FIRMWARE BY w3z315]");
        Serial.println("[VERSION 0.0.1]");
        Serial.println("");
    }

    for (int i = 0; i < numRows; i++) {
        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], HIGH);
    }
    for (int i = 0; i < numCols; i++) {
        pinMode(colPins[i], INPUT_PULLUP);
    }
}


void loop() {
    for (int row = 0; row < numRows; row++) {
        digitalWrite(rowPins[row], LOW);

        for (int col = 0; col < numCols; col++) {
            if (digitalRead(colPins[col]) == LOW) {
                in_mat[row][col] = LOW;

                if (debugMode) {
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

    DcsBios::loop();
}