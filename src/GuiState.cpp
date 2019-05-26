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

#include "GuiState.hpp"

#include "GraphicEngine.hpp"

namespace mazemaze {

GuiState::GuiState(sfg::Desktop* desktop) : desktop(desktop) {
    box = sfg::Box::Create();
}

GuiState::~GuiState() {
    desktop->Remove(getMainContainer());
}

void
GuiState::center(sf::Event event) {
    sf::Vector2f boxSize = box->GetRequisition();
    sf::Vector2f windowSize = sf::Vector2f(event.size.width, event.size.height);

    box->SetPosition((windowSize - boxSize) / 2.0f);
}

void
GuiState::center() {
    GraphicEngine* graphicEngine = GraphicEngine::getInstance();

    sf::Vector2f buttonSize = getMainContainer()->GetRequisition();
    sf::Vector2f windowSize = static_cast<sf::Vector2f>(graphicEngine->getWindow()->getSize());

    getMainContainer()->SetPosition((windowSize - buttonSize) / 2.0f);
}

void
GuiState::show(bool show) {
    getMainContainer()->Show(show);
}

void GuiState::tick(float deltatime) {

}

sfg::Container::Ptr GuiState::getMainContainer() {
    return box;
}

}