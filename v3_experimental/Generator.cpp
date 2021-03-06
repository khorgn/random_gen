#include "Generator.hpp"
#include "Strategy.hpp"
#include <iostream>


PerlinNoise::PerlinNoise(int* sizes, int dimension):
  _tab(sizes, dimension){
  
  generate();
}

double PerlinNoise::blank_noise(int* values){
  double output = 0;
  for(int i=0 ; i<_tab.get_dimension() ; ++i){
    output += PerlinNoise::random(values[i] + (int)(output*850000));
  }
  return output;
}// double PerlinNoise::blank_noise(int* values)

void PerlinNoise::set_strategy(Strategy& strategy){
  
  _strategy = &strategy;
}

Strategy& PerlinNoise::get_strategy(){
  return *_strategy;
}

void PerlinNoise::display(){
  _tab.display();
}

double PerlinNoise::random(int seed){
    seed = (seed<<13) ^ seed;
    seed = (seed * (seed * seed * 15731 + 789221) + 1376312589);
    return 1.0 - (seed & 0x7fffffff) / 1073741824.0;
}// static double PerlinNoise::random(int seed)

void PerlinNoise::generate(){
  int* coordinates;
  double value = 0;
  for(int i=0 ; i<_tab.get_total_size() ; ++i){
    coordinates = _tab.get_coordinates(i);
    value = blank_noise(coordinates);
    //    std::cout << "value(" << i <<") = " << value << std::endl;
    //    std::cout << "0: " << coordinates[0] << ", 1: " << coordinates[1] << ", 2: " << coordinates[2] << std::endl;
    _tab.set_cell(coordinates, value);
  }

  for(int i=0 ; i<tab.get_total_size() ; ++i){
  }
}

void PerlinNoise::execute(){
  //  std::cout << "in PerlinNoise::execute()" << std::endl;
  _strategy->execute(_tab);
  //  std::cout << "out of PerlinNoise::execute()" << std::endl;
}

double PerlinNoise::perlin(int octaves, double frequency, double persistence, double x){
  double r = 0.;
  double f = frequency;
  double amplitude = 1.;
  for(int i = 0; i < octaves; i++){
    //Translation of the symetric center in i * 4096
    int t = i * 4096;
    //Calcul of the translated noise
    r += _strategy->smooth_noise(x * f + t) * amplitude;
    amplitude *= persistence;
    f *= 2;
  }
  double geo_lim = (1 - persistence) / (1 - amplitude);
  return r * geo_lim;
}


