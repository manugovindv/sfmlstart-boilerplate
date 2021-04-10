#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

int main()
{   
    const int winx = 1000;
    const int winy = 800;

    const int num = 200;

    int i=0,j=0;
    float speed = 200.0;

    float a = 0.0, b = 0.0, temp = 0.0;


    sf::RenderWindow window(sf::VideoMode(winx, winy), "Bubble Sort!");
    window.setFramerateLimit(60);
    
    float rectw = static_cast<float>(winx / num);  
    float recth = 1.0;
    //std::vector<sf::RectangleShape> rect(num);
    sf::RectangleShape rect[num];
    int arr[num];
    for (i = 0;i < num;i++) 
    {
        arr[i] = i;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(std::begin(arr), std::end(arr),std::default_random_engine(seed));
    for (i = 0;i < num;i++)
    {
        recth = static_cast<float>(i * winy / num);  //static_cast<float>(i) * winy / winx)
        rect[i].setSize(sf::Vector2f(rectw, recth));
        rect[i].setOrigin(0.0f, recth);  
        rect[i].setPosition(arr[i]*rectw, static_cast<float>(winy));
        rect[i].setFillColor(sf::Color(66, 245, 105, 255));
        rect[i].setOutlineThickness(-1);
        rect[i].setOutlineColor(sf::Color(0, 0, 0, 125));
        std::cout << "Hello  " << i <<"   "<<arr[i]<< std::endl;
    }
    
    

    i = 0;
    //float deltatime = 0.0f;
    //sf::Clock clock;
    while (window.isOpen())
    {
        //deltatime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            if(event.type == sf::Event::Closed ||(sf::Event::KeyPressed && event.key.code==sf::Keyboard::Escape))
            {
                window.close();
            }
        }
        

        if (i < num) 
        {
            for (j = 0;j < num - i - 1;j++)
            {
                a = rect[j].getPosition().x;
                b = rect[j + 1].getPosition().x;
                if (a > b)
                {
                    rect[j].setPosition(b, static_cast<float>(winy));
                    rect[j + 1].setPosition(a, static_cast<float>(winy));
                }
            }
            i++;
        }
        


        
        window.clear();
        for (int k = 0;k < num;k++)
        {
            window.draw(rect[k]);
            //std::cout << "Heo " <<  std::endl;
        }
        window.display();
    }

    return 0;
}





/*
for (i = 0;i < num;i++)
        {
            for (j = 0;j < num - i - 1;j++)
            {
                a = rect[j].getPosition().x;
                b = rect[j+1].getPosition().x;
                if (a > b)
                {
                    rect[j].setPosition(b, static_cast<float>(winy));
                    rect[j+1].setPosition(a, static_cast<float>(winy));

                }
            }
        }
*/