#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFGUI/SFGUI.hpp>

class MainWindow
{
public:
   //begin running the window
   void run();
   //basic constructor, all sizes are in pixels
   MainWindow(unsigned width,
              unsigned height,
              const char* title,
              unsigned menuWidth = 200);

private:
   //set up all of the element properly
   void handleResize();
   //add an item to the table; note that the table has width 3 and
   //attempting to add an item that would cause the table to go over this
   //will stretch the table and produce other unwanted effects
   void addItemToTable(sfg::Widget::Ptr widget,
                       unsigned width);

   //for SFGUI to do anything
   sfg::SFGUI sfgui;
   //the two scroll bars
   sfg::Scrollbar::Ptr scrollVert;
   sfg::Scrollbar::Ptr scrollHorz;
   //the frame for rendering the grid
   sfg::Frame::Ptr frame;
   //the menu interface
   sfg::Table::Ptr table;
   //the view needed for drawing the map
   sf::View view;
   //the SFML window used for rendering
   sf::RenderWindow window;
   //the width of the menu on the side, in pixels
   unsigned menuWidth;
   //the desktop for rendering
   sfg::Desktop desktop;
   //the combo box used for the algorithms
   sfg::ComboBox::Ptr algComboBox;
   //entry for map size x/y
   sfg::Entry::Ptr xEntry;
   sfg::Entry::Ptr yEntry;
   //check box for if algorithm is weighted or not
   sfg::CheckButton::Ptr isWeighted;
   //location managers for the table
   unsigned tableX;
   unsigned tableY;
   //entry for size of squares
   sfg::Entry::Ptr squareSize;
};

#endif // INTERFACE_H
