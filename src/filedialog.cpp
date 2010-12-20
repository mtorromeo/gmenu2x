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

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

//for browsing the filesystem
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include "filedialog.h"
#include "gmenu2x.h"

using namespace std;

FileDialog::FileDialog(GMenu2X *gmenu2x, const string &text, const string &filter, const string &file, const string &title)
	: BrowseDialog(gmenu2x, title, text) {
	string path = CARD_ROOT;
	if (!file.empty()) {
		string::size_type pos = file.rfind("/");
		if (pos != string::npos)
			path = file.substr(0, pos);
	}
	fl = new FileLister(path);
	fl->setFilter(filter);
}

FileDialog::~FileDialog() {
	delete fl;
}

bool FileDialog::exec() {
	// FileDialog must only pick regular files.
	return BrowseDialog::exec() && !fl->isDirectory(selected);
}
