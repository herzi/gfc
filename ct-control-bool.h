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

#ifndef CTCONTROLBOOL_H
#define CTCONTROLBOOL_H

#include "ct-control.h"

G_BEGIN_DECLS

typedef struct _CtControlBool        CtControlBool;
typedef struct _CtControlBoolPrivate CtControlBoolPrivate;
typedef struct _CtControlBoolClass   CtControlBoolClass;

#define CT_TYPE_CONTROL_BOOL         (ct_control_bool_get_type ())
#define CT_CONTROL_BOOL(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), CT_TYPE_CONTROL_BOOL, CtControlBool))
#define CT_CONTROL_BOOL_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), CT_TYPE_CONTROL_BOOL, CtControlBoolClass))
#define CT_IS_CONTROL_BOOL(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), CT_TYPE_CONTROL_BOOL))
#define CT_IS_CONTROL_BOOL_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), CT_TYPE_CONTROL_BOOL))
#define CT_CONTROL_BOOL_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), CT_TYPE_CONTROL_BOOL, CtControlBoolClass))

GType      ct_control_bool_get_type (void);

struct _CtControlBool {
	CtControl             base_instance;
	CtControlBoolPrivate* _private;
};

struct _CtControlBoolClass {
	CtControlClass        base_class;
};

G_END_DECLS

#endif /* !CTCONTROLBOOL_H */
