#include "game.h"
#include "engine.h"

namespace game
{
    bool profileloaded = false;
    string curprofile;
}

static string profilelist =           "profiles/list.cfg";

void createprofile(const char *name)
{
    defformatstring(profiledir   )("SauerEnhanced/profiles/%s",             name);
    defformatstring(videodir     )("SauerEnhanced/profiles/%s/videos",      name);
    defformatstring(screenshotdir)("SauerEnhanced/profiles/%s/screenshots", name);
    defformatstring(demodir      )("SauerEnhanced/profiles/%s/demos",       name);

    path(profilelist  );
    path(profiledir   );
    path(videodir     );
    path(screenshotdir);
    path(demodir      );

    createdir(profiledir);
    createdir(videodir);
    createdir(screenshotdir);
    createdir(demodir);

    stream *f = openfile(profilelist, "a");
    if(!f)
	{
		conoutf("Error while creating/opening profile list file.");
		return;
	}
	f->printf("%s\n", name);
	f->close();

    copystring(game::curprofile, name);
    filtertext(game::player1->name, name, false, MAXNAMELEN);
    writecfg();
    execfile(game::savedconfig());
    game::profileloaded = true;
}

string profiles;
int numprofiles = 0;

void readprofilelist()
{
    char buf[32];
    stream *f = openfile(profilelist, "r");
    while(f->getline(buf, sizeof(buf)))
    {
        formatstring(profiles)("%s %s", profiles, buf);
    }
    f->close();
}

void readprofilenum()
{
    char buf[32];
    stream *f = openfile(profilelist, "r");
    if(!f)
    {
        numprofiles = 0;
    }
    else
    {
        while(f->getline(buf, sizeof(buf)))
        {
            numprofiles++;
        }
        f->close();
    }
}

void readprofile(const char *name)
{
    copystring(game::curprofile, name);
    execfile(game::savedconfig());
    game::profileloaded = true;
}

COMMAND(createprofile, "s");
COMMAND(readprofile, "s");
ICOMMAND(getprofiles, "", (), { readprofilelist(); result(profiles); copystring(profiles, ""); } );
ICOMMAND(getprofilenum, "", (), { readprofilenum(); intret(numprofiles); numprofiles = 0; } );
