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

#include "gfc-reader.h"

struct _GfcReaderPrivate {
	gint        file_descriptor;
	GIOChannel* channel;
};

enum {
	PROP_0,
	PROP_FILE_DESCRIPTOR
};

G_DEFINE_TYPE (GfcReader, gfc_reader, G_TYPE_OBJECT);

static void
gfc_reader_init (GfcReader* self)
{
	self->_private = G_TYPE_INSTANCE_GET_PRIVATE (self,
						      GFC_TYPE_READER,
						      GfcReaderPrivate);
}

static void
reader_constructed (GObject* object)
{
	GfcReader* self = GFC_READER (object);

	self->_private->channel = g_io_channel_unix_new (self->_private->file_descriptor);
	g_io_channel_set_flags (self->_private->channel, G_IO_FLAG_NONBLOCK, NULL); // FIXME: return value and GError
	g_io_channel_set_close_on_unref (self->_private->channel, TRUE);

	if (G_OBJECT_CLASS (gfc_reader_parent_class)->constructed) {
		G_OBJECT_CLASS (gfc_reader_parent_class)->constructed (object);
	}
}

static void
reader_get_property (GObject   * object,
		     guint       prop_id,
		     GValue    * value,
		     GParamSpec* pspec)
{
	GfcReader* self = GFC_READER (object);

	switch (prop_id) {
	case PROP_FILE_DESCRIPTOR:
		g_value_set_int (value, self->_private->file_descriptor);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
reader_set_property (GObject     * object,
		     guint         prop_id,
		     GValue const* value,
		     GParamSpec  * pspec)
{
	GfcReader* self = GFC_READER (object);

	switch (prop_id) {
	case PROP_FILE_DESCRIPTOR:
		self->_private->file_descriptor = g_value_get_int (value);
		g_object_notify (object, "file-descriptor");
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
gfc_reader_class_init (GfcReaderClass* self_class)
{
	GObjectClass* object_class = G_OBJECT_CLASS (self_class);

	object_class->constructed  = reader_constructed;
	object_class->get_property = reader_get_property;
	object_class->set_property = reader_set_property;

	g_object_class_install_property (object_class, PROP_FILE_DESCRIPTOR,
					 g_param_spec_int ("file-descriptor", "file-descriptor", "file-descriptor",
							   0, G_MAXINT, 0, G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

	g_type_class_add_private (self_class, sizeof (GfcReaderPrivate));
}

GIOChannel*
gfc_reader_get_channel (GfcReader const* self)
{
	g_return_val_if_fail (GFC_IS_READER (self), NULL);

	return self->_private->channel;
}
