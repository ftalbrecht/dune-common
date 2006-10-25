// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
/** @file
   @author Robert Kloefkorn
   @brief Provides check for implementation of interface methods when using
   static polymorphism, i.e. Barton-Nackman trick.
   Use by invoking CHECK_INTERFACE_IMPLEMENTATION(asImp().methodToCheck())
   and for template methods double (
   CHECK_INTERFACE_IMPLEMENTATION((asImp().template methodToCheck<param> ())).
 **/

//- Dune includes
#include <dune/common/exceptions.hh>

/** The macro CHECK_AND_CALL_INTERFACE_IMPLEMENTATION throws an exception,
   if the interface method ist not implemented and just calls the method
   otherwise. If NDEBUG is defined no
   checking is done and the method is just called.
 */

#ifndef CHECK_AND_CALL_INTERFACE_IMPLEMENTATION
#define CHECK_AND_CALL_INTERFACE_IMPLEMENTATION(__interface_method_to_call__) \
  (__interface_method_to_call__)
#ifndef NDEBUG
#undef CHECK_AND_CALL_INTERFACE_IMPLEMENTATION
#define CHECK_AND_CALL_INTERFACE_IMPLEMENTATION(__interface_method_to_call__) \
  CHECK_INTERFACE_IMPLEMENTATION(__interface_method_to_call__)
#endif
#endif

#ifndef CHECK_INTERFACE_IMPLEMENTATION
#define CHECK_INTERFACE_IMPLEMENTATION(dummy)
#ifndef NDEBUG
#ifdef DUNE_DEVEL_MODE
#undef CHECK_INTERFACE_IMPLEMENTATION
#define CHECK_INTERFACE_IMPLEMENTATION(__interface_method_to_call__) \
  {\
    static bool call = false; \
    if( call == true ) \
      DUNE_THROW(NotImplemented,"Interface method not implemented!");\
    call = true; \
    (__interface_method_to_call__); \
    call = false; \
  }
#endif
#endif
#endif
