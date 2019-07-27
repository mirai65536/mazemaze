/*
 * Copyright (c) 2018-2019, Мира Странная <miraityan2004@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cmath>
#include <iostream>
#include <gettext.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Desktop.hpp>

#include "Maze.hpp"
#include "MazeRenderer.hpp"
#include "Player.hpp"
#include "StarSky.hpp"
#include "Game.hpp"
#include "GraphicEngine.hpp"
#include "FpsCalculator.hpp"
#include "Settings.hpp"

#include "Gui/MainMenu.hpp"

using namespace mazemaze;

int
main() {
    setlocale(LC_ALL, "");
    bindtextdomain("mazemaze", "./locale");
    textdomain("mazemaze");
    bind_textdomain_codeset("mazemaze", "UTF-8");

    const int startWindowWidth = 854;
    const int startWindowHeight = 480;

    float frameDeltaTime = 1.0f / 60.0f;

    Settings settings;
    sfg::SFGUI sfgui;

    GraphicEngine::getInstance().openWindow(startWindowWidth, startWindowHeight, false);

    gui::MainMenu mainMenu(settings);
    sf::Clock deltaClock;

    bool running = true;

    while (running) {
        GraphicEngine::getInstance().update();
        GraphicEngine::getInstance().setStates();

        sf::RenderWindow& window = GraphicEngine::getInstance().getWindow();

        sf::Event event{};

        while (window.pollEvent(event)) {
            mainMenu.handleEvent(event);

            switch (event.type) {
                case sf::Event::Closed:
                    running = false;
                    break;

                default:
                    break;
            }
        }

        mainMenu.tick(frameDeltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainMenu.render();

        window.resetGLStates();
        sfgui.Display(window);
        window.display();

        running &= !mainMenu.isWantExit();

        frameDeltaTime = deltaClock.getElapsedTime().asSeconds();
        deltaClock.restart();
    }

    std::cout << std::endl;

    return 0;
}
