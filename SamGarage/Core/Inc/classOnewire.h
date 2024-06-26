/*
 * classOnewire.h
 *
 *  Created on: Apr 6, 2021
 *      Author: Lomaster
 *      класс для термодатчиков ds18b20
 *      инициализация указатель на таймер, порт, пин, указательна массив ROM датчика.
 *      Таймер настроить на частоту 1 Мгц => 1 тик = 1 микросек.
 *      1 инициализируем
 *      2 устанавливаем разрешение АЦП если надо 9-12 бит
 *      3 запускаем датчик.convertALL(); тут если все датчики на одном пине то функция для всех одна
 *      	т.е. создаем столько классов сколько датчиков и от любого класса эта функция заставит
 *      	все датчики начать конверсию
 *      4 датчик.getTemperature(); вернет float температуру в цельсиях
 *      далее опять пункт 3, желательно расчитывать по времени преобразования из даташита
 *
 *      в переменных status и trouble сотояние дачика энумерации wire_status и ds_error
 *      criticalEror становится в true если время ошибки превысило DS_MAX_ERROR_TIME, по умолчанию 5000 милисек
 *
 *      status == wireGotPulse && trouble == ds_ok  все хорошо работает
 *      status == wireNoPresentPulse && trouble == ds_error_noRespond нед дачиков на линии или обрыв или др
 *      status == wireLineBusy && trouble == ds_error_line шина данных закорочена на землю
 *      status == wireGotPulse && trouble == ds_error_crc с шиной все хорошо
 *      	 и есть дачики но память конкретно этого читается неправлильно или он отсутствует / отошел
 *
 *      если вызывать раньше чем срабатывает преобразование возможны ошибки чтения
 *      после вызовов функций .convertALL() и .getTemperature() сотояние status разное
 */

#ifndef SRC_CLASSONEWIRE_H_
#define SRC_CLASSONEWIRE_H_

#define DS_CMD_READ_RAM				0xBE
#define DS_CMD_WRITE_RAM			0x4E
#define DS_CMD_COPY_RAM				0x48
#define DS_CMD_REC_EEPROM			0xB8
#define DS_CMD_RPW_RSUPPLY			0xB4
#define DS_CMD_SEARCH_ROM			0xF0
#define DS_CMD_READ_ROM				0x33
#define DS_CMD_MATCH_ROM			0x55
#define DS_CMD_SKIP_ROM				0xCC
#define DS_CMD_CONVERT				0x44

#define DS_TEMP_LSB        0
#define DS_TEMP_MSB        1
#define DS_HIGH_ALARM_TEMP 2
#define DS_LOW_ALARM_TEMP  3
#define DS_CONFIGURATION   4
#define DS_INTERNAL_BYTE   5
#define DS_COUNT_REMAIN    6
#define DS_COUNT_PER_C     7
#define DS_SCRATCHPAD_CRC  8

// DSROM FIELDS
#define DS_ROM_FAMILY    0
#define DS_ROM_CRC       7
#define DS_RAM_CRC       8
#define DS_ROM_LEN       8
#define DS_RAM_LEN       9

// Device resolution
#define DS_RES_9_BIT  0x1F //  9 bit
#define DS_RES_10_BIT 0x3F // 10 bit
#define DS_RES_11_BIT 0x5F // 11 bit
#define DS_RES_12_BIT 0x7F // 12 bit

#define DS_MAX_ERROR_TIME 5000

#include "stm32f1xx_hal.h"
#include "externs.h"




class classOnewire {
private:
	TIM_HandleTypeDef myTim; // таймер настраивается 1 тик = 1 микросек = 1 000 000 тиков в 1 сек
	GPIO_TypeDef * port;

	uint8_t ramData[9] = {0};
	uint8_t romData[8] = {0};
	uint16_t pin;
	bool stable;
	float lastTemp;
	uint32_t stableTime; //set ms
	uint32_t lastTimeUpTemp;
	bool resetPulse();
	bool readBit(void);
	bool checkLine();
	bool matchRom();
	void writeBit(uint8_t bit);
	void writeByte(uint8_t b);
	uint8_t readByte(void);
	uint8_t checkCRS(uint8_t * arr, int lenght);
	void calculateTemperarute();
	void error();

public:
	wireStatus status;
	ds_error trouble;
	float temperature;
	bool criticalEror;
	uint32_t errorLineTime;
	uint32_t errorLineCount;
	uint32_t errorRomCrcCount;
	uint32_t errorRomCrcTime;
	uint32_t errorRamCrcCount;
	uint32_t errorRamCrcTime;
	uint32_t errorNoPulseTime;
	uint32_t errorNoPulseCount;
	classOnewire();
	classOnewire(TIM_HandleTypeDef *timer, GPIO_TypeDef * WirePort, uint16_t WirePin, uint8_t *data);
	bool isStable();
	void setStableCheckTimeSec(uint16_t sec);
	void checkStability();
	bool isConversionComplete();
	bool readRom();
	bool setResolution(uint8_t res);
	bool readRam();
	float getTemperature();
	void convertALL();
	void setRom(uint8_t * data);
	const uint8_t* getRamData() const {	return ramData;	}// ROM
	const uint8_t* getRomData() const {	return romData;	}//			RAM
	uint8_t* getRom();
};

#endif /* SRC_CLASSONEWIRE_H_ */
