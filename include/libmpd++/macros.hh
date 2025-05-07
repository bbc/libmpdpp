#ifndef _BBC_PARSE_DASH_MPD_MACROS_HH_
#define _BBC_PARSE_DASH_MPD_MACROS_HH_
/*****************************************************************************
 * DASH MPD parsing library in C++: common library macros
 *****************************************************************************
 * Copyright: (C) 2025 British Broadcasting Corporation
 * Author(s): David Waring <david.waring2@bbc.co.uk>
 * License: LGPLv3
 *
 * For full license terms please see the LICENSE file distributed with this
 * library or refer to: https://www.gnu.org/licenses/lgpl-3.0.txt.
 */

#ifdef BUILD_LIBPARSEMPD
#ifdef HAVE_VISIBILITY
#define LIBPARSEMPD_PUBLIC_API __attribute__((visibility("default")))
#else
#define LIBPARSEMPD_PUBLIC_API 
#endif
#else
#define LIBPARSEMPD_PUBLIC_API
#endif

#define LIBPARSEMPD_NSCONCAT(A,B) A::B

#define LIBPARSEMPD_NAMESPACE com::bbc::libparsempd
#define LIBPARSEMPD_NAMESPACE_BEGIN namespace LIBPARSEMPD_NAMESPACE {
#define LIBPARSEMPD_NAMESPACE_END }
#define LIBPARSEMPD_NAMESPACE_CLASS(A) LIBPARSEMPD_NSCONCAT(LIBPARSEMPD_NAMESPACE,A)
#define LIBPARSEMPD_NAMESPACE_USING(A) using LIBPARSEMPD_NAMESPACE_CLASS(A)
#define LIBPARSEMPD_NAMESPACE_USING_ALL using namespace LIBPARSEMPD_NAMESPACE

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_MACROS_HH_*/
