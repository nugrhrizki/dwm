Patched version of dwm by me
============================

Requirements
------------
* Xlib header files.
* libxft-bgra [[AUR]](https://aur.archlinux.org/packages/libxft-bgra-git/) | [[patched]](https://github.com/uditkarode/libxft-bgra) | [[source]](https://gitlab.freedesktop.org/xorg/lib/libxft.git)
* nerd-fonts [[AUR]](https://aur.archlinux.org/packages/?O=0&SeB=nd&K=nerd+fonts&outdated=&SB=n&SO=a&PP=50&do_Search=Go) | [[source]](https://github.com/ryanoasis/nerd-fonts)
* dmenu [[MY BUILD]](https://github.com/nugrhrizki/dmenu) | [[source]](https://tools.suckless.org/dmenu/)

> **NOTE:** in config.h there is dmenu_cmd which I have modified,<br>
> so I recommend using my build [dmenu](https://github.com/nugrhrizki/dmenu), or you can do whatever you want

Patches
-------
* fake fullscreen: prevents dwm from crashing when fullscreen
* full gaps: add gaps around the window (toggleable)
* hide vacant tags: prevents dwm from drawing tags with no clients
* pertag: keeps layout, mwfact, barpos and nmaster per tag.
* scratchpads: like a drop-down terminal but more than that
* systray: support system tray, system tray will appear in the bar
* support emoji: i mean colored emoji. that's why you need to install libxft-bgra

Installation
------------
```sh
# Clone the repository to your machine
git clone https://github.com/nugrhrizki/dwm.git

# Open the repo
cd dwm

# Edit config.mk to match your local setup (dwm is installed into
# the /usr/local namespace by default).

# Afterwards enter the following command to build and install dwm (if
# necessary as root):

sudo make install
```


Starting dwm
-----------
Select _Dwm_ from the menu in a **display manager** of choice.
Alternatively, you can start dwm with **startx** append `exec dwm` to `~/.xinitrc` for example:

```sh
exec dwm
```

> see [here](https://github.com/nugrhrizki/dotfiles/blob/main/config/X11/xinitrc) for reference


Statusbar
---------
In order to display status info in the bar, you can do something
like this in your `~/.xinitrc`:

```sh
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
    sleep 1
done &
exec dwm
```

> **Note**: I would recommend to using [dwmblocks](https://github.com/LukeSmithxyz/dwmblocks) for statusbar

Configuration
-------------
The configuration of dwm is done by modifying config.h
and (re)compiling the source code.

Issue
-----
Java applications which use the **XToolkit/XAWT** backend may draw grey windows
only. The **XToolkit/XAWT** backend breaks ICCCM-compliance in recent JDK 1.5 and early
JDK 1.6 versions, because it assumes a reparenting window manager.

Possible workarounds are using JDK 1.4 (which doesn't contain the **XToolkit/XAWT** backend) or setting the
environment variable (to use the older Motif backend instead)

    AWT_TOOLKIT=MToolkit

or running

    xprop -root -f _NET_WM_NAME 32a -set _NET_WM_NAME LG3D

or (to pretend that a non-reparenting window manager is running that the XToolkit/XAWT backend can recognize)

    wmname LG3D

or when using OpenJDK setting the environment variable

    _JAVA_AWT_WM_NONREPARENTING=1

[see](https://github.com/nugrhrizki/dotfiles/blob/8335b2be9d9041e0a0e85ea07ce9f7b228da7a35/config/shell/profile#L54-L57) what i did to fix the issue
