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

#include "available-commands.hpp"
#include "help.hpp"
#include "core/version.hpp"
#include <chrono>
#include <thread>
#include <iostream>
#include "execute-command.hpp"
#include "forwarder-general-module.hpp"
#include <vector>
#include <string>
//#ifndef MYDATA_HPP
#include "myData.hpp"
//#endif
namespace nfd {
namespace tools {
namespace nfdc {

void testFunction(){
	std::cout << "this is test fucntion" << std::endl;
	ForwarderGeneralModule fgm;
//	fgm.fetchStatus
}

static int
main(int argc, char** argv)
{
  std::vector<std::string> args(argv + 1, argv + argc);

  CommandParser parser;
  registerCommands(parser);

  if (args.empty() || args[0] == "-h") {
    helpList(std::cout, parser);
    return 0;
  }

  if (args[0] == "-V") {
    std::cout << NFD_VERSION_BUILD_STRING << std::endl;
    return 0;
  }

  std::string noun, verb;
  CommandArguments ca;
  ExecuteCommand execute;
  try {
    std::tie(noun, verb, ca, execute) = parser.parse(args, ParseMode::ONE_SHOT);
  }
  catch (const std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
    return 2;
  }

  try {
    Face face;
    KeyChain keyChain;
    Controller controller(face, keyChain);
    ExecuteContext ctx{noun, verb, ca, 0, std::cout, std::cerr, face, keyChain, controller};
    execute(ctx);
    return ctx.exitCode;
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}

} // namespace nfdc
} // namespace tools
} // namespace nfd

int
main(int argc, char* argv[])
{
// 0 nfdc, 1 status, 2 show,
// running this file in background , output the function to text file and then put &
// a nfdc status show > text1 &
//  std::cout << "hello main " << std::endl;
  auto newArg = "status";
  if (*argv[2]== *newArg) {
  int k = 1;
     while(k) {
	//k = 0;
	// get the information from forwarder
	argv[1] = "status";
	argv[2] = "show";
	nfd::tools::nfdc::main(argc,argv);
	
	//get te information from content store
	argv[1]= "cs";
	argv[2]= "info"; 
	nfd::tools::nfdc::main(argc,argv) ;
	//extern nfd::tools::nfdc::myData hello;
	
	//nfd::tools::nfdc::myData mydataNew;
	//std::cout << "printing from main: " << mydataNew.n_CsEntries << " " << mydataNew.n_PitEntries << std::endl;
	//std::cout << "printing static: " << myData::n_CsEntries << std::endl;
	std::this_thread::sleep_for (std::chrono::seconds(5));
      }
	return 0;
  } 
  //return 0;
  return nfd::tools::nfdc::main(argc, argv);
}
