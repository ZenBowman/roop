Functions
=========

To execute any of the examples, open up the roop REPL and run the sequence of commands specified for the example.

### load
Loads an image from a file.

#### Arguments:
- arg1: image name

#### Example:
```
(load images/foo.jpg)
```

### set
Binds the value of an image to a name. Once a name has been bound, rebinding it is not permitted (i.e. you cannot set the value of the same name more than once).

#### Arguments:
- arg1: image name
- arg2: image

#### Example:
```
(set foo (load images/foo.jpg))
```
Sets the value of foo to the image in foo.jpg

### get
Gets an image from a named value (the value must have been set beforehand using set).

#### Arguments
- arg1: name of image

#### Example
````
(get foo)
````

Get is called implicitly if the name is used, in most cases you do not need to call it explicitly.

### display
Displays the value of the last result. 

#### Example
```
(load images/foo.jpg)
(display)
```
Will show the foo.jpg image in a new window. When you use the display command, the CLI will stop accepting commands unless you click on the new image and press any key.

### subtract
Subtracts one image from another. 

#### Arguments
- arg1: source image
- arg2: destination image

#### Example
```
(subtract coins penny)
```
Subtracts one image from another.

![Coins](http://psamtani.net/pictures/coins.jpg)

### save 
Saves an image to a file, based on the extension.

#### Arguments
- arg1: image
- arg2: filename (relative path)

#### Example
```
(save (subtract coins penny) images/coins-without-penny.jpg
```

### resize
Resizes an image. 

#### Arguments
- arg1: image
- arg2: New width, in pixels
- arg3: New height, in pixels (optional: If a third argument is not provided, roop assumes that you want to resize to a square image and uses the value of arg2 for both the width and height).

#### Examplex
````
(resize coins 1024 768)
````
