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

#ifndef GFC_SPAWN_SCREEN_H
#define GFC_SPAWN_SCREEN_H

#include <gdk/gdk.h>
#include <gfc/spawn-strategy.h>

G_BEGIN_DECLS

typedef struct _GfcSpawnScreen        GfcSpawnScreen;
typedef struct _GfcSpawnScreenPrivate GfcSpawnScreenPrivate;
typedef struct _GfcSpawnScreenClass   GfcSpawnScreenClass;

#define GFC_TYPE_SPAWN_SCREEN         (gfc_spawn_screen_get_type ())
#define GFC_SPAWN_SCREEN(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), GFC_TYPE_SPAWN_SCREEN, GfcSpawnScreen))
#define GFC_SPAWN_SCREEN_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), GFC_TYPE_SPAWN_SCREEN, GfcSpawnScreenClass))
#define GFC_IS_SPAWN_SCREEN(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), GFC_TYPE_SPAWN_SCREEN))
#define GFC_IS_SPAWN_SCREEN_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), GFC_TYPE_SPAWN_SCREEN))
#define GFC_SPAWN_SCREEN_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), GFC_TYPE_SPAWN_SCREEN, GfcSpawnScreenClass))

GType             gfc_spawn_screen_get_type (void);
GfcSpawnStrategy* gfc_spawn_screen_new      (GdkScreen* screen);

struct _GfcSpawnScreen {
	GfcSpawnStrategy       base_instance;
	GfcSpawnScreenPrivate* _private;
};

struct _GfcSpawnScreenClass {
	GfcSpawnStrategyClass  base_class;
};

G_END_DECLS

#endif /* !GFC_SPAWN_SCREEN_H */
