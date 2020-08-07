# What is it
It is console game *tic-tac-toe*.\
It is my solution for one problem.

# How 2 use
## You play for 'X'
At first, you must compile with `$ make O` (because your opponent is playing for 'O').

Then you must run it `./O`

Input:\
In 3 rows and 3 colums you must print a field after your move.\
Note, that you must input only possible fields!\
`X` - is cell with 'X', `O` - is cell with 'O' and `.` - is empty cell.\
For example:
```
..X
...
...
```
Output:\
Output is modified field after your opponent's move.\
For example:
```
..X
.O.
...
```
## You play for 'O'
**Note, that 'X' make first move!**\
At first, you must compile with `$ make X` (because your opponent is playing for 'X').

Then you must run it `$ ./X`

Input:\
In 3 rows and 3 colums you must print a field after your move.\
Note, that you must input only possible fields!\
`X` - is cell with 'X', `O` - is cell with 'O' and `.` - is empty cell.\
For example:
```
...
...
...
```
Output:\
Output is modified field after your opponent's move.\
For example:
```
...
.X.
...
```
# Why you won't win
The algorithm is based on *Retroanalysis algorithm* for games on graphs. If algorithm can win, it wins.
