#include <Arduino.h>
#include <GotchauButton.h>

Button::Button()
{
}

Button::Button(int8_t _pin, LogicPin lp, ButtonType bt)
{
    pin = _pin;
    logicPin = lp;
    buttonType = bt;
    pinMode(pin, logicPin ? INPUT_PULLUP : INPUT);
}

void Button::update()
{
    if (pin < 0)
        return;

    currentState = digitalRead(pin) ^ logicPin ^ buttonType;
    now = millis();

    // press
    if (currentState && !lastState)
    {
        lastState = currentState;
        if (now - releasedAt > debounceTime)
        {
            pressedAt = now;
            states[Pressed] = true;
            clicks++;
            clickCheckTime = now + clickTimeout;
        }
    }
    // release
    if (!currentState && lastState)
    {
        lastState = currentState;
        if (now - pressedAt > debounceTime)
        {
            releasedAt = now;
            states[WasHolded] = false;
            states[Released] = true;
        }
    }
    // hold
    if (currentState && !states[WasHolded] && now - pressedAt > holdTime)
    {
        states[WasHolded] = true;
        states[Holded] = true;
    }
    // clamp
    if (currentState && states[WasHolded] && now - pressedAt > clampTimeout)
    {
        if (1)
            clicks = 0;
        else
            clicks++;

        pressedAt = now;
        states[Clamped] = true;
    }
    // multiclick
    if (!currentState && clicks > 0 && now > clickCheckTime)
    {
        states[HasClicks] = true;
    }
}

bool Button::is(StateEnum state)
{
    if (autoUpdate)
        update();

    // returns state without reset
    if (state == WasHolded)
        return states[WasHolded];
    if (state == HasClicks)
        return states[HasClicks];

    bool temp = states[state];
    states[state] = false;
    return temp;
}

void Button::setAutoUpdate(bool au)
{
    autoUpdate = au;
}

void Button::setDebounceTime(uint8_t time)
{
    debounceTime = time;
}

void Button::setHoldTime(uint16_t ht)
{
    holdTime = ht;
}
void Button::setClampTimeout(uint16_t clpt)
{
    clampTimeout = clpt;
}
void Button::setClickTimeout(uint16_t clkt)
{
    clickTimeout = clkt;
}

int8_t Button::getClicks()
{
    if (states[HasClicks])
    {
        states[HasClicks] = false;
        int8_t temp = clicks;
        clicks = 0;
        return temp;
    }
    return -1;
}