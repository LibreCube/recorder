#include "game.h"
void sayteam(char *text) { conoutf(CON_TEAMCHAT, "%s:\f1 %s", colorname(player1), text); addmsg(SV_SAYTEAM, "rcs", player1, text); }
