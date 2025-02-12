/*
 * Copyright (C) 2017 Georges Basile Stavracas Neto <georges.stavracas@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2 of the licence or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

/**
 * SECTION:ostree-version
 * @short_description: ostree version checking
 *
 * ostree provides macros to check the version of the library
 * at compile-time
 */

/**
 * OSTREE_YEAR_VERSION:
 *
 * ostree year version component (e.g. 2017 if %OSTREE_VERSION is 2017.2)
 *
 * Since: 2017.4
 */
#define OSTREE_YEAR_VERSION (2024)

/**
 * OSTREE_RELEASE_VERSION:
 *
 * ostree release version component (e.g. 2 if %OSTREE_VERSION is 2017.2)
 *
 * Since: 2017.4
 */
#define OSTREE_RELEASE_VERSION (5)

/**
 * OSTREE_VERSION
 *
 * ostree version.
 *
 * Since: 2017.4
 */
#define OSTREE_VERSION (2024.5)

/**
 * OSTREE_VERSION_S:
 *
 * ostree version, encoded as a string, useful for printing and
 * concatenation.
 *
 * Since: 2017.4
 */
#define OSTREE_VERSION_S "2024.5"

#define OSTREE_ENCODE_VERSION(year,release) \
        ((year) << 16 | (release))

/**
 * OSTREE_VERSION_HEX:
 *
 * ostree version, encoded as an hexadecimal number, useful for
 * integer comparisons.
 *
 * Since: 2017.4
 */
#define OSTREE_VERSION_HEX \
        (OSTREE_ENCODE_VERSION (OSTREE_YEAR_VERSION, OSTREE_RELEASE_VERSION))

/**
 * OSTREE_CHECK_VERSION:
 * @year: required year version
 * @release: required release version
 *
 * Compile-time version checking. Evaluates to %TRUE if the version
 * of ostree is equal or greater than the required one.
 *
 * Since: 2017.4
 */
#define OSTREE_CHECK_VERSION(year,release)   \
        (OSTREE_YEAR_VERSION > (year) || \
         (OSTREE_YEAR_VERSION == (year) && OSTREE_RELEASE_VERSION >= (release)))

/**
 * OSTREE_BUILT_FEATURES:
 *
 * Whitespace separated set of features this libostree was configured with at build time.
 * Consult the source code in configure.ac (or the CLI `ostree --version`) for examples.
 *
 * Since: 2019.3
 */
#ifndef __GI_SCANNER__
#define OSTREE_BUILT_FEATURES "inode64 initial-var libcurl libsoup3 gpgme composefs ex-fsverity libarchive selinux avahi libmount systemd release p2p"
#endif
