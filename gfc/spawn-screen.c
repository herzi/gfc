/* This file is part of libgfc
 *
 * AUTHORS
 *     Sven Herzberg  <sven@imendio.com>
 *
 * Copyright (C) 2008  Sven Herzberg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#include <gfc/spawn-screen.h>

struct _GfcSpawnScreenPrivate {
	GdkScreen* screen;
};

enum {
	PROP_0,
	PROP_SCREEN
};

/* GType Implementation */

G_DEFINE_TYPE (GfcSpawnScreen, gfc_spawn_screen, GFC_TYPE_SPAWN_STRATEGY);

static void
gfc_spawn_screen_init (GfcSpawnScreen* self)
{
	self->_private = G_TYPE_INSTANCE_GET_PRIVATE (self,
						      GFC_TYPE_SPAWN_SCREEN,
						      GfcSpawnScreenPrivate);
}

static void
spawn_screen_finalize (GObject* object)
{
	g_object_unref (GFC_SPAWN_SCREEN (object)->_private->screen);

	G_OBJECT_CLASS (gfc_spawn_screen_parent_class)->finalize (object);
}

static void
spawn_screen_set_property (GObject     * object,
			   guint         prop_id,
			   GValue const* value,
			   GParamSpec  * pspec)
{
	GfcSpawnScreen* self = GFC_SPAWN_SCREEN (object);

	switch (prop_id) {
	case PROP_SCREEN:
		g_return_if_fail (!self->_private->screen);
		g_return_if_fail (g_value_get_object (value));

		self->_private->screen = g_value_dup_object (value);
		g_object_notify (object, "screen");
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static gboolean
spawn_screen_spawn (GfcSpawnStrategy* self,
		    gchar const     * working_folder,
		    gchar           **argv,
		    gchar           **envv,
		    GSpawnFlags       flags,
		    GPid            * return_pid,
		    gint            * return_stdin,
		    gint            * return_stdout,
		    gint            * return_stderr,
		    GError          **return_error)
{
	return gdk_spawn_on_screen_with_pipes (GFC_SPAWN_SCREEN (self)->_private->screen,
					       working_folder,
					       argv, envv,
					       flags,
					       NULL, NULL,
					       return_pid,
					       return_stdin,
					       return_stdout,
					       return_stderr,
					       return_error);
}

static void
gfc_spawn_screen_class_init (GfcSpawnScreenClass* self_class)
{
	GObjectClass         * object_class = G_OBJECT_CLASS (self_class);
	GfcSpawnStrategyClass* spawn_class  = GFC_SPAWN_STRATEGY_CLASS (self_class);

	object_class->finalize     = spawn_screen_finalize;
	object_class->set_property = spawn_screen_set_property;

	g_object_class_install_property (object_class, PROP_SCREEN,
					 g_param_spec_object ("screen", "screen", "screen",
							      GDK_TYPE_SCREEN, G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));

	spawn_class->spawn = spawn_screen_spawn;

	g_type_class_add_private (self_class, sizeof (GfcSpawnScreenPrivate));
}

/* Public API */

/**
 * gfc_spawn_screen_new:
 * @screen: a valid #GdkScreen
 */
GfcSpawnStrategy*
gfc_spawn_screen_new (GdkScreen* screen)
{
	g_return_val_if_fail (GDK_IS_SCREEN (screen), NULL);

	return g_object_new (GFC_TYPE_SPAWN_SCREEN,
			     "screen", screen,
			     NULL);
}

