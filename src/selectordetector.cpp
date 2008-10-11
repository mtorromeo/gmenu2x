#include "selectordetector.h"

SelectorDetector::SelectorDetector() {
    //ctor
    useSelectorBackground = false;
}

SelectorDetector::SelectorDetector(string config) {
    useSelectorBackground = false;
    readSelectorConfig(config);
}

SelectorDetector::~SelectorDetector() {
    //dtor
}

bool SelectorDetector::readSelectorConfig(string config) {
	if (fileExists(config)) {
		ifstream inf(config.c_str(), ios_base::in);
		if (inf.is_open()) {
			string line;
			while (getline(inf, line, '\n')) {
				string::size_type pos = line.find("=");
				string name = trim(line.substr(0,pos));
				string value = trim(line.substr(pos+1,line.length()));

				if (name=="cmdLine") application = value;
				else if (name=="baseDir") filePath = value;
				else if (name=="fileFilter"){
				    if(filters.empty())
                        filters = value;
                    else
                        filters += ("," + value;)
				}
			}
			inf.close();
			return true;
		}
	}
	return false;
}
