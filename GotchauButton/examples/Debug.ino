#include <GotchauButton.h>

Button btn(3);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (btn.is(Pressed))
    {
        Serial.print("Pressed: ");
        Serial.println(millis());
    }
    if (btn.is(Released))
    {
        Serial.print("Released: ");
        Serial.println(millis());
    }
    if (btn.is(Clamped))
    {
        Serial.print("Clamped: ");
        Serial.println(millis());
    }
    if (btn.is(Holded))
    {
        Serial.print("Holded: ");
        Serial.println(millis());
    }
    if (btn.is(HasClicks))
    {
        Serial.print("Clicks: ");
        Serial.println(btn.getClicks());
    }
}