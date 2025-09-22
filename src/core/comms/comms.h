#pragma once
#ifndef COMMS_H
#define COMMS_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>

enum COMMS_CONN_ERR {
    COMMS_SUCCESS = 0,
    COMMS_FAILURE = 1,
    COMMS_NO_TEAM_ID = 2,
    COMMS_INVALID_TEAM_ID = 3
};

enum COMMS_MDNS_ERR {
    MDNS_SUCCESS = 0,
    MDNS_FAILURE = 1
};

enum COMMS_CONN_TYPE {
    CONN_FIELD = 0,
    CONN_BRIDGE = 1,
    CONN_AP = 2
};

// TODO: nada que ver
class Comms {
    protected:
        // Field
        const char* fieldSSID = "MechaLeague-Field";
        const char* fieldPass = "12345678";

        // MDNS
        const char* mdnsFormat = "mechaleague-bot-"; // mechaleague-bot-<team_id>.local

        // Control sockets
        WiFiUDP controlServer;
        const uint controlServerPort = 1010;

        // Telemetry sockets
        WiFiUDP telemetryServer;
        const uint telemetryServerPort = 1011;

        bool validateTeamID() {
            // if (TEAM_ID > 0 && TEAM_ID <= 9999) return true;
            return false;
        }

        COMMS_CONN_ERR connectToWiFi(const char* ssid, const char* password = NULL) {
            #ifdef TEAM_ID
            // Validate team ID
            if (!validateTeamID()) return COMMS_CONN_ERR::COMMS_INVALID_TEAM_ID;

            // Compute IP address if needed
            // if (localIP) localIP.fromString(generateIPAddress(TEAM_ID));

            // Connect to wifi
            // WiFi.config(localIP, gateway, subnet, dns1, dns2);
            WiFi.mode(WIFI_STA);
            if (password != NULL) WiFi.begin(ssid, password);
            else WiFi.begin(ssid);
            WiFi.waitForConnectResult();
            wl_status_t status = WiFi.status();

            // Start control and telemetry servers
            startServer();

            // Start MDNS
            startMDNS();

            return status == WL_CONNECTED ? COMMS_CONN_ERR::COMMS_SUCCESS : COMMS_CONN_ERR::COMMS_FAILURE;

            #else
            return COMMS_CONN_ERR::COMMS_NO_TEAM_ID;
            #endif
        }

    public:
        void startMDNS() {
            char mdnsName[sizeof(mdnsFormat) + 4]; // Enough space for "mechaleague-bot-9999\0"
            // snprintf(mdnsName, sizeof(mdnsName), "%s%d", mdnsFormat, TEAM_ID); // mechaleague-bot-<team_id>
            MDNS.begin(mdnsName);
        }

        void startServer() {
            controlServer.begin(controlServerPort);
            telemetryServer.begin(telemetryServerPort);
        }

        COMMS_CONN_ERR connectToField() {
            return connectToWiFi(fieldSSID, fieldPass);
        }

    // Singleton
    private:
        bool init = false;
    public:
        Comms() {};
        static Comms& getInstance() {
            static Comms instance;
            return instance;
        }
};

#endif