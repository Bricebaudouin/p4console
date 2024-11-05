#include <gtest/gtest.h>

#include "Game.hpp"

//////////////////////////////////////////////////
// helpers
//////////////////////////////////////////////////

void assert_board(const board_t & expected, const Game & game) {
    for (int i=0; i<NI; i++)
        for (int j=0; j<NJ; j++)
            ASSERT_EQ( expected[i][j], game.getCell(i, j) );
}

void playMoves(Game & game, const std::vector<int> & moves) {
    for (int k : moves) {
        ASSERT_TRUE(game.isRunning());
        ASSERT_TRUE(k >= 0);
        ASSERT_TRUE(k < int(game.getMoves().size()));
        game.playK(k);
    }
}

//////////////////////////////////////////////////
// Game
//////////////////////////////////////////////////

TEST( Game, player2cell_1 ) {
    ASSERT_EQ(Cell::R, player2cell(Player::R));
    ASSERT_EQ(Cell::Y, player2cell(Player::Y));
}

TEST(Game, nextPlayer_1 ) {
    ASSERT_EQ( Player::Y, nextPlayer(Player::R) );
    ASSERT_EQ( Player::R, nextPlayer(Player::Y) );
}

TEST( Game, init_1 ) {
    Game game;
    const board_t expectedBoard {{
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E}
    }};
    const std::vector<int> expectedMoves {0, 1, 2, 3, 4, 5, 6};

    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::R, game.getCurrentPlayer());
    ASSERT_EQ(Status::PlayR, game.getStatus());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

TEST( Game, newGame_1 ) {
    Game game;
    const board_t expectedBoard {{
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E}
    }};
    const std::vector<int> expectedMoves {0, 1, 2, 3, 4, 5, 6};

    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::R, game.getCurrentPlayer());
    ASSERT_EQ(Status::PlayR, game.getStatus());
    ASSERT_EQ(expectedMoves, game.getMoves());

    game.newGame();
    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::Y, game.getCurrentPlayer());
    ASSERT_EQ(Status::PlayY, game.getStatus());
    ASSERT_EQ(true, game.isRunning());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

TEST( Game, newGame_2 ) {
    Game game;
    const board_t expectedBoard {{
        {Cell::E, Cell::E, Cell::R, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E}
    }};
    const std::vector<int> expectedMoves {0, 1, 2, 3, 4, 5, 6};

    game.playK(2);
    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::Y, game.getCurrentPlayer());
    ASSERT_EQ(Status::PlayY, game.getStatus());
    ASSERT_EQ(true, game.isRunning());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

TEST( Game, playK_1 ) {
    Game game;
    const std::vector<int> moves {1, 1, 2};
    playMoves(game, moves);

    const board_t expectedBoard {{
        {Cell::E, Cell::R, Cell::R, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::Y, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E}
    }};
    const std::vector<int> expectedMoves {0, 1, 2, 3, 4, 5, 6};

    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::Y, game.getCurrentPlayer());
    ASSERT_EQ(Status::PlayY, game.getStatus());
    ASSERT_EQ(true, game.isRunning());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

TEST( Game, playK_2 ) {
    Game game;
    const std::vector<int> moves {1, 1, 1, 1, 1, 1};
    playMoves(game, moves);

    const board_t expectedBoard {{
        {Cell::E, Cell::R, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::Y, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::R, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::Y, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::R, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::Y, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E}
    }};
    const std::vector<int> expectedMoves {0, 2, 3, 4, 5, 6};

    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::R, game.getCurrentPlayer());
    ASSERT_EQ(Status::PlayR, game.getStatus());
    ASSERT_EQ(true, game.isRunning());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

TEST( Game, playK_3 ) {
    Game game;
    const std::vector<int> moves {1, 1, 1, 1, 1, 1};
    playMoves(game, moves);

    const board_t expectedBoard {{
        {Cell::E, Cell::R, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::Y, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::R, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::Y, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::R, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::Y, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E}
    }};
    const std::vector<int> expectedMoves {0, 2, 3, 4, 5, 6};

    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::R, game.getCurrentPlayer());
    ASSERT_EQ(Status::PlayR, game.getStatus());
    ASSERT_EQ(true, game.isRunning());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

// red column
TEST( Game, playK_4 ) {
    Game game;
    const std::vector<int> moves {0, 4, 0, 4, 0, 4, 0};
    playMoves(game, moves);

    const board_t expectedBoard {{
        {Cell::R, Cell::E, Cell::E, Cell::E, Cell::Y, Cell::E, Cell::E},
        {Cell::R, Cell::E, Cell::E, Cell::E, Cell::Y, Cell::E, Cell::E},
        {Cell::R, Cell::E, Cell::E, Cell::E, Cell::Y, Cell::E, Cell::E},
        {Cell::R, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E}
    }};
    const std::vector<int> expectedMoves {};

    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::R, game.getCurrentPlayer());
    ASSERT_EQ(Status::WinR, game.getStatus());
    ASSERT_EQ(false, game.isRunning());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

// yellow column
TEST( Game, playK_5 ) {
    Game game;
    const std::vector<int> moves {4, 4, 0, 4, 0, 4, 0, 4};
    playMoves(game, moves);

    const board_t expectedBoard {{
        {Cell::R, Cell::E, Cell::E, Cell::E, Cell::R, Cell::E, Cell::E},
        {Cell::R, Cell::E, Cell::E, Cell::E, Cell::Y, Cell::E, Cell::E},
        {Cell::R, Cell::E, Cell::E, Cell::E, Cell::Y, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::Y, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::Y, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E}
    }};
    const std::vector<int> expectedMoves {};

    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::Y, game.getCurrentPlayer());
    ASSERT_EQ(Status::WinY, game.getStatus());
    ASSERT_EQ(false, game.isRunning());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

