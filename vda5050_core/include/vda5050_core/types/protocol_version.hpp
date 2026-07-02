/*
 * Copyright (C) 2026 ROS-Industrial Consortium Asia Pacific
 * Advanced Remanufacturing and Technology Centre
 * A*STAR Research Entities (Co. Registration No. 199702110H)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef VDA5050_CORE__TYPES__PROTOCOL_VERSION_HPP_
#define VDA5050_CORE__TYPES__PROTOCOL_VERSION_HPP_

#include <array>
#include <stdexcept>
#include <string>

namespace vda5050_core {

namespace types {

/// \brief Strongly-typed VDA5050 protocol version.
///
/// Canonical representation of the VDA5050 protocol versions supported by
/// this library. Single source of truth for which versions are supported,
/// conversion to the full semantic version string used in message headers
/// (e.g. "2.0.0"), and conversion to the MQTT topic version segment (e.g.
/// "v2").
class ProtocolVersion
{
public:
  /// \brief VDA5050 protocol version 2.0.0.
  static const ProtocolVersion V2_0_0;

  /// \brief Parses a semantic version string (e.g. "2.0.0").
  /// \throws std::invalid_argument if `version` is not a supported version.
  static ProtocolVersion from_string(const std::string& version)
  {
    if (version == "2.0.0") return V2_0_0;

    throw std::invalid_argument(
      "ProtocolVersion::from_string: unsupported protocol version '" +
      version + "'");
  }

  /// \brief All VDA5050 protocol versions supported by this library.
  static const std::array<ProtocolVersion, 1>& supported_versions()
  {
    static const std::array<ProtocolVersion, 1> versions{V2_0_0};
    return versions;
  }

  /// \brief Full semantic version string, e.g. "2.0.0".
  std::string to_string() const
  {
    switch (value_)
    {
      case Value::V2_0_0:
        return "2.0.0";
    }

    throw std::logic_error("ProtocolVersion::to_string: unhandled version");
  }

  /// \brief MQTT topic version segment, e.g. "v2".
  std::string topic_version() const
  {
    switch (value_)
    {
      case Value::V2_0_0:
        return "v2";
    }

    throw std::logic_error(
      "ProtocolVersion::topic_version: unhandled version");
  }

  bool operator==(const ProtocolVersion& other) const
  {
    return value_ == other.value_;
  }

  bool operator!=(const ProtocolVersion& other) const
  {
    return !(*this == other);
  }

private:
  enum class Value
  {
    V2_0_0
  };

  explicit constexpr ProtocolVersion(Value value)
  : value_(value)
  {
    // Nothing to do here ...
  }

  Value value_;
};

inline constexpr ProtocolVersion ProtocolVersion::V2_0_0{
  ProtocolVersion::Value::V2_0_0};

}  // namespace types
}  // namespace vda5050_core

#endif  // VDA5050_CORE__TYPES__PROTOCOL_VERSION_HPP_
