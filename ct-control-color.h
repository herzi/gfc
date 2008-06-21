/* This file is part of cairo tree
 *
 * AUTHORS
 *     Sven Herzberg  <herzi@gnome-de.org>
 *
 * Copyright (C) 2007  Sven Herzberg
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

#ifndef CTCONTROLCOLOR_H
#define CTCONTROLCOLOR_H

#include "ct-control.h"

G_BEGIN_DECLS

typedef struct _CtControlColor        CtControlColor;
typedef struct _CtControlColorPrivate CtControlColorPrivate;
typedef struct _CtControlColorClass   CtControlColorClass;

#define CT_TYPE_CONTROL_COLOR         (ct_control_color_get_type ())

struct _CtControlColor {
	CtControl              base_instance;
	CtControlColorPrivate* _private;
};

struct _CtControlColorClass {
	CtControlClass         base_class;
};

G_END_DECLS

#endif /* !CTCONTROLCOLOR_H */
