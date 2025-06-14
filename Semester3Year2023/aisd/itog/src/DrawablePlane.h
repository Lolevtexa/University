#pragma once
#include "Libs.h"
#include "Plane.h"

class DrawablePlane : public Plane { 
private:
    static const sf::Color background;
    static const sf::Color green;
    static const sf::Color purple;
    static const sf::Color gold;

    int GRID_SIZE;
    sf::RenderWindow& window;

    int mouseX, mouseY;

public:
    DrawablePlane(sf::RenderWindow& window, const int planeType, int GRID_SIZE) : Plane(planeType), window(window), GRID_SIZE(GRID_SIZE) {}

    void event(sf::Event event) {
        mouseX = event.mouseButton.x;
        mouseY = event.mouseButton.y;
    }

    void draw() {
        window.clear(background);

        switch (neighborsCount) {
        case TRIANGULAR:
            drawTriangular();
            break;
        
        case RECTANGULAR:
            drawRectangular();
            break;
        
        case HEXAGONAL:
            drawHexagonal();
            break;
        }

        switch (neighborsCount) {
        case TRIANGULAR:
            drawMouseTriangular();
            break;
        
        case RECTANGULAR:
            drawMouseRectangular();
            break;
        
        case HEXAGONAL:
            // drawHexagonal();
            break;
        }
        
        window.display();
    }

private:
    sf::Color grad(int value) {
        sf::Color color;
        switch (neighborsCount) {
        case TRIANGULAR:
            switch (value) {
            case 0:
                color = background;
                break;

            case 1:
                color = sf::Color(0, 255, 0);
                break;

            case 2:
                color = sf::Color(255, 255, 0);
                break;
            }
            break;
        
        case RECTANGULAR:
            switch (value) {
            case 0:
                color = background;
                break;
                
            case 1:
                color = sf::Color(0, 255, 0);
                break;
            
            case 2:
                color = sf::Color(255, 255, 0);
                break;
            
            case 3:
                color = sf::Color(255, 0, 0);
                break;
            }
            break;
        
        case HEXAGONAL:
            switch (value) {
            case 0:
                color = background;
                break;
                 
            case 1:
                color = sf::Color(0, 255, 0);
                break;

            case 2:
                color = sf::Color(255, 255, 0);
                break;

            case 3:
                color = sf::Color(255, 0, 0);
                break;

            case 4:
                color = sf::Color(0, 0, 255);
                break;

            case 5:
                color = sf::Color(255, 0, 255);
                break;
            }
            break;
        }
        return color;
    }

    void drawTriangular() {
        sf::ConvexShape cellTop;
        cellTop.setPointCount(3);
        cellTop.setPoint(0, sf::Vector2f(GRID_SIZE, 0));
        cellTop.setPoint(1, sf::Vector2f(0, GRID_SIZE));
        cellTop.setPoint(2, sf::Vector2f(GRID_SIZE * 2, GRID_SIZE));

        sf::ConvexShape cellBottom;
        cellBottom.setPointCount(3);
        cellBottom.setPoint(0, sf::Vector2f(0, 0));
        cellBottom.setPoint(1, sf::Vector2f(GRID_SIZE * 2, 0));
        cellBottom.setPoint(2, sf::Vector2f(GRID_SIZE, GRID_SIZE));

        for (auto& [position, value] : board) {
            int x = position.first;
            int y = position.second;
            if (value > 0) {
                if ((x + y) % 2 == 0) {
                    cellTop.setPosition(x * GRID_SIZE, y * GRID_SIZE);
                    cellTop.setFillColor(grad(value));
                    window.draw(cellTop);
                } else {
                    cellBottom.setPosition(x * GRID_SIZE, y * GRID_SIZE);
                    cellBottom.setFillColor(grad(value));
                    window.draw(cellBottom);
                }
            }
        }
    }

    void drawRectangular() {
        sf::RectangleShape cell(sf::Vector2f(GRID_SIZE, GRID_SIZE));
        for (auto& [position, value] : board) {
            if (value > 0) {
                cell.setPosition(position.first * GRID_SIZE, position.second * GRID_SIZE);
                cell.setFillColor(grad(value));
                window.draw(cell);
            }
        }
    }

    void drawHexagonal() {
        sf::ConvexShape cell;
        cell.setPointCount(6);
        cell.setPoint(0, sf::Vector2f(0, 0));
        cell.setPoint(1, sf::Vector2f(GRID_SIZE, 0));
        cell.setPoint(2, sf::Vector2f(GRID_SIZE + GRID_SIZE / 2, GRID_SIZE / 2));
        cell.setPoint(3, sf::Vector2f(GRID_SIZE, GRID_SIZE));
        cell.setPoint(4, sf::Vector2f(0, GRID_SIZE));
        cell.setPoint(5, sf::Vector2f(-GRID_SIZE / 2, GRID_SIZE / 2));

        for (auto& [position, value] : board) {
            if (value > 0) {
                cell.setPosition(position.first * GRID_SIZE, position.second * GRID_SIZE);
                cell.setFillColor(grad(value));
                window.draw(cell);
            }
        }
    }

    void drawMouseTriangular() {
        sf::ConvexShape cellTop;
        cellTop.setPointCount(3);
        cellTop.setPoint(0, sf::Vector2f(GRID_SIZE, 0));
        cellTop.setPoint(1, sf::Vector2f(0, GRID_SIZE));
        cellTop.setPoint(2, sf::Vector2f(GRID_SIZE * 2, GRID_SIZE));
        cellTop.setOutlineThickness(-1);
        cellTop.setOutlineColor(sf::Color::Black);
        // cellTop.setFillColor(sf::Color(255, 255, 255, 0));

        sf::ConvexShape cellBottom;
        cellBottom.setPointCount(3);
        cellBottom.setPoint(0, sf::Vector2f(0, 0));
        cellBottom.setPoint(1, sf::Vector2f(GRID_SIZE * 2, 0));
        cellBottom.setPoint(2, sf::Vector2f(GRID_SIZE, GRID_SIZE));
        cellBottom.setOutlineThickness(-1);
        cellBottom.setOutlineColor(sf::Color::Black);
        // cellBottom.setFillColor(sf::Color(255, 255, 255, 0));

        int x = mouseX / GRID_SIZE;
        int y = mouseY / GRID_SIZE;

        if ((x + y) % 2 == 0) {
            cellTop.setPosition(x * GRID_SIZE, y * GRID_SIZE);
            window.draw(cellTop);
        } else {
            cellBottom.setPosition(x * GRID_SIZE, y * GRID_SIZE);
            window.draw(cellBottom);
        }
    }

    void drawMouseRectangular() {
        sf::RectangleShape cell(sf::Vector2f(GRID_SIZE, GRID_SIZE));
        cell.setOutlineThickness(-1);
        cell.setOutlineColor(sf::Color::Black);
        // cell.setFillColor(sf::Color(255, 255, 255, 0));

        int x = mouseX / GRID_SIZE;
        int y = mouseY / GRID_SIZE;

        cell.setPosition(x * GRID_SIZE, y * GRID_SIZE);
        window.draw(cell);
    }
};

const sf::Color DrawablePlane::background = sf::Color(255, 255, 255);
const sf::Color DrawablePlane::green = sf::Color(0, 255, 0);
const sf::Color DrawablePlane::purple = sf::Color(255, 0, 255);
const sf::Color DrawablePlane::gold = sf::Color(255, 215, 0);
