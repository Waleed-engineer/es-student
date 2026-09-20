#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>

const uint LED_PIN = 25;
const uint BUTTON_PIN = 15;
const uint DEBOUNCE_MS = 20;

bool get_button_debounce(uint pin)
{
    bool state = gpio_get(pin);
    sleep_ms(DEBOUNCE_MS);
    return state && gpio_get(pin);
}

void set_led(bool on)
{
    gpio_put(LED_PIN, on);
    printf("led %s\n", on ? "on" : "off");
}
int main()
{
    stdio_init_all();
	// === ШАГ 1: ПОЛНАЯ ИНИЦИАЛИЗАЦИЯ ЖЕЛЕЗА ===
    
    // Настраиваем кнопку
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    
    // Настраиваем светодиод (теперь он инициализируется ДО цикла!)
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Переменные для отслеживания состояния кнопки
    bool led = false;
    bool previous = true; // По умолчанию Pull-Up держит true, пока кнопка не нажата

    // === ШАГ 2: ЕДИНЫЙ РАБОЧИЙ ЦИКЛ ===
    while (1)
    {
        bool current = get_button_debounce(BUTTON_PIN);

        // Логика триггера: кнопка была отпущена (true), а стала нажата (false)
        if (previous == true && current == false)
        {
            led = !led;
            set_led(led);
        }

        previous = current;
        
        // Микропауза 5 миллисекунд. Нужна кремнию, чтобы гасить дребезг контактов
        sleep_ms(5); 
    }
}
