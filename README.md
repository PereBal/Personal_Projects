# Personal_Projects
My little secret diary but with code. As soon as I finish a new *relevant* project, I'll upload it here

## C
These are my *relevant* C projects. Most of them don't have a practical use, I've made them just for fun or in order to learn something.

### Calc
A simple calculator implemented with a Lexical analyzer and recursive descent parser to process and evaluate the user's input.

### MazeGenerator
An implementation of a randomized version of Prim's minimal spanning tree algorithm (src: https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_Prim.27s_algorithm).

## Bash
A bunch of lazy user oriented bash scripts.

### Backup.sh
Guess what? is a script to make a backup of:
  1. All folders under /home/$user (yes, you can choose which user using the **-u** option)
  2. Some folders under /home/$user especyfied via: 
     >-f folder1 .. folderN

One must say it's not fully developed so any kind of attempt like
  >-f /home/$user/Desktop/folder
will **NOT** work. Instead you have to
  >-f /home/$user/Desktop
I'm sorry about it, but I'll take care of that flaw later on.
