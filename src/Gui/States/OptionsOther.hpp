/*
 * Copyright (c) 2019, Мира Странная <rsxrwscjpzdzwpxaujrr@yahoo.com>
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

#include "Options.hpp"

#include <SFGUI/SFGUI.hpp>

namespace mazemaze {

class Settings;

namespace gui {

class MainMenu;

namespace states {

class OptionsOther : public Options {
public:
    explicit OptionsOther(MainMenu& mainMenu, Settings& settings);
    ~OptionsOther() override;

    void onResetText() override;

private:
    sfg::ComboBox::Ptr    langCombo;
    sfg::CheckButton::Ptr autosaveCheck;
    sfg::CheckButton::Ptr showFpsCheck;

    Option langOpt;
    Option autosaveOpt;
    Option showFpsOpt;

    void initSignals();
    void initOptions();
};

}
}
}
