#include <Logger/Logger.hpp>
#include <MiscUtils/MiscUtils.hpp>
#include <string>
#include <sstream>
#include <vector>
#include "main.hpp"

Logger logger;

int main(int argc, char* argv[]){
    std::string numbers = logger.getInput("Input the two numbers, seperated by a comma: ");
    numbers = removeWhitespace(numbers);

    std::stringstream ss(numbers);
    std::string num1, num2;

    num1 = numbers.substr(0, numbers.find(","));
    num2 = numbers.substr(numbers.find(",") + 1, std::string::npos);

    std::vector<int> digits1, digits2;

    for (int i = 0; i < num1.length(); i++){
        digits1.push_back(stringToInt(num1.substr(i,1)));
    }

    for (int i = 0; i < num2.length(); i++){
        digits2.push_back(stringToInt(num2.substr(i,1)));
    }

    std::string rawinput;
    while ((rawinput = logger.getInput("Please give the challenge, or a blank line to terminate the program: ")) != ""){
        rawinput = removeWhitespace(rawinput);
        if (rawinput == "") break;

        std::stringstream inputStream(rawinput);
        int length1, length2, intersection;
        char seperator;

        inputStream >> length1 >> seperator >> length2 >> seperator >> intersection;
        std::vector< std::vector<int> > numbers1, numbers2;

        numbers1 = makeNumbers(length1, digits1);
        numbers2 = makeNumbers(length2, digits2);

        validate(numbers1);
        validate(numbers2);

        std::vector<int>* highest1 = findHighest(numbers1);
        std::vector<int>* highest2 = findHighest(numbers2);

        if (!(highest1 && highest2)){
            logger.log(Logger::LogType::Error, "No possible number combination found. Please try a different challenge.");
            continue;
        }

        int horIntersect = -1;
        int verIntersect = -1;
        for (int i = 0; i < highest1->size(); i++){
            if (highest1->at(i) == intersection){
                horIntersect = i;
                break;
            }
        }
        for (int i = 0; i < highest2->size(); i++){
            if (highest2->at(i) == intersection){
                verIntersect = i;
                break;
            }
        }

        if (horIntersect == -1 || verIntersect == -1){
            logger.log(Logger::LogType::Error, "No possible number combination found. Please try a different challenge.");
            continue;
        }

        logger.log("");
        for (int i = 0; i < highest2->size(); i++){ //#lines = length of vertical num
            logger.logNoEndl("");

            if (i == verIntersect){
                for (int j = 0; j < highest1->size(); j++){
                    logger.continuelnNoEndl(highest1->at(j));
                }
            } else {
                for (int j = 0; j < horIntersect; j++){
                    logger.continuelnNoEndl(" ");
                }
                logger.continuelnNoEndl(highest2->at(i));
            }
        }
        logger.log("");
    }
}

std::string removeWhitespace(std::string& input){
    input = removeMatching(input, " ");
    input = removeMatching(input, "\t");
    return input;
}

std::string removeMatching(std::string& input, const std::string& thingToRemove){
    if (thingToRemove.empty()) return input;
    size_t start_pos = 0;
    while((start_pos = input.find(thingToRemove)) != std::string::npos){
        input = input.replace(input.find(thingToRemove), thingToRemove.length(), "");
    }
    return input;
}

std::vector< std::vector<int> > makeNumbers(int length, std::vector<int> theDigits){
    std::vector< std::vector<int> > output;

    if (length == 1){
        for (int i = 0; i < theDigits.size(); i++){
            std::vector<int> digit;
            digit.push_back(theDigits.at(i));
            output.push_back(digit);
        }
        return output;
    }

    for (int i = 0; i < theDigits.size(); i++){
        std::vector<int> tempDigits;
        for (int j = 0; j < theDigits.size(); j++){
            if (j != i) {
                tempDigits.push_back(theDigits.at(j));
            }
        }

        std::vector< std::vector<int> > smallerNumbers = makeNumbers(length - 1, tempDigits);

        for (int j = 0; j < smallerNumbers.size(); j++){
            std::vector<int> tempVector;
            tempVector.push_back(theDigits.at(i));

            for (int k = 0; k < smallerNumbers.at(j).size(); k++){
                tempVector.push_back(smallerNumbers.at(j).at(k));
            }

            output.push_back(tempVector);
        }
    }

    return output;
}

void validate(std::vector< std::vector<int> >& numbers){

    int i = 0;
    while (i < numbers.size()){

        bool zeroFound = false;
        bool valid     = true;
        for (int j = 0; j < numbers.at(i).size(); j++){
            if (numbers.at(i).at(j) == 0){
                if (zeroFound){
                    valid = false;
                    break;
                } else {
                    zeroFound = true;
                }
            }

            if (j > 0){
                if (!(numbers.at(i).at(j) <= numbers.at(i).at(j - 1))){
                    valid = false;
                    break;
                }
            }
        }

        if (!valid){
            numbers.erase(numbers.begin() + i);
        } else {
            i++;
        }
    }
}

void printNums(std::vector< std::vector<int> >& numbers){
    for (int i = 0; i < numbers.size(); i++){
        logger.logNoEndl("");
        for (int j = 0; j < numbers.at(i).size(); j++){
            logger.continuelnNoEndl(numbers.at(i).at(j));
        }
    }
}

void printNums(std::vector<int> num){
    logger.logNoEndl("");
    for (int i = 0; i < num.size(); i++){
        logger.continuelnNoEndl(num.at(i));
    }
}

std::vector<int>* findHighest(std::vector< std::vector<int> >& numbers){
    std::vector<int>* highest = NULL;
    int highestSum = 0;

    for (int i = 0; i < numbers.size(); i++){
        int sum = 0;

        for (int j = 0; j < numbers.at(i).size(); j++){
            sum += numbers.at(i).at(j);
        }

        if (sum > highestSum && sum % 5 == 0){
            highest = &numbers.at(i);
            highestSum = sum;
        }
    }

    return highest;
}
