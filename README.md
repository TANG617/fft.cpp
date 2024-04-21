# FFT.CPP

An implementation of FFT (Fast Fourier Transform) with CPP

Use DIT-2 method

### Project overview:
- `main.cpp`: main cpp source code includes all function
- `FFT.m`: matlab code for generating validated FFT array
- `X.txt` and `Y.txt`: 1024 points signal and its corresponding FFT result
- `X_16.txt` and `Y_16.txt`: 16 points signal and its corresponding FFT result
- `Y_CPP.txt`: calculated FFT result

### Feature(no matter good or bad):
- Only use `std` and `cmath` library.
- Use very few advance feature in CPP(basically just C with class)
  - use classical Array instead of Vector
  - use Class to wrap every function