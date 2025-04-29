#include "coach.h"

#include <iostream>

Coach::Coach()
{
}

void Coach::addCeilingDisplay(Display const &display)
{
    ceiling_displays.push_back(display);
}

void Coach::addSeatDisplay(std::string const &seatId, Display const &display)
{
    seat_displays.insert({seatId, display});
}

void Coach::updateCeilingDisplays(std::string const &newText)
{
    for (Display &el : ceiling_displays)
    {
        el.updateText(newText);
    }
}

void Coach::updateSeatDisplay(std::string const &seatId, std::string const &newText)
{
    if (seat_displays.count(seatId) == 1)
    {
        seat_displays.at(seatId).text = newText;
    }
}

void Coach::showCeilingDisplays() const
{
    for (Display el : ceiling_displays)
    {
        el.show();
    }
}

void Coach::showSeatDisplays() const
{
    for (const auto &[id, display] : seat_displays)
    {
        std::cout << id << ": ";
        display.show();
    }
}

void Coach::showAllDisplays() const
{
    showCeilingDisplays();
    showSeatDisplays();
}
