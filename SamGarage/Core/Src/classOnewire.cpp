/*
 * classOnewire.cpp
 *
 *  Created on: Apr 6, 2021
 *      Author: 123
 */
// 	победы 72 кв 28

#include "classOnewire.h"

classOnewire::classOnewire() {
	// TODO Auto-generated constructor stub

}

classOnewire::classOnewire(TIM_HandleTypeDef *timer, GPIO_TypeDef *WirePort, uint16_t WirePin, uint8_t *data) {
	myTim = *timer;
	port = WirePort;
	pin = WirePin;
	stable = false;
	lastTemp = 0.0;
	stableTime = 180000; // 180 sec defoult = 3 min
	HAL_TIM_Base_Start(&myTim);
	this->status = wireReady;
	this->temperature = 0.0;
	this->criticalEror = false;
	this->errorRomCrcCount = 0;
	this->errorRomCrcTime = 0;
	this->errorRamCrcCount = 0;
	this->errorRamCrcTime = 0;
	this->errorLineCount = 0;
	this->errorLineTime = 0;
	this->errorNoPulseTime = 0;
	this->errorNoPulseCount = 0;
	this->status = wireReady;
	this->trouble = ds_ok;

	for(int i = 0; i < DS_ROM_LEN; i++)
		this->romData[i] = data[i];
	this->readRam();
}
//-----------------------------------------------------------------------
void classOnewire::writeBit(uint8_t bit) {
	myTim.Instance->CNT=0;
	port->ODR &= ~pin;                       //потянуть шину к земле
	while(myTim.Instance->CNT < 2);          //ждать 1 микросекунду
	if(bit) port->ODR |= pin;                //если передаем 1, то отпускаем шину
	while(myTim.Instance->CNT < 60);         //задержка 60 микросекунд
	port->ODR |= pin;                        //отпускаем шину
}
//-----------------------------------------------------------------------
bool classOnewire::readBit() {
	bool result = false;

	myTim.Instance->CNT=0;
	port->ODR &= ~pin;                          //потянуть шину к земле
	while(myTim.Instance->CNT < 2);				//ждать 1 микросекунду
	port->ODR |=  pin;                          //отпускаем шину
	while(myTim.Instance->CNT < 15);            //задержка 15 микросекунд
	if (port->IDR & pin) result = true;         //прочитать шину
	while(myTim.Instance->CNT < 60);            //оставшееся время
	return result;                              //возвратить результат
}
//-----------------------------------------------------------------------
void classOnewire::writeByte(uint8_t b) {
	uint8_t i;
	__disable_irq ();
	for(i = 0; i < 8; i++) this->writeBit(b & (1<<i));
	__enable_irq ();
}
//-----------------------------------------------------------------------
uint8_t classOnewire::readByte(void) {
	__disable_irq ();
	uint8_t i, result = 0;
	for(i = 0; i < 8; i++)
	if(this->readBit()) result |= 1<<i;
	__enable_irq ();
	return result;
}
//-----------------------------------------------------------------------
bool classOnewire::resetPulse() {
	uint16_t result = 0;

	if(!this->checkLine()) return false;	//проверить линию на отсутствие замыкания
	port->ODR &= ~pin;                   	//потянуть шину к земле
	myTim.Instance->CNT = 0;
	__disable_irq ();
	while(myTim.Instance->CNT < 485);       //ждать 480 микросекунд
	port->ODR |=  pin;                      //отпустить шину
    while(myTim.Instance->CNT < 555){};		//ждать 70 микросекунд
	result = port->IDR & pin;               //прочитать шину
	__enable_irq ();
	while(myTim.Instance->CNT < 960);       //дождаться окончания инициализации
	//while(!(port->IDR & pin));
	if(result) {							 //датчик не обнаружен
		this->status = wireNoPresentPulse;
		this->error();
		return false;
	}
	this->status = wireGotPulse;
	this->error();
	return true;							//получен импульс присутсвия
}
//-----------------------------------------------------------------------
bool classOnewire::isConversionComplete() {
	return (port->IDR & pin);
}
//-----------------------------------------------------------------------
bool classOnewire::readRam() {
	if (!this->matchRom()) return false;
	this->writeByte(DS_CMD_READ_RAM);
	for(int i = 0; i < DS_RAM_LEN; i++)
		ramData[i] = this->readByte();
	if (this->checkCRS(this->ramData, DS_RAM_LEN - 1) == ramData[DS_RAM_CRC]) {
		this->status = wireRamCrcOk;
		this->error();
		return true;
	}
	this->status = wireRamCrcError;
	this->error();
	return false;
}
//-----------------------------------------------------------------------
uint8_t classOnewire::checkCRS(uint8_t * mas, int Len) {

	    uint8_t i, dat, crc, fb, st_byt;
	    st_byt = 0;
	    crc = 0;
	    do {
	        dat = mas[st_byt];
	        for (i = 0; i < 8; i++) {  // счетчик битов в байте
	            fb = crc ^ dat;
	            fb &= 1;
	            crc >>= 1;
	            dat >>= 1;
	            if (fb == 1) crc ^= 0x8c; // полином
	        }
	        st_byt++;
	    } while (st_byt < Len); // счетчик байтов в массиве
	    return crc;
}
//-----------------------------------------------------------------------
void classOnewire::calculateTemperarute() {

	int temp = this->ramData[DS_TEMP_MSB];
	temp = temp << 8;
	temp |= this->ramData[DS_TEMP_LSB];
	this->temperature = temp * 0.0625;
}
//-----------------------------------------------------------------------
void classOnewire::convertALL() {
	if (!this->resetPulse()) return;	//если какаято ошибка стоп
	this->writeByte(DS_CMD_SKIP_ROM);
	this->writeByte(DS_CMD_CONVERT);
}
//-----------------------------------------------------------------------
float classOnewire::getTemperature() {
	this->readRam();
	if (this->status == wireRamCrcOk) this->calculateTemperarute();	//если новое измерение прошло
	this->checkStability();
	return this->temperature;										//если новых конверсий не было
}
//-----------------------------------------------------------------------
bool classOnewire::readRom() {

	if (!this->resetPulse()) return false;
	this->writeByte(DS_CMD_READ_ROM);
	for(int i = 0; i < DS_ROM_LEN; i++)
		this->romData[i] = this->readByte();
	if (this->checkCRS(this->romData, DS_ROM_LEN - 1) == romData[DS_ROM_CRC]) {
		this->status = wireRomCrcOk;
		this->error();
		return true;
	}
	this->status = wireRomCrcError;
	this->error();
	return false;
}
//-----------------------------------------------------------------------
void classOnewire::setRom(uint8_t *data) {
	for(int i = 0; i < DS_ROM_LEN; i++)
		this->romData[i] = data[i];
}
//-----------------------------------------------------------------------
bool classOnewire::setResolution(uint8_t res) {
	if (!this->matchRom()) return false ;
	this->writeByte(DS_CMD_WRITE_RAM);
	this->writeByte(ramData[DS_HIGH_ALARM_TEMP]);
	this->writeByte(ramData[DS_LOW_ALARM_TEMP]);
	ramData[DS_CONFIGURATION] = res;
	this->writeByte(ramData[DS_CONFIGURATION]);
	return true;
}
//-----------------------------------------------------------------------
bool classOnewire::checkLine() {
	bool result = false;
	if (port->IDR & pin){			//true если линия свободна
		this->status = wireReady;
		result = true;
	}
	else {
		result = false;
		this->status = wireLineBusy;
	}
	this->error();
	return result;
}
//-----------------------------------------------------------------------
void classOnewire::error() {

	switch (status)
	{
	case wireReady:
		this->errorLineTime = 0;
		break;
	case wireGotPulse:
		this->errorNoPulseTime = 0;
		break;
	case wireRomCrcOk:
		this->errorRomCrcTime = 0;
		break;
	case wireRamCrcOk:
		this->errorRamCrcTime = 0;
		break;
	case wireLineBusy:								//если  на лииии ноль

		if (this->trouble != ds_error_line) this->errorLineCount++;
		if (!this->errorLineTime) {					//если ошибки еще не было или была сброшена
			this->errorLineTime = HAL_GetTick();	//сохраняем время ошибки
			this->trouble = ds_error_line;
		}
		else if ((this->errorLineTime + DS_MAX_ERROR_TIME) < HAL_GetTick()) 	//выскочили за пределы допустимого времени на ошибку
			this->criticalEror = true;
		break;
	case wireRomCrcError:

		if (this->trouble != ds_error_crc) this->errorRomCrcCount++; //чтоб ошибки не прибавлялись каждый тик
		if (!this->errorRomCrcTime){
			this->errorRomCrcTime = HAL_GetTick();
			this->trouble = ds_error_crc;
		}
		else if ((this->errorRomCrcTime + DS_MAX_ERROR_TIME) < HAL_GetTick())
			this->criticalEror = true;
		break;
	case wireRamCrcError:
		if (this->trouble != ds_error_crc) this->errorRamCrcCount++;
		if (!this->errorRamCrcTime){
			this->errorRamCrcTime = HAL_GetTick();
			this->trouble = ds_error_crc;
		}
		else if ((this->errorRamCrcTime + DS_MAX_ERROR_TIME) < HAL_GetTick())
			this->criticalEror = true;

		break;
	case wireNoPresentPulse:
		if (this->trouble != ds_error_noRespond) this->errorNoPulseCount++;
		if (!this->errorNoPulseTime){
			this->errorNoPulseTime = HAL_GetTick();
			this->trouble = ds_error_noRespond;
		}
		else if ((this->errorNoPulseTime + DS_MAX_ERROR_TIME) < HAL_GetTick())
			this->criticalEror = true;
		break;

	}
	if (!(this->errorLineTime || this->errorNoPulseTime
			|| this->errorRamCrcTime || this->errorRomCrcTime)) this->trouble = ds_ok;

									// сброс критической ошибки только если все хорошо//
	if (this->criticalEror){
		this->criticalEror = (bool)(this->errorLineTime || this->errorNoPulseTime
				|| this->errorRamCrcTime || this->errorRomCrcTime);
		if (!this->criticalEror) this->trouble = ds_ok;
	}

}
//-----------------------------------------------------------------------
bool classOnewire::matchRom() {

	if (!this->resetPulse()) return false;
	this->writeByte(DS_CMD_MATCH_ROM);
	for(int i = 0; i < DS_ROM_LEN; i++) {
		this->writeByte(romData[i]);
	}
	return true;
}

bool classOnewire::isStable() { return stable; }

void classOnewire::setStableCheckTimeSec(uint16_t sec) { stableTime = sec * 1000; }

void classOnewire::checkStability()
{
	if (temperature > lastTemp) //если температура возросла значит еще не стабильна
	{
		lastTimeUpTemp = HAL_GetTick();
		stable = false;
		lastTemp = temperature;
		return;
	}
	if (temperature < lastTemp - 3.0) // eсли падает больше чем на три градуса
	{
		stable = false;
		lastTemp = temperature + 1;// +1 защита от предыдущего if ^^
		return;
	}
	//если не возросла то смотрим как долго держится
	uint32_t now = HAL_GetTick();
	if (lastTimeUpTemp + stableTime <= now)// темпера стабилизиловалась и не растет
	{
		stable = true;
	}
}

//-----------------------------------------------------------------------
uint8_t* classOnewire::getRom()
{
	return romData;
}


