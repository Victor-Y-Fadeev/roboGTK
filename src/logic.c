#include "logic.h"
#include <stddef.h>
#include <time.h>


/** Robot data structure */
typedef struct data
{
	double x;			/**< X coordinate */
	double y;			/**< Y coordinate */

	double x_speed;		/**< X speed vector coordinate (mm/sec) */
	double y_speed;		/**< Y speed vector coordinate (mm/sec) */
} data;


/* Last update time */
struct timespec last;

/* Robot coordinates array */
data robots[MAX_ROBOTS];

/* Ball coordinates */
double x_ball;
double y_ball;


/*
 *	 __     __   __     ______   ______     ______     ______   ______     ______     ______
 *	/\ \   /\ "-.\ \   /\__  _\ /\  ___\   /\  == \   /\  ___\ /\  __ \   /\  ___\   /\  ___\
 *	\ \ \  \ \ \-.  \  \/_/\ \/ \ \  __\   \ \  __<   \ \  __\ \ \  __ \  \ \ \____  \ \  __\
 *	 \ \_\  \ \_\\"\_\    \ \_\  \ \_____\  \ \_\ \_\  \ \_\    \ \_\ \_\  \ \_____\  \ \_____\
 *	  \/_/   \/_/ \/_/     \/_/   \/_____/   \/_/ /_/   \/_/     \/_/\/_/   \/_____/   \/_____/
 */


void init()
{
	clock_gettime(CLOCK_MONOTONIC_RAW, &last);
}

void move()
{
	struct timespec current;
	clock_gettime(CLOCK_MONOTONIC_RAW, &current);

	double sec = current.tv_sec - last.tv_sec + (double)(current.tv_nsec - last.tv_nsec) / 1000000000;
	last = current;
}


void ball(double *x, double *y)
{
	*x = x_ball;
	*y = y_ball;
}

int robot(uint8_t num, double *x, double *y, double *angle)
{
	if (x == NULL || y == NULL || angle == NULL)
	{
		return -1;
	}

	*x = robots[num].x;
	*y = robots[num].y;
	//*angle;
}
