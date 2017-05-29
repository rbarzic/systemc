# SystemC examples

Various SystemC examples form the net, sometimes fixed to run correctly with the latest SystemC version.
Also always provided with suitable makefiles.

Tested on Ubuntu 16.04.2  "Xenial" with SystemC 2.3.1a

## Setup

The environment variable SYSTEMC_HOME must be set to point to the Systemc installation folder.

For example

```
export SYSTEMC_HOME=/opt/systemc/2.3.1a

```



##  hello_world

Code from http://www.asic-world.com/systemc/first1.html#Introduction

### Compilation/Simulation

```
make comp # Compilation
make run  # Simulation
```


## First counter


Code from http://www.asic-world.com/systemc/first1.html#Introduction


### Compilation/Simulation

```
make comp # Compilation
make run  # Simulation
make wave # Lauch Gtkwave
```

## And2 gate

Code written following https://www.youtube.com/watch?v=NCFxBGLB5xs&list=PLcvQHr8v8MQLj9tCYyOw44X1PLisEsX-J&index=1
(code from tutorial does not seem to ba available anymore)

### Compilation/Simulation

```
make comp # Compilation
make run  # Simulation
make wave # Lauch Gtkwave
```



# SystemC-AMS example(s)

Various SystemC examples from the net, sometimes fixed to run correctly with the latest SystemC version.
Also always provided with suitable makefiles.

Tested on Ubuntu 16.04.2  "Xenial" with SystemC 2.3.1a, SystemC POC ("Proof of concept") 2.1


The environment variables SYSTEMC_HOME and SYSTEMC_AMS_HOME must be set to point to the SystemC/SystemC-AMS installation folders.

For example

```
export SYSTEMC_HOME=/opt/systemc/2.3.1a
export SYSTEMC_AMS_HOME=/opt/systemc-ams/poc2.1

```


## voltage-divider-eln

Code from https://github.com/Mulan-94/systemc-ams

### Compilation/Simulation

```
make comp # Compilation
make run  # Simulation
make wave # Lauch Gtkwave
```

