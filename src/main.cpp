#define IG_GFX_DX

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "IncludeAll.h"

using namespace Gap;

bool WriteSkeleton(igString, igBool);

int main(int argc, char* argv[])
{
    // Initialize Alchemy and IGB data types
    igAlchemy alchemy;
    Sg::igArkRegisterForIGBFiles();

    igBool split = false;

    // Process command-line arguments
    if (argc < 2) // If there are no arguments, display a description of all acceptable arguments and flags
    {
        std::cout <<
            "\nArguments: <input_file> <flags>\n\n" <<
            "Flags:\n" <<
            "--split: Split different types of data into individual output files\n";
        return -1;
    }
    else if (argc >= 3) // If there is more than one argument, check for flags
    {
        std::string current;
        for (int i = 0; i < argc; i++)
        {
            current = argv[i];
            if (current == "--split")
                split = true;
        }
    }

    // Delete output file if it already exists
    std::string filename = argv[1];
    filename += "-Output.rad";
    std::fstream output;
    output.open(filename, std::fstream::in);
    if (output && !split)
    {
        output.close();
        output.open(filename, std::fstream::out);
        output.close();
    }

    WriteSkeleton(argv[1], split);
}

bool WriteSkeleton(igString igb_file, igBool split)
{
    // Check if input file is valid
    if (!igIGBResource->load(igb_file))
    {
        std::cout << "\nSkeleton: Could not load IGB\n";
        return false;
    }

    // Get animation database from IGB
    igAnimationDatabaseRef animDB = igAnimationDatabase::dynamicCast(igIGBResource->getInfoByType(igb_file, "igAnimationDatabase"));
    igIGBResource->unload(igb_file);

    // Prepare skeleton data for extraction
    igSkeletonRef skeleton = animDB->getSkeleton(0);
    igAnimationCombinerRef combiner = igAnimationCombiner::_instantiateRef();
    combiner->configure(skeleton);
    combiner->setBindPose(-1);

    // If --split was set, append the data type to the end of the file name insted of using the default output name
    std::fstream output;
    std::string output_path = igb_file;
    if (!split)
    {
        std::string append = "-Output.rad"; // Default
        output_path += append;
        output.open(output_path, std::fstream::out | std::ofstream::app);
    }
    else
    {
        std::string append = "-Output-Skeleton.rad"; // Add the name of the data type to the file name
        output_path += append;
        output.open(output_path, std::fstream::out);
    }

    // Get necessary skeleton data and output to file
    output << "SKELETON" << std::endl;                    // Data identifier
    output << skeleton->getBoneCount() << std::endl;        // Bone count
    for (igInt i = 0; i < skeleton->getBoneCount(); i++)
    {
        output << skeleton->getBoneName(i) << std::endl;    // Bone name
        output << i << std::endl;                           // Bone index
        output << skeleton->getParent(i) << std::endl;      // Bone parent index
        for (igInt j = 0; j < 3; j++)                       // Bone tail location relative to parent head (x, y, z)
            output << std::setprecision(7) << (*skeleton->getBoneTranslation(i))[j] << std::endl;
    }
    output.close();

    // Output success message
    std::cout << "\nSkeleton: Skeleton data successfully written to " + output_path + "\n";
    return true;
}