# cerberus-2100
Based on Paul Robson's Cerberus 2080 emulator.

Updated for Cerberus-2100.

Changes:
* Pass most keys to program, including cursor keys and ESC. F10 quits the
  emulator. F12 gets back to the BIOS prompt.
* Fixed keyboard handler to use US layout.
* Updated to Cerberus-2100 hardware (colour support).
* Implemented Cerberus-2100 BIOS functionality (BIOS calls from programs,
  basicz80 and basic6502 commands).

FORTH80 and the games run. Basic65 runs (and the DEFENCE.PRG
game). Z80 BBC Basic runs, sokoz80 runs, crystalz80.bin crashes.

Known issues:
* When starting basicz80, the debug screen appears. Press F5 to exit
  the debugger, from then on, you can use BBC Basic normally. This is caused
  by a feature in the emulator, triggering a debug breakpoint on the DI
  instruction. BBC basic starts with such an instruction.
* Non-blocking sound operations not yet implemented.
* The dir command shows the last page only.
* Under Linux, the file commands are case sensitive. So if user programs
 use upper case and lower case inconsistently, it will not work.
