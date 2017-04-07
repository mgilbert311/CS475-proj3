Evan Carlin & Mark Gilbert
3/17/2017

This program builds upon the readyqueue in project1 and implements a priority queue with
an aging policy so that we handle the issue of starvation. Our test case is in main.c and it
did not change significantly. 

We just need to debug and the issue is that they only eat at the beginning so there must be an
issue with the locks and where they lock/unlock. One issue that I can think of is its impossible to tell which philosopher
has which lock so we might want to lock the whole eating section up but not sure about that yet.
