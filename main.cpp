#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>



int* HSVtoRGB(float H, float S, float V) {
    static int rgb[3];
    if (H == 0) {
        H += 0.1;
    }
    if (H > 360 || H < 0 || S>100 || S < 0 || V>100 || V < 0) {
        std::cout << "The givem HSV values are not in valid range: H: " <<H<<" S: "<<S <<" V: "<<V<<std::endl;
        return rgb;
    }
    float s = S / 100;
    float v = V / 100;
    float C = s * v;
    float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
    float m = v - C;
    float r, g, b;
    if (H >= 0 && H < 60) {
        r = C, g = X, b = 0;
    }
    else if (H >= 60 && H < 120) {
        r = X, g = C, b = 0;
    }
    else if (H >= 120 && H < 180) {
        r = 0, g = C, b = X;
    }
    else if (H >= 180 && H < 240) {
        r = 0, g = X, b = C;
    }
    else if (H >= 240 && H < 300) {
        r = X, g = 0, b = C;
    }
    else {
        r = C, g = 0, b = X;
    }
    rgb[0] = (r + m) * 255;
    rgb[1] = (g + m) * 255;
    rgb[2] = (b + m) * 255;

    return rgb;
}




int main()
{   
    const int winx = 1600;
    const int winy = 800;

    const int num = 500;

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

    int* rgbval;

    

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(std::begin(arr), std::end(arr),std::default_random_engine(seed));
    for (i = 0;i < num;i++)
    {
        rgbval = HSVtoRGB((i * 355.0 / num), 90.0, 90.0);
        recth = static_cast<float>(i * winy / num);  //static_cast<float>(i) * winy / winx)
        rect[i].setSize(sf::Vector2f(rectw, recth));
        rect[i].setOrigin(0.0f, recth);  
        rect[i].setPosition(arr[i]*rectw, static_cast<float>(winy));
        rect[i].setFillColor(sf::Color(rgbval[0], rgbval[1], rgbval[2], 255));   //(66, 245, 105, 255)
        rect[i].setOutlineThickness(-0.8);
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