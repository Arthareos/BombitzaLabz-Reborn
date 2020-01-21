# *README*
Make sure that that the debug config is *x86*

# Good ol' *Documentation* ^^
The list of the methods and classes that are right now in the project:
 1. GameplaySelector();
 2. MainMenu();
 3. GameStart();
 4. Map class;
 5. MapTile class;
 6. Resources class;

# 1. GameplaySelector() method
 >This method is the heart of the game, all the changes in the game's state go through this method.

## Member variables
- sf::RenderWindow **window**;
- sf::Event **event**;
- int16_t **gameState**;
>1. MainMenu
>2. GameStart
>3. Battle
>4. Setup
>5. Password
>6. Exit
- sf::RenderWindow& **test** = window;

## Member methods
**1. "callMainMenu()**";

    callMainMenu(int16_t& gameState, sf::RenderWindow& window);

This method is responsable for calling the game's menu, the only condition is that the "*gameState*" being equal to "1". For more details visit the "*MainMenu()*" documentation;

**2. "callGameStart()**";

    callGameStart(int16_t& gameState, sf::RenderWindow& window);

This method is responsable for calling the game's menu, the only condition is that the "*gameState*" being equal to "2". For more details visit the "*GameStart()*" documentation;

# 2. MainMenu() method
 >This method is the start of the game, all the main *"gameState"* changes start from here.
 ## Member variables
- int **choice**;
- bool **isExiting**;

## Member methods
 ***No methods for the moment***
# 2. GameStart() method
 >This method is the start of the game, all the single-player game's mechanics start from here.

 ## Member variables
 ***incomplete***

## Member methods
***No methods for the moment***