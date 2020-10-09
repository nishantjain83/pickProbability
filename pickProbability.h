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
double getPickProbability(Picks picksMap, int remainingPicks, AwardType pickToFind);
