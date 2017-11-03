# ft_ping 

This project is about recreating ping command as an introduction to raw sockets and the ICMPv4/6 protocol

## Getting Started

To use the progam for learning or use clone it locally.

### Prerequisites

What things you need to install the software and how to install them

```
gcc or clang compiler
```

### Installing

Installing just requires a clone or download


```
git clone https://github.com/afullstopdot/ft_ping.git on terminal or download the zip straight from here.
```

## Compiling the library

For use

### Break down into end to end tests

Compile the library for use, using the Makefile

```
make -C libft (Create the libft lib)
make all
```

Remove the object files

```
make clean
```

Remove the libft library

```
make fclean
```

Remove the library and recompile

```
make re
```

## ping usage

```
./ft_ping [ [-v verbose output] [-h help] ] <hostname>
```

Where “hostname” is the host you want to ping

```
verbose : verbose outpit
```
```
help : display usage
```

## Authors

* **Andre Marques** - *All* - [afullstopdot](https://github.com/afullstopdot)
* **** - *All* - [afullstopdot](https://github.com/afullstopdot)

## Resources

```
Unix Network Programming Vol 1, 3rd version
```

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Disclaimer

This message pertains to the students of 42 and WTC (WeThinkCode_).

Copying this work as is, without understanding and being able to implement your own work defeats the pedagogy and subsequently is cheating.

Goodluck!
