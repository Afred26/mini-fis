#include "coach.h"

#include <iostream>

Coach::Coach()
{
}

void Coach::addCeilingDisplay(Display const& display)
{
    ceiling_displays.push_back(display);
}

void Coach::addSeatDisplay(std::string const& seatId, Display const& display)
{
    seat_displays.insert({seatId, display});
}

void Coach::updateCeilingDisplays(std::string const& newText)
{
    for (Display &el : ceiling_displays ){
        el.text = newText;
    }
}

void Coach::updateSeatDisplay(std::string const& seatId, std::string const& newText)
{
    if (seat_displays.count(seatId) == 1){
       seat_displays.at(seatId).text = newText;
    }
    
}

void Coach::showCeilingDisplays() const
{
    // TODO
}

void Coach::showSeatDisplays() const
{
    // TODO
}

void Coach::showAllDisplays() const
{
    // TODO
}
