/* ##### Autor: David Camuñas ##### */

/* C/C++ Libraries */
#include <iostream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <math.h>
#include <vector>
#include <chrono>
#include <functional>
#include <algorithm>
#include <mutex>
#include <definitions.h>

void parse_argv(int argc, char *argv[], std::string &key_space, std::string &file_path, unsigned int &key_size);
void print_title(std::string file_path);
void check_key_type(char type, std::string &key_space);
void check_key_size(std::string size_str, unsigned int &key_size);
void gen_threads_partitions(long test_size, unsigned int threads_number, unsigned int key_size, std::string key_space, std::string file_path);
void gen_keys(unsigned long start_pos, unsigned long end_pos, unsigned int key_size, std::string key_space, std::string file_path);
void get_keys_with_file(unsigned long start_pos, unsigned long end_pos, std::string key_space, std::string file_path);
void test_key(std::string file_path, std::string key);
void install_signal_handler();
void signal_handler(int signal_n);
void wait_threads();

/* Global Variables */
std::vector<std::thread> threads_vector;
bool is_rock = false, end = false;
unsigned long attempts = 1;
std::mutex sem_key;

/* MAIN FUNCTION */
int main(int argc, char *argv[])
{
    try
    {
        unsigned int threads_number, key_size = 0;
        long test_size;
        std::string key_space, file_path;

        install_signal_handler();
        parse_argv(argc, argv, key_space, file_path, key_size);
        print_title(file_path);

        /* Assign one thread per core */
        threads_number = std::thread::hardware_concurrency();

        !is_rock ? test_size = pow(key_space.length(), key_size) : test_size = count_lines(check_file(key_space));

        gen_threads_partitions(test_size, threads_number, key_size, key_space, file_path);

        wait_threads();

        std::cout << BOLD << "----------------------------------------- PROGRAM'S END ------------------------------------------------\n"
                  << RESET << std::endl;

        return EXIT_SUCCESS;
    }
    catch (const std::exception &e)
    {
        std::cerr << BOLDRED << "Error de ejecuciíon en hilo principal.\n"
                  << RESET << std::endl;
    }
}

/* Generate thread partition */
void gen_threads_partitions(long test_size, unsigned int threads_number, unsigned int key_size, std::string key_space, std::string file_path)
{
    /* Calculate keys per threads */
    int keys_per_threads, rest_keys;
    unsigned int start_pos, end_pos;
    keys_per_threads = test_size / threads_number;
    rest_keys = test_size % threads_number;

    for (unsigned int i = 0; i < threads_number; i++)
    {
        start_pos = (keys_per_threads * i);
        (i == threads_number - 1) ? end_pos = (start_pos + keys_per_threads) + rest_keys : end_pos = (start_pos + keys_per_threads - 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        !is_rock ? threads_vector.push_back(std::thread(gen_keys, start_pos, end_pos, key_size, key_space, file_path)) : threads_vector.push_back(std::thread(get_keys_with_file, start_pos, end_pos, key_space, file_path));
    }
}

/* Generate keys to test */
void gen_keys(unsigned long start_pos, unsigned long end_pos, unsigned int key_size, std::string key_space, std::string file_path)
{
    int index, n, base;
    std::string key, aux;
    base = key_space.length();

    if (start_pos < end_pos && !end)
    {
        n = start_pos;
        index = n % base;
        key = key_space[index];

        while (n >= base && !end)
        {
            n = n / base;
            index = n % base;
            key += key_space[index];
        }
        key.append((key_size - key.length()), key_space[0]);

        /* If it includes Shift --> no chain is reversed (Higher probability 1st letter Shift) */
        if (key_space != ALPHABET)
        {
            std::reverse(key.begin(), key.end());
        }

        test_key(file_path, key);
        gen_keys(start_pos + 1, end_pos, key_size, key_space, file_path);
    }
}

/* Get keys with file (rockyou.txt) */
void get_keys_with_file(unsigned long start_pos, unsigned long end_pos, std::string key_space, std::string file_path)
{
    std::string line;
    std::fstream fs;

    fs.open(key_space, std::ios::in);

    for (int i = 1; getline(fs, line) && !end; i++)
    {
        /* Thread position */
        if (i >= start_pos && i <= end_pos && !end)
        {
            test_key(file_path, line);
        }
    }
}

/* Test key at encript file */
void test_key(std::string file_path, std::string key)
{
    std::string gpg_cmd, save_cmd;
    int status;

    gpg_cmd = "gpg --batch --passphrase " + key + " --yes -d " + file_path;

    status = system(gpg_cmd.c_str());
    if (status == SUCCESS)
    {
        end = true;
        std::cout << BOLDGREEN << "[X] Intento " << attempts << " | Clave encontrada: " << key << RESET << std::endl;
    }
    attempts++;
}

/* Check command line */
void parse_argv(int argc, char *argv[], std::string &key_space, std::string &file_path, unsigned int &key_size)
{
    switch (argc)
    {
    case ARGC_NUMBER:
        check_key_type(argv[4][0], key_space);
        break;

    case ARGC_NUMBER - 2:
        key_space = ALPHANUMERICS;
        if (argv[2][0] == 'f')
        {
            key_space = argv[2];
            is_rock = 1;
        }
        break;

    default:
        std::cout << BOLDRED << "[X] ERROR, formato de comando incorrecto.\n"
                  << RESET << RED << "\tFormatos:\n\t\t[X] ./gpg-cracker --len <n> --charset <char_type> <file.gpg>\n\t\t[X] ./gpg-cracker --len <n> <file.gpg>\n\t\t[X] ./gpg-cracker --charset <charset_file> <file.gpg>\n"
                  << RESET << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!is_rock)
    {
        check_key_size((argv[2]), key_size);
    }
    file_path = open_file(argv[argc - 1]);
}

/* Check key type */
void check_key_type(char type, std::string &key_space)
{
    switch (type)
    {
    case 'l':
        key_space = ALPHABET;
        break;

    case 'm':
        key_space = ALPHABET_MINUS;
        break;

    case 'd':
        key_space = DIGITS;
        break;

    case 'a':
        key_space = ALPHANUMERICS;
        break;

    default:
        std::cout << "[X] ERROR, '" << type << "' no es un tipo de clave válido\n\tOpciones: 'characters' | 'numbers' | 'alphanumerics'\n"
                  << std::endl;
        exit(EXIT_FAILURE);
    }
}

/* Check key size */
void check_key_size(std::string size_str, unsigned int &key_size)
{
    if (!is_integer(size_str))
    {
        std::cout << BOLDRED << "[X] ERROR. El argumento --len '" << size_str << "' no es un número entero.\n"
                  << RESET << std::endl;
        exit(EXIT_FAILURE);
    }

    key_size = stoi(size_str);
}

/* Wait the threads finalize */
void wait_threads()
{
    std::for_each(threads_vector.begin(), threads_vector.end(), std::mem_fn(&std::thread::join));
}

/* Print the program title */
void print_title(std::string file_path)
{
    std::cout << "-------------------------------------------------------------------------------------------------------\n"
              << std::endl;
    std::cout << BOLD << "[X] Obteniendo clave archivo [" << file_path << "]...\n"
              << RESET << std::endl;
}


