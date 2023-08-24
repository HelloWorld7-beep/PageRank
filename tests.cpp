#include "header.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

//Used code from Canvas tutorial video for catch tests
TEST_CASE("Test for no incoming", "[pagerank]") {
    //Create an instance of AdjacencyList
    AdjacencyList list;

    //Test case input data
    istringstream input("3 1\nurl1 url2\nurl1 url3\nurl2 url3\n");
    //Redirect cin to use the input here
    cin.rdbuf(input.rdbuf());

    //Use ostringstream to get the output
    ostringstream output;
    //Save the buffer?
    streambuf* coutBuffer = cout.rdbuf();
    //Redirect the cout
    cout.rdbuf(output.rdbuf());

    //Call pageRank
    list.pageRank();

    //Reset cout to the original buffer
    cout.rdbuf(coutBuffer);

    //Expected output
    string expectedOutput = "url1 0.33\nurl2 0.33\nurl3 0.33\n";

    //Compare the actual and expected output
    REQUIRE(output.str() == expectedOutput);
}

TEST_CASE("Test for one line input", "[pagerank]") {
    //Create an instance of AdjacencyList
    AdjacencyList list;

    //Test case input data
    istringstream input("1 1\nurl1 url2\n");
    //Redirect cin to use the input here
    cin.rdbuf(input.rdbuf());

    //Use ostringstream to get the output
    ostringstream output;
    //Save the buffer?
    streambuf* coutBuffer = cout.rdbuf();
    //Redirect the cout
    cout.rdbuf(output.rdbuf());

    //Call pageRank
    list.pageRank();

    //Reset cout to the original buffer
    cout.rdbuf(coutBuffer);

    //Expected output
    string expectedOutput = "url1 0.50\nurl2 0.50\n";

    //Compare the actual and expected output
    REQUIRE(output.str() == expectedOutput);
}

TEST_CASE("Test for multiple outgoing urls", "[pagerank]") {
    //Create an instance of AdjacencyList
    AdjacencyList list;

    //Test case input data
    istringstream input("3 1\nurl1 url2\nurl1 url3\nurl1 url4\n");
    //Redirect cin to use the input here
    cin.rdbuf(input.rdbuf());

    //Use ostringstream to get the output
    ostringstream output;
    //Save the buffer?
    streambuf* coutBuffer = cout.rdbuf();
    //Redirect the cout
    cout.rdbuf(output.rdbuf());

    //Call pageRank
    list.pageRank();

    //Reset cout to the original buffer
    cout.rdbuf(coutBuffer);

    //Expected output
    string expectedOutput = "url1 0.25\nurl2 0.25\nurl3 0.25\nurl4 0.25\n";

    //Compare the actual and expected output
    REQUIRE(output.str() == expectedOutput);
}

TEST_CASE("Test for multiple power iterations", "[pagerank]") {
    //Create an instance of AdjacencyList
    AdjacencyList list;

    //Test case input data
    istringstream input("5 2\nurl1 url2\nurl1 url3\nurl4 url5\nurl4 url2\nurl3 url4\n");
    //Redirect cin to use the input here
    cin.rdbuf(input.rdbuf());

    //Use ostringstream to get the output
    ostringstream output;
    //Save the buffer?
    streambuf* coutBuffer = cout.rdbuf();
    //Redirect the cout
    cout.rdbuf(output.rdbuf());

    //Call pageRank
    list.pageRank();

    //Reset cout to the original buffer
    cout.rdbuf(coutBuffer);

    //Expected output
    string expectedOutput = "url1 0.00\nurl2 0.20\nurl3 0.10\nurl4 0.20\nurl5 0.10\n";

    //Compare the actual and expected output
    REQUIRE(output.str() == expectedOutput);
}

TEST_CASE("Test for star shaped graph", "[pagerank]") {
    //Create an instance of AdjacencyList
    AdjacencyList list;

    //Test case input data
    istringstream input("4 2\nurl1 url2\nurl1 url3\nurl1 url4\nurl1 url5\n");
    //Redirect cin to use the input here
    cin.rdbuf(input.rdbuf());

    //Use ostringstream to get the output
    ostringstream output;
    //Save the buffer?
    streambuf* coutBuffer = cout.rdbuf();
    //Redirect the cout
    cout.rdbuf(output.rdbuf());

    //Call pageRank
    list.pageRank();

    //Reset cout to the original buffer
    cout.rdbuf(coutBuffer);

    //Expected output
    string expectedOutput = "url1 0.00\nurl2 0.05\nurl3 0.05\nurl4 0.05\nurl5 0.05\n";

    //Compare the actual and expected output
    REQUIRE(output.str() == expectedOutput);
}



