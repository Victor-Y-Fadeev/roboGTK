#pragma once

#include <stdint.h>


/*
 *	┌───────────────>
 *	│ (0, 0)
 *	│
 *	│
 *	\/				┘
 *					  (9000, 6000)
 */
#define MAX_WIDTH	9000.0	/* mm */
#define MAX_HEIGHT	6000.0	/* mm */

#define MAX_ROBOTS	12


#ifdef __cplusplus
extern "C" {
#endif

/**
 *	Initialize logic and robots
 */
void init();

/**
 *	Move robots
 */
void move();


/**
 *	Get ball coordinates
 *
 *	@param	x			X coordinate
 *	@param	y			Y coordinate
 */
void ball(double *x, double *y);

/**
 *	Get robot coordinates
 *
 *	@param	num			Robot number
 *	@param	x			X coordinate
 *	@param	y			Y coordinate
 *	@param	angle		Speed vector angle
 *
 *	@return	@c 1 on robot stop, @c 0 on otherwise
 */
int robot(uint8_t num, double *x, double *y, double *angle);

#ifdef __cplusplus
} /* extern "C" */
#endif
