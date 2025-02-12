/*
 * Copyright © 2015 Red Hat, Inc
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *       Alexander Larsson <alexl@redhat.com>
 */

#if !defined (__FLATPAK_H_INSIDE__) && !defined (FLATPAK_COMPILATION)
#error "Only <flatpak.h> can be included directly."
#endif

#ifndef __FLATPAK_VERSION_MACROS_H__
#define __FLATPAK_VERSION_MACROS_H__


/**
 * FLATPAK_MAJOR_VERSION:
 *
 * The major version.
 */
#define FLATPAK_MAJOR_VERSION (1)

/**
 * FLATPAK_MINOR_VERSION:
 *
 * The minor version.
 */
#define FLATPAK_MINOR_VERSION (14)

/**
 * FLATPAK_MICRO_VERSION:
 *
 * The micro version.
 */
#define FLATPAK_MICRO_VERSION (6)

/**
 * FLATPAK_CHECK_VERSION:
 * @major: major version to compare against
 * @minor: minor version to compare against
 * @micro: micro version to compare against
 *
 * Check that the current version is at least @major.@minor.@micro.
 */
#define FLATPAK_CHECK_VERSION(major,minor,micro)        \
    (FLATPAK_MAJOR_VERSION > (major) || \
     (FLATPAK_MAJOR_VERSION == (major) && FLATPAK_MINOR_VERSION > (minor)) || \
     (FLATPAK_MAJOR_VERSION == (major) && FLATPAK_MINOR_VERSION == (minor) && \
      FLATPAK_MICRO_VERSION >= (micro)))

#ifndef FLATPAK_EXTERN
#define FLATPAK_EXTERN extern
#endif

/**
 * SECTION:flatpak-version-macros
 * @Title: Version information
 *
 * These macros can be used to check the library version in use.
 */

#endif /* __FLATPAK_VERSION_MACROS_H__ */
