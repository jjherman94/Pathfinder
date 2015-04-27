#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>

#include "interface.h"
#include "bfs.h"

int main()
{
	MainWindow window(800, 600, "Hi!");
	window.addAlgorithm(std::unique_ptr<Algorithm>(new BFS));
	window.run();

	return 0;
}

