/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014-2017,  Regents of the University of California,
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

#include "forwarder-general-module.hpp"
#include "format-helpers.hpp"
#include "core/logger.hpp"
#include <string>
#include "myData.hpp"
//NFD_LOG_INIT("Forwarder");
namespace nfd {
namespace tools {
namespace nfdc {
/*
class myData {
public:
	int n_CsEntries;

};
*/

void
ForwarderGeneralModule::fetchStatus(Controller& controller,
                                    const function<void()>& onSuccess,
                                    const Controller::DatasetFailCallback& onFailure,
                                    const CommandOptions& options)
{
  //NFD_LOG_INFO("ALEX fetch status new");
  //std::cout << "hello"<< std::endl;
  controller.fetch<ndn::nfd::ForwarderGeneralStatusDataset>(
    [this, onSuccess] (const ForwarderStatus& result) {
      m_status = result;
      onSuccess();
      //NFD_LOG_INFO(result); // edited`
//      std::cout << "print result: " << result << std::endl;
    },
    onFailure, options);
}

static time::system_clock::Duration
calculateUptime(const ForwarderStatus& status)
{
  return status.getCurrentTimestamp() - status.getStartTimestamp();
}

void
ForwarderGeneralModule::formatStatusXml(std::ostream& os) const
{
  this->formatItemXml(os, m_status);
}

void
ForwarderGeneralModule::formatItemXml(std::ostream& os, const ForwarderStatus& item) const
{
  os << "<generalStatus>";

  os << "<version>" << xml::Text{item.getNfdVersion()} << "</version>";
  os << "<startTime>" << xml::formatTimestamp(item.getStartTimestamp()) << "</startTime>";
  os << "<currentTime>" << xml::formatTimestamp(item.getCurrentTimestamp()) << "</currentTime>";
  os << "<uptime>" << xml::formatDuration(calculateUptime(item)) << "</uptime>";

  os << "<nNameTreeEntries>" << item.getNNameTreeEntries() << "</nNameTreeEntries>";
  os << "<nFibEntries>" << item.getNFibEntries() << "</nFibEntries>";
  os << "<nPitEntries>" << item.getNPitEntries() << "</nPitEntries>";
  os << "<nMeasurementsEntries>" << item.getNMeasurementsEntries() << "</nMeasurementsEntries>";
  os << "<nCsEntries>" << item.getNCsEntries() << "</nCsEntries>";

  os << "<packetCounters>";
  os << "<incomingPackets>"
     << "<nInterests>" << item.getNInInterests() << "</nInterests>"
     << "<nData>" << item.getNInData() << "</nData>"
     << "<nNacks>" << item.getNInNacks() << "</nNacks>"
     << "</incomingPackets>";
  os << "<outgoingPackets>"
     << "<nInterests>" << item.getNOutInterests() << "</nInterests>"
     << "<nData>" << item.getNOutData() << "</nData>"
     << "<nNacks>" << item.getNOutNacks() << "</nNacks>"
     << "</outgoingPackets>";
  os << "</packetCounters>";

  os << "</generalStatus>";
}

void
ForwarderGeneralModule::formatStatusText(std::ostream& os) const
{
//  os << "General NFD status:\n";
  this->formatItemText(os, m_status);
}

void
ForwarderGeneralModule::formatItemText(std::ostream& os, const ForwarderStatus& item) const
{
/*
  os << "               version=" << item.getNfdVersion() << "\n";
  os << "             startTime=" << text::formatTimestamp(item.getStartTimestamp()) << "\n";
  os << "           currentTime=" << text::formatTimestamp(item.getCurrentTimestamp()) << "\n";
  os << "                uptime=" << text::formatDuration(calculateUptime(item), true) << "\n";

  os << "      nNameTreeEntries=" << item.getNNameTreeEntries() << "\n";
  os << "           nFibEntries=" << item.getNFibEntries() << "\n"; // needed
  os << "           nPitEntries=" << item.getNPitEntries() << "\n"; //needed
  os << "  nMeasurementsEntries=" << item.getNMeasurementsEntries() << "\n";
  os << "            nCsEntries=" << item.getNCsEntries() << "\n"; // needed

 os << "          nInInterests=" << item.getNInInterests() << "\n"; //needed 
 os << "         nOutInterests=" << item.getNOutInterests() << "\n"; // needed
  os << "               nInData=" << item.getNInData() << "\n"; // needed
 os << "              nOutData=" << item.getNOutData() << "\n"; // needed
  os << "              nInNacks=" << item.getNInNacks() << "\n";
  os << "             nOutNacks=" << item.getNOutNacks() << "\n";
*/

//nfd::tools::nfdc::myData mydataNew; //declared globally in header file

// std::stringstream buf;
// buf << item.getNCsEntries();
//std::cout << "testing string stream: " << std::stoi(buf.str()) << std::endl ; 
//mydataNew.n_CsEntries = std::stoi(buf.str());
//myData::n_CsEntries = std::stoi(buf.str());
//std::cout << "value from class CsEntries: " << myData::n_CsEntries << std::endl;

//buf.str("");
/*
buf << item.getNPitEntries();
std::cout << "testing string stream: " << std::stoi(buf.str()) << std::endl ; 
mydataNew.n_PitEntries = std::stoi(buf.str());
std::cout << "value from class PitEntries: " << mydataNew.n_PitEntries << std::endl;
*/




//os <<  item.getNCsEntries() <<"#";
//os << item.getNPitEntries() << "#"; 
//os << item.getNFibEntries() << "#"; 
std::cout << "Table_Entries%" << item.getNCsEntries() <<"%" << item.getNPitEntries() << "%" << item.getNFibEntries() << "%" << std::endl; 
//NFD_LOG_INFO("testing logs");
}

} // namespace nfdc
} // namespace tools
} // namespace nfd
