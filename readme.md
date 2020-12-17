## Welcome to Nemesis ##
Nemesis is a set of libraries designed to streamline the creation of time-dependent simulations common to physics and engineering applications. The sort of problems this is aimed to solve include simulating aircraft performance, rocket launches, dynamic electric fields, vibrational systems, engine controller design, and more.

The libraries are self-contained and written in C++11. They are intended to be included as needed and provide useful objects with simple interfaces so that anyone can piece together a simulation in C++. Advanced users will be able to create their own models and libraries for inclusion in their simulations.

## How Much C++ Do I Need to Know? ##
Not much.

While you certainly do '''not''' need to have a degree in computer science to use this library, you should be able to do a little more than write a "Hello, world" program. It is expected that basic users know how to include libraries, write functions, and create classes. These are not particularly advanced topics, and ample tutorials exist on the internet that can get a person up to speed within a day or two.

Advanced users should be have hands-on experience working with object-oriented programming to get the most out of the library. Creating new models, adding integration methods, and such require a thorough knowledge of the both the subjects being addressed and comfort working in C++. Note that this library uses C++11, but those familiar with earlier versions should have no issues adapting. If you are use to using C++14 or later, you may find some approaches to problems different than you are use to seeing.

## Installing Nemesis ##
To install the Nemesis Simulation Toolkit, 
1. Download the latest version of [nemesis.zip](https://github.com/humabout/Nemesis/blob/dev/nemesis-00.01.00.zip)
2. Unzip nemesis.zip to a location easily accessed by your project. If you find you cannot easily access the libraries, don't worry; you can always move it later by simply copying it to a new location.
3. Include <code>nemesis.h</code> in you project where you intend to use it. You now have access to the core Nemesis library.<br>
   3.1. If you want access to other libraries within the Nemesis Toolkit, include the associated headers. For a list of these, see [Nemesis Libraries](https://github.com/humabout/Nemesis/wiki/Nemesis-Libraries).

### Example of including Nemesis ###
```c++
// Example of including Nemesis

#include "Nemesis/nemesis.h"
```
This example assumes that the nemesis library is contained in a directory called <code>Nemesis</code> found in the same directory as the file including it.

## Additional Information ##
In addition to this introduction, a [full wiki](https://github.com/humabout/Nemesis/wiki) on this toolkit is available [here](https://github.com/humabout/Nemesis/wiki).

The [wiki](https://github.com/humabout/Nemesis/wiki) includes detailed information on every library, namespace, class, function, variable, and type in the toolkit, plus technical information on how various objects work, explainations of the physics mathematics behind them, and information on how to contribute to this project.

If you have any questions about how to use a part of the library or how anything works, the [wiki](https://github.com/humabout/Nemesis/wiki) should be your first (and, hopefully, last) stop for answers.

## What's in a name? ##
   _That which we call a rose, / By any other word would smell as sweet._

This project is named 'Nemesis' because the first time I ever encountered creating a simulation, it was for my senior capstone project. The burden of creating a flyout simulation on which my team could base and justify its design decisions fell on my shoulders, and it proved far more difficult than it looked. In fact, all the other teams tasked with the same capstone project also struggled with this task. For about three weeks, this was our nemesis.

The goal behind this library is to make creating basic simulations relatively simple affairs. Thus, the contents of this library should contain this nemesis and prevent it from harrying others. 

Also, I adore [Arch Enemy](https://www.youtube.com/watch?v=n9AcG0glVu4).
