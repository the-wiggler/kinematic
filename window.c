#include <SFML/Graphics.hpp>

int main()
{
    // Create a window with size 800x600 pixels
    sf::RenderWindow window(sf::VideoMode(800, 600), "My First SFML Program");
    
    // Create a circle shape with radius 50 pixels
    sf::CircleShape circle(50.f);
    
    // Set the circle color to green
    circle.setFillColor(sf::Color::Green);
    
    // Set initial position
    circle.setPosition(100.f, 100.f);
    
    // Movement speed (pixels per frame)
    float speedX = 3.f;
    float speedY = 2.f;
    
    // Main game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window if requested
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Move the circle
        sf::Vector2f position = circle.getPosition();
        
        // Bounce off the edges
        if (position.x < 0 || position.x + 100 > 800)
            speedX = -speedX;
        if (position.y < 0 || position.y + 100 > 600)
            speedY = -speedY;
        
        // Update position
        circle.move(speedX, speedY);
        
        // Clear the window with black color
        window.clear(sf::Color::Black);
        
        // Draw the circle
        window.draw(circle);
        
        // Display what was drawn
        window.display();
    }
    
    return 0;
}

