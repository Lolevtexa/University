#include "DrawablePlane.h"

const int WIDTH = 600;
const int HEIGHT = 600;
const int GRID_SIZE = 20;


int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sand Heap");
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(60);

    int planeType = RECTANGULAR;
    DrawablePlane sandHeap(window, planeType, GRID_SIZE);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // int droped = 0, needToDrop = 1, printAfterDrop = 1;
    int droped = 0, needToDrop = 1, printAfterDrop = 1;
    bool saveScreenshot = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / GRID_SIZE;
                int y = event.mouseButton.y / GRID_SIZE;
                sandHeap.addSand(x, y);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
                saveScreenshot = true;
            }
        }
        if (droped < needToDrop) {
            sandHeap.addSand(WIDTH / GRID_SIZE / 2, HEIGHT / GRID_SIZE / 2, printAfterDrop);
            droped += printAfterDrop;
        }

        sandHeap.simulate();
        if (droped % printAfterDrop == 0) {
            sandHeap.draw();

            if (saveScreenshot) {
                sf::Texture texture;
                texture.create(window.getSize().x, window.getSize().y);
                texture.update(window);
                if (texture.copyToImage().saveToFile("../img/afterDrop" + std::to_string(droped) + ".png")) {
                    std::cout << "Screenshot saved successfully!" << std::endl;
                } else {
                    std::cout << "Failed to save the screenshot." << std::endl;
                }
                saveScreenshot = false;
            }
        }

        sandHeap.simulate();
        if (droped % printAfterDrop == 0) {
            sandHeap.draw();

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            start = std::chrono::high_resolution_clock::now();

            std::cout << "Time between drop: " << duration.count() << " milliseconds" << std::endl;
            std::cout << "droped: " << droped << std::endl;
        }
    }

    return 0;
}
