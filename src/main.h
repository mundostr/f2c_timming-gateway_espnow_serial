#pragma once

#include "config.h"

namespace main {
	uint32_t led_timer = 0, lap_counter_1_timer = 0, lap_counter_2_timer = 0, lap_counter_3_timer = 0;
    int lap_counter_1_status = 0, lap_counter_2_status = 0, lap_counter_3_status = 0;

	void init() {
        pinMode(LED_PIN, OUTPUT);
		digitalWrite(LED_PIN, LOW);
		
        pinMode(POWER_PIN, OUTPUT);
		digitalWrite(POWER_PIN, HIGH);

        pinMode(LAP_COUNTER_1_PIN, OUTPUT);
		digitalWrite(LAP_COUNTER_1_PIN, LOW);

        pinMode(LAP_COUNTER_2_PIN, OUTPUT);
		digitalWrite(LAP_COUNTER_2_PIN, LOW);

        pinMode(LAP_COUNTER_3_PIN, OUTPUT);
		digitalWrite(LAP_COUNTER_3_PIN, LOW);

		pinMode(PUSHBTN_PIN, INPUT_PULLUP);
	}

	void turn_led_on() {
		digitalWrite(LED_PIN, HIGH);
		config::led_on = true;
		led_timer = millis();
	}

    void on_data_recv(uint8_t* address, uint8_t* data, uint8_t len, signed int rssi, bool broadcast) {
        turn_led_on();

        char incoming[16];
        snprintf(incoming, len + 1, "%s", data);
    	
        if (strcmp(incoming, "1,BEAT") == 0) {
            digitalWrite(LAP_COUNTER_1_PIN, HIGH);
            quickEspNow.send(address, (uint8_t*)"4,CONN", 6);

            if (lap_counter_1_status == 0) {
                lap_counter_1_status = 1;
                Serial.printf("CON|001-001");
            }

            lap_counter_1_timer = millis();
        
        } else if (strcmp(incoming, "2,BEAT") == 0) {
            digitalWrite(LAP_COUNTER_2_PIN, HIGH);
            quickEspNow.send(address, (uint8_t*)"4,CONN", 6);
        
            if (lap_counter_2_status == 0) {
                lap_counter_2_status = 1;
                Serial.printf("CON|002-001");
            }

            lap_counter_2_timer = millis();
        
        } else if (strcmp(incoming, "3,BEAT") == 0) {
            digitalWrite(LAP_COUNTER_3_PIN, HIGH);
            quickEspNow.send(address, (uint8_t*)"4,CONN", 6);

            if (lap_counter_3_status == 0) {
                lap_counter_3_status = 1;
                Serial.printf("CON|003-001");
            }
            
            lap_counter_3_timer = millis();
        
        } else {
            String parsedData = String(incoming);
            String team = parsedData.substring(0, 1);
            String laps = parsedData.substring(2);
            Serial.printf("LAP|%03s-%03s", team, laps);

            if (team == "1") {
                lap_counter_1_timer = millis();
            } else if (team == "2") {
                lap_counter_2_timer = millis();
            } else {
                lap_counter_3_timer = millis();
            }
        }

        // Serial.printf ("ESPNOW received: %s\n", incoming);
	}

    void on_data_sent(uint8_t* address, uint8_t status) {
    }

	void init_espnow(bool customMac = false) {
        // if (customMac) esp_wifi_set_mac(WIFI_IF_STA, config::custom_mac_master);
        WiFi.mode(WIFI_MODE_STA);
        WiFi.disconnect(false, true);

        quickEspNow.begin (ESPNOW_CHANNEL, 0, false);
        quickEspNow.onDataSent (on_data_sent);
        quickEspNow.onDataRcvd (on_data_recv);

        esp_now_peer_info_t peer = {};
        peer.channel = ESPNOW_CHANNEL;
        peer.encrypt = false;
        peer.ifidx = WIFI_IF_STA;
        memcpy(peer.peer_addr, config::broadcast_mac_address, 6);
        
        if (esp_now_add_peer(&peer) != ESP_OK) {
            #if DEBUG
            Serial.println("Failed to add peer");
            #endif

            while (1);
        }

		if (DEBUG) Serial.println("ESPNOW OK");
		if (DEBUG) Serial.println(WiFi.localIP());
		if (DEBUG) Serial.println(WiFi.channel());
		if (DEBUG) Serial.println(WiFi.macAddress());
	}

	void check_led_advertising() {
		if (config::led_on && (millis() - led_timer >= LED_NOTIF_FREC)) {
			led_timer = millis();
			digitalWrite(LED_PIN, LOW);
			config::led_on = false;
		}

	}

    void verify_lap_counters_leds() {
        if (millis() - lap_counter_1_timer >= LAPTIMERS_LEDS_RESET_FREC) {
            digitalWrite(LAP_COUNTER_1_PIN, LOW);
            
            if (lap_counter_1_status == 1) {
                lap_counter_1_status = 0;
                Serial.printf("CON|001-000");
            }
            
            lap_counter_1_timer = millis();
        }

        if (millis() - lap_counter_2_timer >= LAPTIMERS_LEDS_RESET_FREC) {
            digitalWrite(LAP_COUNTER_2_PIN, LOW);
            
            if (lap_counter_2_status == 1) {
                lap_counter_2_status = 0;
                Serial.printf("CON|002-000");
            }

            lap_counter_2_timer = millis();
        }

        if (millis() - lap_counter_3_timer >= LAPTIMERS_LEDS_RESET_FREC) {
            digitalWrite(LAP_COUNTER_3_PIN, LOW);
            
            if (lap_counter_3_status == 1) {
                lap_counter_3_status = 0;
                Serial.printf("CON|003-000");
            }

            lap_counter_3_timer = millis();
        }
    }
}