// red row
TEST( Game, playK_6 ) {
    Game game;
    const std::vector<int> moves {6, 6, 5, 5, 4, 4, 3};
    playMoves(game, moves);

    const board_t expectedBoard {{
        {Cell::E, Cell::E, Cell::E, Cell::R, Cell::R, Cell::R, Cell::R},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::Y, Cell::Y, Cell::Y},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E}
    }};
    const std::vector<int> expectedMoves {};

    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::R, game.getCurrentPlayer());
    ASSERT_EQ(Status::WinR, game.getStatus());
    ASSERT_EQ(false, game.isRunning());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

// yellow row
TEST( Game, playK_7 ) {
    Game game;
    const std::vector<int> moves {0, 6, 6, 5, 5, 4, 4, 3};
    playMoves(game, moves);

    const board_t expectedBoard {{
        {Cell::R, Cell::E, Cell::E, Cell::Y, Cell::Y, Cell::Y, Cell::Y},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::R, Cell::R, Cell::R},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E}
    }};
    const std::vector<int> expectedMoves {};

    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::Y, game.getCurrentPlayer());
    ASSERT_EQ(Status::WinY, game.getStatus());
    ASSERT_EQ(false, game.isRunning());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

// red diag1
TEST( Game, playK_8 ) {
    Game game;
    const std::vector<int> moves {1, 2, 2, 4, 3, 3, 3, 5, 4, 4, 4};
    playMoves(game, moves);

    const board_t expectedBoard {{
        {Cell::E, Cell::R, Cell::Y, Cell::R, Cell::Y, Cell::Y, Cell::E},
        {Cell::E, Cell::E, Cell::R, Cell::Y, Cell::R, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::R, Cell::Y, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::R, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E}
    }};
    const std::vector<int> expectedMoves {};

    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::R, game.getCurrentPlayer());
    ASSERT_EQ(Status::WinR, game.getStatus());
    ASSERT_EQ(false, game.isRunning());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

// yellow diag1
TEST( Game, playK_9 ) {
    Game game;
    const std::vector<int> moves {2, 1, 3, 2, 3, 3, 4, 4, 4, 4};
    playMoves(game, moves);

    const board_t expectedBoard {{
        {Cell::E, Cell::Y, Cell::R, Cell::R, Cell::R, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::Y, Cell::R, Cell::Y, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::Y, Cell::R, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::Y, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E}
    }};
    const std::vector<int> expectedMoves {};

    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::Y, game.getCurrentPlayer());
    ASSERT_EQ(Status::WinY, game.getStatus());
    ASSERT_EQ(false, game.isRunning());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

// red diag2
TEST( Game, playK_10 ) {
    Game game;
    const std::vector<int> moves {5, 4, 4, 3, 3, 2, 3, 2, 2, 0, 2};
    playMoves(game, moves);

    const board_t expectedBoard {{
        {Cell::Y, Cell::E, Cell::Y, Cell::Y, Cell::Y, Cell::R, Cell::E},
        {Cell::E, Cell::E, Cell::Y, Cell::R, Cell::R, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::R, Cell::R, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::R, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E}
    }};
    const std::vector<int> expectedMoves {};

    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::R, game.getCurrentPlayer());
    ASSERT_EQ(Status::WinR, game.getStatus());
    ASSERT_EQ(false, game.isRunning());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

// yellow diag2
TEST( Game, playK_11 ) {
    Game game;
    const std::vector<int> moves {4, 5, 3, 4, 3, 3, 2, 2, 2, 2};
    playMoves(game, moves);

    const board_t expectedBoard {{
        {Cell::E, Cell::E, Cell::R, Cell::R, Cell::R, Cell::Y, Cell::E},
        {Cell::E, Cell::E, Cell::Y, Cell::R, Cell::Y, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::R, Cell::Y, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::Y, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E},
        {Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E, Cell::E}
    }};
    const std::vector<int> expectedMoves {};

    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::Y, game.getCurrentPlayer());
    ASSERT_EQ(Status::WinY, game.getStatus());
    ASSERT_EQ(false, game.isRunning());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

// tie
TEST( Game, playK_12 ) {
    Game game;
    const std::vector<int> moves
    {   0, 1, 2, 3, 6, 4, 0, 5, 1, 2, 3, 5, 4, 0,
        1, 2, 3, 4, 6, 5, 6, 6, 0, 1, 4, 2, 5, 3,
        0, 1, 2, 3, 4, 5, 6, 0, 0, 0, 1, 0, 0, 0
    };
    playMoves(game, moves);

    const board_t expectedBoard {{
        {Cell::R, Cell::Y, Cell::R, Cell::Y, Cell::Y, Cell::Y, Cell::R},
        {Cell::R, Cell::R, Cell::Y, Cell::R, Cell::R, Cell::Y, Cell::R},
        {Cell::Y, Cell::R, Cell::Y, Cell::R, Cell::Y, Cell::Y, Cell::R},
        {Cell::R, Cell::Y, Cell::Y, Cell::Y, Cell::R, Cell::R, Cell::Y},
        {Cell::R, Cell::Y, Cell::R, Cell::Y, Cell::R, Cell::Y, Cell::R},
        {Cell::Y, Cell::R, Cell::Y, Cell::Y, Cell::R, Cell::R, Cell::Y}
    }};
    const std::vector<int> expectedMoves {};

    assert_board(expectedBoard, game);
    ASSERT_EQ(Player::Y, game.getCurrentPlayer());
    ASSERT_EQ(Status::Tie, game.getStatus());
    ASSERT_EQ(false, game.isRunning());
    ASSERT_EQ(expectedMoves, game.getMoves());
}

//////////////////////////////////////////////////
// main
//////////////////////////////////////////////////

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

