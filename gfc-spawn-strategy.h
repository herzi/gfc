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

#ifndef GFC_SPAWN_STRATEGY_H
#define GFC_SPAWN_STRATEGY_H

#include <glib-object.h>

G_BEGIN_DECLS

#define GFC_TYPE_SPAWN_STRATEGY         (gfc_spawn_strategy_get_type ())
#define GFC_SPAWN_STRATEGY(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), GFC_TYPE_SPAWN_STRATEGY, GfcSpawnStrategy))
#define GFC_SPAWN_STRATEGY_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), GFC_TYPE_SPAWN_STRATEGY, GfcSpawnStrategyClass))
#define GFC_IS_SPAWN_STRATEGY(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), GFC_TYPE_SPAWN_STRATEGY))
#define GFC_IS_SPAWN_STRATEGY_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), GFC_TYPE_SPAWN_STRATEGY))
#define GFC_SPAWN_STRATEGY_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), GFC_TYPE_SPAWN_STRATEGY, GfcSpawnStrategyClass))

typedef struct _GfcSpawnStrategy      GfcSpawnStrategy;
typedef struct _GfcSpawnStrategyClass GfcSpawnStrategyClass;

GType    gfc_spawn_strategy_get_type (void);
gboolean gfc_spawn_strategy_spawn    (GfcSpawnStrategy* self,
				      gchar const     * working_folder,
				      gchar           **argv,
				      gchar           **envv,
				      GSpawnFlags       flags,
				      GPid            * return_pid,
				      gint            * return_stdin,
				      gint            * return_stdout,
				      gint            * return_stderr,
				      GError          **error);

struct _GfcSpawnStrategy {
	GObject      base_instance;
};

struct _GfcSpawnStrategyClass {
	GObjectClass base_class;

	/* vtable */
	gboolean (*spawn) (GfcSpawnStrategy* self,
			   gchar const     * working_folder,
			   gchar           **argv,
			   gchar           **envv,
			   GSpawnFlags       flags,
			   GPid            * return_pid,
			   gint            * return_stdin,
			   gint            * return_stdout,
			   gint            * return_stderr,
			   GError          **error);
};

G_END_DECLS

#endif /* !GFC_SPAWN_STRATEGY_H */
