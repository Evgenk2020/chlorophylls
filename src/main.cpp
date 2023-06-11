#include <iostream>
#include "output.h"

int main(int argc, char *argv[])
{
    const std::string k_help_one = "-h";
    const std::string k_help_two = "--help";
    const std::string k_info = "-i";
    const std::string k_data = "-d";
    const std::string k_file = "-df";
    std::string similar;

    if (argc >= 2)
    {
        similar = (std::string)argv[1];
    }

    if (argc == 2)
    {
        if (similar == k_help_one || similar == k_help_two)
        {
            print_info inf(new help_info);
            inf._print();
        }

        if (similar == k_info)
        {
            print_info inf(new inf_indo);
            inf._print();
        }
    }

    else if (argc == 8 && similar == k_data || argc == 8 && similar == k_file)
    {
        ch_data datas;

        datas.mass_of_probe = atof(argv[2]);
        datas.vol_filtrate = atof(argv[3]);
        datas.vol_photo_probe = atof(argv[4]);
        datas.vol_photo_alch = atof(argv[5]);
        datas.d665 = atof(argv[6]);
        datas.d649 = atof(argv[7]);

        if (similar == k_data)
        {
            print_info inf(new screen_info);
            inf._print(datas);
        }

        if (similar == k_file)
        {
            print_info inf(new file_info);
            inf._print(datas);
        }
    }

    else
    {
        std::cout << "error... use -h or --help for details" << std::endl;
    }

    return 0;
}