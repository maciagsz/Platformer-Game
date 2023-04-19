# Platformer Game

## 1. Project Analysis

The aim of the project was to create a platformer game modeled after the iconic series, based on the SFML library and written in C++.
The character is controlled by the player, whose goal is to to reach the finish line by moving through multi-level platforms.
The player's gameplay is converted into points, the components of which are the distance traveled, collected mushrooms,
and the time it took to complete the level (the longer the time, the fewer the points).
Falling off the platform and touching the surface of the water is equivalent to death, in which case the player must
start the game over again.
Scores are saved only if the player completes the game by winning, that is, after crossing the finish line.

## 2. External specifications

### 2.1. Main menu

The program is launched from an executable .exe file. after launching the game, the user is presented with the main menu,
from which the player can start a new game, exit the game or check the list of top scores.

![main_menu](https://raw.githubusercontent.com/maciagsz/Platformer-Game/master/screenshots/main_menu.png)

### 2.2. Play

After pressing Play, the player is prompted to enter a username.

![enter_nickname](https://raw.githubusercontent.com/maciagsz/Platformer-Game/master/screenshots/enter_nickname.png)

### 2.3. Gameplay

After typing the name and confirming it with the Enter button, the gameplay begins.
The player controls the character with the A, D and Space buttons.

![gameplay](https://raw.githubusercontent.com/maciagsz/Platformer-Game/master/screenshots/gameplay.png)

### 2.4. Pause

When the Escape button is pressed, the game pauses its action. Pause can be exited by pressing the Escape button once again.

![pause_menu](https://raw.githubusercontent.com/maciagsz/Platformer-Game/master/screenshots/pause_menu.png)

### 2.5. Player death

When the player falls into the sheet of water death occurs and the game is interrupted.
The user can retry or quit the game.

![player_death](https://raw.githubusercontent.com/maciagsz/Platformer-Game/master/screenshots/player_death.png)

### 2.6. Winning

If the player manages to reach the finish line the game is over.
The player's score is then saved to scores.txt file.
The final screen contains the score, the option to resume the game or exit to the main menu.

![game_won](https://raw.githubusercontent.com/maciagsz/Platformer-Game/master/screenshots/game_won.png)

### 2.7. Hall of fame

Hall of fame has been implemented and shows top user scores.
If there are no scores, relevant information appears

![hall_of_fame](https://raw.githubusercontent.com/maciagsz/Platformer-Game/master/screenshots/empty_hof.png)

## 3. Internal specifiactions

### 3.1. Classes

The abstract class with virtual methods is the ```State``` class located in the ```Engine``` namespace,
as it is defined as the engine on which the game is based. Each class inheriting from the State class corresponds
to a specific state the game is in. For example, these classes are ```GameOver```, ```GameFinished```, ```MainMenu``` and so on.
Each class contains methods and variables appropriate to the function it performs (e.g., displaying main menu, top score lists, gameplay, etc.).
The ```State``` class contains methods responsible for initialization, processing of input signals, updating and drawing.

```cpp
virtual void Init() = 0;
virtual void ProcessInput() = 0;
virtual void Update(sf::Time) = 0;
virtual void Draw() = 0;
```

The ```StateMan``` class, also part of the game engine components, is responsible for managing states.
It stores created game states on the stack (or rather, pointers to them of type ```std::unique_ptr<State>>```).
States are managed by methods:

```cpp
void Add(std::unique_ptr<State>, bool replace = false);
void PopCurrent();
void ProcessStateChange();
std::unique_ptr<State>& GetCurrent();
```

Responsible for adding, deleting, processing and returning game state.
The ``GameInterface`` class contains the ```Run()``` method that is responsible for starting the game.
In addition to the ```GameInterface``` class, ```Context``` structure has been created containing pointers
to objects of the ```Engine::StateMan``` class, and SFML ```sf::RenderWindow```.
The calculation and display of the score obtained by the player is handled by the ```Score``` class.
Collision determination is done in the ```Collision``` class by passing its references to the
```Player```player object and the ```World``` world object.
The ```World``` class is responsible for displaying and initializing the world. It contains elements
used for storing textures, sprites, the world map, and methods to transform the world stored in a text file into vertexes drawn on the screen.
The objects in the game, such as mushrooms, trees, bushes, are managed by the ```WorldObject``` class, which stores the sprites in a vector,
and the corresponding methods draw, create, check or delete them.
The player is defined by the ```Player``` class. It contains methods responsible for drawing, moving the player and gravity (falling).

### 3.2. Relevant data structures

For the purpose of storing resources, such as textures or fonts, a template has been created to store, load and return these elements.
The type of elements stored is defined when declaring the container type.
For example, for textures it is ```TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;```.
Resources are stored in the ```std::map<Identifier, std::unique_ptr<Resource>> resource_map;```.
Void method ```loadResource(Identifier, const std::filesystem::path&);``` allow operations on map elements by adding
an element of the specified type and path to the list, and the ```Resource&``` type method ```getResource(Identifier);```,
which returns a pointer to the value corresponding to the specified key.
Using the above solution allows creating a container with fast search time and fast access time.
In addition, by adding just a few lines of code, new functionality can be added to the game, for example sound effects.
In order to manage and identify resources with the above interface, a ```ResourceIdentifiers.h``` file was created
containing enumerators of textures and fonts found in the game.

### 3.3. Relevant algorithms

Collision checking involves detecting whether a player object collides with another object on the map.
If so, determine from which side the collision occurred, and undo the player's position.
Checking 1024 items (since level consists of an 8x128 grid) with each run of the game loop would be a huge waste of resources.
Solution to this consists of determining the player's position on the map and mapping the surrounding 3x3 boxes with the following algorithm.

```cpp
for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
    {
        int vertice_id = ((x_pos - 1 + j) + (y_pos - 1 + i) * WORLD_WIDTH) * 4;
        sf::Vector2f vertice_pos = _world.world_vertices[vertice_id].position;
        sf::FloatRect rect(vertice_pos, tile_size);
        rect_vector[counter] = rect;
        counter++;
    }
```

In that only 9 fields around the player are checked during each loop run.

### 3.4. Techniques used from modern C++

- Using modules instead of ```#include``` directives
- Operations on files are performed using ```<filesystem>``` library
- Hall of fame scores are sorted using ```std::ranges```
- Checking user character input involves regular expressions patterns

### 3.5. Program operation algorithm

The ```main``` function creates an object of ```GameInterface``` type, then its ```Run()``` method is called,
in which the loop of the entire game is conducted. This method is constructed to ensure application's time independence.
The ```GameInterface``` class constructor creates a pointer to the ```MainMenu``` object, which is pushed on top of the state stack.
The ```Run()``` method then processes the states on the stack. This displays the ```MainMenu```, from which you can start the game.
When ```Play``` is selected, the main menu is replaced on the stack by the ```InputName``` state, in which the player enters his name.
After that, the ```InputName``` state is replaced by the ```Game``` state. The gameplay begins. Player and world objects are created.
The world is initialized by reading a text file containing ASCII characters from the appropriate range.
The contents of the file are converted into a two-dimensional ```world_map``` array, then the characters are mapped
to ```sf::VertexArray```, vertexes are given an appropriate location on the map and a texture. Next step is to create the world objects.
Then the gameplay defined in the ```GameInterface::Run()``` loop begins. In the event of death or completion of the game,
the ```Game``` state is eplaced by others.

## 4. Preparing the environment to build the application

- [Install vcpkg](https://vcpkg.io/en/getting-started.html)
- Install SFML library

```text
vcpkg install sfml:x64-windows
```
