// Silly Engine
// Copyright (c) 2026 SillyCatDevelopment.
// Created by Murder.
//
// This file is part of Silly Engine, licensed under the GNU GPL v3 or later
// with additional terms. See the LICENSE and NOTICE files for details.

export module sillyengine.core:board;

import std;

import :types;

export namespace sillyengine
{
  class Board
  {
  public:
    // Constructor
    Board() = default;

    // Board functions
    void clear();
    void putPiece(Piece piece, Square square);
    void removePiece(Square square);

    // Print Functions
    void printBoard();
    void printBitboard(std::uint64_t bitboard);
    void printMailbox();

    std::uint64_t pieces(Piece piece) const { return m_bitboards[piece]; }

  private:
    std::array<std::uint64_t, 16> m_bitboards{};
    std::array<Piece, 64> m_mailbox{};

    // Position data
    Color m_sideToMove = Color::White;
    std::uint8_t m_castlingRights = 0b1111;
    Square m_enPassantSquare = Square::nosquare;
    int m_halfmoveClock = 0;
    int m_fullmoveClock = 1;

    // Bitboard functions
    void setBit(std::uint64_t& bitboard, Square square);
    void clearBit(std::uint64_t& bitboard, Square square);
    bool testBit(std::uint64_t bitboard, Square square);

    // Mailbox functions
    void updateMailbox();
  };
}
