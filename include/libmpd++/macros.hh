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

/** @def LIBMPDPP_PUBLIC_API
 * @brief Used to mark something as part of the public API
 *
 * This is used to mark a class, function or global variable as part of the public API for libmpd++.
 */

/** Concatenate C++ namespace elements
 *
 * This is a utility macro to concatenate parts of a C++ namespace path. For example
 * @code{.cpp}
 * LIBMPDPP_NSCONCAT(my::namespace::prefix, classname)
 * @endcode
 * ...would result in the identifier "my::namespace::prefix::classname".
 *
 * @param A The first part of the namespace to concatenate.
 * @param B The second part of the namespace to concatenate.
 * @return The concatenated namespace identifier.
 */
#define LIBMPDPP_NSCONCAT(A,B) A::B

/** The libmpd++ namespace
 */
#define LIBMPDPP_NAMESPACE com::bbc::libmpdpp

/** Mark the start of the libmpd++ namespace
 */
#define LIBMPDPP_NAMESPACE_BEGIN namespace LIBMPDPP_NAMESPACE {

/** Mark the end of the libmpd++ namespace
 */
#define LIBMPDPP_NAMESPACE_END }

/** Substitute an identfier for class @p A in the libmpd++ namespace
 *
 * @param A The class to reference in the libmpd++ namespace.
 * @return An identifier for the class @p A in the libmpd++ namespace.
 */
#define LIBMPDPP_NAMESPACE_CLASS(A) LIBMPDPP_NSCONCAT(LIBMPDPP_NAMESPACE,A)

/** Create a using namespace entry for the libmpd++ namespace
 *
 * Creates a @c "using ..." declaration for identifier @p A in the libmpd++ namespace.
 *
 * For example @c LIBMPDPP_NAMESPACE_USING(MPD); would result in:
 * @code{.cpp}
 * using com::bbc::libmpdpp::MPD;
 * @endcode
 *
 * @param A The identifier for the thing to use from libmpd++ namespace.
 */
#define LIBMPDPP_NAMESPACE_USING(A) using LIBMPDPP_NAMESPACE_CLASS(A)

/** Create a using namespace entry for the libmpd++ namespace
 *
 * Creates a @c "using namespace ..." declaration for identifier @p A in the libmpd++ namespace.
 *
 * For example @c LIBMPDPP_NAMESPACE_USING_ALL; would result in:
 * @code{.cpp}
 * using namespace com::bbc::libmpdpp;
 * @endcode
 */
#define LIBMPDPP_NAMESPACE_USING_ALL using namespace LIBMPDPP_NAMESPACE

/* vim:ts=8:sts=4:sw=4:expandtab:
 */
#endif /*_BBC_PARSE_DASH_MPD_MACROS_HH_*/
