/*
 * Copyright (c) 2019, Мира Странная <miraityan2004@gmail.com>
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

#pragma once

#include <SFML/Graphics.hpp>

namespace mazemaze {

class GraphicEngine {
public:  
    void openWindow(unsigned int width, unsigned int height, bool fullscreen);
    void openWindow(sf::VideoMode videoMode, bool fullscreen);

    void update();
    void setStates();

    void setFullscreen(bool fullscreen);
    void setAntialiasing(unsigned int antialiasing);
    void setVsync(bool vsync);

    sf::RenderWindow* getWindow() const;
    int getWidth() const;
    int getHeight() const;
    unsigned int getMaxAntialiasing();
    bool getFullscreen() const;
    bool getVsync() const;

    GraphicEngine(GraphicEngine const&) = delete;
    void operator= (GraphicEngine const&) = delete;

    static GraphicEngine& getInstance() {
        static GraphicEngine instance;
        return instance;
    }

private:
    GraphicEngine();
    ~GraphicEngine();

    sf::RenderWindow* window;

    sf::Vector2i oldWindowPos;
    sf::Vector2u oldWindowSize;

    int width;
    int height;
    int maxAntialiasing;
    bool needReopen;
    bool fullscreen;
    bool vsync;
    sf::ContextSettings settings;
    sf::VideoMode videoMode;

    sf::Image* icon;
};

}
