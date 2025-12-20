# e-bike electronics for my personal bike

do not use this if you aren't familiar with electrical systems. batteries, soldering irons and electronics are dangerous in their nature, all together. don't blame me if you hurt yourself.

## electrical setup

fundamental for this project is the ST Microelectronics demo board [B-G431-ESC1](https://www.st.com/en/evaluation-tools/b-g431b-esc1.html). it's a good bang-for-the-buck starting point for inverter technologies - although i wished they'd used their STSPIN series for this.
For now this is the center of attention for this project. this will change any time the pcb for using the actual STSPING4 is ready to go.

Follow the instructions given by ST to handle the board and their tooling.

## APIs

## how to compile

this project is done using conan package manager for ease of use.
embedded projects in particular suffer from a highly specialized use of tools
that are mostly scattered in the web, hard to configure, and platfrom specific.
conan helped me to fix at least a little of this embedded worlds dilemma.
this is how you can setup your build:

```bash

# install conan via python package manager
pip install --upgrade conan

# set up default build engine
conan profile detect

# add compiler profile for stm32g4
cp .conan/stm32g4 ~/.conan2/profiles/stm32g4

# build a first
conan build . -pr=stm32g4 -s build_type=Debug -b=missing

```

## todos

- [x] find datasheets
- [x] configure cubemx project to fit schematic
- [x] create minimal compilable c++ project
- [x] create a board support package (bsp)
- [ ] finish pcb
