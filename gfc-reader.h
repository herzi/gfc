/* This file is part of libgfc
 *
 * AUTHORS
 *     Sven Herzberg
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

#ifndef GFC_READER_H
#define GFC_READER_H

#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _GfcReader        GfcReader;
typedef struct _GfcReaderPrivate GfcReaderPrivate;
typedef struct _GfcReaderClass   GfcReaderClass;

#define GFC_TYPE_READER         (gfc_reader_get_type ())
#define GFC_READER(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), GFC_TYPE_READER, GfcReader))
#define GFC_READER_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), GFC_TYPE_READER, GfcReaderClass))
#define GFC_IS_READER(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), GFC_TYPE_READER))
#define GFC_IS_READER_CLASS(i)  (G_TYPE_CHECK_CLASS_TYPE ((c), GFC_TYPE_READER))
#define GFC_READER_GET_CLASS(c) (G_TYPE_INSTANCE_GET_CLASS ((i), GFC_TYPE_READER, GfcReaderClass))

GType       gfc_reader_get_type    (void);
GIOChannel* gfc_reader_get_channel (GfcReader const* self);

struct _GfcReader {
	GObject           base_instance;
	GfcReaderPrivate* _private;
};

struct _GfcReaderClass {
	GObjectClass      base_class;
};

G_END_DECLS

#endif /* !GFC_READER_H */
