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
	guint       io_handler;
};

enum {
	PROP_0,
	PROP_FILE_DESCRIPTOR
};

enum {
	READ_LINE,
	N_SIGNALS
};

static guint signals[N_SIGNALS] = {0};

G_DEFINE_TYPE (GfcReader, gfc_reader, G_TYPE_OBJECT);

static void
gfc_reader_init (GfcReader* self)
{
	self->_private = G_TYPE_INSTANCE_GET_PRIVATE (self,
						      GFC_TYPE_READER,
						      GfcReaderPrivate);
}

static gboolean
io_watch_cb (GIOChannel  * channel,
	     GIOCondition  condition,
	     gpointer      data)
{
	GString  * buffer = g_string_new ("");
	GIOStatus  state = G_IO_STATUS_NORMAL;
	GfcReader* self = GFC_READER (data);

	while (state == G_IO_STATUS_NORMAL) {
		gsize delim = 0;

		// FIXME: add GError here
		state = g_io_channel_read_line_string (channel, buffer, &delim, NULL);
		switch (state) {
		case G_IO_STATUS_NORMAL:
			/* sometimes we get an empty string because we stopped reading at the last character */
			if (delim < buffer->len && buffer->str[delim]) {
				g_string_set_size (buffer, delim);
				g_signal_emit (self,
					       signals[READ_LINE],
					       0,
					       buffer->str); // FIXME: emit by signal id
				g_string_set_size (buffer, 0);
			}
			break;
		case G_IO_STATUS_AGAIN:
			/* no data right now... try again later */
			break;
		case G_IO_STATUS_ERROR:
		case G_IO_STATUS_EOF:
			// FIXME: call g_source_remove() here instead of flush()?
			self->_private->io_handler = 0;
			g_string_free (buffer, TRUE);
			return FALSE;
		}
	}

	g_string_free (buffer, TRUE);
	return TRUE;
}

static void
reader_constructed (GObject* object)
{
	GfcReader* self = GFC_READER (object);

	self->_private->channel = g_io_channel_unix_new (self->_private->file_descriptor);
	g_io_channel_set_flags (self->_private->channel, G_IO_FLAG_NONBLOCK, NULL); // FIXME: return value and GError
	g_io_channel_set_close_on_unref (self->_private->channel, TRUE);

	self->_private->io_handler = g_io_add_watch (gfc_reader_get_channel (GFC_READER (self)),
						     G_IO_IN,
						     io_watch_cb,
						     self);

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

	signals[READ_LINE] = g_signal_new ("read-line",
					   GFC_TYPE_READER,
					   0, 0,
					   NULL, NULL,
					   g_cclosure_marshal_VOID__STRING,
					   G_TYPE_NONE,
					   1,
					   G_TYPE_STRING | G_SIGNAL_TYPE_STATIC_SCOPE);

	g_type_class_add_private (self_class, sizeof (GfcReaderPrivate));
}

GfcReader*
gfc_reader_new (gint file_descriptor)
{
	return g_object_new (GFC_TYPE_READER,
			     "file-descriptor", file_descriptor,
			     NULL);
}

void
gfc_reader_flush (GfcReader* self)
{
	g_return_if_fail (GFC_IS_READER (self));

	if (G_UNLIKELY (!self->_private->io_handler)) {
		return;
	}

	g_source_remove (self->_private->io_handler);

	io_watch_cb (self->_private->channel,
		     G_IO_IN,
		     self); // parse trailing lines
}

GIOChannel*
gfc_reader_get_channel (GfcReader const* self)
{
	g_return_val_if_fail (GFC_IS_READER (self), NULL);

	return self->_private->channel;
}
