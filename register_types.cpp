/*
Copyright 2022 Jordon Gulley

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "register_types.h"

#include "gd_keyboard_ui_selection.h"
SelectionManager* SelectionManagerPtr = nullptr;

void register_keyboard_ui_selection_types() {
    ClassDB::register_class<SelectionManager>();
    ClassDB::register_class<SelectionController>();
    ClassDB::register_class<Selectable>();

    SelectionManagerPtr = memnew(SelectionManager);
    Engine::get_singleton()->add_singleton(Engine::Singleton("SelectionManager", SelectionManager::get_singleton()));

    // Add Keyboard Selection settings
    if(Engine::get_singleton()->is_editor_hint()) {
        if(!ProjectSettings::get_singleton()->has_setting("ui_selection/input/accept_action")) {
            ProjectSettings::get_singleton()->set_setting("ui_selection/input/accept_action", "ui_accept");
            ProjectSettings::get_singleton()->set_setting("ui_selection/input/left_action", "ui_left");
            ProjectSettings::get_singleton()->set_setting("ui_selection/input/right_action", "ui_right");
            ProjectSettings::get_singleton()->set_setting("ui_selection/input/up_action", "ui_up");
            ProjectSettings::get_singleton()->set_setting("ui_selection/input/down_action", "ui_down");
            ProjectSettings::get_singleton()->set_setting("ui_selection/input/back_action", "ui_cancel");
            ProjectSettings::get_singleton()->set_initial_value("ui_selection/input/accept_action", "ui_accept");
            ProjectSettings::get_singleton()->set_initial_value("ui_selection/input/left_action", "ui_left");
            ProjectSettings::get_singleton()->set_initial_value("ui_selection/input/right_action", "ui_right");
            ProjectSettings::get_singleton()->set_initial_value("ui_selection/input/up_action", "ui_up");
            ProjectSettings::get_singleton()->set_initial_value("ui_selection/input/down_action", "ui_down");
            ProjectSettings::get_singleton()->set_initial_value("ui_selection/input/back_action", "ui_cancel");
        }
    }
}

void unregister_keyboard_ui_selection_types() {
    memdelete(SelectionManagerPtr);
}
