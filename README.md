LabCompass
===

An overlay aiming to improve the quality of life when running labyrinths in [Path of Exile](https://www.pathofexile.com/).

Features
---

1. **Compass**: While inside a lab, the overlay will display a live map of the current room showing the directions of contents and exits.
2. **Planner**: You can view the entire map of a lab before entering it. With it, you can plan the route you decide to run, and the compass will guide you through the lab by showing the exit you will be taking.
3. **Timer**: It starts when you opens the labyrinth and stops when you kill Izaro. Currently does not guarantee to be consistent with the official ladder.
4. **Puzzle Solver**: A handy tool to solve 8-switch puzzles.

Download
---

See the [release](https://github.com/yznpku/LabCompass/releases) section.

FAQ
---

**Q: Is it legal to use? Will my account get banned for it?**

A: [It's legal.](https://i.imgur.com/Es321K1.png)

**Q: Where is the lab map coming from?**

A: The lab layouts are provided by POELab team. It may not be immediately available when the lab resets. Visit [poelab.com](poelab.com) for image versions of the layouts.

Run from Source Code
---

Install all dependencies with

    pip install -r requirement.txt

Once you have installed all the dependencies, start LabCompass with

    python main.py
