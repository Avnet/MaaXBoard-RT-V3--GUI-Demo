
#ifndef _LVGL_DEMO_H_
#define _LVGL_DEMO_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef enum _i2cBus
{
    I2C1 = 1,
    I2C2 = 2,
    I2C3 = 3,
    I2C4 = 4,
    I2C5 = 5,
    I2C6 = 6
} i2cBus;

/*******************************************************************************
 * Functions
 ******************************************************************************/

void addItemToSSIDList(const char * text);

bool isLvglReady(void);

void lvgl_task(void *param);
void vApplicationTickHook_lvgl(void);

void openNetworkScreen();
void openMenuScreen();
void openLEDScreen();
void openUSBScreen();
void openAVScreen();
void openCustomScreen();
void openHelpScreen();

void setLedRedImgState(bool state);
void setLedGreenImgState(bool state);
void setLedBlueImgState(bool state);

void setHIDsRefreshed(void);

void setI2cBus(i2cBus bus);
void scani2cBusAndDisplay(void);
void writeToHIDInputTextArea(const char* text);
void deleteLeftCharTextArea();
bool capturingMouseInputOnTA(void);
void setCaptureMouseInputOnTA(bool state);
bool capturingKeyboardInputOnTA(void);
void setCaptureKeyboardInputOnTA(bool state);

void startSSIDScan();

void enableMic(int mic, bool state);
void addMicData(int mic, int16_t value);

void connectToSelectedAP(void);
void notifyConnectedToAP(void);

#endif //_LVGL_DEMO_H_
