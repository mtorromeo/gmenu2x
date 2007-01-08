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
#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "utilities.h"

/**
Hash Map of translation strings.

	@author Massimiliano Torromeo <massimiliano.torromeo@gmail.com>
*/
class Translator {
private:
	string _lang;
	hash_map<string, string> translations;

public:
	Translator(string lang="");
	~Translator();

	string lang();
	void setLang(string lang);
	bool exists(string term);
	string translate(string term,const char *replacestr=NULL,...);
	string operator[](string term);
};

#endif
