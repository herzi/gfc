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

#ifndef CTCONTROLDOUBLE_H
#define CTCONTROLDOUBLE_H

#include "ct-control.h"

G_BEGIN_DECLS

typedef struct _CtControlDouble        CtControlDouble;
typedef struct _CtControlDoublePrivate CtControlDoublePrivate;
typedef struct _CtControlDoubleClass   CtControlDoubleClass;

#define CT_TYPE_CONTROL_DOUBLE         (ct_control_double_get_type ())

struct _CtControlDouble {
	CtControl               base_instance;
	CtControlDoublePrivate* _private;
};

struct _CtControlDoubleClass {
	CtControlClass            base_class;
};

G_END_DECLS

#endif /* !CTCONTROLDOUBLE_H */
