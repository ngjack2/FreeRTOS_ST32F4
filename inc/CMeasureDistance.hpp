/*
 * CMeasureDistance.hpp
 *
 *  Created on: Feb 28, 2021
 *      Author: 1000086162
 */

#ifndef CMEASUREDISTANCE_HPP_
#define CMEASUREDISTANCE_HPP_


class CMeasureDistance
{
public:
	UINT32 RunMeasureDistance(void);

private:
	void initGPIOForUltraSonic(void);
	void startTriggerMode(void);

	UINT32 readBackEchoTiming(void);
};


#endif /* CMEASUREDISTANCE_HPP_ */
