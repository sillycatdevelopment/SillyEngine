// Silly Engine
// Copyright (c) 2026 SillyCatDevelopment.
// Created by Murder.
//
// This file is part of Silly Engine, licensed under the GNU GPL v3 or later
// with additional terms. See the LICENSE and NOTICE files for details.

import std;
import sillyengine.core;

int main()
{
  using namespace sillyengine;

  Board board;
  board.clear();
  board.putPiece(bRook, a8);
  board.putPiece(bRook, h8);

  board.printBitboard(board.pieces(bRook));   // 1s on a8 and h8

  board.removePiece(a8);
  board.printBoard();                         // a8 is now "."
  board.printBitboard(board.pieces(bRook));   // only h8

  return 0;
}
