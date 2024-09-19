#pragma once
#include "Libraries.h"
#include "Constants.h"
#include "ToolBar.h"
#include "Camera.h"

class Screen : 
    public sf::Drawable {
private:
    ToolBar toolBar;
    Camera camera;

public:
    Screen(int toolBarWidth, sf::Vector2f gridSize, sf::RenderWindow& window) : 
        camera(sf::Vector2f(toolBarWidth, 0), sf::Vector2f(gridSize.x - toolBarWidth, gridSize.y), Constants::CELL_SIZE) {
        toolBar.addButton("../assets/images/screenshot.png", [this, &window]() {
            saveScreenshot(window);
        });

        toolBar.addButton("../assets/images/clear.png", [this]() {
            camera.clearGrid();
        });

        toolBar.addToggle("../assets/images/update.png", [this]() {
            camera.updateGrid();
        });

        toolBar.addNumberSelection();
    
        toolBar.addButton("../assets/images/triangle.png", [this]() {
            camera.setShape(TRIANGLE);
        });
        
        toolBar.addButton("../assets/images/rectangle.png", [this]() {
            camera.setShape(RECTANGLE);
        });

        toolBar.addButton("../assets/images/hexagon.png", [this]() {
            camera.setShape(HEXAGON);
        });
    }

    void eventProcessing(sf::Event& event, sf::RenderWindow& window) {
        toolBar.eventProcessing(event);
        camera.eventProcessing(event);

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P) {
                saveScreenshot(window);
            }
        }
    }

    void update(sf::RenderWindow& window) {
        toolBar.update();

        camera.update(window, [this]() {
            return toolBar.getSandNumber();
        });
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(camera, states);
        target.draw(toolBar, states);
    }

private:
    void saveScreenshot(sf::RenderWindow& window) {
        std::string filename = "../screenshots/";
        filename += std::to_string(std::time(nullptr));
        filename += ".png";

        sf::Texture texture;
        texture.create(window.getSize().x, window.getSize().y);
        texture.update(window);
        texture.copyToImage().saveToFile(filename);
    }
};
