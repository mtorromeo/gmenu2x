#include "pxml.h"
#include "tinyxml/tinyxml.h"

using namespace std;

PXml::PXml(string file) {
	valid = false;
	error = title = description = authorName = authorWebsite = category = exec = icon = "";
	version = osVersion = (SoftwareVersion){0,0,0,0};

	TiXmlDocument doc(file);
	if (doc.LoadFile()) {
		TiXmlHandle hDoc(&doc);
		TiXmlElement* pElem;
		
		pElem = hDoc.FirstChildElement().Element();
		TiXmlHandle hPXML(pElem);
		if (pElem) pElem = hPXML.FirstChildElement( "title" ).Element();
		if (pElem) {
			title = pElem->GetText();
			pElem = hPXML.FirstChildElement( "description" ).Element();
		}
		if (pElem) {
			description = pElem->GetText();
			pElem = hPXML.FirstChildElement( "author" ).Element();
		}
		if (pElem) {
			authorName = pElem->Attribute("name");
			authorWebsite = pElem->Attribute("website");
			
			pElem = hPXML.FirstChildElement( "version" ).Element();
		}
		if (pElem) {
			pElem->QueryIntAttribute("major", &version.major);
			pElem->QueryIntAttribute("minor", &version.minor);
			pElem->QueryIntAttribute("release", &version.release);
			pElem->QueryIntAttribute("build", &version.build);
			
			pElem = hPXML.FirstChildElement( "exec" ).Element();
		}
		if (pElem) {
			exec = pElem->GetText();
			
			pElem = hPXML.FirstChildElement( "category" ).Element();
		}
		if (pElem) {
			category = pElem->GetText();
			
			valid = true;
			
			//All required fields have been found, parsing optional fields
			pElem = hPXML.FirstChildElement("icon").Element();
			if (pElem) icon = pElem->GetText();
			
			pElem = hPXML.FirstChildElement( "osversion" ).Element();
			if (pElem) {
				pElem->QueryIntAttribute("major", &osVersion.major);
				pElem->QueryIntAttribute("minor", &osVersion.minor);
				pElem->QueryIntAttribute("release", &osVersion.release);
				pElem->QueryIntAttribute("build", &osVersion.build);
			}
		}
	} else {
		error = doc.ErrorDesc();
	}
}

bool PXml::isValid() {
	return valid;
}

string PXml::getTitle() {
	return title;
}

string PXml::getDescription() {
	return description;
}

string PXml::getAuthorName() {
	return authorName;
}

string PXml::getAuthorWebsite() {
	return authorWebsite;
}

string PXml::getCategory() {
	return category;
}

string PXml::getExec() {
	return exec;
}

string PXml::getIcon() {
	return icon;
}

SoftwareVersion PXml::getVersion() {
	return version;
}

string PXml::getVersionString() {
	string versionString = "";
	stringstream ss;
	ss << version.major << "." << version.minor << "." << version.release << "." << version.build;
	ss >> versionString;
	return versionString;
}

SoftwareVersion PXml::getOsVersion() {
	return osVersion;
}

string PXml::getOsVersionString() {
	string versionString = "";
	stringstream ss;
	ss << osVersion.major << "." << osVersion.minor << "." << osVersion.release << "." << osVersion.build;
	ss >> versionString;
	return versionString;
}

string PXml::getError() {
	return error;
}
