# Hardware Projects

Physical hardware projects built during IoT studies — microcontrollers,
sensors, and LEDs. Each one was built to practice a specific hardware concept,
not just to have something blinking.

| Project | Platform | What it is |
|---|---|---|
| [pomodoro/](pomodoro/) | Raspberry Pi Pico 2 W | Hardware Pomodoro timer — RGB LED signals session phase, button skips early |
| [light-sensor/](light-sensor/) | Arduino Uno | Light-reactive LED — photoresistor drives PWM brightness, button toggles on/off |

---

## Pomodoro Timer

A hardware Pomodoro timer on the Raspberry Pi Pico 2 W. No screen, no display —
an RGB LED is the only output. Each study/break phase gets its own color.
A button with debounce lets you skip sessions early.

Built with the native **Pico C SDK** (not Arduino framework) — direct GPIO
calls, `gpio_pull_up` for internal pull-up, 50 ms debounce.

**What it practices:** state machines on embedded hardware, internal pull-up
resistors, debounce, structuring embedded C into reusable functions.

| Phase | Color | Duration |
|---|---|---|
| Study 1 | Green | 15 s (adjustable) |
| Break 1 | Yellow | 10 s |
| Study 2 | Purple | 15 s |
| Break 2 | White | 10 s |
| Study 3 | Cyan | 15 s |
| Break 3 | Red | 20 s |

---

## Light-Reactive LED

An Arduino project combining a photoresistor, pushbutton, and PWM LED in one
circuit. The button toggles the LED on and off. While on, brightness follows
ambient light — cover the sensor and the LED brightens.

Prototyped in Wokwi first to get wiring right, then verified on real hardware.
The sensor's real-world range (0–16 instead of the theoretical 0–1023) required
rescaling `map()` to the actual measured range.

**What it practices:** `analogRead`, `analogWrite`, `INPUT_PULLUP`, PWM,
`map()` for sensor scaling, serial debug output, Wokwi prototyping workflow.

---

## Build

**Pomodoro** — Pico C SDK + CMake:

```bash
mkdir build && cd build
cmake ..
make
```

Flash the `.uf2` by holding BOOTSEL while connecting, then drag onto the Pico.

**Light sensor** — Arduino IDE or CLI, upload to an Uno.
