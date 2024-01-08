#pragma once

#include "config.h"

namespace pushbtn {
	Button2 btn;

	void notify_all(String message) {
		// wss.broadcastTXT(message.c_str(), message.length());
		quickEspNow.send(ESPNOW_BROADCAST_ADDRESS, (uint8_t*)message.c_str(), message.length());
		if(DEBUG) Serial.println(message);
	}

	void cbPressed(Button2& btn) {
		digitalWrite(LED_PIN, HIGH);
	}

	void cbReleased(Button2& btn) {
		digitalWrite(LED_PIN, LOW);
	}

	void cbLongpressed(Button2& btn) {
		digitalWrite(LED_PIN, LOW);
		// config::race_started = !config::race_started;
        // Serial.printf(config::race_started ? "STA|000|000": "STO|000|000");
		// config::race_started ? notify_all("4,START") : notify_all("4,RESET");
        Serial.printf("STA|000|000");
	}

	void init() {
		btn.begin(PUSHBTN_PIN);
		btn.setDebounceTime(PUSHBTN_DEBOUNCE_TIME);
		btn.setLongClickTime(PUSHBTN_RESET_FREC);
		btn.setPressedHandler(cbPressed);
		btn.setReleasedHandler(cbReleased);
		btn.setLongClickDetectedHandler(cbLongpressed);
	}
}
