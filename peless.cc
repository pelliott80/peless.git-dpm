//
//     PELESS TABBED TEXT FILE LISTER.
//     Copyright (C) 2004,2007 Paul Elliott
//     
//     This file is part of peless.
// 
//     peless is free software; you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation; either version 2 of the License, or
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
#include "config.h"
#include <gtkmm.h>

#include <algorithm>

#include "gmore.hh"


int main(int argc, char *argv[])
{
  // Let gtk get its parameters;
  Gtk::Main kit(argc, argv);


  // this code is needed for internationalization
  bindtextdomain(GETTEXT_PACKAGE, PELESS_LOCALEDIR);
  bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
  textdomain(GETTEXT_PACKAGE);


  // filename parameters
  int filecount = argc - 1;
  char **files = argv + 1;

  // convert argv to argument list sequence to pass to NoteGmore.
  Gmore::NoteGmore::file_list_type arguement_list =
    Glib::sequence<Gmore::NoteGmore::file_list_iterator_type>
    (files,files+filecount);

  // create a note book with one page for every file
  Gmore::NoteGmore note_gmore( arguement_list);

  // run Gtk, X11 main event loop.
  Gtk::Main::run(note_gmore);
    
  return 0;
}
