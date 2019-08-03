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

#include "../State.hpp"

namespace mazemaze {

class Game;
class Settings;

namespace gui {

class MainMenu;

namespace states {

class Main : public State {
public:
    explicit Main(MainMenu& mainMenu, Settings& settings);
    ~Main() override;

    void show(bool show) override;
    void updateButtons(bool saveExists);

private:
    sfg::Button::Ptr buttonResume;
    sfg::Button::Ptr buttonNewGame;
    sfg::Button::Ptr buttonOptions;
    sfg::Button::Ptr buttonExit;

    int newGameState;
    int optionsState;

    void initSignals(MainMenu& mainMenu);
};

}
}
}
