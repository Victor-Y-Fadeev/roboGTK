#include "surface.h"
#include <stdint.h>
#include "logic.h"


/** Color type */
typedef uint32_t color_t;


/* Default colors */
const color_t BACKGROUND = 0xC5E0B4;
const color_t LINE = 0xFFFFFF;
const color_t OBJECT = 0x262626;
const color_t FIRST = 0xFFD966;
const color_t SECOND = 0x9DC3E6;


/* Surface to store current scribbles */
cairo_surface_t *surface = NULL;

/* Current window size */
int width = 0;
int height = 0;


static inline void cairo_set_color(cairo_t *cr, color_t color)
{
	cairo_set_source_rgb(cr
		, (double)((color & 0xFF0000) >> 16) / 0xFF
		, (double)((color & 0x00FF00) >> 8) / 0xFF
		, (double)(color & 0x0000FF) / 0xFF);
}

static void draw_robot(cairo_t *cr, uint8_t num)
{
	/*cairo_set_color(cr, BACKGROUND);
	cairo_paint(cr);

	cairo_set_color(cr, LINE);
	cairo_rectangle(cr, 100, 100, 8800, 5800);
	cairo_fill(cr);*/

	//cairo_translate(cr, 100, 100);
	//cairo_scale(cr, 1.5, 1);
	//cairo_translate(cr, -100, -100);

	/*cairo_set_color(cr, LINE);
	cairo_rectangle(cr, 50, 50, 100, 100);
	cairo_rectangle(cr, 100, 100, 100, 100);
	cairo_fill(cr);

	cairo_destroy(cr);
	cr = cairo_create(surface);

	cairo_translate(cr, 100, 100);
	cairo_scale(cr, 1.5, 1);

	cairo_save(cr);
	cairo_rotate(cr, 1.5);
	cairo_set_color(cr, FIRST);
	cairo_rectangle(cr, -2.50, -6.50, 50, 50);
	cairo_fill(cr);
	cairo_restore(cr);

	cairo_set_color(cr, SECOND);
	cairo_rectangle(cr, -2.50, -6.50, 50, 50);
	cairo_fill(cr);*/
}

static void draw_ball(cairo_t *cr)
{

}

static void draw_field(cairo_t *cr)
{
	const double cm_width = 27;
	const double cm_height = 18;
	const double cm_line = 0.25;

	const double cm_gate_width = cm_width / 9 - cm_line;
	const double cm_gate_height = cm_height / 3;

	cairo_save(cr);
	cairo_scale(cr, MAX_WIDTH / cm_width, MAX_HEIGHT / cm_height);

	cairo_set_color(cr, BACKGROUND);
	cairo_paint(cr);


	cairo_set_color(cr, LINE);

	cairo_rectangle(cr, cm_line, cm_line
		, cm_width - 2 * cm_line, cm_line);
	cairo_rectangle(cr, cm_line, cm_height - 2 * cm_line
		, cm_width - 2 * cm_line, cm_line);
	cairo_rectangle(cr, cm_line, cm_line
		, cm_line, cm_height - 2 * cm_line);
	cairo_rectangle(cr, cm_width - 2 * cm_line, cm_line
		, cm_line, cm_height - 2 * cm_line);

	cairo_rectangle(cr, (cm_width - cm_line) / 2, cm_line, cm_line, cm_height - 2 * cm_line);

	cairo_rectangle(cr, cm_line, (cm_height - cm_gate_height) / 2
		, cm_gate_width, cm_line);
	cairo_rectangle(cr, cm_line, (cm_height + cm_gate_height) / 2 - cm_line
		, cm_gate_width, cm_line);
	cairo_rectangle(cr, cm_gate_width, (cm_height - cm_gate_height) / 2
		, cm_line, cm_gate_height);

	cairo_rectangle(cr, cm_width - cm_gate_width - cm_line, (cm_height - cm_gate_height) / 2
		, cm_gate_width, cm_line);
	cairo_rectangle(cr, cm_width - cm_gate_width - cm_line, (cm_height + cm_gate_height) / 2 - cm_line
		, cm_gate_width, cm_line);
	cairo_rectangle(cr, cm_width - cm_gate_width - cm_line, (cm_height - cm_gate_height) / 2
		, cm_line, cm_gate_height);

	cairo_fill(cr);

	cairo_restore(cr);
}

static void update_surface()
{
	cairo_t *cr = cairo_create(surface);

	if ((double)width / height < MAX_WIDTH / MAX_HEIGHT)
	{
		const double scale = (double)width / MAX_WIDTH;
		cairo_translate(cr, 0, (height - MAX_HEIGHT * scale) / 2);
		cairo_scale(cr, scale, scale);
	}
	else
	{
		const double scale = (double)height / MAX_HEIGHT;
		cairo_translate(cr, (width - MAX_WIDTH * scale) / 2, 0);
		cairo_scale(cr, scale, scale);
	}


	draw_field(cr);
	draw_ball(cr);

	for (uint8_t i = 0; i < MAX_ROBOTS; i++)
	{
		draw_robot(cr, i);
	}

	cairo_destroy(cr);

	/* Move robots */
	move();
}


/*
 *	 __     __   __     ______   ______     ______     ______   ______     ______     ______
 *	/\ \   /\ "-.\ \   /\__  _\ /\  ___\   /\  == \   /\  ___\ /\  __ \   /\  ___\   /\  ___\
 *	\ \ \  \ \ \-.  \  \/_/\ \/ \ \  __\   \ \  __<   \ \  __\ \ \  __ \  \ \ \____  \ \  __\
 *	 \ \_\  \ \_\\"\_\    \ \_\  \ \_____\  \ \_\ \_\  \ \_\    \ \_\ \_\  \ \_____\  \ \_____\
 *	  \/_/   \/_/ \/_/     \/_/   \/_____/   \/_/ /_/   \/_/     \/_/\/_/   \/_____/   \/_____/
 */


gboolean configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer data)
{
	if (surface)
	{
		cairo_surface_destroy(surface);
	}

	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);
	surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget)
		, CAIRO_CONTENT_COLOR, width, height);


	/* Initialize the surface */
	update_surface();

	/* We've handled the configure event, no need for further processing. */
	return TRUE;
}

gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	cairo_set_source_surface(cr, surface, 0, 0);
	cairo_paint(cr);

	update_surface();
	return FALSE;
}

void destroy()
{
	if (surface)
	{
		cairo_surface_destroy(surface);
	}
}
