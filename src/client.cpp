#include <Game.h>
#include <vector>
#include <EventHandler.h>
#include <UITools.h>
#include <GraphicsManager.h>

int main()
{

	// define players
	//  note that this is only temporary
	Player p1 = Player("ethanxxxl", sf::Color::Blue);
	Player p2 = Player("someone", sf::Color::Red);
	std::vector<Player> players = {p1, p2};

	// start new game
	Game game = Game(players, 500);

	GraphicsManager gm(game, 800, 600);

	// start event handling and UI stuff
	EventHandler eventhandler(gm.get_window());
	//auto ui_tools = std::make_shared<UITools>(gm.get_window(), gm.get_view(), &game);
	//eventhandler.events.push_back(ui_tools);
	
	while ( gm.get_window()->isOpen() )
	{
		gm.get_window()->clear(sf::Color(0x505050ff));

		// draw game stuff
		gm.draw_all();

		eventhandler.handle_events();
		
		gm.get_window()->display();
	}
}


