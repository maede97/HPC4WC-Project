#include <HPC4WC/config.h>
#include <HPC4WC/io.h>

#ifdef _WIN32
#define PATH_CHAR "\\"
#else
#define PATH_CHAR "/"
#endif
#define PARSE_EXE_NAME(name) \
    std::string(name).substr(std::string(name).find_last_of(PATH_CHAR) + 1, std::string(name).size() - std::string(name).find_last_of(PATH_CHAR) - 1)

namespace HPC4WC {

void IO::write(std::ostream& out, const Field& field, Field::const_idx_t& k) {
    using const_idx_t = Field::const_idx_t;
    const_idx_t num_halo = field.num_halo();
    for (Field::idx_t i = 0; i < field.num_i(); i++) {
        for (Field::idx_t j = 0; j < field.num_j(); j++) {
            out << field(i + num_halo, j + num_halo, k) << " ";
        }
        out << std::endl;
    }
}

void IO::write(std::ostream& out, const Field& field) {
    for (Field::idx_t k = 0; k < field.num_k(); k++) {
        write(out, field, k);
    }
}

ArgsParser::ArgsParser(int argc, char* argv[]) : m_args(argc, argv), m_argv_0(argv[0]) {
    // Add config entries here.
    m_arguments.push_back({"help", "Shows this help.", "false"});

    m_config_entries.push_back({"block-i", "Perform i-blocking.", Config::BLOCK_I ? "true" : "false"});
    m_config_entries.push_back({"block-j", "Perform j-blocking.", Config::BLOCK_J ? "true" : "false"});
    m_config_entries.push_back({"openmp-num-threads", "How many threads should be used for OpenMP.", std::to_string(Config::OPENMP_NUM_THREADS)});
    m_config_entries.push_back({"blocking-size-i", "How big the block should be, i direction.", std::to_string(Config::BLOCK_SIZE_I)});
    m_config_entries.push_back({"blocking-size-j", "How big the block should be, j direction.", std::to_string(Config::BLOCK_SIZE_J)});

    Config::BLOCK_I = m_args.get<bool>("block-i").value_or(Config::BLOCK_I);
    Config::BLOCK_J = m_args.get<bool>("block-j").value_or(Config::BLOCK_J);
    Config::OPENMP_NUM_THREADS = m_args.get<Field::idx_t>("openmp-num-threads").value_or(Config::OPENMP_NUM_THREADS);
    Config::BLOCK_SIZE_I = m_args.get<Field::idx_t>("blocking-size-i").value_or(Config::BLOCK_SIZE_I);
    Config::BLOCK_SIZE_J = m_args.get<Field::idx_t>("blocking-size-j").value_or(Config::BLOCK_SIZE_J);
}

bool ArgsParser::help() const {
    return m_args.get<bool>("help", false);
}

void ArgsParser::help(std::ostream& stream) const {
    stream << PARSE_EXE_NAME(m_argv_0);
    for (auto& tr : m_arguments) {
        stream << " [--" << std::get<0>(tr) << "=" << std::get<2>(tr) << "]";
    }
    stream << std::endl;
    for (auto& tr : m_arguments) {
        stream << "  --" << std::get<0>(tr) << "  " << std::get<1>(tr) << " (default: " << std::get<2>(tr) << ")" << std::endl;
    }

    stream << std::endl;
    std::cout << "Further Configurations:" << std::endl;
    for (auto& tr : m_config_entries) {
        stream << "  --" << std::get<0>(tr) << "  " << std::get<1>(tr) << " (default: " << std::get<2>(tr) << ")" << std::endl;
    }
}

void ArgsParser::add_argument(Field::idx_t& result, const char* argument, const char* help) {
    m_arguments.push_back({argument, help, std::to_string(result)});
    result = m_args.get<Field::idx_t>(argument).value_or(result);
}

void ArgsParser::add_argument(bool& result, const char* argument, const char* help) {
    m_arguments.push_back({argument, help, result ? "true" : "false"});
    result = m_args.get<Field::idx_t>(argument).value_or(result);
}

}  // namespace HPC4WC