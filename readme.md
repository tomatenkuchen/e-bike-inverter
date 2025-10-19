# Power Management Framework for Battery to Motor Power Conversions

outline

## electrical setup

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
- [ ] implement estdlib as dependency
- [ ] create a board support package (bsp)
