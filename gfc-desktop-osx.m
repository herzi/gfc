/* This file is part of gfc
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

#include "gfc-desktop.h"

#import <AppKit/NSFont.h>

gchar*
gfc_desktop_get_monospace_font (void)
{
	NSFont* font = [NSFont userFixedPitchFontOfSize:-1.0];
	return g_strdup_printf ("%s %d",
				[[font familyName] cStringUsingEncoding:NSUTF8StringEncoding],
				(int)[NSFont systemFontSize]);
}
