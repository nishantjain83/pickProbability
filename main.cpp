#include <iostream>
#include <map>

using namespace std;

enum AwardType
{
    Credit_500,
    Credit_50,
    FreeGames_10,
    FreeGames_5,
    ExtraPics_2,
    ExtraPics_1,
    Blank,
    Stopper
};

typedef map<AwardType, int> Picks;
int main()
{
    Picks input = {
        {Credit_500, 1},
        {Credit_50, 2},
        {FreeGames_10, 1},
        {FreeGames_5, 2},
        {ExtraPics_2, 2},
        {ExtraPics_1, 1},
        {Blank, 5},
        {Stopper, 1},
    };

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

double getPickProbability(Picks picksMap, int remainingPicks, AwardType pickToFind)
{
    double probability = 0.0;
    int targetPickAwards = picksMap.count(pickToFind);
    int totalPickAwards = numberOfRemainingAwards(picksMap);
    if (remainingPicks == 0 || targetPickAwards == 0)
    {
        return 0.0;
    }
    if (remainingPicks == 1)
    {
        if (numberOfExtraPicAwards(picksMap) == 0)
        {
            probability = targetPickAwards / totalPickAwards;
            return probability;
        }

        if (picksMap.count(ExtraPics_1) > 0)
        {
            reduceMapAward(picksMap, ExtraPics_1);
            probability += getPickProbability(picksMap, 1, pickToFind);
            incrementMapAward(picksMap, ExtraPics_1);
        }
        if (picksMap.count(ExtraPics_2) > 0)
        {
            reduceMapAward(picksMap, ExtraPics_2);
            probability += getPickProbability(picksMap, 2, pickToFind);
            incrementMapAward(picksMap, ExtraPics_2);
        }
        return probability;
    }

    
    return probability;
}