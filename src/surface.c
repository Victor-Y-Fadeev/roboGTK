#include "surface.h"


static int width = 0;
static int height = 0;

/* Surface to store current scribbles */
static cairo_surface_t *surface = NULL;

static int i = 0;


static void clear_surface(void)
{
	cairo_t *cr = cairo_create(surface);

	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);

	cairo_destroy(cr);
}

/* Draw a rectangle on the surface at the given position */
static void draw_brush(GtkWidget *widget, gdouble x, gdouble y)
{
	/* Paint to the surface, where we store our state */
	cairo_t *cr = cairo_create(surface);

	cairo_rectangle(cr, x - 3, y - 3, 6, 6);
	cairo_fill(cr);

	cairo_destroy(cr);

	/* Now invalidate the affected region of the drawing area. */
	gtk_widget_queue_draw_area(widget, x - 3, y - 3, 6, 6);
	//gtk_widget_queue_draw(widget);
}


/*
 *	 __     __   __     ______   ______     ______     ______   ______     ______     ______
 *	/\ \   /\ "-.\ \   /\__  _\ /\  ___\   /\  == \   /\  ___\ /\  __ \   /\  ___\   /\  ___\
 *	\ \ \  \ \ \-.  \  \/_/\ \/ \ \  __\   \ \  __<   \ \  __\ \ \  __ \  \ \ \____  \ \  __\
 *	 \ \_\  \ \_\\"\_\    \ \_\  \ \_____\  \ \_\ \_\  \ \_\    \ \_\ \_\  \ \_____\  \ \_____\
 *	  \/_/   \/_/ \/_/     \/_/   \/_____/   \/_/ /_/   \/_/     \/_/\/_/   \/_____/   \/_____/
 */


gboolean resize(GtkWidget *const widget)
{
	if (surface)
	{
		cairo_surface_destroy(surface);
	}

	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);

	surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget)
		, CAIRO_CONTENT_COLOR, width, height);

	return surface ? TRUE : FALSE;
}

gboolean update()
{
	clear_surface();

	return TRUE;
}

void destroy()
{
	if (surface)
	{
		cairo_surface_destroy(surface);
	}
}
