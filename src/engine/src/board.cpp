// Silly Engine
// Copyright (c) 2026 SillyCatDevelopment.
// Created by Murder.
//
// This file is part of Silly Engine, licensed under the GNU GPL v3 or later
// with additional terms. See the LICENSE and NOTICE files for details.

module;

#include <cassert>

module sillyengine.core;

namespace sillyengine
{
  void Board::putPiece(Piece piece, Square square)
  {
    assert(m_mailbox[square] == none);
    setBit(m_bitboards[piece], square);
    m_mailbox[square] = piece;
  }

  void Board::removePiece(Square square)
  {
    assert(m_mailbox[square] != none);
    Piece piece = m_mailbox[square];
    clearBit(m_bitboards[piece], square);
    m_mailbox[square] = none;
  }

  void Board::clear()
  {
    m_bitboards.fill(0);
    m_mailbox.fill(none);

    m_sideToMove = Color::White;
    m_castlingRights = 0;
    m_enPassantSquare = Square::nosquare;
    m_halfmoveClock = 0;
    m_fullmoveClock = 1;
  }

  void Board::printBoard()
  {
    for(int r = 7; r >= 0; r--)
    {
      char toPrint;
      switch (r)
      {
        case 7 : toPrint = '8'; break;
        case 6 : toPrint = '7'; break;
        case 5 : toPrint = '6'; break;
        case 4 : toPrint = '5'; break;
        case 3 : toPrint = '4'; break;
        case 2 : toPrint = '3'; break;
        case 1 : toPrint = '2'; break;
        case 0 : toPrint = '1'; break;
      }
      std::print("{} ", toPrint);
      for(int f = 0; f <= 7; f++)
      {
        Square square = makeSquare(f, r);
        switch(m_mailbox[square])
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
        std::print("{} ", toPrint);
      }
      std::print("\n");
    }
    std::print("\n");
    std::println("  a b c d e f g h");
    std::print("\n");

    std::string sToPrint;
    std::string casted;

    if(m_sideToMove == Color::White)
      casted = "White ";
    else
      casted = "Black ";
    sToPrint += "Side: " + casted;

    switch(m_castlingRights)
    {
      case 0b0000 : casted = "- "; break;
      case 0b0001 : casted = "K "; break;
      case 0b0010 : casted = "Q "; break;
      case 0b0011 : casted = "KQ "; break;
      case 0b0100 : casted = "k "; break;
      case 0b0101 : casted = "Kk "; break;
      case 0b0110 : casted = "Qk "; break;
      case 0b0111 : casted = "KQk "; break;
      case 0b1000 : casted = "q "; break;
      case 0b1001 : casted = "Kq "; break;
      case 0b1010 : casted = "Qq "; break;
      case 0b1011 : casted = "KQq "; break;
      case 0b1100 : casted = "kq "; break;
      case 0b1101 : casted = "Kkq "; break;
      case 0b1110 : casted = "Qkq "; break;
      case 0b1111 : casted = "KQkq "; break;
    }

    sToPrint += "Castling: " + casted;

    // TODO: En passant
    sToPrint += "En passant: - ";

    std::print("{}Clocks: {} {}", sToPrint, m_halfmoveClock, m_fullmoveClock);
    std::print("\n");
  }

  void Board::setBit(std::uint64_t& bitboard, Square square)
  {
    bitboard |= (1ULL << square);
  }

  void Board::clearBit(std::uint64_t& bitboard, Square square)
  {
    bitboard &= ~(1ULL << square);
  }

  bool Board::testBit(std::uint64_t bitboard, Square square)
  {
    return (bitboard >> square) & 1;
  }

  void Board::printBitboard(std::uint64_t bitboard)
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
    std::print("\n");
  }

  void Board::updateMailbox()
  {
    m_mailbox.fill(none);
    for(std::size_t i = 0; i < 16; i++)
    {
      Piece piece = static_cast<Piece>(i);

      for(int s = 0; s < 64; s++)
      {
        Square square = static_cast<Square>(s);
        if(testBit(m_bitboards[i], square))
          m_mailbox[square] = piece;
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
        switch(m_mailbox[square])
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
    std::print("\n");
  }
}
