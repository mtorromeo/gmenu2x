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

//for browsing the filesystem
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <algorithm>
#include <cstring>

#include "filelister.h"
#include "utilities.h"
#include "gmenu2x.h"
#include "debug.h"

using namespace std;

FileLister::FileLister(const string &startPath, bool showDirectories, bool showFiles)
	: showDirectories(showDirectories), showFiles(showFiles) {
	setPath(startPath, false);
}

const string &FileLister::getPath() {
	return path;
}
void FileLister::setPath(const string &path, bool doBrowse) {
	this->path = path;
	if (this->path[path.length()-1]!='/')
		this->path += "/";
	if (doBrowse)
		browse();
}

const string &FileLister::getFilter() {
	return filter;
}
void FileLister::setFilter(const string &filter) {
	this->filter = filter;
}

void FileLister::browse() {
	directories.clear();
	files.clear();

	if (showDirectories || showFiles) {
		DIR *dirp;
		if ((dirp = opendir(path.c_str())) == NULL) {
			ERROR("Error: opendir(%s)", path.c_str());
			return;
		}

		vector<string> vfilter;
		split(vfilter, getFilter(), ",");

		string filepath, file;
		struct stat st;
		struct dirent *dptr;

		while ((dptr = readdir(dirp))) {
			file = dptr->d_name;
			if (file[0]=='.' && file!="..") continue;
			filepath = path+file;
			int statRet = stat(filepath.c_str(), &st);
			if (statRet == -1) {
				ERROR("Stat failed on '%s' with error '%s'", filepath.c_str(), strerror(errno));
				continue;
			}
			if (find(excludes.begin(), excludes.end(), file) != excludes.end())
				continue;

			if (S_ISDIR(st.st_mode)) {
				if (!showDirectories) continue;
#if defined(TARGET_GP2X) || defined(TARGET_WIZ) || defined(TARGET_CAANOO)
				if (!(path==CARD_ROOT && (file!="sd" && file!="ext" && file!="nand")))
#endif
					directories.push_back(file);
			} else {
				if (!showFiles) continue;
				for (vector<string>::iterator it = vfilter.begin(); it != vfilter.end(); ++it) {
					if (it->length() <= file.length()) {
						if (file.compare(file.length() - it->length(), it->length(), *it) == 0) {
							files.push_back(file);
							break;
						}
					}
				}
			}
		}

		closedir(dirp);
		sort(files.begin(), files.end(), case_less());
		sort(directories.begin(), directories.end(), case_less());
	}
}

uint FileLister::size() {
	return files.size()+directories.size();
}
uint FileLister::dirCount() {
	return directories.size();
}
uint FileLister::fileCount() {
	return files.size();
}

string FileLister::operator[](uint x) {
	return at(x);
}

string FileLister::at(uint x) {
	if (x>=size()) return "";
	if (x<directories.size())
		return directories[x];
	else
		return files[x-directories.size()];
}

bool FileLister::isFile(uint x) {
	return x >= directories.size() && x < size();
}

bool FileLister::isDirectory(uint x) {
	return x < directories.size();
}

void FileLister::insertFile(const string &file) {
	files.insert(files.begin(), file);
}

void FileLister::addExclude(const string &exclude) {
	excludes.push_back(exclude);
}
