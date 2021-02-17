/*
 * distanceMeasure.h
 *
 *  Created on: Nov 20, 2020
 *      Author: 1000086162
 */

#ifndef INC_DISTANCEMEASURE_H_
#define INC_DISTANCEMEASURE_H_

__externC UINT8 objDistance;

__externC void IrqPC13Handler(void);
__externC UINT32 MeasureDistance(void);

#endif /* INC_DISTANCEMEASURE_H_ */
