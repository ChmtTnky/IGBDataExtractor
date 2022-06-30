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

To view the data, use the RAD Importer plugin for Blender 3.2 (still in development).


# RAD Format Specification
The RAD format is a basic text format that is soley intended to be used by the Blender plugin as an intermediary container.

All data is in plain text and each individual value is on its own line.

Users can view and edit this data manually with a generic text editor if necessary.


Skeleton Data Format:
```
SKELETON
Bone Count
Bone Name
Bone Index
Bone Parent Index (-1 if no parent)
Bone X translation from parent
Bone Y translation from parent
Bone Z translation from parent
Bone Name
Bone Index
Bone Parent Index (-1 if no parent)
Bone X translation from parent
Bone Y translation from parent
Bone Z translation from parent
...
The bone data repeats for every bone in the model
```
