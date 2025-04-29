#include <catch2/catch_test_macros.hpp>

#include "vehicle.h"

TEST_CASE("empty_vehicle", "[vehicle]")
{
    Vehicle v;

    REQUIRE(v.coaches.empty());
    REQUIRE(v.route.empty());
    REQUIRE(v.reservations.empty());
    REQUIRE(v.next_stop == "");
}

TEST_CASE("add_coach", "[vehicle]")
{
    Vehicle v;
    Coach c;

    v.addCoach(c);

    REQUIRE(v.coaches.size() == 1);
    REQUIRE(v.reservations.size() == 1);
}

TEST_CASE("add_stop", "[vehicle]")
{
    Vehicle v;

    v.addStop("A");
    v.addStop("B");

    REQUIRE(v.route.size() == 2);
    REQUIRE(v.route[0] == "A");
    REQUIRE(v.route[1] == "B");
}

TEST_CASE("add_reservation", "[vehicle]")
{
    Vehicle v;
    Coach c;
    v.addCoach(c);
    v.addStop("A");
    v.addStop("B");

    Reservation r("A", "B");
    v.addReservation(0, "42", r);

    REQUIRE(v.reservations[0].size() == 1);
    REQUIRE(v.reservations[0]["42"].size() == 1);
    REQUIRE(v.reservations[0]["42"][0].from == "A");
    REQUIRE(v.reservations[0]["42"][0].to == "B");
}

TEST_CASE("add_invalid_reservation", "[vehicle]")
{
    Vehicle v;
    Coach c;
    v.addCoach(c);
    v.addStop("A");
    v.addStop("B");

    Reservation r("B", "A"); // ungültige Reservierung
    v.addReservation(0, "42", r);

    REQUIRE(v.reservations[0].size() == 0);
    REQUIRE(v.reservations[0]["42"].empty());
}

TEST_CASE("set_current_stop", "[vehicle]")
{
    Vehicle v;
    v.addStop("A");
    v.addStop("B");
    v.addStop("C");

    v.setCurrentStop(0);
    REQUIRE(v.next_stop == "A");

    v.setCurrentStop(1);
    REQUIRE(v.next_stop == "B");

    v.setCurrentStop(2);
    REQUIRE(v.next_stop == "C");

    v.setCurrentStop(3); // ungültige Position
    REQUIRE(v.next_stop == "");
}

TEST_CASE("arrive_at_stop", "[vehicle]")
{
    Coach c;
    c.addCeilingDisplay(Display());

    Vehicle v;
    v.addCoach(c);
    v.addStop("A");
    v.addStop("B");
    v.setCurrentStop(0);

    v.arriveAtStop();

    REQUIRE(v.coaches[0].ceiling_displays[0].getText() == "A");
    REQUIRE(v.next_stop == "B");
}

TEST_CASE("depart_from_stop", "[vehicle]")
{
    Coach c;
    c.addCeilingDisplay(Display());

    Vehicle v;
    v.addCoach(c);
    v.addStop("A");
    v.addStop("B");
    v.setCurrentStop(0);

    v.arriveAtStop();
    v.departFromStop();

    REQUIRE(v.coaches[0].ceiling_displays[0].getText() == "Nächster Halt: B");
    REQUIRE(v.next_stop == "B");
}
