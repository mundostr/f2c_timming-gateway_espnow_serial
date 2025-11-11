/*
CONTROL TIEMPOS VCC
Gateway ESP32, actúa como GW ESPNOW y enlaza los cuentavueltas inalámbricos por Webserial.
https://github.com/gmag11/QuickEspNow
https://randomnerdtutorials.com/esp-now-two-way-communication-esp32/
https://github.com/m1cr0lab-esp32/esp-now-network-and-wifi-gateway
https://www.survivingwithandroid.com/esp-now-esp32-esp8266/

ATENCION!: recordar borrar la flash completa
(esptool.py --port PUERTO erase_flash) en caso de problemas
*/

#include "config.h"
#include "main.h"
#include "pushbtn.h"

void setup() {
	Serial.begin(SERIAL_CONSOLE_BAUDS);
    // SerialLog.begin(SERIAL_CONSOLE_BAUDS, SERIAL_8N1, 17, 18);
	// WiFi.mode(WIFI_MODE_STA);
    // Serial.println(WiFi.macAddress());
	// while(1);
	
	main::init();
	pushbtn::init();
	main::init_espnow(true);
	
	digitalWrite(LED_PIN, HIGH);
	delay(3000);
	digitalWrite(LED_PIN, LOW);

	// pushbtn::notify_all((String)GATEWAY_ID + ",0");
}

void loop() {
	pushbtn::btn.loop();
	main::check_led_advertising();
    main::verify_lap_counters_leds();
}
