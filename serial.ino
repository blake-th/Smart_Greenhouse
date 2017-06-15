const int BUFFER_SIZE = sizeof(char) * 3 + sizeof(double) * 2 + sizeof(int) + sizeof(' ') * 6 + sizeof('\n');

byte buffer[BUFFER_SIZE];

double t = 25.5;
int m = 780;
double l = 30.3;

void setup() {
    Serial.begin(9600);
    return;
}


void loop() {
        Serial.print("T ");
        Serial.print(t);
        Serial.print(" M ");
        Serial.print(m);
        Serial.print(" L ");
        Serial.print(l);
        Serial.print('\n');
    return;
}