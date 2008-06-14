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

#ifndef GFC_SPAWN_SIMPLE_H
#define GFC_SPAWN_SIMPLE_H

#include <gfc-spawn-strategy.h>

G_BEGIN_DECLS

typedef struct _GfcSpawnSimple        GfcSpawnSimple;
typedef struct _GfcSpawnSimplePrivate GfcSpawnSimplePrivate;
typedef struct _GfcSpawnSimpleClass   GfcSpawnSimpleClass;

#define GFC_TYPE_SPAWN_SIMPLE         (gfc_spawn_simple_get_type ())

GType             gfc_spawn_simple_get_type (void);
GfcSpawnStrategy* gfc_spawn_simple_new      (void);

struct _GfcSpawnSimple {
	GfcSpawnStrategy       base_instance;
	GfcSpawnSimplePrivate* _private;
};

struct _GfcSpawnSimpleClass {
	GfcSpawnStrategyClass  base_class;
};

G_END_DECLS

#endif /* !GFC_SPAWN_SIMPLE_H */
