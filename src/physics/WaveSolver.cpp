#include "WaveSolver.hpp"
#include "Membrane.hpp"
#include <cmath>


    double WaveSolver::calculateLaplacian(int x, int y) const {

        double current = membrane.getDisplacement(x,y);

        double top = membrane.getDisplacement(x-1, y);
        double bottom = membrane.getDisplacement(x+1, y);
        double left = membrane.getDisplacement(x, y-1);
        double right = membrane.getDisplacement(x, y+1);

        double laplacian = (bottom - 2*current + top)/(dy*dy) + (right - 2*current + left)/(dx*dx);

        return laplacian;
    }

    void WaveSolver::applyBoundaryConditions(std::vector<std::vector<double>>& displacement){

        for (int i = 0; i < membrane.getGridLength(); i++) {
            for (int j = 0; j < membrane.getGridWidth(); j++){
            displacement[i][0] = 0.0; // left boundary
            displacement[membrane.getGridLength() - 1][j] = 0.0; // bottom boundary
            displacement[i][membrane.getGridWidth() - 1] = 0.0;             
            displacement[0][j] = 0.0;  // top boundary
        }
    }

    }; 

    void WaveSolver::checkStability() const {

        double condition = c*dt*std::sqrt((1.0/(dx*dx))+(1.0/(dy*dy)));

        if(condition >1 ){
            throw std::invalid_argument("Unstable simulation: timestep is too large");
        }

    };


    void WaveSolver::update(){ 
        
        double F = amplitude * std::sin(2*3.14*frequency*time);

        // we create grid for the next displacement
        std::vector<std::vector<double>> nextDisplacement(
        membrane.getGridLength(),
        std::vector<double>(membrane.getGridWidth(), 0.0)
        );

        // calculate the next displacement for every interior point
          for (int i = 1; i < membrane.getGridLength() - 1; i++) {
            for (int j = 1; j < membrane.getGridWidth() - 1; j++) {

                double current = membrane.getDisplacement(i,j);
                double laplacian = calculateLaplacian(i,j);

                // we use the wave equation to calc next displacement
                nextDisplacement[i][j] = (2*current - (1-gamma*dt)*previousDisplacement[i][j] + c*c*dt*dt*laplacian + dt*dt*F)/(1+gamma*dt);

                }
        }

        applyBoundaryConditions(nextDisplacement);

        
        for (int i = 1; i < membrane.getGridLength() - 1; i++) {
            for (int j = 1; j < membrane.getGridWidth() - 1; j++) {
                
                previousDisplacement[i][j] = membrane.getDisplacement(i,j);

                membrane.setDisplacement(i, j, nextDisplacement[i][j]);
            }
        }

        time += dt;

    };
    


