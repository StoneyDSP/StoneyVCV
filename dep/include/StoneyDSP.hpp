#ifndef STONEYDSP_STRINGIFY
  # define STONEYDSP_STRINGIFY_HELPER(n) #n
  /**
   * @brief Handy stringify pre-processor macro.
   * @param n The value to stringify.
   */
  # define STONEYDSP_STRINGIFY(n) STONEYDSP_STRINGIFY_HELPER(n)
#endif

//==============================================================================

/**
 * @brief The `StoneyDSP` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace StoneyDSP
 *
 */
namespace StoneyDSP
{
/** @addtogroup StoneyDSP
 *  @{
 */

//==============================================================================

/**
 * @brief Handy function for avoiding unused variables warning.
 *
 * @tparam Types
 */
template <typename... Types>
void ignoreUnused (Types&&...) noexcept {}

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

//==============================================================================

