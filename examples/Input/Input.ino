#include <RobotClass_PCA9535.h>

RobotClass_PCA9535 pca;

void setup() {
    Serial.begin(9600);
    delay(2000);

    pca.begin(0x27);
    pca.pinMode(15, INPUT);
}

void loop() {
    byte value = pca.digitalRead(15); 
    Serial.println(value);
    delay(1000);
}