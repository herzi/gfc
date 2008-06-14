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

#include "gfc-spawn-screen.h"

enum {
	PROP_0,
	PROP_SCREEN
};

/* GType Implementation */

G_DEFINE_TYPE (GfcSpawnScreen, gfc_spawn_screen, GFC_TYPE_SPAWN_STRATEGY);

static void
gfc_spawn_screen_init (GfcSpawnScreen* self)
{}

static void
gfc_spawn_screen_class_init (GfcSpawnScreenClass* self_class)
{
	GObjectClass* object_class = G_OBJECT_CLASS (self_class);

	g_object_class_install_property (object_class, PROP_SCREEN,
					 g_param_spec_object ("screen", "screen", "screen",
							      GDK_TYPE_SCREEN, G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
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

