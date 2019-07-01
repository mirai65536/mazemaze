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

#pragma once

#include "Maze.hpp"

namespace mazemaze {

class MazeRenderer {
public:
    explicit MazeRenderer(Maze& maze);
    ~MazeRenderer();

    void update();
    void render(float playerX, float playerY);

private:
    unsigned int drawList;
    Maze& maze;
    unsigned int chunksX;
    unsigned int chunksY;

    void compileChunk(int num);
    void renderChunk(int num);
};

}
