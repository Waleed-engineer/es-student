#include "pico/stdlib.h"
#include "hardware/gpio.h"

const uint LED_PIN = 25;
const uint BUTTON_PIN = 15;

int main()
{
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
        bool current = gpio_get(BUTTON_PIN);

        // Логика триггера: кнопка была отпущена (true), а стала нажата (false)
        if (previous == true && current == false)
        {
            led = !led;
            gpio_put(LED_PIN, led);
        }

        previous = current;
        
        // Микропауза 5 миллисекунд. Нужна кремнию, чтобы гасить дребезг контактов
        sleep_ms(5); 
    }
}
