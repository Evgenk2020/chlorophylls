#include <stdexcept>
#include "chloro.h"

chloro_data::~chloro_data() {}
chlor_allowance::~chlor_allowance() {}

class cl_a_allowance : public chloro_data
{
public:
    virtual float get_chloro(ch_data dat) const { return (float)(13.7 * dat.d665 - 5.76 * dat.d649); }
};

class cl_b_allowance : public chloro_data
{
public:
    virtual float get_chloro(ch_data dat) const { return (float)(25.8 * dat.d649 - 7.6 * dat.d665); }
};

class final_a : public chloro_data
{
private:
    cl_a_allowance _all;

public:
    virtual float get_chloro(ch_data dat) const
    {
        auto mass_n_correct = [dat]()
        { return (float)(100 / dat.mass_of_probe); };

        auto solvent_correct = [dat]()
        { return (float)(dat.vol_filtrate / 1000); };

        auto solv_index = [dat]()
        { return (float)(dat.vol_photo_probe + dat.vol_photo_alch); };

        return (float)(mass_n_correct() * solvent_correct() * _all.get_chloro(dat) * solv_index());
    }
};

class final_b : public chloro_data
{
private:
    cl_b_allowance _all;

public:
    virtual float get_chloro(ch_data dat) const
    {
        auto mass_n_correct = [dat]()
        { return (float)(100 / dat.mass_of_probe); };

        auto solvent_correct = [dat]()
        { return (float)(dat.vol_filtrate / 1000); };

        auto solv_index = [dat]()
        { return (float)(dat.vol_photo_probe + dat.vol_photo_alch); };

        return (float)(mass_n_correct() * solvent_correct() * _all.get_chloro(dat) * solv_index());
    }
};

class cl_sum : public chloro_data
{
private:
    final_a fin_a;
    final_b fin_b;

public:
    virtual float get_chloro(ch_data dat) const { return (float)(fin_a.get_chloro(dat) + fin_b.get_chloro(dat)); }
};

std::unique_ptr<chloro_data> chlor_allowance::chloro_data_get(chlor_data_type types)
{
    switch (types)
    {
    case chlor_data_type::chloro_a_allowance:
    {
        return std::make_unique<cl_a_allowance>();
    }

    case chlor_data_type::chloro_b_allowance:
    {
        return std::make_unique<cl_b_allowance>();
    }

    case chlor_data_type::chloro_a_mg:
    {
        return std::make_unique<final_a>();
    }

    case chlor_data_type::chloro_b_mg:
    {
        return std::make_unique<final_b>();
    }

    case chlor_data_type::chloro_sum:
    {
        return std::make_unique<cl_sum>();
    }

    default:
    {
        throw "Ошибка. Нет данных...";
    }
    }
}