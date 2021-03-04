#include "surface.h"
#include <stdint.h>


typedef uint32_t color_t;


const color_t BACKGROUND = 0xC5E0B4;
const color_t LINE = 0xFFFFFF;
const color_t OBJECT = 0x262626;
const color_t FIRST = 0xFFD966;
const color_t SECOND = 0x9DC3E6;


int width = 0;
int height = 0;

/* Surface to store current scribbles */
cairo_surface_t *surface = NULL;


static inline void cairo_set_color(cairo_t *cr, color_t color)
{
	cairo_set_source_rgb(cr
		, (double)((color & 0xFF0000) >> 16) / 0xFF
		, (double)((color & 0x00FF00) >> 8) / 0xFF
		, (double)(color & 0x0000FF) / 0xFF);
}

static void update_surface(void)
{
	cairo_t *cr = cairo_create(surface);

	//cairo_set_source_rgb(cr, 0.5, 1, 1);
	cairo_set_color(cr, BACKGROUND);
	cairo_paint(cr);

	//cairo_destroy(cr);
	//cr = cairo_create(surface);

	//cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_color(cr, LINE);
	cairo_rectangle(cr, 0, 0, 100, 100);
	cairo_fill(cr);
	//cairo_paint(cr);*/

	cairo_destroy(cr);
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

	surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget)
		, CAIRO_CONTENT_COLOR
		, gtk_widget_get_allocated_width(widget)
		, gtk_widget_get_allocated_height(widget));

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

void destroy(void)
{
	if (surface)
	{
		cairo_surface_destroy(surface);
	}
}
