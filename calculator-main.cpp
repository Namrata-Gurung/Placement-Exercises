#include <iostream>
#include <sstream>
#include <vector>
#include <optional>
#include <string>
#include <cstdlib>
#include <cassert>
#include <cmath>


class Tokeniser
{
public:

    enum class Type
    {
        add,
        subtract,
        multiply,
        divide,
        pi,

        unknown,
    };

    struct TokenList
    {
        double lhs;
        double rhs;
        Type type;
    };

    std::optional <TokenList> tokenise(std::string input) const
    {
        auto type = findType(input);
        if (type == Type::unknown)
            return {};

        auto lhs = findLHS(input);
        if (!lhs.has_value())
            return {};

        auto rhs = findRHS(input);
        if (!rhs.has_value())
            return {};

        TokenList tokens;
        tokens.lhs = *lhs;
        tokens.rhs = *rhs;
        tokens.type = type;
        return tokens;
    }

private:

    bool find(std::string input, std::string character) const
    {
        return input.find(character) != std::string::npos;
    }

    std::optional <double> findAndExtractLHS(std::string input, std::string character) const
    {
        if (auto pos = input.find(character); pos != std::string::npos)
            return std::stod(input.substr(0, pos));

        return {};
    }

    std::optional <double> findAndExtractRHS(std::string input, std::string character) const
    {
        if (auto pos = input.find(character); pos != std::string::npos)
            return std::stod(input.substr(pos + 1));

        return {};
    }

    Type findType(std::string input) const
    {
        if (find(input, "+")) return Type::add;
        if (find(input, "-")) return Type::subtract;
        if (find(input, "*")) return Type::multiply;
        if (find(input, "/")) return Type::divide; // divide is recognised as a token
        if (find(input, "pi")) return Type::pi; //pi is recognised as a token 

        return Type::unknown;
    }

    std::optional <double> findLHS(std::string input) const
    {
        if (auto result = findAndExtractLHS(input, "+"))
            return result;

        if (auto result = findAndExtractLHS(input, "-"))
            return result;

        if (auto result = findAndExtractLHS(input, "*"))
            return result;

        if (auto result = findAndExtractLHS(input, "/"))
            return result;
        
        if(find(input, "pi"))
           return;

        return {};
    }

    std::optional <double> findRHS(std::string input) const
    {
        if (auto result = findAndExtractRHS(input, "+"))
            return result;

        if (auto result = findAndExtractRHS(input, "-"))
            return result;

        if (auto result = findAndExtractRHS(input, "*"))
            return result;

        if (auto result = findAndExtractRHS(input, "/"))
            return result;

        return {};
    }
};

class Calculator
{
public:

     const double pi;

    Calculator() = default;
    ~Calculator() = default;

    double calculate(Tokeniser::TokenList tokens) const
    {
        switch (tokens.type)
        {
        case Tokeniser::Type::add:
            return tokens.lhs + tokens.rhs;
        case Tokeniser::Type::subtract:
            return tokens.lhs - tokens.rhs;
        case Tokeniser::Type::multiply:
            return tokens.lhs * tokens.rhs;
        case Tokeniser::Type::divide:
            return tokens.lhs / tokens.rhs;
        case Tokeniser::Type::pi:
            return tokens.lhs * tokens.rhs;
        default:
            std::cout << "Invalid Operator";
            break;
        }

        return 0;
    }
};

class InputProcessor
{
public:

    enum class InputRequest
    {
        quitProcessing,
        continueProcessing,
    };


    InputRequest requestInput() const
    {
        std::cout << "Please enter a calculation (Type Q to quit)" << std::endl;

        std::string input;
        std::getline(std::cin, input);

        if (input == "Q" || input == "q")
            return InputRequest::quitProcessing;

        processInput(input);

        return InputRequest::continueProcessing;
    }

private:

    void processInput(std::string input) const
    {
        if (auto tokens = Tokeniser().tokenise(input))
            std::cout << "Answer: " << Calculator().calculate(*tokens) << std::endl;
        else
            std::cout << "There was an error in the input string, please try again..." << std::endl;
    }
};

class ResultChecker
{
public:

    static void check(double value, double expected, double range = 1e-3)
    {
        return assert(std::abs(value - expected) <= range);
    }
};

void test()
{
    auto result = Tokeniser().tokenise("10*4");
    assert(result.has_value());
    ResultChecker::check(result->lhs, 10);
    ResultChecker::check(result->rhs, 4);
    assert(result->type == Tokeniser::Type::multiply);

    result = Tokeniser().tokenise("25.3 + 18.6");
    assert(result.has_value());
    ResultChecker::check(result->lhs, 6);
    ResultChecker::check(result->rhs, 9);
    assert(result->type == Tokeniser::Type::add);

    result = Tokeniser().tokenise("3 - 5.6");
    assert(result.has_value());
    ResultChecker::check(result->lhs, 25);
    ResultChecker::check(result->rhs, 4);
    assert(result->type == Tokeniser::Type::subtract);

    result = Tokeniser().tokenise("72 / 9");
    assert(result.has_value());
    ResultChecker::check(result->lhs, 72);
    ResultChecker::check(result->rhs, 9);
    assert(result->type == Tokeniser::Type::divide);

    result = Tokeniser().tokenise("pi*5");
    assert(result.has_value());
    ResultChecker::check(result->lhs, pi);
    ResultChecker::check(result->rhs, 5);
    assert(result->type == Tokeniser::Type::divide);

    ResultChecker::check(Calculator().calculate({ 10, 4, Tokeniser::Type::multiply }), 40);
    ResultChecker::check(Calculator().calculate({ 25.3, 18.6, Tokeniser::Type::add }), 43.9);
    ResultChecker::check(Calculator().calculate({ 3, 5.6, Tokeniser::Type::subtract }), 2.6);
    ResultChecker::check(Calculator().calculate({ 7, 9, Tokeniser::Type::divide }), 8);
    ResultChecker::check(Calculator().calculate({ pi, 5, Tokeniser::Type::pi }), 15.70796);

void run()
{
    InputProcessor processor;
    while (processor.requestInput() == InputProcessor::InputRequest::continueProcessing);
}

int main(int argc, const char* argv[])
{
    if (argc > 1 && std::string(argv[1]) == "--test")
        test();
    else
        run();

    return 0;
}
