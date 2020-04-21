#include <Arduino.h>


enum StateEnum
{
    Pressed = 0,
    Released,
    HasClicks,
    Holded,
    WasHolded,
    Clamped,
    StateEnumLenght
};

enum LogicPin
{
    VCC = false,
    GND = true
};

enum ButtonType
{
    NormalOpen = false,
    NormalClosed = true
};

class Button
{
private:
    int8_t pin = -1;
    bool logicPin = GND;
    bool buttonType = NormalOpen;
    bool autoUpdate = true;

    bool currentState = false;
    bool lastState = false;
    uint32_t now = 0;
    uint32_t pressedAt = 0;
    uint32_t releasedAt = 0;    
    uint32_t clickCheckTime = 0;
    uint8_t debounceTime = 50;
    uint16_t holdTime = 1000;
    uint16_t clampTimeout = 200;
    uint16_t clickTimeout = 400;

    int8_t clicks = 0;

    bool states[StateEnumLenght];

public:
    Button();
    Button(int8_t, LogicPin = GND, ButtonType = NormalOpen);  // pin, logic pin

    void update();    
    void setAutoUpdate(bool);    
    bool is(StateEnum);
    int8_t getClicks();
    void setDebounceTime(uint8_t);
    void setHoldTime(uint16_t);
    void setClampTimeout(uint16_t);
    void setClickTimeout(uint16_t);
};