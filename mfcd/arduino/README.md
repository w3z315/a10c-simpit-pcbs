# MFCD (Multi-Function-Color-Display) Arduino Code

This software is work in progress. And is currently using an Arduino Uno R3.

## Features
- [X] Button Matrix
- [X] OFF/NT/DAY 3-Pos Switch via Matrix
- [ ] Backlighting (Currently missing because the board needs a v2)

## Configuration
Uncomment `#define MFCD_LEFT` and comment `#define MFCD_RIGHT` if you want to compile for the left MFCD version.

Serial-Debugging; set `debugMode = true;`

## Rows / Cols to PinOut

### Cols
| Pin | Col |
|-----|-----|
| 2   | 0   |
| 3   | 1   |
| 4   | 2   |
| 5   | 3   |
| 6   | 4   |
| 7   | 5   |
| 8   | 6   |



### Rows

| Pin | Row |
|-----|-----|
| 9   | 0   |
| 10  | 1   |
| 11  | 2   |
| 12  | 3   |
| 13  | 4   |
| A0  | 5   |
| A1  | 6   |
| A2  | 7   |
| A3  | 8   |
| A4  | 9   |
| A5  | 10  |



### Button / Row Col

|          | C0: 2   | C1: 3     | C2: 4              | C3: 5     | C4: 6 | C5: 7   | C6: 8   |
|----------|---------|-----------|--------------------|-----------|-------|---------|---------|
| R00 : 9  |         | OSB1      | OSB2               | OSB3      | OSB4  | OSB5    |         |
| R01 : 10 | ADJ_UP  |           |                    |           |       |         | DSP_UP  |
| R02 : 11 | ADJ_DWN |           |                    |           |       |         | DSP_DWN |
| R03 : 12 | OSB20   |           |                    |           |       |         | OSB6    |
| R04 : 13 | OSB19   |           |                    |           |       |         | OSB7    |
| R05 : A0 | OSB18   |           |                    |           |       |         | OSB8    |
| R06 : A1 | OSB17   |           |                    |           |       |         | OSB9    |
| R07 : A2 | OSB16   |           |                    |           |       |         | OSB10   |
| R08 : A3 | CON_UP  |           |                    |           |       |         | BRT_UP  |
| R09 : A4 | CON_DWN | 3WAY_POS1 | 3WAY_POS2(ignored) | 3WAY_POS3 |       |         | BRT_DWN |
| R10 : A6 | OSB15   | OSB14     | OSB13              | OSB12     | OSB11 | SYM_DWN | SYM_UP  |

