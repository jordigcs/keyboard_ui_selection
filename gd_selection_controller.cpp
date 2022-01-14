/*
Copyright 2022 Jordon Gulley

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "gd_keyboard_ui_selection.h"

void SelectionController::_bind_methods() {

}

void SelectionController::_notification(int p_what) {
    switch(p_what) {
        case NOTIFICATION_READY: {
            // On ready, set id to the current global id index (Just a simple counter)
            id = SelectionManager::get_singleton()->global_selection_id_index;
            // Increment global selection id for the next SelectionController to use.
            SelectionManager::get_singleton()->global_selection_id_index++;
            
            // Keep track of this SelectionController in the SelectionManager
            // Use map instead of Array so the SelectionController will always be at the same index,
            // Even if controllers get freed or removed.
            SelectionManager::get_singleton()->selection_controllers[id] = this;

            if(use_children_as_items) {
                
                // Iterate over children, if is Selectable: add to items Array.
                for(int i = 0; i < get_child_count();i++) {
                    if(get_child(i)->is_class("Selectable")) {
                        Selectable* s = nullptr;
                        get_child(i)->cast_to<Selectable>(s);
                        items.append(s);
                        s->controller = this;
                    }
                }
            }
        } break;
    }
}