#include <iostream>
#include <fstream>
using namespace std;
#include "LSystem.hpp"
#include "Production.hpp"
#include "LSystemFunctions.hpp"
#include <catch.hpp>

TEST_CASE("Test Validity Productions"){
    unordered_set<char> alphabet = {'F', '[', ']', '+', '-'};
    char predecessor1 = 'F';
    char predecessor2 = 'X';
    vector<char> successor1 = {'F', '[', '+', 'F', ']', '-', 'F'};
    vector<char> successor2 = {'F', '+', 'F', '-', 'F'};
    Production<char> production1 = Production<char>(predecessor1, successor1);
    Production<char> production2 = Production<char>(predecessor2, successor2);
    CHECK(isValidProduction(production1, alphabet));
    CHECK(!isValidProduction(production2, alphabet));
}

TEST_CASE("Test LSystem Constructor"){
    unordered_set<char> alphabet = {'F', 'X', '[', ']', '+', '-'};
    vector<char> axiom = {'X'};
    char predecessor1 = 'X';
    char predecessor2 = 'F';
    vector<char> successor1 = {'F', '+', '[', '[', 'X', ']', '-', 'X', ']', '-', 'F', '[', '-', 'F', 'X', ']', '+', 'X'};
    vector<char> successor2 = {'F', 'F'};
    Production<char> production1 = Production<char>(predecessor1, successor1);
    Production<char> production2 = Production<char>(predecessor2, successor2);
    unordered_set<Production<char>> productions = {production1, production2};
    LSystemInterpreter<char> LSystem = LSystemInterpreter<char>(alphabet, axiom, productions);
}

TEST_CASE("2 Iterations And Reset Test"){
    unordered_set<char> alphabet = {'A', 'B'};
    vector<char> axiom = {'A', 'B', 'A'};
    char predecessor1 = 'A';
    char predecessor2 = 'B';
    vector<char> successor1 = {'A', 'B'};
    vector<char> successor2 = {'A'};
    Production<char> production1 = Production<char>(predecessor1, successor1);
    Production<char> production2 = Production<char>(predecessor2, successor2);
    unordered_set<Production<char>> productions = {production1, production2};
    LSystemInterpreter<char> LSystem = LSystemInterpreter<char>(alphabet, axiom, productions);
    // Vector of results at iteration1 -> index 0, iteration2 -> index 1, ...
    vector<vector<char>> Actual_Result(2); // 2 iterations so a vector of size 2
    const vector<char> Expected_Result1 = {'A', 'B', 'A', 'A', 'B'};
    const vector<char> Expected_Result2 = {'A', 'B', 'A', 'A', 'B', 'A', 'B', 'A'};
    // Update the LSystem and the Actual_Result
    generate(Actual_Result.begin(), Actual_Result.end(), LSystem);
    // Compare results after one iteration
    CHECK(Expected_Result1 == Actual_Result[0]);
    // Compare results after 2 iterations
    CHECK(Expected_Result2 == Actual_Result[1]);
    // Reset the LSystem
    LSystem.reset();
    // After reset the LSystem.getInternal_state() should be equal to the axiom
    CHECK(axiom == LSystem.getInternal_state());
}

TEST_CASE("If A Symbol In Alphabet Has No Production"){
    unordered_set<char> alphabet = {'A', '+', 'B'};
    vector<char> axiom = {'A', '+', 'B', 'A'};
    char predecessor1 = 'A';
    char predecessor2 = 'B';
    vector<char> successor1 = {'A', 'B'};
    vector<char> successor2 = {'A'};
    Production<char> production1 = Production<char>(predecessor1, successor1);
    Production<char> production2 = Production<char>(predecessor2, successor2);
    unordered_set<Production<char>> productions = {production1, production2};
    LSystemInterpreter<char> LSystem = LSystemInterpreter<char>(alphabet, axiom, productions);
    vector<vector<char>> Actual_Result(1);
    const vector<char> Expected_Result = {'A', 'B', '+', 'A', 'A', 'B'};
    // Update the LSystem and the Actual_Result
    generate(Actual_Result.begin(), Actual_Result.end(), LSystem);
    // Compare results after one iteration
    CHECK(Expected_Result == Actual_Result[0]);
}

