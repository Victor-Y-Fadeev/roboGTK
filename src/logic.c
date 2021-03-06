#include "logic.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
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


	const double speed = 100;

	int x_cur = 0;
	int x_inc = 1;

	int y_cur = -3;
	int y_inc = 1;

	for (uint8_t i = 0; i < MAX_ROBOTS; i++)
	{
		robots[i].x = i < MAX_ROBOTS / 2 ? 0 : MAX_WIDTH / 2;
		robots[i].x += (1 + i % 2) * MAX_WIDTH / 6;

		const int half = ceil((double)MAX_ROBOTS / 2);
		const int quarter = ceil((double)MAX_ROBOTS / 4);
		robots[i].y = (1 + (i % half) / 2) * MAX_HEIGHT / (1 + quarter);

		robots[i].x_speed = x_cur * speed;
		x_cur += x_inc;
		x_inc *= abs(x_cur) == 3 ? -1 : 1;

		robots[i].y_speed = y_cur * speed;
		y_cur += y_inc;
		y_inc *= abs(y_cur) == 3 ? -1 : 1;
	}


	clock_gettime(CLOCK_MONOTONIC, &last);
}

void move()
{
	struct timespec current;
	clock_gettime(CLOCK_MONOTONIC, &current);

	double sec = current.tv_sec - last.tv_sec + (double)(current.tv_nsec - last.tv_nsec) / 1000000000;
	last = current;


	for (uint8_t i = 0; i < MAX_ROBOTS; i++)
	{
		robots[i].x += robots[i].x_speed * sec;

		if (robots[i].x < 0 || robots[i].x > MAX_WIDTH)
		{
			robots[i].x_speed *= -1;
			robots[i].x += robots[i].x_speed * sec;
		}

		robots[i].y += robots[i].y_speed * sec;

		if (robots[i].y < 0 || robots[i].y > MAX_HEIGHT)
		{
			robots[i].y_speed *= -1;
			robots[i].y += robots[i].y_speed * sec;
		}
	}
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

	if (fabs(robots[num].x_speed) < 0.000001 && fabs(robots[num].y_speed) < 0.000001)
	{
		return 1;
	}

	*angle = fabs(robots[num].x_speed) < 0.000001
			? robots[num].y_speed > 0 ? M_PI : 0
			: robots[num].x_speed > 0
				? atan(robots[num].y_speed / robots[num].x_speed) + M_PI / 2
				: atan(robots[num].y_speed / robots[num].x_speed) - M_PI / 2;
	return 0;
}
