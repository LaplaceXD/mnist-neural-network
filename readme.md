# MNIST Neural Network in C

A small project that was inspired by [Mark Kraay's Video](https://www.youtube.com/watch?v=ReOxVMxS83o), where he created a Neural Network from Scratch in C. This led me to a rabbit hole in machine learning, where I started learning about the mathematics behind machine learning, forward propagation, backward propagation, neural network architecture, and so on. Now, it would be boring if all I learned are theories, thus I wanted to try making my own rendition of a Neural Network in C, using the [MNIST digit dataset](https://git-disl.github.io/GTDLBench/datasets/mnist_datasets/),

## Usage

- Install a C compiler, preferably [GCC](https://sourceforge.net/projects/mingw-w64/).

```bash
gcc lib/matrix/matrix.c -o output/matrix.o -c
gcc main.c -o output/main.o -c
gcc -o mnist output/main.o output/matrix.o
```
You can then run the compiled `mnist.exe` program using `./mnist` in the console.

## Bibliography
- [3Blue1Brown - Deep Learning Series](https://www.youtube.com/watch?v=aircAruvnKk&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi&index=1)
- [Gradient Descent](https://vitalflux.com/gradient-descent-explained-simply-with-examples/)
- [Samson Zhong - Building a Neural Network From Scratch (Numpy & Maths)](https://www.youtube.com/watch?v=w8yWXqWQYmU&t=1612s)
- [Neural Network from Scratch | Mathematics & Python Code](https://www.youtube.com/watch?v=pauPCy_s0Ok)

## License
[MIT](https://github.com/LaplaceXD/mnist-neural-network/blob/master/LICENSE)