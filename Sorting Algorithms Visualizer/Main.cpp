#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime> //for random generation
#include <string>

#define LOG(x) std::cout << x << std::endl


int main()
{
    bool isSorted = false;

    //initialize
    srand(time(0));

    int winX = 1000;
    int winY = 600;

    int comparisons = 0;

    sf::RenderWindow win(sf::VideoMode(winX, winY), "Sort Algorithm Visualizer By Macks404", sf::Style::Close);
    

    sf::Font font;
    sf::Text text;

    font.loadFromFile("D:\\Fonts\\Roboto\\Roboto-Regular.ttf");
    text.setFont(font);
    text.setString("Comparisons: 0");

    win.display();

    int barAmt;

    LOG("Enter the array size you would like (Enter a factor of 1000): ");
    try {
        std::cin >> barAmt;
    }
    catch(_exception e)
    {
        std::cout << "Please enter an integer";
    }
    int barPosNoPadding = 0;
    int padding = 10;
    int barWidth = winX / barAmt;

    std::vector<sf::RectangleShape> bars (barAmt);

    for (int i = 0; i < barAmt; i++)
    {
        //Generates bars properties giving them random heights
        bars[i].setOrigin(0, -winY);
        bars[i].setSize(sf::Vector2f(barWidth-2, (round(rand() % 1000000) + 1) / -60));
        bars[i].setFillColor(sf::Color::Yellow);
        bars[i].setPosition(barPosNoPadding, 0);

        barPosNoPadding += winX / barAmt;
    }

    //app loop
    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                win.close();
            }
        }

        //sort one
        if (!isSorted)
        {
            for (int i = 0; i < barAmt; i++)
            {
                for (int k = 0; k + 1 < barAmt; k++)
                {
                    comparisons += 1;
                    std::string comparisonsStr = std::to_string(comparisons);
                    text.setString("Comparisons: " + comparisonsStr);
                    if (k != 0)
                    {
                        bars[k - 1].setFillColor(sf::Color::Blue);
                    }
                    bars[k].setFillColor(sf::Color::Red);
                    bars[k + 1].setFillColor(sf::Color::Blue);

                    if (bars[k + 1].getSize().y > bars[k].getSize().y)
                    {
                        int temp = bars[k + 1].getSize().y;
                        bars[k + 1].setSize(sf::Vector2f(bars[k + 1].getSize().x, bars[k].getSize().y));
                        bars[k].setSize(sf::Vector2f(bars[k].getSize().x, temp));
                        

                        win.clear();
                        for (int i = 0; i < bars.size(); i++)
                        {
                            win.draw(bars[i]);
                        }
                        win.draw(text);
                        win.display();
                    }
                    
                    if (k != 0)
                    {
                        bars[k - 1].setFillColor(sf::Color::Yellow);
                    }
                    bars[k].setFillColor(sf::Color::Yellow);
                    bars[k + 1].setFillColor(sf::Color::Yellow);
                }
            }
            win.clear();
            for (int e = 0; e < barAmt; e++)
            {
                bars[e].setFillColor(sf::Color::Green);
                win.draw(bars[e]);
            }
            win.draw(text);
            win.display();
            isSorted = true;
        }
    }
}