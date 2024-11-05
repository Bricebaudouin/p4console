#include "Game.hpp"

#include <array>
#include <cassert>
#include <vector>

Cell player2cell(Player p) {
    return p == Player::R ? Cell::R : Cell::Y;
}

Player nextPlayer(Player p) {
    return p == Player::R ? Player::Y : Player::R;
}

const board_t CELLS({Cell::E});

bool Game::checkIJ(int i, int j) const {
    return i>=0 and i<NI and j>=0 and j<NJ;
}

int Game::length(int i0, int j0, int di, int dj) const {
    Cell c = _cells[i0][j0];
    int l = 0;
    int i = i0 + di;
    int j = j0 + dj;
    while (checkIJ(i, j) and _cells[i][j] == c) {
        l++;
        i += di;
        j += dj;
    }
    return l;
}

bool Game::checkLine(int i0, int j0, int di, int dj) const {
    int l = length(i0, j0, di, dj) + length(i0, j0, -di, -dj);
    return l >= 3;
}

Game::Game() : _firstPlayer(Player::Y) {
    _moves.reserve(NJ);
    newGame();
}

void Game::newGame() {
    _cells = CELLS;
    _moves.clear();
    for (int k=0; k<NJ; k++)
        _moves.push_back(k);
    _firstPlayer = nextPlayer(_firstPlayer);
    _currentPlayer = _firstPlayer;
    _status = _currentPlayer == Player::R ? Status::PlayR : Status::PlayY;
}

void Game::playK(int k) {
    // find and play cell
    const int j0 = _moves[k];
    int i0 = NI;
    while (i0>0 and _cells[i0-1][j0] == Cell::E)
        i0--;
    _cells[i0][j0] = player2cell(_currentPlayer);

    // update status/current/moves
    _moves.clear();
    if (checkLine(i0, j0, 0, 1) 
            or checkLine(i0, j0, 1, 0) 
            or checkLine(i0, j0, 1, 1) 
            or checkLine(i0, j0, 1, -1)) {
        _status = _currentPlayer == Player::R ? Status::WinR : Status::WinY;
    }
    else {
        // update moves
        for (int j=0; j<NJ; j++) {
            if (_cells[NI-1][j] == Cell::E)
                _moves.push_back(j);
        }

        if (_moves.empty()) {
            _status = Status::Tie;
        }
        else {
            _currentPlayer = nextPlayer(_currentPlayer);
            _status = _currentPlayer == Player::R ? Status::PlayR : Status::PlayY;
        }
    }
}

Player Game::getCurrentPlayer() const {
    return _currentPlayer;
}

const std::vector<int> & Game::getMoves() const {
    return _moves;
}

Cell Game::getCell(int i, int j) const {
    return _cells[i][j];
}

Status Game::getStatus() const {
    return _status;
}

bool Game::isRunning() const {
    return _status == Status::PlayR or _status == Status::PlayY;
}

