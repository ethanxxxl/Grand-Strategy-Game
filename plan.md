This game will not be a 4x game, in the sense that the winner is decided by who
has the most technology. Instead, games should be won by combat strategy.


Revision 1 Technical Requirements
===

This will be a multiplayer game, so there should be a server and a client.

## Server
on startup, it will create a game _(in the future, it will have the option to
load a game)_, and sets up players. For now, these can just be command line
arguments.

Players will be distinguished by unique usernames. _(in the future,
there will be player profiles, with usernames, which are only displayed, and a
unique userID.)_

If a client wants to connect, it's username has to match one of the players in
the game, and a player with that username cannot already be connected.

When the player connects, their client will receive the most up-to-date version
of the game that the server has.

When the client is finished playing their turn, the server will receive an
updated version of the game. This will replace the current version of the game
on the server. _(in the future, the server will conduct a check on the new game
state, to make sure that no illegal moves were made.)_

## Client
When the client connects to the server, it will receive the most up-to-date
version of the game. If it is the players turn, then the client will allow the
player to take their turn. Once their turn is completed, the client will send
the new version of the game back to the server.

If it is not the players turn, they can view the current state of the game. If
another player makes a move, then the server should ask the client if it wants
an updated. The client will then ask the player if they would like to view the
most up-to-date game.

The client should have a simple graphical interface for the game. This
interface will display the map, and allow the player to click on companies and
move them around

## Gameplay
This first revision will have the most rudimentary game-play possible.

### Map Generation
The server should generate a square map _(in the future the map will instead
consist of hexagonal tiles)_ and put a starting city for each player somewhere
on the map (no checks will be done to make sure that they are far apart). Each
tile on the can be either land or water (maybe make a little effort to have
smooth terrain generation).

###Combat
Each player will start with 10 companies of 200 men. Combat Effectiveness will
not be implemented, combat will be very simple. Whoever has the largest army
will win a battle. Players will not gain troops over time. Players will not be
able to do anything other than move troops around each turn. Troops will not be
able to move onto water, only on land

Finished Product Goals
===

## World
The world will be randomly generated, and split into either a _hexagonal grid_

Each tile will have resources that will be exploited by the population.


## GDP
The player is a ruler of a capitalistic nation. They do not need to worry about
increasing their GDP each turn. That will happen automatically.

## Military
The size of the players military is affected by the population. The
population should stay fairly constant throughout the game, as I don't think wars don't
typically last long enough for populations to significantly increase. To
increase the head count of the military,

### Army
Army structure will be based off of the US army. The player will be able to
divide the army into Divisions, Brigades, Battalions, and Companies.

The player can allot create and allot soldiers to companies. However,
Companies must contain at least 150 soldiers.

Each company will have combat stats, that determine how well it performs in
battle. These stats will include:

  - Proficiency
  - Readiness
  - Technology
  - Moral

All of those values will be multiplied together to form that companies __Combat
Effectiveness (CE)__. The combat effectiveness of a company helps determine the
outcome of combat on a specific tile.

## Combat
if a player decides that they want to attack a tile, they will have to move the
companies onto a tile that is within their range.