// First test to draw a plant
TEST_CASE("Drawing Fractal Plant") {
    ofstream outputfile("C:\\Data\\CLion\\Datastructuren\\MiniProject\\LSystemDrawer\\txt\\lsystem_firstplant.txt");
    unordered_set<string> alphabet = {"F", "X", "+", "-", "[", "]"};
    vector<string> axiom = {"X"};
    string predecessor1 = "X";
    string predecessor2 = "F";
    vector<string> successor1 = {"F", "+", "[", "[", "X", "]", "-", "X", "]", "-", "F", "[", "-", "F", "X", "]", "+","X"};
    vector<string> successor2 = {"F", "F"};
    Production<string> production1 = Production<string>(predecessor1, successor1);
    Production<string> production2 = Production<string>(predecessor2, successor2);
    unordered_set<Production<string>> productions = {production1, production2};
    LSystemInterpreter<string> LSystem = LSystemInterpreter<string>(alphabet, axiom, productions);
    vector<vector<string>> outputs(6);
    generate(outputs.begin(), outputs.end(), LSystem);
    for (const auto &symbol: outputs[5]) {
        outputfile << symbol << " ";
    }
    outputfile.close();
}

// These plants and trees I'm going to use for the treecollage that im drawing with python turtle
TEST_CASE("Drawing Multiple Plants") {
    ofstream outputfile1("C:\\Data\\CLion\\Datastructuren\\MiniProject\\LSystemDrawer\\txt\\lsystem_output1.txt"); // plant on the left side
    ofstream outputfile2("C:\\Data\\CLion\\Datastructuren\\MiniProject\\LSystemDrawer\\txt\\lsystem_output2.txt"); // Tree
    ofstream outputfile3("C:\\Data\\CLion\\Datastructuren\\MiniProject\\LSystemDrawer\\txt\\lsystem_output3.txt"); // plant rotated so it can go on the right side
    unordered_set<string> alphabet = {"F", "X", "+", "-", "[", "]"};
    vector<string> axiom = {"X"};
    string predecessor1 = "X";
    string predecessor2 = "F";
    vector<string> successor11 = {"F", "+", "[", "[", "X", "]", "-", "X", "]", "-", "F", "[", "-", "F", "X", "]", "+","X"};
    vector<string> successor12 = {"F", "F"};
    vector<string> successor21 = {"F", "[", "+", "X", "]", "[", "-", "X", "]", "F", "X"};
    vector<string> successor22 = {"F", "F"};
    vector<string> successor31 = {"F", "-", "[", "[", "X", "]", "+", "X", "]", "+", "F", "[", "+", "F", "X", "]", "-","X"}; // same as successor11 but every + -> - and every - -> +
    vector<string> successor32 = {"F", "F"};
    Production<string> production11 = Production<string>(predecessor1, successor11);
    Production<string> production12 = Production<string>(predecessor2, successor12);
    Production<string> production21 = Production<string>(predecessor1, successor21);
    Production<string> production22 = Production<string>(predecessor2, successor22);
    Production<string> production31 = Production<string>(predecessor1, successor31);
    Production<string> production32 = Production<string>(predecessor2, successor32);
    unordered_set<Production<string>> productions1 = {production11, production12};
    unordered_set<Production<string>> productions2 = {production21, production22};
    unordered_set<Production<string>> productions3 = {production31, production32};
    LSystemInterpreter<string> LSystem1 = LSystemInterpreter<string>(alphabet, axiom, productions1);
    LSystemInterpreter<string> LSystem2 = LSystemInterpreter<string>(alphabet, axiom, productions2);
    LSystemInterpreter<string> LSystem3 = LSystemInterpreter<string>(alphabet, axiom, productions3);
    vector<vector<string>> output1(6);
    vector<vector<string>> output2(7);
    vector<vector<string>> output3(6);
    generate(output1.begin(), output1.end(), LSystem1);
    generate(output2.begin(), output2.end(), LSystem2);
    generate(output3.begin(), output3.end(), LSystem3);
    for(const auto &symbol1: output1[5]) {
        outputfile1 << symbol1 << " ";
    }
    outputfile1.close();
    for(const auto &symbol2 : output2[6]){
        outputfile2 << symbol2 << " ";
    }
    outputfile2.close();
    for(const auto &symbol3: output3[5]) {
        outputfile3 << symbol3 << " ";
    }
    outputfile3.close();
}

