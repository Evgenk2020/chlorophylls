#include <iostream>
#include <fstream>
#include <locale>
#include "output.h"

general_info::~general_info() {}

void help_info::see_info()
{
    std::cout << "*** Визначенні концентрації хлорофілів ***" << std::endl
              << std::endl
              << "Для виводу в термінал" << std::endl
              << "chloro -d [наважка_г] [фільтарт_мл] [фотометрична_проба_мл] [фотометричний_розчинник_мл] [фотометр_665] [фотометр_649]" << std::endl
              << "Для виводу в файл" << std::endl
              << "chloro -d [наважка_г] [фільтарт_мл] [фотометрична_проба_мл] [фотометричний_розчинник_мл] [фотометр_665] [фотометр_649]" << std::endl
              << "Для виводу довідки" << std::endl
              << "chloro [-h|--help]" << std::endl
              << "Додаткова інформація" << std::endl
              << "chloro -i" << std::endl;
}

void inf_indo::see_info()
{
    std::cout << "Концентрації хлорофілів a і b в розчинах визначають відповідно величинам екстинкції, виміряних за двох довжин хвиль" << std::endl
              << std::endl
              << "Формули для розчинів хлорофілу в 96% етанолі" << std::endl
              << "концентрація хлорофіла а (мг/мл) = 13.7 * D665 - 5.76 * D649" << std::endl
              << "концентрація хлорофіла b (мг/мл) = 25.8 * D649 - 7.6 * D665" << std::endl;
}

//--------------------------------------------------

data_info::~data_info() {}

void screen_info::see_info(ch_data *dat)
{
    chlor_allowance allow;

    std::cout << "Концентрація хлорофілу А: "
              << allow.chloro_data_get(allow.chloro_a_allowance)->get_chloro(*dat) << " мг/мл" << std::endl;

    std::cout << "Концентрація хлорофілу B: "
              << allow.chloro_data_get(allow.chloro_b_allowance)->get_chloro(*dat) << " мг/мл" << std::endl;

    std::cout << "Вміст хлорофілу А: "
              << allow.chloro_data_get(allow.chloro_a_mg)->get_chloro(*dat) << " мг/100 г" << std::endl;

    std::cout << "Вміст хлорофілу B: "
              << allow.chloro_data_get(allow.chloro_b_mg)->get_chloro(*dat) << " мг/100 г" << std::endl;

    std::cout << "Сума хлорофілів А + B: "
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

    writer << "Концентрація хлорофілу А:" << coma
           << quo << allow.chloro_data_get(allow.chloro_a_allowance)->get_chloro(*dat) << quo << coma << quo << "мг/мл" << quo << std::endl;

    writer << "Концентрація хлорофілу B:" << coma
           << quo << allow.chloro_data_get(allow.chloro_b_allowance)->get_chloro(*dat) << quo << coma << quo << "мг/мл" << quo << std::endl;

    writer << "Вміст хлорофілу А:" << coma
           << quo << allow.chloro_data_get(allow.chloro_a_mg)->get_chloro(*dat) << quo << coma << quo << "мг/100 г" << quo << std::endl;

    writer << "Вміст хлорофілу B:" << coma
           << quo << allow.chloro_data_get(allow.chloro_b_mg)->get_chloro(*dat) << quo << coma << quo << "мг/100 г" << quo << std::endl;

    writer << "Сума хлорофілів А + B:" << coma
           << quo << allow.chloro_data_get(allow.chloro_sum)->get_chloro(*dat) << quo << coma << quo << "мг/100 г" << quo << std::endl;
    writer << "" << std::endl;

    std::cout << "Дані додані у файл chlor-dada.csv" << std::endl;
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
