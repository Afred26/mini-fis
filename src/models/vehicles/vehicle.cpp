#include "vehicle.h"
#include <iostream>

Vehicle::Vehicle()
    : next_stop("")
{
}

void Vehicle::addCoach(Coach const &coach)
{
    coaches.push_back(coach);
    std::unordered_map<std::string, std::vector<Reservation>> new_res;
    reservations.push_back(new_res);
}

void Vehicle::addStop(std::string const &stop)
{
    route.push_back(stop);
}

void Vehicle::addReservation(size_t coachIndex, std::string const &seatId, Reservation const &reservation)
{
    if (valid_reservation(reservation, route))
    {
        std::vector<Reservation> res = {reservation};
        if (reservations.at(coachIndex).find(seatId) == reservations.at(coachIndex).end())
        {
            reservations[coachIndex].insert({seatId, res});
        }
        else
        {
            reservations.at(coachIndex).at(seatId).push_back(reservation);
        }
    }
}

void Vehicle::showAllDisplays() const
{
    for (Coach el : coaches)
    {
        el.showAllDisplays();
    }
}

void Vehicle::showAllReservations() const
{
    for (const auto &res : reservations)
    {
        for (const auto &[id, res1] : res)
        {
            std::cout << "An Sitzplatz " + id + " sind " << res1.size() << " Reservationen" << std::endl;
            std::cout << "Die Reservationen sind:" << std::endl;
            for (const auto &res2 : res1)
            {
                std::cout << res2.from + " -> " + res2.to << std::endl;
            }
        }
    }
}

void Vehicle::setCurrentStop(size_t pos)
{
    if (route.size() > pos)
    {
        next_stop = route.at(pos);
    }
    else
    {
        next_stop = "";
    }
}

void Vehicle::arriveAtStop()
{
    for (Coach &el : coaches)
    {
        el.updateCeilingDisplays(next_stop);
    }
    int curent_stop;
    for (int i = 0; i < route.size(); i++)
    {
        if (route.at(i) == next_stop)
        {
            curent_stop = i;
        }
    }
    setCurrentStop(curent_stop + 1);
    updateSeatDisplays();
}

void Vehicle::departFromStop()
{
    for (auto &coach : coaches)
    {
        coach.updateCeilingDisplays("Nächster Halt: " + next_stop);
    }
}

void Vehicle::updateSeatDisplays()
{
    for (size_t i = 0; i < coaches.size(); ++i)
    {
        auto &coach = coaches[i];
        for (const auto &[seatId, reservations] : reservations[i])
        {
            auto reservation = get_next_reservation(reservations, next_stop, route);
            if (!reservation.isEmpty())
            {
                coach.updateSeatDisplay(seatId, reservation.getDisplayText());
            }
        }
    }
}