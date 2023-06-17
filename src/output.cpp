#include <iostream>
#include <fstream>
#include <locale>
#include "output.h"

general_info::~general_info() {}

void help_info::see_info()
{
    std::cout << "*** Определение концентрации хлорофиллов ***" << std::endl
              << std::endl
              << "Для вывода в терминал" << std::endl
              << "chloro -d [навеска г] [фильтрат мл] [проба для фотометрии мл] [растворитель для фотометрии мл] [спектрофотометр 665] [спектрофотометр 649]" << std::endl
              << "Для вывода в файл" << std::endl
              << "chloro -df [навеска г] [фильтрат мл] [проба для фотометрии мл] [растворитель для фотометрии мл] [спектрофотометр 665] [спектрофотометр 649]" << std::endl
              << "Для вывода справки" << std::endl
              << "chloro [-h|--help]" << std::endl
              << "Для просмотра дополнительной информации" << std::endl
              << "chloro -i" << std::endl;
}

void inf_indo::see_info()
{
    std::cout << "Концентрации хлорофиллов a и b в растворах определяют по значениям экстинкции, измеренным при двух длинах волн." << std::endl
              << "Формулы для растворов хлорофилла в 96%-ном этаноле" << std::endl
              << "концентрация хлорофилла а (мг/мл) = 13.7 * D665 - 5.76 * D649" << std::endl
              << "концентрация хлорофилла а (мг/мл) = 25.8 * D649 - 7.6 * D665" << std::endl;
}

//--------------------------------------------------

data_info::~data_info() {}

void screen_info::see_info(ch_data *dat)
{
    chlor_allowance allow;

    std::cout << "Концентрация хлорофилла А: "
              << allow.chloro_data_get(allow.chloro_a_allowance)->get_chloro(*dat) << " мг/мл" << std::endl;

    std::cout << "Концентрация хлорофилла B: "
              << allow.chloro_data_get(allow.chloro_b_allowance)->get_chloro(*dat) << " мг/мл" << std::endl;

    std::cout << "Содержание хлорофилла А: "
              << allow.chloro_data_get(allow.chloro_a_mg)->get_chloro(*dat) << " мг/100 г" << std::endl;

    std::cout << "Содержание хлорофилла B: "
              << allow.chloro_data_get(allow.chloro_b_mg)->get_chloro(*dat) << " мг/100 г" << std::endl;

    std::cout << "Сумма хлорофиллов А + B: "
              << allow.chloro_data_get(allow.chloro_sum)->get_chloro(*dat) << " мг/100 г" << std::endl;
}

void file_info::see_info(ch_data *dat)
{
    std::ofstream writer("chlor-dada.csv", std::ios::app);

    const char coma = ',';
    const char quo = '\"';

    std::locale m_loc("uk_UA.utf8");
    writer.imbue(m_loc);

    chlor_allowance allow;

    writer << "Концентрация хлорофилла А:" << coma
           << quo << allow.chloro_data_get(allow.chloro_a_allowance)->get_chloro(*dat) << quo << coma << quo << "мг/мл" << quo << std::endl;

    writer << "Концентрация хлорофилла B:" << coma
           << quo << allow.chloro_data_get(allow.chloro_b_allowance)->get_chloro(*dat) << quo << coma << quo << "мг/мл" << quo << std::endl;

    writer << "Содержание хлорофилла А:" << coma
           << quo << allow.chloro_data_get(allow.chloro_a_mg)->get_chloro(*dat) << quo << coma << quo << "мг/100 г" << quo << std::endl;

    writer << "Содержание хлорофилла B:" << coma
           << quo << allow.chloro_data_get(allow.chloro_b_mg)->get_chloro(*dat) << quo << coma << quo << "мг/100 г" << quo << std::endl;

    writer << "Сумма хлорофиллов А + B:" << coma
           << quo << allow.chloro_data_get(allow.chloro_sum)->get_chloro(*dat) << quo << coma << quo << "мг/100 г" << quo << std::endl;
    writer << "" << std::endl;

    std::cout << "Данные добавлены в файл chlor-dada.csv" << std::endl;
}

//--------------------------------------------------

print_info::print_info(general_info *temp) : g_info(temp) {}
print_info::print_info(data_info *temp) : d_info(temp) {}

void print_info::_print() { g_info->see_info(); }
void print_info::_print(ch_data temp) { d_info->see_info(&temp); }

print_info::~print_info()
{
    delete g_info;
    g_info = nullptr;

    delete d_info;
    d_info = nullptr;
}
