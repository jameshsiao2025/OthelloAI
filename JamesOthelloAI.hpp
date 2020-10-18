#include "OthelloAI.hpp"

namespace jhsiao4
{
    class JamesOthelloAI : public OthelloAI
    {
    public: 

    std::pair<int, int> chooseMove(const OthelloGameState& state) override;

    int evaluate(const OthelloGameState& state);

    std::vector<std::pair<int,int>> availableMoves(const OthelloGameState& state, int width, int height);

    int search(const OthelloGameState& state, int depth);

    private:

    bool blackPlayer  = true;
    int width;
    int height;
    };



}