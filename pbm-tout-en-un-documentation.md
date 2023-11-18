# Documentation for pbm-tout-en-un-documentaion
This file operates with PBM images and contains these functions:
- [Documentation for pbm-tout-en-un-documentaion](#documentation-for-pbm-tout-en-un-documentaion)
  - [lirePBM](#lirepbm)
    - [Example:](#example)
  - [ecrirePBM](#ecrirepbm)
    - [Example:](#example-1)
  - [affichePBM](#affichepbm)
    - [Example:](#example-2)
  - [inversePBM](#inversepbm)
    - [Example:](#example-3)

In order to compile and execute c++ file you can use execute.sh script.
For example: `./execute.sh pbm-tout-en-un` will compile and execute the file pbm-tout-en-un.cpp.

## lirePBM
`ImageNB lirePBM(string source)`

The function reads a file (by the path given to the argument) and returns an array.
### Example:
For the file:
```
P1
# CREATOR: GIMP PNM Filter Version 1.1
10 10
0 0 0 1 1 1 1 0 0 0 0 0 1 0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 1 0
1 0 0 1 0 0 1 0 0 1 1 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 1
1 0 0 1 0 0 1 0 0 1 0 1 0 0 1 1 0 0 1 0 0 0 1 0 0 0 0 1 0 0
0 0 0 1 1 1 1 0 0 0
```

We get a vector:
```c++
{
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, },
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, },
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, },
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, },
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, },
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, },
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, }
}
```

## ecrirePBM
`void ecrirePBM(ImageNB img, string cible)`

The function gets a vector of vectors of ints, and a path to create a new file or to write to an existing one.

### Example:
If we give a vector:
```c++
{
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, },
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, },
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, },
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, },
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, },
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, },
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, }
}
```
and a path: `"./pbm/smiley.pbm"`

The function will create a file smiley.pbm in the directory pbm:
```
P1
# CREATOR: GIMP PNM Filter Version 1.1
10 10
0 0 0 1 1 1 1 0 0 0 0 0 1 0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 1 0
1 0 0 1 0 0 1 0 0 1 1 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 1
1 0 0 1 0 0 1 0 0 1 0 1 0 0 1 1 0 0 1 0 0 0 1 0 0 0 0 1 0 0
0 0 0 1 1 1 1 0 0 0
```
## affichePBM
`void affichePBM(ImageNB img)`

The function prints to the command line a kind of image.
It prints @ if we get 1 in a vector and ' ' if we get 0.

### Example:
If we give a vector like that:
```c++
{
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, },
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, },
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, },
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, },
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, },
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, },
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, }
}
```

The function will print that:
```
      @ @ @ @       
    @         @     
  @             @   
@     @     @     @ 
@                 @ 
@                 @ 
@     @     @     @ 
  @     @ @     @   
    @         @     
      @ @ @ @       
```


## inversePBM
`ImageNB inversePBM(ImageNB img)`

The function gets a vector of vectors of ints and changes 0's to 1's and change 1's to 0's.

### Example:
If we give this vector:
```c++
{
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, },
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, },
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, },
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, },
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, },
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, },
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, }
}
```

The function will return this vector:
```c++
{
{1, 1, 1, 0, 0, 0, 0, 1, 1, 1, },
{1, 1, 0, 1, 1, 1, 1, 0, 1, 1, },
{1, 0, 1, 1, 1, 1, 1, 1, 0, 1, },
{0, 1, 1, 0, 1, 1, 0, 1, 1, 0, },
{0, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
{0, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
{0, 1, 1, 0, 1, 1, 0, 1, 1, 0, },
{1, 0, 1, 1, 0, 0, 1, 1, 0, 1, },
{1, 1, 0, 1, 1, 1, 1, 0, 1, 1, },
{1, 1, 1, 0, 0, 0, 0, 1, 1, 1, },
}
```