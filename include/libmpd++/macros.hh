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

#ifdef BUILD_LIBMPDPP
#ifdef HAVE_VISIBILITY
#define LIBMPDPP_PUBLIC_API __attribute__((visibility("default")))
#else
#define LIBMPDPP_PUBLIC_API 
#endif
#else
#define LIBMPDPP_PUBLIC_API
#endif

#define LIBMPDPP_NSCONCAT(A,B) A::B

#define LIBMPDPP_NAMESPACE com::bbc::libmpdpp
#define LIBMPDPP_NAMESPACE_BEGIN namespace LIBMPDPP_NAMESPACE {
#define LIBMPDPP_NAMESPACE_END }
#define LIBMPDPP_NAMESPACE_CLASS(A) LIBMPDPP_NSCONCAT(LIBMPDPP_NAMESPACE,A)
#define LIBMPDPP_NAMESPACE_USING(A) using LIBMPDPP_NAMESPACE_CLASS(A)
#define LIBMPDPP_NAMESPACE_USING_ALL using namespace LIBMPDPP_NAMESPACE

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_MACROS_HH_*/
