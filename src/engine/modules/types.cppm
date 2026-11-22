// Silly Engine
// Copyright (c) 2026 SillyCatDevelopment. All rights reserved.
// Created by Murder.

export module sillyengine.core:types;

import std;

export namespace sillyengine
{
  enum Color : std::uint8_t
  {
    Black = 1,
    White = 0  };

  enum PieceType : std::uint8_t
  {
    None = 0,
    Pawn = 1,
    Knight = 2,
    Bishop = 3,
    Rook = 4,
    Queen = 5,
    King = 6
  };

  enum Piece : std::uint8_t
  {
    none = 0b0000,
    wPawn = 0b0001,
    wKnight = 0b0010,
    wBishop = 0b0011,
    wRook = 0b0100,
    wQueen = 0b0101,
    wKing = 0b0110,
    bPawn = 0b1001,
    bKnight = 0b1010,
    bBishop = 0b1011,
    bRook = 0b1100,
    bQueen = 0b1101,
    bKing = 0b1110
  };

  enum Square : std::uint8_t
  {
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8,
    nosquare
  };

  constexpr Piece makePiece(PieceType pieceType, Color color)
  {
    // Shifting right the color by 3 (0001 << 3 = 1000) so the color ends in the 4 bit
    // And then give it it's type with an or operation (1000 | 0110 = 1110)
    return static_cast<Piece>((color << 3) | pieceType);
  }

  constexpr PieceType getPieceType(Piece piece)
  {
    // Getting the piece type with mask 7 (0111) in order to get the piece type (1001 & 0111 = 0001)
    return static_cast<PieceType>(piece & 7);
  }

  constexpr Color getColor(Piece piece)
  {
    // Getting the piece color by shifting to the right by 3 (1110 >> 3 = 0001)
    return static_cast<Color>(piece >> 3);
  }

  constexpr Square makeSquare(int file, int rank)
  {
    return static_cast<Square>(rank * 8 + file);
  }

  constexpr int fileOf(Square square)
  {
    return static_cast<int>(square % 8);
  }

  constexpr int rankOf(Square square)
  {
    return static_cast<int>(square / 8);
  }
}
