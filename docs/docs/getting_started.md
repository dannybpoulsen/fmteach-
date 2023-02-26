# Getting Started
## Building
Before getting started you need to compile FMTeach++. You need to recompile whenever you have solved an exercise

```bash
mkdir build
cd build
cmake ..
make
```



## Solving Exercises  
All exercises in FMTeach++ requires adding code to the repository. Exercises are solved by adding code to the `exercises/exer?/exer.cpp` files. It me beneficial to look around in the `lib` directory, but it should not be necessary to modify files here.   



### Running your solution to an exercise

After solving an exercise `exercisename` in the repository, you can use the  `fmteach` binary to run your solution on a program `program.whiley`   
 
```bash 
fmteach --i program.whiley --e exercisename
```

### Running the examplary solution to an exercise  

 All exercises have a lecturer-implemented solution in the repository. To run the solution to `exercisename` on the the program `program.whiley`:

 
```bash 
fmteach --s --i program.whiley --e exercisename
```


## Docker Image
You can build/run in a docker image. For this you can run the command (in the root of the repository)

```bash 
docker run --workdir /fmteach -it -v$(pwd):/fmteach --rm palanthal/fmteach_build  /bin/bash
```

You can edit the source files on you machine and just drop in to docker when you need /compile fmteach.

