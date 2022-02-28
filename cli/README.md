# 42 labs - CLI

![IMAGE](./images/draw.svg)

### This project was developed for the 42 labs selective process

## Usage

### Requirements

This project requires *gcc* compiler.

### Instructions

In the repository's directory, run `make`

```sh
make 
```

> `make` suports 4 flags: 
> - `make all` or simply `make` compiles the project
> - `make clean` deletes the `.o` files generated during compilation
> - `make fclean` deletes the `.o` and the executable file
> - `make re` executes `fclean` and `all` in sequence

After this you can run the executable file:

```sh
./cli42labs
```

This program accept 3 flags:

  -h, --help				Display the help menu


  -n, --number [<text>]		Prints the number of logs, if a text is passed, prints all logs that contain the occurrence of the text


  -t, --target <text>		Prints all logs that contain the occurrence of the text passed
