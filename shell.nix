with import <nixpkgs> {};

mkShell {
  buildInputs = [
    graphviz
    gtest
    kcachegrind
    valgrind
  ];
}

