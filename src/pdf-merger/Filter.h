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


#if !defined Filter_h
#define Filter_h

#include <vector>
#include <map>
#include <string>

namespace merge_lib
{
   class Object;
    class Decoder;
   //this class is needed to parse object in order to create
   //all decoders to decode object's stream
   class Filter
   {
   public:
      Filter(Object * objectWithStream): _objectWithStream(objectWithStream)
      {
         _createAllDecodersSet();
      }
      virtual ~Filter();
      //replace coded stream with decoded
      void getDecodedStream(std::string & stream);
   private:
      //methods

      //parse object's content and fill out vector with
      //necessary decoders
      std::vector <Decoder * > _getDecoders();
      void _createAllDecodersSet();

      //members
      Object * _objectWithStream;
      static std::map<std::string, Decoder *> _allDecoders;
   };
}
#endif

