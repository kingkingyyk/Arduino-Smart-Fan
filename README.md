***Smart Fan @ Arduino***

An AC fan controller with temperature sensing + OLED display


**My Setup :**

 - DFRduino Nano
 - LM35 Temperature Sensor
 - Grove Relay
 - SSD1306 128x64 0.96" OLED screen


**Working Mechanism :**

 - TARGET_SUSTAIN_TIME -> Buffer time to trigger on / off, ranges between TARGET_TEMPERATURE_MIN and TARGET_TEMPERATURE_MAX
 - TARGET_TEMPERATURE -> The temperature you wish to achieve
 - TARGET_TEMPERATURE_MIN -> The temperature that is low enough to shut off the fan directly (bypass TARGET_SUSTAIN_TIME)
 - TARGET_TEMPERATURE_MAX -> The temperature that is high enough to turn on the fan directly (bypass TARGET_SUSTAIN_TIME)

**Bonus :**
 - Adafruit Watchdog to auto restart when the Arduino hangs at somewhere
 - Fast DigitalIO (On/Off Relay)