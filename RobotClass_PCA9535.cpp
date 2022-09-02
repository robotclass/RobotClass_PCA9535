/*!
 *  @file RobotClass_PCA9535.h
 *  GPIO Extender PCA9535 library
 *  Written by Oleg Evsegneev for RobotClass (2022).
 *  e-mail: oleg.evsegneev@gmail.com
 */
#include "RobotClass_PCA9535.h"

RobotClass_PCA9535::RobotClass_PCA9535(){
}

void RobotClass_PCA9535::begin(uint8_t addr, TwoWire *wire){
	_wire = wire;
	_addr = addr;
	
	_wire->begin();
}

uint8_t RobotClass_PCA9535::digitalRead( uint8_t pin ) {
	uint16_t v = read();
	return (v & (1 << pin)) ? HIGH : LOW;
}

uint16_t RobotClass_PCA9535::read() {
	read_bytes(_addr, INPUT_PORT_0, _input.b, 2);
	return _input.w;
}

bool RobotClass_PCA9535::digitalWrite( uint8_t pin, uint8_t level ) {
	if (level) {
		_output.w |= (1 << pin);
	} else {
		_output.w &= ~(1 << pin);
	}
	return write_impl();
}

bool RobotClass_PCA9535::write(const uint16_t value) {
	_output.w = value;
	return write_impl();
}

bool RobotClass_PCA9535::invertPin(uint8_t pin, uint8_t pol) {
	if (pol == INVERTED) {
		_pol.w |= (1 << pin);
	} else {
		_pol.w &= ~(1 << pin);
	}
	return polarity_impl();
}
	
bool RobotClass_PCA9535::polarity(const uint16_t value) {
	_pol.w = value;
	return polarity_impl();
}

bool RobotClass_PCA9535::pinMode( uint8_t pin, uint8_t mode ){
	if( !mode ){
		_dir.w |= (1 << pin);
	} else {
		_dir.w &= ~(1 << pin);
	}
	return direction_impl();
}

bool RobotClass_PCA9535::direction(const uint16_t value) {
	_dir.w = value;
	return direction_impl();
}

uint8_t RobotClass_PCA9535::i2c_error() {
	return _status;
}

bool RobotClass_PCA9535::write_impl() {
	return write_bytes(_addr, OUTPUT_PORT_0, _output.b, 2);
}

bool RobotClass_PCA9535::polarity_impl() {
	return write_bytes(_addr, POLARITY_INVERSION_PORT_0, _pol.b, 2);
}

bool RobotClass_PCA9535::direction_impl() {
	return write_bytes(_addr, CONFIGURATION_PORT_0, _dir.b, 2);
}

int8_t RobotClass_PCA9535::read_bytes(const uint8_t dev, const uint8_t reg, uint8_t* data, const uint8_t size) {
	_wire->beginTransmission(dev);
	_wire->write(reg);
	_wire->endTransmission();
	_wire->requestFrom(dev, size);
	int8_t count = 0;
	while (_wire->available()) data[count++] = _wire->read();
	return count;
}

bool RobotClass_PCA9535::write_bytes(const uint8_t dev, const uint8_t reg, const uint8_t* data, const uint8_t size) {
	_wire->beginTransmission(dev);
	_wire->write(reg);
	for (uint8_t i = 0; i < size; i++) _wire->write(data[i]);
	_status = _wire->endTransmission();
	return (_status == 0);
}
