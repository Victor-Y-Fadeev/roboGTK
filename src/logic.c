#include "logic.h"
#include <math.h>
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
	x_ball = MAX_WIDTH / 2;
	y_ball = MAX_HEIGHT / 2;

	for (uint8_t i = 0; i < MAX_ROBOTS; i++)
	{
		robots[i].x = i < MAX_ROBOTS / 2 ? 0 : MAX_WIDTH / 2;
		robots[i].x += (1 + i % 2) * MAX_WIDTH / 6;

		const int half = ceil((double)MAX_ROBOTS / 2);
		const int quarter = ceil((double)MAX_ROBOTS / 4);
		robots[i].y = (1 + (i % half) / 2) * MAX_HEIGHT / (1 + quarter);

		robots[i].x_speed = 0;
		robots[i].y_speed = 1;
	}

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

	if (robots[num].x_speed < 0.000001 && robots[num].y_speed < 0.000001)
	{
		return 1;
	}

	*angle = 1;
	return 0;
}
