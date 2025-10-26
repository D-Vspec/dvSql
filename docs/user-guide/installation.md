# Installation Guide

This guide covers installing and setting up the dvSQL lexer on various systems.

## Prerequisites

The lexer requires the following tools to build and run:

- **flex** (Fast Lexical Analyzer Generator) - version 2.6.0 or later
- **gcc** (GNU Compiler Collection) - version 7.0 or later
- **make** (Build automation tool)

## Installation by Platform

### Ubuntu/Debian

```bash
# Update package list
sudo apt-get update

# Install required packages
sudo apt-get install flex build-essential

# Verify installation
flex --version
gcc --version
make --version
```

### CentOS/RHEL/Fedora

```bash
# For CentOS/RHEL
sudo yum install flex gcc make

# For Fedora
sudo dnf install flex gcc make

# Verify installation
flex --version
gcc --version
make --version
```

### macOS

#### Using Homebrew (Recommended)
```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install required packages
brew install flex

# macOS includes gcc and make by default via Xcode Command Line Tools
xcode-select --install
```

#### Using MacPorts
```bash
sudo port install flex-devel
```

### Windows

#### Using WSL (Recommended)
1. Install Windows Subsystem for Linux (WSL)
2. Follow the Ubuntu/Debian instructions above

#### Using MinGW/MSYS2
```bash
# Install MSYS2, then:
pacman -S mingw-w64-x86_64-gcc
pacman -S flex
pacman -S make
```

## Building the Lexer

1. **Clone or download** the project files to your local machine

2. **Navigate** to the project directory:
   ```bash
   cd /path/to/dvSql
   ```

3. **Check dependencies** (optional):
   ```bash
   make check-deps
   ```

4. **Build the lexer**:
   ```bash
   make
   ```

   This will:
   - Generate C code from the flex specification
   - Compile the lexer and supporting files
   - Create the `sql_lexer` executable

## Verification

Test that the installation works correctly:

```bash
# Run a simple test
echo "SELECT * FROM users;" | ./sql_lexer

# Expected output:
# Reading from standard input...
# ----------------------------------------
# Line 1, Col 1: SELECT          'SELECT'
# Line 1, Col 8: MULTIPLY        '*'
# Line 1, Col 10: FROM            'FROM'
# Line 1, Col 15: IDENTIFIER      'users'
# Line 1, Col 20: SEMICOLON       ';'
# ----------------------------------------
# Tokenization complete.
```

## Troubleshooting

### Common Issues

#### "flex: command not found"
- **Solution**: Install flex using your system's package manager
- **Verification**: Run `which flex` to confirm installation

#### "gcc: command not found"
- **Solution**: Install GCC or build tools for your system
- **Linux**: Install `build-essential` or `gcc`
- **macOS**: Install Xcode Command Line Tools

#### "make: command not found"
- **Solution**: Install make
- **Most systems**: Included with build tools
- **Windows**: Use WSL or install MinGW/MSYS2

#### Compilation errors about missing headers
- **Solution**: Ensure you have development headers installed
- **Linux**: Install `libc6-dev` or equivalent
- **Check**: Verify with `make check-deps`

#### Permission denied errors
- **Solution**: Check file permissions
- **Fix**: `chmod +x sql_lexer` after building

### Build Flags

The Makefile supports several options:

```bash
# Clean build (removes all generated files)
make clean

# Build with debug information (default)
make DEBUG=1

# Build optimized version
make CFLAGS="-O2 -DNDEBUG"

# Verbose build output
make VERBOSE=1
```

## Next Steps

- Continue to [Quick Start Guide](quick-start.md)
- Read [Usage Examples](examples.md)
- Review [Command Line Interface](cli.md)

## Getting Help

If you encounter installation issues:

1. Check this troubleshooting section
2. Verify your system meets the prerequisites
3. Try the automated dependency check: `make check-deps`
4. Consult your system's documentation for package installation