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

#ifndef CT_CONTROL_STRING_H
#define CT_CONTROL_STRING_H

#include "ct-control.h"

G_BEGIN_DECLS

typedef struct _CtControlString        CtControlString;
typedef struct _CtControlStringPrivate CtControlStringPrivate;
typedef struct _CtControlStringClass   CtControlStringClass;

#define CT_TYPE_CONTROL_STRING         (ct_control_string_get_type ())
#define CT_CONTROL_STRING(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), CT_TYPE_CONTROL_STRING, CtControlString))
#define CT_CONTROL_STRING_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), CT_TYPE_CONTROL_STRING, CtControlStringClass))
#define CT_IS_CONTROL_STRING(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), CT_TYPE_CONTROL_STRING))
#define CT_IS_CONTROL_STRING_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), CT_TYPE_CONTROL_STRING))
#define CT_CONTROL_STRING_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), CT_TYPE_CONTROL_STRING, CtControlStringClass))

GType ct_control_string_get_type (void);

struct _CtControlString {
	CtControl               base_instance;
	CtControlStringPrivate* _private;
};

struct _CtControlStringClass {
	CtControlClass          base_class;
};

G_END_DECLS

#endif /* !CT_CONTROL_STRING_H */
