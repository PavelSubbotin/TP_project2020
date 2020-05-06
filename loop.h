#include<iostream>
#include "battleboard.h"
#include "SafeInput.h"
#include "build.h"
#include "move.h"
#include "attack.h"
#include "final.h"

class GameLoop{
  public:
    void game_loop(){
        BattleBoard board;
        PrepPhase prep;
        prep.build(board);

        MovePhase move_;
        std::pair<int, int> acts = move_.make_moves(board);

        AttackPhase attack;
        attack.attack_phase(board, acts.first, acts.second);

        FinalPhase final_;
        int winner = final_.final_phase(board);

        if (winner == 0) {
            std::cout << "No winner now!" << std::endl;
        } else if (winner == 1) {
            std::cout << "First player won!" << std::endl;
        } else if (winner == -1) {
            std::cout << "Second player won!" << std::endl;
        } else {
            std::cout << "Draw!";
        }
        board.shuffle_septums()
    }
};
