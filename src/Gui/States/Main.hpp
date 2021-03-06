/*
 * Copyright (c) 2019-2020, Мира Странная <rsxrwscjpzdzwpxaujrr@yahoo.com>
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

    void center() override;
    void resetText() override;

private:
    sfg::Button::Ptr buttonResume;
    sfg::Button::Ptr buttonNewGame;
    sfg::Button::Ptr buttonOptions;
    sfg::Button::Ptr buttonAbout;
    sfg::Button::Ptr buttonExit;

    Settings& settings;

    int newGameState;
    int optionsState;
    int aboutState;

    bool showing;

    void initSignals(MainMenu& mainMenu);
};

}
}
}
