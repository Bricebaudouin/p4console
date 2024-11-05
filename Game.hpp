#include <array>
#include <cassert>
#include <vector>

enum class Cell { E, R, Y };  // Empty, Red, Yellow
enum class Player { R, Y };   // Red, Yellow
enum class Status { PlayR, PlayY, Tie, WinR, WinY };

Cell player2cell(Player p);
Player nextPlayer(Player p);

const int NI = 6;
const int NJ = 7;

using board_t = std::array<std::array<Cell, NJ>, NI>;

extern const board_t CELLS;

class Game {
    private:
        board_t _cells;
        std::vector<int> _moves;
        Status _status;
        Player _currentPlayer;
        Player _firstPlayer;

    public:
        Game();
        void newGame();
        void playK(int k);
        Player getCurrentPlayer() const;
        const std::vector<int> & getMoves() const;
        Cell getCell(int i, int j) const;
        Status getStatus() const;
        bool isRunning() const;

    private:
        bool checkIJ(int i, int j) const;
        int length(int i0, int j0, int di, int dj) const;
        bool checkLine(int i0, int j0, int di, int dj) const;
};

