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
    void setBit(std::uint64_t& bitboard, Square square);
    void clearBit(std::uint64_t& bitboard, Square square);
    bool testBit(std::uint64_t& bitboard, Square square);
    void printBitboard(std::uint64_t& bitboard);

    void updateMailbox();
    void printMailbox();

  private:
    std::array<std::uint64_t, 16> bitboards{};
    std::array<Piece, 64> mailbox{};

  };
}
