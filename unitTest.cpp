#define CATCH_CONFIG_MAIN 
#include "catch.hpp" 
#include "UTrelloInterface.hpp"
#include <stdexcept> 
#include <string> 

TEST_CASE("check estimated time", "")
{
    UTrelloInterface test;

    SECTION("estimated time")
    {
        test.addUser("minoo");
        test.addUser("sara");

        test.addList("Code");

        test.addTask("Code", "Do everything better", 3, 1, "Write the whole code");
        test.addTask("Code", "Do Everything", 11, 1, "Write the whole code");
        test.addTask("Code", "Destroy code formatting", 1, 2, "Write the whole code");

        test.assignTask("Destroy code formatting", "minoo");
        test.assignTask("Do everything better", "sara");
        CHECK(test.printTotalEstimatedTime() == 4);
    }

}

TEST_CASE("check remaining time", "")
{
    UTrelloInterface test;

    SECTION("remained time")
    {
        test.addUser("minoo");
        test.addUser("sara");

        test.addList("Code");

        test.addTask("Code", "Do everything better", 2, 1, "Write the whole code");
        test.addTask("Code", "Do Everything", 3, 1, "Write the whole code");
        test.addTask("Code", "Destroy code formatting", 1, 2, "Write the whole code");
       
        test.assignTask("Do everything better", "minoo");
        test.completeTask("Do everything better");
        test.assignTask("Destroy code formatting", "minoo");
        test.assignTask("Do everything better", "sara");
        CHECK(test.printTotalRemainingTime() == 4);
    }

     
}

TEST_CASE("check users workload", "")
{
    UTrelloInterface test;

    SECTION("workload")
    {
        test.addUser("minoo");

        test.addList("Code");

        test.addTask("Code", "Do everything better", 2, 1, "Write the whole code");
        test.addTask("Code", "Do Everything", 3, 1, "Write the whole code");

        test.assignTask("Do Everything", "minoo");
        test.assignTask("Do everything better", "minoo");

        CHECK(test.printUserWorkload("minoo") == 5);
    }

}