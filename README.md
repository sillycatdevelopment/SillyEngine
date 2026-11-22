# SillyEngine

A chess engine written from scratch.

## Building

Needs CMake 4.5+, Ninja and Homebrew's LLVM: `brew install cmake ninja llvm`.

```sh
cmake --preset debug          # or release
cmake --build --preset debug
ctest --preset debug
```

In VS Code: accept the recommended extensions, pick the **debug** preset,
then ⌘⇧B builds. Build once before clangd understands your modules, and
again after adding an `import`.

## Where code goes

You never edit CMake to add code. Every folder directly inside `src/` is a
**part**, found automatically on the next build:

```
src/
  engine/              a part -> a library called "engine"
    modules/           *.cppm: module interface units (any subfolder depth)
    src/               *.cpp:  sources, module implementation units
  uci/                 a part with main.cpp directly inside -> a program
    main.cpp           built as build/<preset>/uci
tests/                 *.cpp anywhere: GoogleTest tests -> build/<preset>/tests
```

- A part **with `main.cpp` directly inside** becomes a program, named after
  its folder. Any other part becomes a library.
- Programs and tests link every library, so they can `import` any module.
- Subfolders are fine anywhere (`modules/board/`, `src/search/`...).
- Empty parts are skipped until they get their first file.
- Test files only need `TEST(...)` blocks: GoogleTest provides `main()`.
- If one library needs another, add a line to `CMakeLists.txt` after
  `sillyengine_add_parts(...)`, e.g. `target_link_libraries(engine PUBLIC tools)`.

Run or debug a program from VS Code with F5 ("Run program"): it starts the
program selected as CMake Tools' launch target in the status bar.
