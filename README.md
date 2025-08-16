# simple-gtk-tools (sgt)
Collection of command line utilities to create simple gtk windows on the fly, designed to be useful for scripts with GUI prompts.

## Prompt
```sgt prompt [message]```

Displays a message in a GTK MessageDialog window, which closes when "OK" is pressed. This is great for holding scripts in a container pending user interaction in a way that is more visible then text input.

## Button Box
```sgt buttonbox [title] [command] [button name] [command] ...```

Dynamically creates and displays a series of buttons in a GTK window, which each run a command when pressed. This is great if you have repetitive things you need to do in a container.
