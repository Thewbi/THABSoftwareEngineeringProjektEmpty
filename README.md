# THABSoftwareEngineeringProjektEmpty
THABSoftwareEngineeringProjekt (from empty project)

## Introduction

This application reads in .csv files containing positions, one position per row.
Sample input files are contained in the folder KUKAGenerator\KUKAGenerator\resources.

The data is then converted into a KUKA KRL script (file extension is .src) that 
can be used to operate a KUKA robot. For testing the FIREBRAND simulator is used 
to execute the KUKA KRL scripts.

## Compiling

The application is create for Visual Studio Community version 2022 (64-bit), Version 17.9.6.
There is a solution file (KUKAGenerator\KUKAGenerator.sln) that should be opened to 
open all files in Visual Studio Community.

Currently a 32bit library (glut) is used to render a graphical representation of the 
data points. Therefore, currently only the 32-bit configuration will successfully compile.
In Visual Studio Community, make sure that you select Debug x86 or Release x86.
(Do not use Debug x64 or Release x64).

## Running the Application

In order to run the application, copy the file KUKAGenerator\glut-3.7.6-bin\glut32.dll to the 
folder C:\Windows\SysWOW64.

Sample input files are contained in the folder KUKAGenerator\KUKAGenerator\resources. Use one
of the .csv files.

## Implementation

The main.c file contains the main entry point.

First instances are created, in the second part of the main() function, the instances are
used to run the application. The application is split into individual process steps.

The steps read the input from the file, filter the input. The most important step executes
the Douglas Peucker algorithm on the filtered input data.

The velocity is computed and euler angles are computed. Finally the data that the Douglas
Peucker algorithm has not deleted is written into the KUKA KRL output file.
