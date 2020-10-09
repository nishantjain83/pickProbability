#include <iostream>
#include <map>
#include "pickProbability.h"

string const awardName[] = {"Credit_500",
                            "Credit_50",
                            "FreeGames_10",
                            "FreeGames_5",
                            "ExtraPics_2",
                            "ExtraPics_1",
                            "Blank",
                            "Stopper"};

int main()
{
    Picks inputPicks = {
        {Credit_500, 1},
        {Credit_50, 2},
        {FreeGames_10, 1},
        {FreeGames_5, 2},
        {ExtraPics_2, 2},
        {ExtraPics_1, 1},
        {Blank, 5},
        {Stopper, 1},
    };

    double probability = getPickProbability(inputPicks, 1, Credit_500);
    cout << probability << endl;

    return 0;
}

int numberOfRemainingAwards(Picks picksMap)
{
    int sum = 0;
    for (auto it = picksMap.begin(); it != picksMap.end(); it++)
    {
        sum += it->second;
    }
    return sum;
}

int numberOfExtraPicAwards(Picks picksMap)
{
    return picksMap.count(ExtraPics_1) + picksMap.count(ExtraPics_2);
}

Picks &incrementMapAward(Picks &picksMap, AwardType award)
{
    if (picksMap.count(award) == 0)
    {
        picksMap[award] = 1;
    }
    else
    {
        picksMap[award]++;
    }
    return picksMap;
}

Picks &reduceMapAward(Picks &picksMap, AwardType award)
{
    if (picksMap.count(award) > 0)
    {
        picksMap[award]--;
        if (picksMap[award] <= 0)
        {
            picksMap.erase(award);
        }
    }
    return picksMap;
}

int awardCount(const Picks &picksMap, AwardType award)
{
    int count = 0;
    if (picksMap.count(award) > 0)
    {
        count = picksMap.at(award);
    }
    return count;
}

void printPicksMap(const Picks &picksMap)
{
    cout << "{";
    for (auto it = picksMap.begin(); it != picksMap.end(); it++)
    {
        cout << "{" << awardName[it->first] << ": " << it->second << "}";
    }
    cout << "}" << endl;
}

double getPickProbability(Picks picksMap, int remainingPicks, AwardType pickToFind)
{
    printPicksMap(picksMap);
    cout << "remainingPicks: " << remainingPicks << " picsToFind: " << pickToFind << endl;
    double probability = 0.0;
    int targetPickAwards = awardCount(picksMap, pickToFind);
    int totalPickAwards = numberOfRemainingAwards(picksMap);
    if (remainingPicks == 0 || targetPickAwards == 0)
    {
        return 0.0;
    }
    if (remainingPicks == 1)
    {
        probability += double(targetPickAwards) / totalPickAwards;

        if (awardCount(picksMap, ExtraPics_1) > 0)
        {
            reduceMapAward(picksMap, ExtraPics_1);
            probability += getPickProbability(picksMap, 1, pickToFind);
            incrementMapAward(picksMap, ExtraPics_1);
        }
        if (awardCount(picksMap, ExtraPics_2) > 0)
        {
            reduceMapAward(picksMap, ExtraPics_2);
            probability += getPickProbability(picksMap, 2, pickToFind);
            incrementMapAward(picksMap, ExtraPics_2);
        }
        return probability;
    }

    // Probability of pick found at stage step - 1   +
    probability += getPickProbability(picksMap, remainingPicks - 1, pickToFind);

    // Probability of finding award at current stage without Stopper +
    double probCurrentStep = 0.0;
    for (int i = 1; i < remainingPicks; i++)
    {
        int denominator = totalPickAwards - targetPickAwards - i;
        cout << 1 << "/" << denominator << " * ";
        probCurrentStep += 1.0 / double(denominator);
    }
    probCurrentStep *= targetPickAwards / double(totalPickAwards - remainingPicks);
    probability += probCurrentStep;

    // Probability of finding ExtraPic_1 and then finding the award +
    double probPreviousExtraPic_1 = getPickProbability(picksMap, remainingPicks - 1, ExtraPics_1);
    reduceMapAward(picksMap, ExtraPics_1);
    probability += probPreviousExtraPic_1 * getPickProbability(picksMap, remainingPicks, pickToFind);
    incrementMapAward(picksMap, ExtraPics_1);

    // Probability of finding ExtraPic_2 and then finding the award
    double probPreviousExtraPic_2 = getPickProbability(picksMap, remainingPicks - 1, ExtraPics_1);
    reduceMapAward(picksMap, ExtraPics_2);
    probability += probPreviousExtraPic_2 * getPickProbability(picksMap, remainingPicks + 1, pickToFind);
    incrementMapAward(picksMap, ExtraPics_2);

    return probability;
}