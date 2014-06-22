#ifndef MAIN_HPP
#define MAIN_HPP

int main(int argv, char* argc[]);
std::string removeWhitespace(std::string& input);
std::string removeMatching(std::string& input, const std::string& thingToRemove);
std::vector< std::vector<int> > makeNumbers(int length, std::vector<int> digits);
void validate(std::vector< std::vector<int> >& numbers);
void printNums(std::vector< std::vector<int> >& numbers);
void printNums(std::vector<int> num);
std::vector<int>* findHighest(std::vector< std::vector<int> >& numbers);

#endif
