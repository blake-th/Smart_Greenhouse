#include <Servo.h>

#include <OneWire.h> // temperature
#include <DallasTemperature.h> // temperature

const int BAUD_RATE = 9600;

const int SERVO_NUM = 4;
const int SERVO_PULSE_WIDTH_MIN = 600;
const int SERVO_PULSE_WIDTH_MAX = 2400;
const int SERVO_PIN[SERVO_NUM] = {9, 10, 11, 6};
Servo servo[SERVO_NUM];

const int TEMPERATURE_ONE_WIRE_BUS = 2;
const int TEMPERATURE_DELAY = 50000;
const float TEMPERATURE_THRESHOLD = 31.0;
OneWire temperature_one_wire(TEMPERATURE_ONE_WIRE_BUS);
DallasTemperature temperature_sensor(&temperature_one_wire);

const int MOISTURE_THRESHOLD = 750;
const int MOISTURE_PIN = A0;
const int MOISTURE_DELAY = 50000;

const int LUMINANCE_ARRAY_LENGTH = 9;
const float LUMINANCE_VOUT[LUMINANCE_ARRAY_LENGTH] = {0.0011498, 0.0033908, 0.011498, 0.041803, 0.15199, 0.53367, 1.3689, 1.9068, 2.3};
const float LUMINANCE_LUX[LUMINANCE_ARRAY_LENGTH] = {1.0108, 3.1201, 9.8051, 27.43, 69.545, 232.67, 645.11, 73.52, 1000};
const int LUMINANCE_PIN = A1;

void servo_init() {
    // DONE
    for (int i = 0; i < SERVO_NUM; ++i) {
        servo[i].attach(SERVO_PIN[i], SERVO_PULSE_WIDTH_MIN, SERVO_PULSE_WIDTH_MAX);
    }
    return;
}

void moisture_init() {
    // DONE
    pinMode(MOISTURE_PIN, INPUT);
    return;
}

void temperature_init() {
    // DONE
    temperature_sensor.begin();
    return;
}


void sense_moisture() {
    int sensor_value = analogRead(MOISTURE_PIN);
    if (sensor_value < MOISTURE_THRESHOLD) {
        // TODO
        // wet
        Serial.println("wet");
    } else {
        // TODO
        // dry
        Serial.println("dry");
    }
    return;
}

void sense_temperature() {
    temperature_sensor.requestTemperatures();
    float sensor_value = temperature_sensor.getTempCByIndex(0);
    if (sensor_value < TEMPERATURE_THRESHOLD) {
        // TODO
        // cold
        Serial.println("cold");

    } else {
        // TODO
        // HOT
        Serial.println("hot");
    }
    return;
}

void sense_luminance() {
    float sensed_vout = analogRead(LUMINANCE_PIN) * (3.0 / 1023.0);
    float sensor_value = FmultiMap(sensed_vout, LUMINANCE_VOUT, LUMINANCE_LUX, LUMINANCE_ARRAY_LENGTH);
    if (sensor_value < LUMINANCE_THRESHOLD) {
        // TODO
        // dark
        Serial.println("dark");
    } else {
        // TODO
        // bright
        Serial.println("bright");
    }
    return;
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


void setup() {
    Serial.begin(BAUD_RATE);

    servo_init();
    moisture_init();
    temperature_init();
    return;
}

void loop() {
    sense_temperature();
    sense_moisture();
    sense_luminance();
    delay(1500);
    return;
}

