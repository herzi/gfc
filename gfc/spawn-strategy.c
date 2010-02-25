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

#include <gfc/spawn-strategy.h>

/* GType Implementation */

G_DEFINE_ABSTRACT_TYPE (GfcSpawnStrategy, gfc_spawn_strategy, G_TYPE_OBJECT);

static void
gfc_spawn_strategy_init (GfcSpawnStrategy* self)
{}

static void
gfc_spawn_strategy_class_init (GfcSpawnStrategyClass* self_class)
{}

/* Public API */

static GQuark
gfc_spawn_error_quark (void)
{
	static GQuark quark = 0;

	/* FIXME: thread safety with g_once() */
	if (G_UNLIKELY (!quark)) {
		quark = g_quark_from_static_string ("GfcSpawn");
	}

	return quark;
}

/**
 * gfc_spawn_strategy_spawn:
 *
 * Returns: %TRUE on success, %FALSE otherwise (then @error will definitely be
 * set)
 */
gboolean
gfc_spawn_strategy_spawn (GfcSpawnStrategy* self,
			  gchar const     * working_folder,
			  gchar           **argv,
			  gchar           **envv,
			  GSpawnFlags       flags,
			  GPid            * return_pid,
			  gint            * return_stdin,
			  gint            * return_stdout,
			  gint            * return_stderr,
			  GError          **error)
{
	gboolean result = FALSE;

	g_return_val_if_fail (GFC_IS_SPAWN_STRATEGY (self), FALSE);
	g_return_val_if_fail (!error || !*error, FALSE);

	if (G_UNLIKELY (!GFC_SPAWN_STRATEGY_GET_CLASS (self)->spawn)) {
		GError* intern_error = g_error_new (gfc_spawn_error_quark (),
						    0,
						    "Class %s doesn't implement GfcSpawnStrategy->spawn\n",
						    G_OBJECT_TYPE_NAME (self));

		if (error) {
			g_propagate_error (error, intern_error);
		} else {
			g_warning ("%s", intern_error->message);
			g_error_free (intern_error);
		}
		return FALSE;
	}

	result = GFC_SPAWN_STRATEGY_GET_CLASS (self)->spawn (self,
					       working_folder,
					       argv, envv,
					       flags,
					       return_pid,
					       return_stdin,
					       return_stdout,
					       return_stderr,
					       error);

	if (G_UNLIKELY (!result && error && !*error)) {
		g_set_error (error,
			     gfc_spawn_error_quark (),
			     0,
			     "%s\n",
			     "Unknown error spawning child; the strategy returned "
			     "FALSE and didn't set this error");
	}

	return result;
}

