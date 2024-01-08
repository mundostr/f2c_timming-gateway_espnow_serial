#pragma once

#include "config.h"

/**
 * En esta versión no lo estamos utilizando, se comunica por puerto serie con la computadora
*/

namespace socket {
	/* void wss_events(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
		char incoming[length + 1];

        switch(type) {
			case WStype_DISCONNECTED:
				break;
			case WStype_CONNECTED:
                if(DEBUG) Serial.printf("[WSS] connected: %s (%d)\n", payload, num);
				// wss.broadcastTXT("reset");
				break;
			case WStype_TEXT:
                snprintf(incoming, length + 1, "%s", payload);

                if (strcmp(incoming, "5,INIT") == 0) {
                    config::race_started = false;
		        }
				
                if(DEBUG) Serial.printf("[WSS] incoming text: %s\n", payload);
				// wss.sendTXT("message here");
				break;
			case WStype_BIN:
				// wss.sendBIN(payload, length);
				break;
			case WStype_ERROR:			
			case WStype_FRAGMENT_TEXT_START:
			case WStype_FRAGMENT_BIN_START:
			case WStype_FRAGMENT:
			case WStype_FRAGMENT_FIN:
				break;
		}
	} */

	/* void init_wss() {
		wss.begin();
		wss.onEvent(wss_events);
		// wss.setAuthorization("pepe", "pompin");
		// wss.setReconnectInterval(5000);
		// wss.enableHeartbeat(5000, 5000, 0);

		if(DEBUG) Serial.println("Servidor websocket activado");
	} */
}
