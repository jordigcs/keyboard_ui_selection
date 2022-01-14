/*
Copyright 2022 Jordon Gulley

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "gd_keyboard_ui_selection.h"

// Update pages variable, what items are shown depends on if selected is within a certain bound for that page
void SelectionController::update_pages() {
    if(items.size()> 0) {
        if(scroll_region_size != -1) {
            pages.clear();
            int last = -1;
            int begin_index_offset = 0;
            int _srs = scroll_region_size - 1;

            for(int i = 0;i < (items.size()/scroll_region_size);i++) {
                pages.append(Vector2(i*_srs+begin_index_offset, i*scroll_region_size+_srs));
                begin_index_offset += 1;
            }
            if(pages[MAX(pages.size()-1, 0)].y < items.size()) {
                pages.append(Vector2(pages[MAX(pages.size()-1, 0)].y+1, pages[MAX(pages.size()-1, 0)].y + (items.size() - pages[MAX(pages.size()-1, 0)].y)));
            }
        }
        else {
            pages.clear();
            pages.append(Vector2(0, items.size()-1));
        }
    }
}

void SelectionController::update_current_page() {
    if(current_page <= pages.size()-1) {
        if(selected_index != pages[current_page].x) {
            for(int i = 0; i < pages.size();i++) {
                if(pages[i].x >= selected_index) {
                    if(pages[i].y <= selected_index) {
                        current_page = i;
                    }
                }
            }
        }
    }
    else {
        current_page = pages.size() - 1;
    }
}

void SelectionController::update_scroll() {
    if(selected_index == -1) {
        for(int i = 0; i < items.size();i++) {
            items[i].call("hide");
        }
        selected_index = 0;
        return;
    }
    update_current_page();
    if(pages.size() > 1) {
        for(int i = 0; i < items.size(); i++) {
            bool show = true;
            if(pages[current_page].x != pages[current_page].y) {
                if(i < pages[current_page].x || i > pages[current_page].y && pages[current_page].y != 0) {
                    show = false;
                }
            }
            else if(i != pages[current_page].x) {
                show = false;
            }

            if(show) {
                items[i].call("hide");
            }
            else {
                items[i].call("hide");
            }
        }
    }
    else {
        for(int i = 0; i < items.size();i++) {
            items[i].call("show");
        }
    }

    //TODO: Reimpl Scroll Indicators (SelectionController.gd:157)
}

void SelectionController::update_selection() {
    update_scroll();
    if(SelectionManager::get_singleton()->current_selection_controller_index == id) {
        for(int i = 0; i < items.size();i++) {
            if(i == selected_index) {
                items[i].call("select");
            }
            else {
                items[i].call("deselect");
            }
        }
    }
}

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
        case NOTIFICATION_PREDELETE: {
            SelectionManager::get_singleton()->selection_controllers.erase(id);
        }
    }
}

void SelectionController::_input(InputEvent event) {
    if(SelectionManager::get_singleton()->current_selection_controller_index == id) {
        if(items.size() > 0) {
            if(event.is_action_pressed(SelectionManager::get_singleton()->settings.accept_action)) {
                if(items[selected_index].get("clickable")) {
                    accept_event();
                    emit_signal("clicked");
                    items[selected].call("click");
                }
                return;
            }
            else if(event.is_action_pressed(SelectionManager::get_singleton()->settings.back_action)) {
                accept_event();
                emit_signal("cancel");
                if(SelectionManager::get_singleton()->selection_history.size() > 1) {
                    SelectionManager::get_singleton()->back_selection_controller();
                }
            }
        }
    }
}
