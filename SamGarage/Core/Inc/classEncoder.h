/*
 * encoder.h
 *
 *  Created on: Mar 1, 2021
 *      Author: 123
 */

#ifndef SRC_ENCODER_H_
#define SRC_ENCODER_H_


class Encoder
{
private:
	int counts;					//сколько крутнул
	bool turned;				// было ли кручение

public:
	Encoder();

	void tick(int*);
	int getOneStep();
	bool isLeft();
	bool isRight();
	int getAllSteps();
	bool available();
	void clearSteps(void);
};

#endif /* SRC_ENCODER_H_ */
