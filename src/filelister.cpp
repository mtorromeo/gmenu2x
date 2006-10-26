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

#include "filelister.h"
#include "utilities.h"

using namespace std;

FileLister::FileLister(string startPath, bool showDirectories, bool showFiles) {
	this->showDirectories = showDirectories;
	this->showFiles = showFiles;
	setPath(startPath);
}

string FileLister::getPath() {
	return path;
}
void FileLister::setPath(string path) {
	this->path = path;
	browse();
}

string FileLister::getFilter() {
	return filter;
}
void FileLister::setFilter(string filter) {
	this->filter = filter;
}

void FileLister::browse() {
	directories.clear();
	files.clear();
	
	if (showDirectories || showFiles) {
		DIR *dirp;
		if ((dirp = opendir(path.c_str())) == NULL) return;

		vector<string> vfilter;
		split(vfilter,getFilter(),",");

		string filepath;
		struct stat st;
		struct dirent *dptr;

		while ((dptr = readdir(dirp))) {
			if (dptr->d_name[0]=='.') continue;
			filepath = path+dptr->d_name;
			int statRet = stat(filepath.c_str(), &st);
			if (statRet == -1) continue;

			if (S_ISDIR(st.st_mode)) {
				if (!showDirectories) continue;
				directories.push_back(dptr->d_name);
			} else {
				if (!showFiles) continue;
				bool filterOk = false;
				string file = dptr->d_name;
				for (uint i = 0; i<vfilter.size() && !filterOk; i++)
					filterOk = file.substr(file.length()-vfilter[i].length(),vfilter[i].length())==vfilter[i];
				if (filterOk) files.push_back(file);
			}
		}
	
		closedir(dirp);
		sort(files.begin(),files.end(),case_less());
		sort(directories.begin(),directories.end(),case_less());
	}
}
