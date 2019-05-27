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

#include "MainMenu.hpp"

#include "../Game.hpp"
#include "../Saver.hpp"

#include "States/Empty.hpp"
#include "States/Main.hpp"
#include "States/Options.hpp"
#include "States/Pause.hpp"
#include "States/Win.hpp"
#include "States/NewGame.hpp"

namespace mazemaze {
namespace gui {

MainMenu::MainMenu() {
    getDesktop()->LoadThemeFromFile("data/style.theme");

    addState(new states::Main   (getDesktop(), this));
    addState(new states::Options(getDesktop(), this));
    addState(new states::Empty  (getDesktop()));
    addState(new states::NewGame(getDesktop(), this));

    setState(0);

    StarSky* starsky = new StarSky(1024, 600.0f, 0.0f, 0.0f);

    starSkyBackground = new Background(starsky, starsky,
                                       new Camera(0.0f,  0.0f,  0.0f,
                                                  -1.5f, -2.5f, 0.0f,
                                                  110.0, 10.0,  100.0));

    setBackground(starSkyBackground);
}

MainMenu::~MainMenu() {
    delete starSkyBackground->getTickable();
    delete starSkyBackground;

    if (game != nullptr)
        delete game;
}

void
MainMenu::newGame(int mazeWidth, int mazeHeight) {
    game = new Game(this, mazeWidth, mazeHeight);
    game->newGame();

    setupGame();
}

void
MainMenu::resumeGame() {
    game = Saver::getInstance().load(this);

    setupGame();
}

void
MainMenu::stopGame() {
    backTo(0);

    delete game;

    game = nullptr;

    delete getState(5);
    delete getState(4);

    removeState(5);
    removeState(4);

    setBackground(starSkyBackground);
}

void
MainMenu::setupGame() {
    setBackground(game);

    addState(new states::Pause(getDesktop(), this, game));
    addState(new states::Win  (getDesktop(), game));

    setState(2);
}

}
}