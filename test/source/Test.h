////////////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------------- //
//                                                                            //
//                       (C) 2010-2016 Robot Developers                       //
//                       See LICENSE for licensing info                       //
//                                                                            //
// -------------------------------------------------------------------------- //
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------//
// Prefaces                                                                   //
//----------------------------------------------------------------------------//

#pragma once

#include <iostream>
using std::cin;
using std::cout;
using std::dec;
using std::endl;
using std::hex;
using std::ios;
using std::istream;
using std::ostream;

using std::nouppercase;
using std::uppercase;

#include <iomanip>
using std::setfill;
using std::setw;

#include <fstream>
using std::fstream;
using std::ifstream;
using std::ofstream;

#include <cstring>
#include <string>
using std::strcmp;
using std::string;

#include <vector>
using std::make_pair;
using std::vector;

#include <algorithm>
using std::is_sorted;
using std::sort;
using std::unique;

#if (_MSC_VER != 1600)
#  include <thread>
using std::thread;
#endif

#include "robot/Robot.h"
ROBOT_NS_USE_ALL;

//----------------------------------------------------------------------------//
// Macros                                                                     //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////

#define VERIFY(cond) \
  if (!(cond)) { \
    cout << #cond " Failed\n" << __FILE__ << ":" << __LINE__ << "\a\n\n"; \
    return false; \
  }

////////////////////////////////////////////////////////////////////////////////

#define ALL(cont) cont.begin(), cont.end()

//----------------------------------------------------------------------------//
// Helpers                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////

inline ostream& operator<<(ostream& out, const Hash& hash)
{
  // Save the output state
  auto state = out.flags();

  out << "0x" << uppercase << hex << hash.Result;

  // Restore state
  out.flags(state);
  return out;
}

////////////////////////////////////////////////////////////////////////////////

inline ostream& operator<<(ostream& out, const Color& color)
{
  out << "[" << (int32)color.R << ", " << (int32)color.G << ", "
      << (int32)color.B << ", " << (int32)color.A << "]";

  return out;
}

////////////////////////////////////////////////////////////////////////////////

inline ostream& operator<<(ostream& out, const Image& image)
{
  out << "[" << image.GetWidth() << "x" << image.GetHeight() << " - "
      << image.GetLength() << "/" << image.GetLimit() << "]";

  return out;
}

////////////////////////////////////////////////////////////////////////////////

inline ostream& operator<<(ostream& out, const Range& range)
{
  out << "[" << range.Min << ", " << range.Max << ")";

  return out;
}

////////////////////////////////////////////////////////////////////////////////

inline ostream& operator<<(ostream& out, const Point& point)
{
  out << "[" << point.X << ", " << point.Y << "]";

  return out;
}

////////////////////////////////////////////////////////////////////////////////

inline ostream& operator<<(ostream& out, const Size& size)
{
  out << "[" << size.W << ", " << size.H << "]";

  return out;
}

////////////////////////////////////////////////////////////////////////////////

inline ostream& operator<<(ostream& out, const Bounds& bounds)
{
  out << "[" << bounds.X << ", " << bounds.Y << ", " << bounds.W << ", "
      << bounds.H << "]";

  return out;
}

//----------------------------------------------------------------------------//
// Functions                                                                  //
//----------------------------------------------------------------------------//

bool TestTypes(void);
bool TestTimer(void);
bool TestKeyboard(void);
bool TestMouse(void);
bool TestProcess(void);
bool TestWindow(void);
bool TestMemory(void);
bool TestScreen(void);
bool TestClipboard(void);
