// Silly Engine
// Copyright (c) 2026 SillyCatDevelopment.
// Created by Murder.
//
// This file is part of Silly Engine, licensed under the GNU GPL v3 or later
// with additional terms. See the LICENSE and NOTICE files for details.

module sillyengine.core;

namespace sillyengine
{
  void Board::setBit(std::uint64_t& bitboard, Square square)
  {
    bitboard |= (1ULL << square);
  }

  void Board::clearBit(std::uint64_t& bitboard, Square square)
  {
    bitboard &= ~(1ULL << square);
  }

  bool Board::testBit(std::uint64_t& bitboard, Square square)
  {
    return (bitboard >> square) & 1;
  }

  void Board::printBitboard(std::uint64_t& bitboard)
  {
    for(int r = 7; r >= 0; r--)
    {
      for(int f = 0; f <= 7; f++)
      {
        Square square = makeSquare(f, r);
        char toPrint = testBit(bitboard, square) ? '1' : '.';
        std::print("{}", toPrint);
      }
      std::print("\n");
    }
  }

  void Board::updateMailbox()
  {
    mailbox.fill(none);
    for(std::size_t i = 0; i < 16; i++)
    {
      Piece piece = static_cast<Piece>(i);

      for(int s = 0; s < 64; s++)
      {
        Square square = static_cast<Square>(s);
        if(testBit(bitboards[i], square))
          mailbox[square] = piece;
      }
    }
  }

  void Board::printMailbox()
  {
    for(int r = 7; r >= 0; r--)
    {
      for(int f = 0; f <= 7; f++)
      {
        Square square = makeSquare(f, r);
        char toPrint;
        switch(mailbox[square])
        {
          case wPawn : toPrint = 'P'; break;
          case wKnight : toPrint = 'N'; break;
          case wBishop : toPrint = 'B'; break;
          case wRook : toPrint = 'R'; break;
          case wQueen : toPrint = 'Q'; break;
          case wKing : toPrint = 'K'; break;

          case bPawn : toPrint = 'p'; break;
          case bKnight : toPrint = 'n'; break;
          case bBishop : toPrint = 'b'; break;
          case bRook : toPrint = 'r'; break;
          case bQueen : toPrint = 'q'; break;
          case bKing : toPrint = 'k'; break;

          default : toPrint = '.'; break;
        }

        std::print("{}", toPrint);
      }
      std::print("\n");
    }
  }
}
