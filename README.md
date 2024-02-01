# DD2480 - DECIDE

## About

This is a theoretical program for an anti-ballistic missile system, implemented in C++ according to the requirement specifications. The program decides through multiple different input variables whether to launch or not launch a missile, outputting "YES" or "NO".

The variables are collected through theoretical instruments, but in this project the input variables are set through a constructor class. Afterwards, the decode method can be executed in order to determine if a launch should be made, needing to pass 15 "LIC's" which are functions that check the input data against certain conditions.

Each LIC's have different conditions, and in order to understand these, each LIC has at least two unit tests, one positive and one negative, and sometimes additional tests. Furthermore, there are tested for the entire launch program.

## Prerequisites 

Before downloading the source code and atempting to build the project, ensure you have the following requirements:
* You have installed the latest version of 'C++'.
* You have installed one of the following C++ compilers: 'GCC' or 'clang'.
* You have installed 'cmake' and 'make'.
* You have a 'Linux/Mac/Windows' machine.

## How To Build

To build with `cmake`

```bash
mkdir build && cd build
cmake ..
make
```

To build with `make`

```bash
make
```

## Run and Test

To run the program

```bash
cd build
```

```bash
./decide ../example_input.txt
```

To run the tests

```bash
cd build
```

```bash
./CMVTest
```

## Contributing to DECIDE

To contribute to the DICDE code, follow these steps:
1. Fork this repository
2. Create a branch: `git checkout -b <branch_name>`
3. Add changes and commit them, if possible link to a relevant issue: `git commit -m '<commit_message>'`
4. Fetch and merge into main: `git merge origin/main`
5. Resolve any merge issues, push to remote: `git push -u origin <branch-name>`
6. Create a pull request to merge into main.

Pull request will be reviewed before being accepted.

## Dependecncies

Here are the dependecies used:
- [**Google Test**](https://google.github.io/googletest/primer.html): A testing framework for C++ programming, used for unit testing in this project. 

## Contributions

Ahmed:
- write here

Ed:
- write here

Elliot:
- Implemented LIC 2, 7 and 12
- Implemented multiple unit tests for LIC 2, 7, 12. (9 in total)
- Contributed to managing and creating issues, reviewing colleagues pull requests and discussing different implementation methods.
- Implemented the CMV function
- Debugging and solving bug issues related to the LIC's.
- Expanded the README file to enhance its content and structure. Also writing the about, prerequisites and dependencies section.

Hannes:
- write here

Yening:
- write here


## Essence

TODO:
In what state are you in? Why? What are obstacles to reach the next state?

## TODO

### Compulsory

- [ ] good README with a statement of contributions
- [ ] functional program
- [x] unit tests, 2 per LIC
- [ ] collaboration i.e. commits
- [ ] workflow and its documentation

### Optional

- [ ] commits linked to issues
- [ ] "something remarkable"