TEST_CASE("Drawing Evolution Of Plant") {
    ofstream outputfile("C:\\Data\\CLion\\Datastructuren\\MiniProject\\LSystemDrawer\\txt\\lsystem_evolutionplant.txt");
    unordered_set<string> alphabet = {"F", "X", "+", "-", "[", "]"};
    vector<string> axiom = {"X"};
    string predecessor1 = "X";
    string predecessor2 = "F";
    vector<string> successor1 = {"F", "[", "+", "X", "]", "[", "-", "X", "]", "F", "X"};
    vector<string> successor2 = {"F", "F"};
    Production<string> production1 = Production<string>(predecessor1, successor1);
    Production<string> production2 = Production<string>(predecessor2, successor2);
    unordered_set<Production<string>> productions = {production1, production2};
    LSystemInterpreter<string> LSystem = LSystemInterpreter<string>(alphabet, axiom, productions);
    vector<vector<string>> outputs(7);
    generate(outputs.begin(), outputs.end(), LSystem);
    int counter = 0;
    for(const auto &output: outputs){
        if (counter <= 1){ // I don't want to draw the first 2 iterations because the trees are too small
            counter += 1;
            continue;
        }
        for(const auto &symbol : output){
            outputfile << symbol << " ";
        }
        outputfile << "\n";
    }
    outputfile.close();
}

// just wanted to test some other trees but they didn't came out so nice so won't use it for the drawing with turtle
TEST_CASE("Drawing Some Different Trees") {
    ofstream outputfile("C:\\Data\\CLion\\Datastructuren\\MiniProject\\LSystemDrawer\\txt\\lsystem_difftrees.txt");
    unordered_set<string> alphabet = {"F", "X", "Z","+", "-", "[", "]"};
    vector<string> axiom = {"X"};
    string predecessor11 = "X";
    string predecessor12 = "F";
    string predecessor21 = "X";
    string predecessor22 = "F";
    string predecessor23 = "Z";
    vector<string> successor11 = {"F", "+", "[", "-", "F", "-", "X", "F", "-", "X", "]", "[", "+", "F", "F", "]", "[", "-", "-", "X", "F", "[", "+", "X", "]", "]", "[", "+", "+", "F", "-", "X", "]"};
    vector<string> successor12 = {"F", "F"};
    vector<string> successor21 = {"F", "F", "[", "+", "X", "Z", "+", "+", "X", "-", "F", "[", "+", "Z", "X", "]", "]", "[", "-", "X", "+", "+", "F", "-", "X", "]"};
    vector<string> successor22 = {"F", "X", "[", "F", "X", "[", "+", "X", "F", "]", "]"};
    vector<string> successor23 = {"[", "+", "F", "-", "X", "-", "F", "]", "[", "+", "+", "Z", "X", "]"};
    Production<string> production11 = Production<string>(predecessor11, successor11);
    Production<string> production12 = Production<string>(predecessor12, successor12);
    Production<string> production21 = Production<string>(predecessor21, successor21);
    Production<string> production22 = Production<string>(predecessor22, successor22);
    Production<string> production23 = Production<string>(predecessor23, successor23);
    unordered_set<Production<string>> productions1 = {production11, production12};
    unordered_set<Production<string>> productions2 = {production21, production22, production23};
    LSystemInterpreter<string> LSystem1 = LSystemInterpreter<string>(alphabet, axiom, productions1);
    LSystemInterpreter<string> LSystem2 = LSystemInterpreter<string>(alphabet, axiom, productions2);
    vector<vector<string>> output1(4);
    vector<vector<string>> output2(4);
    generate(output1.begin(), output1.end(), LSystem1);
    generate(output2.begin(), output2.end(), LSystem2);
    vector<vector<string>> outputs = {output1[3]};
    for(const auto &output: outputs) {
        for (const auto &symbol: output) {
            outputfile << symbol << " ";
        }
        outputfile << "\n";
    }
    outputfile.close();
}

// Drawing a tree to use with the game 'flappy bird'
// First was going to use multiple trees but with the implementation i'm only using the last one.
TEST_CASE("Drawing Trees For Flappy Bird") {
    ofstream outputfile("C:\\Data\\CLion\\Datastructuren\\MiniProject\\LSystemDrawer\\txt\\lsystem_flappybird.txt");
    unordered_set<string> alphabet = {"F", "X", "+", "-", "[", "]"};
    vector<string> axiom = {"X"};
    string predecessor1 = "X";
    string predecessor2 = "F";
    vector<string> successor1 = {"F", "[", "+", "X", "]", "[", "-", "X", "]", "F", "X"};
    vector<string> successor2 = {"F", "F"};
    Production<string> production1 = Production<string>(predecessor1, successor1);
    Production<string> production2 = Production<string>(predecessor2, successor2);
    unordered_set<Production<string>> productions = {production1, production2};
    LSystemInterpreter<string> LSystem = LSystemInterpreter<string>(alphabet, axiom, productions);
    vector<vector<string>> outputs(5);
    generate(outputs.begin(), outputs.end(), LSystem);
    for(const auto &output: outputs){
        for(const auto &symbol : output){
            outputfile << symbol << " ";
        }
        outputfile << "\n";
    }
    outputfile.close();
}
