/**
 * @file
 *
 * @ingroup RTEMSImplClassicModes
 *
 * @brief This header file provides the implementation interfaces of
 *   the @ref RTEMSImplClassicModes support.
 */

/*  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#ifndef _RTEMS_RTEMS_MODESIMPL_H
#define _RTEMS_RTEMS_MODESIMPL_H

#include <rtems/rtems/modes.h>
#include <rtems/score/isrlevel.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup RTEMSImplClassicModes Task Modes
 *
 * @ingroup RTEMSImplClassic
 *
 * @brief This group contains the implementation to support task modes.
 *
 * @{
 */

/**
 *  @brief Checks if any of the mode flags in mask are set in mode_set.
 *
 *  This function returns TRUE if any of the mode flags in mask
 *  are set in mode_set, and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE bool _Modes_Mask_changed (
  rtems_mode mode_set,
  rtems_mode masks
)
{
   return ( mode_set & masks ) ? true : false;
}

/**
 *  @brief Checks if mode_set says that Asynchronous Signal Processing is disabled.
 *
 *  This function returns TRUE if mode_set indicates that Asynchronous
 *  Signal Processing is disabled, and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE bool _Modes_Is_asr_disabled (
  rtems_mode mode_set
)
{
   return (mode_set & RTEMS_ASR_MASK) == RTEMS_NO_ASR;
}

/**
 *  @brief Checks if mode_set indicates that preemption is enabled.
 *
 *  This function returns TRUE if mode_set indicates that preemption
 *  is enabled, and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE bool _Modes_Is_preempt (
  rtems_mode mode_set
)
{
   return (mode_set & RTEMS_PREEMPT_MASK) == RTEMS_PREEMPT;
}

/**
 *  @brief Checks if mode_set indicates that timeslicing is enabled.
 *
 *  This function returns TRUE if mode_set indicates that timeslicing
 *  is enabled, and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE bool _Modes_Is_timeslice (
  rtems_mode mode_set
)
{
  return (mode_set & RTEMS_TIMESLICE_MASK) == RTEMS_TIMESLICE;
}

/**
 *  @brief Gets the interrupt level portion of the mode_set.
 *
 *  This function returns the interrupt level portion of the mode_set.
 */
RTEMS_INLINE_ROUTINE ISR_Level _Modes_Get_interrupt_level (
  rtems_mode mode_set
)
{
  return ( mode_set & RTEMS_INTERRUPT_MASK );
}

/**
 *  @brief Sets the current interrupt level to that specified in the mode_set.
 *
 *  This routine sets the current interrupt level to that specified
 *  in the mode_set.
 */
RTEMS_INLINE_ROUTINE void _Modes_Set_interrupt_level (
  rtems_mode mode_set
)
{
  _ISR_Set_level( _Modes_Get_interrupt_level( mode_set ) );
}

/**
 *  @brief Changes the modes in old_mode_set indicated by
 *  mask to the requested values in new_mode_set.
 *
 *  This routine changes the modes in old_mode_set indicated by
 *  mask to the requested values in new_mode_set.  The resulting
 *  mode set is returned in out_mode_set and the modes that changed
 *  is returned in changed.
 */
RTEMS_INLINE_ROUTINE void _Modes_Change (
  rtems_mode  old_mode_set,
  rtems_mode  new_mode_set,
  rtems_mode  mask,
  rtems_mode *out_mode_set,
  rtems_mode *changed
)
{
  rtems_mode _out_mode;

  _out_mode      =  old_mode_set;
  _out_mode     &= ~mask;
  _out_mode     |= new_mode_set & mask;
  *changed       = _out_mode ^ old_mode_set;
  *out_mode_set  = _out_mode;
}

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
