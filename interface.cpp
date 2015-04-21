#include "interface.h"

#include <functional>

MainWindow::MainWindow(unsigned width,
                       unsigned height,
                       const char* title,
                       unsigned menuWidth) :
   grid(),
   tableX(0),
   tableY(0),
   menuWidth(menuWidth),
   squareSize(0),
   sfgui(),
   scrollVert(sfg::Scrollbar::Create(sfg::Scrollbar::Orientation::VERTICAL)),
   scrollHorz(sfg::Scrollbar::Create()),
   frame(sfg::Frame::Create()),
   table(sfg::Table::Create()),
   view(),
   window(sf::VideoMode(width, height), title),
   desktop(),
   algComboBox(sfg::ComboBox::Create()),
   xEntry(sfg::Entry::Create("18")),
   yEntry(sfg::Entry::Create("18")),
   isWeighted(sfg::CheckButton::Create("Is weighted?")),
   squareSizeEntry(sfg::Entry::Create("32"))
{
   //resize things automatically
   handleGridResize();
   handleSquareResize();
   //add all of the components to the desktop (they won't look pretty yet)
   desktop.Add(scrollVert);
   desktop.Add(scrollHorz);
   desktop.Add(frame);
   desktop.Add(table);
   //link resize button up to resize function for map
   auto resizeButtonMap = sfg::Button::Create("Resize");
   auto resizeButtonSquare = sfg::Button::Create("Resize");
   //set up callbacks
   resizeButtonMap->GetSignal(sfg::Button::OnLeftClick).Connect
            ([this](){handleGridResize();});
   resizeButtonSquare->GetSignal(sfg::Button::OnLeftClick).Connect
            ([this](){handleSquareResize();});
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
   addItemToTable(squareSizeEntry, 1);
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
   //now scroll bars have to be handled
   updateScrollBars();
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

void MainWindow::handleGridResize()
{
   //get the width and the height
   std::string widthTemp = xEntry->GetText();
   std::string heightTemp = yEntry->GetText();
   auto width = atoi(widthTemp.c_str());
   auto height = atoi(heightTemp.c_str());
   //ignore invalid sizes
   if(width <= 0 || height <= 0)
   {
      return;
   }
   //otherwise re-size the grid
   grid.resize(width, height);
   //also update scroll bars
   updateScrollBars();
}

void MainWindow::handleSquareResize()
{
   std::string sizeTemp = squareSizeEntry->GetText();
   auto size = atoi(sizeTemp.c_str());
   //ignore invalid sizes
   if(size <= 0)
   {
      return;
   }
   //otherwise resize
   squareSize = size;
   //must update scroll bars now
   updateScrollBars();
}

void MainWindow::updateScrollBars()
{
   //determine max height and width
   auto maxWidth = grid.getWidth() * squareSize;
   auto maxHeight = grid.getHeight() * squareSize;
   //if either is invalid ignore this
   if(maxWidth <= 0 || maxHeight <= 0)
   {
      return;
   }
   //otherwise get the window size
   const auto winSize = window.getSize();
   const auto winWidth = winSize.x;
   const auto winHeight = winSize.y;
   const auto scrollHeight = scrollHorz->GetAllocation().height;
   const auto scrollWidth = scrollVert->GetAllocation().width;
   const auto frameWidth = winWidth - scrollWidth - menuWidth;
   const auto frameHeight = winHeight - scrollHeight;
   //code is the same for width and height; abstract it out
   auto resizeScroller = [this](unsigned maxSize,
                                unsigned areaAllowed,
                                sfg::Scrollbar::Ptr& scroller,
                                std::function<void()> handler)
      {
         if(maxSize <= areaAllowed)
         {
            //get the disabled look
            scroller->SetState(sfg::Widget::State::INSENSITIVE);
            scroller->SetAdjustment(
                      sfg::Adjustment::Create(0.f, 0.f, 0.f, 0.f, 0.f, 10.f));
         }
         else
         {
            //otherwise need to adjust
            scroller->SetState(sfg::Widget::State::NORMAL);
            //get the old values, and keep them
            auto old = scroller->GetAdjustment();
            //there are areaAllowed entries visible
            auto visible = 1.f * areaAllowed;
            //upper value is number of squares for that size
            auto upper = 1.f * maxSize;
            //the new value
            float newValue = old->GetValue();
            //if value is less than the minimum + visible then keep it
            if(newValue + visible > upper)
            {
               //otherwise just use the furthest value
               newValue = upper - visible;
            }
            //lower limit will always be 0
            auto adj = sfg::Adjustment::Create(newValue,
                                               0.f,
                                               upper,
                                               1.f * squareSize,
                                               .5f * squareSize,
                                               visible);
            scroller->SetAdjustment(adj);
            //have to redraw it now
            scroller->Invalidate();
            //set up signals
            scroller->GetAdjustment()->
                  GetSignal(sfg::Adjustment::OnChange).Connect(handler);
         }
         //force resizing now
         handler();
      };
   //now actually resize the scrollers
   resizeScroller(maxWidth, frameWidth, scrollHorz,
                  [this, frameWidth]()
                  {
                     //find distance moved and move view
                     auto loc = view.getCenter();
                     auto x = loc.x - frameWidth/2.f;
                     auto xChange = scrollHorz->GetValue() - x;
                     view.move(xChange, 0.f);
                  });
   resizeScroller(maxHeight, frameHeight, scrollVert,
                  [this, frameHeight]()
                  {
                     //find distance moved and move view
                     auto loc = view.getCenter();
                     auto y = loc.y - frameHeight/2.f;
                     auto yChange = scrollVert->GetValue() - y;
                     view.move(0.f, yChange);
                  });
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
         else if(event.type == sf::Event::MouseMoved)
         {
            //if a button is pressed then make/destroy walls
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
               sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
               //set up parameters
               auto frameAlloc = frame->GetAllocation();
               auto xBase = view.getCenter().x - frameAlloc.width/2;
               auto yBase = view.getCenter().y - frameAlloc.height/2;
               auto xLim = frameAlloc.width + xBase;
               auto yLim = frameAlloc.height + yBase;
               auto x = event.mouseMove.x + xBase;
               auto y = event.mouseMove.y + yBase;
               //make sure that they are valid
               if(x >= xBase && y >= yBase && x < xLim && y < yLim &&
                  x/squareSize < grid.getWidth() &&
                  y/squareSize < grid.getHeight())
               {
                  //get weight (-1 = wall, 0 = nothing)
                  int weight = 0 - sf::Mouse::isButtonPressed(sf::Mouse::Left);
                  //can mark the square now
                  grid.getTile(x/squareSize, y/squareSize).weight = weight;
               }
            }
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
         //first clear the background
         auto clearRect = sf::RectangleShape({100000, 100000});
         clearRect.setFillColor({86, 86, 86});
         window.draw(clearRect);
         //now draw the grid
         auto rect = sf::RectangleShape({1.f * squareSize, 1.f * squareSize});
         rect.setOutlineThickness(1.f);
         rect.setOutlineColor(sf::Color::Black);
         sf::Color rectColor;
         for(auto y = 0u; y < grid.getHeight(); ++y)
         {
            for(auto x = 0u; x < grid.getWidth(); ++x)
            {
               //set up the color
               switch(grid.getTile(x, y).status)
               {
                  case Tile::Status::nothing:
                     rectColor = sf::Color::White;
                     break;

                  case Tile::Status::path:
                     rectColor = sf::Color::Red;
                     break;

                  case Tile::Status::visited:
                     rectColor = {127, 127, 127};
                     break;
               }
               //if weight is -1 then it is a wall
               if(grid.getTile(x, y).weight == -1)
               {
                  rectColor = sf::Color::Black;
               }
               //set color and position and then draw
               rect.setFillColor(rectColor);
               rect.setPosition(1.f * squareSize * x, 1.f * squareSize * y);
               window.draw(rect);
            }
         }
      window.popGLStates();

      window.display();
   }
}
