/* ##### Autor: David Camuñas ##### */

#include <iostream>
#include <string>
#include <fstream>
#include <signal.h>

/* Constant definitions */
#define ALPHABET            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ"
#define DIGITS              "0123456789"
#define ALPHANUMERICS       "abcdefghijklmnñopqrstuvwxyz0123456789"
#define ALPHABET_MINUS      "abcdefghijklmnñopqrstuvwxyz"
#define SUCCESS             0
#define ARGC_NUMBER         6


/* ------------------------------------------------------------------------------ */

/* Functions */

/*Check integer number*/
bool is_integer(std::string var)
{
    try
    {
        std::stoi(var);
    }
    catch(const std::exception& e)
    {
        return false;
    }
    
    return true;
}

/*Open file and return path*/
std::string open_file(std::string file)
{
    std::ifstream fs;

    /*Generate the full file_path_*/
    fs.open(file, std::ios::binary);

    if (!fs.is_open())
    {
        std::cout << "[X] Error opening file '" << file << "'" << std::endl;
        exit(EXIT_FAILURE);
    }

    fs.close();
    return file;
}

/*Open file and return path*/
std::string check_file(std::string file)
{
    std::ifstream fs;

    /*Generate the full file_path_*/
    fs.open(file, std::ios::binary);

    if (!fs.is_open())
    {
        std::cout << "[X] Error opening file '" << file << "'" << std::endl;
        exit(EXIT_FAILURE);
    }

    fs.close();
    return file;
}

/*Count file's total lines*/
int count_lines(std::string file)
{
    int lines;
    std::ifstream file_r;
    std::string line = "";

    file_r.open(file, std::ios::binary);

    for (lines = 0; !file_r.eof(); lines++)
    {
        std::getline(file_r, line);
    }

    file_r.close();
    return lines;
}

/* Main thread's signal handler */
void signal_handler(int signal_n)
{
    exit(EXIT_SUCCESS);
    std::cout << "\n----------------------------------------- PROGRAM'S END ------------------------------------------------\n\n"
              << std::endl;
}

/* Install main thread's signal handler */
void install_signal_handler()
{
    if (signal(SIGINT, signal_handler) == SIG_ERR)
    {
        std::cerr << "[X] Error al instalar el manejador de señal." << std::endl;
        exit(EXIT_FAILURE);
    }
}


/* ------------------------------------------------------------------------------ */

/* Colors */
#define RESET       "\033[0m"              /* Default */
#define BLACK       "\033[30m"             /* Black */
#define RED         "\033[31m"             /* Red */
#define GREEN       "\033[32m"             /* Green */
#define YELLOW      "\033[33m"             /* Yellow */
#define BLUE        "\033[34m"             /* Blue */
#define MAGENTA     "\033[35m"             /* Magenta */
#define CYAN        "\033[36m"             /* Cyan */
#define WHITE       "\033[37m"             /* White */
#define BOLD        "\033[1m"              /* Bold */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

/* Get in: https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c */