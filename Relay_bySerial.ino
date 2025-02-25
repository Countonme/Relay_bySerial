/*****************************************************************************************************
 * 功能說明：
 * 通過串口下指令，控制4個繼電器切換
 * 指令表：
 *  R1_ON, R1_OFF, R2_ON, R2_OFF, R3_ON, R3_OFF, R4_ON, R4_OFF, ALL_ON, ALL_OFF
******************************************************************************************************/
const int IN2 = 2;
const int IN3 = 3;
const int IN4 = 4;
const int OUT1 = A5;
const String CMD_DOWN = "DOWN\n";
const String CMD_UP = "UP\n";
const String CMD_R2_ON = "R2_ON\r";
const String CMD_R2_OFF = "R2_OFF\r";
const String CMD_R3_ON = "R3_ON\r";
const String CMD_R3_OFF = "R3_OFF\r";
const String CMD_R4_ON = "R4_ON\r";
const String CMD_R4_OFF = "R4_OFF\r";
const String CMD_ALL_ON = "ALL_ON\r";
const String CMD_ALL_OFF = "ALL_OFF\r";
const String CMD_READ = "READ\n";
const String CMD_IDN = "*IDN?\n";

//设置状态
void setRelayState(int pin, bool state, const String& message) {
    digitalWrite(pin, state ? HIGH : LOW);
    Serial.println(message);
}
//初始化
void setup() {
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    Serial.begin(9600);
}

void loop() {
    String cmd = "";

    while (Serial.available() > 0) {
        cmd += char(Serial.read());
        delay(2);
    }


    if (cmd.length() > 0) {
       if (cmd == CMD_DOWN) {
           digitalWrite(IN4, HIGH);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            delay(200);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            Serial.println("machine is down....");
        } else if (cmd == CMD_UP) {
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            delay(100);
            digitalWrite(IN4, HIGH);
        } else if (cmd == CMD_R2_ON) {
            setRelayState(IN2, false, "Relay2 ON.");
        } else if (cmd == CMD_R2_OFF) {
            setRelayState(IN2, true, "Relay2 OFF.");
        } else if (cmd == CMD_R3_ON) {
            setRelayState(IN3, false, "Relay3 ON.");
        } else if (cmd == CMD_R3_OFF) {
            setRelayState(IN3, true, "Relay3 OFF.");
        } else if (cmd == CMD_R4_ON) {
            setRelayState(IN4, false, "Relay4 ON.");
        } else if (cmd == CMD_R4_OFF) {
            setRelayState(IN4, true, "Relay4 OFF.");
        } else if (cmd == CMD_ALL_ON) {
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, LOW);
            Serial.println("ALL ON.");
        } else if (cmd == CMD_ALL_OFF) {
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, HIGH);
            Serial.println("ALL OFF.");
        } else if (cmd == CMD_READ) {
            int Vol_value = analogRead(OUT1);
            float Vol_voltage = (Vol_value * 0.004828);
            Serial.println(Vol_voltage);
        } else if (cmd == CMD_IDN) {
            Serial.println("Relay");
        }

        cmd = "";
    }
}
