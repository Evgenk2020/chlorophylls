#include <iostream>
#include "chloro.h"

void help();
void info();
void data_run(ch_data data_temp);

int main(int argc, char *argv[])
{
    const std::string k_help_one = "-h";
    const std::string k_help_two = "--help";
    const std::string k_info = "-i";
    const std::string k_data = "-d";
    std::string similar;

    if (argc >= 2)
    {
        similar = (std::string)argv[1];
    }

    if (argc == 2)
    {
        if (similar == k_help_one || similar == k_help_two)
        {
            help();
        }

        if (similar == k_info)
        {
            info();
        }
    }

    else if (argc == 8 && similar == k_data)
    {
        ch_data datas;

        datas.mass_of_probe = atof(argv[2]);
        datas.vol_filtrate = atof(argv[3]);
        datas.vol_photo_probe = atof(argv[4]);
        datas.vol_photo_alch = atof(argv[5]);
        datas.d665 = atof(argv[6]);
        datas.d649 = atof(argv[7]);

        data_run(datas);
    }

    else
    {
        std::cout << "error... use -h or --help for details" << std::endl;
    }

    return 0;
}

void data_run(ch_data data_temp)
{
    chlor_allowance allow;

    std::cout << "Концентрация хлорофилла А: "
              << allow.chloro_data_get(allow.chloro_a_allowance)->get_chloro(data_temp) << " мг/мл" << std::endl;

    std::cout << "Концентрация хлорофилла B: "
              << allow.chloro_data_get(allow.chloro_b_allowance)->get_chloro(data_temp) << " мг/мл" << std::endl;

    std::cout << "Содержание хлорофилла А: "
              << allow.chloro_data_get(allow.chloro_a_mg)->get_chloro(data_temp) << " мг/100 г" << std::endl;

    std::cout << "Содержание хлорофилла B: "
              << allow.chloro_data_get(allow.chloro_b_mg)->get_chloro(data_temp) << " мг/100 г" << std::endl;

    std::cout << "Сумма хлорофиллов А + B: "
              << allow.chloro_data_get(allow.chloro_sum)->get_chloro(data_temp) << " мг/100 г" << std::endl;
}

void help()
{
    std::cout << "*** Определение концентрации хлорофиллов ***" << std::endl
              << std::endl
              << "Использование: " << std::endl
              << "chloro -d [навеска г] [фильтрат мл] [проба для фотометрии мл] [растворитель для фотометрии мл] [спектрофотометр 665] [спектрофотометр 649]" << std::endl
              << "chloro [-h|--help] для вызова справки" << std::endl
              << "chloro -i для просмотра дополнительной информации" << std::endl;
}

void info()
{
    std::cout << "Концентрации хлорофиллов a и b в растворах определяют по значениям экстинкции, измеренным при двух длинах волн." << std::endl
              << "Формулы для растворов хлорофилла в 96%-ном этаноле" << std::endl
              << "концентрация хлорофилла а (мг/мл) = 13.7 * D665 - 5.76 * D649" << std::endl
              << "концентрация хлорофилла а (мг/мл) = 25.8 * D649 - 7.6 * D665" << std::endl;
}