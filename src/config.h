#pragma once

#include <string.h>
#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <QuickEspNow.h>
#include <Button2.h>

#define DEBUG true

#define LED_PIN 25 // 2 Node32S, 33 ESP32 Cam
#define POWER_PIN 33
#define PUSHBTN_PIN 26

#define LAP_COUNTER_1_PIN 27
#define LAP_COUNTER_2_PIN 14
#define LAP_COUNTER_3_PIN 12

#define LED_NOTIF_FREC 100
#define PUSHBTN_DEBOUNCE_TIME 75
#define PUSHBTN_RESET_FREC 2000
#define LAPTIMERS_LEDS_RESET_FREC 5500
#define SERIAL_CONSOLE_BAUDS 115200
#define TTL_REPORT_TIME 1000
#define ESPNOW_CHANNEL 1
#define GATEWAY_ID "GWVCC"
#define USE_BROADCAST 1

// HardwareSerial SerialLog(1);

namespace config {
	// const uint8_t this_mac_address[] = { 0x30, 0xAE, 0xA4, 0x1F, 0x44, 0x0C };
	// const uint8_t custom_mac_master[] = { 0xB4, 0xE6, 0x2D, 0xE9, 0xFE, 0x6E };
	const uint8_t broadcast_mac_address[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

	bool led_on = false;
	bool race_started = false;
}
