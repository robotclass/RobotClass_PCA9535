/*!
 *  @file RobotClass_PCA9535.h
 *  GPIO Extender PCA9535 library
 *  Written by Oleg Evsegneev for RobotClass (2022).
 *  e-mail: oleg.evsegneev@gmail.com
 */
 
#include <Arduino.h>
#include <Wire.h>

#define INVERTED 1

#define BASE_I2C_ADDR 0x27

#define INPUT_PORT_0 0x00
#define INPUT_PORT_1 0x01
#define OUTPUT_PORT_0 0x02
#define OUTPUT_PORT_1 0x03
#define POLARITY_INVERSION_PORT_0 0x04
#define POLARITY_INVERSION_PORT_1 0x05
#define CONFIGURATION_PORT_0 0x06
#define CONFIGURATION_PORT_1 0x07

class RobotClass_PCA9535 {
	union ports {
		uint16_t w;
		uint8_t b[2];
	};

	TwoWire* _wire = NULL;
	uint8_t _addr = BASE_I2C_ADDR;

    ports _input {0x0000};
    ports _output {0xFFFF};
    ports _pol {0x0000};
    ports _dir {0xFFFF};

	uint8_t _status = 0x00;

public:
	RobotClass_PCA9535();
	void begin(uint8_t addr = BASE_I2C_ADDR, TwoWire *wire = &Wire);
	uint8_t digitalRead( uint8_t pin );
	uint16_t read();
	bool digitalWrite( uint8_t pin, uint8_t level );
	bool write(const uint16_t value);
	bool invertPin(uint8_t pin, uint8_t pol);
	bool polarity(const uint16_t value);
	bool pinMode( uint8_t pin, uint8_t mode );
	bool direction(const uint16_t value);
	uint8_t i2c_error();

private:
    bool write_impl();
    bool polarity_impl();
    bool direction_impl();
    int8_t read_bytes(const uint8_t dev, const uint8_t reg, uint8_t* data, const uint8_t size);
    bool write_bytes(const uint8_t dev, const uint8_t reg, const uint8_t* data, const uint8_t size);
};
