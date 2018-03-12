#ifndef fltkfunctions_hpp
#define fltkfunctions_hpp
#include <X11/xpm.h>
#include <FL/x.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_XBM_Image.H>
#include <FL/Fl_XPM_Image.H>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Menu_Button.H>
#include <libintl.h>
#include "common.hpp"
//string
std::string checkBrowser(Fl_Browser* o);
std::string choose_a_directory(std::string directory, std::string label);
std::string choose_a_directory_to_save(std::string directory, std::string label);
std::string choose_a_file();
std::string choose_a_file(std::string directory);
std::string choose_a_file(std::string directory,std::string pattern);
std::string choose_a_program();
std::string choose_an_icon();
std::string choose_an_icon(std::string directory);
std::string config_line(std::string file, std::string thing);
std::string getEQUALvalue(std::string INTERNAL_LINE);
std::string indicatorLine(Fl_Browser *o);
std::string nativeFileDialog(std::string title,std::string path,std::string filters);
std::string widgetColor(Fl_Widget* o);
//vector
std::vector<std::string> IconPaths();
std::vector<std::string> list_icon_dirs_in_themefile(std::string themefile,int size_to_use);
std::vector<std::string> icon_themefiles_vector();
///char*
char* Get_Fl_Icon(const char** pIcon);
///double*
double* choose_a_color(int &c,Fl_Widget *o);
///void
//c
void choose_a_program(Fl_Input *o);
void clearOutput(Fl_Output* o);
//e
void errorOUT(std::string msg);
//g
void get_indicators(Fl_Browser *o, std::string FILENAME);
//m
void makeWidgetIcon(std::string icon_file,Fl_Widget * widget,int wh);
void makeWidgetIcon(std::string icon_file,Fl_Widget * widget,int w,int h);
//o
//p
void populateBrowserWithTextFile(Fl_Browser *o, std::string filename);
void populateBrowserWithString(Fl_Browser *o, std::string STRING);
void populateBrowserWithStringVector(Fl_Browser *o, std::vector<std::string> STRING_VEC);
//s
void searchBrowser(Fl_Input* input,Fl_Browser *browser);
void searchBrowser(std::string term,Fl_Browser *browser);
void setDecorations(Fl_Output *o,std::string element,std::string value);
void startup(Fl_Window *o);
void startup(Fl_Window *o ,const char** windowIcon);
///bool
bool InputIsEmpty(Fl_Input* o);
bool OutputIsEmpty(Fl_Output* o);
bool copy_with_backup(std::string IN, std::string OUT, std::string BACK_EXT);
#endif
