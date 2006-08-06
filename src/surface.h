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
#ifndef SURFACE_H
#define SURFACE_H

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

using std::string;

/**
Wrapper around SDL_Surface

	@author Massimiliano Torromeo <massimiliano.torromeo@gmail.com>
*/
class Surface {
private:
	bool locked;

public:
	Surface();
	Surface(string img);
	Surface(int w, int h);
	~Surface();

	SDL_Surface *raw;

	void free();
	void load(string img);
	void lock();
	void unlock();
	void flip();
	void putPixel(int,int,Uint32);
	bool blit(Surface *destination, int x, int y);
	bool blit(SDL_Surface *destination, int x, int y);
};

#endif
