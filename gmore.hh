//
//     PELESS TABBED TEXT FILE LISTER.
//     Copyright (C) 2004,2007 Paul Elliott
//     
//      This file is part of peless.
// 
//     peless is free software; you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation; either version 3 of the License, or
//     (at your option) any later version.
// 
// 
//     peless is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
// 
// 
//     You should have received a copy of the GNU General Public License
//     along with peless; if not, write to the Free Software
//     Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#ifndef _GMORE_
#define _GMORE_ 1

#include "config.h"

#include "search.hh"

//#include "myhide.h"   // sometimes hide.h cause ambiguity
#include <sigc++/sigc++.h>
#include <gtkmm.h>
#include <gtkmm/label.h>
#include <gtkmm/textview.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/notebook.h>
#include <gtkmm/box.h>
#include <gconfmm.h>

#include <string>


//#include <iostream>
//#include <fstream>
//#include <iomanip>

#include "internat.hh"              // define _() macro to use i18n

namespace Gmore {  // avoid namespace conficts.
  // a NoteGmore is a notebook containing any number of
  // Gmores.
  // each notebook page displays a file.
  class NoteGmore : public Gtk::Window
  {  
  private:
    // A Gmore is a scrolled window containing
    // and a textview 
    // loaded with the data from the file.
    // scrollwindow allows text to be scrolled.
    // subclass to NewsGmore later.
    // each one of these will be a page in the notebook
    // nested class. this class is NoteGmore's bitch.
    class Gmore : public Gtk::ScrolledWindow
    {  
    private:
      friend class NoteGmore;   // this class is NoteGmore's bitch.
      // displays text of file
      class Gtk::TextView textview;

      // filename of the data displayed
      std::string filename;

      // reference to owning gmore.
      NoteGmore& the_note_gmore;

    public:
      // construct from filename.
      Gmore(NoteGmore& gmore,
	    const std::string filename,
	    Glib::ustring& font_name);
      // destructor
      virtual ~Gmore();

    private:
      // property gets filename of file displayed.
      const std::string FileName() const { return filename; };

      // set font in use
      void set_font_in_use(const Glib::ustring&);

      // hold connections that needs to be disconnected
      // when this page goes away.
      sigc::connection change_page_connection;
      sigc::connection change_page_font_connection;

      // create a TextBuffer from the data in our file.
      Glib::RefPtr<Gtk::TextBuffer> load_textbuffer_from_file();
    
      // setup a textview.
      void setup_textview(Glib::RefPtr<Gtk::TextBuffer>,
			  const Glib::ustring& font_name);

    private:
      //disallow: do not define trivial constructor, conv ctr, assignment
      Gmore();
      Gmore(const Gmore&);
      Gmore& operator=(const Gmore&);

      // property haveing title parent window should use to title this file.
      Glib::ustring external_title;

      // buffer to use in this TextView
      Glib::RefPtr<Gtk::TextBuffer>  load_bufferPtr;

      // regular expression search viewer.
      SearchTextView::SearchDisplay search_display;

      // define property set/get methods.
      const Glib::ustring& get_external_title() const 
      { 
	return external_title; 
      };
      void set_external_title(const Glib::ustring& etitle) 
      { 
	external_title=etitle; 
      };

    };

    friend class NoteGmore::Gmore;
    // the boost library gives us a reference wrapper
    // with value sematics!


  public:

    // simple pointer interator in sequence of files passed in.
    typedef char ** file_list_iterator_type;
    typedef Glib::Sequence<NoteGmore::file_list_iterator_type> 
    file_list_type;

    typedef const file_list_iterator_type file_list_const_iterator_type;

    // construct from list of fileames.
    NoteGmore( const file_list_type & ,
	       Gtk::WindowType type=Gtk::WINDOW_TOPLEVEL);
    virtual ~NoteGmore();


  private:
    // set the title to the external title of the current page.
    void change_title( 
		      GtkNotebookPage*, 
		      guint,
		      // RefGmore rather than Gmore& becaus
		      // of bug in bind. bound paramenter must be
		      // destructable. i.e. not a reference.
		      // boost::reference_wrapper gives us this.
		      Gmore&
		      );

    // create a Gmore and add it to the notebook as a page.
    void add_less_page( const std::string& );

    // get filename from user and add coresponding Gmore to notebook
    void OpenNewPage();

    // remove the current page.
    void UnLoadCurrentPage();

    // get new font from user apply to all pages.
    void change_font();

    // change font for a page.
    void change_page_font(Gmore&);

    // search functions
    // find string in buffer after getting string using dialog.
    void find();

    // find next occurance of string in buffer
    void find_next();

    sigc::signal0<void> change_page_font_signal;

    //disallow do not define trivial constructor, conv ctr, assignment
    NoteGmore();
    NoteGmore(const NoteGmore&);
    NoteGmore& operator=(const NoteGmore&);

    //pointer to current Gmore; no deletion responsibility
    NoteGmore::Gmore * current_gmore;


    //SearchCenter for regex searching
    SearchTextView::SearchCenter search_center;

    // verticle has menu and display
    Gtk::VBox m_Box;

    Gtk::MenuBar m_MenuBar;
    Gtk::Menu m_Menu_File, m_Menu_Edit;

    // this is the notebook containing any number of (Gmore)s
    Gtk::Notebook notebook;

    //font to use for all the textviews
    Glib::ustring textview_font_name;

    // info used for textbuffer searcher.
    // text tag for found strings.
    Glib::RefPtr<Gtk::TextTag> regex_found_tag;

    // tag table for all TextView's
    Glib::RefPtr<Gtk::TextTagTable> tag_table;

    // client to remember parameters such as fonts, sizes
    Glib::RefPtr<Gnome::Conf::Client> m_refClient;

    // key for font names.
    Glib::ustring font_name_key;
    // window size keys
    Glib::ustring height_key;
    Glib::ustring width_key;

  };

} // namespace Gmore

#endif // _GMORE_
