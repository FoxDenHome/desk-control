#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#include "mqtt.h"

#include "config.h"
#include "desk.h"
#include "ranging.h"
#include "util.h"

WiFiClient espMqttClient;
PubSubClient mqttClient(espMqttClient);

String lastErrorCode = "";
void mqttSetLastError(String errorCode)
{
    lastErrorCode = errorCode;
    Serial.println("ERROR: " + errorCode);
}

void mqttCallback(char *topic, byte *payload, unsigned int len)
{
    char str[len + 1];
    memcpy(str, payload, len);
    str[len] = 0;

    DynamicJsonDocument doc(256);
    deserializeJson(doc, str);

    const char *id = doc["id"].as<const char *>();

    const char *cmd = doc["command"].as<const char *>();
    if (strcmp(cmd, "adjust") == 0)
    {
        int16_t target = doc["target"].as<int16_t>();
        deskAdjustHeight(target, id);
    }
    else if (strcmp(cmd, "stop") == 0)
    {
        deskStop();
    }
    else if (strcmp(cmd, "range") == 0)
    {
        mqttSendJSON(id, "range", "OK");
    }
    else if (strcmp(cmd, "restart") == 0)
    {
        bool force = doc["force"].as<bool>();
        if (!doRestart(force))
        {
            mqttSendJSON(id, "status", "RESTART NOT ALLOWED");
        }
    }
    else
    {
        mqttSendJSON(id, "error", "UNKNOWN COMMAND");
    }
}

bool mqttIsConnected()
{
    return mqttClient.connected();
}

bool mqttEnsureConnected()
{
    if (mqttClient.connected())
    {
        return true;
    }

    if (!WiFi.isConnected())
    {
        return false;
    }

    mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
    mqttClient.setCallback(mqttCallback);
    String clientId = WIFI_HOSTNAME "-" + String(WiFi.macAddress());

    if (!mqttClient.connect(clientId.c_str(), MQTT_USERNAME, MQTT_PASSWORD))
    {
        Serial.print("MQTT connection error: ");
        Serial.println(mqttClient.state());
        return false;
    }

    Serial.println("MQTT connected");

    mqttClient.subscribe(MQTT_TOPIC_SUB);
    return true;
}

static void mqttLoopTask(void *parameter)
{
    while (1)
    {
        if (mqttEnsureConnected())
        {
            mqttClient.loop();
            if (!lastErrorCode.isEmpty())
            {
                mqttSendJSON(NULL, "error", lastErrorCode.c_str(), -1);
            }
        }
        delay(10);
    }
}

void mqttSetup()
{
    mqttEnsureConnected();
    CREATE_TASK_IO(mqttLoopTask, "mqttLoop", 1, NULL);
}

void mqttSend(const char *data)
{
    if (!mqttEnsureConnected())
    {
        return;
    }
    mqttClient.publish(MQTT_TOPIC_PUB, data);
}

void mqttSendJSON(const char *mqttId, const char *type, const char *data, int16_t range)
{
    if (range == -999)
    {
        range = rangingWaitAndGetDistance();
    }
    const int8_t movingDirection = deskGetMovingDirection();
    const int16_t target = deskGetTarget();

    Serial.print("<");
    Serial.print(type);
    Serial.print("> ");
    Serial.print(data);
    Serial.print(" [");
    Serial.print(range);
    Serial.print(" => ");
    Serial.print(target);
    Serial.print(" @ ");
    Serial.print(movingDirection);
    Serial.println("]");

    char buf[256];

    StaticJsonDocument<256> doc;
    if (mqttId && mqttId[0])
    {
        doc["id"] = mqttId;
    }
    doc["type"] = type;
    doc["data"] = data;
    doc["range"] = range;
    doc["direction"] = movingDirection;
    doc["target"] = target;
    int len = serializeJson(doc, buf);

    buf[len] = 0;

    mqttSend(buf);
}
