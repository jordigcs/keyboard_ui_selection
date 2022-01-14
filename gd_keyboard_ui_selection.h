/*
Copyright 2022 Jordon Gulley

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef GODOT_KEYBOARD_UI_NAV_H
#define GODOT_KEYBOARD_UI_NAV_H

#include "core/object/class_db.h"
#include "gd_selectable.h"
#include "gd_selection_controller.h"
#include "core/object/object.h"
#include <map>
class SelectionManager : public Object {
    GDCLASS(SelectionManager, Object);

protected:
    static SelectionManager* singleton;
    static void _bind_methods();

public:
    static SelectionManager* get_singleton();
    
    SelectionController get_selection_controller();
    void select_selection_controller(SelectionController controller, int selection_index, bool new_history);
    void move_to_selection_controller(SelectionController controller, int selection_index);
    bool back_selection_controller();
    void deselect_selection_controller();

    struct SelectionManagerSettings // Holds ProjectSettings
    {
        String accept_action = "ui_accept";
        String back_action = "ui_cancel";

        String left_action = "ui_left";
        String right_action = "ui_right";
        String up_action = "ui_up";
        String down_action = "up_down";
    } settings;

	std::map<int, SelectionController*> selection_controllers;
	Array selection_history = Array();
	int current_selection_controller_index;
	int global_selection_id_index = 0;
	//bool bind_nav(Object* nav);
    SelectionManager();
};

#endif
