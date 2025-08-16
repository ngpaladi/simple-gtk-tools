#include <cstdlib>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <utility>
#include <iostream>

#include "ButtonBox.h"

ButtonBox::ButtonBox(std::string title_string, std::vector<std::pair<std::string, std::string>> button_list)
{
    title = title_string;
    set_title(title);
    set_border_width(12);
    set_default_size(400, -1);

    grid.set_column_homogeneous(true);
    grid.set_row_spacing(12);
    add(grid);

    for (int i = 0; i < button_list.size(); i++)
    {
        button.push_back(Gtk::Button());
        button[i].set_label((button_list[i].first).c_str());

        if (i == 0)
            grid.add(button[i]);
        else
            grid.attach_next_to(button[i], button[i - 1], Gtk::POS_BOTTOM, 1, 1);
    }
    for (int i = 0; i < button_list.size(); i++)
    {
        button[i].signal_clicked().connect(
            sigc::bind<Glib::ustring>(sigc::mem_fun(*this,
                                                    &ButtonBox::on_button),
                                      button_list[i].second));
    }
    grid.show_all();
}
ButtonBox::ButtonBox(int argc, char *argv[])
    : ButtonBox(
        (argc > 2 && argc % 2 == 1) ? std::string(argv[2]) : std::string(),
        [&]() {
            std::vector<std::pair<std::string, std::string>> buttons;
            if (argc > 2 && argc % 2 == 1)
            {
                for (int i = 3; i < argc; i += 2)
                {
                    buttons.push_back(std::pair<std::string, std::string>(std::string(argv[i]), std::string(argv[i + 1])));
                }
            }
            else
            {
                std::cerr << "Requires an odd number of arguments (title + n*(name + action))!" << std::endl;
                std::exit(EXIT_FAILURE);
            }
            return buttons;
        }()
    )
{
    // Nothing needed here
}

ButtonBox::~ButtonBox() = default;
// Destructor is not needed as Gtk::Window handles its own cleanup.

void ButtonBox::on_button(const Glib::ustring &data)
{
    std::cout << "Running `" << data << "`" << std::endl;
    system(data.c_str());
    return;
}
