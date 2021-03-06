/*
 * Copyright (C) 2012 Webdoc SA
 *
 * This file is part of Open-Sankoré.
 *
 * Open-Sankoré is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License,
 * with a specific linking exception for the OpenSSL project's
 * "OpenSSL" library (or with modified versions of it that use the
 * same license as the "OpenSSL" library).
 *
 * Open-Sankoré is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Open-Sankoré.  If not, see <http://www.gnu.org/licenses/>.
 */


#if !defined Utils_h
#define Utils_h

#include "Config.h"

#include <stdlib.h>
#include <string>
#include <time.h>
#include <stdio.h>

namespace merge_lib
{
   class Utils
   {
   public:
      static int stringToInt(const std::string & str); //throw ConvertException
      static std::string uIntToStr(unsigned int integer);
      static std::string doubleToStr(double doubleValue);
      static double stringToDouble(const std::string & s );
      static bool doubleEquals(const double left,const double right, const double epsilon = +1.e-10);
      static double normalizeValue(double &val,const double epsilon = +1.e-10);
      static unsigned long getFileSize(const char * fileName);

   private:
      static int _stringToInt(const std::string & str); //throw ConvertException
      static int _stringToInt(std::string & str); //throw ConvertException
   };



}
#endif
