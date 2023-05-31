#ifndef CHLORO_H
#define CHLORO_H

#include <memory>

struct ch_data
{
    float mass_of_probe, vol_filtrate, vol_photo_probe, vol_photo_alch, d665, d649;
};

class chloro_data
{
public:
    virtual float get_chloro(ch_data dat) const = 0;
    ~chloro_data();
};

class chlor_allowance
{
private:
    ch_data _ch_data;

public:
    enum chlor_data_type
    {
        chloro_a_allowance,
        chloro_b_allowance,
        chloro_a_mg,
        chloro_b_mg,
        chloro_sum
    };

    static std::unique_ptr<chloro_data> chloro_data_get(chlor_data_type types);
    ~chlor_allowance();
};

#endif // CHLORO_H