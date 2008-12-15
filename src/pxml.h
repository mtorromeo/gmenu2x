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

#ifndef PXML_H_
#define PXML_H_

#include <string>

using std::string;

struct SoftwareVersion {
	int major, minor, release, build;
};

class PXml {
private:
	bool valid;
	string title, description, error, authorName, authorWebsite, category, exec, icon;
	SoftwareVersion version, osVersion;

public:
	PXml(string file);
	
	bool isValid();
	
	string getTitle();
	string getDescription();
	string getAuthorName();
	string getAuthorWebsite();
	string getCategory();
	string getExec();
	string getIcon();
	
	SoftwareVersion getVersion();
	string getVersionString();
	SoftwareVersion getOsVersion();
	string getOsVersionString();
	
	string getError();
};

#endif /*PXML_H_*/
