#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

float ground = 530;

class PLAYER {
public:
    FloatRect rect, rect_2;
    float dx, dy;
    bool onGround;
    Sprite sprite;
    

   
    PLAYER(Texture& image)
    {
        sprite.setTexture(image);
        rect = FloatRect(400, 50, 50, 50);
        rect_2 = FloatRect(0, 0, 800, 800);

        dx = dy = 0;
    }

    void update(float time)
    {
        rect.left += dx * time;
        if (!onGround)
            dy = dy + 0.0002 * time;
        rect.top += dy * time;
        onGround = false;
        if (rect.top > ground)
        {
            rect.top = ground;
            dy = 0;
            onGround = true;
        }
        sprite.setPosition(rect.left, rect.top);
        sprite.setOrigin(129.5, 128.5);
        sprite.setRotation(rect.left);
        dx = 0;
    }
};


int main()
{
    setlocale(LC_ALL, "ru");
    RenderWindow window(VideoMode(1000, 800), "Картинка!");

    Image ball;
    ball.loadFromFile("ball.png");
    ball.createMaskFromColor(Color(0, 0, 0));
    Texture t;
    t.loadFromImage(ball);
    Texture t_2;
    t_2.loadFromFile("field.png");

    

    PLAYER p(t);

    Clock clock;

    Sprite sprite_2;
    sprite_2.setTexture(t_2);

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 200;

            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                p.dx = -0.1;
            }
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                p.dx = 0.1;
            }
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                if (p.onGround)
                {
                    p.dy = -0.4;
                    p.onGround = false;
                }
            }
            p.update(time);
            window.clear(Color::White);
            sprite_2.setPosition(0, 0);
            window.draw(sprite_2);
            window.draw(p.sprite);
           
            window.display();
    }
    return 0;
}


int move(int x)
{
    x += 10;
    return x;
}