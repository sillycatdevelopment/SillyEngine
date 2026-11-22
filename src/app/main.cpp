// Silly Engine
// Copyright (c) 2026 SillyCatDevelopment. All rights reserved.
// Created by Murder.

import std;
import sillyengine.core;

int main()
{
  using namespace sillyengine;

  Board board;
  std::uint64_t bb = 0;
  board.setBit(bb, e8);
  board.setBit(bb, a1);
  board.printBitboard(bb);

  std::print("\n");
  board.clearBit(bb, e8);
  board.clearBit(bb, a1);
  board.printBitboard(bb);

  return 0;
}
