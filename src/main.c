#include <gtk/gtk.h>
#include "logic.h"
#include "surface.h"

#if defined(_WIN32) || defined(_WIN64)
	#include <windows.h>
#endif


const char *const APPLICATION = "org.gtk.robots";
const char *const TITLE = "РобоФутбол";

const gint MIN_WIDTH = 630;
const gint MIN_HEIGHT = 420;


static void activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), TITLE);
	gtk_window_maximize(GTK_WINDOW(window));
	//gtk_window_fullscreen(GTK_WINDOW(window));

	g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);


	GtkWidget *drawing_area = gtk_drawing_area_new();

	/* Set a minimum size */
	gtk_widget_set_size_request(drawing_area, MIN_WIDTH, MIN_HEIGHT);
	gtk_container_add(GTK_CONTAINER(window), drawing_area);


	/* Signals used to handle the backing surface */
	g_signal_connect(drawing_area, "configure-event", G_CALLBACK(configure_event), NULL);
	g_signal_connect(drawing_area, "draw", G_CALLBACK(draw), NULL);

	gtk_widget_add_tick_callback(drawing_area, callback, NULL, NULL);


	gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
#if defined(_WIN32) || defined(_WIN64)
	HWND var=GetConsoleWindow();
	ShowWindow(var, SW_HIDE);
#endif

	/* Initialize logic */
	init();

	GtkApplication *app = gtk_application_new(APPLICATION, G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

	const int status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}
