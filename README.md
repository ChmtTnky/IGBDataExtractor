# IGBDataExtractor
A program that uses the Alchemy 5.0 SDK to extract data from an IGB file and export it into a format that can be imported into Blender.

This program was made for the Dokapon Kingdom community (https://discord.gg/9P4DqYxVm6) to expand its modding capabilities, though it can theoretically work on IGB files from other Alchemy based games.

Games tested on so far: Dokapon Kingdom, Project Diva

DO NOT ASK FOR ACCESS TO THE SDK

# Instructions
Either drag-and-drop an IGB onto the executable or run the executable with the command line.

If run through the command line, one can specify extra flags to specify which parts of the IGB are to be extracted and whether to separate them into individual files.

To view all available flags, run the executable without any arguments through the command line.

The final output should be an RAD file containing the extracted data.

To view the data, use the RAD Importer plugin for Blender 3.2 (https://github.com/ChmtTnky/RADImporter).

# RAD Format Specification
The RAD format is a binary data format containing blocks of data indentifiable by a 4 byte ID string before a given block of data.

The data is written in binary to ensure that the output matches the original data from the IGB as closely as possible.

Skeleton Data Format:
```
4 byte ID String: SKEL
Int32: Bone Count

Char8: Length of Bone Name String
? Byte String: Bone Name
Int32: Bone Index
Int32: Bone Parent Index (-1 if no parent)
Float32: Bone X translation from parent
Float32: Bone Y translation from parent
Float32: Bone Z translation from parent

Char8: Length of Bone Name String
? Byte String: Bone Name
Int32: Bone Index
Int32: Bone Parent Index (-1 if no parent)
Float32: Bone X translation from parent
Float32: Bone Y translation from parent
Float32: Bone Z translation from parent
...
The bone data repeats for every bone in the model
```
