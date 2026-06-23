#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

int main()
{
    const int tileSize = 50;

    std::vector<std::vector<std::string>> levels = {
        {
            "##########",
            "#S   #   #",
            "# ## # # #",
            "#    # # #",
            "#### # # #",
            "#      #E#",
            "##########"
        },
        {
            "############",
            "#S #     # #",
            "#  ### # # #",
            "##     #   #",
            "#  ####### #",
            "#        #E#",
            "############"
        },
        {
            "##############",
            "#S   #     # #",
            "### ### ###  #",
            "#     #   ## #",
            "# ### ###    #",
            "#   #   #### #",
            "##      #   E#",
            "##############"
        }
    };

    sf::Font font;
    if (!font.loadFromFile("assets/DejaVuSans.ttf"))
    {
        std::cout << "Could not load assets/DejaVuSans.ttf\n";
        return 1;
    }

    sf::SoundBuffer moveBuffer, wallBuffer, winBuffer;
    if (!moveBuffer.loadFromFile("assets/move.wav"))
        std::cout << "Could not load assets/move.wav\n";
    if (!wallBuffer.loadFromFile("assets/wall.wav"))
        std::cout << "Could not load assets/wall.wav\n";
    if (!winBuffer.loadFromFile("assets/win.wav"))
        std::cout << "Could not load assets/win.wav\n";

    sf::Sound moveSound, wallSound, winSound;
    moveSound.setBuffer(moveBuffer);
    wallSound.setBuffer(wallBuffer);
    winSound.setBuffer(winBuffer);

    int currentLevel = 0;
    std::vector<std::string> maze;
    int rows = 0, cols = 0;
    int playerRow = 0, playerCol = 0;
    int exitRow = 0, exitCol = 0;
    int health = 3;

    bool gameWon = false;
    bool gameLost = false;
    bool rWasPressed = false;

    sf::Clock totalTimer;
    sf::Clock levelTimer;
    int frozenTotalTime = 0;
    int frozenLevelTime = 0;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Maze Runner Ultimate");
    window.setFramerateLimit(10);

    sf::Text infoText1;
    infoText1.setFont(font);
    infoText1.setCharacterSize(22);
    infoText1.setFillColor(sf::Color::White);

    sf::Text infoText2;
    infoText2.setFont(font);
    infoText2.setCharacterSize(22);
    infoText2.setFillColor(sf::Color::White);

    sf::Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(38);
    messageText.setFillColor(sf::Color::Yellow);

    sf::Text retryText;
    retryText.setFont(font);
    retryText.setCharacterSize(24);
    retryText.setFillColor(sf::Color::Cyan);

    sf::Text watermarkText;
    watermarkText.setFont(font);
    watermarkText.setCharacterSize(16);
    watermarkText.setFillColor(sf::Color(180, 180, 180));
    watermarkText.setString("rajanandani khatoi | reg-2341011306");

    auto loadLevel = [&](int levelIndex)
    {
        maze = levels[levelIndex];
        rows = maze.size();
        cols = maze[0].size();

        window.create(
            sf::VideoMode(cols * tileSize, rows * tileSize + 140),
            "Maze Runner Ultimate"
        );
        window.setFramerateLimit(10);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (maze[i][j] == 'S')
                {
                    playerRow = i;
                    playerCol = j;
                }
                else if (maze[i][j] == 'E')
                {
                    exitRow = i;
                    exitCol = j;
                }
            }
        }

        infoText1.setPosition(10, rows * tileSize + 10);
        infoText2.setPosition(10, rows * tileSize + 40);
        watermarkText.setPosition(10, rows * tileSize + 105);

        messageText.setPosition(40, rows * tileSize / 2 - 30);
        retryText.setPosition(90, rows * tileSize / 2 + 30);

        levelTimer.restart();
    };

    auto startGame = [&]()
    {
        currentLevel = 0;
        health = 3;
        gameWon = false;
        gameLost = false;
        frozenTotalTime = 0;
        frozenLevelTime = 0;
        loadLevel(currentLevel);
        totalTimer.restart();
        levelTimer.restart();
    };

    startGame();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!gameWon && !gameLost)
        {
            int newRow = playerRow;
            int newCol = playerCol;
            bool keyPressed = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                newRow--;
                keyPressed = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                newRow++;
                keyPressed = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                newCol--;
                keyPressed = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                newCol++;
                keyPressed = true;
            }

            if (keyPressed)
            {
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols)
                {
                    if (maze[newRow][newCol] != '#')
                    {
                        playerRow = newRow;
                        playerCol = newCol;
                        moveSound.play();
                    }
                    else
                    {
                        health--;
                        wallSound.play();
                    }
                }
            }

            if (health <= 0)
            {
                gameLost = true;
                frozenTotalTime = (int)totalTimer.getElapsedTime().asSeconds();
                frozenLevelTime = (int)levelTimer.getElapsedTime().asSeconds();
                messageText.setString("YOU LOSE");
                retryText.setString("Press R to Try Again");
            }

            if (playerRow == exitRow && playerCol == exitCol)
            {
                winSound.play();

                if (currentLevel < (int)levels.size() - 1)
                {
                    currentLevel++;
                    loadLevel(currentLevel);
                }
                else
                {
                    gameWon = true;
                    frozenTotalTime = (int)totalTimer.getElapsedTime().asSeconds();
                    frozenLevelTime = (int)levelTimer.getElapsedTime().asSeconds();
                    messageText.setString("YOU WIN!");
                    retryText.setString("Press R to Start Again");
                }
            }
        }
        else
        {
            bool rPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::R);

            if (rPressed && !rWasPressed)
            {
                startGame();
            }

            rWasPressed = rPressed;
        }

        int showLevelTime = (gameWon || gameLost) ? frozenLevelTime : (int)levelTimer.getElapsedTime().asSeconds();
        int showTotalTime = (gameWon || gameLost) ? frozenTotalTime : (int)totalTimer.getElapsedTime().asSeconds();

        std::ostringstream line1, line2;
        line1 << "Level: " << currentLevel + 1 << "   Health: " << health;
        line2 << "Level Time: " << showLevelTime << " sec   Total Time: " << showTotalTime << " sec";

        infoText1.setString(line1.str());
        infoText2.setString(line2.str());

        window.clear(sf::Color::Black);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                sf::RectangleShape cell(sf::Vector2f(tileSize - 2, tileSize - 2));
                cell.setPosition(j * tileSize, i * tileSize);

                if (maze[i][j] == '#')
                    cell.setFillColor(sf::Color(80, 80, 80));
                else if (maze[i][j] == 'E')
                    cell.setFillColor(sf::Color::Green);
                else
                    cell.setFillColor(sf::Color(200, 200, 200));

                window.draw(cell);
            }
        }

        sf::CircleShape player(tileSize / 2 - 8);
        player.setFillColor(sf::Color::Red);
        player.setPosition(playerCol * tileSize + 8, playerRow * tileSize + 8);
        window.draw(player);

        window.draw(infoText1);
        window.draw(infoText2);
        window.draw(watermarkText);

        if (gameWon || gameLost)
        {
            window.draw(messageText);
            window.draw(retryText);
        }

        window.display();
    }

    return 0;
}
