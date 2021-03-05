#include "surface.h"
#include <math.h>
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
	const double cm_scale = 1000.0 / 3;
	const double cm_diameter = 1;

	const double cm_centre = cm_diameter / 3;
	const double cm_arrow = cm_diameter / 4;

	cairo_save(cr);

	double x, y, angle;
	const int stop = robot(num, &x, &y, &angle);
	cairo_translate(cr, x, y);

	cairo_scale(cr, cm_scale, cm_scale);

	cairo_set_color(cr, OBJECT);
	cairo_arc(cr, 0, 0, cm_diameter / 2, 0, 2 * G_PI);
	cairo_fill(cr);


	cairo_set_color(cr, num < MAX_ROBOTS / 2 ? FIRST : SECOND);
	cairo_arc(cr, 0, 0, cm_centre / 2, 0, 2 * G_PI);
	cairo_fill(cr);

	if (!stop)
	{
		cairo_rotate(cr, angle);
		cairo_move_to(cr, 0, -cm_diameter / 2);

		double cathetus = sqrt(pow(cm_diameter / 2, 2) - pow(cm_diameter / 2 - cm_arrow, 2));
		cairo_rel_line_to(cr, -cathetus, cm_arrow);
		cairo_rel_line_to(cr, 2 * cathetus, 0);
		cairo_close_path(cr);

		cairo_rectangle(cr, -cm_centre / 2, 0, cm_centre, cm_arrow - cm_diameter / 2);
		cairo_fill(cr);
		cairo_rotate(cr, -angle);
	}


	cairo_set_color(cr, OBJECT);
	cairo_select_font_face(cr, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, cm_centre);

	cairo_move_to(cr, -cm_centre / 2.75, cm_centre / 2.75);

	char buf[3];
	sprintf(buf, "%01X", num + 1);
	cairo_show_text(cr, buf);

	cairo_restore(cr);
}

static void draw_ball(cairo_t *cr)
{
	const double cm_scale = 1000.0 / 3;
	const double cm_diameter = 1.0 / 3;

	cairo_save(cr);

	double x, y;
	ball(&x, &y);
	cairo_translate(cr, x, y);

	cairo_scale(cr, cm_scale, cm_scale);

	cairo_set_color(cr, OBJECT);
	cairo_arc(cr, 0, 0, cm_diameter / 2, 0, 2 * G_PI);
	cairo_fill(cr);

	cairo_restore(cr);
}

static void draw_field(cairo_t *cr)
{
	const double cm_scale = 1000.0 / 3;

	const double cm_width = MAX_WIDTH / cm_scale;
	const double cm_height = MAX_HEIGHT / cm_scale;
	const double cm_line = 0.25;

	const double cm_gate_width = cm_width / 9 - cm_line;
	const double cm_gate_height = cm_height / 3;

	cairo_save(cr);
	cairo_scale(cr, cm_scale, cm_scale);

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

	/* We've handled the configure event, no need for further processing */
	return TRUE;
}

gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	cairo_set_source_surface(cr, surface, 0, 0);
	cairo_paint(cr);

	return FALSE;
}

gboolean callback(GtkWidget *widget, GdkFrameClock *frame_clock, gpointer user_data)
{
	update_surface();

	/* Now invalidate the drawing area */
	gtk_widget_queue_draw(widget);

	return G_SOURCE_CONTINUE;
}

void destroy()
{
	if (surface)
	{
		cairo_surface_destroy(surface);
	}
}
