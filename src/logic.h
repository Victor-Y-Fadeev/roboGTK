#pragma once


#define MAX_ROBOTS 12


#ifdef __cplusplus
extern "C" {
#endif

/*
 *	┌───────────────>
 *	│ (0, 0)
 *	│
 *	│
 *	\/				┘
 *					  (9000, 6000)
 */
const double MAX_WIDTH = 9000;	/* mm */
const double MAX_HEIGHT = 6000;	/* mm */


/**
 *	Initialize logic and robots
 */
void init();

/**
 *	Move robots
 */
void move();

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
int robot(int num, double *x, double *y, double *angle);

#ifdef __cplusplus
} /* extern "C" */
#endif
