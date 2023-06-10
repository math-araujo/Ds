//[]---------------------------------------------------------------[]
//|                                                                 |
//| Copyright (C) 2007, 2023 Paulo Pagliosa.                        |
//|                                                                 |
//| This software is provided 'as-is', without any express or       |
//| implied warranty. In no event will the authors be held liable   |
//| for any damages arising from the use of this software.          |
//|                                                                 |
//| Permission is granted to anyone to use this software for any    |
//| purpose, including commercial applications, and to alter it and |
//| redistribute it freely, subject to the following restrictions:  |
//|                                                                 |
//| 1. The origin of this software must not be misrepresented; you  |
//| must not claim that you wrote the original software. If you use |
//| this software in a product, an acknowledgment in the product    |
//| documentation would be appreciated but is not required.         |
//|                                                                 |
//| 2. Altered source versions must be plainly marked as such, and  |
//| must not be misrepresented as being the original software.      |
//|                                                                 |
//| 3. This notice may not be removed or altered from any source    |
//| distribution.                                                   |
//|                                                                 |
//[]---------------------------------------------------------------[]
//
// OVERVIEW: ErrorHandler.cpp
// ========
// Source file for generic error handler.
//
// Author: Paulo Pagliosa
// Last revision: 15/05/2023

#include "ErrorHandler.h"
#include <cstdio>

namespace cg::parser
{ // begin namespace cg::parser

//
// Auxiliary function
//
const char*
searchErrorMessage(ErrorMessageTableEntry* entries, int code)
{
  while (entries->code != -1)
  {
    if (code == entries->code)
      break;
    entries++;
  }
  return entries->message;
}


/////////////////////////////////////////////////////////////////////
//
// ErrorHandler implementation
// ============
const char*
ErrorHandler::findErrorMessage(int) const
{
  return nullptr;
}

void
ErrorHandler::throwErrorMessage(const char* msg) const
{
  throw std::runtime_error{msg};
}

void
ErrorHandler::error(int code, ...) const
{
  va_list args;

  va_start(args, code);
  handleError(code, args);
}

void
ErrorHandler::error(int code, const char* arg) const
{
  constexpr auto maxLen = 1024;
  char buffer[maxLen];
  auto fmt = errorMessageFormat(errorMessage(code));

  snprintf(buffer, maxLen, fmt.c_str(), arg);
  throwErrorMessage(buffer);
}

inline const char*
ErrorHandler::errorMessage(int code) const
{
  auto msg = findErrorMessage(code);
  return nullptr == msg ? "undefined error code" : msg;
}

void
ErrorHandler::handleError(int code, va_list args) const
{
  constexpr auto maxLen = 1024;
  char buffer[maxLen];
  auto fmt = errorMessageFormat(errorMessage(code));

  vsnprintf(buffer, maxLen, fmt.c_str(), args);
  throwErrorMessage(buffer);
}

String
ErrorHandler::errorMessageFormat(const char* msg) const
{
  constexpr auto maxLen = 1024;
  char buffer[maxLen];

  snprintf(buffer, maxLen, "Error: %s", msg);
  return buffer;
}

} // end namespace cg::parser
