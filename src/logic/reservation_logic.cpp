

#include "reservation_logic.h"

void insert_reservation(Reservation const &reservation, std::vector<Reservation> &reservations, std::vector<std::string> const &stops)
{
    if (valid_reservation(reservation, stops))
    {
        auto pos = reservations.begin();
        for (int i = 0; i < reservations.size(); i++)
        {

            if (is_first(reservation, reservations.at(i), stops))
            {
                reservations.insert(pos + i, reservation);
                return;
            }
        }
        reservations.push_back(reservation);
    }
}

Reservation get_next_reservation(std::vector<Reservation> const &reservations, std::string const &next_stop, std::vector<std::string> const &stops)
{
    for (Reservation el : reservations)
    {
        if (el.from == next_stop)
        {
            return el;
        }
        else if (el.to == next_stop)
        {
            return el;
        }
    }
    for (int i = 0; i < stops.size(); i++)
    {
        if (stops.at(i) == next_stop)
        {
            return get_next_reservation(reservations, stops.at(i - 1), stops);
        }
    }

    return Reservation();
}

bool is_valid_for_route(Reservation const &reservation, std::vector<std::string> const &stops)
{

    return valid_reservation(reservation, stops);
}

bool is_first(Reservation const &reservation1, Reservation const &reservation2, std::vector<std::string> const &stops)
{
    for (int i = 0; i < stops.size(); i++)
    {
        if (reservation1.from == stops.at(i))
        {
            return true;
        }
        else if (reservation2.from == stops.at(i))
        {
            return false;
        }
    }
    return false;
}

bool valid_reservation(Reservation const &reservation, std::vector<std::string> const &stops)

{
    bool result = false;
    for (std::string el : stops)
    {
        if (result || el == reservation.from)
        {
            result = true;
            if (el == reservation.to)
            {
                return true;
            }
        }
    }
    return false;
}