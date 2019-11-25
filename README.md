# QTaskbarControl
A class to create a taskbar/launcher progress and more, for all desktop platforms

## Features
- Show a progress in the taskbar/launcher/dock/…
- Show a badge with a number in the taskbar/launcher/dock/…
- Works on:
	- Windows >= 7
	- macOS
	- Linux (Desktops that support the `com.canonical.Unity.LauncherEntry` D-Bus signal, for example Unity, KDE)
- Additional Windows Features:
	- Set the badge icon background and text color
	- Set the progress state (running, paused, stopped)
	- Show indeterminate progress

## Installation
The package is provided via qdep, as `Skycoder42/QTaskbarControl`. To use it simply:

1. Install and enable qdep (See [qdep - Installing](https://github.com/Skycoder42/qdep#installation))
2. Add the following to your pro file:
```qmake
QDEP_DEPENDS += Skycoder42/QTaskbarControl
!load(qdep):error("Failed to load qdep feature! Run 'qdep.py prfgen --qmake $$QMAKE_QMAKE' to create it.")
```

## Usage
For most platforms, you simply need to create an instance of the class for a window, and your good to go. For Linux however, you need to do additional setup. Read [Special setup for Linux](#special-setup-for-linux). The following example shows the part thats the same for all platforms:

```cpp
auto widget = new QWidget(); //your window
auto taskbar = new QTaskbarControl(widget); //MUST have a valid parent!

taskbar->setProgress(0.42);
taskbar->setProgressVisible(true);
taskbar->setCounter(42);
taskbar->setCounterVisible(true);
```

### Special setup for Linux
In order to work, the Linux implementation needs an application with a valid desktop file in an accessible location (e.g. `~/.local/share/applications/` on KDE). You need to set [desktopFileName](https://doc.qt.io/qt-5/qguiapplication.html#desktopFileName-prop) property to enable it. The following steps explain how to properly setup QTaskbarProgress with a desktop file:

1. Create a `.desktop` file. For testing purpose, the following should suffice:
```.desktop
[Desktop Entry]
Type=Application
Version=1.1
Name=<MyApp>
Exec=<path_to_MyApp>
```
2. Copy that file to a location where desktop files are found by the OS (e.g. `~/.local/share/applications`, `/usr/local/share/applications`, `/usr/share/applications`)
3. Register the desktop file in your application:

```cpp
QGuiApplication::setDesktopFileName("myapp.desktop");
```

And that's it. When you run the application it should work. I case it doesn't work: Try to set a different icon for the desktop file, e.g. `gtk-edit`. If you see that icon in the taskbar, your application gets correctly "connected" to that desktop file.

## Icon Reference
- Windows: https://www.iconfinder.com/icons/10282/circle_red_icon#size=48
