// 
// Copyright 2011 Oblong Industries Inc. All rights reserved.
// 
// Author: Ambrus Csaszar
// Email: ambrus@oblong.com
// Date: Aug 10, 2011
// 
// Proprietary softare, do not distribute.
// 

#ifndef LINUXHELPERS_H
#define LINUXHELPERS_H

#include <algorithm>
#include <cstdarg>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include "iphelpers.h"

//#include "cameracommonglobals.h"

// ----------------------../inputmanagerethernet/linuxhelpers.h:102: error: ‘int snprintf(char*, size_t, const char*, ...)’ redeclared inline without ‘gnu_inline’ attribute-----------------------------------------------------------------------------------------------
// Linux ethernet adapter information ----------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

// Bare essential information about an ethernet adapter
struct EthAdapter
{
  std::string Name;
  AddrIpv4 Address;
};

inline std::ostream& operator << (std::ostream &os, const EthAdapter &a)
{ return os << a.Name << " (" << a.Address << ")"; }

// A utility class for querying ethernet adapter info
class EthInfo
{
public:
  EthInfo();
  ~EthInfo();

  // Enumerates all available ethernet adapters and their addresses
  int GetAdapters(std::vector<EthAdapter> &adapters);

  // Queries the netmask for a particular ethernet adapter
  int GetNetmask(const std::string &adapterName, AddrIpv4 &out_netmask);

  // Gets the name of an ethernet adapter based on its address
  int GetName(const AddrIpv4 &address, std::string &out_name);

private:
  int sockfd;
};


// ---------------------------------------------------------------------------------------------------------------------
// Linux ports of windows-specifc string manipulations -----------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

inline int strcpy_s(
	char *strDestination,
	size_t numberOfElements,
	const char *strSource)
{
	strncpy(strDestination, strSource, numberOfElements);
	strDestination[numberOfElements-1] = '\0';
	return 0;
}

template <size_t size>
inline int strncpy_s(
	char (&strDestination)[size],
	const char *strSource,
	size_t count)
{
	int ct = std::min(size, count);
	strncpy(strDestination, strSource, ct);
	strDestination[size-1] = '\0';
	return 0;
}

inline int strcat_s(
	char *strDestination,
	size_t numberOfElements,
	const char *strSource)
{
	int ctDest = strlen(strDestination);
	int ctCat = numberOfElements - ctDest - 1;
	strncat(strDestination, strSource, ctCat);
	strDestination[ctDest + ctCat] = '\0';
	return 0;
}

/*
inline int sprintf_s(
	char *buffer,
	size_t sizeOfBuffer,
	const char *format,
	...
)
{
	va_list argList;
	va_start(argList, format);
	vsnprintf(buffer, sizeOfBuffer, format, argList);
	va_end(argList);
	buffer[sizeOfBuffer-1] = '\0';
	return 0;
}*/


// ---------------------------------------------------------------------------------------------------------------------
// Some useful string functions ----------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

// Transforms a string to its lowercase version
inline void StrToLower(std::string &str)
{
	transform(str.begin(), str.end(), str.begin(), tolower);
}

// Tokenizes a string by splitting across 'delim' and discarding the delimiters
inline void StrSplit(
	const std::string &str,
	char delim,
	std::vector<std::string> &out_tokens)
{
	size_t pos = 0;
	while( true )
	{
		size_t nextPos = str.find( delim, pos );
		if( nextPos == str.npos )
		{
			out_tokens.push_back( std::string( str.substr( pos, str.length() - pos ) ) );
			break;
		}
		out_tokens.push_back( std::string( str.substr( pos, nextPos - pos ) ) );
		pos = nextPos + 1;
	}
}


// ---------------------------------------------------------------------------------------------------------------------
// ARP table helper functions ------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

// Converts mac address bytes to their hex string representation
inline std::string MacBytesToString(const unsigned char *mac)
{
	const int macct = 6;
	std::stringstream ss;
	for (int i = 0; i < macct; i++)
	{
		ss << std::setw(2) << std::setfill('0') << std::hex << int(mac[i]);
		if (i < (macct - 1))
			ss << ":";
	}
	return ss.str();
}

// Finds the LSB of the IP address associated with the given MAC in the ARP table.
inline int ArpFindMac(const unsigned char* MACAddress, const std::string &adapterName = "")
{
	// The target mac address
	// TODO - this mac address is probably in bytes... but what order?
	std::string mac = MacBytesToString(MACAddress);
	StrToLower(mac);

	// The arp table
	std::ifstream arp("/proc/net/arp");

	try
	{
		// Discard the first line
		while (arp.good() && arp.get() != '\n') { }

		// Read the arp table
		while (arp.good())
		{
			// Read a row from the table
			std::string ip, type, flags, address, mask, device;
			arp >> ip >> type >> flags >> address >> mask >> device;

			// Discard the rest of the line
			while (arp.good() && arp.get() != '\n') { }

			// We got the right adapter
			if (adapterName.length() == 0 ||
					adapterName.compare(device) == 0)
			{
				// Found the mac
				if (address.find(mac) != std::string::npos)
				{
					// Extract the ip LSB
					std::vector<std::string> iptokens;
					StrSplit(ip, '.', iptokens);

					// Succeed
					return atoi(iptokens[3].c_str());
				}
			}
		}
	}
	catch (...)
	{
		arp.close();
		throw;
	}

	// Fail
	return 0;
}

// Verifies that no IP address with this given LSB is in the ARP table.
inline bool ArpVerifyClean(int lsb, const std::string &adapterName = "")
{
	// The arp table
	std::ifstream arp("/proc/net/arp");

	try
	{
		// Discard the first line
		while (arp.good() && arp.get() != '\n') { }

		// Read the arp table
		while (arp.good())
		{
			// Read a row from the table
			std::string ip, type, flags, address, mask, device;
			arp >> ip >> type >> flags >> address >> mask >> device;

			// Discard the rest of the line
			while (arp.good() && arp.get() != '\n') { }

			// We got the right adapter
			if (adapterName.length() == 0 ||
					adapterName.compare(device) == 0)
			{
				// Tokenize the IP address
				std::vector<std::string> iptokens;
				StrSplit(ip, '.', iptokens);

				// Found the LSB
				if (iptokens.size() >= 4 && atoi(iptokens[3].c_str()) == lsb)
					return false;
			}
		}
	}
	catch (...)
	{
		arp.close();
		throw;
	}

	// The IP's LSB was not found
  return true;
}


#endif // LINUXHELPERS_H

