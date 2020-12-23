# VR-Attention-Overlay

A small application that can be executed to show an image overlay in VR to warn the user that the real world demands attention.

**This is a work in progress**

## Use cases:
* A button is connected to an Arduino connected to a PC and a Windows service listens on the serial port and executes this program whenever the button is pressed.
* Windows Task Scheduler executes this program whenever a task is triggered.
* Microsoft Outlook executes this program whenever the calendar shows a reminder (unsure how, possibly VBA code needed).

## TODO 

* Allow relative image paths.
* Add code comments.
* Add support for multiple images.
* Add config file (so a user can set position, timing etc.)
