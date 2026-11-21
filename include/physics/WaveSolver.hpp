#pragma once // it tells the compiler to 
// include a header file only once per compilation
// regardless how many times it is referencedd by #include
#include <vector>
#include <stdexcept>
#include "Membrane.hpp"

#define M_PI 3.14159265358979323846

class WaveSolver{

    private:

    double dx;
    double dy;
    double dt;
    double c;
    double gamma;

    double F;
    
    double amplitude;
    double frequency; // excitation freq
    double time = 0.0;

    Membrane& membrane;
    std::vector<std::vector<double>> previousDisplacement;

    public:


    WaveSolver(Membrane& membrane, double dt, double gamma, double amplitude, double frequency)
    : membrane(membrane),
    dt(dt),
    dx(0.0),
    dy(0.0),
    c(0.0),
    amplitude(amplitude),
    frequency(frequency),
    gamma(gamma),
    time(0.0)
    
    {
        if(dt <= 0 || gamma < 0){
            throw std::invalid_argument("invalid argument(s)");
        }

        if(membrane.getGridLength() < 3 || membrane.getGridWidth() < 3){
            throw std::invalid_argument("Grid dimensions must be at least 3");
        }


        dx = (membrane.getWidth()) / (double)(membrane.getGridWidth() - 1);
        
        dy = membrane.getLength() / (double)(membrane.getGridLength() - 1);
        
        c = membrane.waveSpeed();

        checkStability();

        previousDisplacement.resize(membrane.getGridLength(), std::vector<double>(membrane.getGridWidth(), 0.0));

    };

    void update();


    private:
    double calculateLaplacian(int x, int y) const;

    void applyBoundaryConditions(std::vector<std::vector<double>>& displacement);

    void checkStability() const;

    

};



