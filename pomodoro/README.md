# Pomodoro Timer — Raspberry Pi Pico

A hardware Pomodoro timer built on the Raspberry Pi Pico 2 W. An RGB LED
signals which session is active. A button lets you skip sessions early.

This was the project that pushed me past blinking LEDs. No display, no screen —
just color as communication. It forced me to think about state machines and how
to make hardware tell a story using only light.

## How it works

Three study sessions with breaks in between. Each phase has its own color:

| Phase | Color | Duration |
|---|---|---|
| Study 1 | Green | 15 s |
| Break 1 | Yellow | 10 s |
| Study 2 | Purple | 15 s |
| Break 2 | White | 10 s |
| Study 3 | Cyan | 15 s |
| Break 3 | Red | 20 s |

Durations are short for testing — change the loop counts in the source for real sessions.

The button uses an internal pull-up (`gpio_pull_up`) so no external resistor is needed.
Pressing it during any phase skips to the next one. A 50 ms debounce delay prevents
false triggers from switch bounce.

## Build

Built with the Pico C SDK on a Pico 2 W.

```bash
mkdir build && cd build
cmake ..
make
```

Flash the generated `.uf2` by holding BOOTSEL while connecting via USB,
then drag the file onto the Pico's storage.

## What I learned

- `gpio_init`, `gpio_set_dir`, `gpio_pull_up` for hardware setup
- Active-low button logic with internal pull-up
- 50 ms debounce pattern to filter switch bounce
- Structuring embedded code into reusable functions (`study_session`, `break_session`)
- Why button init must come before any animation that might read it

## What I would improve

- Real session lengths — just increase the `sleep_ms` loop counts
- A buzzer to signal transitions without needing to watch the LED
- WiFi logging via the onboard CYW43 chip (CMakeLists already links the library)
