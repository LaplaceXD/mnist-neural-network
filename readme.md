# MNIST Neural Network in C

A small project that was inspired by [Mark Kraay's Video](https://www.youtube.com/watch?v=ReOxVMxS83o), where he created a Neural Network from Scratch in C. This led me to a rabbit hole in machine learning, where I started learning about the mathematics behind machine learning, forward propagation, backward propagation, neural network architecture, and so on. Now, it would be boring if all I learned are theories, thus I wanted to try making my own rendition of a Neural Network in C, using the [MNIST digit dataset](https://git-disl.github.io/GTDLBench/datasets/mnist_datasets/).

## Usage

- Install a C compiler, preferably [GCC](https://sourceforge.net/projects/mingw-w64/).
- **[Optional]** Install [Make](https://sourceforge.net/projects/ezwinports/files/make-4.3-without-guile-w32-bin.zip/download) to make use of `MakeFile` and instantly compile binaries.

Without `MakeFile`:
```bash
gcc lib/stats.c -o output/stats.o -c
gcc lib/matrix.c -o output/matrix.o -c
gcc lib/doubly_ll.c -o output/doubly_ll.o -c
gcc lib/image_set.c -o output/image_set.o -c
gcc lib/neural_net.c -o output/neural_net.o -c
gcc main.c -o output/main.o -c
cd output
gcc -o mnist main.o matrix.o stats.o image_set.o neural_net.o doubly_ll.o -c
```
With `MakeFile`:
```bash
make
```

You can then run the compiled `mnist.exe` program using `./mnist` in the console.

## Libraries Created

There are currently 5 libraries that I created for this project. They are completely reusable depending on the needs of your project. However, do take note of their header files and dependencies when copying. The documentation for the functions stored in these libraries can be found in their respective header files.

| Library      | Dependencies      | Description |
|:-------------|:------------------|:------------|
|**stats**     | none              | A utility library which contains different statistical functions. |
|**matrix**    | none              | A library for working with matrices. |
|**doubly_ll** | none              | A library for working with doubly linked list. |
|**image_set** | matrix, ml        | A library for working with the MNIST digit dataset. |
|**neural_net**| matrix, doubly_ll | A library for creating and working with neural networks. |
|**ml**        | WIP               | WIP |

## Bibliography
- [3Blue1Brown - Deep Learning Series](https://www.youtube.com/watch?v=aircAruvnKk&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi&index=1)
- [Gradient Descent](https://vitalflux.com/gradient-descent-explained-simply-with-examples/)
- [Samson Zhong - Building a Neural Network From Scratch (Numpy & Maths)](https://www.youtube.com/watch?v=w8yWXqWQYmU&t=1612s)
- [Neural Network from Scratch | Mathematics & Python Code](https://www.youtube.com/watch?v=pauPCy_s0Ok)
- [Normalization VS Standardization of Data](https://stackoverflow.com/questions/63746182/correct-way-of-normalizing-and-scaling-the-mnist-dataset)
- [What is a Makefile and how does it work?](https://opensource.com/article/18/8/what-how-makefile)
- [Weight Initialization Techniques in Neural Networks](https://towardsdatascience.com/weight-initialization-techniques-in-neural-networks-26c649eb3b78)
- [Bias Initialization in a Neural Network](https://medium.com/@glenmeyerowitz/bias-initialization-in-a-neural-network-2e5d26fed0f0)

## License
[MIT](https://github.com/LaplaceXD/mnist-neural-network/blob/master/LICENSE)