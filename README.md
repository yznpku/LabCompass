LabCompass
[![Github All Releases](https://img.shields.io/github/downloads/yznpku/LabCompass/total.svg)](https://github.com/yznpku/LabCompass/releases)
[![Donate by PayPal](https://img.shields.io/badge/donate-%F0%9F%92%B0-1A1A1A.svg)](https://www.paypal.me/futurecode)
===

An overlay aiming to improve the quality of life when running labyrinths in [Path of Exile](https://www.pathofexile.com/).

Features
---

1. **Compass**: While inside a lab, the overlay will display a live map of the current room showing the directions of contents and exits.
2. **Planner**: You can view the entire map of a lab before entering it. With it, you can plan the route you decide to run, and the compass will guide you through the lab by showing the exit you will be taking.
3. **Timer**: It starts when you open the labyrinth and stops when you kill Izaro. Currently does not guarantee to be consistent with the official ladder.
4. **Puzzle Solver**: A handy tool to solve 8-switch puzzles.

System Requirements
---

- Windows 7/8/10.
- OpenGL 2.1 or higher. Update your graphics card drivers if you experience display issues.

Downloads
---

See the [release](https://github.com/yznpku/LabCompass/releases) section.

FAQ
---

**Q: How does it work?**

A: Every time you enter a new area, the client logs "You have entered XXXXXX." to Client.txt, which is used by LabCompass to determine your current location. LabCompass does not interact with the client in any ways other than that.

**Q: Is it legal to use? Will my account get banned for it?**

A: [It's legal.](https://i.imgur.com/Es321K1.png)

**Q: Where can I get lab notes to import?**

A: They are provided by [poelab.com](http://www.poelab.com). The download links are right below the corresponding images. Make sure you grab the latest version every day!

Build
---

After installing the latest version of Qt, run the following command to build:

    qmake LabCompass.pro
    make
