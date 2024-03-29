/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014-2018,  Regents of the University of California,
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

#include "cs-module.hpp"
#include "format-helpers.hpp"

namespace nfd {
namespace tools {
namespace nfdc {

void
CsModule::fetchStatus(Controller& controller,
                      const function<void()>& onSuccess,
                      const Controller::DatasetFailCallback& onFailure,
                      const CommandOptions& options)
{
  controller.fetch<ndn::nfd::CsInfoDataset>(
    [this, onSuccess] (const CsInfo& result) {
      m_status = result;
      onSuccess();
    },
    onFailure, options);
}

void
CsModule::formatStatusXml(std::ostream& os) const
{
  os << "<cs>";
  os << "<nHits>" << m_status.getNHits() << "</nHits>";
  os << "<nMisses>" << m_status.getNMisses() << "</nMisses>";
  os << "</cs>";
}

void
CsModule::formatStatusText(std::ostream& os) const
{
//  os << "CS information:\n  ";
  text::ItemAttributes ia;
  //os << ia("nHits") << m_status.getNHits()
    // << ia("nMisses") << m_status.getNMisses()
    // << ia.end();
  //os << '\n';
 // os << m_status.getNHits() << "#" << m_status.getNMisses() << "#" << "\n";
  std::cout << "CsHitMiss%" <<m_status.getNHits() << "%" << m_status.getNMisses() << "%" << std::endl;
  

}

} // namespace nfdc
} // namespace tools
} // namespace nfd
