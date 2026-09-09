/*
 * Pomodoro Timer - Raspberry Pi Pico
 * Uses an RGB LED and a push button to guide study/break sessions.
 * Color signals which session is active, button can interrupt sessions early.
 */

#include <stdio.h>
#include "pico/stdlib.h"
// #include "pico/cyw43_arch.h"  -- not used in this version, added for future WiFi features

/* RGB LED pins -- had to swap RED and GREEN after testing, LED wiring was reversed */
#define RED_PIN   12
#define GREEN_PIN 13
#define BLUE_PIN  11

/* Button on pin 14, uses internal pull-up so it reads LOW when pressed */
#define BUTTON_PIN 14


/* Returns true if the button is currently held down (active-low logic) */
bool is_button_pressed() {
    return gpio_get(BUTTON_PIN) == 0;
}

/* Drive the RGB LED -- each channel is just on/off (1 or 0), no PWM needed here */
void set_color(int r, int g, int b) {
    gpio_put(RED_PIN,   r);
    gpio_put(GREEN_PIN, g);
    gpio_put(BLUE_PIN,  b);
}

/*
 * Lights the LED in a session-specific color for ~15 seconds (150 * 100ms).
 * Session 1 = green, session 2 = purple, session 3 = cyan.
 * Button press during the loop allows the user to skip ahead early.
 */
void study_session(int session) {
    if (session == 1) {
        set_color(0, 1, 0);   // green -- fresh start
    } else if (session == 2) {
        set_color(1, 0, 1);   // purple -- mid-grind
    } else if (session == 3) {
        set_color(0, 1, 1);   // cyan -- final stretch
    }

    /* Poll every 100ms so button response feels instant to the user */
    for (int i = 0; i < 150; i++) {
        sleep_ms(100);
        if (is_button_pressed()) {
            sleep_ms(50);   // debounce -- let the signal settle before continuing
            break;
        }
    }
}

/*
 * Break between sessions -- color and duration scale with session number.
 * Longer final break (20s) after session 3 since it's the hardest one.
 * Button can skip the break early, same as study sessions.
 */
void break_session(int session) {
    int duration_steps;

    if (session == 1) {
        set_color(1, 1, 0);   // yellow -- short 10s breather
        duration_steps = 100; // 100 * 100ms = 10s
    } else if (session == 2) {
        set_color(1, 1, 1);   // white -- another 10s break
        duration_steps = 100;
    } else if (session == 3) {
        set_color(1, 0, 0);   // red -- 20s, earned it
        duration_steps = 200; // 200 * 100ms = 20s
    } else {
        return;
    }

    for (int i = 0; i < duration_steps; i++) {
        sleep_ms(100);
        if (is_button_pressed()) {
            sleep_ms(50);   // debounce -- let the signal settle before continuing
            break;
        }
    }
}


int main() {
    stdio_init_all();
    // cyw43_arch_init();  -- left here for when I add WiFi in a future version

    /* Set up LED pins as outputs */
    gpio_init(RED_PIN);
    gpio_set_dir(RED_PIN, GPIO_OUT);

    gpio_init(GREEN_PIN);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);

    gpio_init(BLUE_PIN);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);

    /* Button init -- must be set up before the startup animation in case user presses it */
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    /* Startup animation -- slow blink then fast blink in blue to signal ready */
    for (int i = 0; i < 3; i++) {
        set_color(0, 0, 1);
        sleep_ms(500);
        set_color(0, 0, 0);
        sleep_ms(500);
    }
    for (int i = 0; i < 5; i++) {
        set_color(0, 0, 1);
        sleep_ms(100);
        set_color(0, 0, 0);
        sleep_ms(100);
    }

    /* Main loop -- repeats the full 3-session Pomodoro cycle indefinitely */
    while (1) {

        // --- Session 1 ---
        printf("Study time! TIME TO BE PRODUCTIVE!\n");
        study_session(1);
        printf("Break time! WHICH IS ALSO PRODUCTIVE!\n");
        break_session(1);

        // --- Session 2 ---
        printf("Time for session 2, KEEP IT UP\n");
        study_session(2);
        printf("Break time! Rest up and get ready\n");
        break_session(2);

        // --- Session 3 ---
        printf("TIME FOR SESSION 3, YOU'RE ALMOST THERE\n");
        study_session(3);
        printf("SESSION 3 IS OVER, you have earned the rest -- or keep going!\n");
        break_session(3);

        /* Loop back to session 1 automatically.
         * The commented block below was an early idea to let the user quit,
         * but auto-looping is simpler for now. */
        // printf("Continue? (y/n):\n");
        // char choice;
        // scanf(" %c", &choice);
        // if (choice == 'n') { break; }

    }  // end while
}
