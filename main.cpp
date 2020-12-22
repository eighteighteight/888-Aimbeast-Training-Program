/*
 Copyright (C) 2020 eighteighteight

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.*/

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include "json.hpp"
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <fileapi.h>
#include <cstdlib>
#include <random>

void sleep(int seconds) {
    Sleep(seconds * 1000);
}

void clear_screen(char fill = ' ') {
    COORD tl = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}

using json = nlohmann::json;
json config;

bool config_exist;

bool DoesFileExist(LPCWSTR pszFilename) {
    DWORD dwAttrib = GetFileAttributes(reinterpret_cast<LPCSTR>(pszFilename));
    if (!(dwAttrib & FILE_ATTRIBUTE_DEVICE) &&
        !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
        return true;
    }
    return false;
}

enum CATEGORIES {
    FLICKING, TRACKING, SPEED
};

enum DIFFICULTIES {
    EASY, MEDIUM, HARD, INTENSE
};

class Difficulties {
public:
    const std::vector<DIFFICULTIES> DIFFI = {EASY, MEDIUM, HARD, INTENSE};
    bool mastery_toggle = false;
};

class Maps : public Difficulties {
public:
    void get_maps(CATEGORIES, DIFFICULTIES);

    std::vector<std::string> map4;
};

void Maps::get_maps(CATEGORIES category, DIFFICULTIES difficulty) {
    switch (category) {
        case CATEGORIES::FLICKING:
            if (mastery_toggle) {
                map4 = {
                        "DRIMZI 6 DOTS WIDE XXS",
                        "NFNT SIMPLE POP",
                        "DRIMZI REACTION FLICK S"
                };
            } else {
                switch (difficulty) {
                    case DIFFICULTIES::INTENSE:
                        map4 = {
                                "DRIMZI 6 DOTS WIDE XS",
                                "DRIMZI 6 DOTS XXS",
                                "DRIMZI 6 DOTS WIDE XXS",
                                "NFNT SPEED STICK FLICK",
                                "NFNT JUGGLING CIMBER",
                                "NFNT SIMPLE POP",
                                "DRIMZI REACTION FLICK L",
                                "DRIMZI REACTION FLICK M",
                                "DRIMZI REACTION FLICK S"
                        };
                        break;
                    case DIFFICULTIES::HARD:
                        map4 = {
                                "DRIMZI 2 DOTS XS",
                                "DRIMZI 6 DOTS XS",
                                "DRIMZI MICRO GRID S",
                                "NFNT SHOOTING STAR",
                                "NFNT CLAY PIGEON SHOOTING",
                                "NFNT DOME FLICK",
                                "DRIMZI PRESSURE 03",
                                "DRIMZI PRESSURE 06",
                                "DRIMZI PRESSURE 09"
                        };
                        break;
                    case DIFFICULTIES::MEDIUM:
                        map4 = {
                                "DRIMZI FRENZY WIDE S",
                                "DRIMZI FRENZY XS",
                                "DRIMZI 6 DOTS WIDE S",
                                "NFNT TILE FRENZY",
                                "NFNT MOMENTARY FIRE",
                                "NFNT RAILWAY SHOOTER",
                                "DRIMZI PRESSURE 02",
                                "DRIMZI PRESSURE 05",
                                "DRIMZI PRESSURE 08"
                        };
                        break;
                    case DIFFICULTIES::EASY:
                        map4 = {
                                "DRIMZI FRENZY S",
                                "DRIMZI 2 DOTS S",
                                "DRIMZI 6 DOTS S",
                                "NFNT BARCODE FLICK",
                                "NFNT FIREWORKS FLICK",
                                "NFNT SQUARE FRENZY",
                                "DRIMZI PRESSURE 01",
                                "DRIMZI PRESSURE 04",
                                "DRIMZI PRESSURE 07"
                        };
                        break;
                    default:
                        break;
                }
            }
            break;
        case CATEGORIES::TRACKING:
            if (mastery_toggle) {
                map4 = {
                        "GOOBS SPHERE TARGET SWITCHING",
                        "NFNT CRAB WALKING TRACKING",
                        "1 WALL 5 TARGETS PASU TRACK MINI"
                };
            } else {
                switch (difficulty) {
                    case DIFFICULTIES::INTENSE:
                        map4 = {
                                "GOOBS HEAD GLITCH TRACKING",
                                "PYRA TRACK 180",
                                "GOOBS SPHERE TARGET SWITCHING",
                                "NFNT SPEED STICK TRACK",
                                "NFNT NARROW STRAFE",
                                "NFNT CRAB WALKING TRACKING",
                                "VERTICAL TRACKING MIDAIR NANO",
                                "SHINYY HARD TRACKING",
                                "1 WALL 5 TARGETS PASU TRACK MINI"
                        };
                        break;
                    case DIFFICULTIES::HARD:
                        map4 = {
                                "GOOBS AIR INVINCIBLE EASY",
                                "GOOBS JIM TRACKING",
                                "GOOBS BOWL",
                                "NFNT EDGE TRACKING",
                                "NFNT DOME TRACK INVINCIBLE",
                                "NFNT DOME BOUNCE TRACK",
                                "POWDER RING AROUND THE DOT TRACKING",
                                "GOOBS SMOOTHBOT INVINCIBLE",
                                "XOLO MOUSE CONTROL MADNESS"
                        };
                        break;
                    case DIFFICULTIES::MEDIUM:
                        map4 = {
                                "GOOBER SIMPLE TRACKING",
                                "GOOBS ASCENDED TRACKING 90",
                                "GOOBS DOWNWARD TRACKING",
                                "NFNT FOUNTAIN TRACKING",
                                "GOOBS BOUNCE 360 TRACKING",
                                "NFNT EDGE TRACKING SLOW",
                                "TRACKING 4 FLOORS",
                                "BOUNCER TRACK V2 HARD",
                                "HC AIR TRACK"
                        };
                        break;
                    case DIFFICULTIES::EASY:
                        map4 = {
                                "GOOBS SMOOTHNESS TRAINER V2",
                                "GOOBS RAMP TRACKING",
                                "GOOBS TRACKING EXPERIENCE EASY",
                                "NFNT SIMPLE STRAFE",
                                "NFNT LINEAR TRACKING",
                                "NFNT VARIOUS DIRECTIONS",
                                "GOOBS CLS",
                                "CLOSE LONG STRAFES INV",
                                "TEABAGGING TRACKING HARD"
                        };
                        break;
                    default:
                        break;
                }
            }
            break;
        case CATEGORIES::SPEED:
            if (mastery_toggle) {
                map4 = {
                        "S02 DRIMZI REACTION FLICK S",
                        "NFNT QUICK FLICK",
                        "DREKES 200MS FLICK"
                };
            } else {
                switch (difficulty) {
                    case DIFFICULTIES::HARD:
                        map4 = {
                                "1 TARGET REACTION MEDIUM",
                                "KING FLICK EASY",
                                "S02 DRIMZI REACTION FLICK PRACTICE ONE",
                                "S02 DRIMZI REACTION FLICK PRACTICE TWO",
                                "DREKES 300MS FLICK",
                                "NFNT DOME BOUNCE",
                                "GOOBS REFLEX FLICK MINI RELOAD",
                                "FLICK TIME SMALL",
                                "SHINYY FLICK TIME HARD"
                        };
                        break;
                    case DIFFICULTIES::MEDIUM:
                        map4 = {
                                "KANDO SNAP TRACKING",
                                "TARGET SWITCH 360 STATIC",
                                "SHINYY SMALL AND PRECISE",
                                "FAST PUMP FLICK 180 EASY",
                                "FAST PUMP FLICK 180",
                                "SHINYY FLICK TIME MEDIUM",
                                "ENTRY AND SEARCH",
                                "S02 DRIMZI REACTION FLICK S",
                                "FAST PUMP FLICK 180 HARD"
                        };
                        break;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }
}

class Main : public Maps {
public:
    enum dDIFF_COUNTS {
        EASY = 2, MEDIUM = 3, HARD = 3, INTENSE = 2
    };
    const std::vector<dDIFF_COUNTS> Diffs = {EASY, MEDIUM, HARD, INTENSE};
    std::vector<dDIFF_COUNTS> dDiffs = {EASY, MEDIUM, HARD, INTENSE};
    std::vector<std::vector<CATEGORIES>> cat_vec{
            {FLICKING, TRACKING},
            {FLICKING, TRACKING, SPEED},
            {FLICKING, TRACKING, SPEED},
            {FLICKING, TRACKING}
    };
};

std::string name {"Default"};
const double default_train_time = 30.0;
int todays_train_time = default_train_time;
int user_default_train_time = default_train_time;
// 2 easy, 3 medium, 3 hard, 2 intense
const Main DEFAULT_DIF_COUNT{};


bool selection_check() {
    std::string selection;
    while (true) {
        std::cin.clear();
        std::cin >> selection;
        std::cin.ignore();
        if (selection == "y" || selection == "Y") {
            return true;
        } else if (selection == "n" || selection == "N") {
            return false;
        } else {
            std::cout << "Invalid selection." << std::endl;
            std::cout << "Please try again." << std::endl << ":";
        }
    }
}

double flicking_cum{};
double tracking_cum{};
double speed_cum{};

void settings() {
    std::string selection;
    while (selection != "0") {
        clear_screen();
        std::cout << "1 - Name: " << config["name"] << std::endl;
        std::cout
                << "--------------------------------------------------------------------------------------------------\n";
        std::cout << "2 - Default training time: " << config["default_time"] << std::endl;
        std::cout
                << "--------------------------------------------------------------------------------------------------\n";
        std::cout << "Please select a number to edit or exit by typing 0" << std::endl;
        std::cout << ":";
        std::cin.clear();
        std::cin >> selection;
        std::cin.ignore();
        if (selection == "1") {
            clear_screen();
            std::cout << "Please type the name you would like to be changed to." << std::endl;
            std::cin.clear();
            std::string sel{};
            std::cin >> sel;
            config["name"] = sel;
            std::cin.ignore();
        } else if (selection == "2") {
            clear_screen();
            std::cout << "Please type the number you would like default time be changed to.\n:";
            std::cin.clear();
            int def_t{};
            std::cin >> def_t;
            while (std::cin.fail()){
                std::cout << "Invalid input. Input must be a positive number.Try again\n:";
                std::cin >> def_t;
            }
            while (def_t < 0){
                std::cout << "Invalid input. Input must be a positive number.Try again\n:";
                std::cin >> def_t;
            }
            config["default_time"] = def_t;
            std::cin.ignore();
        }
    }
}

void stats() {
    clear_screen();
    if (config["mastery_flicking"]) {
        std::cout << "Flicking level: Mastery" << std::endl;
    } else {
        std::cout << "Flicking level: " << config["flicking_level"] << std::endl;
        std::cout << "Flicking cumulative score: " << config["flicking_cum"] << std::endl;
    }
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    if (config["mastery_tracking"]) {
        std::cout << "Tracking level: Mastery" << std::endl;
    } else {
        std::cout << "Tracking level: " << config["tracking_level"] << std::endl;
        std::cout << "Tracking cumulative score: " << config["tracking_cum"] << std::endl;
    }
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    if (config["mastery_speed"]) {
        std::cout << "Speed level: Mastery" << std::endl;
    } else {
        std::cout << "Speed level: " << config["speed_level"] << std::endl;
        std::cout << "Speed cumulative score: " << config["speed_cum"] << std::endl;
    }
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    std::cout << "Last date day peformance tested: " << config["last_per_test"]
              << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    std::cout << "Enter anything to leave.\n:";
    std::string sell{};
    std::cin.clear();
    std::cin.ignore();
    std::getline(std::cin, sell);
    std::cin.clear();
}

int peformance_test(bool just_time) {
    Main c;
    int map_count{};
    int flicking_level{config["flicking_level"]};
    int tracking_level{config["tracking_level"]};
    int speed_level{config["speed_level"]};
    int flicking{};
    int tracking{};
    int speed{};
    if (just_time == false) {
        for (int i = 0; i < c.cat_vec.size(); ++i) {
            c.mastery_toggle = false;
            for (int i2 = 0; i2 < c.cat_vec.at(i).size(); ++i2) {
                if (c.cat_vec.at(i).at(i2) == FLICKING && i2 == 0 && config["mastery_flicking"] == false) {
                    clear_screen();
                    std::cout << "Train each map for the default time." << std::endl;
                    std::cout << "LEVEL " << flicking_level << std::endl;
                    DIFFICULTIES dTrack;
                    if (i == 0) {
                        dTrack = EASY;
                        std::cout << "\t|EASY" << std::endl;
                    } else if (i == 1) {
                        dTrack = MEDIUM;
                        std::cout << "\t|MEDIUM" << std::endl;
                    } else if (i == 2) {
                        dTrack = HARD;
                        std::cout << "\t|HARD" << std::endl;
                    } else if (i == 3) {
                        dTrack = INTENSE;
                        std::cout << "\t|INTENSE" << std::endl;
                    }
                    c.get_maps(FLICKING, dTrack);
                    std::cout << "\t\t|FLICKING" << std::endl;
                    std::cout << "\t\t\t|" << c.map4.at(flicking_level - 1) << std::endl;
                    std::cout << "\t\t\t\tEnter today's highscore.\n\t\t\t\t:";
                    std::cin.clear();
                    std::cin >> flicking;
                    flicking_cum += flicking;
                    ++map_count;
                } else if (c.cat_vec.at(i).at(i2) == TRACKING && i2 == 1 && config["mastery_tracking"] == false) {
                    clear_screen();
                    std::cout << "Train each map for the default time." << std::endl;
                    std::cout << "LEVEL " << tracking_level << std::endl;
                    DIFFICULTIES dTrack;
                    if (i == 0) {
                        dTrack = EASY;
                        std::cout << "\t|EASY" << std::endl;
                    } else if (i == 1) {
                        dTrack = MEDIUM;
                        std::cout << "\t|MEDIUM" << std::endl;
                    } else if (i == 2) {
                        dTrack = HARD;
                        std::cout << "\t|HARD" << std::endl;
                    } else if (i == 3) {
                        dTrack = INTENSE;
                        std::cout << "\t|INTENSE" << std::endl;
                    }
                    c.get_maps(TRACKING, dTrack);
                    std::cout << "\t\t|TRACKING" << std::endl;
                    std::cout << "\t\t\t|" << c.map4.at(tracking_level - 1) << std::endl;
                    std::cout << "\t\t\t\tEnter today's highscore.\n\t\t\t\t:";
                    std::cin.clear();
                    std::cin >> tracking;
                    tracking_cum += tracking;
                    ++map_count;
                } else if (c.cat_vec.at(i).size() == 3 && i2 == 2 && config["mastery_speed"] == false) {
                    clear_screen();
                    std::cout << "Train each map for the default time." << std::endl;
                    std::cout << "LEVEL " << speed_level << std::endl;
                    DIFFICULTIES dTrack;
                    if (i == 0) {
                        dTrack = EASY;
                        std::cout << "\t|EASY" << std::endl;
                    } else if (i == 1) {
                        dTrack = MEDIUM;
                        std::cout << "\t|MEDIUM" << std::endl;
                    } else if (i == 2) {
                        dTrack = HARD;
                        std::cout << "\t|HARD" << std::endl;
                    } else if (i == 3) {
                        dTrack = INTENSE;
                        std::cout << "\t|INTENSE" << std::endl;
                    }
                    c.get_maps(SPEED, dTrack);
                    std::cout << "\t\t|SPEED" << std::endl;
                    std::cout << "\t\t\t|" << c.map4.at(speed_level - 1) << std::endl;
                    std::cout << "\t\t\t\tEnter today's highscore.\n\t\t\t\t:";
                    std::cin.clear();
                    std::cin >> speed;
                    speed_cum += speed;
                    ++map_count;
                }
            }
            std::cout
                    << "----------------------------------------------------------------------------------------------\n";
        }
        clear_screen();
        std::cout << map_count << " minutes." << std::endl;
        int flicking_plat = config["flicking_plat"];
        int tracking_plat = config["tracking_plat"];
        int speed_plat = config["speed_plat"];

        int conf_flicking_cum = config["flicking_cum"];
        int conf_tracking_cum = config["tracking_cum"];
        int conf_speed_cum = config["speed_cum"];

        if (!config["mastery_flicking"]) {
            if (flicking_cum < (conf_flicking_cum + conf_flicking_cum * 0.05) &&
                flicking_cum > (conf_flicking_cum + conf_flicking_cum * -0.05)) {
                if (flicking_plat == 3) {
                    if (flicking_level == 9)
                        config["mastery_flicking"] = true;
                    else {
                        ++flicking_level;
                        flicking_plat = 0;
                    }
                } else {
                    ++flicking_plat;
                }
            } else if (flicking_cum > (conf_flicking_cum + conf_flicking_cum * 0.05)) {
                flicking_plat = 0;
            }
            std::cout << flicking_cum << " flicking cum score." << std::endl;
        }
        if (!config["mastery_tracking"]) {
            if (tracking_cum < (conf_tracking_cum + conf_tracking_cum * 0.05) &&
                tracking_cum > (conf_tracking_cum + conf_tracking_cum * -0.05)) {
                if (tracking_plat == 3) {
                    if (tracking_level == 9)
                        config["mastery_tracking"] = true;
                    else {
                        ++tracking_level;
                        tracking_plat = 0;
                    }
                } else {
                    ++tracking_plat;
                }
            } else if (tracking_cum > (conf_tracking_cum + conf_tracking_cum * 0.05)) {
                tracking_plat = 0;
            }
            std::cout << tracking_cum << " tracking cum score." << std::endl;
        }
        if (!config["mastery_speed"]) {
            if (speed_cum < (conf_speed_cum + conf_speed_cum * 0.05) &&
                speed_cum > (conf_speed_cum + conf_speed_cum * -0.05)) {
                if (speed_plat == 3) {
                    if (speed_level == 9)
                        config["mastery_speed"] = true;
                    else {
                        ++speed_level;
                        speed_plat = 0;
                    }
                } else {
                    ++speed_plat;
                }
            } else if (speed_cum > (conf_speed_cum + conf_speed_cum * 0.05)) {
                speed_plat = 0;
            }
            std::cout << speed_cum << " speed cum score." << std::endl;
        }
        config["flicking_cum"] = flicking_cum;
        config["tracking_cum"] = tracking_cum;
        config["speed_cum"] = speed_cum;
        config["flicking_plat"] = flicking_plat;
        config["tracking_plat"] = tracking_plat;
        config["speed_plat"] = speed_plat;
        config["flicking_level"] = flicking_level;
        config["tracking_level"] = tracking_level;
        config["speed_level"] = speed_level;
        std::cout << "Enter anything to leave.\n:";
        std::string sell{};
        std::cin.clear();
        std::cin.ignore();
        std::getline(std::cin, sell);
        std::cin.clear();
        SYSTEMTIME cur_time{};
        GetLocalTime(&cur_time);
        config["last_per_test"] = static_cast<WORD>(cur_time.wDay);
        config["t_ns"] = false;
    } else {
        for (int i = 0; i < c.cat_vec.size(); ++i) {
            c.mastery_toggle = false;
            for (int i2 = 0; i2 < c.cat_vec.at(i).size(); ++i2) {
                if (c.cat_vec.at(i).at(i2) == FLICKING && i2 == 0 && config["mastery_flicking"] == false) {
                    DIFFICULTIES dTrack;
                    if (i == 0) {
                        dTrack = EASY;
                    } else if (i == 1) {
                        dTrack = MEDIUM;
                    } else if (i == 2) {
                        dTrack = HARD;
                    } else if (i == 3) {
                        dTrack = INTENSE;
                    }
                    c.get_maps(FLICKING, dTrack);
                    ++map_count;
                } else if (c.cat_vec.at(i).at(i2) == TRACKING && i2 == 1 && config["mastery_tracking"] == false) {
                    DIFFICULTIES dTrack;
                    if (i == 0) {
                        dTrack = EASY;
                    } else if (i == 1) {
                        dTrack = MEDIUM;
                    } else if (i == 2) {
                        dTrack = HARD;
                    } else if (i == 3) {
                        dTrack = INTENSE;
                    }
                    c.get_maps(TRACKING, dTrack);
                    ++map_count;
                } else if (c.cat_vec.at(i).size() == 3 && i2 == 2 && config["mastery_speed"] == false) {
                    DIFFICULTIES dTrack;
                    if (i == 0) {
                        dTrack = EASY;
                    } else if (i == 1) {
                        dTrack = MEDIUM;
                    } else if (i == 2) {
                        dTrack = HARD;
                    } else if (i == 3) {
                        dTrack = INTENSE;
                    }
                    c.get_maps(SPEED, dTrack);
                    ++map_count;
                }
            }
        }
    }
    std::cin.clear();
    return map_count;
}

void train() {
    clear_screen();
    const int flicking_level{config["flicking_level"]};
    const int tracking_level{config["tracking_level"]};
    const int speed_level{config["speed_level"]};
    std::cout << "How long long would you like to train for ? (minutes, 0=default)" << std::endl << ":";
    std::cin.clear();
    std::cin >> todays_train_time;
    while (std::cin.fail()){
        std::cout << "Invalid input. Input must be a positive number.Try again\n:";
        std::cin >> todays_train_time;
    }
    while (todays_train_time < 0){
        std::cout << "Invalid input. Input must be a positive number.Try again\n:";
        std::cin >> todays_train_time;
    }
    sleep(1);
    clear_screen();
    if (todays_train_time == 0) {
        todays_train_time = config["default_time"];
    }
    if (config["asked_default_time"] == false) {
        std::cin.clear();
        std::cout << "Would you like " << todays_train_time << " to be the default time? (y/n)" << std::endl << ":";
        bool selection = selection_check();
        config["asked_default_time"] = true;
        if (selection) {
            user_default_train_time = todays_train_time;
            std::cout << "Default time changed." << std::endl;
            sleep(1);
            clear_screen();
        } else {
            std::cout << "Default time unchanged." << std::endl;
            sleep(1);
            clear_screen();
        }
        config["default_time"] = user_default_train_time;
    }
    if (todays_train_time == 0)
        todays_train_time = config["default_time"];

    bool perf_test{};
    SYSTEMTIME cur_time{};
    GetLocalTime(&cur_time);
    WORD conf_time_day = config["last_per_test"];
    if (config["t_ns"]) {
            std::cout << "Would you like to account for your daily performance test? (y/n)\n:";
            perf_test = selection_check();
            if (perf_test) {
                std::cout << "Performance test accounted for.\n";
                todays_train_time -= peformance_test(true);
            } else
                std::cout << "Performance test not accounted for.\n";
    } else {
        if (cur_time.wDay - conf_time_day >= 1) {
            std::cout << "Would you like to account for your daily performance test? (y/n)\n:";
            perf_test = selection_check();
            if (perf_test) {
                std::cout << "Performance test accounted for.\n";
                todays_train_time -= peformance_test(true);
            } else
                std::cout << "Performance test not accounted for.\n";
        }
    }
    clear_screen();
    double time_percent_dif = todays_train_time / default_train_time;
    Main c;
    for (int i = 0; i < DEFAULT_DIF_COUNT.dDiffs.size(); ++i) {
        c.dDiffs.at(i) = static_cast<Main::dDIFF_COUNTS>(DEFAULT_DIF_COUNT.dDiffs.at(i) * time_percent_dif);
        //std::cout << c.dDiffs.at(i) << std::endl;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> zero_one(0,1);
    std::uniform_int_distribution<> zero_two(0,2);
    std::uniform_int_distribution<> zero_three(0,3);

    if (c.dDiffs.at(0) % 2 == 0)
        c.cat_vec.at(0) = {FLICKING, TRACKING};
    else if (c.dDiffs.at(0) == 0)
        c.cat_vec.at(0) = {};
    else if (c.dDiffs.at(0) == 1){
        int z_o {zero_one(gen)};
        if (z_o == 0)
            c.cat_vec.at(0) = {FLICKING};
        else
            c.cat_vec.at(0) = {TRACKING};
    }

    if (c.dDiffs.at(1) % 3 == 0)
        c.cat_vec.at(1) = {FLICKING, TRACKING, SPEED};
    else if (c.dDiffs.at(1) % 2 == 0)
        c.cat_vec.at(1) = {FLICKING, TRACKING};
    else if (c.dDiffs.at(1) == 0)
        c.cat_vec.at(1) = {};
    else if (c.dDiffs.at(2) == 1) {
        int z_t {zero_two(gen)};
        if (z_t == 0)
            c.cat_vec.at(1) = {FLICKING};
        if (z_t == 1)
            c.cat_vec.at(1) = {TRACKING};
        else
            c.cat_vec.at(1) = {SPEED};
    }

    if (c.dDiffs.at(2) % 3 == 0)
        c.cat_vec.at(2) = {FLICKING, TRACKING, SPEED};
    else if (c.dDiffs.at(2) % 2 == 0)
        c.cat_vec.at(2) = {FLICKING, TRACKING};
    else if (c.dDiffs.at(2) == 0)
        c.cat_vec.at(2) = {};
    else if (c.dDiffs.at(2) == 1) {
        int z_t {zero_two(gen)};
        if (z_t == 0)
            c.cat_vec.at(2) = {FLICKING};
        if (z_t == 1)
            c.cat_vec.at(2) = {TRACKING};
        else
            c.cat_vec.at(2) = {SPEED};
    }

    if (c.dDiffs.at(3) % 2 == 0)
        c.cat_vec.at(3) = {FLICKING, TRACKING};
    else if (c.dDiffs.at(3) == 0)
        c.cat_vec.at(3) = {};
    else if (c.dDiffs.at(3) == 1){
        int z_o {zero_one(gen)};
        if (z_o == 0)
            c.cat_vec.at(3) = {FLICKING};
        else
            c.cat_vec.at(3) = {TRACKING};
    }

    int map_counter{};

    if (config["mastery_flicking"] == true) {
        c.mastery_toggle = zero_one(gen);
        c.get_maps(FLICKING, c.DIFFI.at(zero_three(gen)));
        std::cout << "MASTERY" << std::endl;
        std::cout << "\t|FLICKING" << std::endl;
        std::uniform_int_distribution<> m(0,c.map4.size());
        for (int j = m(gen); j < c.map4.size(); ++j) {
            ++map_counter;
            std::cout << "\t\t|" << c.map4.at(j) << std::endl;
        }
        std::cout << "--------------------------------------------------------------------------------------\n";
    }

    if (config["mastery_tracking"] == true) {
        c.mastery_toggle = zero_one(gen);
        c.get_maps(TRACKING, c.DIFFI.at(zero_three(gen)));
        std::cout << "MASTERY" << std::endl;
        std::cout << "\t|TRACKING" << std::endl;
        std::uniform_int_distribution<> m(0,c.map4.size());
        for (int j = m(gen); j < c.map4.size(); ++j) {
            ++map_counter;
            std::cout << "\t\t|" << c.map4.at(j) << std::endl;
        }
        std::cout << "--------------------------------------------------------------------------------------\n";
    }

    if (config["mastery_speed"] == true) {
        c.mastery_toggle = zero_one(gen);
        c.get_maps(SPEED, c.DIFFI.at(zero_three(gen)));
        std::cout << "MASTERY" << std::endl;
        std::cout << "\t|SPEED" << std::endl;
        std::uniform_int_distribution<> m(0,c.map4.size());
        for (int j = m(gen); j < c.map4.size(); ++j) {
            ++map_counter;
            //std::cout << "\t\t|" << c.map4.at(j) << std::endl;
        }
        std::cout << "--------------------------------------------------------------------------------------\n";
    }

    for (int i = 0; i < c.cat_vec.size(); ++i) {
        c.mastery_toggle = false;
        DIFFICULTIES dTrack;
        int diTrack;
        if (i == 0) {
            dTrack = EASY;
            diTrack = 0;
            std::cout << "EASY" << std::endl;
        } else if (i == 1) {
            dTrack = MEDIUM;
            diTrack = 1;
            std::cout << "MEDIUM" << std::endl;
        } else if (i == 2) {
            dTrack = HARD;
            diTrack = 2;
            std::cout << "HARD" << std::endl;
        } else if (i == 3) {
            dTrack = INTENSE;
            diTrack = 3;
            std::cout << "INTENSE" << std::endl;
        }
        for (int i2 = 0; i2 != c.cat_vec.at(i).size(); ++i2) {
            if (c.cat_vec.at(i).at(i2) == FLICKING && config["mastery_flicking"] == false) {
                c.get_maps(FLICKING, dTrack);
                std::cout << "\t|FLICKING" << std::endl;
                std::cout << "\t\t|LEVEL " << flicking_level << std::endl;
                for (int i3 = 0; i3 < c.Diffs.at(diTrack) / c.Diffs.at(diTrack); ++i3) {
                    if (c.Diffs.at(diTrack) / c.Diffs.at(diTrack) < 1){
                        ++map_counter;
                        std::cout << "\t\t\t|" << c.map4.at(flicking_level-1) << std::endl;
                    }else{
                        ++map_counter;
                        std::cout << "\t\t\t|" << c.map4.at(i3 + flicking_level - 1) << std::endl;
                    }
                }
            } else if (c.cat_vec.at(i).at(i2) == TRACKING && config["mastery_tracking"] == false) {
                c.get_maps(TRACKING, dTrack);
                std::cout << "\t|TRACKING" << std::endl;
                std::cout << "\t\t|LEVEL " << tracking_level << std::endl;
                for (int i3 = 0; i3 < c.Diffs.at(diTrack) / c.Diffs.at(diTrack); ++i3) {
                    if (c.Diffs.at(diTrack) / c.Diffs.at(diTrack) < 1){
                        ++map_counter;
                        std::cout << "\t\t\t|" << c.map4.at(flicking_level-1) << std::endl;
                    }else{
                        ++map_counter;
                        std::cout << "\t\t\t|" << c.map4.at(i3 + flicking_level - 1) << std::endl;
                    }
                }
            } else if (c.cat_vec.at(i).at(i2) == SPEED && config["mastery_speed"] == false) {
                c.get_maps(SPEED, dTrack);
                std::cout << "\t|SPEED" << std::endl;
                std::cout << "\t\t|LEVEL " << speed_level << std::endl;
                for (int i3 = 0; i3 < c.Diffs.at(diTrack) / c.Diffs.at(diTrack); ++i3) {
                    if (c.Diffs.at(diTrack) / c.Diffs.at(diTrack) < 1){
                        ++map_counter;
                        std::cout << "\t\t\t|" << c.map4.at(flicking_level-1) << std::endl;
                    }else{
                        ++map_counter;
                        std::cout << "\t\t\t|" << c.map4.at(i3 + flicking_level - 1) << std::endl;
                    }

                }
            }
        }
        std::cout << "--------------------------------------------------------------------------------------\n";
    }
    if (map_counter != 0){
        std::cout << "\nTrain each map for " << todays_train_time / map_counter << " minutes." << std::endl;
    }
    else{
        std::cout << "Not enough time to train maps." << std::endl;
    }
    std::string sell{};
    if (perf_test) {
        std::cout << "Enter anything to execute performance test.\n:";
        std::cin.clear();
        std::cin.ignore();
        std::getline(std::cin, sell);
        std::cin.clear();
        peformance_test(false);
    }
    std::cout << "Enter anything to leave.\n:";
    std::cin.clear();
    std::cin.ignore();
    std::getline(std::cin, sell);
    std::cin.clear();
}

bool cmd_promt() {
    clear_screen();
    if (!config_exist) {
        std::cout << "Hello! What's your name?" << std::endl << ":";
        std::getline(std::cin, name);
        name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
        config["name"] = name;
    } else {
        name = config["name"];
    }

    std::string select{};
    SYSTEMTIME cur_time{};
    GetLocalTime(&cur_time);
    WORD conf_time_day = config["last_per_test"];
    while (select != "5") {
        clear_screen();
        std::cout << "Welcome " << name << " to 888's training program." << std::endl;
        std::cout << "1 - TRAIN" << std::endl;
        if (config["t_ns"]) {
            std::cout << "2 - PERFORMANCE TEST" << std::endl;
        }
        else {
            if (cur_time.wDay - conf_time_day >= 1) {
                std::cout << "2 - PERFORMANCE TEST" << std::endl;
            }
        }
        std::cout << "3 - STATS" << std::endl;
        std::cout << "4 - SETTINGS" << std::endl;
        std::cout << "5 - EXIT" << std::endl;
        select = "";
        std::cout << ": ";
        std::cin.clear();
        std::getline(std::cin, select);
        if (select == "1")
            train();
        else if (select == "2") {
            if (config["t_ns"]) {
                peformance_test(false);
            } else {
                if (cur_time.wDay - conf_time_day >= 1) {
                    peformance_test(false);
                }
            }
        } else if (select == "3") {
            stats();
            sleep(1);
        } else if (select == "4") {
            settings();
            sleep(1);
        } else if (select == "5")
            return true;
    }
}

int main() {
    std::cout << "    888-Aimbeast-Training-Program (C) 2020  eighteighteight\n"
                 "    This program comes with ABSOLUTELY NO WARRANTY.\n"
                 "    This is free software, and you are welcome to redistribute it\n"
                 "    under certain conditions; for more details please locate the LICENSE file.\n";
    sleep(6);
    config["name"] = "Default";
    config["default_time"] = user_default_train_time;
    config["asked_default_time"] = false;
    config["mastery_flicking"] = false;
    config["mastery_tracking"] = false;
    config["mastery_speed"] = false;
    config["tracking_cum"] = 1;
    config["flicking_cum"] = 1;
    config["speed_cum"] = 1;
    config["tracking_level"] = 1;
    config["flicking_level"] = 1;
    config["speed_level"] = 1;
    config["flicking_plat"] = 0;
    config["tracking_plat"] = 0;
    config["speed_plat"] = 0;
    SYSTEMTIME cur_time{};
    GetLocalTime(&cur_time);
    config["last_per_test"] = static_cast<WORD>(cur_time.wDay);
    config["t_ns"] = true;

    if (!DoesFileExist(reinterpret_cast<LPCWSTR>("config.json"))) {
        config_exist = false;
    } else {
        std::ifstream i("config.json");
        i >> config;
        config_exist = true;
    }
    cmd_promt();
    std::ofstream o("config.json");
    o << std::setw(4) << config << std::endl;
    o.close();
    return 0;
}
