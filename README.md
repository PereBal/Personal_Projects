# Personal_Projects
My little secret diary but with code. As soon as I finish a new *relevant* project, I'll upload it here

## Index
1. [C](https://github.com/PereBal/Personal_Projects#c)
  1. [Calc](https://github.com/PereBal/Personal_Projects#calc)
  2. [MazeGenerator](https://github.com/PereBal/Personal_Projects#mazegenerator)
2. [Bash](https://github.com/PereBal/Personal_Projects#bash)
  1. [Backup](https://github.com/PereBal/Personal_Projects#backup)
3. [Python](https://github.com/PereBal/Personal_Projects#python)
  1. [Chat-App](https://github.com/PereBal/Personal_Projects#chat-app)

## C
These are my *relevant* C projects. Most of them don't have a practical use, I've made them just for fun or in order to learn something.

### Calc
A simple calculator implemented with a Lexical analyzer and recursive descent parser to process and evaluate the user's input.

#### Instalation
1. Go to the folder

>**cd** path_to_folder

2. Execute the makefile

>**make**

### MazeGenerator
An implementation of a randomized version of Prim's minimal spanning tree algorithm (src: https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_Prim.27s_algorithm).

#### Instalation
The same as with Calc


## Bash
A bunch of lazy user oriented bash scripts.

### Backup
Guess what? it's a script to make a backup of:
  1. All folders under /home/$user (yes, you can choose which user using the **-u** option)
  2. Some folders under /home/$user specified via: 

     >-f folder1 .. folderN

One must say it's not fully developed so any kind of attempt like
  
  >-f /home/$user/Desktop/folder

will **NOT** work. Instead you have to

  >-f /home/$user/Desktop

I'm sorry about that, but I'll take care of that flaw later on (I promise).

#### Instalation
1. Go to the folder where* backup.sh* is stored
>**cd** path_to_folder

2. Make both scripts executable
>**chmod u+x** *backup.sh* *bck_exef.sh*

3. Execute backup.sh and enjoy? (right now it's necessary to have both scripts on the same folder)
>*./backup.sh* user \[-f folder {folder}\] 

## Python
The things I do with *Python 3*...

### Chat-App
Just a little chat application using [socket](https://docs.python.org/3/library/socket.html) and [multiprocessing](https://docs.python.org/3.3/library/multiprocessing.html) (with a [Manager](https://docs.python.org/3.3/library/multiprocessing.html#sharing-state-between-processes) to share users info). It isn't fully tested and the code it's kind of horrible but, I'll get on those details later

#### Instalation
1. Install Python from [here](https://www.python.org/downloads/) or from your distribution repository (under Linux)

2. Go to the *Chat-App* folder
>**cd** path_to_folder

3. Start the server (stop it with Ctrl + C)
>**python** *server.py*

4. Start as many client instances as you want & enjoy?
>**python** *client.py*
