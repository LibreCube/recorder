#loop through the all the .dmo files in demos/ and for each of them, start up sauer, record the demo, and then quit

#command to start sauer from inside sauer root directory:
# ./bin_unix/native_client -q/home/isaac/.sauerbraten

#how to specify which player to spec??

demosdir="/var/local/$(whoami)/demos"
pushd "$demosdir" >/dev/null
#for demo in $(ls *.dmo | cut -d'.' -f1); do

demo="$1"
player="$2"
    
    #start sauer
    pushd /home/$(whoami)/sauerbraten

    #write out CS script
    echo "Creating CS script ${demosdir}/record.cfg"
    echo "//generated by ../renderdemos.sh
        demo ${demo}
        pausegame 1
        goto ${player}
        moview 1280
        movieh 720
        moviefps 30
        name 'eS|TV
        movieaccel 0
        pausegame 0
        sleep 100 [ movie ${demo}; clearconsole;
        ];
        sleep 609000 [ showscores; movie; //would be nice to display the scoreboard every time the player dies or event happens Perhaps mod to the client??
        sleep 100 [ quit;
        ];
        ];" > record.cfg

    sauerconout="${demosdir}/../sauerconout.log"
    echo "Rendering demo ${demo} with pov from ${player}..."
    ./bin_unix/native_client -g${sauerconout} -x"exec record.cfg" -q${demosdir} >& ${demosdir}/../sauerbraten-recent.log && echo "Demo rendering completed!" || echo "Unexpected failure while rendering demo, check /var/local/$(whoami)/sauerbraten.log"

    #back to var/local/usr/demos
    popd
    
    mv ${demo} "../done"
    

#done

popd