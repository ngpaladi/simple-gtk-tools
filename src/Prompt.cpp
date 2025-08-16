#include <string>
#include <gtkmm/messagedialog.h>
#include <iostream>

#include "Prompt.h"


Prompt::Prompt(const std::string& message)
    : MessageDialog( message, false, Gtk::MESSAGE_OTHER, Gtk::BUTTONS_OK)
{
    set_title("");
    set_message(message);

    // Connect the response signal to hide the dialog when OK is clicked
    signal_response().connect([this](int response_id) {
        if (response_id == Gtk::RESPONSE_OK)
            close();
    });

    show();
}
Prompt::Prompt(int argc, char *argv[])
    : Prompt((argc > 2 && argc % 2 == 1) ? std::string(argv[2]) : std::string())
{
}
Prompt::~Prompt() = default;
// Destructor is not needed as Gtk::MessageDialog handles its own cleanup.

