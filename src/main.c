#include <gtk/gtk.h>
#include "surface.h"


static const char *const APPLICATION = "org.gtk.example";
static const char *const TITLE = "Drawing Area";

static const gint MIN_WIDTH = 630;
static const gint MIN_HEIGHT = 420;


static int i = 0;


/* Create a new surface of the appropriate size to store our scribbles */
static gboolean configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer data)
{
	resize(widget);

	/* Initialize the surface to white */
	update();

	/* We've handled the configure event, no need for further processing. */
	return TRUE;
}

/* Redraw the screen from the surface. Note that the ::draw
 * signal receives a ready-to-be-used cairo_t that is already
 * clipped to only draw the exposed areas of the widget
 */
static gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	/*cairo_set_source_surface(cr, surface, 0, 0);
	cairo_paint(cr);

	draw_brush(widget, i % 630, i / 630);
	i += 6;*/

	return update();
}



static void close_window(void)
{
	destroy();
}

static void activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), TITLE);
	gtk_window_maximize(GTK_WINDOW(window));
	//gtk_window_fullscreen(GTK_WINDOW(window));

	g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);


	GtkWidget *drawing_area = gtk_drawing_area_new();

	/* Set a minimum size */
	gtk_widget_set_size_request(drawing_area, MIN_WIDTH, MIN_HEIGHT);
	gtk_container_add(GTK_CONTAINER(window), drawing_area);


	/* Signals used to handle the backing surface */
	g_signal_connect(drawing_area, "configure-event", G_CALLBACK(configure_event), NULL);
	g_signal_connect(drawing_area, "draw", G_CALLBACK(draw), NULL);


	gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
	GtkApplication *app = gtk_application_new(APPLICATION, G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

	const int status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}
