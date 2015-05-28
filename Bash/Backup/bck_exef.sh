#!/usr/bin/bash -x

usr=$(whoami)
if [ $usr != $1 ]; then
  exit -1
fi

bckfolders=$2

src_path=/home/$usr
dest_path=$src_path/Backups
dst=_home_$usr$(date +%d-%m-%Y_%H%M%S)


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
tar -cf "./$dst.tar" "./$dst"
rm -rf "./$dst"

cd $current_path
exit 0
