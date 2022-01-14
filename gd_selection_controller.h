/*
Copyright 2022 Jordon Gulley

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef GODOT_UI_NAV_H
#define GODOT_UI_NAV_H

#include "scene/gui/control.h"
#include "gd_selectable.h"
// SelectionController -> Controls the selection of Selectable UIs
// Only one SelectionController can be active at a time.
// Use SelectionManager.select_selection_manager(SelectionController controller) to activate.

class SelectionController : public Control {
    GDCLASS(SelectionController, Control);

    protected:
        static void _bind_methods();

    public:
        enum Shape {
            Column,
            Row
        };

        int current_page = 0;
        PackedVector2Array pages;

        void update_pages();
        void update_current_page();
        void update_scroll();
        void update_selection();


        Array items = Array();
        int selected_index = 0;
        int scroll_region_size = -1; // -1 to show all (no scroll)

        Shape shape = Column;
        bool loop = false;
        bool use_children_as_items = false;

        int id = 0; // Identifier used to differientate different SelectionControllers.
        void _notification(int p_what);
        void _input(InputEvent event);
};
#endif