Functions
=========

To execute any of the examples, open up the roop REPL and run the sequence of commands specified for the example.

### load
Loads an image from a file.

#### Arguments:
- arg1: image name

For example:
```
(load images/foo.jpg)
```

### set
Sets the value of a variable to an image. 

#### Arguments:
- arg1: image name
- arg2: image

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
Subtracts one image from another. 

#### Arguments:
- arg1: source image
- arg2: destination image

For example:
```
(subtract coins penny)
```
Subtracts one image from another.

![Coins](http://psamtani.net/pictures/coins.jpg)

### save 
Saves an image to a file, based on the extension.

#### Arguments:
- arg1: image
- arg2: filename (relative path)

For example:
```
(save (subtract coins penny) images/coins-without-penny.jpg
```

### resize
Resizes an image. 

#### Arguments:
- arg1: image
- arg2: New size, in pixels.
