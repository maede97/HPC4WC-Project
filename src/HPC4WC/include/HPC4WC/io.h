#pragma once
#include <HPC4WC/field.h>

#include <iostream>

// ArgsParser
#include <flags.h>

namespace HPC4WC {

class IO {
public:
    /**
     * @brief Write a field to a stream.
     * @param[inout] stream The stream to which the file should be written (can be std::cout, or i.e. std::ofstream)
     * @param[in] field The field to write.
     * @param[in] k The last index of the field, which means this writes only a i-j-plane.
     */
    static void write(std::ostream& stream, const Field& field, Field::const_idx_t& k);

    /**
     * @brief Write the full field to a stream.
     * 
     * It will be written as a continuous array, where the i-j-planes are stacked.
     * @param[inout] stream The stream to which the file should be written (can be std::cout, or i.e. std::ofstream)
     * @param[in] field The field to write.
     */
    static void write(std::ostream& stream, const Field& field);
};

/**
 * @brief Simple Argument parser.
 * 
 * Wrapper around https://github.com/sailormoon/flags.
 * 
 * @todo Write about default arguments. (and config arguments)
 */
class ArgsParser {
public:
    /**
     * @brief Initialize the argument parser with the number of arguments and all given arguments.
     * @param[in] argc Number of entries in argv
     * @param[in] argv Array of arguments.
     * @param[in] default_args If true, also adds the configuration parameters (block_i etc.), default true.
     */
    ArgsParser(int argc, char* argv[], bool default_args=true);

    /**
     * @brief Default deconstructor
     */
    ~ArgsParser() {}

    /**
     * @brief Add an optional bool argument to the parser.
     * 
     * The default value is the value the variable result currently has.
     * @param[inout] result In: Default value, out: new value if the argument has been specified.
     * @param[in] argument The argument to search for.
     * @param[in] Helper string for the help display.
     */
    void add_argument(bool& result, const char* argument, const char* help);

    /**
     * @brief Add an optional Field::idx_t argument to the parser.
     * 
     * The default value is the value the variable result currently has.
     * @param[inout] result In: Default value, out: new value if the argument has been specified.
     * @param[in] argument The argument to search for.
     * @param[in] Helper string for the help display.
     */
    void add_argument(Field::idx_t& result, const char* argument, const char* help);

    /**
     * @brief Add an optional Field::idx_t argument to the parser.
     * 
     * The default value is the value the variable result currently has.
     * @param[inout] result In: Default value, out: new value if the argument has been specified.
     * @param[in] argument The argument to search for.
     * @param[in] Helper string for the help display.
     */
    void add_argument(std::string& result, const char* argument, const char* help);

    /**
     * @brief Checker to see if an executable should show the help.
     * @return True, if the help data should be shown.
     */
    bool help() const;
    
    /**
     * @brief Write the help menu to the stream provided.
     * @param[inout] stream Where to write the help data.
     */
    void help(std::ostream& stream) const;

private:
    flags::args m_args; ///< internal argument parser

    const char* m_argv_0; ///< the name of the program, used inside help()

    std::vector<std::array<std::string, 3>> m_arguments; ///< user defined arguments
    std::vector<std::array<std::string, 3>> m_config_entries; ///< config arguments (block_i etc.)
};
}  // namespace HPC4WC