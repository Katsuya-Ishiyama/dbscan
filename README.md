# DBSCAN

This is my C++ inplementation of DBSCAN which was proposed by Ester et al.(1996).

## Requirements

- OS  
  Ubuntu18.04 LTS
- Compiler  
  g++

## Build executable file

1. Please clone this repository.  
   `git clone https://github.com/Katsuya-Ishiyama/dbscan.git`
2. Move to dbscan which will be made after "git clone".
3. Build an executable file with make.  

## Usage

Please run the following command:
```shell
dbscan $ ./dbscan <input> <output> <eps> <minpoints>
```

Definition of parameters:
|parameters   |meanings                                                      |
|:------------|:-------------------------------------------------------------|
|\<input\>    |Path to input csv file.                                       |
|\<output\>   |Path to csv file to be made as a result.                      |
|\<eps\>      |The distance between two points determined to be neighborhood.|
|\<minpoints\>|Minimum number of points composed as a cluster.               |
