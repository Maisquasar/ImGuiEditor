# ImGuiEditor

## Overview
**ImGuiEditor** is a simple tool designed to facilitate the creation process with ImGui by providing a user-friendly interface.

## Features
- **Real-Time Preview**: See your UI changes in real-time as you build and edit your layout, ensuring that your ImGui code matches your vision immediately.
- **User-Friendly Interface**: ImGuiEditor provides a graphical interface that allows users to interact with ImGui layouts easily.
- **Clipboard Copy**: The main functionality of the tool is to copy the generated ImGui code to the clipboard, streamlining the integration process into your projects.
- **Copy and Paste**: Users can quickly copy and paste elements within the editor to expedite the creation of complex interfaces.

## How to use it

### Create Window
This is the starting point for building your ImGui interface:

- **Items**: These are basic ImGui widgets like Buttons, Text, Checkboxes, etc., which can be directly placed on the canvas.
- **Scope**: These are container widgets that encapsulate other widgets. Examples include Child, Group, ... They require a begin and end call in ImGui, and they define the scope for their children.
- **Shape**: These are primitives drawn directly onto the window's draw list.

Note : There is also an Empty item useful to change style of all childs objects

### Hierarchy Window
The Hierarchy Window is where you can manage the structure of your ImGui interface:

- **Parent-Child Relationships**: Understand at a glance how your interface is structured. Scope items can act as parents to other widgets, defining a clear hierarchy.
- **Drag-and-Drop Reordering**: Easily restructure your layout by dragging widgets to change their parent-child relationships. This feature allows you to nest widgets within scopes or move them around in your design.
- **Copy and Paste**: Duplicate widgets using copy and paste functionality to speed up the design process.
- **Selection and Editing**: Click on any widget in the Hierarchy Window to select it. Once selected, you can modify its properties using the Inspector Window.

### Inspector Window
After selecting an object in the Hierarchy Window, the Inspector Window allows you to:

- **Edit Properties**: Change properties like position, size, anchor of the selected widget.
- **Customize Widgets**: Adjust specific settings for different widgets, such as the label for a button or the min/max values for a slider.
- **Apply Styles**: Apply custom styles to your widgets to make them match your application's theme or to stand out (note : all style that are change are inherited for all these childrens).

By utilizing the Create Window to add new widgets, managing them in the Hierarchy Window, and customizing them in the Inspector Window, you can quickly build and iterate on your ImGui interfaces.

### Editor Window
In this window there is many settings :

- **Save** : save your current canvas to a file.
- **Load** : load a canvas that you saved.
- **Copy Code** : copy the code into your clipboard.
- **Is Dynamic** : this checkbox is useful when you need to build a static interface where the cursor allways start at the top left of the window.
- **User Mode** : when the checkbox is check, it simulate the user interactions.

### Canvas Window
This is the demo window where you can see the layout that you made.
You can click on object to select them and drag them by holding the click

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details.
