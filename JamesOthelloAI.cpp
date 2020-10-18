#include <ics46/factory/DynamicFactory.hpp>
#include "JamesOthelloAI.hpp"


ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, jhsiao4::JamesOthelloAI, "working title(required)");


std::pair<int, int> jhsiao4::JamesOthelloAI::chooseMove(const OthelloGameState& state)
{
    // implementation of the AI goes here
    //std::vector<std::pair<int,int>> valid; 
    if(state.blackScore() > state.whiteScore())
    {
        blackPlayer = false;
    }
    width =  state.board().width();
    height = state.board().height(); 
    int move = 0;
    int max = 0;
    std::vector<std::pair<int,int>> valid;
    valid = availableMoves(state, width, height);
    for(int i=0;i<valid.size(); ++i)
    {
       std::unique_ptr tempBoard = state.clone();
        tempBoard->makeMove(valid.at(i).first, valid.at(i).second);
        int current = search(*tempBoard, 3);
        if(current > max)
            {
                max = current;
                move = i;
            }
    }
    
    return std::pair(valid.at(move).first, valid.at(move).second);

}

int jhsiao4::JamesOthelloAI::evaluate(const OthelloGameState& state)
{
    int score;

    if(blackPlayer == false)
    {
        score = state.whiteScore() - state.blackScore();
    }
    else
    {
        score = state.blackScore() - state.whiteScore();
    }
    
    return score;
}

std::vector<std::pair<int,int>> jhsiao4::JamesOthelloAI::availableMoves(const OthelloGameState& state, int width, int height)
{
    std::vector<std::pair<int,int>> valid; 
    for(int i=0; i<width; ++i)
    {
        for(int j=0; j<height; ++j)
        {
            if(state.isValidMove(i,j) == true)
            {
                valid.push_back(std::pair(i,j));
            }
        }
    }
    return valid;
}

int jhsiao4::JamesOthelloAI::search(const OthelloGameState& state, int depth)
{
    if(depth ==0)
    {
        return evaluate(state);
    }
    else
    {
        if((blackPlayer == true && state.isBlackTurn() == true)||(blackPlayer == false && state.isBlackTurn() == false))
        {
            std::vector<std::pair<int,int>> temp;
            temp = availableMoves(state, width, height);
            int max = 0;
  
            for(int i=0; i< temp.size(); ++i)
            {
                std::unique_ptr tempBoard = state.clone();
                tempBoard->makeMove(temp.at(i).first, temp.at(i).second);
                int current = search(*tempBoard, depth-1);
                if(current > max)
                {
                    max = current;
                }
            }
            return max;
        }
        else
        {
            std::vector<std::pair<int,int>> temp;
            temp = availableMoves(state, width, height);
            int min = 999999999;
  
            for(int i=0; i< temp.size(); ++i)
            {
                std::unique_ptr tempBoard = state.clone();
                tempBoard->makeMove(temp.at(i).first, temp.at(i).second);
                int current = search(*tempBoard, depth-1);
                if(current < min)
                {
                    min = current;
                }
            } 
            return min;
        }
    }
    
    return 0;
}