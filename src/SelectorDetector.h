#ifndef SELECTORDETECTOR_H
#define SELECTORDETECTOR_H

/* This class is for handling applications that use Kounch's Selector, to correctly import their settings to GMenu
 * It provides interfaces to examine the gpe file to detect Selector and from there, parse the config files.
 */


 /*
#Selector configuration file
#Version 1.0

#selector-language english (and it doesn't work, crap)
langCode=EN         // ignore
layoutCode=0        // ignore

selectRectangle=2   // ignore

#Full path to skin files
skinPath=./         //  use possibly

#command line
cmdLine=./race      //  USE

#path to base directory for file explorer
baseDir=/mnt/sd/roms/ngpc/      //  USE

#File filters                   //  USE
fileFilter=ngp
fileFilter=ngc
fileFilter=npc
 */
#include <string>

using std::string;
class SelectorDetector
{
    public:
        SelectorDetector();
        SelectorDetector(string config);
        ~SelectorDetector();

        bool readSelectorConfig(string config);

        string getApplication(){return application;}
        string getFilePath(){return filePath;}
        string getFilters(){return filters;}

    private:
        bool useSelectorBackground;
        string application;
        string filePath;
        string filters;
        //bool isSelectorGPE(string gpe);
        //string getSelectorConfig(string gpe);       //  Looks in the GPE for the location of the selectorconfig
};

#endif // SELECTORDETECTOR_H
