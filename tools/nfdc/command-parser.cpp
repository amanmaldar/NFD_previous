/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014-2016,  Regents of the University of California,
 *                           Arizona Board of Regents,
 *                           Colorado State University,
 *                           University Pierre & Marie Curie, Sorbonne University,
 *                           Washington University in St. Louis,
 *                           Beijing Institute of Technology,
 *                           The University of Memphis.
 *
 * This file is part of NFD (Named Data Networking Forwarding Daemon).
 * See AUTHORS.md for complete list of NFD authors and contributors.
 *
 * NFD is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * NFD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * NFD, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "command-parser.hpp"
#include <ndn-cxx/util/logger.hpp>

namespace nfd {
namespace tools {
namespace nfdc {

NDN_LOG_INIT(CommandParser);

std::ostream&
operator<<(std::ostream& os, AvailableIn modes)
{
  int count = 0;

#define PRINT_BIT(bit, str) \
  if ((modes & bit) != 0) { \
    if (++count > 1) { \
      os << '|'; \
    } \
    os << str; \
  }

  PRINT_BIT(AVAILABLE_IN_ONE_SHOT, "one-shot")
  PRINT_BIT(AVAILABLE_IN_BATCH, "batch")

#undef PRINT_BIT

  if (count == 0) {
    os << "none";
  }
  return os;
}

std::ostream&
operator<<(std::ostream& os, ParseMode mode)
{
  switch (mode) {
    case ParseMode::ONE_SHOT:
      return os << "one-shot";
    case ParseMode::BATCH:
      return os << "batch";
  }
  return os << static_cast<int>(mode);
}

CommandParser&
CommandParser::addCommand(const CommandDefinition& def, const Execute& execute, AvailableIn modes)
{
  BOOST_ASSERT(modes != AVAILABLE_IN_NONE);
  m_commands[{def.getNoun(), def.getVerb()}].reset(new Command{def, execute, modes});
  return *this;
}

CommandParser&
CommandParser::addAlias(const std::string& noun, const std::string& verb, const std::string& verb2)
{
  m_commands[{noun, verb2}] = m_commands.at({noun, verb});
  return *this;
}

std::tuple<CommandParser::Execute*, CommandArguments>
CommandParser::parse(const std::vector<std::string>& tokens, ParseMode mode) const
{
  BOOST_ASSERT(mode == ParseMode::ONE_SHOT);

  const std::string& noun = tokens.size() > 0 ? tokens[0] : "";
  const std::string& verb = tokens.size() > 1 ? tokens[1] : "";
  size_t nameLen = std::min<size_t>(2, tokens.size());

  auto i = m_commands.find({noun, verb});
  if (i == m_commands.end()) {
    if (verb.empty()) {
      i = m_commands.find({noun, "list"});
    }
    else {
      // help, exit, quit, legacy nfdc commands
      i = m_commands.find({noun, ""});
    }
    nameLen = std::min<size_t>(1, tokens.size());
  }
  if (i == m_commands.end() || (i->second->modes & static_cast<AvailableIn>(mode)) == 0) {
    BOOST_THROW_EXCEPTION(Error("no such command: " + noun + " " + verb));
  }

  const CommandDefinition& def = i->second->def;
  NDN_LOG_TRACE("found command " << def.getNoun() << " " << def.getVerb());

  return std::make_tuple(&i->second->execute, def.parse(tokens, nameLen));
}

} // namespace nfdc
} // namespace tools
} // namespace nfd