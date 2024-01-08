# CONTROL LINE F2C TIMMING 2024
## ESPNOW GATEWAY

## This proyect is related with Aeromodelling, Control Line Racing class F2C.

### Elements needed:
- ESP32 based development board with external 2.4 antenna.
- 12x12 pushbutton or alternative endstop for start/stop races.
- 5 x 5mm regular led:
    * 1 for power indicador.
    * 1 for packets transmission indicator.
    * 3 for lapcounters connection indicators (can be of different colours).

### Features:
- Visual lapcounters connections indicators.
- Central start/stop race button with delay.

### Operation:
- Just plug the adapter cable into any free USB port of the computer, it will be used for both power the box and send serial communication to the timming program. The power led (1st to the left) should light up and stay on.
- The box is ready for lacounters connections, if any lapcounter is powered on the remote side, the corresponding led will light up on the box and also stay on. If any lapcounter is powered off or losses connection, the corresponding led will light off.
- To send a start / stop signal to the timming program, just press and hold the central button for 2 secs (once will start, once will stop, and so on). This is a secure measure to avoid the sending of accidental commands by misstouching the button.