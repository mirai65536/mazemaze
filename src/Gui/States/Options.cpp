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

#include "Options.hpp"

#include "../../utils.hpp"
#include "../../Settings.hpp"

#include "../MainMenu.hpp"

using namespace sfg;

namespace mazemaze {
namespace gui {
namespace states {

sf::Vector2f
Options::getSeparatorRequiredRequisition(float requiredWidth, Box::Ptr current) {
    float fullscreenBoxWidth = current->GetRequisition().x;
    float separatorWidth = requiredWidth - fullscreenBoxWidth;

    return {separatorWidth, 0.0f};
}

Box::Ptr
Options::addToOptionsList(const sf::String& label, Widget::Ptr widget) {
    auto alignment1 = Alignment::Create();
    auto alignment2 = Alignment::Create();
    auto box        = Box::Create();

    alignment1->Add(Label::Create(label));

    alignment1->SetScale({0.0f, 0.0f});
    alignment1->SetAlignment({0.0f, 0.5f});

    alignment2->Add(widget);

    alignment2->SetScale({0.0f, 0.0f});
    alignment2->SetAlignment({1.0f, 0.5f});

    box->Pack(alignment1);
    box->Pack(alignment2);
    box->SetClass("options");

    return box;
}

void
Options::initSignals(MainMenu& mainMenu) {
    fullscreenCheck->GetSignal(Widget::OnLeftClick).Connect([this] () {
        settings.setFullscreen(fullscreenCheck->IsActive());
    });

    antialiasingCombo->GetSignal(ComboBox::OnSelect).Connect([this] () {
        int item = antialiasingCombo->GetSelectedItem();
        unsigned int antialiasing = 1;

        for (int i = 0; i < item; i++)
            antialiasing *= 2;

        if (antialiasing == 1)
            antialiasing = 0;

        settings.setAntialiasing(antialiasing);
    });

    langCombo->GetSignal(ComboBox::OnSelect).Connect([this] () {
        const std::string* const langCodes = settings.getSupportedLangs();

        settings.setLang(langCodes[langCombo->GetSelectedItem()]);
    });

    vsyncCheck->GetSignal(Widget::OnLeftClick).Connect([this] () {
        settings.setVsync(vsyncCheck->IsActive());
    });

    autosaveCheck->GetSignal(Widget::OnLeftClick).Connect([this] () {
        settings.setAutosave(autosaveCheck->IsActive());
    });

    backButton->GetSignal(Widget::OnLeftClick).Connect([&mainMenu] () {
        mainMenu.back();
    });
}

void
Options::initAntialiasingCombo() {
    int maxAntialiasing = settings.getMaxAntialiasing();

    antialiasingCombo->AppendItem(pgtx("options", "No"));

    for (int i = 2; i <= maxAntialiasing; i *= 2)
        antialiasingCombo->AppendItem(format("%dx", i));
}

void
Options::initOptions() {
    fullscreenCheck->SetActive(settings.getFullscreen());

    initAntialiasingCombo();

    unsigned int antialiasing = settings.getAntialiasing();

    if (antialiasing == 0)
        antialiasing = 1;

    for (unsigned int i = 0, j = 1; j <= antialiasing; i++, j *= 2)
        if (j == antialiasing) {
            antialiasingCombo->SelectItem(i);
            break;
        }

    langCombo->AppendItem(L"English");
    langCombo->AppendItem(L"Русский");
    langCombo->AppendItem(L"Українська");
    langCombo->AppendItem(L"Қазақша");

    std::string lang = settings.getLang();
    const std::string* const langCodes = settings.getSupportedLangs();

    for (int i = 0; i < settings.getSupportedLangsCount(); i++)
        if (langCodes[i] == lang)
            langCombo->SelectItem(i);

    vsyncCheck->SetActive(settings.getVsync());
    autosaveCheck->SetActive(settings.getAutosave());
}

Options::Options(Desktop& desktop, MainMenu& mainMenu, Settings& settings) :
        State(desktop),
        settings(settings),
        backButton       (Button::Create(pgtx("options", "Back"))),
        fullscreenCheck  (CheckButton::Create(L"")),
        vsyncCheck       (CheckButton::Create(L"")),
        antialiasingCombo(ComboBox::Create()),
        langCombo        (ComboBox::Create()),
        autosaveCheck    (CheckButton::Create(L"")) {
    auto window             = Window::Create(Window::Style::BACKGROUND);
    auto scroll             = ScrolledWindow::Create(Adjustment::Create(), Adjustment::Create());
    auto windowBox          = Box::Create(Box::Orientation::VERTICAL);
    auto graphicsGroupLabel = Label::Create(pgtx("options", "Graphics"));
    auto otherGroupLabel    = Label::Create(pgtx("options", "Other"));
    auto separator          = Separator::Create();
    auto groupSeparator1    = Separator::Create();
    auto groupSeparator2    = Separator::Create();

    scroll->SetScrollbarPolicy(ScrolledWindow::ScrollbarPolicy::HORIZONTAL_AUTOMATIC |
                               ScrolledWindow::ScrollbarPolicy::VERTICAL_ALWAYS);

    graphicsGroupLabel->SetClass("optionsGroup");
    otherGroupLabel->SetClass("optionsGroup");

    windowBox->Pack(otherGroupLabel);
    windowBox->Pack(addToOptionsList(pgtx("options", "Language"), langCombo));
    windowBox->Pack(addToOptionsList(pgtx("options", "Autosave"), autosaveCheck));
    windowBox->Pack(groupSeparator1);
    windowBox->Pack(graphicsGroupLabel);
    windowBox->Pack(addToOptionsList(pgtx("options", "Fullscreen"), fullscreenCheck));
    windowBox->Pack(addToOptionsList(pgtx("options", "Antialiasing"), antialiasingCombo));
    windowBox->Pack(addToOptionsList(pgtx("options", "V-Sync"), vsyncCheck));  
    windowBox->Pack(groupSeparator2);

    groupSeparator1->SetRequisition({0.0f, 40.0f});
    groupSeparator2->SetRequisition({0.0f, 80.0f});
    separator->SetRequisition({440.0f, 0.0f});
    windowBox->Pack(separator);

    scroll->AddWithViewport(windowBox);
    window->Add(scroll);
    window->SetRequisition({512.0f, 300.0f});

    box = Box::Create(Box::Orientation::VERTICAL);
    box->SetSpacing(20.0f);
    box->Pack(window);
    box->Pack(backButton);

    desktop.Add(box);

    initSignals(mainMenu);
    initOptions();

    center();
}

Options::~Options() = default;

}
}
}
