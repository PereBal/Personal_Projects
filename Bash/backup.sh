#!/usr/bin/bash

# This version only works with folders DIRECTLY under /home/$user, which means you can not 
# try to compress a /home/$user/Desktop/folder, just /home/$user/Desktop instead. 
# I'll fix this flaw when I have some time to.

function help_f {
  echo "Usage: $0 [username] [params]"
  echo -e "Params:"
  echo "-f list-of-folders/files-to-bck"
  echo "-u username"
}

who="$(whoami)"

bckfolders=""
if [ $# -gt 1 ]; then
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
        help_f
        exit;
        ;;
      *) shift
        ;;
    esac
  done
  if [ $usr == "-f" ]; then
    help_f
    exit
  fi
  if [ $bckfolders == ""]; then
    bckfolders=$(ls /home/$usr | grep -v /home/$usr/Backups | tr '\n' ' ' | sed 's://*\|//*$::g')
  fi
elif [ $# -eq 1]; then
  usr=$1
  bckfolders=$(ls /home/$usr | grep -v /home/$usr/Backups | tr '\n' ' ' | sed 's://*\|//*$::g')
else
  help_f
  exit
fi

src_path=/home/$usr
dest_path=$src_path/Backups
dst=_home_$usr$(date +%d-%m-%Y)

if [[ $who != $usr ]]; then
  echo "$usr, you can only backup your own home folder!"
  exit
fi

# Create Backup/year/month/_home_$usrdd-mm-YYYY folder structure
if [ ! -d "$dest_path" ]; then
  mkdir $dest_path
fi

dest_path=$dest_path/$(date +%Y)
if [ ! -d $dest_path ]; then
  mkdir $dest_path
fi

dest_path=$dest_path/$(date +%m)
if [ ! -d $dest_path ]; then
  mkdir $dest_path
fi

if [ ! -d $dest_path/$dst ]; then
  mkdir $dest_path/$dst
fi

# For each element to backup under /home/$usr
current_path="$(pwd)"
cd $src_path
for elem in $bckfolders
do
    echo "Backing up '$elem'"
    # if is a file
    # copy it to a special folder to compress it later
    # with other "unfoldered" files.
    if [ -f "$elem" ]; then
      if [ ! -d $dest_path/$dst/others ]; then
        mkdir $dest_path/$dst/others
      fi
      cp -f "$elem" $dest_path/$dst/others
    else 
      if [ ! -f $dest_path/$dst/$elem.tar.gz ]; then
        tar -czf "$dest_path/$dst/$elem.tar.gz" "./$elem" 
      else
        echo "File ./$elem.tar.gz already exists, overwrite? [y/N]:"
        read -r res
        if [[ "$res" == "y" || "$res" == "Y" ]]; then
          rm "./$elem.tar.gz" 
          tar -czf "./$elem.tar.gz" "$src_path/$elem" 1> /dev/null 
        fi
      fi
    fi
done

cd $dest_path/$dst
# Compress & remove auxiliar folder 'others'
if [[ -d ./others && ! -f ./others.tar.gz ]]; then
  tar -czf ./others.tar.gz ./others 
elif [ -d ./others ]; then
  echo "File ./others.tar.gz already exists, overwrite? [y/N]:"
  read -r res
  if [[ "$res" == "y" || "$res" == "Y" ]]; then
    rm ./others.tar.gz 
    tar -czf ./others.tar.gz ./others 1> /dev/null 
  fi
fi
rm -rf "./others"

cd ..
# Compress & remove auxiliar folder '$dst'
# Just 'tared' it to speed up.
tar -cf $dst.tar $dst
rm -rf $dst

cd $current_path
