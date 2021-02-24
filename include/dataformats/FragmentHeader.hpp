/**
 * @file FragmentHeader.hpp  FragmentHeader struct definition
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DATAFORMATS_INCLUDE_DATAFORMATS_FRAGMENTHEADER_HPP_
#define DATAFORMATS_INCLUDE_DATAFORMATS_FRAGMENTHEADER_HPP_

#include "dataformats/GeoID.hpp"
#include "dataformats/Types.hpp"

#include <bitset>
#include <cstdlib>
#include <numeric>
#include <vector>

namespace dunedaq {
namespace dataformats {

/**
 * @brief The header for a DUNE Fragment
 */
struct FragmentHeader
{
  /**
   * @brief Magic bytes to identify a FragmentHeader entry in a raw data stream
   */
  static constexpr uint32_t s_fragment_header_magic = 0x11112222; // NOLINT(build/unsigned)

  /**
   * @brief The current version of the Fragment
   */
  static constexpr uint32_t s_fragment_header_version = 1; // NOLINT(build/unsigned)

  /**
   * @brief By default, all error bits are unset
   */
  static constexpr uint32_t s_default_error_bits = 0; // NOLINT(build/unsigned)

  /**
   * @brief Magic Bytes used to identify FragmentHeaders in a raw data stream
   */
  uint32_t m_fragment_header_marker = s_fragment_header_magic; // NOLINT(build/unsigned)

  /**
   * @brief Version of the FragmentHeader
   */
  uint32_t m_version = s_fragment_header_version; // NOLINT(build/unsigned)

  /**
   * @brief Size of the Fragment (including header and payload)
   */
  fragment_size_t m_size{ TypeDefaults::s_invalid_fragment_size }; // NOLINT(build/unsigned)

  /**
   * @brief Trigger Number this Fragment is associated with
   */
  trigger_number_t m_trigger_number{ TypeDefaults::s_invalid_trigger_number };

  /**
   * @brief Timestamp of the TriggerDecision
   */
  timestamp_t m_trigger_timestamp{ TypeDefaults::s_invalid_timestamp };

  /**
   * @brief Window offset of data in the Fragment
   */
  timestamp_diff_t m_window_offset{ TypeDefaults::s_invalid_timestamp_diff };

  /**
   * @brief Window width of data in the Fragment
   */
  timestamp_diff_t m_window_width{ TypeDefaults::s_invalid_timestamp_diff };

  /**
   * @brief Run number this Fragment is associated with
   */
  run_number_t m_run_number{ TypeDefaults::s_invalid_run_number };

  /**
   * @brief Component that generated the data in this Fragment
   */
  GeoID m_link_id;

  /**
   * @brief Error bits set by the Upstream DAQ
   *
   * Defined Error bits should be documented here, along with the Fragment Type(s) that they apply to
   */
  uint32_t m_error_bits{ s_default_error_bits }; // NOLINT(build/unsigned)

  /**
   * @brief Type of the Fragment, indicating the format of the contained payload
   */
  fragment_type_t m_fragment_type{ TypeDefaults::s_invalid_fragment_type };
};

/**
 * @brief This enumeration should list all defined error bits, as well as a short documentation of their meaning
 */
