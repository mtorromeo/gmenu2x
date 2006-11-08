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

#ifndef FILELISTER_H_
#define FILELISTER_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

class FileLister {
private:
	string path, filter;
	bool showDirectories, showFiles;

public:
	FileLister(string startPath, bool showDirectories = true, bool showFiles = true);
	void browse();

	vector<string> directories, files;
	uint size();
	uint dirCount();
	uint fileCount();
	string operator[](uint);
	bool isFile(uint);
	bool isDirectory(uint);

	string getPath();
	void setPath(string path);
	string getFilter();
	void setFilter(string filter);
};

#endif /*FILELISTER_H_*/
