#pragma once

#include <gtk/gtk.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 *	Create a new surface of the appropriate size
 *
 *	@param	widget		Widget contained surface
 *	@param	event		Event which triggered the signal
 *	@param	data		User data
 *
 *	@return	@c TRUE on success, @c FALSE on failure
 */
gboolean configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer data);

/**
 *	Redraw the screen from the surface
 *
 *	@note The draw signal receives a ready-to-be-used cairo_t
 *		that is already clipped to only draw the exposed areas
 *
 *	@param	widget		Widget contained surface
 *	@param	cr			Cairo context
 *	@param	data		User data
 *
 *	@return	@c TRUE on success, @c FALSE on failure
 */
gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer data);

/**
 *	Destroy current surface
 */
void destroy(void);

#ifdef __cplusplus
} /* extern "C" */
#endif
