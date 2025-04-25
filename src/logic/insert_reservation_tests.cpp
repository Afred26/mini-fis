#include <catch2/catch_test_macros.hpp>

#include "reservation_logic.h"

TEST_CASE("insert_in_order", "[insert_reservation]")
{
    std::vector<Reservation> reservations;

    std::vector<std::string> stops = {"A", "B", "C", "D", "E"};
    Reservation r1{"A", "B"};
    Reservation r2{"B", "C"};
    Reservation r3{"C", "D"};

    insert_reservation(r1, reservations, stops);
    REQUIRE(reservations.size() == 1);
    REQUIRE(reservations[0].from == "A");
    REQUIRE(reservations[0].to == "B");

    insert_reservation(r2, reservations, stops);
    REQUIRE(reservations.size() == 2);
    REQUIRE(reservations[0].from == "A");
    REQUIRE(reservations[0].to == "B");
    REQUIRE(reservations[1].from == "B");
    REQUIRE(reservations[1].to == "C");

    insert_reservation(r3, reservations, stops);
    REQUIRE(reservations.size() == 3);
    REQUIRE(reservations[0].from == "A");
    REQUIRE(reservations[0].to == "B");
    REQUIRE(reservations[1].from == "B");
    REQUIRE(reservations[1].to == "C");
    REQUIRE(reservations[2].from == "C");
    REQUIRE(reservations[2].to == "D");
}

TEST_CASE("insert_out_of_order", "[insert_reservation]")
{
    std::vector<Reservation> reservations;

    std::vector<std::string> stops = {"A", "B", "C", "D", "E"};
    Reservation r1{"A", "B"};
    Reservation r2{"B", "C"};
    Reservation r3{"C", "D"};

    insert_reservation(r3, reservations, stops);
    REQUIRE(reservations.size() == 1);
    REQUIRE(reservations[0].from == "C");
    REQUIRE(reservations[0].to == "D");

    insert_reservation(r2, reservations, stops);
    REQUIRE(reservations.size() == 2);
    REQUIRE(reservations[0].from == "B");
    REQUIRE(reservations[0].to == "C");
    REQUIRE(reservations[1].from == "C");
    REQUIRE(reservations[1].to == "D");

    insert_reservation(r1, reservations, stops);
    REQUIRE(reservations.size() == 3);
    REQUIRE(reservations[0].from == "A");
    REQUIRE(reservations[0].to == "B");
    REQUIRE(reservations[1].from == "B");
    REQUIRE(reservations[1].to == "C");
    REQUIRE(reservations[2].from == "C");
    REQUIRE(reservations[2].to == "D");
}

TEST_CASE("insert_invalid", "[insert_reservation]")
{
    std::vector<Reservation> reservations;

    std::vector<std::string> stops = {"A", "B", "C", "D", "E"};
    Reservation r1{"A", "F"}; // Ungültiger Zielort
    Reservation r2{"F", "A"}; // Ungültiger Abfahrtsort
    Reservation r3{"D", "C"}; // Falsche Reihenfolge

    insert_reservation(r1, reservations, stops);
    REQUIRE(reservations.size() == 0);

    insert_reservation(r2, reservations, stops);
    REQUIRE(reservations.size() == 0);

    insert_reservation(r3, reservations, stops);
    REQUIRE(reservations.size() == 0);
}
