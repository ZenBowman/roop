Functions
=========

To execute any of the examples, open up the roop REPL and run the sequence of commands specified for the example.

### load
Loads an image from a file - example:
```
(load images/foo.jpg)
```

### set
Sets the value of a variable to an image. 
As an example:
```
(set foo (load images/foo.jpg))
```
Sets the value of foo to the image in foo.jpg

### display
Displays the value of the last result. As an example:
```
(load images/foo.jpg)
(display)
```
Will show the foo.jpg image in a new window.

