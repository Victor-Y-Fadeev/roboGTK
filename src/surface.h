#pragma once

#include <gtk/gtk.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 *	Resize drawing area
 *
 *	@param	widget		Widget contained surface
 *
 *	@return	@c TRUE on success, @c FALSE on failure
 */
gboolean resize(GtkWidget *const widget);

/**
 *	Update and redraw screen
 *
 *	@return	@c TRUE on success, @c FALSE on failure
 */
gboolean update();

/**
 *	Destroy current surface
 */
void destroy();

#ifdef __cplusplus
} /* extern "C" */
#endif
