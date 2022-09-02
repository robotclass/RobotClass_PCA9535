#include <RobotClass_PCA9535.h>

RobotClass_PCA9535 pca;

// к этому контакту Arduino подключен встроенный светодиод
const byte ledPin = 13;

// к этому контакту расширителя подключена кнопка
const byte btnPin = 0;

// к этому контакту Arduino подключен контакт INT расширителя
const byte arduinoIntPin = 3;

// на 3-м контакте Arduino обслуживается прерывание №1
const byte arduinoInterrupt = 1;

// переменная - флаг, которая примет значение true
// при возникновении прерывания
volatile boolean awakenByInterrupt = false;

void setup(){
    // настраиваем режим контакта для прерывания Arduino
    pinMode(arduinoIntPin, INPUT);

    // инициализируем расширитель с адресом 0x27
    pca.begin(0x27);
    // настраиваем режим контакта для кнопки
    pca.pinMode(btnPin, INPUT);

    // настраиваем режим контакта для светодиода
    pinMode(ledPin, OUTPUT);
    // активируем прерывание Arduino под номером arduinoInterrupt
    // с вызовом функции intCallBack
    // в режиме детектирования спада импульса - FALLING
    attachInterrupt(arduinoInterrupt,intCallBack,FALLING);
}

// обработчик прерывания Arduino
void intCallBack(){
    awakenByInterrupt = true;
}

void handleInterrupt(){
    // отключаем прерывание на время пока выполняется обработчик
    detachInterrupt(arduinoInterrupt);

    // мигаем один раз светодиодом
    digitalWrite(ledPin,HIGH);
    delay(100);
    digitalWrite(ledPin,LOW);
    delay(100);

    // ждём, пока кнопку не отпустят
    while( pca.digitalRead(btnPin) == HIGH);
    // сбрасываем флаг нажатия
    awakenByInterrupt = false;

    // включаем прерывание обратно
    attachInterrupt(arduinoInterrupt,intCallBack,FALLING);
}

void loop(){
    // если прерывание сработало и флаг истина
    if(awakenByInterrupt){
        // делаем, что задумали
        handleInterrupt();
    }
}
