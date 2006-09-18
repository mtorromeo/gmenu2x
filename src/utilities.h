/***************************************************************************
 *   Copyright (C) 2006 by Massimiliano Torromeo   *
 *   massimiliano.torromeo@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef UTILITIES_H
#define UTILITIES_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

string trim(const string& s);
string strreplace (string orig, string search, string replace);

bool fileExists(string file);

int max (int a, int b);
int min (int a, int b);
int constrain (int x, int imin, int imax);

float max (float a, float b);
float min (float a, float b);
float constrain (float x, float imin, float imax);

bool split (vector<string> &vec, const string &str, const string &delim);

#endif
