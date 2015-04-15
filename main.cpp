#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>

#include "interface.h"

int main()
{
	MainWindow window(800, 600, "Hi!");
	window.run();

	return 0;
}

