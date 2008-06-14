/* This file is part of libgfc
 *
 * AUTHORS
 *     Sven Herzberg
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

#include "gfc-spawn-simple.h"

/* GType Implementation */

G_DEFINE_TYPE (GfcSpawnSimple, gfc_spawn_simple, GFC_TYPE_SPAWN_STRATEGY);

static void
gfc_spawn_simple_init (GfcSpawnSimple* self)
{}

static gboolean
simple_spawn (GfcSpawnStrategy* self,
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
	g_return_val_if_fail (GFC_IS_SPAWN_SIMPLE (self), FALSE);

	return g_spawn_async_with_pipes (working_folder,
					 argv,
					 envv,
					 G_SPAWN_SEARCH_PATH | G_SPAWN_DO_NOT_REAP_CHILD,
					 NULL, NULL,
					 return_pid,
					 return_stdin,
					 return_stdout,
					 return_stderr,
					 return_error);

}

static void
gfc_spawn_simple_class_init (GfcSpawnSimpleClass* self_class)
{
	GfcSpawnStrategyClass* spawn_class = GFC_SPAWN_STRATEGY_CLASS (self_class);

	spawn_class->spawn = simple_spawn;
}

/* Public API */

GfcSpawnStrategy*
gfc_spawn_simple_new (void)
{
	return g_object_new (GFC_TYPE_SPAWN_SIMPLE,
			     NULL);
}

