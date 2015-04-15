#include "interface.h"

MainWindow::MainWindow(unsigned width,
                       unsigned height,
                       const char* title,
                       unsigned menuWidth) :
   sfgui(),
   scrollVert(sfg::Scrollbar::Create(sfg::Scrollbar::Orientation::VERTICAL)),
   scrollHorz(sfg::Scrollbar::Create()),
   frame(sfg::Frame::Create()),
   table(sfg::Table::Create()),
   view(),
   window(sf::VideoMode(width, height), title),
   menuWidth(menuWidth),
   desktop(),
   algComboBox(sfg::ComboBox::Create()),
   xEntry(sfg::Entry::Create("10")),
   yEntry(sfg::Entry::Create("10")),
   isWeighted(sfg::CheckButton::Create("Is weighted?")),
   tableX(0),
   tableY(0),
   squareSize(sfg::Entry::Create("8"))
{
   //add all of the components to the desktop (they won't look pretty yet)
   desktop.Add(scrollVert);
   desktop.Add(scrollHorz);
   desktop.Add(frame);
   desktop.Add(table);
   //link resize button up to resize function for map
   auto resizeButtonMap = sfg::Button::Create("Resize");
   auto resizeButtonSquare = sfg::Button::Create("Resize");
   algComboBox->AppendItem("A*");
   //set up the table
   table->SetRowSpacings(5.f);
   //fill in the table
   addItemToTable(sfg::Label::Create("Algorithm:"), 3);
   addItemToTable(algComboBox, 3);
   addItemToTable(isWeighted, 3);
   addItemToTable(sfg::Label::Create("Map Size:"), 3);
   addItemToTable(xEntry, 1);
   addItemToTable(sfg::Label::Create("x"), 1);
   addItemToTable(yEntry, 1);
   addItemToTable(resizeButtonMap, 3);
   addItemToTable(sfg::Label::Create("Square Size:"), 1);
   addItemToTable(squareSize, 1);
   addItemToTable(resizeButtonSquare, 1);
   //this is essentially a resize, makes window pretty
   handleResize();
}

void MainWindow::handleResize()
{
   //get the window sizes
   const auto winSize = window.getSize();
   const auto winWidth = winSize.x;
   const auto winHeight = winSize.y;
   //get sizes of various elements
   const auto scrollHeight = scrollHorz->GetAllocation().height;
   const auto scrollWidth = scrollVert->GetAllocation().width;

   //if the width is smaller than the menuWidth don't do anything as it would
   //not be correct anyways
   if(winWidth <= menuWidth + scrollWidth)
   {
      return;
   }
   //if the height is smaller scroll height than it also won't be pretty
   if(winHeight <= scrollHeight)
   {
      return;
   }
   //frame size...
   const auto frameWidth = winWidth - scrollWidth - menuWidth;
   const auto frameHeight = winHeight - scrollHeight;
   //now set up the format
   frame->SetAllocation({0,
                         0,
                         frameWidth,
                         frameHeight});
   scrollVert->SetAllocation({frameWidth,
                              0,
                              scrollWidth,
                              frameHeight});
   scrollHorz->SetAllocation({0,
                              frameHeight,
                              frameWidth,
                              scrollHeight});
   table->SetAllocation({5 + static_cast<float>(frameWidth + scrollWidth),
                         0,
                         static_cast<float>(menuWidth) - 10,
                         static_cast<float>(winHeight)});
   //set up the view
   view.reset({0,
               0,
               static_cast<float>(frameWidth),
               static_cast<float>(frameHeight)});
   view.setViewport({
            0,
            0,
            static_cast<float>(frameWidth) / winWidth,
            static_cast<float>(frameHeight) / winHeight
   });
}


void MainWindow::addItemToTable(sfg::Widget::Ptr widget,
                                unsigned width)
{
   table->Attach(widget,
                 {tableX, tableY, width, 1},
                 sfg::Table::FILL | sfg::Table::EXPAND,
                 sfg::Table::FILL);
   tableX += width;
   if(tableX >= 3)
   {
      tableX = 0;
      ++tableY;
   }
}

void MainWindow::run()
{
   sf::Clock clock;
   //loop until the window is closed
   while(true)
   {
      sf::Event event;
      while(window.pollEvent(event))
      {
         //default handling
         desktop.HandleEvent(event);

         //close the window and return if needed
         if(event.type == sf::Event::Closed)
         {
            window.close();
            return;
         }
         else if(event.type == sf::Event::Resized)
         {
            //resize contents if needed
            handleResize();
         }
      }

      //update back end of SFGUI
      desktop.Update(clock.restart().asSeconds());

      //clear screen to gray
      window.clear({86, 86, 86});

      //have to reset GL states for drawing the GUI
      window.resetGLStates();
      //display the GUI
      sfgui.Display(window);

      //push states so that SFML drawing can be used
      window.pushGLStates();
         //set the view and draw the grid
         window.setView(view);
         auto rect = sf::RectangleShape({100000, 100000});
         rect.setFillColor(sf::Color::Red);
         rect.setPosition(0.f, 0.f);
         window.draw(rect);
      window.popGLStates();

      window.display();
   }
}
