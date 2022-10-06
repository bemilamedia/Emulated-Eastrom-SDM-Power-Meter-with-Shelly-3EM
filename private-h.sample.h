// Replace the next variables with your SSID/Password combination
const char* ssid = "SSID";
const char* password = "password";

// MQTT setup
const char* mqtt_server = "192.168.0.10";                           // IP of the MQTT broker
const char* mqtt_username = "user";                                 // MQTT username
const char* mqtt_password = "password";                             // MQTT password
const char* clientID = "fakesdm";                                   // MQTT client ID
//const char* mqtt_topic = "shellies/Saldierung_Zaehler/Power";  // MQTT topic to get power calculated balance from the shellie 3EM over Homeassistant
// Setting the 3 MQTT topics to your shelly 3EM
const char* mqtt_topic_phase1 = "shellies/shellyem3-smartmeter/emeter/0/power";  // MQTT topic to get power reading from Phase 1
const char* mqtt_topic_phase2 = "shellies/shellyem3-smartmeter/emeter/1/power";  // MQTT topic to get power reading from Phase 2
const char* mqtt_topic_phase3 = "shellies/shellyem3-smartmeter/emeter/2/power";  // MQTT topic to get power reading from Phase 3
