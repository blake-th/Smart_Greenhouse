#include <Servo.h>

#include <OneWire.h> // temperature
#include <DallasTemperature.h> // temperature

const int BAUD_RATE = 9600;

const int SERVO_NUM = 2;
const int SERVO_PULSE_WIDTH_MIN = 600;
const int SERVO_PULSE_WIDTH_MAX = 2400;
const int SERVO_PIN[SERVO_NUM] = {10, 11};
Servo servo[SERVO_NUM];
char roof_state = 'c';


const int SERIAL_BUFFER_SIZE = 13;
byte serial_buffer[SERIAL_BUFFER_SIZE];

const int TEMPERATURE_ONE_WIRE_BUS = 2;
const int TEMPERATURE_DELAY = 50000;
const float TEMPERATURE_THRESHOLD = 28.0;
float average_temperature = 26.0;
OneWire temperature_one_wire(TEMPERATURE_ONE_WIRE_BUS);
DallasTemperature temperature_sensor(&temperature_one_wire);

const int MOISTURE_THRESHOLD = 750;
const int MOISTURE_PIN = A0;
const int MOISTURE_DELAY = 50000;
int average_moisture = 900;

const int LUMINANCE_ARRAY_LENGTH = 9;
const float LUMINANCE_VOUT[LUMINANCE_ARRAY_LENGTH] = {0.0011498, 0.0033908, 0.011498, 0.041803, 0.15199, 0.53367, 1.3689, 1.9068, 2.3};
const float LUMINANCE_LUX[LUMINANCE_ARRAY_LENGTH] = {1.0108, 3.1201, 9.8051, 27.43, 69.545, 232.67, 645.11, 73.52, 1000};
const int LUMINANCE_PIN = A1;
const float LUMINANCE_THRESHOLD = 10.0;
float average_luminance = 30.0;

const int FAN_PIN = 7;
const int LIGHT_PIN = 4;
const int PUMP_PIN = 8;

void servo_init() {
    // DONE
    for (int i = 0; i < SERVO_NUM; ++i) {
        servo[i].attach(SERVO_PIN[i], SERVO_PULSE_WIDTH_MIN, SERVO_PULSE_WIDTH_MAX);
    }

    servo[0].write(0);
    servo[1].write(180);

    return;
}

void check_roof() {
    bool change;
    String buf;
    if (Serial.available() > 0) {
        buf = Serial.readString();
        change = buf[0] != roof_state;
        roof_state = buf[0];
    } else {

    }

    if (change) {
        if (roof_state == 'c') {
            servo[0].write(0);
            servo[1].write(180);
        } else if (roof_state == 'o') {
            servo[0].write(90);
            servo[1].write(90);
        }
    } else {

    }

    //Serial.print(roof_state);
    return;
}

void communiaction_init() {
    Serial.begin(BAUD_RATE);
    return;
}

void moisture_init() {
    // DONE
    pinMode(MOISTURE_PIN, INPUT);
    pinMode(PUMP_PIN, OUTPUT);
    return;
}

void temperature_init() {
    // DONE
    temperature_sensor.begin();
    pinMode(FAN_PIN, OUTPUT);
    return;
}

void luminance_init() {
    pinMode(LIGHT_PIN, OUTPUT);
    return;
}


int sense_moisture() {
    int sensor_value = analogRead(MOISTURE_PIN);
    average_moisture = (9 * average_moisture + sensor_value) / 10;
    if (average_moisture < MOISTURE_THRESHOLD) {
        // TODO
        // wet
        //Serial.print("wet: ");
        actuate_pump(false);
    } else {
        // TODO
        // dry
        //Serial.print("dry: ");
        actuate_pump(true);
    }
    //Serial.println(average_moisture);
    return average_moisture;
}

float sense_temperature() {
    temperature_sensor.requestTemperatures();
    float sensor_value = temperature_sensor.getTempCByIndex(0);
    average_temperature = 0.9 * average_temperature + 0.1 * sensor_value;
    if (average_temperature < TEMPERATURE_THRESHOLD) {
        // TODO
        // cold
        //Serial.print("cold: ");
        actuate_fan(false);
    } else {
        // TODO
        // HOT
        //Serial.print("hot: ");
        actuate_fan(true);
    }
    //Serial.println(average_temperature);
    return average_temperature;
}

float sense_luminance() {
    float sensed_vout = analogRead(LUMINANCE_PIN) * (3.0 / 1023.0);
    float sensor_value = FmultiMap(sensed_vout, LUMINANCE_VOUT, LUMINANCE_LUX, LUMINANCE_ARRAY_LENGTH);
    average_luminance = 0.9 * average_luminance + 0.1 * sensor_value;
    if (average_luminance < LUMINANCE_THRESHOLD) {
        // TODO
        // dark
        //Serial.print("dark: ");
        actuate_light(true);
    } else {
        // TODO
        // bright
        //Serial.print("bright: ");
        actuate_light(false);
    }
    //Serial.println(average_luminance);
    return average_luminance;
}


float FmultiMap(float val, float* _in, float* _out, uint8_t size) {
    // take care the value is within range
    // val = constrain(val, _in[0], _in[size-1]);
    if (val <= _in[0]) return _out[0];
    if (val >= _in[size-1]) return _out[size-1];

    // search right interval
    uint8_t pos = 1;  // _in[0] allready tested
    while(val > _in[pos]) pos++;

    // this will handle all exact "points" in the _in array
    if (val == _in[pos]) return _out[pos];

    // interpolate in the right segment for the rest
    return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}

void actuate_fan(bool turn_on) {
    if (turn_on) {
        digitalWrite(FAN_PIN, HIGH);
    } else {
        digitalWrite(FAN_PIN, LOW);
    }
    return;
}

void actuate_light(bool turn_on) {
    if (turn_on) {
        digitalWrite(LIGHT_PIN, HIGH);
    } else {
        digitalWrite(LIGHT_PIN, LOW);
    }
    return;
}

void actuate_pump(bool turn_on) {
    if (turn_on) {
        digitalWrite(PUMP_PIN, HIGH);
    } else {
        digitalWrite(PUMP_PIN, LOW);
    }
    return;
}

void send_sensor_value() {
    Serial.print("T ");
    Serial.print(sense_temperature());
    Serial.print(" M ");
    Serial.print(sense_moisture());
    Serial.print(" L ");
    Serial.print(sense_luminance());
    Serial.print('\n');
    return;
}

void setup() {
    communiaction_init();
    servo_init();
    moisture_init();
    temperature_init();
    luminance_init();
    delay(10000);
    return;
}

void loop() {
    check_roof();
    send_sensor_value();
    delay(500);
    return;
}