enum class FragmentErrorBits : size_t
{
  kDataNotFound      = 0,   ///< The requested data was not found at all, so the fragment is empty
  kIncomplete        = 1,   ///< Only part of the requested data is present in the fragment
  kUnassigned2 = 2,   ///< Error bit 2 is not assigned
  kUnassigned3 = 3,   ///< Error bit 3 is not assigned
  kUnassigned4 = 4,   ///< Error bit 4 is not assigned
  kUnassigned5 = 5,   ///< Error bit 5 is not assigned
  kUnassigned6 = 6,   ///< Error bit 6 is not assigned
  kUnassigned7 = 7,   ///< Error bit 7 is not assigned
  kUnassigned8 = 8,   ///< Error bit 8 is not assigned
  kUnassigned9 = 9,   ///< Error bit 9 is not assigned
  kUnassigned10 = 10, ///< Error bit 10 is not assigned
  kUnassigned11 = 11, ///< Error bit 11 is not assigned
  kUnassigned12 = 12, ///< Error bit 12 is not assigned
  kUnassigned13 = 13, ///< Error bit 13 is not assigned
  kUnassigned14 = 14, ///< Error bit 14 is not assigned
  kUnassigned15 = 15, ///< Error bit 15 is not assigned
  kUnassigned16 = 16, ///< Error bit 16 is not assigned
  kUnassigned17 = 17, ///< Error bit 17 is not assigned
  kUnassigned18 = 18, ///< Error bit 18 is not assigned
  kUnassigned19 = 19, ///< Error bit 19 is not assigned
  kUnassigned20 = 20, ///< Error bit 20 is not assigned
  kUnassigned21 = 21, ///< Error bit 21 is not assigned
  kUnassigned22 = 22, ///< Error bit 22 is not assigned
  kUnassigned23 = 23, ///< Error bit 23 is not assigned
  kUnassigned24 = 24, ///< Error bit 24 is not assigned
  kUnassigned25 = 25, ///< Error bit 25 is not assigned
  kUnassigned26 = 26, ///< Error bit 26 is not assigned
  kUnassigned27 = 27, ///< Error bit 27 is not assigned
  kUnassigned28 = 28, ///< Error bit 28 is not assigned
  kUnassigned29 = 29, ///< Error bit 29 is not assigned
  kUnassigned30 = 30, ///< Error bit 30 is not assigned
  kUnassigned31 = 31, ///< Error bit 31 is not assigned
  kInvalid = 32       ///< Error bit 32 and higher are not valid (m_error_bits is only 32 bits)
};

/**
 * @brief This enumeration should list all defined Fragment types
*/
enum class FragmentType : fragment_type_t
{
    kInvalid ///< Not a valid fragment_type. Should always be last
};

/**
 * @brief This map relates FragmentType values to string names
 * 
 * These names can be used, for example, as HDF5 Group names
*/
static const std::map<FragmentType, std::string> s_fragment_type_names{};

/**
 * @brief Convert a FragmentType enum value to string
 * @param type Type to convert
 * @return String representation of the given type 
*/
inline std::string
fragment_type_to_string(FragmentType type)
{
  if (!s_fragment_type_names.count(type))
    return "INVALID";
  return s_fragment_type_names.at(type);
}

/**
 * @brief Convert a string to a FragmentType value
 * @param name Name of the type
 * @return FragmentType corresponding to given string
 * 
 * Note that this function assumes that string names given in map are all uppercase. This function should be modified if that is not the case.
*/
inline FragmentType
string_to_fragment_type(std::string name)
{
  std::transform(name.begin(), name.end(), name.begin(), toupper);
  for (auto& it : s_fragment_type_names) {
    if (it.second == name)
      return it.first;
  }
  return FragmentType::kInvalid;
}

/**
 * @brief Stream a Fragment Header in human-readable form
 * @param o Stream to write to
 * @param hdr FragmentHeader to stream
 * @return Stream instance for further streaming
 */
inline std::ostream&
operator<<(std::ostream& o, FragmentHeader const& hdr)
{
  return o << "check_word: " << std::hex << hdr.m_fragment_header_marker << std::dec << ", "
           << "version: " << hdr.m_version << ", "
           << "size: " << hdr.m_size << ", "
           << "trigger_number: " << hdr.m_trigger_number << ", "
           << "run_number: " << hdr.m_run_number << ", "
           << "trigger_timestamp: " << hdr.m_trigger_timestamp << ", "
           << "window_offset: " << hdr.m_window_offset << ", "
           << "window_width: " << hdr.m_window_width << ", "
           << "link_id: " << hdr.m_link_id << ", "
           << "error_bits: " << hdr.m_error_bits << ", "
           << "fragment_type : " << hdr.m_fragment_type;
}

} // namespace dataformats
} // namespace dunedaq

#endif // DATAFORMATS_INCLUDE_DATAFORMATS_FRAGMENTHEADER_HPP_
