#!/bin/bash
# script for capturing image and compressing it
# Author: Mukta Darekar

# This is a text string which will be searched within the recieved socket file
SEARCHSTR=capture

# This is a directory and file where socket data is present
SEARCHDIR=/tmp/socket-data

y=0

#while [ 1 ]
#do 

    echo "Waiting for Capture command"

    # Check if file exists or not
    if [ -f "$SEARCHDIR" ] 
    then

        while [ $y == 0 ]
        do
            # Number of lines matching with given string in this file
            y=$(grep -i "$SEARCHSTR" "$SEARCHDIR" | wc -l)
        done

        y=0

        echo "Capture command found"
        echo "       " > /tmp/socket-data

        cd /usr/bin

        echo "Capturing greyscale image"
        ./capture

        cd ../../var

        echo "Compressing image"
        mogrify -format jpg test.pgm

        cd ..
    fi

#done

#end
