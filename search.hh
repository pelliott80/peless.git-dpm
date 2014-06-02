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
#ifndef _TEXTSEARCH_
#define _TEXTSEARCH_ 1

#include "config.h"
#include <gtkmm/textview.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/dialog.h>
#include <gtkmm/frame.h>
#include <gtkmm/entry.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/checkbutton.h>

#include <boost/regex.hpp>

#include "internat.hh"


#ifndef  __STDC_ISO_10646__
#error wchar_T must be UCS-4
#endif // __STDC_ISO_10646__

// I am requiring that wchar_t be a UCS-4 that is =gunichar with static-cast


// interface for searching TextViews for regular expressions.

namespace SearchTextView {  // avoid namespace conficts.

  // convert an iterator by using static_cast on the "pointed to" type.
  // Am I reinventing the wheel here? If so, email pelliott@io.com

  // modify iterator's pointed to type.
  //Requirement: OldIter must be bi-di traversal iterator
  //with equality
  // static_cast<New>(OltIter::value_type) must be OK.
  //Result is bidi traversal iterator with value_type New
  //can be assigned or converted back to OldIter
template<typename New, typename OldIter >
class NewIter
{
public:
  // required typdefs when defing an iterator
  // most come from OldIter.
  typedef typename OldIter::iterator_category iterator_category;
  // this type changes!
  typedef New value_type;
  typedef typename OldIter::difference_type difference_type;
  typedef typename OldIter::reference     reference;
  typedef New *pointer;

  // required default constructor
  NewIter(): base() {};
  // can create one from an OldIter
  NewIter(const OldIter& existing):
    base(existing)
  {
  };

  // convert back to OldIter by returning base!
  operator OldIter&()
  {
    return base;
  };

  // can assign to OldIter by assigning to base
  OldIter& operator=(OldIter& to)
  {
    to=base;
    return to;
  };

  // value operator by static cast of value of base!
  value_type operator*() 
  { 
    return static_cast<value_type>( base.operator*() ); 
  };

  // equality operators
  bool operator==(const NewIter& other) const
  {
    return ( base == other.base );
  };

  bool operator!=(const NewIter& other) const
  {
    return ( base != other.base );
  };


  // do transversal operators by refering to base!
  NewIter& operator++() { base.operator++(); return *this; };
  NewIter const operator++(int i) 
  {
    const NewIter nv( *this );
    base.operator++(i);
    return nv;
  };

  NewIter& operator--() { base.operator--(); return *this; };
  NewIter const operator--(int i) 
  {
    const NewIter nv ( *this );
    base.operator--(i);
    return nv;
  };

private:
  // NewIter "has-a" OldIter which makes it work!
  OldIter base;

};

  //This class has a dialog that gets a regular expression to search for!

class SearchCenter : public   boost::basic_regex<wchar_t>
{
public:


  typedef Glib::ustring::value_type value_type;

  // create a search dialog given its parent.
  SearchCenter(Gtk::Window& parent);

  // query user to get regular expression
  void query_find();

  // should we search in forward direction.
  bool search_forward();

  // regular expression string is NULL.
  bool Empty() { return regex_string.empty(); };

private:
  // disabled, declare private but do not define.
  SearchCenter();
  SearchCenter(const SearchCenter&);
  SearchCenter& operator=(const SearchCenter&);

  // I used glade-2 for these elements converting 
  // pointers to objects, to object members.
  // dialog elements.
  Gtk::Dialog dialog;
  Gtk::VBox regex_vbox;
  Gtk::HBox top_hbox;
  Gtk::Frame entry_frame;
  Gtk::Entry regex_entry;
  Gtk::Frame type_frame;
  Gtk::VBox checkbox_vbox;
  Gtk::VBox type_vbox;
  Gtk::RadioButtonGroup type_group;
  Gtk::RadioButton literal_radiobutton,normal_radiobutton,
                   basic_radiobutton,extended_radiobutton;
  Gtk::CheckButton exact_checkbutton,reverse_checkbutton;
  //end of dialog elements

  // string contains regular expression.
  Glib::ustring regex_string;

};



// does search scrool TextView to display results.
// result is taged (possibly chaning collor) with the TextTable tag.
class SearchDisplay
{
public:
  // requirement: view uses a TextBuffer that has a TextTable that
  // contains the found_tag!

  // create a search and displayer
  SearchDisplay(
		// view that displays buffer
		Gtk::TextView& view, 
		// buffer in view above
		Glib::RefPtr<Gtk::TextBuffer> view_buffer,
		// tag must be in tagtable of buffer above.
		Glib::RefPtr<Gtk::TextBuffer::Tag>& found_tag);

  // search for text in buffer and scroll the buffer so we can see.
  void SearchAndScroll(SearchCenter& search_center);

  // iterator over text buffer converted so that regex_search
  // can use it! changes value type returned with static_cast<>
  typedef SearchTextView::NewIter<wchar_t,Gtk::TextBuffer::iterator> 
                                                     TextBufferIterWchar;

private:
  //disallow do not define trivial constructor, conv ctr, assignment
  SearchDisplay();
  SearchDisplay(const SearchDisplay&);
  SearchDisplay& operator=(const SearchDisplay&);

  // save the view buffer.
  Gtk::TextView& view;
  Glib::RefPtr<Gtk::TextBuffer> view_buffer;

  Gtk::TextBuffer& buffer;

  // save the tag.
  Glib::RefPtr<Gtk::TextBuffer::Tag>& found_tag;


  // limits on regex found string if == then empty.
  TextBufferIterWchar regex_found_begin,regex_found_end;

  // is found buffer empty
  bool RegexFoundEmpty() const 
  { 
    return ( regex_found_begin == regex_found_end );
  };

  // 
  void RegexSetFoundEmpty()
  {
    regex_found_begin = regex_found_end = buffer.begin();
  };

  // search region for regular expression. setting regex_found
  bool search_region(
		     // direction to search
		     bool forward,
		     // regular expresion to search for.
		     SearchCenter& search_center,
		     // region to search
		     SearchDisplay::TextBufferIterWchar reg_begin,
		     SearchDisplay::TextBufferIterWchar reg_end
		     );
  // display yes no message. return if OK pressed.
  bool display_message_YES(const Glib::ustring& msg);
  // display message.
  void display_message_OK(const Glib::ustring& msg);
};

} // namespace SearchTextView



#endif // _TEXTSEARCH_
