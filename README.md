# merge_sort

Multithread merge sort on C++

**requirements**:

* [mpi](https://www.open-mpi.org/)
* [python](https://www.python.org/)

**run**:

```
$ bash run.sh {array_size} {values_range} {number_of_procces}
```

**or**

```
$ ./run.sh {array_size} {values_range} {number_of_procces}
```

**for example**: `$ bash run.sh 10 100 3` - sort the array of 10 random numbers
to 100 using 3 process:

<img src="http://res.cloudinary.com/dzsjwgjii/image/upload/v1474804254/merge_sort.png" width=700px/>

for direct input use `input.txt`
