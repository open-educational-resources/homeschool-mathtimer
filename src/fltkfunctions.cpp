/*                 Joe's Window Manager Configuration
 *
 * This program configures JWM using pugixml and FLTK
 *
 *         Copyright (C) 2016  Israel <israeldahl@gmail.com>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * This has been developed as a part of the ToriOS Project
 *
 *
 * You may redistribute this, but you must keep this comment in place
 * Jesus is my Lord, and if you don't like it feel free to ignore it.
 */
#include "../include/fltkfunctions.hpp"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#define NANOSVG_ALL_COLOR_KEYWORDS  // Include full list of color keywords.
#define NANOSVG_IMPLEMENTATION      // Expands implementation
#include "../include/nanosvg.h"
#define NANOSVGRAST_IMPLEMENTATION
#include "../include/nanosvgrast.h"
//String////////////////////////////////////////////////////////////////
std::string checkBrowser(Fl_Browser* o){
	std::string retval="";
	unsigned int val=o->value();
	if(val<o->size()){
		const char* txt=o->text(val);
		if(txt!=NULL){retval=txt;}
	}
	return retval;
}
/** open a directory chooser
 * @param directory the directory to start at
 * @param label the dialog window label
 */
std::string choose_a_directory(std::string directory, std::string label){
	if(directory.compare("")==0){directory=linuxcommon::home_path();}
	if(label.compare("")==0){label = gettext("Choose Directory");}
	Fl_Native_File_Chooser fnfc;
	fnfc.title(label.c_str());
	fnfc.type(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
	fnfc.directory(directory.c_str());
	std::string String;
	// Show native chooser
	switch ( fnfc.show() ){
		case -1:
			//("Error in directory chooser");
			break; // ERROR
		case 1:
			break; // CANCEL
		default:
			const char *result =fnfc.filename();
			if(result!=NULL){
				String = result;
				return String;
			}
	}
	return "";
}
/** choose a directory for saving in
 * @param directory the directory to start in
 * @param label the dialog label
 */
std::string choose_a_directory_to_save(std::string directory, std::string label){
	if(directory.compare("")==0){directory=linuxcommon::home_path();}
	if(label.compare("")==0){label = gettext("Choose Directory");}
	Fl_Native_File_Chooser fnfc;
	fnfc.title(label.c_str());
	fnfc.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
	fnfc.directory(directory.c_str());
	std::string String;
	// Show native chooser
	switch ( fnfc.show() ){
		case -1:
			//("Error in directory chooser");
			break; // ERROR
		case 1:
			break; // CANCEL
		default:
			const char *result =fnfc.filename();
			if(result!=NULL){
				String = result;
			}
	}
	if(String.compare("")!=0){
		std::string message = gettext("Save as ");
		message +=String;
		int choice = fl_choice("Save ?","No","Yes","Cancel");//message.c_str(),gettext("No"),gettext("Yes"),gettext("Cancel"));
		std::cout<<"Choice:"<<choice<<std::endl;
		if (choice!=1){return "";}
	}
	return String;
}
/** Choose a file from the home directory (or wherever else the user navigates)*/
std::string choose_a_file(){
	std::string directory=linuxcommon::home_path();
	std::string chooseName=gettext("Choose a File");
	std::string String=nativeFileDialog(chooseName,directory,"*");
	return String;
}
/** Choose a file
 * @param directory the starting directory
 */
std::string choose_a_file(std::string directory){
	std::string chooseName=gettext("Choose a File");
	std::string String=nativeFileDialog(chooseName,directory,"*");
	return String;
}
/** Choose a file from a directory with an optional filter
 * @param directory the directory to start in
 * @param pattern the pattern to look for (ex *.svg)
 */
std::string choose_a_file(std::string directory,std::string pattern){
	std::string chooseName=gettext("Choose a File");
	std::string String=nativeFileDialog(chooseName,directory,pattern);
	return String;
}
/** choose a desktop file program*/
std::string choose_a_program(){
	//("std::string choose_a_program()");
	std::string chooseName=gettext("Choose a program");
	std::string result=nativeFileDialog(chooseName,"/usr/share/applications","*.desktop");
	if(result.compare("")==0){return "";}
    bool isDESKTOP = false;
    std::string returnable = result;
    std::string base = result;
    unsigned found2 = returnable.find(".desktop");
    if(found2<=result.length()){
		returnable=returnable.erase(found2,std::string::npos);
		isDESKTOP=true;
	}
    if(isDESKTOP){
		std::string execline= linuxcommon::get_line_with_equal(base,"TryExec=");
		if(execline.compare("")==0){execline= linuxcommon::get_line_with_equal(base,"Exec=");}
		execline=linuxcommon::remove_percentage(execline);
		return execline;
	}
	else{
		unsigned int found;
		found=returnable.rfind("/");
		if(found<returnable.length()){returnable=returnable.erase(0,found+1);}
    }
	return returnable;
}
/** Choose a file from the normal icon directory*/
std::string choose_an_icon(){
	std::string directory=linuxcommon::find_xdg_data_dir_subdir("icon");
	return choose_an_icon(directory);
}
/** choose an icon from a specified directory*/
std::string choose_an_icon(std::string directory){
	//("std::string choose_an_icon(std::string "+directory+")");
	std::string chooseName=gettext("Choose an Icon");
	if(directory.compare("")==0){directory=linuxcommon::find_xdg_data_dir_subdir("icon");}
	std::string String=nativeFileDialog(chooseName,directory,"*.{xbm,XBM,png,PNG,svg,SVG}");
	return String;
}
std::string config_line(std::string FILENAME, std::string item){
	if(item.compare("")==0)return "";
	if(FILENAME.compare("")==0){FILENAME=choose_a_file("/etc/lightdm/");}
	if(FILENAME.compare("")==0){return "";}
	return linuxcommon::get_line_with_equal(FILENAME,item);
}
std::string getEQUALvalue(std::string INTERNAL_LINE){
	std::string subString;
	unsigned int found =INTERNAL_LINE.find("=");
	if(found < INTERNAL_LINE.length()){
		subString=INTERNAL_LINE.substr(found+1,std::string::npos);
		return subString;
	}
	return "";
}
std::string indicatorLine(Fl_Browser *o){
	int SIZE=o->size();
	std::string ret="";
	for(int iter=1;iter<=SIZE;iter++){
		const char* tmp=o->text(iter);
		if(tmp!=NULL){
			if(ret.compare("")==0){ret=tmp;}
			else{
				ret+=";";
				ret+=tmp;
			}
		}
	}
	return ret;
}
/** the function used by the 'choose_a_*' functions to actuall open a file chooser
 * @param title the title to use in the dialog
 * @param path the path to start looking in
 * @param filters the file filters to use (ex *.svg)
 */
 std::string nativeFileDialog(std::string title,std::string path,std::string filters){
	//("std::string nativeFileDialog(std::string "+title+",std::string "+path+",std::string "+filters+")");
	if(title.compare("")==0){title=gettext("Choose");}
	if(path.compare("")==0){path=linuxcommon::home_path();}
	if(filters.compare("")==0){filters="*";}
	const char * f=path.c_str();
	const char * m=title.c_str();
	const char * p=filters.c_str();
	Fl_Native_File_Chooser fnfc;
	fnfc.title(m);
	fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
	fnfc.options(Fl_Native_File_Chooser::PREVIEW);
	fnfc.filter(p);
	fnfc.directory(f); // default directory to use
	// Show native chooser
	switch ( fnfc.show() ){
		case -1:
			//("ERROR");
			break; // ERROR
		case 1:
			break; // CANCEL
		default:
			const char *result =fnfc.filename();
			if(result!=NULL){
				std::string String = result;
				return String;
			}
			break; // FILE CHOSEN
	}
	return "";
}
std::string widgetColor(Fl_Widget* o){
	uchar r;
	uchar g;
	uchar b;
	Fl::get_color((o->color()),r,g,b);
	double* colors = new double[4];
	colors[0] = int(r); 
	colors[1] = int(g);
	colors[2] = int(b);
	colors[3] = 0;
	return linuxcommon::color_double_to_string(colors);
}
//Char*/////////////////////////////////////////////////////////////////
/** create data FLTK can use to set a window icon
 * @param pIcon the data sent in (from an xpm file)
 */
char* Get_Fl_Icon(const char** pIcon){
	//("char* Get_Fl_Icon(const char** pIcon)");
    /* Set icon for Linux:
     * This function must be initialised once by assigning an icon with parameter pIcon.
     * For sequential setting of icon to subwindows, this function can be called several
     * times without assigning an icon every time.
     *
     * Code from Vincent on FLTK forums 2015 Feb 10
     */
	/** Set icon for Linux:
      * This function must be initialised once by assigning an icon with parameter pIcon.
      * For sequential setting of icon to subwindows, this function can be called several
      * times without assigning an icon every time.
	  */
	static Pixmap p= 0;                // static store of assigned icon
	static Pixmap mask;
	if (!p && pIcon){
		// assign icon once
		fl_open_display();
		XpmCreatePixmapFromData(fl_display, DefaultRootWindow(fl_display),
		(char**) pIcon, &p, &mask, 0);
	}
	return (char*) p;
}
//Double////////////////////////////////////////////////////////////////
/** the color chooser dialog
 * @param &c the return value
 * @param o the Fl_Widget to change the color of
 */
double* choose_a_color(int &c,Fl_Widget *o){
	uchar r;
	uchar g;
	uchar b;
	Fl::get_color((o->color()),r,g,b);
	const char * label =gettext("Choose a Color");
	c= fl_color_chooser(label,r,g,b,2);
	double* colors = new double[4];
	colors[0] = int(r); 
	colors[1] = int(g);
	colors[2] = int(b);
	colors[3] = 0;
	return colors;
}
//Void//////////////////////////////////////////////////////////////////
//C
/** choose a program and put the text into an Fl_Input
 * @param o the Fl_Input to send the string to
 */
void choose_a_program(Fl_Input *o){
	//("void choose_a_program(Fl_Input *o)");
	std::string chooseName=gettext("Choose a program");
	std::string result=nativeFileDialog(chooseName,"/usr/share/applications","*.desktop");
	if(result.compare("")==0){return;}
	unsigned period = result.rfind(".");
    bool isDESKTOP = false;
    std::string returnable = result;
    std::string base = result;
    if(result.compare("")!=0){
        if(period<result.length()){
            std::string testDesktop = result.substr(period+1,std::string::npos);
            if(testDesktop.compare("desktop")==0){isDESKTOP = true;}
        }
        unsigned found = result.rfind("//");
        if((found+1)<result.length()){returnable=result.erase(0,found+1);}
        unsigned found2 = returnable.rfind(".");
        if(found2<result.length()){returnable=returnable.erase(found2,std::string::npos);}
        if(isDESKTOP){
			std::string execline= linuxcommon::get_line_with_equal(base,"TryExec=");
			if(execline.compare("")==0){execline= linuxcommon::get_line_with_equal(base,"Exec=");}
			execline=linuxcommon::remove_percentage(execline);
            o->value(execline.c_str());
            return;
        }
    }
	o->value(returnable.c_str());
}
/** clear an Fl_Output
 * @param o, the output to clear
 */
void clearOutput(Fl_Output* o){
	//("void clearOutput(Fl_Output* o)");
	int retval=o->value(NULL);
	if(retval!=0){errorOUT("Different value set");}
}
//M
/** make a symetrical image in an Fl_Widget
 * @param icon_file the filename (or relative name) to turn into the icon
 * @param widget the widget to draw the icon on
 * @param wh the width/height
 */
void makeWidgetIcon(std::string icon_file, Fl_Widget * widget,int wh){
	makeWidgetIcon(icon_file,widget,wh,wh);
}
/** make a symetrical image in an Fl_Widget
 * @param icon_file the filename (or relative name) to turn into the icon
 * @param widget the widget to draw the icon on
 * @param w the width you want it to be
 * @param h the height you want it to be
 */
void makeWidgetIcon(std::string icon_file, Fl_Widget * widget, int w, int h){
	//("void makeWidgetIcon(std::string "+icon_file+", Fl_Widget * widget, int w, int h)");
	//std::string oldfile=icon_file;
	if(icon_file.compare("")==0){
		errorOUT("Icon file is empty");
		return;
	}
	widget->align(FL_ALIGN_CENTER);
	widget->copy_label("");
	widget->label(0L);
	//unsigned int found=icon_file.find("/");
	if(!linuxcommon::test_file(icon_file)){  
		std::vector<std::string> tmpV=IconPaths();
		std::string tmp=icon_file;
		unsigned int ext=icon_file.rfind(".");
		if(ext>icon_file.length()){
			tmp=icon_file+".svg";
			tmp=linuxcommon::test_file_in_vector_path(tmp,tmpV);
			if(tmp.compare("")==0){
				tmp=icon_file+".png";
				tmp=linuxcommon::test_file_in_vector_path(tmp,tmpV);
			}
		}
		else{tmp=linuxcommon::test_file_in_vector_path(tmp,tmpV);}
		if(tmp.compare("")==0){tmp=linuxcommon::look_for_icon_file(icon_file);}
		if(tmp.compare("")!=0){
			icon_file=tmp;
			//("RESULT="+tmp);
		}
	}
	else{errorOUT(icon_file+" is a file!");}
	if(icon_file.compare("")==0){
		//("Icon file is empty");
		return;
	}
	Fl_Image* image2=NULL;
	if(linuxcommon::has_file_extention_at_end(icon_file,".png")){
        Fl_Image* image = new Fl_PNG_Image(icon_file.c_str());
        image2 = image->copy(w,h);
    }
    else if(linuxcommon::has_file_extention_at_end(icon_file,".xpm")){
    	Fl_Image* image = new Fl_XPM_Image(icon_file.c_str());
    	image2 = image->copy(w,h);
	}
	else if(linuxcommon::has_file_extention_at_end(icon_file,".xbm")){
    	Fl_Image* image = new Fl_XBM_Image(icon_file.c_str());
    	image2 = image->copy(w,h);
	}
	else if(linuxcommon::has_file_extention_at_end(icon_file,".svg")){
		NSVGimage *svg_image = NULL;
		NSVGrasterizer *rast = NULL;
		unsigned char* img_data = NULL;
		int width;
		int height;
		const int depth = 4;
		svg_image = nsvgParseFromFile(icon_file.c_str(), "px", 96.0f);
		if (svg_image == NULL) {
			errorOUT("Could not open SVG image:"+icon_file);
			return;
		}
    	width = (int)svg_image->width;
		height = (int)svg_image->height;
		rast = nsvgCreateRasterizer();
		if (rast == NULL) {
			errorOUT("Could not init rasterizer.");
			return;
		}
		img_data = (unsigned char*)malloc(width * height * depth);
		if (img_data == NULL) {
			errorOUT("Could not alloc image buffer.\n");
			return;
		}
		nsvgRasterize(rast, svg_image, 0, 0, 1, img_data, width, height, (width * depth));
		Fl_Image* image  = new Fl_RGB_Image(img_data, width, height, depth);
		image2 = image->copy(w,h);
		nsvgDeleteRasterizer(rast);
		nsvgDelete(svg_image);
	}
	else if((linuxcommon::has_file_extention_at_end(icon_file,".jpg"))||(linuxcommon::has_file_extention_at_end(icon_file,".jpeg"))||(linuxcommon::has_file_extention_at_end(icon_file,".face"))){
		Fl_Image* image = new Fl_JPEG_Image(icon_file.c_str());
		image2 = image->copy(w,h);
	}
	else if(linuxcommon::has_file_extention_at_end(icon_file,".gif")){
		Fl_Image* image = new Fl_GIF_Image(icon_file.c_str());
		image2 = image->copy(w,h);
	}
	else{return;}
	widget->image(image2);
}

//P
/** make a text file into lines of an Fl_Browser
 * @param o the browser to populate
 * @param filename the file to read
 */
void populateBrowserWithTextFile(Fl_Browser *o, std::string filename){
	if(filename.compare("")==0)return;
	std::vector<std::string> myfile=linuxcommon::file_to_vector(filename);
	populateBrowserWithStringVector(o,myfile);
}
/** populate a Fl_Browser with a string each line separated by a new line, OR the whole string as one line
 * @param o the browser
 * @param STRING the string to populate the browser with
 */
void populateBrowserWithString(Fl_Browser *o, std::string STRING){
	//("void populateBrowserWithString(Fl_Browser *o, std::string "+STRING+")");
	if(STRING.compare("")==0)return;
	std::string sep="\n";
	unsigned int finder=STRING.find(sep);
	unsigned int length=STRING.length();
	/** If no '\n' is found just add the string and return*/
	if(finder>length){
		//("No Newline found");
		o->add(STRING.c_str());
		return;
	}
	/** while there is a new line keep adding*/
	while(finder<length){
		finder=STRING.find(sep);
		length=STRING.length();
		std::string tmp1=STRING;
		/** make sure if no newline is at the end it wont crash*/
		if(finder<length+1){
			std::string tmp2=tmp1.erase(finder,std::string::npos);	
			o->add(tmp2.c_str());
			tmp1=STRING;
			finder=tmp1.find(sep);
			STRING=tmp1.substr(finder+1,std::string::npos);
		}
	}
}
/** Populate an Fl_Browser with a vector
 * @param o the browser object
 * @param STRING_VEC the vector to use
 */
void populateBrowserWithStringVector(Fl_Browser *o, std::vector<std::string> STRING_VEC){
	for( std::vector<std::string>::iterator it = STRING_VEC.begin();
		it!=STRING_VEC.end();
		++it){
		std::string tmp=*it;
		o->add(tmp.c_str());
	}
}
//S
/** search an Fl_Browser with content from and input
 * @param input    the Fl_Input to read data from
 * @param browser  the Fl_Browser to search
 */
void searchBrowser(Fl_Input* input,Fl_Browser *browser){
	if(InputIsEmpty(input)){return;}
	std::string term=input->value();
	std::transform(term.begin(), term.end(), term.begin(), ::tolower);
	searchBrowser(term,browser);
}
/** search an Fl_Browser with content from and input
 * @param term     the string to search for
 * @param browser  the Fl_Browser to search
 */
void searchBrowser(std::string term,Fl_Browser *browser){
	if(browser->size()==0){return;}
	for(int start=browser->size();start>0;--start){
		std::string val=browser->text(start);
		std::transform(val.begin(), val.end(), val.begin(), ::tolower);
		unsigned int finder=val.find(term);
		if(finder<val.length()){
			if(browser->visible(start)==0)browser->show(start);
		}
		else{browser->hide(start);}
	}
}

//Boolean///////////////////////////////////////////////////////////////
bool InputIsEmpty(Fl_Input* o){
	//("bool InputIsEmpty(Fl_Input* o)");
	if(o->value()==NULL){return true;}
	const char* value=o->value();
	/** is it NULL?*/
	if(value==NULL){
		//("Empty");
		return true;
	}
	std::string val=value;
	/** is it empty?*/
	if(val.compare("")==0){
		//("Empty");
		return true;
	}
	//("Not empty");
	return false;
}
/** Check if an Fl_Output is empty or not even containing "" rather than NULL
 * @param o the output to check
 */
bool OutputIsEmpty(Fl_Output* o){
	//("bool OutputIsEmpty(Fl_Output* o)");
	if(o->value()==NULL){return true;}
	const char* value=o->value();
	/** is it NULL?*/
	if(value==NULL){
		//("Empty");
		return true;
	}
	std::string val=value;
	/** is it empty?*/
	if(val.compare("")==0){
		//("Empty");
		return true;
	}
	//("Not empty");
	return false;
}
std::vector<std::string> IconPaths(){
	std::vector<std::string> ret;
	std::string themefile;
	int size_to_use=48;
	std::vector<std::string> themesVector=icon_themefiles_vector();
	std::string gtk_theme=linuxcommon::get_gtk_icon_theme();
	if(themesVector.empty()){
		errorOUT("Didn't find any Icon themes");
		return ret;
	}
	for( std::vector<std::string>::iterator it = themesVector.begin();
		it!=themesVector.end();
		++it){
		std::string THEME=*it;
		errorOUT("File="+THEME);
		if(THEME.compare("")!=0){
			std::string themeStyle=linuxcommon::get_line_with_equal(THEME,"Name=");
			if((THEME.find(gtk_theme)<THEME.length())||(gtk_theme.compare(themeStyle)==0)){themefile=THEME;}
			ret=linuxcommon::join_string_vectors(ret,list_icon_dirs_in_themefile(themefile,size_to_use));
		}
	}
	return ret;
}
std::vector<std::string> list_icon_dirs_in_themefile(std::string themefile,int size_to_use){
	errorOUT("std::vector<std::string> list_icon_dirs_in_themefile(std::string "+themefile+",int size_to_use)");
	std::vector<std::string> ListOfIconDirs;
	std::string SIZE_TO_USE=linuxcommon::convert_num_to_string(size_to_use);
	std::string INTERNAL_LINE;
	std::string subString;
	std::string basedir=linuxcommon::get_directory_from_filename(themefile);
	std::string THEME_DIR=basedir;
	std::ifstream inputFileStrem (themefile.c_str(), std::ifstream::in);
	std::string INHERITS;
	std::string tmpDIRi="/usr/share/pixmaps/";
	if(linuxcommon::test_dir(tmpDIRi))ListOfIconDirs.push_back(tmpDIRi);
	tmpDIRi="/usr/share/icons/hicolor/48x48/apps/";
	if(linuxcommon::test_dir(tmpDIRi))ListOfIconDirs.push_back(tmpDIRi);
	tmpDIRi="/usr/share/icons/hicolor/scalable/apps/";
	if(linuxcommon::test_dir(tmpDIRi))ListOfIconDirs.push_back(tmpDIRi);
	if(inputFileStrem.is_open()){
		std::string DIRS,MIN,MAX,SIZE,TYPE,THRESH,CONTEXT,HEADER;
		int size=0;
		int tresh=0;
		int max=0;
		int min=0;
		std::string LINE=getEQUALvalue(INTERNAL_LINE);
		while (getline(inputFileStrem,INTERNAL_LINE)){
			if(INTERNAL_LINE.find('[')<INTERNAL_LINE.length()){
				HEADER=INTERNAL_LINE;
				HEADER=linuxcommon::remove_cruft(HEADER,"[");
				HEADER=linuxcommon::remove_cruft(HEADER,"]");
				HEADER="/"+HEADER;
			}
			else if(INTERNAL_LINE.find("Inherits=")<INTERNAL_LINE.length()){
				INHERITS=LINE;
			}
			else if(INTERNAL_LINE.find("Directories=")<INTERNAL_LINE.length()){
				DIRS=LINE;
			}
			else if(INTERNAL_LINE.find("MinSize=")<INTERNAL_LINE.length()){
				MIN=LINE;
				min=linuxcommon::convert_string_to_number(MIN.c_str());
			}
			else if(INTERNAL_LINE.find("MaxSize=")<INTERNAL_LINE.length()){
				MAX=LINE;
				max=linuxcommon::convert_string_to_number(MAX.c_str());
			}
			else if(INTERNAL_LINE.find("Size=")<INTERNAL_LINE.length()){
				SIZE=LINE;
				size=linuxcommon::convert_string_to_number(SIZE.c_str());
			}
			else if(INTERNAL_LINE.find("Type=")<INTERNAL_LINE.length()){
				TYPE=LINE;
			}
			else if(INTERNAL_LINE.find("Threshold=")<INTERNAL_LINE.length()){
				THRESH=LINE;
				tresh=linuxcommon::convert_string_to_number(THRESH.c_str());
			}
			else if(INTERNAL_LINE.find("Context=")<INTERNAL_LINE.length()){
				CONTEXT=LINE;
			}
			if((CONTEXT.compare("Animations")!=0)
			&&(CONTEXT.compare("Stock")!=0)
			&&(CONTEXT.compare("Status")!=0)
			&&(CONTEXT.compare("Emblems")!=0)
			&&(CONTEXT.compare("Emotes")!=0)
			&&(CONTEXT.compare("International")!=0) ){
				if((SIZE.compare(SIZE_TO_USE))||
				((tresh-size)==(size_to_use))||
				((tresh+size)==(size_to_use)) ){
					if(HEADER.find(SIZE)<HEADER.length()){
						std::string testDIR=THEME_DIR+HEADER;
						if(linuxcommon::test_dir(testDIR)){
							//debug_out("Sized:"+testDIR+" is a directory");
							if(!linuxcommon::look_for_string_in_vector(ListOfIconDirs,testDIR))ListOfIconDirs.push_back(testDIR);
						}
					}
				}
				else{
					if(TYPE.compare("Scalable")==0){
						if((max>=size)&&(min<=size)){
							std::string testDIR=THEME_DIR+HEADER;
							if(linuxcommon::test_dir(testDIR)){
								//debug_out("Scalable:"+testDIR+" is a directory");
								if(!linuxcommon::look_for_string_in_vector(ListOfIconDirs,testDIR))ListOfIconDirs.push_back(testDIR);
							}
						}
					}
				}
			}
		}
	}
	//debug_out("Done parsing themefile "+themefile);
	if(INHERITS.compare("")!=0){
		std::string inheritThemeFileDIR=linuxcommon::find_xdg_data_dir_subdir("icons");
		std::string inheritThemeFile=inheritThemeFileDIR;
		if(INHERITS.find(",")<INHERITS.length()){
			std::vector<std::string> InheritFileVector=linuxcommon::comma_vector(INHERITS,InheritFileVector);
			std::vector<std::string> IconFileVector=list_icon_dirs_in_themefile( themefile, size_to_use);
			for( std::vector<std::string>::iterator it = InheritFileVector.begin();
			it!=InheritFileVector.end();
			++it){
				std::string thisTheme=*it;
				inheritThemeFile+=thisTheme;
				std::string temp=linuxcommon::look_for_file_in_subdirs("index.theme",inheritThemeFile);
				if(temp.compare("")==0){
					//debug_out("Couldn't find theme file in:"+inheritThemeFile);
				}
				else{
					std::vector<std::string> ListOfInheritIconDirs=list_icon_dirs_in_themefile(temp,size_to_use);
					if(!ListOfInheritIconDirs.empty()){
						ListOfIconDirs=linuxcommon::join_string_vectors(ListOfInheritIconDirs,ListOfIconDirs);
					}
				}
			}
		}
		else{
			inheritThemeFile+=INHERITS;
			std::string temp=linuxcommon::look_for_file_in_subdirs("index.theme",inheritThemeFile);
			if(temp.compare("")==0){errorOUT("Couldn't find theme file in:"+inheritThemeFile);}
			else{
				std::vector<std::string> ListOfInheritIconDirs=list_icon_dirs_in_themefile(temp,size_to_use);
				if(!ListOfInheritIconDirs.empty()){
					ListOfIconDirs=linuxcommon::join_string_vectors(ListOfInheritIconDirs,ListOfIconDirs);
				}
			}
		}
	}
	return ListOfIconDirs;
}
std::vector<std::string> icon_themefiles_vector(){
	//debug_out("std::vector<std::string> icon_themefiles_vector()");
	std::string DIRECTORY=linuxcommon::find_xdg_data_dir_subdir("icons");
	std::vector<std::string> thisISmyVector;
	if(DIRECTORY.compare("")==0){errorOUT("Icon directory NOT found");}
	else{thisISmyVector=linuxcommon::get_file_vector(DIRECTORY,"index.theme");}
	if(thisISmyVector.empty()){errorOUT("Didn't find and Icon themes");}
	return thisISmyVector;
}
void errorOUT(std::string msg){
	std::cerr<<msg<<std::endl;
}
void get_indicators(Fl_Browser *o, std::string FILENAME){
	std::string res=config_line(FILENAME,"indicators");
	std::vector <std::string> TMP=linuxcommon::delimiter_vector_from_string(res,";");
	populateBrowserWithStringVector(o,TMP);
}
bool copy_with_backup(std::string IN, std::string OUT, std::string BACK_EXT){
	bool retval=true;
	if(BACK_EXT.find('.')>1)BACK_EXT="."+BACK_EXT;
	std::string backup=linuxcommon::file_to_string(OUT);
	std::string BAK=OUT+BACK_EXT;
	if(!linuxcommon::save_string_to_file(backup,BAK)){
		retval=false;
		errorOUT("Didn't make Backup to:"+BAK);
	}
	else{errorOUT("saved backup:"+BAK);}
	std::string Contents=linuxcommon::file_to_string(IN);
	if(Contents.compare("")==0){
		errorOUT("Contents of file:"+IN+" are empty!! Must exit!");
		return false;
	}
	if(!linuxcommon::save_string_to_file(Contents,OUT)){
		retval=false;
		errorOUT("Couldn't save contents to:"+OUT);
	}
	else{errorOUT("Saved to:"+OUT);}
	return retval;
}
