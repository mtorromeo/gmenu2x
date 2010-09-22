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

#include <linux/types.h>

#define GP2X_CLK_FREQ 7372800

// pickle add support for caanoo analog stick
#if defined(TARGET_CAANOO)
    #define MAX_JOY_MOTION              1000    // This value works good so that diag directions are simulated
    #define CAANOO_UP                   (0x1)
    #define CAANOO_DOWN                 (0x2)
    #define CAANOO_LEFT                 (0x4)
    #define CAANOO_RIGHT                (0x8)    
    
    #define GP2X_BUTTON_UP              (11)    // Directional dummies for Caanoo
    #define GP2X_BUTTON_DOWN            (12)
    #define GP2X_BUTTON_LEFT            (13)
    #define GP2X_BUTTON_RIGHT           (14)
    #define GP2X_BUTTON_UPLEFT          (15)
    #define GP2X_BUTTON_UPRIGHT         (16)
    #define GP2X_BUTTON_DOWNLEFT        (17)
    #define GP2X_BUTTON_DOWNRIGHT       (18)
    #define GP2X_BUTTON_CLICK           (19)
    #define GP2X_BUTTON_A               (0)
    #define GP2X_BUTTON_B               (2)
    #define GP2X_BUTTON_X               (1)
    #define GP2X_BUTTON_Y               (3)
    #define GP2X_BUTTON_L               (4)
    #define GP2X_BUTTON_R               (5)
    #define GP2X_BUTTON_START           (9)     // Help 2
    #define GP2X_BUTTON_SELECT          (8)     // Help 1
    #define GP2X_BUTTON_HOME            (6)     // Home (caanoo only)
    #define GP2X_BUTTON_VOLUP           (20)    // doesnt exist on caanoo, but need a define
    #define GP2X_BUTTON_VOLDOWN         (21)    // same as above
#else
    #define GP2X_BUTTON_UP              (0)
    #define GP2X_BUTTON_DOWN            (4)
    #define GP2X_BUTTON_LEFT            (2)
    #define GP2X_BUTTON_RIGHT           (6)
    #define GP2X_BUTTON_UPLEFT          (1)
    #define GP2X_BUTTON_UPRIGHT         (7)
    #define GP2X_BUTTON_DOWNLEFT        (3)
    #define GP2X_BUTTON_DOWNRIGHT       (5)
    #define GP2X_BUTTON_CLICK           (18)
    #define GP2X_BUTTON_A               (12)
    #define GP2X_BUTTON_B               (13)
    #define GP2X_BUTTON_START           (8)
    #define GP2X_BUTTON_SELECT          (9)
    #define GP2X_BUTTON_VOLUP           (16)
    #define GP2X_BUTTON_VOLDOWN         (17)
    
#ifdef GP2X_OLDSDL_FIX
        #define GP2X_BUTTON_X           (15)
        #define GP2X_BUTTON_Y           (14)
        #define GP2X_BUTTON_L           (11)
        #define GP2X_BUTTON_R           (10)
#else
        #define GP2X_BUTTON_X           (14)
        #define GP2X_BUTTON_Y           (15)
        #define GP2X_BUTTON_L           (10)
        #define GP2X_BUTTON_R           (11)
#endif    
#endif

#define FBMMSP2CTRL 0x4619
