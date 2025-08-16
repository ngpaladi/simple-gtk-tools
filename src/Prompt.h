#pragma once

#include <cstdlib>
#include <gtkmm/window.h>
#include <gtkmm/messagedialog.h>
#include <utility> 


class Prompt : public Gtk::MessageDialog {
public:
    Prompt(const std::string& message);
    Prompt(int argc, char *argv[]);
    ~Prompt();
private:
    std::string message;
};


