// 
// Copyright 2011 Oblong Industries Inc. All rights reserved.
// 
// Author: Ambrus Csaszar
// Email: ambrus@oblong.com
// Date: Aug 10, 2011
// 
// Proprietary softare, do not distribute.
// 


#ifndef IPHELPERS_H
#define IPHELPERS_H

#include <string.h>
#include <iostream>
#include <sstream>

//#include "blockingsocket.h"

// ---------------------------------------------------------------------------------------------------------------------
// Cross platform IP address helpers -----------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

// A cross-platform Windows/Linux helpers structure for IPV4 address handling
struct AddrIpv4
{
  union
  {
    unsigned long Value;
    unsigned char Data[4];
  };

  inline AddrIpv4() :
    Value(0)
  { }

  inline AddrIpv4(const in_addr &addr) :
#ifdef WIN32
    Value(addr.S_un.S_addr)
#else
    Value(addr.s_addr)
#endif
  { }

  inline AddrIpv4(
    unsigned char b0,
    unsigned char b1,
    unsigned char b2,
    unsigned char b3)
  {
    Data[0] = b0;
    Data[1] = b1;
    Data[2] = b2;
    Data[3] = b3;
  }

  inline in_addr To_in_addr()
  {
    in_addr ret;
#ifdef WIN32
    ret.S_un.S_addr = Value;
#else
    ret.s_addr = Value;
#endif
    return ret;
  }

  inline std::string ToString();

  inline static bool TryParse(const char *addressString, AddrIpv4 &out_address)
  {
    //  sockaddr_in in;
   //   in.sin_addr.s_addr = inet_addr(addressString); 
    //  out_address.Value = in.sin_addr.s_addr;
    //  return true;
      /*
    int d0, d1, d2, d3;
    int ct = sscanf(addressString, "%d.%d.%d.%d", &d0, &d1, &d2, &d3);

    out_address = AddrIpv4(
      (unsigned char)d0,
      (unsigned char)d1,
      (unsigned char)d2,
      (unsigned char)d3);
    
    return (ct == 4);*/
      
      //sin_addr.s_addr = inet_addr(pchIP); 
  } 

  inline static bool TryParse(const std::string &addressString, AddrIpv4 &out_address)
  { return TryParse(addressString.c_str(), out_address); } 

};


inline std::ostream& operator << (std::ostream &os, const AddrIpv4 &a)
{ return os << int(a.Data[0]) << "." << int(a.Data[1]) << "." << int(a.Data[2]) << "." << int(a.Data[3]); }


inline std::string AddrIpv4::ToString()
{
  std::stringstream ss;
  ss << *this;
  return ss.str();
}



#endif // IPHELPERS_H

