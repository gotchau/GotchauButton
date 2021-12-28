#include <GotchauButton.h>

Button btn(3); // в скобках номер контакта

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (btn.is(Pressed)) //нажатие
    {
        Serial.print("Pressed: ");
        Serial.println(millis());
    }
    if (btn.is(Released)) //отпускание
    {
        Serial.print("Released: ");
        Serial.println(millis());
    }
    if (btn.is(Clamped)) //зажатие на продолжительный период
    {
        Serial.print("Clamped: ");
        Serial.println(millis());
    }
    if (btn.is(Holded)) //удержание
    {
        Serial.print("Holded: ");
        Serial.println(millis());
    }
    if (btn.is(HasClicks)) //многокликовость, выводит сколько было сделано кликов
    {
        Serial.print("Clicks: ");
        Serial.println(btn.getClicks());
    }
}
