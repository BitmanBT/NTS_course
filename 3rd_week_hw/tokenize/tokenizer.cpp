#include <string>
#include <variant>
#include <vector>
#include <unordered_map>

struct OpeningBracket {};

struct ClosingBracket {};

struct Comma {};

struct Number
{
  int value;
};

struct UnknownToken
{
  std::string value;
};

struct MinToken {};

struct MaxToken {};

struct SqrToken {};

struct AbsToken {};

struct Plus {};

struct Minus {};

struct Multiply {};

struct Modulo {};

struct Divide {};

using Token = std::variant<OpeningBracket, ClosingBracket, Comma, Number, UnknownToken, MinToken,
                           MaxToken, SqrToken, AbsToken, Plus, Minus, Multiply, Modulo, Divide>;

const std::unordered_map<char, Token> kSymbol2Token {
    {'+', Plus{}}, {'-', Minus{}}, {'*', Multiply{}}, {'/', Divide{}}, {'%', Modulo{}},
    {'(', OpeningBracket{}}, {')', ClosingBracket{}}, {',', Comma{}}
};

int ToDigit(unsigned char symbol)
{
  return symbol - '0';
}

Number ParseNumber(const std::string& input, size_t& pos)
{
  int value = 0;
  auto symbol = static_cast<unsigned char>(input[pos]);
  while (std::isdigit(symbol))
  {
    value = value * 10 + ToDigit(symbol);
    if (pos == input.size() - 1)
    {
      ++pos;
      break;
    }
    symbol = static_cast<unsigned char>(input[++pos]);
  }
  return Number{value};
}

Token ParseName(const std::string& input, size_t& pos)
{
  std::string content;
  char symbol = input[pos];
  while (std::isalpha(static_cast<unsigned char>(symbol)))
  {
    content.push_back(symbol);
    if (pos == input.size() - 1)
    {
      ++pos;
      break;
    }
    symbol = input[++pos];
  }
  
  if (content == "min" || content == "MIN")
    return MinToken{};
  else if (content == "max" || content == "MAX")
    return MaxToken{};
  else if (content == "sqr" || content == "SQR")
    return SqrToken{};
  else if (content == "abs" || content == "ABS")
    return AbsToken{};
  else
    return UnknownToken{content};
}

std::vector<Token> Tokenize(const std::string& input)
{
  std::vector<Token> tokens;
  const size_t size = input.size();
  size_t pos = 0;
  while (pos < size)
  {
    const char symbol = input[pos];
    if (std::isspace(static_cast<unsigned char>(symbol))) {
      ++pos;
    } else if (std::isdigit(static_cast<unsigned char>(symbol))) {
      tokens.emplace_back(ParseNumber(input, pos));
    } else if (auto it = kSymbol2Token.find(symbol); it != kSymbol2Token.end()) {
      tokens.emplace_back(it->second);
      ++pos;
    } else if (std::isalpha(static_cast<unsigned char>(symbol))) {
      tokens.emplace_back(ParseName(input, pos));
    }
  }
  return tokens;
}