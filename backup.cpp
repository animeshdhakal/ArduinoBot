#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <L298NX2.h>
#include <WiFi.h>

#define MOTOR1_SPEED 2
#define MOTOR1_1 5
#define MOTOR1_2 4

#define MOTOR2_SPEED 21
#define MOTOR2_1 18
#define MOTOR2_2 19

#define MOTOR3_SPEED 25
#define MOTOR3_1 26
#define MOTOR3_2 27

#define MOTOR4_SPEED 13
#define MOTOR4_1 12
#define MOTOR4_2 14

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define UP_LEFT 5
#define UP_RIGHT 6
#define DOWN_LEFT 7
#define DOWN_RIGHT 8
#define STOP 0

const char* ssid = "ValmikiRobo";
const char* password = "valmiki123";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

L298NX2 motors1(MOTOR1_SPEED, MOTOR1_1, MOTOR1_2, MOTOR2_SPEED, MOTOR2_1, MOTOR2_2);
L298NX2 motors2(MOTOR3_SPEED, MOTOR3_1, MOTOR3_2, MOTOR4_SPEED, MOTOR4_1, MOTOR4_2);

const char* htmlHomePage PROGMEM = R"HTMLHOMEPAGE(
<!DOCTYPE html><html><head><meta name="viewport" content="width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no"><style>.arrows{font-size:70px;color:red}.circularArrows{font-size:80px;color:#00f}td{background-color:#000;border-radius:25%;box-shadow:5px 5px #888}td:active{transform:translate(5px,5px);box-shadow:none;justify-content:center}.speedcontainer{display:flex;flex-direction:row;justify-content:center;gap:10px;margin-top:20px}.noselect{-webkit-touch-callout:none;-webkit-user-select:none;-khtml-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none}</style></head><body class="noselect" align="center" style="background-color:#fff"><h1 style="color:teal;text-align:center">Valmiki Shiksha Sadan</h1><h2 style="color:teal;text-align:center">Animesh Dhakal</h2><table id="mainTable" style="width:400px;margin:auto;table-layout:fixed" cellspacing="10"><tr><td ontouchstart='onTouchStartAndEnd("5")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows">&#11017;</span></td><td ontouchstart='onTouchStartAndEnd("1")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows">&#8679;</span></td><td ontouchstart='onTouchStartAndEnd("6")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows">&#11016;</span></td></tr><tr><td ontouchstart='onTouchStartAndEnd("3")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows">&#8678;</span></td><td></td><td ontouchstart='onTouchStartAndEnd("4")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows">&#8680;</span></td></tr><tr><td ontouchstart='onTouchStartAndEnd("7")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows">&#11019;</span></td><td ontouchstart='onTouchStartAndEnd("2")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows">&#8681;</span></td><td ontouchstart='onTouchStartAndEnd("8")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows">&#11018;</span></td></tr></table><div class="speedcontainer"><input type="range" value="125" min="0" max="255" id="speedrange"><output id="speedrangeoutput">125</output></div><script>var webSocketUrl = "ws:\/\/" + window.location.hostname + "/ws"; var websocket; function initWebSocket() { websocket = new WebSocket(webSocketUrl); websocket.onopen = function (event) {}; websocket.onclose = function (event) { setTimeout(initWebSocket, 2000); }; websocket.onmessage = function (event) {}; } function onTouchStartAndEnd(value) { websocket.send(value); } const speedRange = document.getElementById("speedrange"); speedRange.oninput = function () { document.getElementById("speedrangeoutput").value = speedRange.value; websocket.send("S" + speedRange.value); }; window.onload = initWebSocket; document .getElementById("mainTable") .addEventListener("touchend", function (event) { event.preventDefault(); });</script></body></html>
)HTMLHOMEPAGE";

void processCarMovement(String inputValue) {
    Serial.printf("Got value as %s %d\n", inputValue.c_str(), inputValue.toInt());

    if (inputValue[0] == 'S') {
        String sSpeed = inputValue.substring(1);
        int speed = sSpeed.toInt();
        motors1.setSpeed(speed);
        motors2.setSpeed(speed);
        Serial.printf("Setting Speed to %d\n", speed);
        return;
    }

    switch (inputValue.toInt()) {

    case UP:
        motors1.forward();
        motors2.forward();
        break;

    case DOWN:
        motors1.backward();
        motors2.backward();
        break;

    case LEFT:
        motors1.forwardB();
        motors1.backwardA();
        motors2.forwardB();
        motors2.backwardA();
        break;

    case RIGHT:
        motors1.forwardA();
        motors1.backwardB();
        motors2.forwardA();
        motors2.backwardB();
        break;

    case STOP:
        motors1.stop();
        motors2.stop();
        break;

    default:
        break;
    }
}

void handleRoot(AsyncWebServerRequest* request) {
    request->send_P(200, "text/html", htmlHomePage);
}

void handleNotFound(AsyncWebServerRequest* request) {
    request->send(404, "text/plain", "File Not Found");
}

void onWebSocketEvent(AsyncWebSocket* server,
                      AsyncWebSocketClient* client,
                      AwsEventType type,
                      void* arg,
                      uint8_t* data,
                      size_t len) {
    switch (type) {
    case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        // client->text(getRelayPinsStatusJson(ALL_RELAY_PINS_INDEX));
        break;
    case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        processCarMovement("0");
        break;
    case WS_EVT_DATA:
        AwsFrameInfo* info;
        info = (AwsFrameInfo*)arg;
        if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
            std::string myData = "";
            myData.assign((char*)data, len);
            processCarMovement(myData.c_str());
        }
        break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    default:
        break;
    }
}

void setup(void) {
    Serial.begin(115200);

    motors1.setSpeed(255);
    motors2.setSpeed(255);

    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    server.on("/", HTTP_GET, handleRoot);
    server.onNotFound(handleNotFound);

    ws.onEvent(onWebSocketEvent);
    server.addHandler(&ws);

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    ws.cleanupClients();
}
