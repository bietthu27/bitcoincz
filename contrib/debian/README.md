
Debian
====================
This directory contains files used to package bczd/bcz-qt
for Debian-based Linux systems. If you compile bczd/bcz-qt yourself, there are some useful files here.

## bcz: URI support ##


bcz-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bcz-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bczqt binary to `/usr/bin`
and the `../../share/pixmaps/bcz128.png` to `/usr/share/pixmaps`

bcz-qt.protocol (KDE)

