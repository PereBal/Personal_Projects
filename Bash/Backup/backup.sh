#!/usr/bin/bash

# This version only works with folders DIRECTLY under /home/$user, which means you can not 
# try to compress a /home/$user/Desktop/folder, just /home/$user/Desktop instead. 
# I'll fix this flaw when I have some time to.

function helpf {
  echo "Usage: $0 [username] [params]"
  echo -e "Params:"
  echo "-f list-of-folders/files-to-bck"
  echo "-u username"
  exit
}

function exef {
  usr=$1
  if [ "$2" != "" ]; then
    # if the sed expression is "enquoted", $usr isn't evaluated and
    # ... bum!
    bckfolders="$(echo $2 | sed s:/home/$usr/::g)"
  else
    bckfolders="$(ls /home/$usr | grep -v /home/$usr/Backups | tr '\n' ' ' | sed -e 's://* : :g' -e 's://*$::g')"
  fi

  if [ $(whoami) != $usr ]; then
    su $usr -c "bash ./bck_exef.sh $usr $bckfolders"
  else
    ./bck_exef.sh $usr "$bckfolders"
  fi
}

if [ $# -gt 1 ]; then
  bckfolders=""
  usr=$1
  while [ $# -gt 0 ]
  do
    case $1 in
      "-f")
        shift
        while [[ $# -gt 0 && $1 != "-u" && $1 != "-h" ]]
        do
          bckfolders="$bckfolders $(echo $1 | sed 's://*$::g')"
          shift
        done
        ;;
      "-u")
        shift
        usr=$1
        shift
        ;;
      "-h")
        helpf
        ;;
      *) shift
        ;;
    esac
  done
  if [ $usr == "-f" ]; then
    helpf
  fi
  exef $usr $bckfolders
elif [ $# -eq 1 ]; then
  usr=$1
  exef $usr 
else
  helpf
fi
