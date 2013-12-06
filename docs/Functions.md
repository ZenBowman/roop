Functions
=========

To execute any of the examples, open up the roop REPL and run the sequence of commands specified for the example.

### load
Loads an image from a file. The sole argument is the filename containing the image.
For example:
```
(load images/foo.jpg)
```

### set
Sets the value of a variable to an image. The first argument is the name of the new image, the second is the image itself.
For example:
```
(set foo (load images/foo.jpg))
```
Sets the value of foo to the image in foo.jpg

### display
Displays the value of the last result. 
For example:
```
(load images/foo.jpg)
(display)
```
Will show the foo.jpg image in a new window.

### subtract
Subtracts one image from another. The first argument is the original image, the second is the image to subtract.
For example:
```
(subtract coins penny)
```
Subtracts one image from another.

![Coins](http://www.psamtani.net/pictures/subtraction.jpg)

### save
Saves an image to a file. The first argument is the image, the second is the filename.
For example:
```
(save (subtract coins penny) images/coins-minus-penny.jpg)
```
