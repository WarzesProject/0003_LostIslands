#pragma once

class Terminal;

extern bool UserInit(Terminal *terminal);
extern void UserFrame(Terminal *terminal);
extern void UserClose(Terminal *terminal);

int terminal_open();
void terminal_close();