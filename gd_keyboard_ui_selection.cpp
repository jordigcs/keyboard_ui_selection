/*
Copyright 2022 Jordon Gulley

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "gd_keyboard_ui_selection.h"

SelectionManager* SelectionManager::singleton;

SelectionManager* SelectionManager::get_singleton() {
    return singleton;
}

SelectionManager::SelectionManager() {
    if(get_singleton() == nullptr) {
        singleton = this;
    }
    else {
        if(singleton != this) {
            if(!Engine::get_singleton()->is_editor_hint()) {
                memdelete(singleton);
                singleton = this;
            }
        }
    }
    settings.accept_action = ProjectSettings::get_singleton()->get_setting("ui_selection/input/accept_action");
    settings.back_action = ProjectSettings::get_singleton()->get_setting("ui_selection/input/back_action");

    settings.left_action = ProjectSettings::get_singleton()->get_setting("ui_selection/input/left_action");
    settings.right_action = ProjectSettings::get_singleton()->get_setting("ui_selection/input/right_action");
    settings.up_action = ProjectSettings::get_singleton()->get_setting("ui_selection/input/up_action");
    settings.down_action = ProjectSettings::get_singleton()->get_setting("ui_selection/input/down_action");
}

SelectionController* SelectionManager::get_selection_controller() {
    if(current_selection_controller_index != -1) {
        return selection_controllers[current_selection_controller_index];
    }
    else {
        return nullptr;
    }
}

void SelectionManager::select_selection_controller(SelectionController controller, int selection_index, bool new_history) {
    if(new_history) {
        selection_history.clear();
    }
    if(current_selection_controller_index != -1) {
        selection_controllers[current_selection_controller_index].call("deselect_all");
    }
    
}

void SelectionManager::_bind_methods() {

}