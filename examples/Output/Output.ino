#include <RobotClass_PCA9535.h>

RobotClass_PCA9535 pca;

void setup() {
    pca.begin(0x27);
    pca.pinMode(15, OUTPUT);
}

void loop() {
    pca.digitalWrite(15, HIGH);
    delay(3000);
    pca.digitalWrite(15, LOW);
    delay(3000);    
}