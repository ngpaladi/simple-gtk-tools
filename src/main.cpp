#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <string>
#include <iostream>
#include <utility>

#include "ButtonBox.h"
#include "Prompt.h"

static int on_cmd(const Glib::RefPtr<Gio::ApplicationCommandLine> &, Glib::RefPtr<Gtk::Application> &app)
{
    app->activate();
    return 0;
}

int main(int argc, char *argv[])
{

    auto app = Gtk::Application::create(argc, argv, "com.noahpaladino.simple-gtk-tools", Gio::APPLICATION_HANDLES_COMMAND_LINE);
    app->signal_command_line().connect(sigc::bind(sigc::ptr_fun(on_cmd), app), false);

    if (argc > 1)
    {
        std::string arg = argv[1];
        std::transform(arg.begin(), arg.end(), arg.begin(),
                   [](unsigned char c){ return std::tolower(c); });
        if (arg == "buttonbox")
        {
            ButtonBox window(argc, argv);
            return app->run(window);
        }
        else if (arg == "prompt")
        {
            Prompt window(argc, argv);
            return app->run(window);
        }
        else if (arg == "help" || arg == "--help" || arg == "-h")
        {
            std::cout << "Usage: sgt [command] [args]\n"
                      << "Commands:\n"
                      << "  buttonbox  [title] [button name] [command] [button name] [command] ...\n"
                      << "  prompt     [message]\n"
                      << "  help, -h, --help - Show this help message\n";
            return EXIT_SUCCESS;
        }
        else
        {
            std::cerr << "Unknown command: " << arg << std::endl;
            std::cerr << "Use 'sgt help' for a list of commands." << std::endl;
            return EXIT_FAILURE;
        }
    }
}